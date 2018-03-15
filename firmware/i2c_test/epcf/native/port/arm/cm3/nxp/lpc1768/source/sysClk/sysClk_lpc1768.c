#include <stdlib.h>

#include "pcf.h"

#define __EPCF_PRIVATE_SYSCLK_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,sysClk/,sysClk_hidden.h)
 #include  __EPCF_PRIVATE_SYSCLK_H_INCLUDE
 #undef __EPCF_PRIVATE_SYSCLK_H_INCLUDE

//#include "epcf_string.h"

/**
 * Function provides detailed configuration of PLL with given arguments. 
 * CPU Freq = ((SrcClkFreq / N) * 2M) / D
 *
 * \param pllPreDivider PLL0 Pre-Divider value "N". 
 * \param pllMultiplier PLL0 Multiplier value "M". 
 * \param cpuClkDivider PLL clock will be divided by this value to produce the CPU clock.
 * \param pllClksrc Selects the clock source for PLL0
 *  
 * \return PLL config Status.
 */
static int8_t _epcfPllConfig(uint32_t pllPreDivider,uint32_t pllMultiplier,uint32_t cpuClkDivider,uint32_t pllClksrc);

/**
 * The function sets the CPU Clock(CCLK) frequency with given settings.
 * The function internally calculates PLL0 Multiplier value(M),PLL0 Pre-Divider value(N), CPU clock divider(D) form given settings.
 * It calls pfPllInit with calculated arguments for that.
 *
 * \param config Pointer to configuration structure which contains the settings for PLL and CPU clock.
 *
 * \return CPU clock config Status.
 */
static int8_t _epcfSysSetCpuClock(EPCFSysClkCfg_t* pConfig);

static void _epcfPllFeedSequence(void);

static uint32_t clkFrq=0;

EPCFSysClkDevice_t* epcfNativeCreateSysClk(EPCFSysClkCfg_t* pSysClkConfig)
{
  EPCFSysClkDevice_t* pSysClkDevice;
  int8_t status = 0;

  pSysClkDevice = (EPCFSysClkDevice_t *)malloc(sizeof(EPCFSysClkDevice_t));
  if (pSysClkDevice == NULL)
    return NULL;

  status = _epcfSysSetCpuClock(pSysClkConfig);
  if(status != 0)
    return NULL;

  return pSysClkDevice;
}

uint32_t epcfNativeSysGetCpuClock (EPCFSysClkDevice_t *pSysClkDevice)
{
  uint32_t pllPreDiv, pllMul, pllDiv, srcClkFreq, freq, clkSrc;
  
  pllMul = (PERIPH_SC->PLL0STAT & 0x7FFF) + 1;
  pllPreDiv = ((PERIPH_SC->PLL0STAT >> 16) & 0xFF) + 1;
  pllDiv = (PERIPH_SC->CCLKCFG & 0xFF)+ 1;
  clkSrc = PERIPH_SC->CLKSRCSEL & 0x03;     

  switch (clkSrc)
  {
    default:                            // Reserved
    case 0:                             // Internal RC oscillator
      srcClkFreq = 4000000;
            break;
    
    case 1:                             // Main oscillator
      srcClkFreq = clkFrq;
      break;

    case 2:                             // RTC oscillator
      srcClkFreq = 32768;
      break;
  }

  if ( ((PERIPH_SC->PLL0STAT >> 24) & 3) == 3 )   // PLL0 connected
  {
    freq = ( (srcClkFreq / pllPreDiv) * (2 * pllMul) ) / pllDiv;
  }
  else
  {
    freq = (srcClkFreq / pllDiv);
  }
  return freq;
}

void epcfNativeSysSetPclkDiv(EPCFSysClkDevice_t *pSysClkDevice, uint32_t peripheral, uint32_t clock)
{
  if(peripheral > 30)
  {
    PERIPH_SC->PCLKSEL1 &= ~(0x03 << (peripheral-32));
    PERIPH_SC->PCLKSEL1 |= (clock << (peripheral-32));
  }
  else
  {
    PERIPH_SC->PCLKSEL0 &= ~(0x03 << peripheral);
    PERIPH_SC->PCLKSEL0 |= (clock << peripheral);
  }
}

