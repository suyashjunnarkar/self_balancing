/*
 * \File   epcfDebugSupport.c
 *
 */

#if PCF_ENABLE_DEBUG == PCF_YES

#include "epcf.h"
#include <errno.h>
#include "../include/epcf_debug_support.h"

#include "stdio.h"

//#define __EPCF_DEBUG_ADAPTER_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,extended/,adapter/,adapter.h)
//#include __EPCF_DEBUG_ADAPTER_INCLUDE
//#undef __EPCF_DEBUG_ADAPTER_INCLUDE

///** @brief Macro for Debug Message Type */
//#define PCF_DEBUG_MESSAGE_TYPE_INFO       1	/**< Informationmessage    */
//#define PCF_DEBUG_MESSAGE_TYPE_ERROR      2	/**< Error message         */
//#define PCF_DEBUG_MESSAGE_TYPE_WARN       3	/**< Warning message       */
//#define PCF_DEBUG_MESSAGE_TYPE_DEBUG      4	/**< Debuging message      */
//#define PCF_DEBUG_MESSAGE_TYPE_FATAL      5	/**< Fatal Error message   */
//#define PCF_DEBUG_MESSAGE_TYPE_PANIC      6	/**< Panic Error message   */

/*
#define PCF_DEBUG()                             _PCF_DEBUG()
#define PCF_DEBUG_INFO(message)                 _PCF_DEBUG_INFO(message)
#define PCF_DEBUG_ERROR(message)                _PCF_DEBUG_ERROR(message)

#define PCF_REPORT_UNEXPECTED_ERROR()                                    _PCF_REPORT_UNEXPECTED_ERROR()
#define PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG(message)                    _PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG(message)
#define PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG_CODE(message, errorCode)    _PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG_CODE(message, errorCode)
*/

#define S_PRINTF     sprintf
#define DEBUG_MSG_MAX_LEN		150

#define __PRINT_MSG_LEN   PCF_DISABLE


extern int errno ;

static void _pcfDeviceDebugStdout(char* string,int len);
static void _pcfDeviceDebugFile(char* string,int len);
static void _pcfDeviceDebugAdapter(char* string,int len);

static void (*pcfDebugCallBack[])(char*, int) =
{
    _pcfDeviceDebugStdout,
	_pcfDeviceDebugFile,
	_pcfDeviceDebugAdapter,
};

static EnPCFDebugDeviceType_t deviceType;
static void* deviceConfig = PCF_NULL;
static char debugMsgBuffer[DEBUG_MSG_MAX_LEN] = {};


int8_t pcfDebugInit(EnPCFDebugDeviceType_t device, void* config)
{
	//FILE * fp;
	switch(device)
	{
		case enPCFDebugDevice_StdOutput:
				/*
				 	TODO: Add Support
				 	deviceType = device;
				 */
				deviceType = device;
				//deviceConfig = config;
			break;
		case enPCFDebugDevice_File:
			return EPCF_STATUS_NOT_SUPPORTED;
				if(config == PCF_NULL)
					return EPCF_STATUS_INVALID_ARGS;
				/*
				 	TODO: Add Support
				 	deviceType = device;
				 	fp = fopen((const char *)config, "w");
					if( fp == PCF_NULL )
					{
					  fprintf(stderr, "Value of errno: %d\n", errno);
					  fprintf(stderr, "Error opening file: %s\n", strerror(errno));
					}
					deviceType = device;
					deviceConfig = config;
				 */

			break;
		case enPCFDebugDevice_Adapter:
				if( config == PCF_NULL )
				{
					return EPCF_STATUS_INVALID_ARGS;
				}
				deviceType = device;
				deviceConfig = config;
			break;
		default:
				return EPCF_STATUS_NOT_SUPPORTED;
			break;
	}
	return EPCF_STATUS_SUCCESS;
}

void pcfDebugAssert(Cstring_t condition, Cstring_t file, uint32_t line, Cstring_t message)
{
	int msgLen=0;
	if (message != 0)
	{
		// TODO : Add some code if possible for the excceding Max msg len.
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:assert(C<%s>:F<%s>:L<%d>:M<%s>)",condition, file,(int)line,message);
	}
    else
    	msgLen=S_PRINTF(debugMsgBuffer,"pcf:assert(C<%s>:F<%s>:L<%d>)",condition, file,(int)line);

	pcfDebugCallBack[deviceType]((char*)debugMsgBuffer,msgLen);
}

