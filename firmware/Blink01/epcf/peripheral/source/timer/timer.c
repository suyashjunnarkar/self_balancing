/**
 * \file  timer.c
 * \brief This file is used to configure a TIMER device
 */

#include "pcf.h"

#include "./timer_hidden.h"
 
EPCFTimerDevice_t* epcf_timer_createNative(EPCFTimerCfg_t* pTimerConfig)
{
	EPCFTimerDevice_t* pTimerDevice;
	int8_t status=0;
	
	if(epcf_timer_nativeGetDeviceCount())
	{
		pTimerDevice = (EPCFTimerDevice_t *)malloc(sizeof(EPCFTimerDevice_t));
		if (pTimerDevice == NULL)
		return NULL;

		status = epcf_timer_nativeInit(pTimerDevice, pTimerConfig);
		if(status != 0)
			return NULL;
		
		return pTimerDevice;
	}
	else
		return NULL;
}

#ifdef EPCF_SUPPORT_EXTENDED_TIMER
EPCFTimerDevice_t* epcf_timer_createExtended(EPCFTimerController_t* pTimerController, EPCFTimerCfg_t* pTimerConfig)
{
	EPCFTimerDevice_t* pTimerDevice;
	int8_t status = 0;

	if(epcf_timer_extGetDeviceCount(pTimerController))
	{
		pTimerDevice = (EPCFTimerDevice_t*)malloc(sizeof(EPCFTimerDevice_t));
		if(pTimerDevice == NULL)
			return NULL;

		pTimerDevice->controllerConfig = pTimerController;

		status = pTimerController->timerInit(pTimerDevice, pTimerConfig);
		if(status != 0)
			return NULL;

		return pTimerDevice;
	}
	else
		return NULL;	
}
#endif

int8_t epcf_timer_start(EPCFTimerDevice_t* pTimerDevice)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeStart(pTimerDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;	
}

int8_t epcf_timer_stop(EPCFTimerDevice_t* pTimerDevice)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeStop(pTimerDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_reset(EPCFTimerDevice_t* pTimerDevice)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeReset(pTimerDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

EnEPCFTimerState_t epcf_timer_getState(EPCFTimerDevice_t* pTimerDevice)
{
	EnEPCFTimerState_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeGetState(pTimerDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_getTime(EPCFTimerDevice_t* pTimerDevice,EPCFTime_t* time)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeGetTime(pTimerDevice,time);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_setCounter(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerInputPolarity_t inputPolarity)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeSetCounter(pTimerDevice,channel,inputPolarity);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_getCounterValue(EPCFTimerDevice_t* pTimerDevice, uint32_t* count)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeGetCounterValue(pTimerDevice,count);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_attachCallback(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerInterruptSource_t interruptSource,epcfCallback_fp callback)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeAttachCallback(pTimerDevice,interruptSource,callback);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_detachCallback(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerInterruptSource_t interruptSource)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeDetachCallback(pTimerDevice,interruptSource);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_setCompareTime(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerCompareAction_t compareAction,EnEPCFTimerPinAction pinAction,EPCFTime_t time)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeSetCompareTime(pTimerDevice,channel,compareAction,pinAction,time);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_setInputCapture(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerInputPolarity_t inputPolarity)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeSetInputCapture(pTimerDevice,channel,inputPolarity);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_getInputCaptureTime(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EPCFTime_t* time)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeGetInputCaptureTime(pTimerDevice,channel,time);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_timer_close(EPCFTimerDevice_t* pTimerDevice)
{
	int8_t status=0;

	if(pTimerDevice->controllerConfig == NULL)
	{
		status = epcf_timer_nativeClose(pTimerDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;	
}

uint8_t epcf_timer_getDeviceCount()
{
	uint8_t status=0;
	status = epcf_timer_nativeGetDeviceCount();
	return status;
}

uint8_t epcf_timer_extGetDeviceCount(EPCFTimerController_t* pTimerController)
{
	uint8_t status=0;

//	TODO: controller structure is not defined
	return status;
}





