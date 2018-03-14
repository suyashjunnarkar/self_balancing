/**
 * \file    pwm_lpc1768.h
 * \brief   Native PWM Driver Description for LPC1768.
 *
 */

#ifndef __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_PWM_PWM_LPC1768_H
#define __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_PWM_PWM_LPC1768_H

#include "pwm_lpc1768_config.h"

#define __EPCF_PIN_LPC1768_INCLUDE      PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/   \
                ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)
#include __EPCF_PIN_LPC1768_INCLUDE
#undef __EPCF_PIN_LPC1768_INCLUDE



/**  \brief Platform specific structure for LPC1768 */
typedef struct EPCFPwmLpc1768Cfg
{
   uint8_t noOfPwmChannel;
   EPCFPortPin_t *pwmOutputPin;
}EPCFPwmLpc1768Cfg_t;


extern int8_t epcf_pwm_nativeInit(EPCFPwmDevice_t* pPwmDevice, EPCFPwmCfg_t* pConfig);
extern int8_t epcf_pwm_nativeStart(EPCFPwmDevice_t* pPwmDevice);
extern int8_t epcf_pwm_nativeStop(EPCFPwmDevice_t* pPwmDevice);
extern int8_t epcf_pwm_nativeAttachCallback(EPCFPwmDevice_t* pPwmDevice,EnEPCFPwmChannel_t channel,EnEPCFPwmInterruptSource_t interruptSource,epcfCallback_fp callback);
extern int8_t epcf_pwm_nativeDetachCallback(EPCFPwmDevice_t* pPwmDevice,uint8_t callbackId);
extern int8_t epcf_pwm_nativeSetPeriod(EPCFPwmDevice_t* pPwmDevice,EPCFTime_t period);
extern int8_t epcf_pwm_nativeSetDutyCycle(EPCFPwmDevice_t* pPwmDevice,EnEPCFPwmChannel_t channel,uint8_t dutyCycle,EnEPCFPwmOutputSignal_t signal);
extern int8_t epcf_pwm_nativeClose(EPCFPwmDevice_t* pPwmDevice);
extern uint8_t epcf_pwm_nativeGetDeviceCount();
extern EnEPCFPwmState_t epcf_pwm_nativeGetState(EPCFPwmDevice_t* pPwmDevice);

#endif      // __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_PWM_PWM_LPC1768_H

/** @} */
