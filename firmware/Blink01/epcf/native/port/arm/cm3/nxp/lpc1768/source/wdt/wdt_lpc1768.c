
#include "pcf.h"

#define __EPCF_WDT_HIDDEN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,wdt/,wdt_hidden.h)
#include  __EPCF_WDT_HIDDEN_INCLUDE
#undef __EPCF_WDT_HIDDEN_INCLUDE

/* Macros for WDT modules*/
#define __EPCF_WDT_MAX_DEVICE                   1

/* Macros for Clock select MASK of WDT*/
#define __EPCF_WDT_CLKSEL_MASK                  (uint8_t)(BIT_MASK(0) | BIT_MASK(1))

/* Macros for time boundary of WDT*/
#define __EPCF_WDT_TIMEOUT_MIN                  ((uint32_t)0x000000FF)
#define __EPCF_WDT_TIMEOUT_MAX                  ((uint32_t)0xFFFFFFFF)

/*Macro for reset bit in WDMOD*/
#define __EPCF_WDT_RESET_BIT                    BIT_MASK(1)
#define __EPCF_WDT_TIMEOUT_BIT                  BIT_MASK(2)
#define __EPCF_WDT_START_BIT                    BIT_MASK(0)

/* Macro for fixed resolution in IRC&RTC*/
#define __EPCF_WDT_RTC_FIX_RESOLUTION_US           122
#define __EPCF_WDT_IRC_FIX_RESOLUTION_US           1

/* Macro for watchdog feed register*/
#define __EPCF_WDT_FEED_AA                      0xAA
#define __EPCF_WDT_FEED_55                      0x55


// basic variables for internal use
static const uint32_t wdtIrqNum         = EPCF_IRQ_NUM(EPCF_WDT_CH);
static const uint32_t wdtChClkPdiv      = EPCF_PCLK_DIV(EPCF_WDT_CH);
static const uint32_t wdtChAdd          = WDT_BASE;

// global variables
static uint8_t  wdtDeviceCount     = __EPCF_WDT_MAX_DEVICE;
static EnEPCFBoolean_t wdtChInit    = enEPCFBoolean_False;
static uint8_t  wdtChState          =enEPCFWdtState_Idle;
static EnEPCFBoolean_t wdtChStart   = enEPCFBoolean_False;

// Static Function Declaration
static int8_t __epcfWdtInit(EPCFWdtCfg_t *pConfig, EPCFWdtDevice_t* pWdtDevice);
static int8_t __epcfWdtFeed(EPCFWdtDevice_t* pWdtDevice);
static int8_t __epcfWdtSetTimeout(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t timeOut);
static int8_t __epcfWdtGetClkDiv(EPCFWdtDevice_t* pWdtDevice,uint8_t* clkDiv);
static int8_t __epcfWdtReadResolutionMicroSec(EPCFWdtDevice_t* pWdtDevice,uint32_t *count);

// Function Definition
int8_t epcfNativeWdtInit(EPCFWdtDevice_t* pWdtDevice, EPCFWdtCfg_t *pConfig)
{
  int8_t status = EPCF_STATUS_SUCCESS;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
  CHECK_NULL_PTR(pConfig);
  if(pConfig->wdtWidth != enEPCFWdtWidth_32)
      return EPCF_STATUS_INVALID_ARGS;
#endif  // if (PCF_ENABLE_DEBUG == PCF_ENABLE)

      pWdtDevice->wdtId  = pConfig->wdtId;
      pWdtDevice->wdtChannelAddr= (WDT_TypeDef*)wdtChAdd;
      pWdtDevice->resolution = pConfig->resolution;

    status = __epcfWdtInit(pConfig, pWdtDevice);
    if(status != EPCF_STATUS_SUCCESS)
      return EPCF_STATUS_ERROR;

    wdtChState = enEPCFWdtState_Idle;

    wdtDeviceCount--;
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_wdt_close(EPCFWdtDevice_t* pWdtDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(wdtChInit);
#endif  // if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    return EPCF_STATUS_NOT_SUPPORTED;
}

uint8_t epcf_wdt_getDeviceCount()
{
    return wdtDeviceCount;
}

int8_t epcf_wdt_start(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t timeout)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(wdtChInit);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    __epcfWdtSetTimeout(pWdtDevice,timeout);
    ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr))->WDMOD |= __EPCF_WDT_START_BIT;        //Setting WDEN bit in WDMOD reg
    __epcfWdtFeed(pWdtDevice);
    wdtChStart = enEPCFBoolean_True;
    wdtChState = enEPCFWdtState_Running;
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_wdt_stop(EPCFWdtDevice_t* pWdtDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(wdtChInit);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    return EPCF_STATUS_NOT_SUPPORTED;
}

