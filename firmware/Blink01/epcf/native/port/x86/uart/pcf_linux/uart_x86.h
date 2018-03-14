/**
 * \file    uart_x86_32.h
 * \brief   Native Uart Driver Description for x86_32 system.
 *
 */

#ifndef __EPCF_INCLUDED_NATIVE_PORT_X86_UART_PCF_LINUX_H
#define __EPCF_INCLUDED_NATIVE_PORT_X86_UART_PCF_LINUX_H

#include "uart_x86_config.h"

//typedef struct EPCFUartDevice EPCFUartDevice_t;
//typedef struct EPCFUartCfg EPCFUartCfg_t;


/**  \brief Platform specific structure for Linux 32 bit system */
typedef struct EPCFUartLinuxCfg {
  EnEPCFBoolean_t    isUSBdevice;     /**< device is USB type or not */
}EPCFUartLinuxCfg_t;

int8_t epcfNativeUartInit(EPCFUartDevice_t* pUartDevice, EPCFUartCfg_t* pConfig);
int8_t epcfNativeUartClose(EPCFUartDevice_t* pUartDevice);
int32_t epcfNativeUartWrite(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout);
int32_t epcfNativeUartWriteBlocking(EPCFUartDevice_t* pUartDevice, const uint8_t* pdata, uint32_t size, EPCFTime_t timeout);
int32_t epcfNativeUartWriteString(EPCFUartDevice_t* pUartDevice, const uint8_t* data, EPCFTime_t timeout);
int32_t epcfNativeUartRead(EPCFUartDevice_t* pUartDevice, uint8_t* data, uint32_t size, EPCFTime_t timeout);
//int8_t epcfNativeUartReadByte(EPCFUartDevice_t* pUartDevice, PFbyte* data);
uint32_t epcfNativeUartGetDeviceCount();

int32_t epcfNativeUartGetTxBufferCount(EPCFUartDevice_t* pUartDevice);
int32_t epcfNativeUartGetRxBufferCount(EPCFUartDevice_t* pUartDevice);
int8_t epcfNativeUartTxBufferFlush(EPCFUartDevice_t* pUartDevice);
int8_t epcfNativeUartRxBufferFlush(EPCFUartDevice_t* pUartDevice);

#endif  //#ifndef __EPCF_INCLUDED_NATIVE_PORT_X86_32_UART_LINUX32_H

