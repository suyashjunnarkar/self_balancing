#ifndef __PCF_INCLUDED_DEBUG_CPP_DEBUG_H
#define __PCF_INCLUDED_DEBUG_CPP_DEBUG_H

#if (PCF_LANGUAGE & PCF_LANGUAGE_ANY_CPP)
#include<string>
namespace pcf
{

/** \addtogroup pcf
*  @{
*/


/**A class which defines few methods which are used by macros pcf_assert,
pcf_assert_with_message, pcf_check_for_null_pointer, pcf_report_bug, pcf_report_bug_with_mesage
pcf_report_unexpected_error, pcf_report_unexpected_error_with_message, pcf_debug, pcf_debug_info,
pcf_debug_error.

@remarks
Use the macros to keep the client code uniform across the languges (C/C++)
*/

	class PCF_API DebugSupport
	{
	public:

	/*
	When an assertion fails, this method is responsible for breaking into the code and attaching
	the debugger to it, since this debug break is compiler dependent it is not always possible to
	have this behavior out of implementation. If the exception support is present then it also throws
	an exception. What exception is exactly thrown will be dependent on the implementation.

	@param
	condition  The condition which failed and resulted into the failure.
	@param
	file  The file where this assertion failed.
	@param
	line The line number where the assertion of condition failed.
	@param
	message The message to be shown when the assertion fails.
	*/
	static void assert(Cstring_t condition, Cstring_t file, int line, Cstring_t message = 0);

	/*
	Checks if the pointer was null and if it is, then, this method is responsible for breaking into the
	code and attaching the debugger to it, since this debug break is compiler dependent it is not always
	possible to have this behavior out of implementation. If the exception support is present then it
	also throws an exception. What exception is exactly thrown will be dependent on the implementation.
	@param
	condition  The string representation of poniter to the variable.
	@param
	file  The file where the pointer was checked.
	@param
	line The line number where the pointer was checked.
	@param
	message The message to be shown when the pointer was null.
	*/
	static void checkForNullPointer(Cstring_t pointerToCheck, Cstring_t file, int line);

	/*
	When an internal error is found, this method shall be called to report the file in which
	the error occured and the line number where the error is located. This method is responsible
	for breaking into the code and attaching the debugger to it, since this debug break is compiler
	dependent it is not always possible to have this behavior out of implementation. If the
	exception support is present then it also throws an exception. What exception is exactly
	thrown will be dependent on the implementation.
	*/
	static void reportError(Cstring_t file, int line);

	/*
	When an internal error is found, this method shall be called to report the file in which
	the error occured and the line number where the error is located, along with some message
	describing the error itself. This method is responsible for breaking into the code and
	attaching the debugger to it, since this debug break is compiler dependent it is not always
	possible to have this behavior out of implementation. If the exception support is present
	then it also throws an exception. What exception is exactly thrown will be dependent on
	the implementation.
	*/
	static void reportError(Cstring_t message, Cstring_t file, int line);

	/*
	When an unexpected error is found, this method shall be called to report the file in which
	the error occured and the line number where the error is located.
	This method is responsible for breaking into the code and attaching the debugger to it,
	since this debug break is compiler dependent it is not always possible to have this behavior
	out of implementation. If the exception support is present then it also throws an exception.
	What exception is exactly thrown will be dependent on the implementation.

	@remarks
	There is difference in error and unexpected error. Usually, unexpected errors are meant to
	handled when the design isn't followed, for example a plugins ctor and dtor are across dll
	boundaries. Mostly, this method will be called from within the catch block in C++.
	*/
	static void reportUnexpectedError(Cstring_t file, int line);
	/*
	When an unexpected error is found, this method shall be called to report the file in which
	the error occured and the line number where the error is located, along with some message
	describing the error itself. This method is responsible for breaking into the code and
	attaching the debugger to it, since this debug break is compiler dependent it is not always
	possible to have this behavior out of implementation. If the exception support is present
	then it also throws an exception. What exception is exactly thrown will be dependent on
	the implementation.

	@remarks
	There is difference in error and unexpected error. Usually, unexpected errors are meant to
	handled when the design isn't followed, for example a plugins ctor and dtor are across dll
	boundaries. Mostly, this method will be called from within the catch block in C++.
	*/
	static void reportUnexpectedError(Cstring_t file, int line, Cstring_t message);
	/*
	This method is responsible for breaking into the code and attaching the debugger to it,
	since this debug break is compiler dependent it is not always possible to have this behavior
	out of implementation.
	*/
	static void debugger(Cstring_t file, int line);
	/*
	This method is responsible for breaking into the code and attaching the debugger to it,
	since this debug break is compiler dependent it is not always possible to have this behavior
	out of implementation. If attachment was successful, then the message will be passed to debugger's
	message pool else it will be written to stderr.

	@param
	messageType Type of message, 0 = nothing, 1 = information, 2 = error.
	@remarks
	When messageType is 0, message isn't forwarded. It will have same effect as
	debugger(Cstring_t file, int line).
	*/
	static void debugger(const char* file, int line, Cstring_t message = 0, uint8_t messageType = 0);

	protected:
		/*
		This method provides the formatting of messages.
		*/
		static std::string format(const char* message, const char* file, int line, const char* text);
	};
/** @} */
}

#include<iostream>

#define pcf_assert(___CONDITION__) \
    if (!(___CONDITION__)) pcf::DebugSupport::assert(#___CONDITION__, \
    	__PCF_FILE__, __PCF_LINE__); else (void) 0

#define pcf_assert_with_message(___CONDITION__, __TEXT_MESSAGE__) \
    if (!(___CONDITION__)) pcf::DebugSupport::assert(#___CONDITION__, \
    	__PCF_FILE__, __PCF_LINE__,__TEXT_MESSAGE__); else (void) 0

#define pcf_check_for_null_pointer(__PTR_TO_CHECK__) \
     if (!(__PTR_TO_CHECK__)) pcf::DebugSupport::checkForNullPointer(#__PTR_TO_CHECK__,\
    	__PCF_FILE__, __PCF_LINE__); else (void) 0

#define pcf_report_error()   pcf::DebugSupport::reportError(__PCF_FILE__, __PCF_LINE__)

#define pcf_report_error_with_mesage(__TEXT_MESSAGE__) \
		pcf::DebugSupport::reportError(__PCF_FILE__, __PCF_LINE__,__TEXT_MESSAGE__)

#define pcf_report_unexpected_error() \
		pcf::DebugSupport::reportUnexpectedError(__PCF_FILE__, __PCF_LINE__)

#define pcf_report_unexpected_error_with_message(__TEXT_MESSAGE__) \
		pcf::DebugSupport::reportUnexpectedError(__PCF_FILE__, __PCF_LINE__)

#define pcf_debug() pcf::DebugSupport::debugger(__PCF_FILE__, __PCF_LINE__)

#define pcf_debug_info(__TEXT_MESSAGE__) \
		pcf::DebugSupport::debugger(__PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__, 1)

#define pcf_debug_error(__TEXT_MESSAGE__) \
		pcf::DebugSupport::debugger(__PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__, 2)

#define pcf_report_to_stderror(__TEXT_MESSAGE__) \
		std::cerr << "pcf:error(" << __PCF_FILE__ << ':' << std::dec <<  __PCF_LINE__ << \
		':' << __TEXT_MESSAGE__ << ')' << std::endl



#endif // #if (PCF_LANGUAGE & PCF_LANGUAGE_ANY_CPP)

#endif // __PCF_INCLUDED_DEBUG_CPP_DEBUG_H
