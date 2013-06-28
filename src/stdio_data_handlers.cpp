#include <stdio.h>
#include <stdlib.h>

#include "stdio_data_handlers.h"

void StdioCovertDataReceiver::loopDataHandling() const {
	while (true) {
		covertDataReceiver.receiveByte();
	}
}

void StdioCovertDataReceiver::handleReceivedByte(unsigned char byte) {
	// Note that the received byte is an actual byte, and cannot be EOF. So
	// without an additional mechanism to signify EOF over the channel, we
	// can't quit on EOF here.
	fputc(byte, stdout);

	// Since we have no mechanism of "proper closing", and output might be to a
	// file, we have to make sure we flush output before we're killed.
	fflush(stdout);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void StdioCovertDataTransmitter::loopDataHandling() const {
	while (true) {
		int charToSend = getchar();

		// Upon EOF, getchar() will return with EOF ad infinitum, causing us to
		// spam the receiving end. Instead, we quit on EOF, like ordinary
		// data-driven unix programs.
		if (charToSend == EOF) {
			exit(0);
		}

		covertDataTransmitter.transmitByte(charToSend);
	}
}
