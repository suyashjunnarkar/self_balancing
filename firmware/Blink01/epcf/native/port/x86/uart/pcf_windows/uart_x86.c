/*
 *  \file       uart_x86.c
 *  \brief      Windows Uart Driver.
 *
 *	\details	TODO: Add discription to this file.
 */

#include "epcf.h"

//Conditional include for uart_hidden.h
#define __EPCF_PRIVATE_UART_H_INCLUDE      PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,peripheral/,uart/,uart_hidden.h)
#include  __EPCF_PRIVATE_UART_H_INCLUDE
#undef __EPCF_PRIVATE_UART_H_INCLUDE

//Conditional include for epcf_string.h
#define __EPCF_UTILS_STRING_H_INCLUDE      PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,utils/,include/,epcf_string.h)
#include  __EPCF_UTILS_STRING_H_INCLUDE
#undef __EPCF_UTILS_STRING_H_INCLUDE

#define DEBUG_PRINT(...)        printf(__VA_ARGS__)

// Read only Lookup tables should have static const keyword.
static const uint8_t stopBitsMap[2] = {ONESTOPBIT, TWOSTOPBITS};
static const uint32_t baudRateMap[7] = {2400, 4800, 9600, 19200, 38400, 57600, 115200};
static uint32_t uartDeviceCount = UART_MAX_CHANNEL;

// Macro for acessing Lookup table
#define _EPCF_PRIVATE_UART_STOPBITS_MAP(x)         stopBitsMap[x-1]

// Below function call the Windows OS API to open the communication port
// with the Setting Specified by the Caller.
int8_t epcfNativeUartInit(EPCFUartDevice_t* pUartDevice, EPCFUartCfg_t *pConfig)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	//PCF_CHECK_FOR_NULL_POINTER(pUartDevice);
	//PCF_CHECK_FOR_NULL_POINTER(pConfig);
#endif
    
	int32_t status = 0;
    Uchar_t uartPort[50];
    HANDLE  hUart;
    DCB uartDCBParams = {0};
    COMMTIMEOUTS timeouts = {0};
    
    // Setting the com Port string
    if (pConfig->uartId >= (uint8_t)10)
        sprintf((char *)uartPort,"\\\\.\\COM%d", pConfig->uartId);
    else
        sprintf((char *)uartPort, "COM%d", pConfig->uartId);
    
    // Opening the Com port
    hUart = CreateFile((char *)uartPort, GENERIC_READ | GENERIC_WRITE, 0 , \
    				NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if ( hUart == INVALID_HANDLE_VALUE) // INVAILD_HANDLE_VALUE is windows OS System error code.
    {
		pUartDevice->uartChannelAddr = NULL;
		//pUartDevice->uartChannelAddr = PCF_NULL;
		status = GetLastError();
		// ERROR_FILE_NOT_FOUND is windows OS System error code.
        if ((status == ERROR_FILE_NOT_FOUND) || (status == ERROR_PATH_NOT_FOUND))
        {
            DEBUG_PRINT("Uart Port not exist. Port No.:", pConfig->uartId);
            return EPCF_STATUS_FILE_NOT_FOUND;
        }
        else
        {
            DEBUG_PRINT("Windows Error with:", hUart);
        	return EPCF_STATUS_INVALID_HANDLE;
        }    
    }
    pUartDevice->uartChannelAddr = (void*)hUart;

	//DCB    dcbUartParams ;
    // uart DCB Parameter setting for opened com port
    if (!GetCommState(hUart, &uartDCBParams))
    {
    	DEBUG_PRINT("Failed to Get Com Port State [Reason: %d]",GetLastError());
    	//"Can't set baudrate! " // phi flasher error log
    	// TODO : Add appropiate error. for GetCommState
    	return EPCF_STATUS_ERROR;
    }

    uartDCBParams.DCBlength       = sizeof(uartDCBParams);
    uartDCBParams.BaudRate        = baudRateMap[pConfig->baudrate];
    uartDCBParams.ByteSize        = pConfig->dataBits;
    uartDCBParams.Parity          = pConfig->parity;
    uartDCBParams.StopBits        = _EPCF_PRIVATE_UART_STOPBITS_MAP(pConfig->stopBits);
    uartDCBParams.fBinary         = TRUE;
    uartDCBParams.fDtrControl     = DTR_CONTROL_DISABLE;
    uartDCBParams.fRtsControl     = RTS_CONTROL_DISABLE;
    uartDCBParams.fOutxCtsFlow    = FALSE;
    uartDCBParams.fOutxDsrFlow    = FALSE;
    uartDCBParams.fDsrSensitivity = FALSE;
    uartDCBParams.fAbortOnError   = TRUE;
 
    if (!SetCommState(hUart, &uartDCBParams))
    {
		DEBUG_PRINT("!!!!! Warning: Could not Set Comm state \n");
    	//EPCF_DEBUG_PRINT_STDOUT("[Warning]: Failed to Get Com Port State [Reason: %d]",GetLastError());
    	// TODO : Add appropiate error. for SetCommState
    	//return EPCF_STATUS_ERROR;
    }
    if( !GetCommTimeouts( hUart, &timeouts ) )
	{
		DEBUG_PRINT("!!!!! Warning: Could not get Comm state \n");
    	// TODO : Add appropiate error. for GetcommTimeouts
    	//EPCF_DEBUG_PRINT_STDOUT("[Warning]: Failed to Get Com Port State [Reason: %d]",GetLastError());
		//Util.log("Error reading COM port settings!");
		//return EPCF_STATUS_ERROR;
	}
 
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier= 10;
 
    if(!SetCommTimeouts(hUart, &timeouts)) 
    {
    	// TODO : Add appropiate error. for SetCommTimeouts
        printf("!!!!! Warning: Could not Set Port Timeouts \n");
        return EPCF_STATUS_ERROR;
    }
    
    return EPCF_STATUS_SUCCESS;
}

