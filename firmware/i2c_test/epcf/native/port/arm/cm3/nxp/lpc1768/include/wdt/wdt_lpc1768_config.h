/**
 * \file    wdt_lpc1768_config.h
 * \brief   Native WDT Driver Configuration for LPC1768.
 *
 */
#ifndef __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_WDT_WDT_LPC1768_CONFIG_H
#define __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_WDT_WDT_LPC1768_CONFIG_H


/** \brief ARCH SPECIFIC Configuration macros       */
#define EPCF_WDT_CH             WDT

#define EPCF_WDT_CHANNEL        PERIPH(EPCF_WDT_CH)

#define EPCF_WDT_INT_HANDLER    PCF_CONCATE(EPCF_WDT_CH,_IRQHandler)

#define EPCF_PCLK_DIV(X)        PCF_CONCATE(PCLK_DIV_,X)
#define EPCF_PERIPH(X)          PCF_CONCATE(PERIPH_,X)
#define EPCF_IRQ_NUM(X)         PCF_CONCATE(X,_IRQn)

#endif      // __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_WDT_WDT_LPC1768_CONFIG_H
