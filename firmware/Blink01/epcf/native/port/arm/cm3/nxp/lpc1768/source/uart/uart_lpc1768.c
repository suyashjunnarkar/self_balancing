/*
 *  \file       uart_lpc1768.c
 *  \brief      LPC1768 Uart Driver.
 *
 */
#include "pcf.h"

#define __EPCF_PIN_LPC1768_INCLUDE      PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/   \
                ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)
#include __EPCF_PIN_LPC1768_INCLUDE
#undef __EPCF_PIN_LPC1768_INCLUDE

//Include fifo file
#define __EPCF_UTIL_FIFO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_fifo.h)
#include  __EPCF_UTIL_FIFO_INCLUDE
#undef __EPCF_UTIL_FIFO_INCLUDE

#define __EPCF_UTILS_STRING_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_string.h)
#include  __EPCF_UTILS_STRING_INCLUDE
#undef __EPCF_UTILS_STRING_INCLUDE

#define __EPCF_PRIVATE_UART_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,uart/,uart_hidden.h)
#include  __EPCF_PRIVATE_UART_H_INCLUDE
#undef __EPCF_PRIVATE_UART_H_INCLUDE


/** \brief Maximum UART Device available for UART module				*/
#define UART_MAX_CHANNEL		4

// Lookup tables.
uint32_t irq_num[4]           = {IRQ_NUM(UART0_CH),IRQ_NUM(UART1_CH),IRQ_NUM(UART2_CH),IRQ_NUM(UART3_CH)};
uint32_t pwr_uart_ch[4]       = {PWR_UART_CH(UART0_CH),PWR_UART_CH(UART1_CH), PWR_UART_CH(UART2_CH), PWR_UART_CH(UART3_CH)};
uint32_t pdiv_clk_uart_ch[4]  = {PCLK_DIV(UART0_CH),PCLK_DIV(UART1_CH), PCLK_DIV(UART2_CH), PCLK_DIV(UART3_CH)};
uint32_t uart_channel_addr[4] = {UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE};
static const uint32_t uartBaudValue[8] = {2400, 4800, 9600, 19200, 38400, 57600, 115200};
static const uint32_t uartParity[5]   = {0x00,0x01,0x03,0x05,0x07};
static const uint32_t uartStopBits[2] = {0,1};
static const uint32_t uartDataBits[4] = {0,1,2,3};
#define _U_PARITY(x)    uartParity[x]
#define _U_STOPBITS(x)  uartStopBits[x-1]
#define _U_DATABITS(x)  uartDataBits[x-5]
#define _CLK_DIV        0

/*
#define _U_PIN_ALT_FUNCTION_1     1
#define _U_PIN_ALT_FUNCTION_2     2
#define _U_PIN_ALT_FUNCTION_3     3
const uint8_t _uart_AltFunction[] = {
                          //Used, PIN,    ALT_FN_1,    ALT_FN_2,  ALT_FN_3
  _U_PIN_ALT_FUNCTION_2,   //TXD3  P0[0]   RD1          TXD3       SDA1
  _U_PIN_ALT_FUNCTION_2,   //RXD3  P0[1]   TD1          RXD3       SCL1
  _U_PIN_ALT_FUNCTION_1,   //TXD0  P0[2]   TXD0         AD0[7]     RES
  _U_PIN_ALT_FUNCTION_1,   //RXD0  P0[3]   RXD0         AD0[6      RES
  _U_PIN_ALT_FUNCTION_1,   //TXD1  P0[15]  TXD1         SCK0       SCK
  _U_PIN_ALT_FUNCTION_1,   //RXD1  P0[16]  RXD1         SSEL0      SSEL
  _U_PIN_ALT_FUNCTION_3,   //TXD3  P0[25]  AD0[2]       I2SRX_SDA  TXD3
  _U_PIN_ALT_FUNCTION_3,   //RXD3  P0[26]  AD0[3]       AOUT       RXD3
  _U_PIN_ALT_FUNCTION_1,   //TXD1  P2[0]   PWM1[1]      TXD1       RES
  _U_PIN_ALT_FUNCTION_1,   //RXD1  P2[1]   PWM1[2]      RXD1       RES
  _U_PIN_ALT_FUNCTION_2,   //TXD2  P2[8]   TD2          TXD2       RES
  _U_PIN_ALT_FUNCTION_2,   //RXD2  P2[9]   USB_CONNECT  RXD2       RES
  _U_PIN_ALT_FUNCTION_3,   //TXD3  P4[28]  RX_MCLK      MAT2[0]    TXD3
  _U_PIN_ALT_FUNCTION_3   //RXD3  P4[29]  TX_MCLK      MAT2[1]    RXD3
};
const uint8_t _uart_Port_Pin[] = {1,0,8,0,12};
*/

