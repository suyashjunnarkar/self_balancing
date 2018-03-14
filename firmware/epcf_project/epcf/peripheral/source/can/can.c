/**
 * \file  can.c
 * \brief This file is used to configure a CAN device
 */

#include "pcf.h"
#undef __EPCF_H_FILE_INCLUDE

#define __EPCF_PRIVATE_CAN_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,can/,can_hidden.h)
#include  __EPCF_PRIVATE_CAN_H_INCLUDE
#undef __EPCF_PRIVATE_CAN_H_INCLUDE

#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
	#define CAN_GET_DEVICE_COUNT()							epcfNativeCanGetDeviceCount()

#elif(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
	#define CAN_GET_DEVICE_COUNT(pCanController)			epcfExtCanGetDeviceCount(pCanController)
#endif


#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
 
EPCFCanDevice_t* epcf_can_createNative(EPCFCanCfg_t* pCanConfig)
{
	EPCFCanDevice_t* pCanDevice;
	int8_t status=0;
	
	//if(CAN_GET_DEVICE_COUNT())
	//{
		pCanDevice = (EPCFCanDevice_t *)malloc(sizeof(EPCFCanDevice_t));
		if (pCanDevice == (EPCFCanDevice_t *)NULL)
		return NULL;
		
		//pCanDevice->controllerConfig = NULL;
		
		status = epcfNativeCanInit(pCanDevice, pCanConfig);
		if(status != 0)
			return NULL;
		
		return pCanDevice;
	//}
//	else
//		return NULL;
}
 
#endif

//#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
//
//EPCFUartDevice_t* epcfCreateUart(EPCFUartController_t* pUartController, EPCFUartCfg_t* pUartConfig)
//{
//	EPCFUartDevice_t* pUartDevice;
//	int8_t status = 0;
//
//#if((EPCF_USE_UART == PCF_YES) || (EPCF_EXTENDED_USE_UART == PCF_YES))
//	if(UART_GET_DEVICE_COUNT(pUartController))
//	{
//		pUartDevice = (EPCFUartDevice_t*)malloc(sizeof(EPCFUartDevice_t));
//		if(pUartDevice == NULL)
//			return NULL;
//
//		pUartDevice->controllerConfig = pUartController;
//
//		if(pUartController == NULL)
//		{
//#if(EPCF_USE_UART == PCF_YES)
//			status = epcfNativeUartInit(pUartDevice, pUartConfig);
//			if(status != 0)
//				return NULL;
//#else
//			return EPCF_STATUS_ERROR;
//#endif
//		}
//		else
//		{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//			status = pUartController->uartInit(pUartDevice, pUartConfig);
//			if(status != 0)
//				return NULL;
//#else
//			// TODO : Error log and debug log should be included.
//			//           return EPCF_STATUS_ERROR;
//			return NULL;
//#endif
//		}
//		return pUartDevice;
//	}
//	else
//		return NULL;
//#endif
//}
//
//int8_t epcfExtUartClose(EPCFUartDevice_t* pUartDevice)
//{
//	int8_t status=0;
//
//	if(pUartDevice->controllerConfig == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//		status = epcfNativeUartClose(pUartDevice);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//		status = pUartDevice->controllerConfig->uartClose(pUartDevice);
//#endif
//	}
//	return status;
//}
//
//int32_t epcfExtUartWrite(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout)
//{
//	int32_t retVal=0;
//
//	if(pUartDevice->controllerConfig == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//	retVal = epcfNativeUartWrite(pUartDevice, data, size, timeout);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//	retVal = pUartDevice->controllerConfig->uartWrite(pUartDevice, data, size, timeout);
//#endif
//	}
//	return retVal;
//}
//
//int32_t epcfExtUartWriteBlocking(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout)
//{
//	int32_t retVal=0;
//
//	if(pUartDevice->controllerConfig == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//	retVal = epcfNativeUartWriteBlocking(pUartDevice, data, size, timeout);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//	retVal = pUartDevice->controllerConfig->uartWriteBlocking(pUartDevice, data, size, timeout);
//#endif
//	}
//	return retVal;
//}
//
//int32_t epcfExtUartWriteString(EPCFUartDevice_t* pUartDevice, const uint8_t* data, EPCFTime_t timeout)
//{
//	int32_t retVal=0;
//
//	if(pUartDevice->controllerConfig == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//	retVal = epcfNativeUartWriteString(pUartDevice, data, timeout);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//	retVal = pUartDevice->controllerConfig->uartWriteString(pUartDevice, data, timeout);
//#endif
//	}
//	return retVal;
//}
//
//int32_t epcfExtUartRead(EPCFUartDevice_t* pUartDevice, uint8_t *data, uint32_t size, EPCFTime_t timeout)
//{
//	int32_t retVal = 0;
//
//	if(pUartDevice->controllerConfig == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//	retVal = epcfNativeUartRead(pUartDevice, data, size, timeout);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//	retVal = pUartDevice->controllerConfig->uartRead(pUartDevice, data, size, timeout);
//#endif
//	}
//	return retVal;
//}
//
//uint32_t epcfExtUartGetDeviceCount(EPCFUartController_t* pUartController)
//{
//	uint32_t retVal=0;
//
//	if(pUartController == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//		retVal = epcfNativeUartGetDeviceCount(pUartController);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//		retVal = pUartController->uartGetDeviceCount(pUartController);
//#endif
//	}
//	return retVal;
//}
//
//int32_t epcfExtUartGetRxBufferCount(EPCFUartDevice_t* pUartDevice)
//{
//	int32_t retVal=0;
//
//	if(pUartDevice->controllerConfig == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//	retVal = epcfNativeUartGetRxBufferCount(pUartDevice);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//	retVal = pUartDevice->controllerConfig->uartRxBufferCount(pUartDevice);
//#endif
//	}
//	return retVal;
//}
//
//int8_t epcfExtUartRxBufferFlush(EPCFUartDevice_t* pUartDevice)
//{
//	int8_t retVal=0;
//
//	if(pUartDevice->controllerConfig == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//	retVal = epcfNativeUartRxBufferFlush(pUartDevice);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//	retVal = pUartDevice->controllerConfig->uartRxBufferFlush(pUartDevice);
//#endif
//	}
//	return retVal;
//}
//
//int32_t epcfExtUartGetTxBufferCount(EPCFUartDevice_t* pUartDevice)
//{
//	int32_t retVal=0;
//
//	if(pUartDevice->controllerConfig == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//	retVal = epcfNativeUartGetTxBufferCount(pUartDevice);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//	retVal = pUartDevice->controllerConfig->uartTxBufferCount(pUartDevice);
//#endif
//	}
//	return retVal;
//}
//
//int8_t epcfExtUartTxBufferFlush(EPCFUartDevice_t* pUartDevice)
//{
//	int8_t retVal=0;
//
//	if(pUartDevice->controllerConfig == NULL)
//	{
//#if(EPCF_USE_UART == PCF_YES)
//	retVal = epcfNativeUartTxBufferFlush(pUartDevice);
//#endif
//	}
//	else
//	{
//#if(EPCF_EXTENDED_USE_UART == PCF_YES)
//	retVal = pUartDevice->controllerConfig->uartTxBufferFlush(pUartDevice);
//#endif
//	}
//	return retVal;
//}
//
//#endif
