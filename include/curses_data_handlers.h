#ifndef _CURSES_DATA_HANDLERS_H_
#define _CURSES_DATA_HANDLERS_H_

#include "covert_data_receiver.h"
#include "covert_data_transmitter.h"
#include "data_handlers.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// The CursesCovertDataReceiver class will be used receive data using a CovertDataReceiver	//
// and printing it via curses infrastructure.												//
// This class will also be used as an IReceiveDataHandler for handling received data from	//
// CovertDataReceiver.																		//
//////////////////////////////////////////////////////////////////////////////////////////////

class CursesCovertDataReceiver : public IDataHandler, public IReceiveDataHandler {
public:
	
	CursesCovertDataReceiver()
	: covertDataReceiver(*this)
	{}
	
	virtual ~CursesCovertDataReceiver() {}

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

class CursesCovertDataTransmitter : public IDataHandler {
public:
	virtual ~CursesCovertDataTransmitter() {}

	virtual void setCovertChannel(ICovertChannel& covertChannel) {
		covertDataTransmitter.setCovertChannelTransmitter(covertChannel);
	}
	
	virtual void loopDataHandling() const;					// will loop reading keyboard input and transmitting it.

protected:
	CovertDataTransmitter covertDataTransmitter;
};

#endif
