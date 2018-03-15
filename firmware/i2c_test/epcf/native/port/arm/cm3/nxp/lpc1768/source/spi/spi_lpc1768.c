/**
 * \file  spi.c
 * \brief This file is used to configure a UART device
 */

#include "pcf.h"

#define __EPCF_FIFO_INCLUDE         PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_fifo.h)
#include  __EPCF_FIFO_INCLUDE
#undef __EPCF_FIFO_INCLUDE

#define __EPCF_SPI_HIDDEN_INCLUDE   PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,spi/,spi_hidden.h)
#include  __EPCF_SPI_HIDDEN_INCLUDE
#undef __EPCF_SPI_HIDDEN_INCLUDE

#define __EPCF_STRING_INCLUDE       PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_string.h)
#include  __EPCF_STRING_INCLUDE
#undef __EPCF_STRING_INCLUDE

#define __EPCF_SPI_CONFIG_INCLUDE    PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/  \
                                     ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/    \
                                     ,PCF_ARCH_DEVICE/include/spi/,spi_lpc1768_config.h)
#include __EPCF_SPI_CONFIG_INCLUDE
#undef __EPCF_SPI_CONFIG_INCLUDE


// Macro for Debug Enable
#if PCF_ENABLE_DEBUG == PCF_ENABLE
    #define _SPI_DEBUG  PCF_ENABLE
#else
    #define _SPI_DEBUG  PCF_DISABLE
#endif // PCF_ENABLE_DEBUG == PCF_ENABLE

// Macros to change later
// TODO: ADD Debug Log
#define _SPI_CHECK_DEV_INIT(dev)         if(dev == enEPCFBoolean_False){ return EPCF_STATUS_NOT_CONFIGURED; }                                         }
#define _SPI_CHECK_NULL_PTR(ptr)         if(ptr == 0){ return EPCF_STATUS_INVALID_ARGS; }
// end macros to be change

// Lookup tables.
static const uint32_t spiIrqNum[EPCF_SPI_MAX_CHANNEL]       = {EPCF_IRQ_NUM(EPCF_SPI0_CH),EPCF_IRQ_NUM(EPCF_SPI1_CH)};
static const uint32_t spiChAddr[EPCF_SPI_MAX_CHANNEL]       = {SSP0_BASE, SSP1_BASE};
static const uint32_t spiChPwr[EPCF_SPI_MAX_CHANNEL]        = {EPCF_PWR_SPI_CH(EPCF_SPI0_CH),EPCF_PWR_SPI_CH(EPCF_SPI1_CH)};
static const uint32_t spiChClkPdiv[EPCF_SPI_MAX_CHANNEL]    = {PCLK_DIV(EPCF_SPI1_CH),PCLK_DIV(EPCF_SPI1_CH)};

// SPI Configuration Macro
#define __EPCF_SPI_CLK_DIV              0

#define __EPCF_SPI_STATE_IDLE           0
#define __EPCF_SPI_STATE_READ           1
#define __EPCF_SPI_STATE_WRITE          2

#define __EPCF_SPI_SSE_ENABLE           BIT_MASK(1)
#define __EPCF_SPI_MASTER_MODE          INV_BIT_MASK(2)
#define __EPCF_SPI_SLAVE_MODE           BIT_MASK(2)

#define __EPCF_SPI_TNF_FLAG             BIT_MASK(1)
#define __EPCF_SPI_BUSY_FLAG            BIT_MASK(4)
#define __EPCF_SPI_RNE_FLAG             BIT_MASK(2)
#define __EPCF_SPI_TFE_FLAG             BIT_MASK(0)

#define __EPCF_SPI_IMSC_CLR             0x00
#define __EPCF_SPI_CLR_REG              0x00000000
#define __EPCF_SPI_DATABITS_MASK        0xFFFFFFF0
#define __EPCF_SPI_CLOCKMODE_MASK       ~(0x03 << 6)
#define __EPCF_SPI_MIN_PRESCALAR        2
#define __EPCF_SPI_CR0_SCR_MASK         0x00FF
#define __EPCF_SPI_CR0_SCR_BIT          8
#define __EPCF_SPI_CR0_CPOL_CPHA_BIT    6


// Macro for Temporary Delay 
// TODO: Replace this with the function call from the epcf_delay.h
#define __EPCF_SPI_DELAY                _spiDelay()
void _spiDelay(void)
{
    uint32_t i;
    for(i=0;i<100;i++);
}

/*
 * variable for selecting the Alternative Function as SPI specific ALT function.
 * Row 1 -> Port 0
 * Row 2 -> Port 1
 */
