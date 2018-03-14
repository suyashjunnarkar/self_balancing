/**
 * \file    i2c_lpc1768_config.h
 * \brief   Native I2C Driver Configuration for LPC1768.
 *
 */
#ifndef __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_I2C_I2C_LPC1768_CONFIG_H
#define __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_I2C_I2C_LPC1768_CONFIG_H

/** \brief ARCH SPECIFIC Configuration macros       */
#define I2C0_CH            I2C0
#define I2C1_CH            I2C1
#define I2C2_CH            I2C2

#define I2C0_CHANNEL       PERIPH(I2C0_CH)
#define I2C1_CHANNEL       PERIPH(I2C1_CH)
#define I2C2_CHANNEL       PERIPH(I2C2_CH)

#define I2C0_INT_HANDLER   PCF_CONCATE(I2C0,_IRQHandler)
#define I2C1_INT_HANDLER   PCF_CONCATE(I2C1,_IRQHandler)
#define I2C2_INT_HANDLER   PCF_CONCATE(I2C2,_IRQHandler)

#define PWR_I2C0        (1<<7)
#define PWR_I2C1        (1<<19)
#define PWR_I2C2        (1<<26)

#define PWR_I2C_CH(X)       PCF_CONCATE(PWR_,X)
#define PCLK_DIV(X)         PCF_CONCATE(PCLK_DIV_,X)
#define PERIPH(X)           PCF_CONCATE(PERIPH_,X)
#define POWER_ON(X)         PERIPH_SC->PCONP |= X
#define POWER_OFF(X)        PERIPH_SC->PCONP &= ~(X)
#define IRQ_NUM(X)          PCF_CONCATE(X,_IRQn)

#endif      // __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_I2C_I2C_LPC1768_CONFIG_H
