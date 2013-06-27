#ifndef _MESSAGE_EXCEPTION_H_
#define _MESSAGE_EXCEPTION_H_

#include <exception>

//////////////////////////////////////////////////////////////////////////
// The MessageException class will be used to throw simple exceptions	//
// holding a simple message and a constructor to receive that message.	//
//////////////////////////////////////////////////////////////////////////

class MessageException : std::exception {
public:
	MessageException(const char* exceptionMessage)
	: message(exceptionMessage)
	{}
	virtual ~MessageException() throw() {}

	virtual const char* what() const throw() { return message; }

protected:
	const char* message;
};

#endif
