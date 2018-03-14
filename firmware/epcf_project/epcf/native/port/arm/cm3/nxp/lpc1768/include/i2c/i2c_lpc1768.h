/**
 * \file    i2c_lpc1768.h
 * \brief   Native I2C Driver Description for LPC1768.
 *
 */

#ifndef __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_I2C_I2C_LPC1768_H
#define __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_I2C_I2C_LPC1768_H

#include "i2c_lpc1768_config.h"

#define __EPCF_PIN_LPC1768_INCLUDE      PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/   \
                ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)
#include __EPCF_PIN_LPC1768_INCLUDE
#undef __EPCF_PIN_LPC1768_INCLUDE

//Include fifo file
#define __EPCF_UTIL_FIFO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_fifo.h)
#include  __EPCF_UTIL_FIFO_INCLUDE
#undef __EPCF_UTIL_FIFO_INCLUDE

/**  \brief Platform specific structure for LPC1768 */
typedef struct EPCFI2cLpc1768Cfg
{
    EPCFPortPin_t   i2cSDAPin;
    EPCFPortPin_t   i2cSCLPin;
}EPCFI2cLpc1768Cfg_t;


extern int8_t epcf_i2c_nativeInit(EPCFI2cDevice_t* pI2cDevice, EPCFI2cCfg_t* pConfig);
extern int32_t epcf_i2c_nativeWrite(EPCFI2cDevice_t* pI2cDevice,EnEPCFBoolean_t masterEnable,uint8_t slaveAddress,const uint8_t* data,uint32_t size,EnEPCFBoolean_t busRelease,EPCFTime_t timeout);
extern int32_t epcf_i2c_nativeRead(EPCFI2cDevice_t* pI2cDevice,EnEPCFBoolean_t masterEnable,uint8_t slaveAddress,uint8_t* data,uint32_t size,EnEPCFBoolean_t busRelease,EPCFTime_t timeout);
extern int8_t epcf_i2c_nativeIntEnable(EPCFI2cDevice_t* pI2cDevice);
extern int8_t epcf_i2c_nativeIntDisable(EPCFI2cDevice_t* pI2cDevice);
extern int32_t epcf_i2c_nativeGetRxBufferCount(EPCFI2cDevice_t* pI2cDevice);
extern int8_t epcf_i2c_nativeRxBufferFlush(EPCFI2cDevice_t* pI2cDevice);
extern int32_t epcf_i2c_nativeGetTxBufferCount(EPCFI2cDevice_t* pI2cDevice);
extern int8_t epcf_i2c_nativeTxBufferFlush(EPCFI2cDevice_t* pI2cDevice);
extern int8_t epcf_i2c_nativeClose(EPCFI2cDevice_t* pI2cDevice);
extern uint8_t epcf_i2c_nativeGetDeviceCount();


#endif      // __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_I2C_I2C_LPC1768_H

/** @} */
