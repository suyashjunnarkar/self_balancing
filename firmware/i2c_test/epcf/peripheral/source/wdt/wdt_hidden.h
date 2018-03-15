/**
 * \file    wdt_hidden.h
 * \brief   hidden header file for WDT Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *          It contains WdtDevice and WdtController structure definition.
 *
 */

#ifndef __EPCF_INCLUDE_PRIVATE_WDT_WDT_HIDDEN_H
#define __EPCF_INCLUDE_PRIVATE_WDT_WDT_HIDDEN_H

typedef struct EPCFWdtController   		EPCFWdtController_t;
typedef struct EPCFWdtDevice			EPCFWdtDevice_t;
typedef struct EPCFAdapter          	EPCFAdapter_t;

typedef int8_t (*epcfWdtInit_fp)(EPCFWdtDevice_t*, EPCFWdtCfg_t*);
typedef int8_t (*epcfWdtStart_fp)(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t timeout);
typedef int8_t (*epcfWdtStop_fp)(EPCFWdtDevice_t* pWdtDevice);
typedef int8_t (*epcfWdtReset_fp)(EPCFWdtDevice_t* pWdtDevice);
typedef int8_t (*epcfWdtGetRemainingTimeToTimeout_fp)(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t* time);
typedef EnEPCFWdtState_t (*epcfWdtGetState_fp)(EPCFWdtDevice_t* pWdtDevice);
typedef int8_t (*epcfWdtGetDeviceCount_fp)(EPCFWdtController_t*);
typedef int8_t (*epcfWdtClose_fp)(EPCFWdtDevice_t*);

typedef struct EPCFWdtDevice
{
    EPCFWdtController_t*   controllerConfig;
    uint8_t                 wdtId;
    void*                   wdtChannelAddr;
    EPCFTime_t				resolution;
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedWdtDeviceId;         // ID Returned from the Device.
#endif
}EPCFWdtDevice_t;

typedef struct EPCFWdtController
{
    epcfWdtInit_fp                  		WdtInit;
    epcfWdtStart_fp							WdtStart;
    epcfWdtStop_fp							WdtStop;
    epcfWdtReset_fp							WdtReset;
    epcfWdtGetRemainingTimeToTimeout_fp		WdtGetRemainingTimeToTimeout;
    epcfWdtGetState_fp						WdtGetState;
    epcfWdtGetDeviceCount_fp        		WdtGetDeviceCount;
    epcfWdtClose_fp          	   			WdtClose;
    void                               		*hardwareCfg;
}EPCFExtIntController_t;

#endif      //  __EPCF_INCLUDE_PRIVATE_WDT_WDT_HIDDEN_H
