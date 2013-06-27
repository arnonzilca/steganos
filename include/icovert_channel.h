#ifndef _ICOVERT_CHANNEL_H_
#define _ICOVERT_CHANNEL_H_

//////////////////////////////////////////////////////////////////////////////////////////////
// The ICovertChannelTransmitter interface is used to indicate a covert channel transmitter.//
// It can be used by a trasmitter process to transmit bits to a receiver.					//
//////////////////////////////////////////////////////////////////////////////////////////////

class ICovertChannelTransmitter {
public:
	virtual ~ICovertChannelTransmitter() {}
	virtual void writeBit(bool bit)=0;		// will be used to write a data bit.
};



//////////////////////////////////////////////////////////////////////////////////////////////
// The ICovertChannelReceiver interface is used to indicate a covert channel receiver.		//
// It can be used by a receiver process to receive bit from a transmitter.					//
//////////////////////////////////////////////////////////////////////////////////////////////

class ICovertChannelReceiver {
public:
	virtual ~ICovertChannelReceiver() {}
	virtual bool readBit()=0;				// will be used to read a data bit.
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The ICovertChannel interface consolidates the ICovertChannelTransmitter and ICovertChannelReceiver interfaces.	//
// Its main function is using one covert channel implementation to appear as either transmitting or receiving.		//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ICovertChannel :	public ICovertChannelTransmitter,
						public ICovertChannelReceiver		{
public:
	virtual ~ICovertChannel() {}
};


#endif
