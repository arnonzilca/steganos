#include <getopt.h>
#include <stdlib.h>
#include <iostream>
#include <ncurses.h>

#include "message_exception.h"
#include "locks_covert_channel.h"
#include "file_permissions_covert_channel.h"
#include "curses_data_handlers.h"
#include "stdio_data_handlers.h"

using namespace std;

void printUsage();

int main(int argc, char** argv)
{
	ICovertChannel* covertChannel = NULL;			// creating generic covert channel pointer.
	IDataHandler* cursesDataHandler = NULL;	// creating generic data handler pointer.

	if (argc > 3) {
		cout << "Error: Too many arguments. see help screen (-h/--help)." << endl;	
		exit(1);
	}

	// setting getopt infrastructure for argument reading.
	char c;
	int option_index;
	static struct option long_options[] = {
               {"help",				optional_argument, 0, 'h'},
               {"transmitter",		optional_argument, 0, 't'},
               {"receiver",			optional_argument, 0, 'r'},
               {"file-permissions",	optional_argument, 0, 'f'},
               {"locks",			optional_argument, 0, 'l'},
               {0, 0, 0, 0}};
	try {
		while ((c = getopt_long(argc, argv, "htrfl", long_options, &option_index)) != -1) {
			switch (c) {
				case 'h':
					printUsage();
					exit(0);
				  break;
				case 't':
					cursesDataHandler = new CursesCovertDataTransmitter();
				  break;
				case 'r':
					cursesDataHandler = new CursesCovertDataReceiver();
				  break;
				case 'f':
					covertChannel = new FilePermissionsCovertChannel();
				  break;
				case 'l':
					covertChannel = new LocksCovertChannel();
				  break;
				case '?':
				  return 1;
				default:
				  exit(10);
			}
		}

		if (cursesDataHandler == NULL) {
			cout << "Error: No role was selected. see help screen (-h/--help)." << endl;
			exit(2);
		}
		if (covertChannel == NULL) {
			cout << "Error: No method was selected. see help screen (-h/--help)." << endl;
			exit(3);
		}

		// connecting the specific curses data handler with the specific covert channel.
		cursesDataHandler->setCovertChannel(*covertChannel);
		// looping on transmitting/receiving data.
		cursesDataHandler->loopDataHandling();
	}
	catch (MessageException& ex) {
		endwin();
		cout << ex.what() << endl;;
	}

	return 0;
}


void printUsage()
{
	cout << "steganos - transfer data steganographically."										<< endl;
	cout << "Usage: steganos ROLE METHOD"														<< endl;
	cout << "Roles:"																			<< endl;
	cout << "   -t, --transmitter       sets the process as transmitter."                       << endl;
	cout << "   -r, --receiver          set the process as receiver."                           << endl;
	cout << "Methods:"                                                                          << endl;
	cout << "   -f, --file-permissions  sets the transmission method to be file permissions."   << endl;
	cout << "   -l, --locks             sets the transmission method to be locks."              << endl;
}