int8_t epcf_wdt_reset(EPCFWdtDevice_t* pWdtDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(wdtChInit);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr)) ->WDTC =__EPCF_WDT_TIMEOUT_MAX;

    __epcfWdtFeed(pWdtDevice);
    wdtChState = enEPCFWdtState_Running;
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_wdt_getRemainingTimeToTimeout(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t* time)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(wdtChInit);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    uint32_t currentCount;
    float resTimeMilliSec;

    // TC value is copied into TV and TV is decremented.
    currentCount = ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr))->WDTV;

    // converting resolution time value into milli seconds
    switch (pWdtDevice->resolution.unit)
    {
    case enEPCFTimeUnit_ns:
        resTimeMilliSec = ((float)(pWdtDevice->resolution.count)/1000000);
        break;
    case enEPCFTimeUnit_us:
        resTimeMilliSec = ((float)(pWdtDevice->resolution.count)/1000);
        break;
    case enEPCFTimeUnit_ms:
        resTimeMilliSec = (float)(pWdtDevice->resolution.count);
        break;
    case enEPCFTimeUnit_s:
        resTimeMilliSec = ((float)(pWdtDevice->resolution.count)*1000);
        break;
    default:
        return EPCF_STATUS_INVALID_ARGS;
    }
    time->count = currentCount * resTimeMilliSec;
    time->unit = enEPCFTimeUnit_ms;

    return EPCF_STATUS_SUCCESS;
}

EnEPCFWdtState_t epcf_wdt_getState(EPCFWdtDevice_t* pWdtDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(wdtChInit);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    return wdtChState;
}


/***************************** static function definition******************************************/
//return values:
//0 : success
//-1: error
static int8_t __epcfWdtInit(EPCFWdtCfg_t *pConfig, EPCFWdtDevice_t* pWdtDevice)
{
    uint8_t clkDiv=0;
    int8_t status;
    EnEPCFWdtClkSrc_t clockSrc=0;
    uint32_t timeMicroSec;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_NULL_PTR(pConfig);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    //Set Clock Source
    ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr))->WDCLKSEL &= ~(__EPCF_WDT_CLKSEL_MASK);        //Clearing the Bit 0 and Bit 1 of WDCLKSEL
    ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr))->WDCLKSEL =  ((EPCFWdtLpc1768Cfg_t*)(pConfig->hardwareCfg))->wdtClkSrc;                                //Setting Clksrc to CLKSEL reg

    //Set WatchDog Timer Mode Rest Bit set
    ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr))->WDMOD |= __EPCF_WDT_RESET_BIT;

    // Read clock source selected
    clockSrc =  ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr))->WDCLKSEL;
    clockSrc &=__EPCF_WDT_CLKSEL_MASK;

    if(clockSrc == enEPCFWdtClkPCLK)
    {
        // find clock divider as per resolution
        status = __epcfWdtGetClkDiv (pWdtDevice,&clkDiv);
        if(status != 0 )
            return EPCF_STATUS_ERROR;

        // set peripheral clock divider
        epcfNativeSysSetPclkDiv(NULL,wdtChClkPdiv, clkDiv);
    }
    else
    {
        // error return if resolution for IRC is not equal to 1 us
        if(clockSrc == enEPCFWdtClkIRC)
        {
            __epcfWdtReadResolutionMicroSec(pWdtDevice,&timeMicroSec);
            if(timeMicroSec != __EPCF_WDT_IRC_FIX_RESOLUTION_US)
                return EPCF_STATUS_INVALID_ARGS;
        }
        // error return if resolution for RTC is not equal to 123 us
        if(clockSrc == enEPCFWdtClkRTC)
        {
            __epcfWdtReadResolutionMicroSec(pWdtDevice,&timeMicroSec);
            if(timeMicroSec != __EPCF_WDT_RTC_FIX_RESOLUTION_US)
                return EPCF_STATUS_INVALID_ARGS;

        }
    }
    wdtChInit = enEPCFBoolean_True;

    return EPCF_STATUS_SUCCESS;
}

