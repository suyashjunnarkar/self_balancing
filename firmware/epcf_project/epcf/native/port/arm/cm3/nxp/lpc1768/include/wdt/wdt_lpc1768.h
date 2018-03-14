/**
 * \file    wdt_lpc1768.h
 * \brief   Native WatchDog Driver Description for LPC1768.
 *
 */

#ifndef __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_WDT_WDT_LPC1768_H
#define __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_WDT_WDT_LPC1768_H

#include "wdt_lpc1768_config.h"

#define EPCF_PIN_LPC1768_INCLUDE 		PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/	\
                ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)

#include EPCF_PIN_LPC1768_INCLUDE
#undef EPCF_PIN_LPC1768_INCLUDE

/** \brief Enumeration for Watchdog clock Source        */
typedef enum
{
    enEPCFWdtClkIRC     = 0,                    /**< Use clock from internal RC oscillator      */
    enEPCFWdtClkPCLK    = 1,                    /**< Use clock of APB peripheral clock          */
    enEPCFWdtClkRTC     = 2,                    /**< Use clock from RTC oscillator              */
    enEPCFWdtClkMax                             /**< Boundary checking                          */
}EnEPCFWdtClkSrc_t;

/**  \brief Platform specific structure for LPC1768 */
typedef struct EPCFWdtLpc1768Cfg
{
    EnEPCFWdtClkSrc_t  wdtClkSrc;     /**< WDT clock source         */
}EPCFWdtLpc1768Cfg_t;

extern int8_t epcfNativeWdtInit(EPCFWdtDevice_t* pWdtDevice, EPCFWdtCfg_t *pConfig);
extern int8_t epcf_wdt_start(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t timeout);
extern int8_t epcf_wdt_stop(EPCFWdtDevice_t* pWdtDevice);
extern int8_t epcf_wdt_reset(EPCFWdtDevice_t* pWdtDevice);
extern int8_t epcf_wdt_getRemainingTimeToTimeout(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t* time);
extern EnEPCFWdtState_t epcf_wdt_getState(EPCFWdtDevice_t* pWdtDevice);
extern int8_t epcf_wdt_close(EPCFWdtDevice_t* pWdtDevice);
extern uint8_t epcf_wdt_getDeviceCount();

#endif      // __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_WDT_WDT_LPC1768_H

/** @} */