uint32_t epcfNativeSysGetPclk(EPCFSysClkDevice_t *pSysClkDevice, uint32_t peripheral)
{
  const uint8_t pclkDiv[] = {4, 1, 2, 8};
  uint32_t divIndex;
  uint32_t freq = epcfNativeSysGetCpuClock(pSysClkDevice);

  if(peripheral > 30)
  {
    divIndex = PERIPH_SC->PCLKSEL1 & (0x03 << (peripheral-32));
    divIndex = divIndex >> (peripheral-32);
  }
  else
  {
    divIndex = PERIPH_SC->PCLKSEL0 & (0x03 << (peripheral));
    divIndex = divIndex >> (peripheral);
  }
  
  freq = freq / pclkDiv[divIndex];
  return freq;
}

//return values:
//0  : success
//-1 : invalid arguments
static int8_t _epcfPllConfig(uint32_t pllPreDivider,uint32_t pllMultiplier,uint32_t cpuClkDivider,uint32_t pllClkSrc)
{
  uint32_t pllStatus;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
  if(pllClkSrc > 2)
  {
    return -1;
  }
#endif  // #if (PF_SYSCLK_DEBUG == 1)

  pllStatus = PERIPH_SC->PLL0STAT;
  PERIPH_SC->SCS = 0x20;              // Enable main oscillator
  while ((PERIPH_SC->SCS & SYSCLK_SC_OSCSTAT) == 0);      // Wait for Oscillator to be ready
  
  if(pllStatus & PLL_PLLC0_STAT)              // if PLL is connected, disconnect it
  {
    //Disconnect PLL
    PERIPH_SC->PLL0CON &= ~0x01;          
    _epcfPllFeedSequence();
  }
  if(pllStatus & PLL_PLLE0_STAT)              // if PLL is enabled, disable it
  {
    //Disable PLL
    PERIPH_SC->PLL0CON &= ~0x02;
    _epcfPllFeedSequence();
  }
  PERIPH_SC->CLKSRCSEL = pllClkSrc;       // Select main oscillator as clock source for PLL

  PERIPH_SC->PLL0CFG = ((pllPreDivider-1) << 16) | (pllMultiplier-1); 
  _epcfPllFeedSequence();

  PERIPH_SC->PLL0CON = 0x01;            // Enable PLL
  _epcfPllFeedSequence();

  PERIPH_SC->CCLKCFG = cpuClkDivider-1;     // CPU clock divider
  
  PERIPH_SC->PCLKSEL0 = 0x00;             // Peripheral Clock Selection CCLK / 4
  PERIPH_SC->PCLKSEL1 = 0x00;

  while( (PERIPH_SC->PLL0STAT & PLL_PLOCKO) == 0 ); // Wait for PLL to achieve lock
  
  PERIPH_SC->PLL0CON = 0x03;            // Connect PLL
  _epcfPllFeedSequence();

  //LPC_SC->CLKOUTCFG =  0x00;

  pllStatus = PERIPH_SC->PLL0STAT;
  pllStatus = 0;
  
  return 0;
}

static void _epcfPllFeedSequence(void)
{
  PERIPH_SC->PLL0FEED = 0xAA;
  PERIPH_SC->PLL0FEED = 0x55;
}

//return values:
//0  : success
//-1 : invalid arguments
//-2 : error
static int8_t _epcfSysSetCpuClock(EPCFSysClkCfg_t* config)
{
  uint32_t pllPreDiv, pllMul, pllDiv, temp, loop, preDivStatus = 0;
  int8_t status=0;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
 // CHECK_NULL_PTR(config);
  if(config->pllClkSrc > 2)
  {
    return -1;
  }
  if(config->cpuFreqHz > 100000000)
  {
    return -1;
  }
#endif  // #if (PF_SYSCLK_DEBUG == 1)

  clkFrq=config->oscFreq;
  pllDiv = (300*1000000) / config->cpuFreqHz;
  temp = ((config->cpuFreqHz * pllDiv) / (2 * config->oscFreq));

  for(loop = temp; loop <= (config->oscFreq/1000000); loop++)
  {
    if( ((config->oscFreq/1000000) % loop) == 0 )
    {
      pllPreDiv = loop;
      preDivStatus = 1;
      break;
    }
  }
  if(!preDivStatus)
  {
    return -2;
  }

  pllMul = ((config->cpuFreqHz * pllDiv * pllPreDiv) / 24) / 1000000;

  status = _epcfPllConfig(pllPreDiv ,pllMul ,pllDiv, config->pllClkSrc);
  return status;
}
