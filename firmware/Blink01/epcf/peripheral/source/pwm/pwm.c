/**
 * \file  pwm.c
 * \brief This file is used to configure a PWM device
 */

#include "pcf.h"

#define __EPCF_PRIVATE_PWM_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,pwm/,pwm_hidden.h)
#include  __EPCF_PRIVATE_PWM_H_INCLUDE
#undef __EPCF_PRIVATE_PWM_H_INCLUDE

EPCFPwmDevice_t* epcf_pwm_createNative(EPCFPwmCfg_t* pPwmConfig)
{
    EPCFPwmDevice_t* pPwmDevice;
    int8_t status=0;

    if(epcf_pwm_getDeviceCount())
    {
        pPwmDevice = (EPCFPwmDevice_t *)malloc(sizeof(EPCFPwmDevice_t));
        if (pPwmDevice == NULL)
            return NULL;

		pPwmDevice->controllerConfig = NULL;
		
        status = epcf_pwm_nativeInit(pPwmDevice, pPwmConfig);
        if(status != 0)
            return NULL;

        return pPwmDevice;
    }
    else
        return NULL;
}

#ifdef EPCF_SUPPORT_EXTENDED_PWM
EPCFPwmDevice_t* epcf_pwm_CreateExtended(EPCFPwmController_t* pPwmController, EPCFPwmCfg_t* pPwmConfig)
{
	EPCFPwmDevice_t* pPwmDevice;
	int8_t status = 0;

	if(epcf_pwm_extGetDeviceCount(pPwmController))
	{
		pPwmDevice = (EPCFPwmDevice_t*)malloc(sizeof(EPCFPwmDevice_t));
		if(pPwmDevice == NULL)
			return NULL;

		pPwmDevice->controllerConfig = pPwmController;

		status = pPwmController->pwmInit(pPwmDevice, pPwmConfig);
		if(status != 0)
			return NULL;

		return pPwmDevice;
	}
	else
		return NULL;
}
#endif

int8_t epcf_pwm_start(EPCFPwmDevice_t* pPwmDevice)
{
	int8_t status=0;

	if(pPwmDevice->controllerConfig == NULL)
	{
		status = epcf_pwm_nativeStart(pPwmDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_pwm_stop(EPCFPwmDevice_t* pPwmDevice)
{
	int8_t status=0;

	if(pPwmDevice->controllerConfig == NULL)
	{
		status = epcf_pwm_nativeStop(pPwmDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_pwm_attachCallback(EPCFPwmDevice_t* pPwmDevice,EnEPCFPwmChannel_t channel,EnEPCFPwmInterruptSource_t interruptSource,epcfCallback_fp callback)
{
	int8_t status=0;

	if(pPwmDevice->controllerConfig == NULL)
	{
		status = epcf_pwm_nativeAttachCallback(pPwmDevice,channel,interruptSource,callback);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_pwm_detachCallback(EPCFPwmDevice_t* pPwmDevice,uint8_t callbackId)
{
	int8_t status=0;

	if(pPwmDevice->controllerConfig == NULL)
	{
		status = epcf_pwm_nativeDetachCallback(pPwmDevice,callbackId);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_pwm_setPeriod(EPCFPwmDevice_t* pPwmDevice,EPCFTime_t period)
{
	int8_t status=0;

	if(pPwmDevice->controllerConfig == NULL)
	{
		status = epcf_pwm_nativeSetPeriod(pPwmDevice,period);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_pwm_setDutyCycle(EPCFPwmDevice_t* pPwmDevice,EnEPCFPwmChannel_t channel,uint8_t dutyCycle,EnEPCFPwmOutputSignal_t signal)
{
	int8_t status=0;

	if(pPwmDevice->controllerConfig == NULL)
	{
		status = epcf_pwm_nativeSetDutyCycle(pPwmDevice,channel,dutyCycle,signal);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;	
}

int8_t epcf_pwm_close(EPCFPwmDevice_t* pPwmDevice)
{
	int8_t status=0;

	if(pPwmDevice->controllerConfig == NULL)
	{
		status = epcf_pwm_nativeClose(pPwmDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;	
}

uint8_t epcf_pwm_getDeviceCount()
{
	uint8_t retVal=0;

	retVal = epcf_pwm_nativeGetDeviceCount();
	return retVal;
}

EnEPCFPwmState_t epcf_pwm_getState(EPCFPwmDevice_t* pPwmDevice)
{
	EnEPCFPwmState_t status=0;

	if(pPwmDevice->controllerConfig == NULL)
	{
		status = epcf_pwm_nativeGetState(pPwmDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;		
}

uint8_t epcf_pwm_extGetDeviceCount(EPCFPwmController_t* pPwmController)
{
	uint8_t status=0;
//	TODO: controller structure is not defined
	return status;
}










