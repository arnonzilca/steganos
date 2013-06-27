#ifndef _STDIO_DATA_HANDLERS_H_
#define _STDIO_DATA_HANDLERS_H_

#include "data_handlers.h"
#include "covert_data_receiver.h"
#include "covert_data_transmitter.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// The StdioCovertDataReceiver class will be used receive data using a CovertDataReceiver   //
// and printing it via standard I/O.                                                        //
// This class will also be used as an IReceiveDataHandler for handling received data from	//
// CovertDataReceiver.																		//
//////////////////////////////////////////////////////////////////////////////////////////////

class StdioCovertDataReceiver : public IDataHandler, public IReceiveDataHandler {
public:

	StdioCovertDataReceiver()
	: covertDataReceiver(*this)
	{}
	
	virtual ~StdioCovertDataReceiver() {}

	virtual void setCovertChannel(ICovertChannel& covertChannel) {
		covertDataReceiver.setCovertChannelReceiver(covertChannel);
	}

	virtual void loopDataHandling() const ;					// will loop receiving bytes.
	virtual void handleReceivedByte(unsigned char byte);	// (overrides IReceiveDataHandler) will print the received byte.

protected:
	CovertDataReceiver covertDataReceiver;
};


//////////////////////////////////////////////////////////////////////////////////////////////
// The CursesCovertDataTransmitter class will be used to transmit data gathered from the	//
// user's keyboard using a CovertDataTransmitter and the curses infrastructure.				//
//////////////////////////////////////////////////////////////////////////////////////////////

class StdioCovertDataTransmitter : public IDataHandler {
public:
	virtual ~StdioCovertDataTransmitter() {}

	virtual void setCovertChannel(ICovertChannel& covertChannel) {
		covertDataTransmitter.setCovertChannelTransmitter(covertChannel);
	}
	
	virtual void loopDataHandling() const;					// will loop reading keyboard input and transmitting it.

protected:
	CovertDataTransmitter covertDataTransmitter;
};

#endif
