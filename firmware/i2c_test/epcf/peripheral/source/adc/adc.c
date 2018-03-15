/**
 * \file  adc.c
 * \brief This file is used to configure a ADC device
 */

#include "pcf.h"

#define __EPCF_PRIVATE_ADC_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,adc/,adc_hidden.h)
#include  __EPCF_PRIVATE_ADC_H_INCLUDE
#undef __EPCF_PRIVATE_ADC_H_INCLUDE

 
EPCFAdcDevice_t* epcf_adc_createNative(EPCFAdcCfg_t* pAdcConfig)
{
	EPCFAdcDevice_t* pAdcDevice;
	int8_t status=0;
	
	if(epcf_adc_getDeviceCount())
	{
		pAdcDevice = (EPCFAdcDevice_t *)malloc(sizeof(EPCFAdcDevice_t));
		if (pAdcDevice == NULL)
			return NULL;

		pAdcDevice->controllerConfig = NULL;
		
		status = epcf_adc_nativeInit(pAdcDevice, pAdcConfig);
		if(status != 0)
			return NULL;
		
		return pAdcDevice;
	}
	else
		return NULL;
}

#ifdef EPCF_SUPPORT_EXTENDED_ADC
EPCFAdcDevice_t* epcf_adc_createExtended(EPCFAdcController_t* pAdcController, EPCFAdcCfg_t* pAdcConfig)
{
	EPCFAdcDevice_t* pAdcDevice;
	int8_t status = 0;

	if(epcf_adc_extGetDeviceCount(pAdcController))
	{
		pAdcDevice = (EPCFAdcDevice_t*)malloc(sizeof(EPCFAdcDevice_t));
		if(pAdcDevice == NULL)
			return NULL;

		pAdcDevice->controllerConfig = pAdcController;

		status = pAdcController->adcInit(pAdcDevice, pAdcConfig);
		if(status != 0)
			return NULL;

		return pAdcDevice;
	}
	else
		return NULL;
}
#endif

int8_t epcf_adc_continuousConversionStart(EPCFAdcDevice_t* pAdcDevice,uint16_t channel)
{
	int8_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeContinuousConversionStart(pAdcDevice,channel);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_adc_conversionStop(EPCFAdcDevice_t* pAdcDevice)
{
	int8_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeConversionStop(pAdcDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_adc_getValue(EPCFAdcDevice_t* pAdcDevice, uint32_t* data, EnEPCFAdcChannel_t channel)
{
	int8_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeGetValue(pAdcDevice,data,channel);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_adc_getVoltage(EPCFAdcDevice_t* pAdcDevice, uint32_t* milliVolts, EnEPCFAdcChannel_t channel)
{
	int8_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeGetVoltage(pAdcDevice,milliVolts,channel);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_adc_attachCallback(EPCFAdcDevice_t* pAdcDevice,epcfCallback_fp callback, EnEPCFAdcChannel_t channel)
{
	int8_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeAttachCallback(pAdcDevice,callback,channel);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_adc_detachCallback(EPCFAdcDevice_t* pAdcDevice, EnEPCFAdcChannel_t channel)
{
	int8_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeDetachCallback(pAdcDevice,channel);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_adc_singleConversion(EPCFAdcDevice_t* pAdcDevice,EnEPCFAdcChannel_t channel,uint32_t* data,EPCFTime_t timeout)
{
	int8_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeSingleConversion(pAdcDevice,channel,data,timeout);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_adc_singleConversionGetVoltage(EPCFAdcDevice_t* pAdcDevice,EnEPCFAdcChannel_t channel,uint32_t* milliVolts,EPCFTime_t timeout)
{
	int8_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeSingleConversionGetVoltage(pAdcDevice,channel,milliVolts,timeout);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_adc_close(EPCFAdcDevice_t* pAdcDevice)
{
	int8_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeClose(pAdcDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

uint8_t epcf_adc_getDeviceCount()
{
	uint8_t status=0;

	status=epcf_adc_nativeGetDeviceCount();
	return status;
}

EnEPCFAdcState_t epcf_adc_getState(EPCFAdcDevice_t* pAdcDevice)
{
	EnEPCFAdcState_t status=0;

	if(pAdcDevice->controllerConfig == NULL)
	{
		status = epcf_adc_nativeGetState(pAdcDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

uint8_t epcf_adc_extGetDeviceCount(EPCFAdcController_t* pAdcController)
{
	uint8_t status=0;

//	TODO: controller structure is not defined
	return status;
}


