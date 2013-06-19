#ifndef _LOCKS_COVERT_CHANNEL_H_
#define _LOCKS_COVERT_CHANNEL_H_

#include <semaphore.h>
#include <queue>

#include "icovert_channel.h"

//////////////////////////////////////////////////////////////////////////////////////
// The LocksCovertChannel class will handle sending covert information using locks.	//
// the data itself will be sent using a 'data lock', whereas the syncing will be	//
// achieved by three locks in a queue (acctually two queues). Each of the			//
// transmitter or receiver will allways lock one lock while and try to capture		//
// the third one. Who ever achieves the third one will get to read/write.			//
// a fourth sync lock (fifth in general) will be used for first sync.				//
//////////////////////////////////////////////////////////////////////////////////////

class LocksCovertChannel : public ICovertChannel {
public:
	LocksCovertChannel();
	virtual ~LocksCovertChannel() {}

	virtual void writeBit(bool bit);	// (overrides ICovertChannel) will be used to write a data bit.
	virtual bool readBit();				// (overrides ICovertChannel) will be used to read a data bit.

protected:
	virtual void waitForAReceiver();		// will be used as first sync for the first time transmitting.
	virtual void waitForATransmitter();		// will be used as first sync for the first time receiving.

	virtual void takeLockFromQueues();		// will take a lock not taken by this process from unlockedQueue and lock it.
	virtual void releaseLockFromQueues();	// will take a lock taken by this process from lockedQueue and release it.

	virtual void clearAllLocks() const;			// will clear all the locks.
	virtual void clearLock(sem_t* sem) const;	// will clear a specific lock.

	virtual void writeData(bool bit) const;		// will write data to the data lock.
	virtual bool readData() const;				// will read data from the data lock.

	virtual int getLockValue(sem_t* sem) const;	// will get a lock's value (how many available on this semaphore).

	sem_t* dataLock;			// will hold the data sent.
	sem_t* firstSyncLock;		// will be used for first syncing.
	sem_t* lockA;				// will be used for syncing.
	sem_t* lockB;				// will be used for syncing.
	sem_t* lockC;				// will be used for syncing.

	bool receiverArrived;				// will indicate first negotiation with a receiver has been accomplished.
	bool transmitterArrived;			// will indicate first negotiation with a transmitter has been accomplished.
	std::queue<sem_t*> lockedQueue;		// will be used to hold locks that are locked by this process.
	std::queue<sem_t*> unlockedQueue;	// will be used to hold locks that are not locked by this process.
};

#endif
