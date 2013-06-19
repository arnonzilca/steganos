#include "covert_data_receiver.h"

void CovertDataReceiver::receiveByte() const {
	unsigned char c = 0;							// will hold the character to be gathered.
	for (int i = 0; i < 8; ++i) {					// foreach bit in a byte
		c |= covertChannelReceiver->readBit() << i;	// setting the read bit to it's place (i) in the byte being read.
	}
	receiveDataHandler.handleReceivedByte(c);		// informing a byte has been read to handle.
}
