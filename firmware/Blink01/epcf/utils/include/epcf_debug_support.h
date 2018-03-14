/**
 *  \file  epcf_debug_support.h
 *  
 *  \brief File contain the basic API defination for Debug Support.
 *  
 */
 
#ifndef __EPCF_UTILS_INCLUDE_DEBUGSUPPORT_H
#define __EPCF_UTILS_INCLUDE_DEBUGSUPPORT_H

/** @brief Enum for Debug Device type */
typedef enum EnPCFDebugDeviceType {
	enPCFDebugDevice_StdOutput =0,	/**< Debug messages to the Standard Output  */
    enPCFDebugDevice_File,        	/**< Debug messages to the File System      */
    enPCFDebugDevice_Adapter,      	/**< Debug messages to the Any Adapter      */
    enPCFDebugDevice_Max          	/**< Used for Boundry Checking of Enum      */
} EnPCFDebugDeviceType_t;

/**
 *  \brief This function is used to Initilized a Debug Device. Call this function in beginning to initialize the device.
 *        
 *  
 *  \param debugDevice   debug device type as per the Enum EnPCFDebugDeviceType_t.
 *  \param deviceConfig  deviceConfig is the configuration of debug device.
 *                       device Type : 
 *                        1. enPCFDebugDevice_StdOutput  : Pass PCF_NULL, as it doesn't required the configuration.
 *                        2. enPCFDebugDevice_File       : Pass string containing the filename with the Path.
 *                        3. enPCFDebugDevice_Adapter    : Pass the Config structure as per the Adapter.
 *                                                         check structure EPCFAdapter_t in adapter.h for more details.
 *  
 *  \return return Initilization status of device initilization. Check status code in case return value is less than 0.
 *         Refer to "../../common/status.h" header file for the appropriate status codes.
 */
#define PCF_DEBUG_INIT(debugDevice, deviceConfig)           pcfDebugInit(debugDevice, deviceConfig)

/**
 *  \brief This Macro check weather the pointer is NULL. If the pointer is NULL then it prints a message with the
 *         name of pointer to the debug device.
 *  
 *  \param pointerToCheck   Pointer which is to be tested for the NULL value.  
 *  
 *  \return This macro does not return any value.
 */
#define PCF_CHECK_FOR_NULL_POINTER(pointerToCheck)          _PCF_CHECK_FOR_NULL_POINTER(pointerToCheck)


/**
 *  \brief This Macro allows diagnostic information to be written debug Device.
 *  
 *  \param expression   This can be a variable or any C expression. 
 *                      If expression evaluates to TRUE, PCF_ASSERT() does nothing. 
 *                      If expression evaluates to FALSE, PCF_ASSERT() displays an error on debug device 
 *                      and aborts/halts program execution.
 *  
 *  \return This macro does not return any value.
 */
#define PCF_ASSERT(expression)                              _PCF_ASSERT(expression)

/**
 *  \brief This Macro allows diagnostic information to be written debug Device along with the User Message.
 *  
 *  \param expression   This can be a variable or any C expression. If expression evaluates to TRUE, PCF_ASSERT_WITH_MSG()
 *                      does nothing. If expression evaluates to FALSE, PCF_ASSERT_WITH_MSG() displays an error with user message on
 *                      debug device and aborts/halts program execution.
 *  
 *  \return This macro does not return any value.
 */
#define PCF_ASSERT_WITH_MSG(expression, message)            _PCF_ASSERT_WITH_MSG(expression, message)

/**
 *  \brief  This macro writes file name and line number with error report message to debug device. 
 *  
 *  \return This macro does not return any value.
 */
#define PCF_REPORT_ERROR()                                  _PCF_REPORT_ERROR()

/**
 *  \brief  This macro writes file name, line number and user message to debug device.
 *  
 *  \return This macro does not return any value.
 */
#define PCF_REPORT_ERROR_WITH_MSG(message)                   _PCF_REPORT_ERROR_WITH_MSG(message)

/**
 *  \brief  This macro writes file name, line number, user message and errorCode to debug device.
 *  
 *  \return This macro does not return any value.
 */
#define PCF_REPORT_ERROR_WITH_MSG_CODE(message, errorCode)   _PCF_REPORT_ERROR_WITH_MSG_CODE(message, errorCode)

/**
 *  \brief  This macro writes file name, line number, user message to Standard Error.
 *  
 *  \return This macro does not return any value.
 */
#define PCF_REPORT_TO_STDERROR(message)                     _PCF_REPORT_TO_STDERROR(message)

/**
 *  \brief Macro checks the return Status of any function for EPCF_STATUS_SUCCESS status code
 *         and prints a user message to the debug device if status is not equal to EPCF_STATUS_SUCCESS.
 *  
 *  \param  returnStatus    variable having the return status of function to be checked.  
 *  \param  msgIfFailed     user message for debug device if the returnStatus is not equal to EPCF_STATUS_SUCCESS.
 *  
 *  \return This macro does not return any value.
 */
#define PCF_DEBUG_CHECK_STATUS(returnStatus, msgIfFailed)			if(returnStatus != EPCF_STATUS_SUCCESS){    \
                                                                        PCF_REPORT_ERROR_MSG(msgIfFailed);	  	\
                                                                    }

#endif // #define __EPCF_UTILS_INCLUDE_DEBUGSUPPORT_H
