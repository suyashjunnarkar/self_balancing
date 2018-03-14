/**
 * \file  sysClk.h
 * \brief This file is used to configure sysClock of the device
 */

#ifndef __EPCF__INCLUDED_PERIPHERAL_INCLUDE_SYSCLK_SYSCLK_H
#define __EPCF__INCLUDED_PERIPHERAL_INCLUDE_SYSCLK_SYSCLK_H

typedef struct EPCFSysClkDevice EPCFSysClkDevice_t;

/** \brief	Enumeration for PLL Clock Source Selection			*/
typedef enum EnEPCFClkSrc
{
	enEPCFPllClkSrcInternalRC = 0x00,		/**< Selects the Internal RC oscillator as the PLL0 clock source.	*/
	enEPCFPllClkSrcMainOSC,					/**< Selects the main oscillator as the PLL0 clock source.			*/
	enEPCFPllClkSrcRtcOSC,					/**< Selects the RTC oscillator as the PLL0 clock source.			*/
    enEPCFClkSrc_Max	                    /**< Special value for boundary checking	*/
}EnEPCFClkSrc_t;

/** \brief Enumeration for peripheral clock divider		*/
typedef enum EnEPCFPclkDivider
{
	enEPCFPclkDiv_4 = 0,					/**< PCLK_peripheral = CCLK/4.              */
	enEPCFPclkDiv_1,						/**< PCLK_peripheral = CCLK/1.		        */
	enEPCFPclkDiv_2,						/**< PCLK_peripheral = CCLK/2.              */
	enEPCFPclkDiv_8,						/**< PCLK_peripheral = CCLK/8.              */
    enEPCFPclkDivider_Max					/**< Special value for boundary checking    */
}EnEPCFPclkDivider_t;

/**	\brief	CPU Clock configure Structure	*/
typedef struct EPCFSysClkCfg
{
	uint32_t cpuFreqHz;					/**< Set frequency of CPU Clock.			*/
	uint32_t oscFreq;					/**< Value of Oscillator Frequency in Hz.  	*/
	EnEPCFClkSrc_t pllClkSrc;			/**< Set Clock Source for PLL.				*/
}EPCFSysClkCfg_t;

//ToDo: Add comments for function description
extern EPCFSysClkDevice_t* epcfCreateSysClk(EPCFSysClkCfg_t* pSysClkConfig);
extern uint32_t epcfNativeSysGetCpuClock(EPCFSysClkDevice_t *pSysClkDevice);
extern void epcfNativeSysSetPclkDiv(EPCFSysClkDevice_t *pSysClkDevice, uint32_t peripheral, uint32_t clockDiv);
extern uint32_t epcfNativeSysGetPclk(EPCFSysClkDevice_t *pSysClkDevice, uint32_t peripheral);

#endif      //__EPCF__INCLUDED_PERIPHERAL_INCLUDE_SYSCLK_SYSCLK_H