/*
 * Below variable _uart_Alt_Function
 * Row 1 -> Port 0
 * Row 2 -> Port 2
 * Row 3 -> Port 4
 */
const uint8_t _uart_AltFunction[3][32] =
{
 //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
  {2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0},
  {2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0},
};

// Lookup tables ends
// Static Variable Declaration
static uint32_t  uartDeviceCount = UART_MAX_CHANNEL;
static EPCFUartDevice_t* uartDevice[UART_MAX_CHANNEL] = {0,0,0,0};
static EnEPCFBoolean_t uartChInit[4] = {0,0,0,0};        // initialize flag for the channel
static uint8_t *uartRxBuffer = 0;
static uint8_t *uartTxBuffer = 0;
static uint32_t uartTxBufferSize=0, uartRxBufferSize=0;
static struct fract_div_entry
{
    real_t fr;
    uint8_t  div;
    uint8_t  mul;
} fract_divs[] =
{
    { 1.000, 0, 1 },    { 1.067, 1, 15 },   { 1.071, 1, 14 },   { 1.077, 1, 13 },
    { 1.083, 1, 12 },   { 1.091, 1, 11 },   { 1.100, 1, 10 },   { 1.111, 1, 9 },
    { 1.125, 1, 8 },    { 1.133, 2, 15 },   { 1.143, 1, 7 },    { 1.154, 2, 13 },
    { 1.167, 1, 6 },    { 1.182, 2, 11 },   { 1.200, 1, 5 },    { 1.214, 3, 14 },
    { 1.222, 2, 9 },    { 1.231, 3, 13 },   { 1.250, 1, 4 },    { 1.267, 4, 15 },
    { 1.273, 3, 11 },   { 1.286, 2, 7 },    { 1.300, 3, 10 },   { 1.308, 4, 13 },
    { 1.333, 1, 3 },    { 1.357, 5, 14 },   { 1.364, 4, 11 },   { 1.375, 3, 8 },
    { 1.385, 5, 13 },   { 1.400, 2, 5 },    { 1.417, 5, 12 },   { 1.429, 3, 7 },
    { 1.444, 4, 9 },    { 1.455, 5, 11 },   { 1.462, 6, 13 },   { 1.467, 7, 15 },
    { 1.500, 1, 2 },    { 1.533, 8, 15 },   { 1.538, 7, 13 },   { 1.545, 6, 11 },
    { 1.556, 5, 9 },    { 1.571, 4, 7 },    { 1.583, 7, 12 },   { 1.600, 3, 5 },
    { 1.615, 8, 13 },   { 1.625, 5, 8 },    { 1.636, 7, 11 },   { 1.643, 9, 14 },
    { 1.667, 2, 3 },    { 1.692, 9, 13 },   { 1.700, 7, 10 },   { 1.714, 5, 7 },
    { 1.727, 8, 11 },   { 1.733, 11, 15 },  { 1.750, 3, 4 },    { 1.769, 10, 13 },
    { 1.778, 7, 9 },    { 1.786, 11, 14 },  { 1.800, 4, 5 },    { 1.818, 9, 11 },
    { 1.833, 5, 6 },    { 1.846, 11, 13 },  { 1.857, 6, 7 },    { 1.867, 13, 15 },
    { 1.875, 7, 8 },    { 1.889, 8, 9 },    { 1.900, 9, 10 },   { 1.909, 10, 11 },
    { 1.917, 11, 12 },  { 1.923, 12, 13 },  { 1.929, 13, 14 },  { 1.933, 14, 15 },
};

