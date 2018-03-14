/**
 * \file  extInt.c
 * \brief This file is used to configure a UART device
 */

#include "epcf.h"
#undef __EPCF_H_FILE_INCLUDE

#define __EPCF_EXTINT_HIDDEN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,peripheral/,extInt/,extInt_hidden.h)
#include  __EPCF_EXTINT_HIDDEN_INCLUDE
#undef __EPCF_EXTINT_HIDDEN_INCLUDE

#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
    #define EXTINT_GET_DEVICE_COUNT()                           epcfNativeExtIntGetDeviceCount()

#elif(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    #define EXTINT_GET_DEVICE_COUNT(pExtIntController)          epcfNativeExtIntGetDeviceCount(pExtIntController)
#endif


#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
 

EPCFExtIntDevice_t* epcfCreateExtInt(EPCFExtIntCfg_t* pExtIntConfig)
{
    EPCFExtIntDevice_t* pExtIntDevice;
    int8_t status=0;
    
    if(EPCF_EXTINT_GET_DEVICE_COUNT())
    {
        pExtIntDevice = (EPCFExtIntDevice_t *)malloc(sizeof(EPCFExtIntDevice_t));
        if (pExtIntDevice == (EPCFExtIntDevice_t *)NULL)
        return NULL;

        pExtIntDevice->controllerConfig = NULL;

        status = epcfNativeExtIntInit(pExtIntDevice, pExtIntConfig);
        if(status != 0)
            return NULL;

        return pExtIntDevice;
    }
    else
        return NULL;
}
 
#endif
