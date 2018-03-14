
#include "pcf.h"
#include <stdlib.h>

#define __EPCF_PRIVATE_PWM_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,pwm/,pwm_hidden.h)
#include  __EPCF_PRIVATE_PWM_H_INCLUDE
#undef __EPCF_PRIVATE_PWM_H_INCLUDE

#define __PWM_MAX_DEVICE      1
#define __PWM_MAX_CALLBACK    6

// Lookup tables.
static uint32_t pwmIrqNum[__PWM_MAX_DEVICE]           = {IRQ_NUM(PWM_CH)};
static uint32_t pwrPwmCh[__PWM_MAX_DEVICE]       = {PWR_UART_CH(PWM_CH)};
static uint32_t pdivClkPwmCh[__PWM_MAX_DEVICE]  = {PCLK_DIV(PWM_CH)};
static uint32_t pwmChannelAddr[__PWM_MAX_DEVICE] = {PWM1_BASE};

/*
 * Below variable pwmAltFunction
 * Row 1 -> Port 1
 * Row 2 -> Port 2
 * Row 3 -> Port 3
 */
static const uint8_t pwmAltFunction[3][32] =
{
 //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0}
};
// Lookup tables ends

// Static Variable Declaration
static uint32_t  pwmDeviceCount = __PWM_MAX_DEVICE;
static EPCFPwmDevice_t* pwmDevice[__PWM_MAX_DEVICE] = {0};
static EnEPCFBoolean_t pwmChInit[__PWM_MAX_DEVICE] = {0};
static epcfCallback_fp pwmCallbackArr[__PWM_MAX_CALLBACK];
static EnEPCFPwmState_t pwmState = enEPCFPwmState_Stopped;
static uint32_t pwmPeriodCount=0;

// Static Function Declaration
static int8_t __epcfPwmInit(EPCFPwmDevice_t* pPwmDevice, EPCFPwmCfg_t* pConfig);
static int8_t __epcfPwmGetPrescaler(EPCFTime_t resolution, uint8_t *pclkDiv, uint32_t *prescaler);