//return values
// 0 : success
//-1 : error
int8_t epcfNativeUartClose(EPCFUartDevice_t* pUartDevice)
{
    if(epcfNativeUartTxBufferFlush(pUartDevice) == EPCF_STATUS_ERROR)
    {
    	// TODO : Add appropiate error Message.
        return EPCF_STATUS_ERROR;
    }
    if(epcfNativeUartRxBufferFlush(pUartDevice) == EPCF_STATUS_ERROR)
    {
    	// TODO : Add appropiate error Message.
        return EPCF_STATUS_ERROR;
    }
    if(! CloseHandle((HANDLE)pUartDevice->uartChannelAddr))
    {
    	// TODO : Add appropiate error Message.
        printf("!!!!! Error: Could not Purge Comm Port \n");
        return EPCF_STATUS_ERROR;
    }
    return EPCF_STATUS_SUCCESS;
}

//return values
// 0 : success
//-1 : error
int32_t epcfNativeUartWrite(EPCFUartDevice_t* pUartDevice, const uint8_t* pData, uint32_t size, EPCFTime_t timeout)
{
    uint32_t wrbytes=0;
    if(size == 0)
        return EPCF_STATUS_SUCCESS;
    
    if (! WriteFile((HANDLE)pUartDevice->uartChannelAddr, pData, size, (unsigned long*)&wrbytes, NULL))
    {
    	// TODO : Add appropiate error Message.
        printf("!!!!! Warning: Could not Write to Output Buffer \n");

    }
    return wrbytes;
}

int32_t epcfNativeUartWriteBlocking(EPCFUartDevice_t* pUartDevice, const uint8_t* pdata, uint32_t size, EPCFTime_t timeout)
{
	return EPCF_STATUS_NOT_SUPPORTED;
}

//return values
// 0 : success
int32_t epcfNativeUartWriteString(EPCFUartDevice_t* pUartDevice, const uint8_t* data, EPCFTime_t timeout)
{
    int32_t status;
    uint32_t wrbytes=0;

    while(data[wrbytes] != '\0')
    {
        status = epcfNativeUartWrite(pUartDevice, &(data[wrbytes]), 1, timeout);
        if(status == 0)
            return wrbytes;

        wrbytes++;
    }
    return wrbytes;
}

//return values
// 0 : success
//-1 : error
int32_t epcfNativeUartRead(EPCFUartDevice_t* pUartDevice, uint8_t* data, uint32_t maxsize, EPCFTime_t timeout)
{
    uint32_t bytesread=0;
    uint32_t sizetoread=maxsize;
    uint16_t retries=10;
    uint16_t attempt=0;
    uint32_t rdbytes;

    pcfMemSet(data, 0, maxsize);
    rdbytes = 0;

    while((attempt<retries) && (rdbytes < maxsize))             // 10 Attempts are made to collect all the data
    {
        if(!ReadFile((HANDLE)pUartDevice->uartChannelAddr, data, sizetoread, (unsigned long*)&bytesread, NULL))
        {
            attempt++;                                              // Read Failed
        }
        else
        {
            if(bytesread == 0)
            {
                attempt++;                                          // 0 data bytes are received
            }
            else
            {
                data += bytesread;
                rdbytes += bytesread;
                sizetoread -= bytesread;
            }
        }
    }
    if(rdbytes < maxsize)
    {
        return EPCF_STATUS_ERROR;
    }
    return rdbytes;
}

uint32_t epcfNativeUartGetDeviceCount()
{
    return uartDeviceCount;
}

//return values
// 0 : success
//-1 : error
int8_t epcfNativeUartTxBufferFlush(EPCFUartDevice_t* pUartDevice)
{
    if(! PurgeComm((HANDLE)pUartDevice->uartChannelAddr, PURGE_TXCLEAR | PURGE_TXABORT))        // Purged Data is not transmitted. It is discarded
    {
        printf("!!!!! Error: Could not Purge Comm Port \n");
        return EPCF_STATUS_ERROR;
    }
    return EPCF_STATUS_SUCCESS;
}

//return values
// 0 : success
//-1 : error
int8_t epcfNativeUartRxBufferFlush(EPCFUartDevice_t* pUartDevice)
{
    if(! PurgeComm((HANDLE)pUartDevice->uartChannelAddr, PURGE_RXCLEAR | PURGE_RXABORT))        // Purged Data is not Received. It is discarded
    {
        printf("!!!!! Error: Could not Purge Comm Port \n");
        return EPCF_STATUS_ERROR;
    }
    return EPCF_STATUS_SUCCESS;
}

int32_t epcfNativeUartGetTxBufferCount(EPCFUartDevice_t* pUartDevice)
{
    return EPCF_STATUS_NOT_SUPPORTED;
}

int32_t epcfNativeUartGetRxBufferCount(EPCFUartDevice_t* pUartDevice)
{
    return EPCF_STATUS_NOT_SUPPORTED;
}
