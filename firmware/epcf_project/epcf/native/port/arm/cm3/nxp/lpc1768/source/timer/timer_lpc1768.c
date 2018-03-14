
#include "pcf.h"

#define __EPCF_PRIVATE_TIMER_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,timer/,timer_hidden.h)
#include  __EPCF_PRIVATE_TIMER_H_INCLUDE
#undef __EPCF_PRIVATE_TIMER_H_INCLUDE

#define __TIMER_MAX_DEVICE				4
#define __TIMER_MAX_CALLBACKS			6
#define __TIMER_INTERRUPT_SOURCE		6

// Lookup tables.
static uint32_t timerIrqNum[__TIMER_MAX_DEVICE]           = {IRQ_NUM(TIMER0_CH),IRQ_NUM(TIMER1_CH),IRQ_NUM(TIMER2_CH),IRQ_NUM(TIMER3_CH)};
static uint32_t pwrTimerCh[__TIMER_MAX_DEVICE]       = {PWR_TIMER_CH(TIMER0_CH),PWR_TIMER_CH(TIMER1_CH), PWR_TIMER_CH(TIMER2_CH), PWR_TIMER_CH(TIMER3_CH)};
static uint32_t timerChannelAddr[__TIMER_MAX_DEVICE] = {TIM0_BASE, TIM1_BASE, TIM2_BASE, TIM3_BASE};
static uint32_t pdivClkTimerCh[__TIMER_MAX_DEVICE]  = {PCLK_DIV(TIMER0_CH),PCLK_DIV(TIMER1_CH), PCLK_DIV(TIMER2_CH), PCLK_DIV(TIMER3_CH)};

/*
 * Below variable timerMatchPinAltFunction
 * Row 1 -> Port 0
 * Row 2 -> Port 1
 * Row 3 -> Port 2
 * Row 4 -> Port 3
 * Row 5 -> Port 4
 */
const uint8_t timerMatchPinAltFunction[5][32] =
{
 //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
  {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 3, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0}
};
/*
 * Below variable timerCapturePinAltFunction
 * Row 1 -> Port 0
 * Row 2 -> Port 1
 */
const uint8_t timerCapturePinAltFunction[2][32] =
{
 //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
  {0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 2, 0, 0}
  };
// Lookup tables ends

// Static Variable Declaration
static uint32_t  timerDeviceCount = __TIMER_MAX_DEVICE;
static EPCFTimerDevice_t* timerDevice[__TIMER_MAX_DEVICE] = {0};
static volatile epcfCallback_fp  timerCallbackArr[__TIMER_MAX_DEVICE][__TIMER_INTERRUPT_SOURCE];
static EnEPCFTimerState_t timerState = enEPCFTimerState_Stopped;
static EnEPCFBoolean_t timerChInit[4] = {0};        // initialize flag for the channel

// Static Function Declaration
static int8_t __epcfTimerInit(EPCFTimerDevice_t* pTimerDevice, EPCFTimerCfg_t *pConfig);
static int8_t __epcfTimerGetPrescaler(EPCFTime_t resolution, uint8_t *pclkDiv, uint32_t *prescaler);

// Function Definition

