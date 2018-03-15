/**
 * \file    uart_hidden.h
 * \brief   hidden header file for UART Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *          It contains UartDevice and UartController structure defination.
 *
 */

#ifndef __EPCF_PERIPHERAL_SOURCE_UART_UART_HIDDEN_H
#define __EPCF_PERIPHERAL_SOURCE_UART_UART_HIDDEN_H

typedef struct EPCFUartController   EPCFUartController_t;
typedef struct EPCFUartDevice		EPCFUartDevice_t;
typedef struct EPCFAdapter          EPCFAdapter_t;

typedef int8_t (*epcfUartInit_fp)(EPCFUartDevice_t*, EPCFUartCfg_t*);
typedef int32_t (*epcfUartWrite_fp)(EPCFUartDevice_t*, const uint8_t*, uint32_t, EPCFTime_t);
typedef int32_t (*epcfUartWriteBlocking_fp)(EPCFUartDevice_t*, const uint8_t*, uint32_t, EPCFTime_t);
typedef int32_t (*epcfUartWriteString_fp)(EPCFUartDevice_t*, const uint8_t*, EPCFTime_t);
typedef int32_t (*epcfUartRead_fp)(EPCFUartDevice_t*, uint8_t*,uint32_t, EPCFTime_t);
typedef uint32_t (*epcfUartGetDeviceCount_fp)(EPCFUartController_t*);
typedef int8_t (*epcfUartBufferFlush_fp)(EPCFUartDevice_t*);
typedef int32_t (*epcfUartBufferCount_fp)(EPCFUartDevice_t*);
typedef int8_t (*epcfUartClose_fp)(EPCFUartDevice_t*);

typedef struct EPCFUartDevice
{
    EPCFUartController_t*   controllerConfig;
    uint8_t                 uartId;
    void*                   uartChannelAddr;
    EnEPCFBoolean_t         uartChBusy;
    EnEPCFBoolean_t         interruptEnable;
    PCFFifoDesc_t           *uartTxFifo;
    PCFFifoDesc_t           *uartRxFifo;
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedUartDeviceId;         // ID Returned from the Device.
#endif
}EPCFUartDevice_t;

typedef struct EPCFUartController
{
    epcfUartInit_fp                 uartInit;
    epcfUartWrite_fp                uartWrite;
    epcfUartWriteBlocking_fp		uartWriteBlocking;
    epcfUartWriteString_fp          uartWriteString;
    epcfUartRead_fp                 uartRead;
    epcfUartGetDeviceCount_fp       uartGetDeviceCount;
    epcfUartBufferFlush_fp          uartRxBufferFlush;
    epcfUartBufferCount_fp          uartRxBufferCount;
    epcfUartBufferFlush_fp          uartTxBufferFlush;
    epcfUartBufferCount_fp          uartTxBufferCount;
    epcfUartClose_fp                uartClose;
    void                            *hardwareCfg;
}EPCFUartController_t;

#endif      //  __EPCF_PERIPHERAL_SOURCE_UART_UART_HIDDEN_H
