
#include "pcf.h"

#define __EPCF_PRIVATE_ADC_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,adc/,adc_hidden.h)
#include  __EPCF_PRIVATE_ADC_H_INCLUDE
#undef __EPCF_PRIVATE_ADC_H_INCLUDE

#define __ADC_MAX_DEVICE		1
#define __ADC_MAX_CHANNEL		8
#define	__ADC_MAX_FREQ			13000000

// Lookup tables.
static uint32_t adcIrqNum[__ADC_MAX_DEVICE] = {IRQ_NUM(ADC_CH)};
static uint32_t pwrAdcCh[__ADC_MAX_DEVICE] = {PWR_ADC_CH(ADC_CH)};
static uint32_t adcChannelAddr[__ADC_MAX_DEVICE] = {ADC_BASE};
static uint32_t pdivClkAdcCh[__ADC_MAX_DEVICE] = {PCLK_DIV(ADC_CH)};
/*
 * Below variable adcAltFunction
 * Row 1 -> Port 0
 * Row 2 -> Port 1
 */
const uint8_t adcAltFunction[2][32] =
{
 //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
  {0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3}
};
/*
 * Below variable externalSrcPinAdcAltFunction
 * Row 1 -> Port 1
 * Row 2 -> Port 3
 */
const uint8_t externalSrcPinAdcAltFunction[2][32] =
{
 //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 0, 0, 3, 0, 3, 3, 3, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0}
};
// Lookup tables ends

// Static Variable Declaration
static uint32_t  adcDeviceCount = __ADC_MAX_DEVICE;
static EPCFAdcDevice_t* adcDevice[__ADC_MAX_DEVICE];
static EnEPCFBoolean_t adcChInit[__ADC_MAX_DEVICE] = {enEPCFBoolean_False};   // initialize flag for the channel
static EnEPCFAdcState_t adcState = enEPCFAdcState_Stopped;
static volatile epcfCallback_fp  adcCallbackArr[__ADC_MAX_CHANNEL];
static uint8_t adcCallbackId[__ADC_MAX_CHANNEL];

// Static Function Declaration
static int8_t __epcfAdcInit(EPCFAdcDevice_t* pAdcDevice, EPCFAdcCfg_t *pConfig);
static int8_t __epcfAdcGetPrescaler(uint8_t *pclkDiv, uint32_t *prescaler);
// Function Defination


int8_t epcf_adc_nativeInit(EPCFAdcDevice_t* pAdcDevice, EPCFAdcCfg_t* pConfig)
{
	EPCFPortPin_t *pAdcPortPinCfg;
	EPCFPortPin_t *pExtSrcPortPinCfg;
	int8_t status = 0;
	uint8_t ind, adcChannel, extSrc;

	adcChannel = ((EPCFAdcLpc1768Cfg_t*)(pConfig->hardwareCfg))->noOfAdcChannel;
	extSrc = ((EPCFAdcLpc1768Cfg_t*)(pConfig->hardwareCfg))->noOfExternalSrc;

	EPCFPinCfg_t pAdcPinCfg[adcChannel];
	EPCFPinCfg_t pExtSrcPinCfg[extSrc];

	pAdcDevice->adcId = pConfig->adcId;
	pAdcDevice->adcChannelAddr = (ADC_TypeDef*)adcChannelAddr[pConfig->adcId];
	pAdcDevice->refVtg = pConfig->refVtg;
	pAdcDevice->adcWidth = pConfig->adcWidth;
	pAdcDevice->adcSingleConvStart = ((EPCFAdcLpc1768Cfg_t*)(pConfig->hardwareCfg))->adcSingleConvStart;
	pAdcDevice->interruptEnable = pConfig->interruptEnable;
	adcDevice[pConfig->adcId] = pAdcDevice;

	pAdcPortPinCfg = ((EPCFAdcLpc1768Cfg_t*)(pConfig->hardwareCfg))->adcChannelPin;
	pExtSrcPortPinCfg = ((EPCFAdcLpc1768Cfg_t*)(pConfig->hardwareCfg))->externalSrcPin;

	for(ind=0; ind<adcChannel; ind++)
	{
		pAdcPinCfg[ind].direction    = 0; // enEPCFGpioDirInput
		pAdcPinCfg[ind].mode         = 0; // enEPCFGpioPinModePullUp
		pAdcPinCfg[ind].openDrain    = 0; // open Drain disable
		pAdcPinCfg[ind].portPin.port = pAdcPortPinCfg[ind].port;
		pAdcPinCfg[ind].portPin.pin  = pAdcPortPinCfg[ind].pin;

		pAdcPinCfg[ind].altFunction = adcAltFunction[(pAdcPinCfg[ind].portPin.port)][pAdcPinCfg[ind].portPin.pin];

		status = epcfPinInit(&pAdcPinCfg[ind]);
		if(status != EPCF_STATUS_SUCCESS)
		  return -1;
	}

	for(ind=0; ind<extSrc; ind++)
	{
		pExtSrcPinCfg[ind].direction    = 0; // enEPCFGpioDirInput
		pExtSrcPinCfg[ind].mode         = 0; // enEPCFGpioPinModePullUp
		pExtSrcPinCfg[ind].openDrain    = 0; // open Drain disable
		pExtSrcPinCfg[ind].portPin.port = pExtSrcPortPinCfg[ind].port;
		pExtSrcPinCfg[ind].portPin.pin  = pExtSrcPortPinCfg[ind].pin;

		pExtSrcPinCfg[ind].altFunction = externalSrcPinAdcAltFunction[(pExtSrcPinCfg[ind].portPin.port)-1][pExtSrcPinCfg[ind].portPin.pin];

		status = epcfPinInit(&pExtSrcPinCfg[ind]);
		if(status != EPCF_STATUS_SUCCESS)
		  return -1;
	}

	status = __epcfAdcInit(pAdcDevice, pConfig);
	if(status != 0)
		return EPCF_STATUS_ERROR;

	adcDeviceCount--;
	return EPCF_STATUS_SUCCESS;
}