// Static Function Declaration
static int32_t _epcfUartBaudrateCalc(uint32_t pclk, uint32_t baud, uint8_t *mul, uint8_t *div);
static int8_t _epcfUartInit(EPCFUartCfg_t *pConfig, EPCFUartDevice_t* pUartDevice);

//EPCFPlatfromSpecificCfg_t
// Function Definition
int8_t epcf_uart_nativeInit(EPCFUartDevice_t* pUartDevice, EPCFUartCfg_t *pConfig)
{
  EPCFPinCfg_t pPinCfg;
  int8_t status = EPCF_STATUS_SUCCESS;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
  //CHECK_NULL_PTR(pConfig);
  if(pConfig->baudrate >= enEPCFUartBaudrate_Max)
      return (-2);    //Invalid Arguments
  if(pConfig->dataBits >= enEPCFUartDatabits_Max)
      return (-2);
  if(pConfig->parity >= enEPCFUartParity_Max)
      return (-2);
  if(pConfig->stopBits >= enEPCFUartStopBits_Max)
      return (-2);
  if(pConfig->interruptEnable > enEPCFBoolean_True)
      return (-2);
  //CHECK_NULL_PTR(pConfig->hardwareCfg);
#endif  // PCF_ENABLE_DEBUG

	pUartDevice->uartId = pConfig->uartId;
	if(pConfig->uartId== 1)
		(pUartDevice->uartChannelAddr) = (UART1_TypeDef*) uart_channel_addr[pConfig->uartId];
	else
		(pUartDevice->uartChannelAddr) = (UART_TypeDef*)uart_channel_addr[pConfig->uartId];
    uartDevice[pUartDevice->uartId] = pUartDevice;
	pUartDevice->interruptEnable = pConfig->interruptEnable;
    pPinCfg.direction    = 1; // enEPCFGpioDirOutput
    pPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
    pPinCfg.openDrain    = 0; // open Drain disable
    pPinCfg.portPin.port = ((EPCFUartLpc1768Cfg_t*)(pConfig->hardwareCfg))->uartTxPin.port;
    pPinCfg.portPin.pin  = ((EPCFUartLpc1768Cfg_t*)(pConfig->hardwareCfg))->uartTxPin.pin;

    if(pPinCfg.portPin.port == EPCF_PORT_0 || pPinCfg.portPin.port == EPCF_PORT_2 ||(pPinCfg.portPin.port == EPCF_PORT_4))
    {
      pPinCfg.altFunction = _uart_AltFunction[(pPinCfg.portPin.port)/2][pPinCfg.portPin.pin];
    }
    else
    {
      return -1;
    }

    status = epcfPinInit(&pPinCfg);
    if(status != EPCF_STATUS_SUCCESS)
      return -1;

    pPinCfg.direction    = 0; // enEPCFGpioDirOutput
    pPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
    pPinCfg.openDrain    = 0; // open Drain disable
    pPinCfg.portPin.port = ((EPCFUartLpc1768Cfg_t*)(pConfig->hardwareCfg))->uartRxPin.port;;
    pPinCfg.portPin.pin  = ((EPCFUartLpc1768Cfg_t*)(pConfig->hardwareCfg))->uartRxPin.pin;;
    
    if(pPinCfg.portPin.port == EPCF_PORT_0 || pPinCfg.portPin.port == EPCF_PORT_2 ||(pPinCfg.portPin.port == EPCF_PORT_4))
    {
      pPinCfg.altFunction = _uart_AltFunction[(pPinCfg.portPin.port)/2][pPinCfg.portPin.pin];
    }
    else
    {
      return -1;
    }
    status = epcfPinInit(&pPinCfg);
    if(status != EPCF_STATUS_SUCCESS)
      return -1;

    status = _epcfUartInit(pConfig, pUartDevice);
    if(status != EPCF_STATUS_SUCCESS)
      return -1;

    uartDeviceCount--;
	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_uart_nativeClose(EPCFUartDevice_t* pUartDevice)
{
    uartChInit[pUartDevice->uartId] = enEPCFBoolean_False;
    pUartDevice->uartChBusy = enEPCFBoolean_False;
    // power off UART0 peripheral
    POWER_OFF(pwr_uart_ch[pUartDevice->uartId]);
    return EPCF_STATUS_SUCCESS;
}

int32_t epcf_uart_nativeWrite(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout)
{
    uint32_t index;
    int32_t count;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    // check if the channel is initialized
   // CHECK_DEV_INIT(uartChInit[pUartDevice->uartId]);
    //CHECK_NULL_PTR(data);
#endif  // PCF_ENABLE_DEBUG

    // check if the channel is busy
    if(pUartDevice->uartChBusy != enEPCFBoolean_False)
    {
        return EPCF_STATUS_BUSY;
    }
    // set channel busy
    pUartDevice->uartChBusy = enEPCFBoolean_True;
    // if fifo is to be used push data into the fifo
    if((pUartDevice->interruptEnable) != enEPCFBoolean_False)
    {
      count = epcf_uart_getTxBufferCount(pUartDevice); // getting fifo count
       if( (uartTxBufferSize - count) < size) // checking fifo is full or not
        {
          pUartDevice->uartChBusy = enEPCFBoolean_False;   // Fifo don't have enough space for data so return error
          return EPCF_STATUS_NO_MEMORY;
        }
        for(index = 0; index < size; index++)
        {
            pcfFifoPush(pUartDevice->uartTxFifo, *(data + index));
        }
        if(epcf_uart_getTxBufferCount(pUartDevice) == size)
        {
            if(pUartDevice->uartId==1)
                ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->THR =  pcfFifoPop(pUartDevice->uartTxFifo);
            else
                ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->THR = pcfFifoPop(pUartDevice->uartTxFifo);
        }
    }
    else
    {
        // for polling based transmission, write each byte one by one to data register
      for(index = 0; index < size; index++)
      {
        if(pUartDevice->uartId==1)
        {
          ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->THR =   *(data + index);
           while((((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->LSR & (BIT_MASK(5))) == 0);
        }
        else
        {
          ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->THR = *(data + index);
          while((((UART_TypeDef*)(pUartDevice->uartChannelAddr))->LSR & (BIT_MASK(5))) == 0);
        }
      }
    }

    pUartDevice->uartChBusy = enEPCFBoolean_False;
    return EPCF_STATUS_SUCCESS; // Success
}

int32_t epcf_uart_nativeWriteString(EPCFUartDevice_t* pUartDevice, const uint8_t* data, EPCFTime_t timeout)
{
  uint32_t index, strLen; 
  int32_t count;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    // check if the channel is initialized
    //CHECK_DEV_INIT(uartChInit[pUartDevice->uartId]);
    //CHECK_NULL_PTR(data);
#endif  // PCF_ENABLE_DEBUG

    // check if the channel is busy
    if(pUartDevice->uartChBusy != enEPCFBoolean_False)
    {
        return EPCF_STATUS_BUSY; //Busy
    }
    // set channel busy
    pUartDevice->uartChBusy = enEPCFBoolean_True;
    // if fifo is to be used push data into the fifo
    if((pUartDevice->interruptEnable) != 0)
    {     
      count = epcf_uart_getTxBufferCount(pUartDevice); // getting fifo count
      strLen = pcfStrLen(data);

      if( (uartTxBufferSize - count) < strLen) // checking fifo is full or not
      {
        pUartDevice->uartChBusy = enEPCFBoolean_False;   // Fifo don't have enough space for data so return error
        return EPCF_STATUS_NO_MEMORY;
      }

      for(index = 0; *(data + index) != 0; index++)
      {
          pcfFifoPush(pUartDevice->uartTxFifo, *(data + index));
      }
        if(epcf_uart_getTxBufferCount(pUartDevice) == strLen)
        {
            if(pUartDevice->uartId==1)
                ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->THR =  pcfFifoPop(pUartDevice->uartTxFifo);
            else
                ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->THR = pcfFifoPop(pUartDevice->uartTxFifo);
        }
    }
    else
    {
      // for polling based transmission, write each byte one by one to data register
      for(index = 0; *(data + index) != 0; index++)
      {
        if(pUartDevice->uartId==1)
        {
          ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->THR =  *(data + index);;
          while((((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->LSR & (BIT_MASK(5))) == 0);
        }
        else
        {
          ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->THR = *(data + index);;
          while((((UART_TypeDef*)(pUartDevice->uartChannelAddr))->LSR & (BIT_MASK(5))) == 0);
        }
      }
    }
    pUartDevice->uartChBusy = enEPCFBoolean_False;
    return EPCF_STATUS_SUCCESS;
}

int32_t epcf_uart_nativeRead(EPCFUartDevice_t* pUartDevice, uint8_t *data, uint32_t size, EPCFTime_t timeout)
{
    uint32_t index=0;
    int32_t readBytes=0;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    //CHECK_DEV_INIT(uart0ChInit);
    //CHECK_NULL_PTR(data);
#endif  // #if (PF_UART0_DEBUG == 1)
    // check if channel is busy
    if(pUartDevice->uartChBusy != enEPCFBoolean_False)
    {
        return EPCF_STATUS_BUSY;
    }
    // set channel busy
    pUartDevice->uartChBusy = enEPCFBoolean_True;
    // reset read byte count
    readBytes = 0;

    if((pUartDevice->interruptEnable) != 0)
    {
      for(index = 0; index < size; index++)
      {
        if(pcfFifoIsEmpty(pUartDevice->uartRxFifo) == enEPCFBoolean_True)
        {
            break;
        }
        *(data + index) = pcfFifoPop(pUartDevice->uartRxFifo);
        readBytes += 1;
      }
    }
    else
    {
        for(index = 0; index < size; index++)
        {
          if(pUartDevice->uartId==1)
          {
            while((((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->LSR & 0x01 ) == 0);
            *(data + index) = ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->RBR;
            readBytes += 1;
          }
          else
          {
            while((((UART_TypeDef*)(pUartDevice->uartChannelAddr))->LSR & 0x01 ) == 0);
            *(data + index) = ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->RBR;
            readBytes += 1;
          }
        }
    }
    pUartDevice->uartChBusy = enEPCFBoolean_False;
    return readBytes;
}

uint32_t epcf_uart_nativeGetDeviceCount()
{
    return uartDeviceCount;
}

int32_t epcf_uart_nativeGetRxBufferCount(EPCFUartDevice_t* pUartDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
  //CHECK_DEV_INIT(uartChInit[pUartDevice->uartId]);
#endif  // #if (PF_UART3_DEBUG == 1)

  return pcfFifoCount(pUartDevice->uartRxFifo); // success
}

int8_t epcf_uart_nativeRxBufferFlush(EPCFUartDevice_t* pUartDevice)
{
#if (EPCF_UART_DEBUG == PCF_ENABLE)
  //CHECK_DEV_INIT(uartChInit[pUartDevice->uartId]);
#endif  // #if (PF_UART0_DEBUG == 1)
  pcfFifoFlush(pUartDevice->uartRxFifo);
  return 0;  // success
}

int32_t epcf_uart_nativeGetTxBufferCount(EPCFUartDevice_t* pUartDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
  //CHECK_DEV_INIT(uartChInit[pUartDevice->uartId]);
#endif  // #if (PF_UART3_DEBUG == 1)

  return pcfFifoCount(pUartDevice->uartTxFifo); // success
}

int8_t epcf_uart_nativeTxBufferFlush(EPCFUartDevice_t* pUartDevice)
{
#if (EPCF_UART_DEBUG == PCF_ENABLE)
 // CHECK_DEV_INIT(uartChInit[pUartDevice->uartId]);
#endif  // #if (PF_UART0_DEBUG == 1)
  pcfFifoFlush(pUartDevice->uartTxFifo);
return 0;  // success
}

// Static Function Definition
//return values:
//0 : success
//-1: error
static int32_t _epcfUartBaudrateCalc(uint32_t pclk, uint32_t baud, uint8_t *mul, uint8_t *div)
{
  real_t fr_est, curr_fr;
  uint16_t dl;
  uint32_t i;
  
  if( pclk % (16 * baud) == 0 )
  {
    *mul = 1;
    *div = 0;
    return (pclk / (16 * baud));
  }

  fr_est = 1.5;
  while(1)
  {
    dl = pclk / (16 * baud * fr_est);
    curr_fr = (real_t)pclk / (real_t)(16 * baud * dl);
    if(curr_fr <= 1.1)
    {
      fr_est += 0.1;
    }
    else if(curr_fr >= 1.9)
    {
      fr_est -= 0.1;
    }
    else
    {
      fr_est = curr_fr;
      break;
    }
  }

  for(i = 0; i < (sizeof(fract_divs)/sizeof(struct fract_div_entry)); i++)
  {
    if( fr_est <= fract_divs[i].fr )
    {
      if( i == 0 )
      {
        *mul = fract_divs[i].mul;
        *div = fract_divs[i].div;
      }
      else if( (fract_divs[i].fr - fr_est) <= (fr_est - fract_divs[i-1].fr) )
      {
        *mul = fract_divs[i].mul;
        *div = fract_divs[i].div;
      }
      else
      {
        *mul = fract_divs[i-1].mul;
        *div = fract_divs[i-1].div;
      }
      return dl;
    }
  }

  *mul = 0;
  *div = 0;

    return 0;
}

//return values:
//0 : success
//-1: error
static int8_t _epcfUartInit(EPCFUartCfg_t *pConfig, EPCFUartDevice_t* pUartDevice)
{
  uint32_t uartPclk, baudDl, temp;
  uint8_t baudFractMul, baudFractDiv;

    // power on UART0 peripheral
    POWER_ON(pwr_uart_ch[pConfig->uartId]);

    // set peripheral clock divider
    epcfNativeSysSetPclkDiv(NULL, pdiv_clk_uart_ch[pConfig->uartId], _CLK_DIV);

    // configure UART0 channel
    temp = ( ((_U_DATABITS(pConfig->dataBits))& 0x03)| (((_U_STOPBITS(pConfig->stopBits)) & 0x01) << 2) \
          | (((_U_PARITY(pConfig->parity)) & 0x07) << 3) | (BIT_MASK(7)) );

    if(pConfig->uartId == 1)
      ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->LCR = temp;
    else
      ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->LCR = temp;

    // set baudrate //
    uartPclk = epcfNativeSysGetPclk(NULL, pdiv_clk_uart_ch[pConfig->uartId]);
    baudDl = _epcfUartBaudrateCalc(uartPclk, uartBaudValue[pConfig->baudrate], &baudFractMul, &baudFractDiv);
    if(baudDl == 0)
    {
        return -3;   //enStatusNotSupported
    }
    if(pConfig->uartId == 1)
    {
      ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->DLL = baudDl & 0xFF;
      ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->DLM = (baudDl >> 8) & 0xFF;
      ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->FDR = ((baudFractDiv & 0x0F) | ((baudFractMul << 4) & 0xF0));
    }
    else
    {
      ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->DLL = baudDl & 0xFF;
      ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->DLM = (baudDl >> 8) & 0xFF;
      ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->FDR = ((baudFractDiv & 0x0F) | ((baudFractMul << 4) & 0xF0));
    }

    // disable divisor latch
    if(pConfig->uartId == 1)
        ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->LCR &= INV_BIT_MASK(7);
    else
        ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->LCR &= INV_BIT_MASK(7);

    // Interrupt Initialization //
    if(pConfig->interruptEnable == enEPCFBoolean_True)
    {
		uartTxBufferSize = pConfig->txBufferSize;
		uartRxBufferSize = pConfig->rxBufferSize;

        // Rx & Tx buffer initialization
        uartRxBuffer = (uint8_t*)malloc(uartRxBufferSize);
        uartTxBuffer = (uint8_t*)malloc(uartTxBufferSize);

        pcfMemSet(uartRxBuffer, 0, uartRxBufferSize);
        pcfMemSet(uartTxBuffer, 0, uartTxBufferSize);

        // Enable interrupt
        if(pConfig->uartId == 1)
          ((UART1_TypeDef*)(pUartDevice->uartChannelAddr))->IER = BIT_3;
        else
          ((UART_TypeDef*)(pUartDevice->uartChannelAddr))->IER = BIT_3;
	  
          NVIC_EnableIRQ(irq_num[pConfig->uartId]);

          // Fifo Initialization
          pUartDevice->uartTxFifo = pcfFifoInit(uartTxBuffer, uartTxBufferSize);
          if(pUartDevice->uartTxFifo == NULL)    // enStatusSuccess
              return EPCF_STATUS_ERROR;

          pUartDevice->uartRxFifo = pcfFifoInit(uartRxBuffer, uartRxBufferSize);
          if(pUartDevice->uartRxFifo == NULL) //enStatusSuccess
              return EPCF_STATUS_ERROR;
    }

    uartChInit[pConfig->uartId] = enEPCFBoolean_True;
    pUartDevice->uartChBusy = enEPCFBoolean_False;
    return EPCF_STATUS_SUCCESS;
}

// Interrupt Handler for all Uart Channel
void UART0_INT_HANDLER(void)
{
  uint32_t intStat =0;
  if(uartDevice[0]->uartId==1)
  {
    intStat=((UART1_TypeDef*)(uartDevice[0]->uartChannelAddr))->IIR; //pfUart0GetIntStatus();
  }
  else
  {
    intStat=((UART_TypeDef*)(uartDevice[0]->uartChannelAddr))->IIR; //pfUart0GetIntStatus();
  }

  if((intStat & 0x04) != 0)       // Data received interrupt
  {
    uint8_t rxByte;
    if(uartDevice[1]->uartId==1)
    {
      rxByte=((UART1_TypeDef*)(uartDevice[0]->uartChannelAddr))->RBR;
    }
    else
    {
      rxByte=((UART_TypeDef*)(uartDevice[0]->uartChannelAddr))->RBR;
    }
    pcfFifoPush(uartDevice[0]->uartRxFifo, rxByte);
  }

  if((intStat & 0x02) != 0)       // THR Reg empty interrypt
  {  
    if(pcfFifoIsEmpty(uartDevice[0]->uartTxFifo) != enEPCFBoolean_True)
    {
      if(uartDevice[0]->uartId==1)
      {
        ((UART1_TypeDef*)(uartDevice[0]->uartChannelAddr))->THR= pcfFifoPop(uartDevice[0]->uartTxFifo);
      }
      else
      {
        ((UART_TypeDef*)(uartDevice[0]->uartChannelAddr))->THR= pcfFifoPop(uartDevice[0]->uartTxFifo);
      }
    }
  }
}

void UART1_INT_HANDLER(void)
{
  uint32_t intStat =0;
  if(uartDevice[1]->uartId==1)
  {
    intStat=((UART1_TypeDef*)(uartDevice[1]->uartChannelAddr))->IIR; //pfUart1GetIntStatus();
  }
  else
  {
    intStat=((UART_TypeDef*)(uartDevice[1]->uartChannelAddr))->IIR; //pfUart1GetIntStatus();
  }

  if((intStat & 0x04) != 0)       // Data received interrupt
  {
    uint8_t rxByte;
    if(uartDevice[1]->uartId==1)
    {
      rxByte=((UART1_TypeDef*)(uartDevice[1]->uartChannelAddr))->RBR;
    }
    else
    {
    rxByte=((UART_TypeDef*)(uartDevice[1]->uartChannelAddr))->RBR;
    }
    pcfFifoPush(uartDevice[1]->uartRxFifo, rxByte);
  }

  if((intStat & 0x02) != 0)       // THR Reg empty interrypt
  {
    if(pcfFifoIsEmpty(uartDevice[1]->uartTxFifo) != enEPCFBoolean_True)
    {
      if(uartDevice[1]->uartId==1)
      {
        ((UART1_TypeDef*)(uartDevice[1]->uartChannelAddr))->THR= pcfFifoPop(uartDevice[1]->uartTxFifo);
      }
      else
      {
        ((UART1_TypeDef*)(uartDevice[1]->uartChannelAddr))->THR= pcfFifoPop(uartDevice[1]->uartTxFifo);
      }
    }
  }
}

void UART2_INT_HANDLER(void)
{
  uint32_t intStat =0;
  if(uartDevice[2]->uartId==1)
  {
    intStat=((UART1_TypeDef*)(uartDevice[2]->uartChannelAddr))->IIR; //pfUart1GetIntStatus();
  }
  else
  {
    intStat=((UART_TypeDef*)(uartDevice[2]->uartChannelAddr))->IIR; //pfUart1GetIntStatus();
  }
    
   if((intStat & 0x04) != 0)       // Data received interrupt
   {
     uint8_t rxByte;
     if(uartDevice[2]->uartId==1)
     {
         rxByte=((UART1_TypeDef*)(uartDevice[2]->uartChannelAddr))->RBR;
     }
     else
     {
       rxByte=((UART_TypeDef*)(uartDevice[2]->uartChannelAddr))->RBR;
     }
     pcfFifoPush(uartDevice[2]->uartRxFifo, rxByte);
   }

   if((intStat & 0x02) != 0)       // THR Reg empty interrypt
   {
     if(pcfFifoIsEmpty(uartDevice[2]->uartTxFifo) != enEPCFBoolean_True)
     {
       if(uartDevice[2]->uartId==1)
       {
        ((UART1_TypeDef*)(uartDevice[2]->uartChannelAddr))->THR= pcfFifoPop(uartDevice[2]->uartTxFifo);
       }
     else
       {
        ((UART1_TypeDef*)(uartDevice[2]->uartChannelAddr))->THR= pcfFifoPop(uartDevice[2]->uartTxFifo);
       }
     }
   }
}

void UART3_INT_HANDLER(void)
{
  uint32_t intStat =0;
  if(uartDevice[3]->uartId==1)
  {
    intStat=((UART1_TypeDef*)(uartDevice[3]->uartChannelAddr))->IIR; //pfUart1GetIntStatus();
  }
  else
  {
    intStat=((UART_TypeDef*)(uartDevice[3]->uartChannelAddr))->IIR; //pfUart1GetIntStatus();
  }
  
  if((intStat & 0x04) != 0)       // Data received interrupt
  {
    uint8_t rxByte;
    if( uartDevice[3]->uartId== 1 )
    {
        rxByte=((UART1_TypeDef*)(uartDevice[3]->uartChannelAddr))->RBR;
    }
    else
    {
      rxByte=((UART_TypeDef*)(uartDevice[3]->uartChannelAddr))->RBR;
    }
    pcfFifoPush(uartDevice[3]->uartRxFifo, rxByte);
  }

  if((intStat & 0x02) != 0)       // THR Reg empty interrypt
  {
    if(pcfFifoIsEmpty(uartDevice[3]->uartTxFifo) != enEPCFBoolean_True)
    {
      if(uartDevice[3]->uartId==1)
      {
        ((UART1_TypeDef*)(uartDevice[3]->uartChannelAddr))->THR= pcfFifoPop(uartDevice[3]->uartTxFifo);
      }
      else
      {
        ((UART1_TypeDef*)(uartDevice[3]->uartChannelAddr))->THR= pcfFifoPop(uartDevice[3]->uartTxFifo);
      }
    }
  }
}


