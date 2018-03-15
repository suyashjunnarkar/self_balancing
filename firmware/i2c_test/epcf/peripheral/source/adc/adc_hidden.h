/**
 * \file    adc_hidden.h
 * \brief   hidden header file for ADC Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *          It contains TimerDevice and TimerController structure defination.
 *
 */
 
#ifndef __EPCF_PERIPHERAL_SOURCE_ADC_ADC_HIDDEN_H
#define __EPCF_PERIPHERAL_SOURCE_ADC_ADC_HIDDEN_H


typedef struct EPCFAdcController EPCFAdcController_t;
typedef struct EPCFAdcDevice	EPCFAdcDevice_t;

typedef struct EPCFAdcDevice
{
	EPCFAdcController_t*    controllerConfig;
	uint8_t					adcId;
	void*                   adcChannelAddr;
	uint32_t				refVtg;
	EnEPCFAdcWidth_t		adcWidth;
	EnEPCFAdcStart_t		adcSingleConvStart;
	EnEPCFBoolean_t			interruptEnable;
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedAdcDeviceId;         // ID Returned from the Device.
#endif
}EPCFAdcDevice_t;

#endif      //  __EPCF_PERIPHERAL_SOURCE_ADC_ADC_HIDDEN_H
