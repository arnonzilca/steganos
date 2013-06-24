#include <stdio.h>

#include "stdio_data_handlers.h"

void StdioCovertDataReceiver::loopDataHandling() const {
	while (true) {
		covertDataReceiver.receiveByte();
	}
}

void StdioCovertDataReceiver::handleReceivedByte(unsigned char byte) {
    fputc(byte, stdout);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void StdioCovertDataTransmitter::loopDataHandling() const {
	while (true) {
		covertDataTransmitter.transmitByte(getchar());
	}
}
