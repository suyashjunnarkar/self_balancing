/**
 * \file    gpio_hidden.h
 * \brief   hidden header file for GPIO Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *          It contains GpioDevice and GpioController structure defination.
 *
 */

#ifndef __EPCF_PERIPHERAL_SOURCE_GPIO_GPIO_HIDDEN_H
#define __EPCF_PERIPHERAL_SOURCE_GPIO_GPIO_HIDDEN_H

typedef struct EPCFGpioController EPCFGpioController_t;
typedef struct EPCFAdapter  EPCFAdapter_t;

typedef int8_t (*epcfGpioInit_fp)(EPCFGpioDevice_t*,EPCFGpioCfg_t*);
typedef int8_t (*epcfGpioSet_fp)(EPCFGpioDevice_t*);
typedef int8_t (*epcfGpioClear_fp)(EPCFGpioDevice_t*);
typedef int8_t (*epcfGpioRead_fp)(EPCFGpioDevice_t*);
typedef int8_t (*epcfGpioSetDirection_fp)(EPCFGpioDevice_t*, EnEPCFGpioDirection_t);
typedef uint32_t (*epcfGpioGetDeviceCount_fp)(EPCFGpioController_t*);

typedef struct EPCFGpioDevice
{
    EPCFGpioController_t*   controllerConfig;
    EPCFPortPin_t           portPin;
    EnEPCFGpioDirection_t   direction;
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedGpioDeviceId;
#endif
}EPCFGpioDevice_t;

typedef struct EPCFGpioController
{
    epcfGpioInit_fp             gpioInit;
    epcfGpioSet_fp              gpioSet;
    epcfGpioClear_fp            gpioClear;
    epcfGpioRead_fp             gpioRead;
    epcfGpioSetDirection_fp     gpioSetDirection;
    epcfGpioGetDeviceCount_fp   gpioGetDeviceCount;
    void*                       hardwareCfg;
}EPCFGpioController_t;

#endif      //  __EPCF_PERIPHERAL_SOURCE_GPIO_GPIO_HIDDEN_H
