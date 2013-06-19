#ifndef _COVERT_DATA_RECEIVER_H_
#define _COVERT_DATA_RECEIVER_H_

#include "icovert_channel.h"

//////////////////////////////////////////////////////////
// The IReceiveDataHandler interface will be used		//
// as an event mechanism in case a CovertDataReceiver	//
// receives data he likes to share.						//
//////////////////////////////////////////////////////////

class IReceiveDataHandler {
public:
	virtual ~IReceiveDataHandler() {}
	virtual void handleReceivedByte(unsigned char byte)=0;
};


//////////////////////////////////////////////////////////
// The CovertDataReceiver class will handle byte		//
// receiving using an ICovertChannelReceiver.			//
// When data is received and gathered to a byte,		//
// the receiveDataHandler will be used to inform.		//
//////////////////////////////////////////////////////////

class CovertDataReceiver {
public:
	CovertDataReceiver(IReceiveDataHandler& _receiveDataHandler)
	:	receiveDataHandler(_receiveDataHandler)
	{}

	virtual ~CovertDataReceiver() {}
	
	void setCovertChannelReceiver(ICovertChannelReceiver& covertChannelReceiver) {
		this->covertChannelReceiver = &covertChannelReceiver;
	}

	void receiveByte() const;

protected:
	ICovertChannelReceiver* covertChannelReceiver;
	IReceiveDataHandler& receiveDataHandler;
};

#endif
