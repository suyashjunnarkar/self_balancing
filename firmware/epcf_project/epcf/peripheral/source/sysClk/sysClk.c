/**
 * \file  sysClk.c
 * \brief This file is used to configure sysClk.
 */

 #include "pcf.h"
 
 EPCFSysClkDevice_t* epcfCreateSysClk(EPCFSysClkCfg_t* pSysClkConfig)
 {
	 EPCFSysClkDevice_t* pDevice;
	 
	 pDevice = epcfNativeCreateSysClk(pSysClkConfig);
	 return pDevice;
 }
