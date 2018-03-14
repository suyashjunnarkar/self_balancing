/**
 * \file    spi_lpc1768_config.h
 * \brief   Native SPI Driver Configuration for LPC1768.
 *
 */
#ifndef __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SPI_SPI_LPC1768_CONFIG_H
#define __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SPI_SPI_LPC1768_CONFIG_H

/** \brief Maximum ports available for SPI module               */
#define EPCF_SPI_MAX_CHANNEL        2

/** \brief Maximum devices supported for SPI module             */
#define EPCF_SPI_MAX_DEVICE_SUPPORTED   7

/** \brief ARCH SPECIFIC Configuration macros       */
#define EPCF_SPI0_CH                SSP0
#define EPCF_SPI1_CH                SSP1

#define EPCF_SPI0_CHANNEL           EPCF_PERIPH(EPCF_SPI0_CH)
#define EPCF_SPI1_CHANNEL           EPCF_PERIPH(EPCF_SPI1_CH)

#define EPCF_SPI0_INT_HANDLER       PCF_CONCATE(EPCF_SPI0_CH,_IRQHandler)
#define EPCF_SPI1_INT_HANDLER       PCF_CONCATE(EPCF_SPI1_CH,_IRQHandler)

#define EPCF_PWR_SSP0               BIT_MASK(21)
#define EPCF_PWR_SSP1               BIT_MASK(10)

#define EPCF_PWR_SPI_CH(X)          PCF_CONCATE(EPCF_PWR_,X)
#define EPCF_PCLK_DIV(X)            PCF_CONCATE(EPCF_PCLK_DIV,X)
#define EPCF_PERIPH(X)              PCF_CONCATE(PERIPH_,X)
#define EPCF_IRQ_NUM(X)             PCF_CONCATE(X,_IRQn)
#define EPCF_POWER_ON(X)            PERIPH_SC->PCONP |= X
#define EPCF_POWER_OFF(X)           PERIPH_SC->PCONP &= ~(X)

#endif      // __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SPI_SPI_LPC1768_CONFIG_H