static int8_t __epcfWdtReadResolutionMicroSec(EPCFWdtDevice_t* pWdtDevice,uint32_t *count)
{
    uint32_t timeMicroSec;

    switch(pWdtDevice->resolution.unit)
    {
    case enEPCFTimeUnit_ns:
        timeMicroSec = ((float)(pWdtDevice->resolution.count)/1000);
        break;
    case enEPCFTimeUnit_us:
        timeMicroSec = ((float)(pWdtDevice->resolution.count)/1);
        break;
    case enEPCFTimeUnit_ms:
        timeMicroSec = (float)(pWdtDevice->resolution.count)*1000;
        break;
    case enEPCFTimeUnit_s:
        timeMicroSec = ((float)(pWdtDevice->resolution.count)*1000000);
        break;
    default:
        return EPCF_STATUS_INVALID_ARGS;
    }
    *count = timeMicroSec;
    return EPCF_STATUS_SUCCESS;
}
static int8_t __epcfWdtGetClkDiv(EPCFWdtDevice_t* pWdtDevice,uint8_t* clkDiv)
{
    uint8_t pclkDivArr[4] = {1,2,4,8};
    uint8_t index =0;
    float cpuClk=0;

    cpuClk = epcfNativeSysGetCpuClock(NULL);

    // find resolution in us
    switch(pWdtDevice->resolution.unit)
    {
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

    for(index=0;index<4;index++)
    {
        if(pWdtDevice->resolution.count == (4*(pclkDivArr[index])/cpuClk))
        {
            *clkDiv = pclkDivArr[index];
            return EPCF_STATUS_SUCCESS;
        }
    }
    return EPCF_STATUS_ERROR;
}

static int8_t __epcfWdtSetTimeout(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t timeOut)
{
    uint32_t count ;
    float timeOutMicroSec;
    float ResolutionMicroSec;
    // user required timeOut in us
    switch(timeOut.unit)
    {
    case enEPCFTimeUnit_ns:
        timeOutMicroSec = ((float)(timeOut.count)/1000);
        break;
    case enEPCFTimeUnit_us:
        timeOutMicroSec = ((float)(timeOut.count)/1);
        break;
    case enEPCFTimeUnit_ms:
        timeOutMicroSec = (float)(timeOut.count)*1000;
        break;
    case enEPCFTimeUnit_s:
        timeOutMicroSec = ((float)(timeOut.count)*1000000);
        break;
    default:
        return EPCF_STATUS_INVALID_ARGS;
    }
    // user set resolution
    switch(pWdtDevice->resolution.unit)
    {
    case enEPCFTimeUnit_ns:
        ResolutionMicroSec = ((float)(pWdtDevice->resolution.count)/1000);
        break;
    case enEPCFTimeUnit_us:
        ResolutionMicroSec = ((float)(pWdtDevice->resolution.count)*1);
        break;
    case enEPCFTimeUnit_ms:
        ResolutionMicroSec = (float)(pWdtDevice->resolution.count)*1000;
        break;
    case enEPCFTimeUnit_s:
        ResolutionMicroSec = ((float)(pWdtDevice->resolution.count)*1000000);
        break;
    default:
        return EPCF_STATUS_INVALID_ARGS;
    }

    count =(uint32_t)(timeOutMicroSec/ResolutionMicroSec);
    if( (count >= __EPCF_WDT_TIMEOUT_MIN) &&  (count <= __EPCF_WDT_TIMEOUT_MAX))
    {
        ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr))->WDTC = (uint32_t)count;
        return EPCF_STATUS_SUCCESS;
    }
    return EPCF_STATUS_ERROR;
}

static int8_t __epcfWdtFeed(EPCFWdtDevice_t* pWdtDevice)
{
    ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr))->WDFEED = __EPCF_WDT_FEED_AA;
    ((WDT_TypeDef*)(pWdtDevice->wdtChannelAddr))->WDFEED = __EPCF_WDT_FEED_55;

    return EPCF_STATUS_SUCCESS;
}
// No need to write interrupt handler it will automatically reset the controller
// If in future interrupt mode is required to add without reset then only handler is required
void EPCF_WDT_INT_HANDLER(void)
{
    //PERIPH_WDT->WDMOD &= ~(__EPCF_WDT_TIMEOUT_BIT);        /* clear the time-out flag*/
}

