/**
 * \file    can_lpc1768.h
 * \brief   Native CAN Driver Description for LPC1768.
 *
 */

#ifndef __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_CAN_CAN_LPC1768_H
#define __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_CAN_CAN_LPC1768_H

#include "can_lpc1768_config.h"

#define __EPCF_PIN_LPC1768_INCLUDE      PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/   \
                ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)
#include __EPCF_PIN_LPC1768_INCLUDE
#undef __EPCF_PIN_LPC1768_INCLUDE

//Include fifo file
#define __EPCF_UTIL_FIFO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_fifo.h)
#include  __EPCF_UTIL_FIFO_INCLUDE
#undef __EPCF_UTIL_FIFO_INCLUDE


/**  \brief Platform specific structure for LPC1768 */
typedef struct EPCFCanLpc1768Cfg
{
  EPCFPortPin_t           canTxPin;     /**< Pin discription of UartTx pin and port        */
  EPCFPortPin_t           canRxPin;     /**< Pin discription of UartRx pin and port        */
}EPCFCanLpc1768Cfg_t;

uint32_t epcf_can_getRxBufferCount(EPCFCanDevice_t* pCanDevice);
int8_t epcf_can_rxBufferFlush(EPCFCanDevice_t* pCanDevice);
uint32_t epcf_can_getTxBufferCount(EPCFCanDevice_t* pCanDevice);
EnEPCFBoolean_t epcf_can_getRxFifoEmpty(EPCFCanDevice_t* pCanDevice);
int8_t epcf_can_txBufferFlush(EPCFCanDevice_t* pCanDevice);
int8_t epcf_can_intAttachCallback(EPCFCanDevice_t* pCanDevice,EnEPCFCanCallback_t intType,epcfCallbackWithArg_fp pCallback);
int8_t epcf_can_intDetachCallback(EPCFCanDevice_t* pCanDevice,EnEPCFCanCallback_t intType);
int8_t epcf_can_intEnable(EPCFCanDevice_t* pCanDevice,EnEPCFIntType_t intType);
int8_t epcf_can_intDisable(EPCFCanDevice_t* pCanDevice,EnEPCFIntType_t intType);
int8_t epcf_can_setMsgHeader(EPCFCanDevice_t* pCanDevice,EPCFCanMsgHeader_t* pMsgHeader);
int8_t epcf_can_write(EPCFCanDevice_t* pCanDevice,const uint8_t* data, uint32_t size,EPCFTime_t timeout);
int8_t epcf_can_read(EPCFCanDevice_t*  pCanDevice,EPCFpCanRxMessage_t rxMessage,EPCFTime_t timeout);
int8_t epcf_can_filterInit(EPCFCanDevice_t* pCanDevice,EPCFpCfgFilter pFilterConfig);
int8_t epcf_can_getTxErrCounter(EPCFCanDevice_t* pCanDevice,uint8_t* errCount);
int8_t epcf_can_getRxErrCounter(EPCFCanDevice_t* pCanDevice,uint8_t* errCount);
int8_t epcf_can_getIntStatus(EPCFCanDevice_t* pCanDevice,uint32_t* status);
int8_t epcf_can_getCtrlStatus(EPCFCanDevice_t* pCanDevice,uint32_t* status);
int8_t epcf_can_close(EPCFCanDevice_t* pCanDevice);


#endif      // __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_CAN_CAN_LPC1768_H

/** @} */
