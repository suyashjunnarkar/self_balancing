/**
 * \file    timer_lpc1768.h
 * \brief   Native TIMER Driver Description for LPC1768.
 *
 */
 
#ifndef __EPCF_NATIVE_PORT_ARM_CM3_NXP_LPC1768_INCLUDE_TIMER_TIMER_LPC1768_H
#define __EPCF_NATIVE_PORT_ARM_CM3_NXP_LPC1768_INCLUDE_TIMER_TIMER_LPC1768_H

#include "timer_lpc1768_config.h"

#define __EPCF_PIN_LPC1768_INCLUDE 		PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/	\
                ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)

#include __EPCF_PIN_LPC1768_INCLUDE
#undef __EPCF_PIN_LPC1768_INCLUDE



/**  \brief Platform specific structure for LPC1768 */
typedef struct EPCFTimerLpc1768Cfg
{
	uint8_t					noOfExtMatPin;
	uint8_t					noOfCapturePin;
	EPCFPortPin_t			*timerExtMatPin;
	EPCFPortPin_t			*timerCapPin;
}EPCFTimerLpc1768Cfg_t;

extern int8_t epcf_timer_nativeInit(EPCFTimerDevice_t* pTimerDevice, EPCFTimerCfg_t* pConfig);
extern int8_t epcf_timer_nativeStart(EPCFTimerDevice_t* pTimerDevice);
extern int8_t epcf_timer_nativeStop(EPCFTimerDevice_t* pTimerDevice);
extern int8_t epcf_timer_nativeReset(EPCFTimerDevice_t* pTimerDevice);
extern EnEPCFTimerState_t epcf_timer_nativeGetState(EPCFTimerDevice_t* pTimerDevice);
extern int8_t epcf_timer_nativeGetTime(EPCFTimerDevice_t* pTimerDevice,EPCFTime_t* time);
extern int8_t epcf_timer_nativeGetCounterValue(EPCFTimerDevice_t* pTimerDevice, uint32_t* count);
extern int8_t epcf_timer_nativeSetCounter(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerInputPolarity_t inputPolarity);
extern int8_t epcf_timer_nativeAttachCallback(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerInterruptSource_t interruptSource,epcfCallback_fp callback);
extern int8_t epcf_timer_nativeDetachCallback(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerInterruptSource_t interruptSource);
extern int8_t epcf_timer_nativeSetCompareTime(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerCompareAction_t compareAction,EnEPCFTimerPinAction pinAction,EPCFTime_t time);
extern int8_t epcf_timer_nativeSetInputCapture(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerInputPolarity_t inputPolarity);
extern int8_t epcf_timer_nativeGetInputCaptureTime(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EPCFTime_t* time);
extern int8_t epcf_timer_nativeClose(EPCFTimerDevice_t* pTimerDevice);
extern uint8_t epcf_timer_nativeGetDeviceCount();

#endif      // __EPCF_NATIVE_PORT_ARM_CM3_NXP_LPC1768_INCLUDE_TIMER_TIMER_LPC1768_H

/** @} */
