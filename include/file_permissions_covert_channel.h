#ifndef _FILE_PERMISSIONS_COVERT_CHANNEL_H_
#define _FILE_PERMISSIONS_COVERT_CHANNEL_H_

#include "icovert_channel.h"

//////////////////////////////////////////////////////////////////////////////////////
// The FilePermissionsCovertChannel class will handle sending covert information	//
// using two bits of a certain file's permission data.								//
// One bit used as sync bit between a transmitter process and a receiver one		//
// (it's function is to indicate a transmitter process that it can now transmit		//
// and a receiver process that it can now receive).									//
// The other bit is used to transfer the data.										//
//////////////////////////////////////////////////////////////////////////////////////

class FilePermissionsCovertChannel : public ICovertChannel {
public:
	FilePermissionsCovertChannel();
	virtual ~FilePermissionsCovertChannel() {}

	virtual void writeBit(bool bit);	// (overrides ICovertChannel) will be used to write a data bit.
	virtual bool readBit();				// (overrides ICovertChannel) will be used to read a data bit.

protected:
	
	bool readPermissionsBit(int pos) const;		// will read and return the bit at pos from the file's permission.
	void writePermissionsBit(bool value, int pos) const;	// will write value to pos in the file's permission.
	
	static const char FILE_NAME[];				// name of the file a transmitter and a receiver will share.
	static const int SYNC_BIT_POS;				// the position of the sync bit.
	static const int DATA_BIT_POS;				// the position of the data bit.
	static const bool SYNC_BIT_WRITE_STATE;		// indicates whether sync bit = true means transmitting or receiving.
};

#endif
