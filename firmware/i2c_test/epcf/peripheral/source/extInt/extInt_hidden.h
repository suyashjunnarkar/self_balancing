/**
 * \file    extInt_hidden.h
 * \brief   hidden header file for External Interrupt Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *          It contains ExtIntDevice and ExtIntController structure definition.
 *
 */

#ifndef __EPCF_INCLUDE_PRIVATE_EXTINT_EXTINT_HIDDEN_H
#define __EPCF_INCLUDE_PRIVATE_EXTINT_EXTINT_HIDDEN_H

typedef struct EPCFExtIntController     EPCFExtIntController_t;
typedef struct EPCFExtIntDevice         EPCFExtIntDevice_t;
typedef struct EPCFAdapter              EPCFAdapter_t;

typedef int8_t (*epcfExtIntInit_fp)(EPCFExtIntDevice_t*, EPCFExtIntCfg_t*);
typedef int8_t (*epcfExtIntEnable_fp)(EPCFExtIntDevice_t*);
typedef int8_t (*epcfExtIntDisable_fp)(EPCFExtIntDevice_t*);
typedef int8_t (*epcfExtIntAttachCallback_fp)(EPCFExtIntDevice_t*, epcfCallback_fp, uint8_t);
typedef int8_t (*epcfExtIntDetachCallback_fp)(EPCFExtIntDevice_t*, uint8_t);
typedef int8_t (*epcfExtIntGetDeviceCount_fp)(EPCFExtIntController_t*);
typedef int8_t (*epcfExtIntClose_fp)(EPCFExtIntDevice_t*);

typedef struct EPCFExtIntDevice
{
    EPCFExtIntController_t*   controllerConfig;
    uint8_t                 extIntId;
    void*                   ExtIntChannelAddr;
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedExtIntDeviceId;         // ID Returned from the Device.
#endif
}EPCFExtIntDevice_t;

typedef struct EPCFExtIntController
{
    epcfExtIntInit_fp                  extIntInit;
    epcfExtIntEnable_fp                extIntEnable;
    epcfExtIntDisable_fp               extIntDisable;
    epcfExtIntAttachCallback_fp        extIntAttachCallback;
    epcfExtIntDetachCallback_fp        extIntDetachCallback;
    epcfExtIntGetDeviceCount_fp        extIntGetDeviceCount;
    epcfExtIntClose_fp                 extIntClose;
    void                               *hardwareCfg;
}EPCFExtIntController_t;

#endif      //  __EPCF_INCLUDE_PRIVATE_EXTINT_EXTINT_HIDDEN_H
