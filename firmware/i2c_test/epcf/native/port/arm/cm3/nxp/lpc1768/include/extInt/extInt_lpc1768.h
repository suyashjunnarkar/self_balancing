/**
 * \file    extInt_lpc1768.h
 * \brief   Native External Interrupt Driver Description for LPC1768.
 *
 */

#ifndef __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_EXTINT_EXTINT_LPC1768_H
#define __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_EXTINT_EXTINT_LPC1768_H

#include "extInt_lpc1768_config.h"

#define EPCF_PIN_LPC1768_INCLUDE      PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/   \
                ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/,pin_lpc1768.h)

#include EPCF_PIN_LPC1768_INCLUDE
#undef EPCF_PIN_LPC1768_INCLUDE

int8_t epcfNativeExtIntInit(EPCFExtIntDevice_t* pExtIntDevice, EPCFExtIntCfg_t* pConfig);
int8_t epcfNativeExtIntClose(EPCFExtIntDevice_t* pExtIntDevice);
int8_t epcfNativeExtIntEnable(EPCFExtIntDevice_t* pExtIntDevice);
int8_t epcfNativeExtIntDisable(EPCFExtIntDevice_t* pExtIntDevice);
int8_t epcfNativeExtIntAttachCallback(EPCFExtIntDevice_t* pExtIntDevice,epcfCallback_fp pCallback);
int8_t epcfNativeExtIntDetachCallback(EPCFExtIntDevice_t* pExtIntDevice);
int8_t epcfNativeExtIntClose(EPCFExtIntDevice_t* pExtIntDevice);
uint8_t epcfNativeExtIntGetDeviceCount();

#endif      // __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_EXTINT_EXTINT_LPC1768_H

/** @} */
