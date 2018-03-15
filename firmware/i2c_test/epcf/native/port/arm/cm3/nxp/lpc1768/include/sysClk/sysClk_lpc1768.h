/**
 * \file	sysClk_lpc1768.h
 * \brief   SysCLK Driver Description for LPC1768.
 * \copyright Copyright (c) 2014 <br> PhiRobotics Research Pvt Ltd
 * 
 * \par
 *  For licensing information, see the file 'LICENSE' in the root folder of
 *  this software module.
 * 
 * Review status: NO
 *
 */

#ifndef __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SYSCLK_SYSCLK_LPC1768_H
#define __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SYSCLK_SYSCLK_LPC1768_H

#include "sysClk_lpc1768_config.h"

//typedef struct EPCFSysClkDevice EPCFSysClkDevice_t;
//typedef struct EPCFSysClkCfg EPCFSysClkCfg_t;


EPCFSysClkDevice_t* epcfNativeCreateSysClk(EPCFSysClkCfg_t* pSysClkConfig);

/**
 * The function calculates Frequency of CPU Clock(CCLK).
 *
 * \return CPU clock Frequency in Hz.
 */
uint32_t epcfNativeSysGetCpuClock(EPCFSysClkDevice_t *pSysClkDevice);

/**
 * Function sets peripheral clock divider. 
 * CPU clock is divided by the peripheral clock divider and then fed to peripheral.
 *
 * \param peripheral peripheral number to set clock divider.
 * 			predefined macros to be used,defined in prime_sysClk_config.h.
 * \param clockDiv clock divider to set for peripheral.
 */
void epcfNativeSysSetPclkDiv(EPCFSysClkDevice_t *pSysClkDevice, uint32_t peripheral, uint32_t clockDiv);

/**
 * The function reads the clock divider set for the peripheral and calculates peripheral clock frequency
 *
 * \param peripheral peripheral number to get clock frequency
 *			predefined macros to be used,defined in prime_sysClk_config.h.
 *
 * \return peripheral clock frequency in hertz
 */
uint32_t epcfNativeSysGetPclk(EPCFSysClkDevice_t *pSysClkDevice, uint32_t peripheral);

#endif 		// __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SYSCLK_SYSCLK_LPC1768_H

/** @} */
