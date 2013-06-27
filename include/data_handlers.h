#ifndef _DATA_HANDLERS_H_
#define _DATA_HANDLERS_H_

#include "covert_data_receiver.h"
#include "covert_data_transmitter.h"

//////////////////////////////////////////////////////////////////////////////////////
// The IDataHandler interface will be used to conceal the transmitting or receiving //
// nature of an I/O infrastructure using class being a transmitter or receiver and  //
// printing its data with the same I/O infrastructure.                              //
//////////////////////////////////////////////////////////////////////////////////////

class IDataHandler {
public:
	virtual ~IDataHandler() {}
	virtual void setCovertChannel(ICovertChannel& covertChannel)=0;		// setting a bussiness logic covert channel.
	virtual void loopDataHandling() const=0;							// looping receiving or transmitting data.
};

#endif
