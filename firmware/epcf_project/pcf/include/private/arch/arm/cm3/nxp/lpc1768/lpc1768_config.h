/*
 * lpc1768_config.h
 *
 *  Created on: 2 Mar 2017
 *      Author: Vivek
 */

#ifndef PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_CONFIG_H
#define PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_CONFIG_H

// Enable the Macro for all peripheral Which are on-chip in the Lpc1768

// Must defined Macro
#define PCF_IS_PERIPH_SYSCLK      PCF_YES

#define PCF_IS_PERIPH_ADC         PCF_YES
#define PCF_IS_PERIPH_DAC         PCF_YES
#define PCF_IS_PERIPH_CAN         PCF_YES
//#define PCF_IS_PERIPH_GPDMA       PCF_YES
#define PCF_IS_PERIPH_GPIO        PCF_YES
#define PCF_IS_PERIPH_GPIOINT     PCF_YES
#define PCF_IS_PERIPH_TIMER       PCF_YES
#define PCF_IS_PERIPH_PWM         PCF_YES
#define PCF_IS_PERIPH_UART        PCF_YES         // UASRT- UART1
#define PCF_IS_PERIPH_SPI         PCF_YES
//#define PCF_IS_PERIPH_SSP        PCF_YES
#define PCF_IS_PERIPH_I2C         PCF_YES
#define PCF_IS_PERIPH_I2S         PCF_YES
#define PCF_IS_PERIPH_RIT         PCF_YES
#define PCF_IS_PERIPH_RTC         PCF_YES
#define PCF_IS_PERIPH_WDT         PCF_YES

#define PCF_IS_PERI_MCPWM       PCF_YES
#define PCF_IS_PERI_QEI         PCF_YES
#define PCF_IS_PERI_USB         PCF_YES
#define PCF_IS_PERI_EMAC        PCF_YES


#endif // PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_CONFIG_H