int8_t epcf_timer_nativeInit(EPCFTimerDevice_t* pTimerDevice, EPCFTimerCfg_t* pConfig)
{
	int8_t status = 0;
	uint8_t ind, extMatPin, capturePin;

	// Hardware configuration
	extMatPin = ((EPCFTimerLpc1768Cfg_t*)(pConfig->hardwareCfg))->noOfExtMatPin;
	capturePin = ((EPCFTimerLpc1768Cfg_t*)(pConfig->hardwareCfg))->noOfCapturePin;

	EPCFPinCfg_t pExtMatPinCfg[extMatPin], pCapPinCfg[capturePin];
	EPCFPortPin_t *pExtMatPortPinCfg, *pCapPortPinCfg;

	pTimerDevice->timerId = pConfig->timerId;
	pTimerDevice->timerChannelAddr = (TIM_TypeDef*)timerChannelAddr[pConfig->timerId];
	pTimerDevice->resolution = pConfig->resolution;
	pTimerDevice->timerWidth = pConfig->timerWidth;
	pTimerDevice->mode = pConfig->mode;
	pTimerDevice->interruptEnable = pConfig->interruptEnable;

	timerDevice[pConfig->timerId] = pTimerDevice;

	// Hardware configuration
	pCapPortPinCfg = ((EPCFTimerLpc1768Cfg_t*)(pConfig->hardwareCfg))->timerCapPin;
	pExtMatPortPinCfg = ((EPCFTimerLpc1768Cfg_t*)(pConfig->hardwareCfg))->timerExtMatPin;

	for(ind=0; ind<capturePin; ind++)
	{
			pCapPinCfg[ind].direction    = 0; // enEPCFGpioDirInput
			pCapPinCfg[ind].mode         = 0; // enEPCFGpioPinModePullUp
			pCapPinCfg[ind].openDrain    = 0; // open Drain disable
			pCapPinCfg[ind].portPin.port = pCapPortPinCfg[ind].port;
			pCapPinCfg[ind].portPin.pin  = pCapPortPinCfg[ind].pin;

			pCapPinCfg[ind].altFunction = timerCapturePinAltFunction[(pCapPinCfg[ind].portPin.port)][pCapPinCfg[ind].portPin.pin];

			status = epcfPinInit(&pCapPinCfg[ind]);
			if(status != EPCF_STATUS_SUCCESS)
			  return -1;
	}

	for(ind=0; ind<extMatPin; ind++)
	{
			pExtMatPinCfg[ind].direction    = 1; // enEPCFGpioDirOutput
			pExtMatPinCfg[ind].mode         = 0; // enEPCFGpioPinModePullUp
			pExtMatPinCfg[ind].openDrain    = 0; // open Drain disable
			pExtMatPinCfg[ind].portPin.port = pExtMatPortPinCfg[ind].port;
			pExtMatPinCfg[ind].portPin.pin  = pExtMatPortPinCfg[ind].pin;

			pExtMatPinCfg[ind].altFunction = timerMatchPinAltFunction[(pExtMatPinCfg[ind].portPin.port)][pExtMatPinCfg[ind].portPin.pin];

			status = epcfPinInit(&pExtMatPinCfg[ind]);
			if(status != EPCF_STATUS_SUCCESS)
			  return -1;
	}

	status = __epcfTimerInit(pTimerDevice, pConfig);
	if(status != 0)
		return EPCF_STATUS_ERROR;

	timerDeviceCount--;
	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_timer_nativeStart(EPCFTimerDevice_t* pTimerDevice)
{
	if(timerChInit[pTimerDevice->timerId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;

	// Disable Interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);

	((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->TCR = 0x01;
	// Enable Interrupt
	if(pTimerDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(timerIrqNum[pTimerDevice->timerId]);

	timerState = enEPCFTimerState_Running;

	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_timer_nativeStop(EPCFTimerDevice_t* pTimerDevice)
{
	if(timerChInit[pTimerDevice->timerId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;

	// Disable interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);
	((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->TCR = 0x00;

	timerState = enEPCFTimerState_Stopped;

	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_timer_nativeReset(EPCFTimerDevice_t* pTimerDevice)
{
	if(timerChInit[pTimerDevice->timerId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;

	// Disable interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);

	((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->TCR = 0x02;
	// Enable interrupt
	if(pTimerDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(timerIrqNum[pTimerDevice->timerId]);

	return EPCF_STATUS_SUCCESS;
}

EnEPCFTimerState_t epcf_timer_nativeGetState(EPCFTimerDevice_t* pTimerDevice)
{
	if(timerChInit[pTimerDevice->timerId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;

	return timerState;
}

int8_t epcf_timer_nativeGetTime(EPCFTimerDevice_t* pTimerDevice,EPCFTime_t* time)
{
	uint32_t timerCount=0;
	float resTimeMicroSec=0;

	// Disable Interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);

	timerCount = ((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->TC;
	// converting resolution time value into micro seconds
	switch (pTimerDevice->resolution.unit){
	case enEPCFTimeUnit_ns:
		resTimeMicroSec = ((float)(pTimerDevice->resolution.count)/1000);
		break;
	case enEPCFTimeUnit_us:
		resTimeMicroSec = ((float)(pTimerDevice->resolution.count));
		break;
	case enEPCFTimeUnit_ms:
		resTimeMicroSec = ((float)(pTimerDevice->resolution.count)*1000);
		break;
	case enEPCFTimeUnit_s:
		resTimeMicroSec = ((float)(pTimerDevice->resolution.count)*1000000);
		break;
	default:
		return EPCF_STATUS_INVALID_ARGS;
	}
	time->count = (uint32_t)((timerCount+1) * resTimeMicroSec);
	time->unit = enEPCFTimeUnit_us;
	// Enable Interrupt
	if(pTimerDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(timerIrqNum[pTimerDevice->timerId]);

	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_timer_nativeGetCounterValue(EPCFTimerDevice_t* pTimerDevice, uint32_t* count)
{
	if(timerChInit[pTimerDevice->timerId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;

	// Disable Interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);

	*count = ((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->TC;
	// Enable Interrupt
	if(pTimerDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(timerIrqNum[pTimerDevice->timerId]);
	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_timer_nativeSetCounter(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerInputPolarity_t inputPolarity)
{
	if(timerChInit[pTimerDevice->timerId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	if((inputPolarity>enEPCFTimer_BothEdge) && (inputPolarity<enEPCFTimer_RisingEdge))
		return EPCF_STATUS_INVALID_ARGS;
	if(channel>enEPCFTimerChannel_1)
		return EPCF_STATUS_INVALID_ARGS;

	// Disable Interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);

	if(pTimerDevice->mode != enEPCFTimerMode_Counter)
		return EPCF_STATUS_NOT_CONFIGURED;
	else
	{
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CTCR = 0x00;
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CCR = 0x00;
		// select counter on rising/falling/both edges
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CTCR |= (0x03 & inputPolarity);
		// select capture pin for counter
		if(channel == enEPCFTimerChannel_0)
			((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CTCR |= (channel<<2);
		else
		{
			((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CTCR |= (channel<<3);
		}
		return EPCF_STATUS_SUCCESS;
	}
}

int8_t epcf_timer_nativeAttachCallback(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerInterruptSource_t interruptSource,epcfCallback_fp callback)
{
	if( (interruptSource== enEPCFTimer_Overflow) || (interruptSource== enEPCFTimerCompareMatchChannel_4) || (interruptSource== enEPCFTimerCompareMatchChannel_5) || \
			(interruptSource== enEPCFTimerInputCaptureChannel_2) || (interruptSource== enEPCFTimerInputCaptureChannel_3) || \
			(interruptSource== enEPCFTimerInputCaptureChannel_4) || (interruptSource== enEPCFTimerInputCaptureChannel_5))
		return EPCF_STATUS_INVALID_ARGS;

	if(timerState == enEPCFTimerState_Running)
		return EPCF_STATUS_BUSY;

	// Disable Interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);

	if(pTimerDevice->interruptEnable != enEPCFBoolean_False)
	{
		switch(interruptSource){
			case enEPCFTimerCompareMatchChannel_0:
				((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MCR |= 1<<0;
				break;
			case enEPCFTimerCompareMatchChannel_1:
				((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MCR |= 1<<3;
				break;
			case enEPCFTimerCompareMatchChannel_2:
				((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MCR |= 1<<6;
				break;
			case enEPCFTimerCompareMatchChannel_3:
				((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MCR |= 1<<9;
				break;
			case enEPCFTimerInputCaptureChannel_0:
				((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CCR |= 1<<2;
				break;
			case enEPCFTimerInputCaptureChannel_1:
				((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CCR |= 1<<5;
				break;
			default:
				return EPCF_STATUS_INVALID_ARGS;
		}

		if(timerCallbackArr[pTimerDevice->timerId][interruptSource] == 0)
		{
			timerCallbackArr[pTimerDevice->timerId][interruptSource] = callback;
		}
		return EPCF_STATUS_SUCCESS;
	}
	else
		return EPCF_STATUS_ERROR;
}

int8_t epcf_timer_nativeDetachCallback(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerInterruptSource_t interruptSource)
{
	if(timerState == enEPCFTimerState_Running)
		return EPCF_STATUS_BUSY;

	timerCallbackArr[pTimerDevice->timerId][interruptSource] = 0;
	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_timer_nativeSetCompareTime(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerCompareAction_t compareAction,EnEPCFTimerPinAction pinAction,EPCFTime_t time)
{
	uint32_t matchCount=0;
	float resTimeMilliSec=0, compareTimeMilliSec=0;
	if(timerChInit[pTimerDevice->timerId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	if(pTimerDevice->mode != enEPCFTimerMode_Timer)
		return EPCF_STATUS_INVALID_ARGS;
	if(channel>enEPCFTimerChannel_3)
		return EPCF_STATUS_INVALID_ARGS;

	if(timerState == enEPCFTimerState_Running)
		return EPCF_STATUS_BUSY;

	// Disable Interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);

	// converting compare time value into milli seconds
	switch(time.unit){
	case enEPCFTimeUnit_ns:
		compareTimeMilliSec = ((float)(time.count)/1000000);
		break;
	case enEPCFTimeUnit_us:
		compareTimeMilliSec = ((float)(time.count)/1000);
		break;
	case enEPCFTimeUnit_ms:
		compareTimeMilliSec = (float)(time.count);
		break;
	case enEPCFTimeUnit_s:
		compareTimeMilliSec = ((float)(time.count)*1000);
		break;
	default:
		return EPCF_STATUS_INVALID_ARGS;
	}
	// converting resolution time value into milli seconds
	switch (pTimerDevice->resolution.unit){
	case enEPCFTimeUnit_ns:
		resTimeMilliSec = ((float)(pTimerDevice->resolution.count)/1000000);
		break;
	case enEPCFTimeUnit_us:
		resTimeMilliSec = ((float)(pTimerDevice->resolution.count)/1000);
		break;
	case enEPCFTimeUnit_ms:
		resTimeMilliSec = (float)(pTimerDevice->resolution.count);
		break;
	case enEPCFTimeUnit_s:
		resTimeMilliSec = ((float)(pTimerDevice->resolution.count)*1000);
		break;
	default:
		return EPCF_STATUS_INVALID_ARGS;
	}

	matchCount = (uint32_t)(compareTimeMilliSec/resTimeMilliSec);

	switch(channel){
	case enEPCFTimerChannel_0:
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MR0 = matchCount;
		break;
	case enEPCFTimerChannel_1:
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MR1 = matchCount;
		break;
	case enEPCFTimerChannel_2:
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MR2 = matchCount;
		break;
	case enEPCFTimerChannel_3:
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MR3 = matchCount;
		break;
	default:
		return EPCF_STATUS_INVALID_ARGS;
	}

	if(compareAction != enEPCFTimerCompareAction_None)
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MCR |= ((compareAction & 0x03) << ((channel * 3)+1));
	if(pinAction != enEPCFTimerPinAction_None)
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->EMR |= ( (pinAction & 0x03) << ((channel * 2) + 4));

	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_timer_nativeSetInputCapture(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerInputPolarity_t inputPolarity)
{
	if(timerChInit[pTimerDevice->timerId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;
	if(channel>enEPCFTimerChannel_1)
		return EPCF_STATUS_INVALID_ARGS;

	if(timerState == enEPCFTimerState_Running)
		return EPCF_STATUS_BUSY;

	// Disable Interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);

	if(pTimerDevice->mode != enEPCFTimerMode_Timer)
	{
		if(channel == enEPCFTimerChannel_0)
			return EPCF_STATUS_NOT_SUPPORTED;

		// for conter mode, 3 bits of this register should be 000
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CCR = 0x00;
		((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CCR |= (inputPolarity & 0x03)<<3;
		return EPCF_STATUS_SUCCESS;
	}
	else
	{
		switch(channel){
		case enEPCFTimerChannel_0:
			((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CCR |= inputPolarity & 0x03;
			break;
		case enEPCFTimerChannel_1:
			((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CCR |= (inputPolarity & 0x03)<<3;
			break;
		default:
			return EPCF_STATUS_INVALID_ARGS;
		}
		return EPCF_STATUS_SUCCESS;
	}
}

int8_t epcf_timer_nativeGetInputCaptureTime(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EPCFTime_t* time)
{
	uint32_t capCount=0;
	float resTimeMilliSec=0;
	if(timerChInit[pTimerDevice->timerId] != enEPCFBoolean_True)
		return EPCF_STATUS_NOT_CONFIGURED;

	// Disable Interrupt
	NVIC_DisableIRQ(timerIrqNum[pTimerDevice->timerId]);

	switch(channel){
	case enEPCFTimerChannel_0:
		capCount = ((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CR0;
		break;
	case enEPCFTimerChannel_1:
		capCount = ((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CR1;
		break;
	default:
		return EPCF_STATUS_INVALID_ARGS;
	}
	// converting resolution time value into milli seconds
	switch (pTimerDevice->resolution.unit){
	case enEPCFTimeUnit_ns:
		resTimeMilliSec = ((float)(pTimerDevice->resolution.count)/1000000);
		break;
	case enEPCFTimeUnit_us:
		resTimeMilliSec = ((float)(pTimerDevice->resolution.count)/1000);
		break;
	case enEPCFTimeUnit_ms:
		resTimeMilliSec = (float)(pTimerDevice->resolution.count);
		break;
	case enEPCFTimeUnit_s:
		resTimeMilliSec = ((float)(pTimerDevice->resolution.count)*1000);
		break;
	default:
		return EPCF_STATUS_INVALID_ARGS;
	}
	time->count = (uint32_t)((capCount+1) * resTimeMilliSec);
	time->unit = enEPCFTimeUnit_ms;

	// Enable Interrupt
	if(pTimerDevice->interruptEnable == enEPCFBoolean_True)
		NVIC_EnableIRQ(timerIrqNum[pTimerDevice->timerId]);

	return EPCF_STATUS_SUCCESS;
}

uint8_t epcf_timer_nativeGetDeviceCount()
{
	return timerDeviceCount;
}

int8_t epcf_timer_nativeClose(EPCFTimerDevice_t* pTimerDevice)
{
    timerChInit[pTimerDevice->timerId] = enEPCFBoolean_False;
    // power off TIMER peripheral
    POWER_OFF(pwrTimerCh[pTimerDevice->timerId]);
    pTimerDevice = NULL;
    return EPCF_STATUS_SUCCESS;
}

//******************* Static Function Definitions ********************//
static int8_t __epcfTimerGetPrescaler(EPCFTime_t resolution, uint8_t *pclkDiv, uint32_t *prescaler)
{
	uint32_t presCalVal=0;
	float cpuClk=0;
	uint8_t pclkDivInd=0;
	uint8_t pclkDivArr[4] = {1,2,4,8};

	cpuClk = epcfNativeSysGetCpuClock(NULL);
	switch(resolution.unit){
	case enEPCFTimeUnit_ns:
		cpuClk = (cpuClk / 1000000000);
		break;
	case enEPCFTimeUnit_us:
		cpuClk = (cpuClk / 1000000);
		break;
	case enEPCFTimeUnit_ms:
		cpuClk = (cpuClk / 1000);
		break;
	case enEPCFTimeUnit_s:
		cpuClk = cpuClk * 1;
		break;
	default:
		return EPCF_STATUS_INVALID_ARGS;
	}

	for(pclkDivInd=0; pclkDivInd<4; pclkDivInd++)
	{
		for(presCalVal=0; presCalVal<4294967296; presCalVal++)
		{
			if( (uint32_t)((pclkDivArr[pclkDivInd] * presCalVal) / cpuClk) == resolution.count)
			{
				*pclkDiv = pclkDivArr[pclkDivInd];
				*prescaler = (presCalVal-1);
				return EPCF_STATUS_SUCCESS;
			}
		}
	}
	return EPCF_STATUS_ERROR;
}

static int8_t __epcfTimerInit(EPCFTimerDevice_t* pTimerDevice, EPCFTimerCfg_t *pConfig)
{
	int8_t status;
	uint32_t prescaler = 0;
	uint8_t pclkDivider = 0;
    // power on Timer peripheral
    POWER_ON(pwrTimerCh[pConfig->timerId]);
    // Calculate pclk divider and prescaler value
    status = __epcfTimerGetPrescaler(pConfig->resolution, &pclkDivider, &prescaler);
    if(status != 0)
    	return EPCF_STATUS_ERROR;
    // set peripheral clock divider
    epcfNativeSysSetPclkDiv(NULL, pdivClkTimerCh[pConfig->timerId], pclkDivider);
	// set prescaler
    ((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->PR = prescaler;
    // select timer/counter
    if(pConfig->mode == enEPCFTimerMode_Timer)
    	((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->CTCR = enEPCFTimerMode_Timer;

    ((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->TCR = 0x02;
    ((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->IR = 0x3F;
    ((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->MCR = 0x0000;
    ((TIM_TypeDef*)(pTimerDevice->timerChannelAddr))->EMR = 0x0000;

    timerChInit[pTimerDevice->timerId]= enEPCFBoolean_True;
    return EPCF_STATUS_SUCCESS;
}
//****************** End of Static Function Definition ***************//

void TIMER0_INT_HANDLER(void)
{
	if( (((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR & 0x01) != 0)
	{
		if(timerCallbackArr[timerDevice[0]->timerId][1] != NULL)
			timerCallbackArr[timerDevice[0]->timerId][1]();
		((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR = (1<<0);
	}
	if( (((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR & 0x02) != 0)
	{
		if(timerCallbackArr[timerDevice[0]->timerId][2] != NULL)
			timerCallbackArr[timerDevice[0]->timerId][2]();
		((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR = (1<<1);
	}
	if( (((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR & 0x04) != 0)
	{
		if(timerCallbackArr[timerDevice[0]->timerId][3] != NULL)
			timerCallbackArr[timerDevice[0]->timerId][3]();
		((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR = (1<<2);
	}
	if( (((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR & 0x08) != 0)
	{
		if(timerCallbackArr[timerDevice[0]->timerId][4] != NULL)
			timerCallbackArr[timerDevice[0]->timerId][4]();
		((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR = (1<<3);
	}
	if( (((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR & 0x10) != 0)
	{
		if(timerCallbackArr[timerDevice[0]->timerId][7] != NULL)
			timerCallbackArr[timerDevice[0]->timerId][7]();
		((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR = (1<<4);
	}
	if( (((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR & 0x20) != 0)
	{
		if(timerCallbackArr[timerDevice[0]->timerId][8] != NULL)
			timerCallbackArr[timerDevice[0]->timerId][8]();
		((TIM_TypeDef*)(timerDevice[0]->timerChannelAddr))->IR = (1<<5);
	}
}

void TIMER1_INT_HANDLER(void)
{
	if( (((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR & 0x01) != 0)
	{
		if(timerCallbackArr[timerDevice[1]->timerId][1] != NULL)
			timerCallbackArr[timerDevice[1]->timerId][1]();
		((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR = (1<<0);
	}
	if( (((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR & 0x02) != 0)
	{
		if(timerCallbackArr[timerDevice[1]->timerId][2] != NULL)
			timerCallbackArr[timerDevice[1]->timerId][2]();
		((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR = (1<<1);
	}
	if( (((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR & 0x04) != 0)
	{
		if(timerCallbackArr[timerDevice[1]->timerId][3] != NULL)
			timerCallbackArr[timerDevice[1]->timerId][3]();
		((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR = (1<<2);
	}
	if( (((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR & 0x08) != 0)
	{
		if(timerCallbackArr[timerDevice[1]->timerId][4] != NULL)
			timerCallbackArr[timerDevice[1]->timerId][4]();
		((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR = (1<<3);
	}
	if( (((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR & 0x10) != 0)
	{
		if(timerCallbackArr[timerDevice[1]->timerId][7] != NULL)
			timerCallbackArr[timerDevice[1]->timerId][7]();
		((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR = (1<<4);
	}
	if( (((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR & 0x20) != 0)
	{
		if(timerCallbackArr[timerDevice[1]->timerId][8] != NULL)
			timerCallbackArr[timerDevice[1]->timerId][8]();
		((TIM_TypeDef*)(timerDevice[1]->timerChannelAddr))->IR = (1<<5);
	}
}

void TIMER2_INT_HANDLER(void)
{
	if( (((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR & 0x01) != 0)
	{
		if(timerCallbackArr[timerDevice[2]->timerId][1] != NULL)
			timerCallbackArr[timerDevice[2]->timerId][1]();
		((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR = (1<<0);
	}
	if( (((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR & 0x02) != 0)
	{
		if(timerCallbackArr[timerDevice[2]->timerId][2] != NULL)
			timerCallbackArr[timerDevice[2]->timerId][2]();
		((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR = (1<<1);
	}
	if( (((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR & 0x04) != 0)
	{
		if(timerCallbackArr[timerDevice[2]->timerId][3] != NULL)
			timerCallbackArr[timerDevice[2]->timerId][3]();
		((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR = (1<<2);
	}
	if( (((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR & 0x08) != 0)
	{
		if(timerCallbackArr[timerDevice[2]->timerId][4] != NULL)
			timerCallbackArr[timerDevice[2]->timerId][4]();
		((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR = (1<<3);
	}
	if( (((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR & 0x10) != 0)
	{
		if(timerCallbackArr[timerDevice[2]->timerId][7] != NULL)
			timerCallbackArr[timerDevice[2]->timerId][7]();
		((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR = (1<<4);
	}
	if( (((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR & 0x20) != 0)
	{
		if(timerCallbackArr[timerDevice[2]->timerId][8] != NULL)
			timerCallbackArr[timerDevice[2]->timerId][8]();
		((TIM_TypeDef*)(timerDevice[2]->timerChannelAddr))->IR = (1<<5);
	}
}

void TIMER3_INT_HANDLER(void)
{
	if( (((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR & 0x01) != 0)
	{
		if(timerCallbackArr[timerDevice[3]->timerId][1] != NULL)
			timerCallbackArr[timerDevice[3]->timerId][1]();
		((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR = (1<<0);
	}
	if( (((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR & 0x02) != 0)
	{
		if(timerCallbackArr[timerDevice[3]->timerId][2] != NULL)
			timerCallbackArr[timerDevice[3]->timerId][2]();
		((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR = (1<<1);
	}
	if( (((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR & 0x04) != 0)
	{
		if(timerCallbackArr[timerDevice[3]->timerId][3] != NULL)
			timerCallbackArr[timerDevice[3]->timerId][3]();
		((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR = (1<<2);
	}
	if( (((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR & 0x08) != 0)
	{
		if(timerCallbackArr[timerDevice[3]->timerId][4] != NULL)
			timerCallbackArr[timerDevice[3]->timerId][4]();
		((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR = (1<<3);
	}
	if( (((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR & 0x10) != 0)
	{
		if(timerCallbackArr[timerDevice[3]->timerId][7] != NULL)
			timerCallbackArr[timerDevice[3]->timerId][7]();
		((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR = (1<<4);
	}
	if( (((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR & 0x20) != 0)
	{
		if(timerCallbackArr[timerDevice[3]->timerId][8] != NULL)
			timerCallbackArr[timerDevice[3]->timerId][8]();
		((TIM_TypeDef*)(timerDevice[3]->timerChannelAddr))->IR = (1<<5);
	}
}



