
#include "pcf.h"
#include "../include/epcf_time.h"
#include "../../peripheral/source/timer/timer_hidden.h"
#include "../../peripheral/include/timer/timer.h"
#include "../../native/port/arm/cm3/nxp/lpc1768/include/timer/timer_lpc1768.h"

#define __DEBUG_ENABLE      0

#if(__DEBUG_ENABLE == 1)
    #include "appConfig.h"

    uint8_t data1[200] = {0};
#endif

#define __OVERFLOW_UINT32       4294967295

static EPCFTimerDevice_t *pTimerDevice;
static EnEPCFBoolean_t timeInit = enEPCFBoolean_False;
static uint64_t timerWidth = 0;
static volatile uint32_t cycleUpdate=0;
static float resTimeMicroSec=0;
static float resTimeSec = 0;
static uint32_t tcOverFlowSec=0;
static  uint32_t tickCount=0;

// function to pass as callback
static void cycleUpdateFunc(void);

int8_t epcf_time_init(EPCFTimeCfg_t* pTimeConfig)
{
    uint32_t cpuClk = 0;
    EPCFTime_t compareTime;
    EPCFTimerCfg_t timerConfig;
    EPCFTimerLpc1768Cfg_t timerHWCfg;

    cpuClk = epcfNativeSysGetCpuClock(NULL);

    timerConfig.timerId = pTimeConfig->timerId;
    timerConfig.timerWidth = pTimeConfig->timerWidth;
    timerConfig.interruptEnable = enEPCFBoolean_True;
    timerConfig.mode = enEPCFTimerMode_Timer;
    timerConfig.resolution.count = (uint32_t)(1000000000/cpuClk);
    timerConfig.resolution.unit = enEPCFTimeUnit_ns;
    timerConfig.hardwareCfg = &timerHWCfg;
    ((EPCFTimerLpc1768Cfg_t*)(timerConfig.hardwareCfg))->noOfExtMatPin = 0;
    ((EPCFTimerLpc1768Cfg_t*)(timerConfig.hardwareCfg))->noOfCapturePin = 0;
    ((EPCFTimerLpc1768Cfg_t*)(timerConfig.hardwareCfg))->timerCapPin = NULL;
    ((EPCFTimerLpc1768Cfg_t*)(timerConfig.hardwareCfg))->timerExtMatPin = NULL;

    pTimerDevice = epcf_timer_createNative(&timerConfig);
    if(pTimerDevice == NULL)
        return EPCF_STATUS_NO_MEMORY;

    switch ( pTimerDevice->timerWidth){
    case enEPCFTimerWidth_8:
        timerWidth = ((uint64_t)1<<7);
        timerWidth = (timerWidth * 2);
        break;
    case enEPCFTimerWidth_16:
        timerWidth = ((uint64_t)1<<15);
        timerWidth = (timerWidth * 2);
        break;
    case enEPCFTimerWidth_32:
        timerWidth = ((uint64_t)1<<31);
        timerWidth = (timerWidth * 2);
        break;
    case enEPCFTimerWidth_64:
        break;
    default:
        return EPCF_STATUS_INVALID_ARGS;
    }

        // converting resolution time value into micro seconds
    switch ( pTimerDevice->resolution.unit){
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

    // time of one overflow in seconds
    resTimeSec = resTimeMicroSec/1000000;
    tcOverFlowSec = (timerWidth-1)*resTimeSec;

    compareTime.count = (uint32_t)( timerWidth * resTimeMicroSec );
    compareTime.unit = enEPCFTimeUnit_us;

    epcf_timer_setCompareTime(pTimerDevice,enEPCFTimerChannel_0,enEPCFTimerCompareAction_Reset,enEPCFTimerPinAction_None,compareTime);
    epcf_timer_attachCallback(pTimerDevice,enEPCFTimerCompareMatchChannel_0,cycleUpdateFunc);
    timeInit = enEPCFBoolean_True;
    epcf_timer_start(pTimerDevice);

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_getCpuTime(EPCFTimeStamp_t* time)
{
    if(timeInit != enEPCFBoolean_True)
        return EPCF_STATUS_NOT_CONFIGURED;

    EPCFTime_t getTime;
    EPCFTimeStamp_t getTimeStamp;
    float secondValue=0;

    epcf_timer_getTime(pTimerDevice,&getTime);
    //convert get time into nano seconds
    if( ((uint64_t)getTime.count * 1000) >= 4294967295 )    // if nano second value is greater than storing variable(2^32)
    {
        secondValue = (float)getTime.count/1000000;
        getTimeStamp.time_sec = (uint32_t)secondValue;
        getTimeStamp.time_nanoSec = (uint32_t)((secondValue - getTimeStamp.time_sec) * 1000000000);
    }
    else
    {
        getTimeStamp.time_sec = 0;
        getTimeStamp.time_nanoSec = getTime.count * 1000;
    }

    time->time_sec = (tcOverFlowSec * cycleUpdate) + getTimeStamp.time_sec;
    time->time_nanoSec = getTimeStamp.time_nanoSec;

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_delayMilliSec(uint32_t delayMs)
{
    if(timeInit != enEPCFBoolean_True)
        return EPCF_STATUS_NOT_CONFIGURED;

    EPCFTick_t setTimeOutTick, returnTimeOutTick;
    float overFlowCount = 0;

    if(delayMs > (tcOverFlowSec*1000))
    {
        overFlowCount = delayMs / (tcOverFlowSec*1000);
        setTimeOutTick.cycles = (uint32_t)overFlowCount;
        setTimeOutTick.tickValue = (uint32_t)((overFlowCount - setTimeOutTick.cycles)/resTimeSec);
    }
    else
    {
        setTimeOutTick.cycles = 0;
        setTimeOutTick.tickValue = (uint32_t)((delayMs*1000)/resTimeMicroSec);
    }
    returnTimeOutTick = epcf_setTimeout(setTimeOutTick);
#if(__DEBUG_ENABLE == 1)
    sprintf(data1,"return_cycles: %u\rreturn_tick: %u\r",returnTimeOutTick.cycles,returnTimeOutTick.tickValue);
    APP_DEBUG(data1);
#endif
    while( epcf_checkTimeout(returnTimeOutTick) == enEPCFBoolean_False );

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_delayMicroSec(uint32_t delayUs)
{
    if(timeInit != enEPCFBoolean_True)
        return EPCF_STATUS_NOT_CONFIGURED;

    EPCFTick_t setTimeOutTick, returnTimeOutTick;
    float overFlowCount = 0;

    if(delayUs > (tcOverFlowSec*1000000))
    {
        overFlowCount = delayUs / (tcOverFlowSec*1000000);
        setTimeOutTick.cycles = (uint32_t)overFlowCount;
        setTimeOutTick.tickValue = (uint32_t)((overFlowCount - setTimeOutTick.cycles)/resTimeSec);
    }
    else
    {
        setTimeOutTick.cycles = 0;
        setTimeOutTick.tickValue = (uint32_t)(delayUs/resTimeMicroSec);
    }
    returnTimeOutTick = epcf_setTimeout(setTimeOutTick);
    while( epcf_checkTimeout(returnTimeOutTick) == enEPCFBoolean_False );
    return EPCF_STATUS_SUCCESS;
}

EPCFTick_t epcf_setTimeout(EPCFTick_t timeoutValue)
{
    EPCFTick_t setTimeOutTick;
    uint32_t updateVal=0;

    epcf_timer_getCounterValue(pTimerDevice, &tickCount);

    while(1)
    {
        if((((uint64_t)timeoutValue.tickValue + (uint64_t)tickCount)- updateVal*__OVERFLOW_UINT32) >= __OVERFLOW_UINT32 )
        {
            ++updateVal;
        }
        else
            break;
    }
    setTimeOutTick.cycles = timeoutValue.cycles + cycleUpdate + updateVal;
    setTimeOutTick.tickValue = timeoutValue.tickValue + tickCount - updateVal*(__OVERFLOW_UINT32);

#if(__DEBUG_ENABLE == 1)
        APP_DEBUG("if\r");
        sprintf(data1,"dealy: %u\tcpu: %u\tOutCyc :%u\r",timeoutValue.tickValue,tickCount,setTimeOutTick.cycles);
        APP_DEBUG(data1);
#endif

    return setTimeOutTick;
}

EnEPCFBoolean_t epcf_checkTimeout(EPCFTick_t timeoutValue)
{
    epcf_timer_getCounterValue(pTimerDevice, &tickCount);
#if(__DEBUG_ENABLE == 1)
    sprintf(data1,"check_cyc: %u\tcheck_tick: %u\r",cycleUpdate,tickCount);
    APP_DEBUG(data1);
#endif
    if(timeoutValue.cycles == cycleUpdate)
    {
        if(timeoutValue.tickValue >= tickCount)
            return enEPCFBoolean_False;
        else
        {
#if(__DEBUG_ENABLE == 1)
    sprintf(data1,"check_cyc: %u\tcheck_tick: %u\r",cycleUpdate,tickCount);
    APP_DEBUG(data1);
    APP_DEBUG("cycle Equal, cpu tick increased\r");
#endif
            return enEPCFBoolean_True;
        }
    }
    else if(timeoutValue.cycles > cycleUpdate)
        return enEPCFBoolean_False;
    else
    {
#if(__DEBUG_ENABLE == 1)
    APP_DEBUG("cycle increased\r");
#endif
        return enEPCFBoolean_True;
    }
}

static void cycleUpdateFunc(void)
{
    ++cycleUpdate;
    tickCount = 0;
}