// Function Defination
int8_t epcf_pwm_nativeInit(EPCFPwmDevice_t* pPwmDevice, EPCFPwmCfg_t* pConfig)
{
    int8_t status = EPCF_STATUS_SUCCESS;
    uint8_t ind, pwmOutputChannel;

    // Hardware configuration
    pwmOutputChannel = ((EPCFPwmLpc1768Cfg_t*)(pConfig->hardwareCfg))->noOfPwmChannel;
    EPCFPinCfg_t pPwmOutputPinCfg[pwmOutputChannel];
    EPCFPortPin_t *pPwmOutputPortPinCfg;

    pPwmDevice->pwmId = pConfig->pwmId;
    pPwmDevice->pwmChannelAddr = (PWM_TypeDef*)pwmChannelAddr[pPwmDevice->pwmId];
    pPwmDevice->pwmWidth = pConfig->pwmWidth;
    pPwmDevice->resolution = pConfig->resolution;
    pPwmDevice->interruptEnable = pConfig->interruptEnable;

    pwmDevice[pConfig->pwmId] = pPwmDevice;

    // Hardware configuration
    pPwmOutputPortPinCfg = ((EPCFPwmLpc1768Cfg_t*)(pConfig->hardwareCfg))->pwmOutputPin;

    for(ind=0; ind<pwmOutputChannel; ind++)
    {
        pPwmOutputPinCfg[ind].direction    = 1; // enEPCFGpioDirOutput
        pPwmOutputPinCfg[ind].mode         = 0; // enEPCFGpioPinModePullUp
        pPwmOutputPinCfg[ind].openDrain    = 0; // open Drain disable
        pPwmOutputPinCfg[ind].portPin.port = pPwmOutputPortPinCfg[ind].port;
        pPwmOutputPinCfg[ind].portPin.pin  = pPwmOutputPortPinCfg[ind].pin;

        pPwmOutputPinCfg[ind].altFunction = pwmAltFunction[(pPwmOutputPinCfg[ind].portPin.port)-1][pPwmOutputPinCfg[ind].portPin.pin];

            status = epcfPinInit(&pPwmOutputPinCfg[ind]);
            if(status != EPCF_STATUS_SUCCESS)
              return EPCF_STATUS_ERROR;
    }

    status = __epcfPwmInit(pPwmDevice, pConfig);
    if(status != EPCF_STATUS_SUCCESS)
        return EPCF_STATUS_ERROR;

    pwmDeviceCount--;
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_pwm_nativeStart(EPCFPwmDevice_t* pPwmDevice)
{
    if(pwmChInit[pPwmDevice->pwmId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    // Disable Interrupt
    NVIC_DisableIRQ(pwmIrqNum[pPwmDevice->pwmId]);

    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->TCR = 0x09; // enable pwm & TC
    // Enable Interrupt
    if(pPwmDevice->interruptEnable == enEPCFBoolean_True)
        NVIC_EnableIRQ(pwmIrqNum[pPwmDevice->pwmId]);

    pwmState = enEPCFPwmState_Running;   // pwm is running

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_pwm_nativeStop(EPCFPwmDevice_t* pPwmDevice)
{
    if(pwmChInit[pPwmDevice->pwmId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    // Disable Interrupt
    NVIC_DisableIRQ(pwmIrqNum[pPwmDevice->pwmId]);

    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->TCR = 0x02; // disable pwm & reset TC

    pwmState = enEPCFPwmState_Stopped;  // pwm is stopped

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_pwm_nativeAttachCallback(EPCFPwmDevice_t* pPwmDevice,EnEPCFPwmChannel_t channel,EnEPCFPwmInterruptSource_t interruptSource,epcfCallback_fp callback)
{
    if(pwmState != enEPCFPwmState_Stopped)
        return EPCF_STATUS_BUSY;
    if( (channel < enEPCFPwmChannel_2)||(channel == enEPCFPwmChannel_1)||(channel == enEPCFPwmChannel_3)||(channel == enEPCFPwmChannel_5)||(channel > enEPCFPwmChannel_6) )
        return EPCF_STATUS_INVALID_ARGS;

    int8_t callbackId=0;


    if( pPwmDevice->interruptEnable == enEPCFBoolean_True)
    {
        if(interruptSource == enEPCFPwmPulse_Start)
        {
            switch(channel){
            case enEPCFPwmChannel_2:
                if(pwmCallbackArr[1] == 0)
                {
                    // MR1
                    pwmCallbackArr[1] = callback;
                    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MCR |= (1<<3);  // enable interrupt
                    return (callbackId = 1);
                }
                else
                    return EPCF_STATUS_ALREADY_CONFIGURED;
                break;
            case enEPCFPwmChannel_4:
                if(pwmCallbackArr[3] == 0)
                {
                    // MR3
                    pwmCallbackArr[3] = callback;
                    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MCR |= (1<<9);  // enable interrupt
                    return (callbackId = 3);
                }
                else
                    return EPCF_STATUS_ALREADY_CONFIGURED;
                break;
            case enEPCFPwmChannel_6:
                if(pwmCallbackArr[5] == 0)
                {
                    // MR5
                    pwmCallbackArr[5] = callback;
                    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MCR |= (1<<15); // enable interrupt
                    return (callbackId = 5);
                }
                else
                    return EPCF_STATUS_ALREADY_CONFIGURED;
                break;
            default:
                return EPCF_STATUS_INVALID_ARGS;
            }
        }
        else
        {
            switch(channel){
            case enEPCFPwmChannel_2:
                if(pwmCallbackArr[2] == 0)
                {
                    // MR2
                    pwmCallbackArr[2] = callback;
                    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MCR |= (1<<6);  // enable interrupt
                    return (callbackId = 2);
                }
                else
                    return EPCF_STATUS_ALREADY_CONFIGURED;
                break;
            case enEPCFPwmChannel_4:
                if(pwmCallbackArr[4] == 0)
                {
                    // MR4
                    pwmCallbackArr[4] = callback;
                    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MCR |= (1<<12); // enable interrupt
                    return (callbackId = 4);
                }
                else
                    return EPCF_STATUS_ALREADY_CONFIGURED;
                break;
            case enEPCFPwmChannel_6:
                if(pwmCallbackArr[6] == 0)
                {
                    // MR6
                    pwmCallbackArr[6] = callback;
                    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MCR |= (1<<18); // enable interrupt
                    return (callbackId = 6);
                }
                else
                    return EPCF_STATUS_ALREADY_CONFIGURED;
                break;
            default:
                return EPCF_STATUS_INVALID_ARGS;
            }
        }
    }

    return EPCF_STATUS_ERROR;
}

int8_t epcf_pwm_nativeDetachCallback(EPCFPwmDevice_t* pPwmDevice,uint8_t callbackId)
{
    if(pwmState != enEPCFPwmState_Stopped)
        return EPCF_STATUS_BUSY;

    pwmCallbackArr[callbackId] = 0;

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_pwm_nativeSetPeriod(EPCFPwmDevice_t* pPwmDevice,EPCFTime_t period)
{
    if(pwmChInit[pPwmDevice->pwmId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    float periodTimeMilliSec=0,resTimeMilliSec=0;

    // converting period time value into milliseconds
    switch(period.unit){
    case enEPCFTimeUnit_ns:
        periodTimeMilliSec = ((float)(period.count)/1000000);
        break;
    case enEPCFTimeUnit_us:
        periodTimeMilliSec = ((float)(period.count)/1000);
        break;
    case enEPCFTimeUnit_ms:
        periodTimeMilliSec = (float)(period.count);
        break;
    case enEPCFTimeUnit_s:
        periodTimeMilliSec = ((float)(period.count)*1000);
        break;
    default:
        return EPCF_STATUS_INVALID_ARGS;
    }
    // converting resolution time value into milliseconds
    switch (pPwmDevice->resolution.unit){
    case enEPCFTimeUnit_ns:
        resTimeMilliSec = ((float)(pPwmDevice->resolution.count)/1000000);
        break;
    case enEPCFTimeUnit_us:
        resTimeMilliSec = ((float)(pPwmDevice->resolution.count)/1000);
        break;
    case enEPCFTimeUnit_ms:
        resTimeMilliSec = (float)(pPwmDevice->resolution.count);
        break;
    case enEPCFTimeUnit_s:
        resTimeMilliSec = ((float)(pPwmDevice->resolution.count)*1000);
        break;
    default:
        return EPCF_STATUS_INVALID_ARGS;
    }

    pwmPeriodCount = ((uint32_t)(periodTimeMilliSec/resTimeMilliSec))-1;
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR0 = pwmPeriodCount;
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->LER = (1<<0);   // Enable latch for MR0
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MCR |= (1<<1);  // Reset on match

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_pwm_nativeSetDutyCycle(EPCFPwmDevice_t* pPwmDevice,EnEPCFPwmChannel_t channel,uint8_t dutyCycle,EnEPCFPwmOutputSignal_t signal)
{
    if(pwmChInit[pPwmDevice->pwmId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;
    if( (channel < enEPCFPwmChannel_2)||(channel == enEPCFPwmChannel_1)||(channel == enEPCFPwmChannel_3)||(channel == enEPCFPwmChannel_5)||(channel > enEPCFPwmChannel_6) )
        return EPCF_STATUS_INVALID_ARGS;

    uint32_t pwmPulseWidthCount=0;

    pwmPulseWidthCount = (dutyCycle * pwmPeriodCount) / 100;


    switch (channel){
    case enEPCFPwmChannel_2:
        // rise at MR1 and fall at MR2
        if(signal == enEPCFPwmOutputSignal_Normal)
        {
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR1 = 1;
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR2 = pwmPulseWidthCount;
        }
        else
        {
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR1 = pwmPulseWidthCount;
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR2 = pwmPeriodCount-1;
        }
        ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->PCR = (1<<2)|(1<<10);   // enable double edge, output
        ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->LER = (1<<1)|(1<<2);    // Enable Latch
        break;
    case enEPCFPwmChannel_4:
        // rise at MR3 and fall at MR4
        if(signal == enEPCFPwmOutputSignal_Normal)
        {
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR3 = 1;
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR4 = pwmPulseWidthCount;
        }
        else
        {
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR3 = pwmPulseWidthCount;
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR4 = pwmPeriodCount-1;
        }
        ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->PCR = (1<<4)|(1<<12);   // enable double edge, output
        ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->LER = (1<<3)|(1<<4);
        break;
    case enEPCFPwmChannel_6:
        // rise at MR5 and fall at MR6
        if(signal == enEPCFPwmOutputSignal_Normal)
        {
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR5 = 1;
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR6 = pwmPulseWidthCount;
        }
        else
        {
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR5 = pwmPulseWidthCount;
            ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MR6 = pwmPeriodCount-1;
        }
        ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->PCR = (1<<6)|(1<<14);   // enable double edge, output
        ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->LER = (1<<5)|(1<<6);
        break;
    default:
        return EPCF_STATUS_INVALID_ARGS;
    }
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_pwm_nativeClose(EPCFPwmDevice_t* pPwmDevice)
{
    if(pwmChInit[pPwmDevice->pwmId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    // power off PWM peripheral
    POWER_OFF(pwrPwmCh[pPwmDevice->pwmId]);
    pPwmDevice = NULL;
    return EPCF_STATUS_SUCCESS;
}

uint8_t epcf_pwm_nativeGetDeviceCount()
{
    return pwmDeviceCount;
}

EnEPCFPwmState_t epcf_pwm_nativeGetState(EPCFPwmDevice_t* pPwmDevice)
{
	if(pwmChInit[pPwmDevice->pwmId] != enEPCFBoolean_True)
		return EPCF_STATUS_ERROR;
	
	return pwmState;
}

void PWM_INT_HANDLER(void)
{
    uint32_t intState;
    intState = ((PWM_TypeDef*)pwmDevice[0]->pwmChannelAddr)->IR;

    if((intState & (1<<1)) != 0)    // pwm1
    {
        if(pwmCallbackArr[1] != 0)
            pwmCallbackArr[1]();
    }
    if((intState & (1<<2)) != 0)    // pwm2
    {
        if(pwmCallbackArr[2] != 0)
            pwmCallbackArr[2]();
    }
    if((intState & (1<<3)) != 0)    // pwm3
    {
        if(pwmCallbackArr[3] != 0)
            pwmCallbackArr[3]();
    }
    if((intState & (1<<4)) != 0)    // pwm4
    {
        if(pwmCallbackArr[4] != 0)
            pwmCallbackArr[4]();
    }
    if((intState & (1<<5)) != 0)    // pwm5
    {
        if(pwmCallbackArr[5] != 0)
            pwmCallbackArr[5]();
    }
    if((intState & (1<<6)) != 0)    // pwm6
    {
        if(pwmCallbackArr[6] != 0)
            pwmCallbackArr[6]();
    }
    ((PWM_TypeDef*)pwmDevice[0]->pwmChannelAddr)->IR |= 0xFF;
}


static int8_t __epcfPwmInit(EPCFPwmDevice_t* pPwmDevice, EPCFPwmCfg_t* pConfig)
{
    int8_t status;
    uint32_t prescaler = 0;
    uint8_t pclkDivider = 0;
    // power on PWM peripheral
    POWER_ON(pwrPwmCh[pConfig->pwmId]);

    status = __epcfPwmGetPrescaler(pConfig->resolution, &pclkDivider, &prescaler);
    if(status != 0)
        return EPCF_STATUS_ERROR;
    // set peripheral clock divider
    epcfNativeSysSetPclkDiv(NULL, pdivClkPwmCh[pConfig->pwmId], pclkDivider);
    // pwm initialization
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->PR = prescaler;
    // Reset all registers
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->IR = 0xFF;
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->MCR = 0x00;
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->CCR = 0x00;
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->PCR = 0x00;
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->LER = 0x00;

    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->TCR = 0x02; //reset TC
    ((PWM_TypeDef*)pPwmDevice->pwmChannelAddr)->CTCR = 0;   // TC increments on value of PR


    pwmChInit[pConfig->pwmId] = enEPCFBoolean_True;
    return EPCF_STATUS_SUCCESS;
}

static int8_t __epcfPwmGetPrescaler(EPCFTime_t resolution, uint8_t *pclkDiv, uint32_t *prescaler)
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
        for(presCalVal=1; presCalVal<65536; presCalVal++)
        {
            if( (uint64_t)((pclkDivArr[pclkDivInd] * presCalVal) / cpuClk) == resolution.count)
            {
                *pclkDiv = pclkDivArr[pclkDivInd];
                *prescaler = (presCalVal-1);
                return EPCF_STATUS_SUCCESS;
            }
        }
    }
    return EPCF_STATUS_ERROR;
}