static int8_t __epcfAdcInit(EPCFAdcDevice_t* pAdcDevice, EPCFAdcCfg_t *pConfig)
{
	int8_t status=0;
	uint32_t prescaler = 0;
	uint8_t pclkDivider = 0;
    // power on Timer peripheral
    POWER_ON(pwrAdcCh[pConfig->adcId]);

    status = __epcfAdcGetPrescaler(&pclkDivider, &prescaler);
    if (status != 0)
    	return EPCF_STATUS_NOT_CONFIGURED;
    // set peripheral clock divider
    epcfNativeSysSetPclkDiv(NULL, pdivClkAdcCh[pConfig->adcId], pclkDivider);

    ((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR = 0x0000;
    ((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADINTEN = 0x0000;
    ((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= (prescaler+1)<<8;
    // Disable power down mode
    ((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= (1<<21);

    adcChInit[pAdcDevice->adcId]= enEPCFBoolean_True;
    return EPCF_STATUS_SUCCESS;
}

static int8_t __epcfAdcGetPrescaler(uint8_t *pclkDiv, uint32_t *prescaler)
{
	uint32_t presCalVal=0;
	float cpuClk=0;
	uint8_t pclkDivInd=0;
	uint8_t pclkDivArr[4] = {1,2,4,8};

	cpuClk = epcfNativeSysGetCpuClock(NULL);
	for(pclkDivInd=0; pclkDivInd<4; pclkDivInd++)
	{
		for(presCalVal=1; presCalVal<65536; presCalVal++)
		{
			if( (uint64_t)( cpuClk / (pclkDivArr[pclkDivInd] * presCalVal) ) <= __ADC_MAX_FREQ )
			{
				*pclkDiv = pclkDivArr[pclkDivInd];
				*prescaler = presCalVal;
				return EPCF_STATUS_SUCCESS;
			}
		}
	}
	return EPCF_STATUS_ERROR;
}

int8_t epcf_adc_nativeContinuousConversionStart(EPCFAdcDevice_t* pAdcDevice,uint16_t channel)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;

	// Disable Interrupt
	NVIC_DisableIRQ(adcIrqNum[pAdcDevice->adcId]);
	// Select channel number
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= channel;
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADINTEN &= ~(1<<8);
	// Start bits disable
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR &= ~(0x07 <<24);
	// Burst Mode enable
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |=  (1<<16);
	// Enable Interrupt
	if(pAdcDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(adcIrqNum[pAdcDevice->adcId]);

	adcState = enEPCFAdcState_Running;
	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_adc_nativeConversionStop(EPCFAdcDevice_t* pAdcDevice)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;

	// Disable Interrupt
	NVIC_DisableIRQ(adcIrqNum[pAdcDevice->adcId]);
	// Burst Mode disable
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= (0<<16);
	// Start bits disable
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR &= ~(0x07 <<24);
	// Enable Interrupt
	if(pAdcDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(adcIrqNum[pAdcDevice->adcId]);

	adcState = enEPCFAdcState_Stopped;
	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_adc_nativeGetValue(EPCFAdcDevice_t* pAdcDevice,uint32_t* data,EnEPCFAdcChannel_t channel)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	if(channel > enEPCFAdcChannel_7)
		return EPCF_STATUS_INVALID_ARGS;

	uint8_t ind;

	// Disable Interrupt
	NVIC_DisableIRQ(adcIrqNum[pAdcDevice->adcId]);

	for(ind=0; ind<__ADC_MAX_CHANNEL; ind++)
	{
		if( (channel & (1<<ind)) == channel)
			break;
	}

	*data = ( (((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADDR[ind] >> 4)& 0xFFF );

	// Enable Interrupt
	if(pAdcDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(adcIrqNum[pAdcDevice->adcId]);

	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_adc_nativeGetVoltage(EPCFAdcDevice_t* pAdcDevice,uint32_t* milliVolts,EnEPCFAdcChannel_t channel)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	if(channel > enEPCFAdcChannel_7)
		return EPCF_STATUS_INVALID_ARGS;

	uint32_t adcValue;
	uint8_t ind;

	// Disable Interrupt
	NVIC_DisableIRQ(adcIrqNum[pAdcDevice->adcId]);

	for(ind=0; ind<__ADC_MAX_CHANNEL; ind++)
	{
		if( (channel & (1<<ind)) == channel)
			break;
	}

	adcValue = ( (((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADDR[ind] >> 4)& 0xFFF );

	*milliVolts = ( (adcValue * ((pAdcDevice->refVtg * 1000)/(1<<pAdcDevice->adcWidth))) / 1000 );

	// Enable Interrupt
	if(pAdcDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(adcIrqNum[pAdcDevice->adcId]);

	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_adc_nativeSingleConversion(EPCFAdcDevice_t* pAdcDevice,EnEPCFAdcChannel_t channel,uint32_t* data,EPCFTime_t timeout)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	if(channel>enEPCFAdcChannel_7)
		return EPCF_STATUS_INVALID_ARGS;

	uint8_t ind;

	// Disable Interrupt
	NVIC_DisableIRQ(adcIrqNum[pAdcDevice->adcId]);
	// Disable burst mode
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= (0<<16);
	// Select channel
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= channel;

	for(ind=0; ind<__ADC_MAX_CHANNEL; ind++)
	{
		if( (channel & (1<<ind)) == channel)
			break;
	}
	// Start conversion
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= (pAdcDevice->adcSingleConvStart << 24);
	// wait till conversion is completed
	while( ( ((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADDR[ind] & (1<<31) ) == 0);
	// Get data from data register
	*data = ( (((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADDR[ind] >> 4)& 0xFFF );
	// Enable Interrupt
	if(pAdcDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(adcIrqNum[pAdcDevice->adcId]);

	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_adc_nativeSingleConversionGetVoltage(EPCFAdcDevice_t* pAdcDevice,EnEPCFAdcChannel_t channel,uint32_t* milliVolts,EPCFTime_t timeout)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	if(channel>enEPCFAdcChannel_7)
		return EPCF_STATUS_INVALID_ARGS;

	uint32_t adcVal;
	uint8_t ind;

	// Disable Interrupt
	NVIC_DisableIRQ(adcIrqNum[pAdcDevice->adcId]);
	// Disable burst mode
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= (0<<16);
	// Select channel
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= channel;

	for(ind=0; ind<__ADC_MAX_CHANNEL; ind++)
	{
		if( (channel & (1<<ind)) == channel)
			break;
	}
	// Start conversion
	((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR |= (pAdcDevice->adcSingleConvStart << 24);
	// wait till conversion is completed
	while( ( ((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADDR[ind] & (1<<31) ) == 0);
	// Get data from data register
	adcVal = ( (((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADDR[ind] >> 4)& 0xFFF );

	*milliVolts = ( (adcVal * ((pAdcDevice->refVtg * 1000)/(1<<pAdcDevice->adcWidth))) / 1000 );
	// Enable Interrupt
	if(pAdcDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(adcIrqNum[pAdcDevice->adcId]);

	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_adc_nativeAttachCallback(EPCFAdcDevice_t* pAdcDevice,epcfCallback_fp callback, uint16_t channel)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	if(adcState == enEPCFAdcState_Running)
		return EPCF_STATUS_BUSY;
	if(channel>enEPCFAdcChannel_7)
		return EPCF_STATUS_INVALID_ARGS;

	uint8_t ind;

	if(pAdcDevice->interruptEnable == enEPCFBoolean_True)
	{
		// Disable Interrupt
		NVIC_DisableIRQ(adcIrqNum[pAdcDevice->adcId]);

		((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADINTEN = channel;

		for(ind=0; ind<__ADC_MAX_CHANNEL; ind++)
		{
			if( (channel & (1<<ind)) == channel)
			{
				adcCallbackId[ind] = ind;
				break;
			}
		}
		if(adcCallbackArr[adcCallbackId[ind]] == 0)
			adcCallbackArr[adcCallbackId[ind]] = callback;

		NVIC_EnableIRQ(adcIrqNum[pAdcDevice->adcId]);
		return EPCF_STATUS_SUCCESS;
	}
	else
		return EPCF_STATUS_ERROR;
}

int8_t epcf_adc_nativeDetachCallback(EPCFAdcDevice_t* pAdcDevice, uint16_t channel)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	if(adcState == enEPCFAdcState_Running)
		return EPCF_STATUS_BUSY;
	if(channel>enEPCFAdcChannel_7)
		return EPCF_STATUS_INVALID_ARGS;

	uint8_t ind;

	for(ind=0; ind<__ADC_MAX_CHANNEL; ind++)
	{
		if( (channel & (1<<ind)) == channel)
			break;
	}
	adcCallbackArr[adcCallbackId[ind]] = 0;

	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_adc_nativeClose(EPCFAdcDevice_t* pAdcDevice)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;

    ((ADC_TypeDef*)(adcChannelAddr[pAdcDevice->adcId]))->ADCR = 0x00;
    POWER_OFF(pwrAdcCh[pAdcDevice->adcId]);

    adcState = enEPCFAdcState_Stopped;
    adcChInit[pAdcDevice->adcId]= enEPCFBoolean_False;
    return EPCF_STATUS_SUCCESS;
}

uint8_t epcf_adc_nativeGetDeviceCount()
{
	return adcDeviceCount;
}

EnEPCFAdcState_t epcf_adc_nativeGetState(EPCFAdcDevice_t* pAdcDevice)
{
	if(adcChInit[pAdcDevice->adcId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	
	return adcState;
}

void ADC_INT_HANDLER(void)
{
	uint32_t intState=0;
	intState = ((ADC_TypeDef*)(adcChannelAddr[adcDevice[0]->adcId]))->ADSTAT;

	if((intState & (1<<0)) != 0)	// ADC0
	{
		if(adcCallbackArr[0] != 0)
			adcCallbackArr[0]();
	}
	if((intState & (1<<1)) != 0)	// ADC1
	{
		if(adcCallbackArr[1] != 0)
			adcCallbackArr[1]();
	}
	if((intState & (1<<2)) != 0)	// ADC2
	{
		if(adcCallbackArr[2] != 0)
			adcCallbackArr[2]();
	}
	if((intState & (1<<3)) != 0)	// ADC3
	{
		if(adcCallbackArr[3] != 0)
			adcCallbackArr[3]();
	}
	if((intState & (1<<4)) != 0)	// ADC4
	{
		if(adcCallbackArr[4] != 0)
			adcCallbackArr[4]();
	}
	if((intState & (1<<5)) != 0)	// ADC5
	{
		if(adcCallbackArr[5] != 0)
			adcCallbackArr[5]();
	}
	if((intState & (1<<6)) != 0)	// ADC6
	{
		if(adcCallbackArr[6] != 0)
			adcCallbackArr[6]();
	}
	if((intState & (1<<7)) != 0)	// ADC7
	{
		if(adcCallbackArr[7] != 0)
			adcCallbackArr[7]();
	}
}