void pcfDebugDebugger(Cstring_t file, uint32_t line, Cstring_t message, uint8_t messageType)
{
	int msgLen=0;
	if (message != 0)
	{
		// TODO : Add some code if possible for the excceding Max msg len.
		msgLen=sprintf(debugMsgBuffer,"pcf:[%d](F<%s>:L<%d>:M<%s>)",(int)messageType,file,(int)line,message);
	}
    else
    	msgLen=S_PRINTF(debugMsgBuffer,"pcf:(F<%s>:L<%d>)",file,(int)line);

	pcfDebugCallBack[deviceType]((char*)debugMsgBuffer,msgLen);
}

void pcfDebugDebuggerErrCode(Cstring_t file, uint32_t line, Cstring_t message, uint8_t messageType, int32_t errorCode)
{
	int msgLen=0;
	if (message != 0)
	{
		// TODO : Add some code if possible for the excceding Max msg len.
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:[%d](F<%s>:L<%d>:M<%s>:E<%d>)",(int)messageType,file,(int)line,message,(int)errorCode);
	}
	else
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:[%d](F<%s>:L<%d>:E<%d>)",(int)PCF_DEBUG_MESSAGE_TYPE_DEBUG,file,(int)line,(int)errorCode);

	pcfDebugCallBack[deviceType]((char*)debugMsgBuffer,msgLen);
}

void pcfDebugReportError(Cstring_t file, uint32_t line, Cstring_t message)
{
	int msgLen=0;
	if (message != 0)
	{
		// TODO : Add some code if possible for the excceding Max msg len.
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:Report Error(F<%s>:L<%d>:M<%s>)",file,(int)line,message);
	}
	else
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:Report Error(F<%s>:L<%d>)",file,(int)line);

	pcfDebugCallBack[deviceType]((char*)debugMsgBuffer,msgLen);
}

void pcfDebugReportErrorErrCode(Cstring_t file, uint32_t line, Cstring_t message, int32_t errorCode)
{
	int msgLen=0;
	if (message != 0)
	{
		// TODO : Add some code if possible for the excceding Max msg len.
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:Error(F<%s>:L<%d>:M<%s>:E<%d>)",file,(int)line,message,(int)errorCode);
	}
	else
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:Error(F<%s>:L<%d>:E<%d>)",file,(int)line,(int)errorCode);

	pcfDebugCallBack[deviceType]((char*)debugMsgBuffer,msgLen);
}

void pcfDebugReportUnexpectedError(Cstring_t file, uint32_t line, Cstring_t message)
{
	int msgLen=0;
	if (message != 0)
	{
		// TODO : Add some code if possible for the excceding Max msg len.
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:Unexpected Error(F<%s>:L<%d>:M<%s>)",file,(int)line,message);
	}
	else
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:Unexpected Error(F<%s>:L<%d>)",file,(int)line);

	pcfDebugCallBack[deviceType]((char*)debugMsgBuffer,msgLen);
}

void pcfDebugReportUnexpectedErrorErrCode(Cstring_t file, uint32_t line, Cstring_t message, int32_t errorCode)
{
	int msgLen=0;
	if (message != 0)
	{
		// TODO : Add some code if possible for the excceding Max msg len.
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:Report Error(F<%s>:L<%d>:M<%s>:E<%d>)",file,(int)line,message,(int)errorCode);
	}
	else
		msgLen=S_PRINTF(debugMsgBuffer,"pcf:Report Error(F<%s>:L<%d>:E<%d>)",file,(int)line,(int)errorCode);

	pcfDebugCallBack[deviceType]((char*)debugMsgBuffer,msgLen);
}

static void _pcfDeviceDebugStdout(char* string,int len)
{
#if (PCF_ARCH == PCF_ARCH_X86)
    #if ( __PRINT_MSG_LEN == PCF_ENABLE)
        printf("%s {MSG LEN:%d}\n",string,len);
    #else
        printf("%s\n",string);
    #endif
	
#endif
}

static void _pcfDeviceDebugFile(char* string,int len)
{
#if (PCF_ARCH == PCF_ARCH_X86)
    #if ( __PRINT_MSG_LEN == PCF_ENABLE)
        fprintf(stdout,"%s {MSG LEN:%d}\n",string,len);
    #else
        fprintf(stdout,"%s\n",string);
    #endif
#endif
}

static void _pcfDeviceDebugAdapter(char* string,int len)
{
	EPCFTime_t fakeTime;
	//EPCFAdapter_t*, const uint8_t*, uint32_t, EPCFTime_t
	((EPCFAdapter_t*)deviceConfig)->adapterWrite(deviceConfig,(uint8_t*)string,(uint32_t)len,fakeTime);
	((EPCFAdapter_t*)deviceConfig)->adapterWrite(deviceConfig,(uint8_t*)"\r",(uint32_t)1,fakeTime);
}

#endif //#if PCF_ENABLE_DEBUG == PCF_YES
