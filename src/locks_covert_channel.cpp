#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "locks_covert_channel.h"
#include "message_exception.h"

using namespace std;

LocksCovertChannel::LocksCovertChannel() 
: receiverArrived(false)
, transmitterArrived(false) {
	// setting up all locks.
	if ((dataLock		= sem_open("dataLock",		O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED ||
		(firstSyncLock	= sem_open("firstSyncLock",	O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED ||
		(lockA			= sem_open("lockA",			O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED ||
		(lockB			= sem_open("lockB",			O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED ||
		(lockC			= sem_open("lockC",			O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED ) {
		throw MessageException("<LocksCovertChannel::c'tor> Error: Failed to open semaphores!");
	}
}

void LocksCovertChannel::writeBit(bool bit) {
	if (!receiverArrived) {
		waitForAReceiver();		// waiting for first sync with a receiver.
	}
	takeLockFromQueues();		// locks a lock from unlockedQueue.
	writeData(bit);
	releaseLockFromQueues();	// releases a lock from lockedQueue.
}

bool LocksCovertChannel::readBit() {
	if (!transmitterArrived) {
		waitForATransmitter();	// waiting for first sync with a transmitter.
	}
	takeLockFromQueues();		// locks a lock from unlockedQueue.
	bool readBit = readData();
	releaseLockFromQueues();	// releases a lock from lockedQueue.
	return readBit;
}

void LocksCovertChannel::waitForAReceiver() {
	// semaphores are tricky creatures.
	// when a process dies the OS doesn't free it's locks,
	// and since other processes runs are involved, releasing
	// all locks and not releasing 'too much' is pretty hard,
	// especially if a process is 'terminated'.
	// therefore clearing all the locks is performed every run
	// and is only called by the transmitter.
	// this also explains the use of firstSyncLock
	// which is a more 'controled' lock than A, B & C.
	clearAllLocks();			

	unlockedQueue.push(lockA);					// -| putting the locks in the unlockedQueue.
	unlockedQueue.push(lockB);					//  | notice the different order of queueing those locks
	unlockedQueue.push(lockC);					// -| when comparing to a receiver's order.

	takeLockFromQueues();						// locking the first lock in the unlockedQueue.
	sem_wait(firstSyncLock);					// locking the firstSyncLock indicating wait for a receiver.
	while (getLockValue(lockC) != 0) {			// waiting for a receiver to take lockC.
	}
	receiverArrived = true;						// marking that a receiver has arrived and first sync is over.
	sem_post(firstSyncLock);					// releasing firstSyncLock.
}

void LocksCovertChannel::waitForATransmitter() {
	unlockedQueue.push(lockC);					// -| putting the locks in the unlockedQueue.
	unlockedQueue.push(lockA);					//  | notice the different order of queueing those locks
	unlockedQueue.push(lockB);					// -| when comparing to a transmitter's order.

	while (getLockValue(firstSyncLock) != 0) {	// waiting for a transmitter to take firstSyncLock.
	}
	transmitterArrived = true;					// marking that a transmitter has arrived and first sync is over.
	takeLockFromQueues();						// locking the first lock in the unlockedQueue.
}

void LocksCovertChannel::takeLockFromQueues() {
	sem_t* lock = unlockedQueue.front();		// getting the first of unlockedQueue.
	unlockedQueue.pop();						// taking it out.
	lockedQueue.push(lock);						// pushing it to lockedQueue.
	sem_wait(lock);								// waiting to lock the new lock.
}

void LocksCovertChannel::releaseLockFromQueues() {
	sem_t* lock = lockedQueue.front();			// getting the first of lockedQueue.
	lockedQueue.pop();                          // taking it out.
	unlockedQueue.push(lock);                   // pushing it to unlockedQueue.
	sem_post(lock);                             // unlock the lock.
}

void LocksCovertChannel::clearAllLocks() const {
	clearLock(dataLock);
	clearLock(firstSyncLock);
	clearLock(lockA);
	clearLock(lockB);
	clearLock(lockC);
}

void LocksCovertChannel::clearLock(sem_t* sem) const {
	// clearing a lock is also tricky.
	// a lock can be preoccupied and can't be used
	// and can also be 'too free' if sem_post is overused
	// which will cause it to able to be locked several times
	// even if it's declaration marked only 1 locking it at a time.
	
	// therefore one loop is set to lock it so that it will only be free once (if needed).
	while (getLockValue(sem) > 1) {
		sem_wait(sem);
	}
	// and another loop is set to release the lock so that it will only be free once (if needed).
	while (getLockValue(sem) < 1) {
		sem_post(sem);
	}
}

void LocksCovertChannel::writeData(bool bit) const {
	clearLock(dataLock);			// clear data lock (we can't know it's state).
	if (bit) {						// if bit is true,
		sem_wait(dataLock);			// then lock the dataLock.
	}
}

bool LocksCovertChannel::readData() const {
	int lockValue = getLockValue(dataLock);	// get the locks value
	return lockValue == 0;	// lock value is 0 if it was locked by the transmitter.
}

int LocksCovertChannel::getLockValue(sem_t* sem) const {
	int value;
	if (sem_getvalue(sem, &value) != 0) {
		throw MessageException("<LocksCovertChannel::readData> Error: Failed to check semaphore!");
	}
	return value;
}