const uint8_t spiAltFunc[2][32] =
{
 //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
  {0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0, 2},
};
// Lookup tables ends

// Static Variable Declaration
static uint32_t spiDeviceCount = EPCF_SPI_MAX_CHANNEL;
static EPCFSpiDevice_t* spiDevice[EPCF_SPI_MAX_CHANNEL] = {0};
static EnEPCFBoolean_t spiChInit[EPCF_SPI_MAX_CHANNEL] = {enEPCFBoolean_False};        // initialize flag for the channel
static uint8_t *spiTxBuffer = 0;
static uint8_t *spiRxBuffer = 0;
static uint32_t spiRxBufferSize=0;
static uint32_t spiTxBufferSize=0;
static uint8_t spiChState[EPCF_SPI_MAX_CHANNEL]={0};
static EnEPCFBoolean_t spiOverrunInt[EPCF_SPI_MAX_CHANNEL]={enEPCFBoolean_False};
static EnEPCFBoolean_t spiRxBuffHalfFullInt[EPCF_SPI_MAX_CHANNEL]={enEPCFBoolean_False};
static EnEPCFBoolean_t spiTimeOutInt[EPCF_SPI_MAX_CHANNEL]={enEPCFBoolean_False};
static EnEPCFBoolean_t masterMode[EPCF_SPI_MAX_CHANNEL]= {enEPCFBoolean_False};
static uint8_t spiRegDeviceCount[EPCF_SPI_MAX_CHANNEL]={0};
static uint8_t spiRegDevice[EPCF_SPI_MAX_CHANNEL][EPCF_SPI_MAX_DEVICE_SUPPORTED];
static EPCFPortPin_t spiChipSelect[EPCF_SPI_MAX_CHANNEL][EPCF_SPI_MAX_DEVICE_SUPPORTED];
static EnEPCFBoolean_t spiIntEnable[EPCF_SPI_MAX_CHANNEL]={enEPCFBoolean_False};
static EnEPCFBoolean_t spiFifoInit[EPCF_SPI_MAX_CHANNEL]={enEPCFBoolean_False};
EPCFGpioDevice_t *spiCsGpioDevice[EPCF_SPI_MAX_CHANNEL][EPCF_SPI_MAX_DEVICE_SUPPORTED];
static uint8_t slaveSelectId[EPCF_SPI_MAX_CHANNEL]= {0};
// true : MSB  false: LSB
static EnEPCFBoolean_t spiChBusy[EPCF_SPI_MAX_CHANNEL]={enEPCFBoolean_False};

// Static Function Declaration
static int8_t _epcfSpiInit(EPCFSpiCfg_t *pConfig, EPCFSpiDevice_t* pSpiDevice);
//EPCFPlatfromSpecificCfg_t

