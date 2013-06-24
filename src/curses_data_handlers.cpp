#include "curses_data_handlers.h"

#include <ncurses.h>

using namespace std;

void CursesCovertDataReceiver::loopDataHandling() const {
	initscr();								// clearing screen with curses.
	refresh();
	while (true) {							// looping forever on
		covertDataReceiver.receiveByte();	// receiving bytes from covertDataReceiver.
	}
}

void CursesCovertDataReceiver::handleReceivedByte(unsigned char byte) {
	printw("%c", byte);						// print the byte when received
	refresh();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CursesCovertDataTransmitter::loopDataHandling() const {
	initscr();								// clearing screen with curses.
	refresh();
	while (true) {
		// reading a character from the keyboard and transmitting it.
		covertDataTransmitter.transmitByte(getch());
	}
}
