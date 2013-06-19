#include <sys/stat.h>
#include <stdlib.h>
#include <fstream>

#include "file_permissions_covert_channel.h"
#include "message_exception.h"

using namespace std;

const char FilePermissionsCovertChannel::FILE_NAME[] = "/tmp/innocent_file";
const int  FilePermissionsCovertChannel::SYNC_BIT_POS = 0;
const int  FilePermissionsCovertChannel::DATA_BIT_POS = 1;
const bool FilePermissionsCovertChannel::SYNC_BIT_WRITE_STATE = false;


FilePermissionsCovertChannel::FilePermissionsCovertChannel() {
	//creating the file
	ofstream outfile(FILE_NAME);
	outfile << "These are not the files you're looking for..." << endl;
	outfile.close();
}

void FilePermissionsCovertChannel::writeBit(bool bit) {
	bool syncBit = readPermissionsBit(SYNC_BIT_POS);			// reading the sync bit.

	while (syncBit != SYNC_BIT_WRITE_STATE) {					// checking if the sync marks 'write'.
		syncBit = readPermissionsBit(SYNC_BIT_POS);				// reading the sync bit again.
	}

	writePermissionsBit(bit, DATA_BIT_POS);						// writing the data bit.
	writePermissionsBit(!SYNC_BIT_WRITE_STATE, SYNC_BIT_POS);	// setting the sync bit to 'read'.
}

bool FilePermissionsCovertChannel::readBit() {
	bool syncBit = readPermissionsBit(SYNC_BIT_POS);			// reading the sync bit.

	while (syncBit == SYNC_BIT_WRITE_STATE) {					// checking if the sync marks 'read'.
		syncBit = readPermissionsBit(SYNC_BIT_POS);				// reading the sync bit again.
	}

	bool readDataBit = readPermissionsBit(DATA_BIT_POS);		// reading the data bit.
	writePermissionsBit(SYNC_BIT_WRITE_STATE, SYNC_BIT_POS);	// setting the sync bit to 'write'.
	return readDataBit;
}


bool FilePermissionsCovertChannel::readPermissionsBit(int pos) const {
	struct stat fileStat;
	if (stat(FILE_NAME, &fileStat) < 0) {	// getting the file's stats.
		throw MessageException("<FilePermissionsCovertChannel::readPermissionsBit> Error reading file stat.");
	}
	
	return (fileStat.st_mode >> pos) & 1;	// returning the bit at pos from the file's permissions.
}

void FilePermissionsCovertChannel::writePermissionsBit(bool bit, int pos) const {
	struct stat fileStat;
	if (stat(FILE_NAME, &fileStat) < 0) {	// getting the file's stats.
		throw MessageException("<FilePermissionsCovertChannel::writePermissionsBit> Error reading file stat.");
	}

	mode_t mode = fileStat.st_mode;			// reading the file's current mode.
	if (bit == true) {
		mode |= 1 << pos;					// setting the bit at pos to true
	}
	else {
		mode &= ~(1 << pos);				// setting the bit at pos to false
	}

	if (chmod(FILE_NAME, mode) < 0) {		// changing the file's mode. 
		throw MessageException("<FilePermissionsCovertChannel::writePermissionsBit> Error writing chmod.");
	}
}
