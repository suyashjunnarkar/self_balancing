/**
 * \file    uart_lpc1768.h
 * \brief   Native UART Driver Description for LPC1768.
 *
 */

#ifndef __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_UART_UART_LPC1768_H
#define __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_UART_UART_LPC1768_H


#include "uart_lpc1768_config.h"

int8_t epcf_uart_nativeInit(EPCFUartDevice_t* pUartDevice, EPCFUartCfg_t* pConfig);
int8_t epcf_uart_nativeClose(EPCFUartDevice_t* pUartDevice);
int32_t epcf_uart_nativeWrite(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout);
int32_t epcf_uart_nativeWriteString(EPCFUartDevice_t* pUartDevice, const uint8_t* data, EPCFTime_t timeout);
int32_t epcf_uart_nativeRead(EPCFUartDevice_t* pUartDevice, uint8_t* data, uint32_t size, EPCFTime_t timeout);
uint32_t epcf_uart_nativeGetDeviceCount();

int32_t epcf_uart_nativeGetRxBufferCount(EPCFUartDevice_t* pUartDevice);
int8_t epcf_uart_nativeRxBufferFlush(EPCFUartDevice_t* pUartDevice);
int32_t epcf_uart_nativeGetTxBufferCount(EPCFUartDevice_t* pUartDevice);
int8_t epcf_uart_nativeTxBufferFlush(EPCFUartDevice_t* pUartDevice);

#endif      // __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_UART_UART_LPC1768_H

/** @} */
