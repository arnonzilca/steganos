#ifndef _COVERT_DATA_TRANSMITTER_H_
#define _COVERT_DATA_TRANSMITTER_H_

#include "icovert_channel.h"

//////////////////////////////////////////////////////////
// The CovertDataTransmitter class will handle byte		//
// transmittion using an ICovertChannelTransmitter.		//
//////////////////////////////////////////////////////////

class CovertDataTransmitter {
public:
	virtual ~CovertDataTransmitter() {}

	void setCovertChannelTransmitter(ICovertChannelTransmitter& covertChannelTransmitter) {
		this->covertChannelTransmitter = &covertChannelTransmitter;
	}

	void transmitByte(unsigned char byte) const;

private:
	ICovertChannelTransmitter* covertChannelTransmitter;
};

#endif
