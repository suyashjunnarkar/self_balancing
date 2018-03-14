/**
 * \file  gpio.c
 * \brief This file is used to configure a GPIO device
 */

 #include "pcf.h"

#define __EPCF_GPIO_HIDDEN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,gpio/,gpio_hidden.h)
#include  __EPCF_GPIO_HIDDEN_INCLUDE
#undef __EPCF_GPIO_HIDDEN_INCLUDE

#include "./gpio_hidden.h"

EPCFGpioDevice_t* epcf_gpio_createNative(EPCFGpioCfg_t* pGpioConfig)
{
    EPCFGpioDevice_t* pGpioDevice;
    int8_t status=0;

	if(epcf_gpio_nativeGetDeviceCount())
	{
		pGpioDevice = (EPCFGpioDevice_t *)malloc(sizeof(EPCFGpioDevice_t));
		if (pGpioDevice == PCF_NULL)
			return PCF_NULL;

		pGpioDevice->portPin.port 		= pGpioConfig->portPin.port;
		pGpioDevice->portPin.pin 		= pGpioConfig->portPin.pin;
		pGpioDevice->direction 			= pGpioConfig->direction;
		pGpioDevice->controllerConfig 	= PCF_NULL;

		status = epcf_gpio_nativeInit(pGpioConfig);
	    if(status != 0)
	         return PCF_NULL;

        return pGpioDevice;
    }
    else
        return PCF_NULL;
}

#ifdef EPCF_SUPPORT_EXTENDED_GPIO
EPCFGpioDevice_t* epcf_gpio_createExtended(EPCFGpioController_t* pGpioController, EPCFGpioCfg_t* pGpioConfig)
{
    EPCFGpioDevice_t* pGpioDevice=0;
    int8_t status=0;

    if(epcf_gpio_extGetDeviceCount(pGpioController))
    {
        pGpioDevice = (EPCFGpioDevice_t *)malloc(sizeof(EPCFGpioDevice_t));
        if (pGpioDevice == 0)
            return 0;

        pGpioDevice->portPin.port       = pGpioConfig->portPin.port;
        pGpioDevice->portPin.pin        = pGpioConfig->portPin.pin;
        pGpioDevice->direction          = pGpioConfig->direction;
        pGpioDevice->controllerConfig   = pGpioController;


            status = pGpioController->gpioInit(pGpioDevice, pGpioConfig);
            if(status != 0)
                return NULL;

        return pGpioDevice;
    }
    else
        return NULL;
}
#endif

int8_t epcf_gpio_set(EPCFGpioDevice_t* pGpiodevice)
{
    int8_t status=0;

    if(pGpiodevice->controllerConfig == NULL)
    {
        status = epcf_gpio_nativeSet(pGpiodevice);
    }
    else
    {
        status = pGpiodevice->controllerConfig->gpioSet(pGpiodevice);
    }
    return status;
}

int8_t epcf_gpio_clear(EPCFGpioDevice_t* pGpiodevice)
{
    int8_t status=0;

    if(pGpiodevice->controllerConfig == NULL)
    {
        status = epcf_gpio_nativeClear(pGpiodevice);
    }
    else
    {
        status = pGpiodevice->controllerConfig->gpioClear(pGpiodevice);
    }
    return status;
}

int8_t epcf_gpio_read(EPCFGpioDevice_t* pGpiodevice)
{
    int8_t retVal=0;

    if(pGpiodevice->controllerConfig == NULL)
    {
        retVal = epcf_gpio_nativeRead(pGpiodevice);
    }
    else
    {
        retVal = pGpiodevice->controllerConfig->gpioRead(pGpiodevice);
    }
    return retVal;
}

int8_t epcf_gpio_setDirection(EPCFGpioDevice_t* pGpiodevice, EnEPCFGpioDirection_t direction)
{
    int8_t status=0;

    if(pGpiodevice->controllerConfig == NULL)
    {
        status = epcf_gpio_nativeSetDirection(pGpiodevice,direction);
    }
    else
    {
        status = pGpiodevice->controllerConfig->gpioSetDirection(pGpiodevice,direction);
    }
    return status;
}

#ifdef EPCF_USING_MT_ENV
// TODO : Adding the Support for EPCF_USING_MT_ENV
// TODO : Add Comments for Function Discription.
extern int8_t epcf_gpio_lock(EPCFGpioDevice_t* pGpioDevice)
{

}
extern int8_t epcf_gpio_unlock(EPCFGpioDevice_t* pGpioDevice)
{

}
#endif

uint8_t epcf_gpio_getDeviceCount()
{
	uint8_t retVal=0;
    retVal = epcf_gpio_nativeGetDeviceCount();
    return retVal;
}

uint8_t epcf_gpio_extGetDeviceCount(EPCFGpioController_t* pGpioController)
{
	uint8_t retVal;
	retVal = pGpioController->gpioGetDeviceCount(pGpioController);
	return retVal;
}
