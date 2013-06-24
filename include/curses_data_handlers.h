#ifndef _CURSES_DATA_HANDLERS_H_
#define _CURSES_DATA_HANDLERS_H_

#include "covert_data_receiver.h"
#include "covert_data_transmitter.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// The ICursesDataHandler interface will be used to conceal the transmitting or receiving	//
// nature of a curses infrastructure using class being a transmitter or receiver and		//
// printing its data with curses infrastructure.											//
//////////////////////////////////////////////////////////////////////////////////////////////

class ICursesDataHandler {
public:
	virtual ~ICursesDataHandler() {}
	virtual void setCovertChannel(ICovertChannel& covertChannel)=0;		// setting a bussiness logic covert channel.
	virtual void loopDataHandling() const=0;							// looping receiving or transmitting data.
};


//////////////////////////////////////////////////////////////////////////////////////////////
// The CursesCovertDataReceiver class will be used receive data using a CovertDataReceiver	//
// and printing it via curses infrastructure.												//
// This class will also be used as an IReceiveDataHandler for handling received data from	//
// CovertDataReceiver.																		//
//////////////////////////////////////////////////////////////////////////////////////////////

class CursesCovertDataReceiver : public ICursesDataHandler, public IReceiveDataHandler {
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

class CursesCovertDataTransmitter : public ICursesDataHandler {
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
