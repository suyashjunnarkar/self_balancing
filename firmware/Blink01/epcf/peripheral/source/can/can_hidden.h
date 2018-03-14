/**
 * \file    can_hidden.h
 * \brief   hidden header file for CAN Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *          It contains GpioDevice and GpioController structure defination.
 *
 */

#ifndef __EPCF_INCLUDED_SOURCE_PRIVATE_CAN_HIDDEN_H
#define __EPCF_INCLUDED_SOURCE_PRIVATE_CAN_HIDDEN_H

// typedef struct EPCFUartController   EPCFUartController_t;
// typedef struct EPCFUartDevice		EPCFUartDevice_t;
// typedef struct EPCFAdapter          EPCFAdapter_t;
//
// typedef int8_t (*epcfUartInit_fp)(EPCFUartDevice_t*, EPCFUartCfg_t*);
// typedef int32_t (*epcfUartWrite_fp)(EPCFUartDevice_t*, const uint8_t*, uint32_t, EPCFTime_t);
// typedef int32_t (*epcfUartWriteBlocking_fp)(EPCFUartDevice_t*, const uint8_t*, uint32_t, EPCFTime_t);
// typedef int32_t (*epcfUartWriteString_fp)(EPCFUartDevice_t*, const uint8_t*, EPCFTime_t);
// typedef int32_t (*epcfUartRead_fp)(EPCFUartDevice_t*, uint8_t*,uint32_t, EPCFTime_t);
// typedef uint32_t (*epcfUartGetDeviceCount_fp)(EPCFUartController_t*);
// typedef int8_t (*epcfUartBufferFlush_fp)(EPCFUartDevice_t*);
// typedef int32_t (*epcfUartBufferCount_fp)(EPCFUartDevice_t*);
// typedef int8_t (*epcfUartClose_fp)(EPCFUartDevice_t*);


typedef struct EPCFCanDevice
{
    uint8_t                 canId;
    void*                   canChannelAddr;
    EnEPCFIntType_t			interrupt;
    EnEPCFBoolean_t         canChBusy;
    PCFFifoDesc_t           *canTxFifo;
    PCFFifoDesc_t           *canRxFifo;
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedCanDeviceId;         // ID Returned from the Device.
#endif
}EPCFCanDevice_t;



#endif      //  __EPCF_INCLUDED_SOURCE_PRIVATE_GPIO_HIDDEN_H
