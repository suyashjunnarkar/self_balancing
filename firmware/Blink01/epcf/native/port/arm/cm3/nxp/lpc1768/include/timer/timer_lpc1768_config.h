/**
 * \file    timer_lpc1768_config.h
 * \brief   Native TIMER Driver Configuration for LPC1768.
 *
 */
#ifndef __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_TIMER_TIMER_LPC1768_CONFIG_H
#define __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_TIMER_TIMER_LPC1768_CONFIG_H


/** \brief ARCH SPECIFIC Configuration macros       */
#define TIMER0_CH            TIMER0
#define TIMER1_CH            TIMER1
#define TIMER2_CH            TIMER2
#define TIMER3_CH            TIMER3

#define TIMER0_CHANNEL       PERIPH(TIMER0_CH)
#define TIMER1_CHANNEL       PERIPH(TIMER1_CH)
#define TIMER2_CHANNEL       PERIPH(TIMER2_CH)
#define TIMER3_CHANNEL       PERIPH(TIMER3_CH)

#define TIMER0_INT_HANDLER   PCF_CONCATE(TIMER0,_IRQHandler)
#define TIMER1_INT_HANDLER   PCF_CONCATE(TIMER1,_IRQHandler)
#define TIMER2_INT_HANDLER   PCF_CONCATE(TIMER2,_IRQHandler)
#define TIMER3_INT_HANDLER   PCF_CONCATE(TIMER3,_IRQHandler)

#define PWR_TIMER0        BIT_MASK(1)
#define PWR_TIMER1        BIT_MASK(2)
#define PWR_TIMER2        BIT_MASK(22)
#define PWR_TIMER3        BIT_MASK(23)


#define	PWR_TIMER_CH(X)		PCF_CONCATE(PWR_,X)
#define PCLK_DIV(X)         PCF_CONCATE(PCLK_DIV_,X)
#define PERIPH(X)			PCF_CONCATE(PERIPH_,X)
#define POWER_ON(X) 		PERIPH_SC->PCONP |= X
#define POWER_OFF(X) 		PERIPH_SC->PCONP &= ~(X)
#define IRQ_NUM(X)			PCF_CONCATE(X,_IRQn)

#endif      // __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_TIMER_TIMER_LPC1768_CONFIG_H
