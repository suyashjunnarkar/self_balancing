/**
 * \file    extInt_lpc1768_config.h
 * \brief   Native External Interrupt Driver Configuration for LPC1768.
 *
 */
#ifndef __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_EXTINT_EXTINT_LPC1768_CONFIG_H
#define __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_EXTINT_EXTINT_LPC1768_CONFIG_H


/** \brief ARCH SPECIFIC Configuration macros       */
#define EPCF_EXTINT0_CH            0
#define EPCF_EXTINT1_CH            1
#define EPCF_EXTINT2_CH            2
#define EPCF_EXTINT3_CH            3

#define EPCF_EINT0_CH 				EINT0
#define EPCF_EINT1_CH 				EINT1
#define EPCF_EINT2_CH				EINT2
#define EPCF_EINT3_CH				EINT3

#define EPCF_EINT0_INT_HANDLER   PCF_CONCATE(EPCF_EINT0_CH,_IRQHandler)
#define EPCF_EINT1_INT_HANDLER   PCF_CONCATE(EPCF_EINT1_CH,_IRQHandler)
#define EPCF_EINT2_INT_HANDLER   PCF_CONCATE(EPCF_EINT2_CH,_IRQHandler)

#define EPCF_PCLK_DIV(X)         PCF_CONCATE(PCLK_DIV_,X)
#define EPCF_PERIPH(X)           PCF_CONCATE(PERIPH_,X)
#define EPCF_POWER_ON(X)         PERIPH_SC->PCONP |= X
#define EPCF_POWER_OFF(X)        PERIPH_SC->PCONP &= ~(X)
#define EPCF_IRQ_NUM(X)          PCF_CONCATE(X,_IRQn)

#endif      // __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_EXTINT_EXTINT_LPC1768_CONFIG_H
