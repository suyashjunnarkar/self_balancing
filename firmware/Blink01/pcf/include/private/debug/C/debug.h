#ifndef __PCF_INCLUDED_DEBUG_C_DEBUG_H
#define __PCF_INCLUDED_DEBUG_C_DEBUG_H

#if (PCF_LANGUAGE & PCF_LANGUAGE_ANY_C)

#define PCF_DEBUG_MODE		PCF_YES


/** @brief Macro for Debug Message Type */
#define PCF_DEBUG_MESSAGE_TYPE_INFO		1	/**< Information message    */
#define PCF_DEBUG_MESSAGE_TYPE_ERROR	2	/**< Error message         */
#define PCF_DEBUG_MESSAGE_TYPE_WARN		3	/**< Warning message       */
#define PCF_DEBUG_MESSAGE_TYPE_DEBUG	4	/**< Debuging message      */
#define PCF_DEBUG_MESSAGE_TYPE_FATAL	5	/**< Fatal Error message   */
#define PCF_DEBUG_MESSAGE_TYPE_PANIC	6	/**< Panic Error message   */

// /** @brief Enum for Debug Device type */
// typedef enum EnPCFDebugDeviceType {
	// enPCFDebugDevice_StdOutput =0,	/**< Debug messages to the Standard Output  */
    // enPCFDebugDevice_File,        	/**< Debug messages to the File System      */
    // enPCFDebugDevice_Adapter,      	/**< Debug messages to the Any Adapter      */
    // enPCFDebugDevice_Max          	/**< Used for Boundry Checking of Enum      */
// } EnPCFDebugDeviceType_t;

typedef enum EnPCFDebugDeviceType EnPCFDebugDeviceType_t;

extern int8_t pcfDebugInit(EnPCFDebugDeviceType_t debugDevice, void* debugConfig);

extern void pcfDebugAssert(Cstring_t condition, Cstring_t file, uint32_t line, Cstring_t message);
extern void pcfDebugDebugger(Cstring_t file, uint32_t line, Cstring_t message, uint8_t messageType);
extern void pcfDebugDebuggerErrCode(Cstring_t file, uint32_t line, Cstring_t message, uint8_t messageType, int32_t errorCode);
extern void pcfDebugReportError(Cstring_t file, uint32_t line, Cstring_t message);
extern void pcfDebugReportErrorErrCode(Cstring_t file, uint32_t line, Cstring_t message, int32_t errorCode);
extern void pcfDebugReportUnexpectedError(Cstring_t file, uint32_t line, Cstring_t message);
extern void pcfDebugReportUnexpectedErrorErrCode(Cstring_t file, uint32_t line, Cstring_t message, int32_t errorCode);

#endif //#if (PCF_LANGUAGE & PCF_LANGUAGE_ANY_C)

#endif // __PCF_INCLUDED_DEBUG_C_DEBUG_H