// Function Definition
int8_t epcf_Spi_nativeInit(EPCFSpiDevice_t* pSpiDevice, EPCFSpiCfg_t *pConfig)
{
    EPCFPinCfg_t pPinCfg;
    int8_t status = EPCF_STATUS_SUCCESS;

#if (_SPI_DEBUG == PCF_ENABLE)
    // Parameter Checking
    _SPI_CHECK_NULL_PTR(pConfig);
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_NULL_PTR(pConfig->hardwareCfg);

#endif  // _SPI_DEBUG
    if(((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->misoPin.port!=EPCF_PORT_0 &&((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->misoPin.port!=EPCF_PORT_1)
    {
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }

    if(((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->mosiPin.port!=EPCF_PORT_0 &&((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->misoPin.port!=EPCF_PORT_1)
    {
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }
    if(((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->sckPin.port!=EPCF_PORT_0 &&((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->misoPin.port!=EPCF_PORT_1)
    {
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }
    if( (pConfig->spiMode == enEPCFSpiMode_Slave) && (((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->csPin.port!=EPCF_PORT_0 &&((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->misoPin.port!=EPCF_PORT_1))
    {
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }

    pSpiDevice->spiId = pConfig->spiId;
    (pSpiDevice->SpiChannelAddr) = (SSP_TypeDef*) spiChAddr[pConfig->spiId];
    spiDevice[pSpiDevice->spiId] = pSpiDevice;

    // Pin configuration for MISO.
    pPinCfg.direction    = 0; // enEPCFGpioDirInput
    pPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
    pPinCfg.openDrain    = 0; // open Drain disable
    pPinCfg.portPin.port = ((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->misoPin.port;
    pPinCfg.portPin.pin  = ((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->misoPin.pin;
    pPinCfg.altFunction = spiAltFunc[(pPinCfg.portPin.port)][pPinCfg.portPin.pin];
    
    status = epcfPinInit(&pPinCfg);
    if(status != EPCF_STATUS_SUCCESS){
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }
    
    // Pin configuration for MOSI.
    pPinCfg.direction    = 1; // enEPCFGpioDirOutput
    pPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
    pPinCfg.openDrain    = 0; // open Drain disable
    pPinCfg.portPin.port = ((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->mosiPin.port;
    pPinCfg.portPin.pin  = ((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->mosiPin.pin;
    pPinCfg.altFunction = spiAltFunc[(pPinCfg.portPin.port)][pPinCfg.portPin.pin];

    status = epcfPinInit(&pPinCfg);
    if(status != EPCF_STATUS_SUCCESS){
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }

    // Pin configuration for SCK.
    pPinCfg.direction    = 1; // enEPCFGpioDirOutput
    pPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
    pPinCfg.openDrain    = 0; // open Drain disable
    pPinCfg.portPin.port = ((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->sckPin.port;
    pPinCfg.portPin.pin  = ((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->sckPin.pin;
    pPinCfg.altFunction = spiAltFunc[(pPinCfg.portPin.port)][pPinCfg.portPin.pin];
    
    status = epcfPinInit(&pPinCfg);
    if(status != EPCF_STATUS_SUCCESS){
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }

    if(pConfig->spiMode == enEPCFSpiMode_Slave)
    {
        // Pin configuration for Slave Select (CS) for SPI Slave mode.
        pPinCfg.direction    = 1; // enEPCFGpioDirOutput
        pPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
        pPinCfg.openDrain    = 0; // open Drain disable
        pPinCfg.portPin.port = ((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->csPin.port;
        pPinCfg.portPin.pin  = ((EPCFSpiLpc1768Cfg_t*)(pConfig->hardwareCfg))->csPin.pin;
        pPinCfg.altFunction = spiAltFunc[(pPinCfg.portPin.port)][pPinCfg.portPin.pin];

        status = epcfPinInit(&pPinCfg);
        if(status != EPCF_STATUS_SUCCESS){
            //TODO: ADD Debug Log
            return EPCF_STATUS_ERROR;
        }
    }

    status = _epcfSpiInit(pConfig, pSpiDevice);
    if(status != EPCF_STATUS_SUCCESS){
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }

    spiDeviceCount--;
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_spi_nativeClose(EPCFSpiDevice_t* pSpiDevice)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);

#endif

    // chip select is asserted and we are trying to close device.
     if(spiChBusy[pSpiDevice->spiId]== enEPCFBoolean_True)
     {
         //TODO: ADD Debug Log
         return EPCF_STATUS_BUSY;
     }

    spiChInit[pSpiDevice->spiId] = enEPCFBoolean_False;

    // Power off SSP peripheral
    POWER_OFF(spiChPwr[pSpiDevice->spiId]);
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_spi_nativeRegisterSlaveDevice(EPCFSpiDevice_t* pSpiDevice, EPCFPortPin_t slaveSelectPin)
{
    uint8_t index;
    EPCFGpioCfg_t pConfig;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
#endif

    // Checking SPI Mode if Slave Return
    if(masterMode[pSpiDevice->spiId]!= enEPCFBoolean_True )
    {
        //TODO: ADD Debug Log
        return EPCF_STATUS_NOT_SUPPORTED;
    }

    // Pin Configuration for CS pin in Master mode
    pConfig.direction    = 1;                   // enEPCFGpioDirOutput
    pConfig.mode         = 0;                   // enEPCFGpioPinModePullUp
    pConfig.openDrain    = 0;                   // open Drain disable
    pConfig.portPin.port = slaveSelectPin.port;
    pConfig.portPin.pin  = slaveSelectPin.pin;

    for(index = 0; index < EPCF_SPI_MAX_DEVICE_SUPPORTED; index++)
    {
        if(spiCsGpioDevice[pSpiDevice->spiId][index]==0)
            break;
    }
    spiCsGpioDevice[pSpiDevice->spiId][index] = epcf_gpio_createNative(&pConfig);

    if(spiRegDeviceCount[pSpiDevice->spiId] >= EPCF_SPI_MAX_DEVICE_SUPPORTED)
    {
        return EPCF_STATUS_MAX_DEVICES_CONNECTED;
    }
    
    for(index = 0; index < EPCF_SPI_MAX_DEVICE_SUPPORTED; index++)
    {
        if(spiRegDevice[pSpiDevice->spiId][index] == enEPCFBoolean_False)
        {
            spiRegDevice[pSpiDevice->spiId][index] = enEPCFBoolean_True;
            spiRegDeviceCount[pSpiDevice->spiId]++;
            spiChipSelect[pSpiDevice->spiId][index].port = slaveSelectPin.port;
            spiChipSelect[pSpiDevice->spiId][index].pin = slaveSelectPin.pin;
            epcf_gpio_set(spiCsGpioDevice[pSpiDevice->spiId][index]);
            return index;
        }
    }
    //TODO: ADD Debug Log
    return EPCF_STATUS_ERROR;
}

int8_t epcf_spi_nativeDeRegisterSlaveDevice(EPCFSpiDevice_t* pSpiDevice,uint8_t slaveId)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
    
    if(slaveId >=EPCF_SPI_MAX_DEVICE_SUPPORTED ){
        //TODO: ADD Debug Log
        return EPCF_STATUS_INVALID_ARGS;
    }
#endif

    // Checking SPI Mode if Slave Return
    if(masterMode[pSpiDevice->spiId]!= enEPCFBoolean_True )
    {
        //TODO: ADD Debug Log
        return EPCF_STATUS_NOT_SUPPORTED;

    }

    spiRegDevice[pSpiDevice->spiId][slaveId]  = enEPCFBoolean_False;
    spiRegDeviceCount[pSpiDevice->spiId]--;

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_spi_nativeSlaveSelect(EPCFSpiDevice_t* pSpiDevice, uint8_t slaveId)
{
    uint8_t index;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
 
    if(slaveId >=EPCF_SPI_MAX_DEVICE_SUPPORTED ){
        //TODO: ADD Debug Log
        return EPCF_STATUS_INVALID_ARGS;
    }

     if(spiRegDevice[pSpiDevice->spiId][slaveId]!=enEPCFBoolean_True ){
        //TODO: ADD Debug Log
        return EPCF_STATUS_INVALID_ARGS;
    }
#endif

    // Checking SPI Mode if Slave Return
    if(masterMode[pSpiDevice->spiId] != enEPCFBoolean_True)
    {
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }

    //Check if its already busy
     if(spiChBusy[pSpiDevice->spiId]== enEPCFBoolean_True)
        return EPCF_STATUS_BUSY;

    for(index = 0; index < EPCF_SPI_MAX_DEVICE_SUPPORTED; index++)
    {
        if( epcf_gpio_read(spiCsGpioDevice[pSpiDevice->spiId][slaveId])&& 1<<spiChipSelect[pSpiDevice->spiId][index].pin  == 0 )
        {
            return EPCF_STATUS_BUSY;
        }
    }
    // chip select id slave is saved
    slaveSelectId[pSpiDevice->spiId] = slaveId;
    spiChBusy[pSpiDevice->spiId] = enEPCFBoolean_True;
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_spi_nativeSlaveDeSelect(EPCFSpiDevice_t* pSpiDevice, uint8_t slaveId)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);

    if(slaveId >=EPCF_SPI_MAX_DEVICE_SUPPORTED ){
        //TODO: ADD Debug Log
        return EPCF_STATUS_INVALID_ARGS;
    }

    if(spiRegDevice[pSpiDevice->spiId][slaveId]!=enEPCFBoolean_True ){
       //TODO: ADD Debug Log
        return EPCF_STATUS_INVALID_ARGS;
    }
#endif

    //De-assert chip select
    epcf_gpio_set(spiCsGpioDevice[pSpiDevice->spiId][slaveId]);
    spiChBusy[pSpiDevice->spiId] = enEPCFBoolean_False;
    slaveSelectId[pSpiDevice->spiId] = 0;
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_spi_nativeExchange(EPCFSpiDevice_t* pSpiDevice, uint16_t txData, uint16_t* rxData, EPCFTime_t timeout)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_NULL_PTR(rxData);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
#endif

    if(spiOverrunInt[pSpiDevice->spiId] ||spiTimeOutInt[pSpiDevice->spiId]||spiRxBuffHalfFullInt[pSpiDevice->spiId])
        NVIC_DisableIRQ(spiIrqNum[pSpiDevice->spiId]);

    spiChState[pSpiDevice->spiId] = __EPCF_SPI_STATE_IDLE;             // Changing the State of SPI Channel to IDLE State

    if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
        epcf_gpio_clear(spiCsGpioDevice[pSpiDevice->spiId][slaveSelectId[pSpiDevice->spiId]]);

     // wait if transmit FIFO is full
    while( ((((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->SR) & __EPCF_SPI_TNF_FLAG) != __EPCF_SPI_TNF_FLAG );
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR = txData ;
    // wait till data is transmitted
    while( ((((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->SR) & __EPCF_SPI_BUSY_FLAG) == __EPCF_SPI_BUSY_FLAG );
    *rxData = ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR;

    if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
        epcf_gpio_set(spiCsGpioDevice[pSpiDevice->spiId][slaveSelectId[pSpiDevice->spiId]]);
    
    if(spiOverrunInt[pSpiDevice->spiId] ||spiTimeOutInt[pSpiDevice->spiId]||spiRxBuffHalfFullInt[pSpiDevice->spiId])
        NVIC_EnableIRQ(spiIrqNum[pSpiDevice->spiId]);

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_spi_nativeWrite(EPCFSpiDevice_t* pSpiDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout)
{
    uint32_t index;
    uint8_t dummyRead PCF_C_UNUSED_ARG;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
    _SPI_CHECK_NULL_PTR(data);
#endif

     if( spiIntEnable[pSpiDevice->spiId] == enEPCFBoolean_True)
     {
        if(spiChState[pSpiDevice->spiId] != __EPCF_SPI_STATE_WRITE)
        {
            spiChState[pSpiDevice->spiId] = __EPCF_SPI_STATE_WRITE;
                if((SSP_TypeDef*)(pSpiDevice->bitOrder) == enEPCFSpiBitOrder_Msb)
                {
                    for(index = 0; index < size; index++)
                    {
                        pcfFifoPush(pSpiDevice->spiTxFifo, *(data + index));
                    }
                }
                else
                {
                    for(index = size; index > 0; index--)
                    {
                        pcfFifoPush(pSpiDevice->spiTxFifo, *(data + index));
                    }
                 }
                while( (((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->SR & (__EPCF_SPI_RNE_FLAG)) != 0 )
                {
                    dummyRead = ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR;
                }
                if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
                    epcf_gpio_clear(spiCsGpioDevice[pSpiDevice->spiId][slaveSelectId[pSpiDevice->spiId]]);

                ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR = pcfFifoPop(pSpiDevice->spiTxFifo);
        }
     }
     else
     {
            if((SSP_TypeDef*)(pSpiDevice->bitOrder) == enEPCFSpiBitOrder_Msb)
                {
                    for(index = 0; index < size; index++)
                    {
                        if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
                            epcf_gpio_clear(spiCsGpioDevice[pSpiDevice->spiId][slaveSelectId[pSpiDevice->spiId]]);

                        ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR = *(data + index);;
                        while( (((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->SR & __EPCF_SPI_BUSY_FLAG) == __EPCF_SPI_BUSY_FLAG );
                        dummyRead = ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR;

                        if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
                            epcf_gpio_set(spiCsGpioDevice[pSpiDevice->spiId][slaveSelectId[pSpiDevice->spiId]]);
                    }
                }
             else
             {
                for(index = size; index >0; index--)
                    {
                    if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
                        epcf_gpio_clear(spiCsGpioDevice[pSpiDevice->spiId][slaveSelectId[pSpiDevice->spiId]]);

                        ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR= *(data + index);
                        while( (((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->SR & __EPCF_SPI_BUSY_FLAG) == __EPCF_SPI_BUSY_FLAG );
                        dummyRead = ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR;

                    if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
                        epcf_gpio_set(spiCsGpioDevice[pSpiDevice->spiId][slaveSelectId[pSpiDevice->spiId]]);
                    }
             }
     }
    return EPCF_STATUS_SUCCESS;
}

int8_t  epcf_spi_nativeRead(EPCFSpiDevice_t* pSpiDevice, uint8_t* data, uint32_t size, EPCFTime_t timeout)
{
    uint32_t index;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_NULL_PTR(data);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
#endif

    if(spiIntEnable[pSpiDevice->spiId] == enEPCFBoolean_True)
    {
         //LastspiChState[pSpiDevice->spiId] = spiChState[pSpiDevice->spiId];           // Preserving the State of SPI channel
        if(spiChState[pSpiDevice->spiId] != __EPCF_SPI_STATE_READ)
        {
            spiChState[pSpiDevice->spiId] = __EPCF_SPI_STATE_READ;
            if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
                {
                    // For master mode, push dummy data in buffer
                    for(index = 0; index < size; index++)
                    {
                        pcfFifoPush(pSpiDevice->spiTxFifo, 0);
                    }
                    if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
                        epcf_gpio_clear(spiCsGpioDevice[0][slaveSelectId[pSpiDevice->spiId]]);
                    
                    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR = pcfFifoPop(pSpiDevice->spiTxFifo);
                    // wait for all bytes to transmit and state change to be IDLE

                }
         }

         if(epcf_spi_getRxBufferCount(pSpiDevice) == size)
         {
                // Read receive fifo
                for(index = 0; index < size; index++)
                {
                    if(pcfFifoIsEmpty(pSpiDevice->spiRxFifo) == enEPCFBoolean_True)
                        break;
                    *(data + index) = pcfFifoPop(pSpiDevice->spiRxFifo);
                }
         }
        }
     else
     {
        for(index = 0; index < size; index++)
            {
                if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
                    epcf_gpio_clear(spiCsGpioDevice[pSpiDevice->spiId][slaveSelectId[pSpiDevice->spiId]]);
                
                ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR= 0;
                while( (((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->SR & __EPCF_SPI_BUSY_FLAG) == __EPCF_SPI_BUSY_FLAG );
                *(data + index) = ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->DR;

                if(masterMode[pSpiDevice->spiId]== enEPCFBoolean_True)
                {
                    epcf_gpio_set(spiCsGpioDevice[pSpiDevice->spiId][slaveSelectId[pSpiDevice->spiId]]);
                    __EPCF_SPI_DELAY;
                }

            }
    }
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_spi_nativeIntEnable(EPCFSpiDevice_t* pSpiDevice, EnEPCFSpiIntType intType)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
    
    if(intType >=enEPCFSpiInt_Max){
        //TODO: ADD Debug Log
        return EPCF_STATUS_INVALID_ARGS;
    }
#endif

    if(spiFifoInit[pSpiDevice->spiId] == enEPCFBoolean_False){
        //TODO: ADD Debug Log
        return EPCF_STATUS_ERROR;
    }

    NVIC_EnableIRQ(spiIrqNum[pSpiDevice->spiId]);

    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->IMSC|= BIT_MASK(intType);

    if(intType == enEPCFSpiIntRx_Overrun)
        spiOverrunInt[pSpiDevice->spiId] = enEPCFBoolean_True;

    if(intType == enEPCFSpiIntRx_Timeout)
        spiTimeOutInt[pSpiDevice->spiId] = enEPCFBoolean_True;

    if(intType == enEPCFSpiIntRx_BuffHalfFull)
        spiRxBuffHalfFullInt[pSpiDevice->spiId] = enEPCFBoolean_True;

    spiIntEnable[pSpiDevice->spiId]= enEPCFBoolean_True;

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_spi_nativeIntDisable(EPCFSpiDevice_t* pSpiDevice , EnEPCFSpiIntType intType)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
    
    if(intType >=enEPCFSpiInt_Max){
        //TODO: ADD Debug Log
        return EPCF_STATUS_INVALID_ARGS;
    }
#endif

    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->IMSC|= INV_BIT_MASK(intType);
    NVIC_DisableIRQ(spiIrqNum[pSpiDevice->spiId]);

    if(intType == enEPCFSpiIntRx_Overrun)
        spiOverrunInt[pSpiDevice->spiId] = enEPCFBoolean_False;

    if(intType == enEPCFSpiIntRx_Timeout)
        spiTimeOutInt[pSpiDevice->spiId] = enEPCFBoolean_False;

    if(intType == enEPCFSpiIntRx_BuffHalfFull)
        spiRxBuffHalfFullInt[pSpiDevice->spiId] = enEPCFBoolean_False;

    if(((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->IMSC == __EPCF_SPI_IMSC_CLR)
        spiIntEnable[pSpiDevice->spiId]= enEPCFBoolean_False;

    return EPCF_STATUS_SUCCESS;
}

uint8_t epcf_spi_nativeGetDeviceCount()
{
    return spiDeviceCount;
}

int32_t epcf_spi_nativeGetRxBufferCount(EPCFSpiDevice_t* pSpiDevice)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    return pcfFifoCount(pSpiDevice->spiRxFifo); // success
}

int8_t epcf_spi_nativeRxBufferFlush(EPCFSpiDevice_t* pSpiDevice)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    pcfFifoFlush(pSpiDevice->spiRxFifo);
    return EPCF_STATUS_SUCCESS;  // success
}

int32_t epcf_spi_nativeGetTxBufferCount(EPCFSpiDevice_t* pSpiDevice)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    return pcfFifoCount(pSpiDevice->spiTxFifo); // Success
}

int8_t epcf_spi_nativeTxBufferFlush(EPCFSpiDevice_t* pSpiDevice)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_DEV_INIT(spiChInit[pSpiDevice->spiId]);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    pcfFifoFlush(pSpiDevice->spiTxFifo);

return EPCF_STATUS_SUCCESS;
}

// Static Function Definition
static int8_t _epcfSpiInit(EPCFSpiCfg_t *pConfig, EPCFSpiDevice_t* pSpiDevice)
{
    uint32_t spiPclk;
    uint32_t  cr0_div, cmp_clk, prescale, temp;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    _SPI_CHECK_NULL_PTR(pSpiDevice);
    _SPI_CHECK_NULL_PTR(pConfig);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    spiDevice[pConfig->spiId] = pSpiDevice;
    
    // power on SPI peripheral
    POWER_ON(spiChPwr[pConfig->spiId]);

     // clear Spi configuration registers                                                                                                                                                                
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR0 =__EPCF_SPI_CLR_REG;
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR1 =__EPCF_SPI_CLR_REG;
    
    // set peripheral clock divider
    epcfNativeSysSetPclkDiv(NULL, spiChClkPdiv[pConfig->spiId], __EPCF_SPI_CLK_DIV);

    // set peripheral clock
    spiPclk = epcfNativeSysGetPclk(NULL, spiChClkPdiv[pConfig->spiId]);

    // set data bit size
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR0 &= __EPCF_SPI_DATABITS_MASK;
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR0 |= (pConfig->dataBits+3);

    // set mode
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR0 &= __EPCF_SPI_CLOCKMODE_MASK;
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR0 |= pConfig->clockMode << __EPCF_SPI_CR0_CPOL_CPHA_BIT;

    //set FIFO size
    spiTxBufferSize = pConfig->txBufferSize;
    spiRxBufferSize = pConfig->rxBufferSize;

    // set baudrate
    cr0_div = 0;
    cmp_clk = 0xFFFFFFFF;
    prescale = __EPCF_SPI_MIN_PRESCALAR;

    while (cmp_clk > pConfig->baudrate)
    {
        cmp_clk = spiPclk / ((cr0_div + 1) * prescale);
        if (cmp_clk > pConfig->baudrate)
        {
            cr0_div++;
        if (cr0_div > 0xFF)
        {
            cr0_div = 0;
            prescale += 2;
        }
        }
    }

    temp = ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR0 & __EPCF_SPI_CR0_SCR_MASK;
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR0 = temp | (cr0_div << __EPCF_SPI_CR0_SCR_BIT);
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CPSR = prescale;

    // set master/slave
    if(pConfig->spiMode == enEPCFSpiMode_Master)
    {
        ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR1 &= __EPCF_SPI_MASTER_MODE;
        masterMode[pConfig->spiId] = enEPCFBoolean_True;
    }
    else
    {
        ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR1 |= __EPCF_SPI_SLAVE_MODE;
    }
    pSpiDevice->interruptEnable =  pConfig->interruptEnable;

    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->IMSC = __EPCF_SPI_IMSC_CLR;

    if(pSpiDevice->interruptEnable == enEPCFBoolean_True)   
    {
        // Rx & Tx buffer initialization
        spiTxBufferSize = pConfig->txBufferSize;
        spiRxBufferSize = pConfig->rxBufferSize;

        // Rx & Tx buffer initialization
        spiRxBuffer = (uint8_t*)malloc(spiRxBufferSize);
        spiTxBuffer = (uint8_t*)malloc(spiTxBufferSize);

        pcfMemSet(spiTxBuffer, 0, spiTxBufferSize);
        pcfMemSet(spiRxBuffer, 0, spiRxBufferSize);

        pSpiDevice->spiTxFifo = pcfFifoInit(spiTxBuffer, spiTxBufferSize);
        if(pSpiDevice->spiTxFifo == NULL)    // enStatusSuccess
            return EPCF_STATUS_ERROR;

        pSpiDevice->spiRxFifo = pcfFifoInit(spiRxBuffer, spiRxBufferSize);
        if(pSpiDevice->spiRxFifo == NULL) //enStatusSuccess
            return EPCF_STATUS_ERROR;

        epcf_spi_intEnable(NULL,pConfig->intType);
        spiIntEnable[pSpiDevice->spiId] =enEPCFBoolean_True;
        spiFifoInit[pSpiDevice->spiId] =enEPCFBoolean_True;
    }

    pSpiDevice->bitOrder =  pConfig->bitOrder;
    ((SSP_TypeDef*)(pSpiDevice->SpiChannelAddr))->CR1 |= __EPCF_SPI_SSE_ENABLE;

    // Initialization done
    spiChInit[pConfig->spiId] = enEPCFBoolean_True;
    spiChState[pConfig->spiId] = __EPCF_SPI_STATE_IDLE;
    return EPCF_STATUS_SUCCESS;
}

// Interrupt Handler for all SPI Channel
void EPCF_SPI0_INT_HANDLER(void)
{
    uint8_t dummyRead PCF_C_UNUSED_ARG;

    // for write operation
    if(spiChState[0] == __EPCF_SPI_STATE_WRITE)
    {
        if(pcfFifoIsEmpty(spiDevice[0]->spiTxFifo) == enEPCFBoolean_True)
        {
            dummyRead = ((SSP_TypeDef*)(spiDevice[0]->SpiChannelAddr))->DR;
            spiChState[0] = __EPCF_SPI_STATE_IDLE;      // Recovering the Last State of SPI channel
            if(masterMode[0]== enEPCFBoolean_True)
                epcf_gpio_set(spiCsGpioDevice[0][slaveSelectId[0]]);
            return;
        }

        dummyRead = ((SSP_TypeDef*)(spiDevice[0]->SpiChannelAddr))->DR;
        if(masterMode[0]== enEPCFBoolean_True)
            epcf_gpio_set(spiCsGpioDevice[0][slaveSelectId[0]]);

        if(masterMode[0]== enEPCFBoolean_True)
            epcf_gpio_clear(spiCsGpioDevice[0][slaveSelectId[0]]);

        ((SSP_TypeDef*)(spiDevice[0]->SpiChannelAddr))->DR = pcfFifoPop(spiDevice[0]->spiTxFifo);
    }
    else    // for read operation
    {
        pcfFifoPush((spiDevice[0]->spiRxFifo), ((SSP_TypeDef*)(spiDevice[0]->SpiChannelAddr))->DR);
        if(masterMode[0]== enEPCFBoolean_True)
            epcf_gpio_set(spiCsGpioDevice[0][slaveSelectId[0]]);

        // check if TX Buffer is Empty
        if( pcfFifoIsEmpty((spiDevice[0]->spiTxFifo)) != enEPCFBoolean_True )
        {
            if(masterMode[0]== enEPCFBoolean_True)
                epcf_gpio_clear(spiCsGpioDevice[0][slaveSelectId[0]]);

            ((SSP_TypeDef*)(spiDevice[0]->SpiChannelAddr))->DR = pcfFifoPop((spiDevice[0]->spiTxFifo));
        }
        else
        {
            spiChState[0] = __EPCF_SPI_STATE_IDLE;  // Recovering the Last State of SPI channel
        }
    }
}

void EPCF_SPI1_INT_HANDLER(void)
{
    uint8_t dummyRead PCF_C_UNUSED_ARG;

    // for write operation
    if(spiChState[1] == __EPCF_SPI_STATE_WRITE)
    {
        if(pcfFifoIsEmpty(spiDevice[1]->spiTxFifo) == enEPCFBoolean_True)
        {
            dummyRead = ((SSP_TypeDef*)(spiDevice[1]->SpiChannelAddr))->DR;
            spiChState[1] = __EPCF_SPI_STATE_IDLE;      // Recovering the Last State of SPI channel
            if(masterMode[1]== enEPCFBoolean_True)
                epcf_gpio_set(spiCsGpioDevice[1][slaveSelectId[1]]);
            return;
        }

        dummyRead = ((SSP_TypeDef*)(spiDevice[1]->SpiChannelAddr))->DR;
        if(masterMode[1]== enEPCFBoolean_True)
            epcf_gpio_set(spiCsGpioDevice[1][slaveSelectId[1]]);

        if(masterMode[1]== enEPCFBoolean_True)
            epcf_gpio_clear(spiCsGpioDevice[1][slaveSelectId[1]]);

        ((SSP_TypeDef*)(spiDevice[1]->SpiChannelAddr))->DR = pcfFifoPop(spiDevice[1]->spiTxFifo);
    }
    else    // for read operation
    {
        pcfFifoPush((spiDevice[1]->spiRxFifo), ((SSP_TypeDef*)(spiDevice[1]->SpiChannelAddr))->DR);
        if(masterMode[1]== enEPCFBoolean_True)
            epcf_gpio_set(spiCsGpioDevice[1][slaveSelectId[1]]);

        // check if TX Buffer is Empty
        if( pcfFifoIsEmpty((spiDevice[1]->spiTxFifo)) != enEPCFBoolean_True )
        {
            if(masterMode[1]== enEPCFBoolean_True)
                epcf_gpio_clear(spiCsGpioDevice[1][slaveSelectId[1]]);

            ((SSP_TypeDef*)(spiDevice[1]->SpiChannelAddr))->DR = pcfFifoPop((spiDevice[1]->spiTxFifo));
        }
        else
        {
            spiChState[1] = __EPCF_SPI_STATE_IDLE;  // Recovering the Last State of SPI channel
        }
    }
}

