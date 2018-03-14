/**
 * \file    gpio_lpc1768_config.h
 * \brief   Native GPIO Driver Configuration for LPC1768.
 *
 */

#ifndef __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_GPIO_GPIO_LPC1768_CONFIG_H
#define __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_GPIO_GPIO_LPC1768_CONFIG_H

/** \brief Maximum ports available for GPIO module              */

#define EPCF_EINT3_INT_HANDLER   PCF_CONCATE(EPCF_EINT3_CH,_IRQHandler)

#endif      // __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_GPIO_GPIO_LPC1768_CONFIG_H

/** @} */
