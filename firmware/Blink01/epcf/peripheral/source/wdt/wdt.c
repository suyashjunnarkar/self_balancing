/**
 * \file  uart.c
 * \brief This file is used to configure a UART device
 */

#include "pcf.h"

#include "./wdt_hidden.h"
 

EPCFWdtDevice_t* epcf_wdt_createNative(EPCFWdtCfg_t* pWdtConfig)
{
    EPCFWdtDevice_t* pWdtDevice;
    int8_t status=0;
    
    if(epcf_wdt_getDeviceCount())
    {
        pWdtDevice = (EPCFWdtDevice_t *)malloc(sizeof(EPCFWdtDevice_t));
        if (pWdtDevice == (EPCFWdtDevice_t *)NULL)
        return NULL;

        pWdtDevice->controllerConfig = NULL;

        status = epcfNativeWdtInit(pWdtDevice, pWdtConfig);
        if(status != 0)
            return NULL;

        return pWdtDevice;
    }
    else
        return NULL;
}
 
