/**
 * \file    adc_lpc1768_config.h
 * \brief   Native ADC Driver Configuration for LPC1768.
 *
 */
#ifndef __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_ADC_ADC_LPC1768_CONFIG_H
#define __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_ADC_ADC_LPC1768_CONFIG_H


/** \brief ARCH SPECIFIC Configuration macros       */
#define ADC_CH            ADC

#define ADC_CHANNEL       PERIPH(ADC_CH)

#define ADC_INT_HANDLER   PCF_CONCATE(ADC,_IRQHandler)

#define	PWR_ADC			(1<<12) 

#define	PWR_ADC_CH(X)		PCF_CONCATE(PWR_,X)
#define PCLK_DIV(X)         PCF_CONCATE(PCLK_DIV_,X)
#define PERIPH(X)			PCF_CONCATE(PERIPH_,X)
#define POWER_ON(X) 		PERIPH_SC->PCONP |= X
#define POWER_OFF(X) 		PERIPH_SC->PCONP &= ~(X)
#define IRQ_NUM(X)			PCF_CONCATE(X,_IRQn)

#endif      // __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_ADC_ADC_LPC1768_CONFIG_H
