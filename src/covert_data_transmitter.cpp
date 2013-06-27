#include "covert_data_transmitter.h"

void CovertDataTransmitter::transmitByte(unsigned char byte) const {
	for (int i = 0; i < 8; ++i) {								// foreach bit in the byte
		covertChannelTransmitter->writeBit((byte >> i) & 1);	// writing the current (i) bit of the byte.
	}
}
