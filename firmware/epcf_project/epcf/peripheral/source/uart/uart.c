/**
 * \file  uart.c
 * \brief This file is used to configure a UART device
 */

#include "pcf.h"

//Include fifo file Required by uart_hidden.h
#define __EPCF_UTIL_FIFO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_fifo.h)
#include  __EPCF_UTIL_FIFO_INCLUDE
#undef __EPCF_UTIL_FIFO_INCLUDE

#include "./uart_hidden.h"

EPCFUartDevice_t* epcf_uart_createNative(EPCFUartCfg_t* pUartConfig)
{
	EPCFUartDevice_t* pUartDevice;
	int8_t status=0;
	
	if(epcf_uart_nativeGetDeviceCount())
	{
		pUartDevice = (EPCFUartDevice_t *)malloc(sizeof(EPCFUartDevice_t));
		if (pUartDevice == (EPCFUartDevice_t *)NULL)
		return NULL;
		
		pUartDevice->controllerConfig = NULL;
		
		status = epcf_uart_nativeInit(pUartDevice, pUartConfig);
		if(status != 0)
			return NULL;
		
		return pUartDevice;
	}
	else
		return NULL;
}
 

#ifdef EPCF_SUPPORT_EXTENDED_UART
EPCFUartDevice_t* epcf_uart_createExtended(EPCFUartController_t* pUartController, EPCFUartCfg_t* pUartConfig)
{
	EPCFUartDevice_t* pUartDevice;
	int8_t status = 0;

	if(epcf_uart_extGetDeviceCount(pUartController))
	{
		pUartDevice = (EPCFUartDevice_t*)malloc(sizeof(EPCFUartDevice_t));
		if(pUartDevice == NULL)
			return NULL;

		pUartDevice->controllerConfig = pUartController;

		status = pUartController->uartInit(pUartDevice, pUartConfig);
		if(status != 0)
			return NULL;

		return pUartDevice;
	}
	else
		return NULL;
}
#endif

int8_t epcf_uart_close(EPCFUartDevice_t* pUartDevice)
{
	int8_t status=0;

	if(pUartDevice->controllerConfig == NULL)
	{
		status = epcf_uart_nativeClose(pUartDevice);
	}
	else
	{
		status = pUartDevice->controllerConfig->uartClose(pUartDevice);
	}
	return status;
}

int32_t epcf_uart_write(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout)
{
	int32_t retVal=0;

	if(pUartDevice->controllerConfig == NULL)
	{
		retVal = epcf_uart_nativeWrite(pUartDevice, data, size, timeout);
	}
	else
	{
		retVal = pUartDevice->controllerConfig->uartWrite(pUartDevice, data, size, timeout);
	}
	return retVal;
}

int32_t epcf_uart_writeString(EPCFUartDevice_t* pUartDevice, const uint8_t* data, EPCFTime_t timeout)
{
	int32_t retVal=0;

	if(pUartDevice->controllerConfig == NULL)
	{
		retVal = epcf_uart_nativeWriteString(pUartDevice, data, timeout);
	}
	else
	{
		retVal = pUartDevice->controllerConfig->uartWriteString(pUartDevice, data, timeout);
	}
	return retVal;
}

int32_t epcf_uart_read(EPCFUartDevice_t* pUartDevice, uint8_t *data, uint32_t size, EPCFTime_t timeout)
{
	int32_t retVal = 0;

	if(pUartDevice->controllerConfig == NULL)
	{
		retVal = epcf_uart_nativeRead(pUartDevice, data, size, timeout);
	}
	else
	{
		retVal = pUartDevice->controllerConfig->uartRead(pUartDevice, data, size, timeout);
	}
	return retVal;
}

uint8_t epcf_uart_getDeviceCount()
{
	uint8_t retVal=0;

	retVal = epcf_uart_nativeGetDeviceCount();
	return retVal;
}

int32_t epcf_uart_getRxBufferCount(EPCFUartDevice_t* pUartDevice)
{
	int32_t retVal=0;

	if(pUartDevice->controllerConfig == NULL)
	{
		retVal = epcf_uart_nativeGetRxBufferCount(pUartDevice);
	}
	else
	{
		retVal = pUartDevice->controllerConfig->uartRxBufferCount(pUartDevice);
	}
	return retVal;
}

int8_t epcf_uart_rxBufferFlush(EPCFUartDevice_t* pUartDevice)
{
	int8_t retVal=0;

	if(pUartDevice->controllerConfig == NULL)
	{
		retVal = epcf_uart_nativeRxBufferFlush(pUartDevice);
	}
	else
	{
		retVal = pUartDevice->controllerConfig->uartRxBufferFlush(pUartDevice);
	}
	return retVal;
}

int32_t epcf_uart_getTxBufferCount(EPCFUartDevice_t* pUartDevice)
{
	int32_t retVal=0;

	if(pUartDevice->controllerConfig == NULL)
	{
		retVal = epcf_uart_nativeGetTxBufferCount(pUartDevice);
	}
	else
	{
		retVal = pUartDevice->controllerConfig->uartTxBufferCount(pUartDevice);
	}
	return retVal;
}

int8_t epcf_uart_txBufferFlush(EPCFUartDevice_t* pUartDevice)
{
	int8_t retVal=0;

	if(pUartDevice->controllerConfig == NULL)
	{
		retVal = epcf_uart_nativeTxBufferFlush(pUartDevice);
	}
	else
	{
		retVal = pUartDevice->controllerConfig->uartTxBufferFlush(pUartDevice);
	}
	return retVal;
}

uint32_t epcf_uart_extGetDeviceCount(EPCFUartController_t* pUartController)
{
	uint32_t retVal=0;

	if(pUartController == NULL)
		return EPCF_STATUS_ERROR;
	else
	{
		retVal = pUartController->uartGetDeviceCount(pUartController);
		return retVal;
	}
}
