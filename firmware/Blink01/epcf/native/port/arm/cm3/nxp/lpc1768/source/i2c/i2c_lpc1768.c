
#include "pcf.h"
#include <stdlib.h>

#define __EPCF_PRIVATE_I2C_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,i2c/,i2c_hidden.h)
#include  __EPCF_PRIVATE_I2C_H_INCLUDE
#undef __EPCF_PRIVATE_I2C_H_INCLUDE

//Include fifo file
#define __EPCF_UTIL_FIFO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_fifo.h)
#include  __EPCF_UTIL_FIFO_INCLUDE
#undef __EPCF_UTIL_FIFO_INCLUDE

#define __EPCF_UTILS_STRING_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_string.h)
#include  __EPCF_UTILS_STRING_INCLUDE
#undef __EPCF_UTILS_STRING_INCLUDE

#define __I2C_MAX_DEVICE        3
#define __I2C_CLK_DIV           1

/* State codes for I2C communication        */
/* Master mode              */
#define __I2C_M_START                   0x08    /* Start condition transmitted                      */
#define __I2C_M_REP_START               0x10    /* Repeated start condition transmitted             */
#define __I2C_M_ARB_LOST                0x38    /* Arbitration lost                                 */
/* Master transmitter       */
#define __I2C_M_SLA_W_TX_ACK            0x18    /* SLA+W transmitted; ACK received.                 */
#define __I2C_M_SLA_W_TX_NACK           0x20    /* SLA+W transmitted; NOT ACK received.             */
#define __I2C_M_DATA_TX_ACK             0x28    /* Data byte transmitted; ACK received.             */
#define __I2C_M_DATA_TX_NACK            0x30    /* Data byte transmitted; NOT ACK received.         */
/* Master receiver          */
#define __I2C_M_SLA_R_ACK               0x40    /* SLA+R transmitted; ACK received.                 */
#define __I2C_M_SLA_R_NACK              0x48    /* SLA+R transmitted; NOT ACK received.             */
#define __I2C_M_DATA_RX_ACK             0x50    /* Data byte received; ACK returned.                */
#define __I2C_M_DATA_RX_NACK            0x58    /* Data byte received; NOT ACK returned.            */
/* Slave receiver           */
#define __I2C_S_SLA_W_RX_ACK            0x60    /* Own SLA+W received; ACK returned.                                                    */
#define __I2C_S_ARB_LOST_SLA_W_RX       0x68    /* Arbitration lost in SLA+R/W as master; Own SLA+W received, ACK returned.             */
#define __I2C_S_GEN_CALL_RX_ACK         0x70    /* General call address (0x00) has been received; ACK returned.                         */
#define __I2C_S_ARB_LOST_GC_RX          0x78    /* Arbitration lost in SLA+R/W as master; General call address received, ACK returned.  */
#define __I2C_S_SLA_W_DATA_RX_ACK       0x80    /* Previously addressed with own SLA; DATA received; ACK returned.                      */
#define __I2C_S_SLA_W_DATA_RX_NACK      0x88    /* Previously addressed with own SLA; DATA byte received; NOT ACK returned.             */
#define __I2C_S_GC_DATA_RX_ACK          0x90    /* Previously addressed with General Call; DATA byte received; ACK returned.            */
#define __I2C_S_GC_DATA_RX_NACK         0x98    /* Previously addressed with General Call; DATA byte received; NOT ACK returned.        */
#define __I2C_S_STOP_REP_START          0xA0    /* A STOP or Repeated START condition received while still addressed as SLA+R/W.        */
/* Slave transmitter        */
#define __I2C_S_SLA_R_RX_ACK            0xA8    /* Own SLA+R received; ACK returned.                                                    */
#define __I2C_S_ARB_LOST_SLA_R_RX       0xB0    /* Arbitration lost in SLA+R/W as master; Own SLA+R received, ACK returned.             */
#define __I2C_S_DATA_TX_ACK             0xB8    /* Data byte transmitted; ACK received.                                                 */
#define __I2C_S_DATA_TX_NACK            0xC0    /* Data byte transmitted; NOT ACK received.                                             */
#define __I2C_S_LAST_DATA_TX_NACK       0xC8    /* Last data byte transmitted (AA = 0); ACK received.                                   */

/* I2C control bits         */
#define __I2C_AA_FLAG                   (1 << 2)
#define __I2C_INT_FLAG                  (1 << 3)
#define __I2C_STOP_FLAG                 (1 << 4)
#define __I2C_START_FLAG                (1 << 5)
#define __I2C_EN_FLAG                   (1 << 6)

#define __I2C_SET_CTRL_BIT(CH_ADDRESS, BIT)         (CH_ADDRESS->I2CONSET = BIT)
#define __I2C_CLR_CTRL_BIT(CH_ADDRESS, BIT)         (CH_ADDRESS->I2CONCLR = BIT)
#define __I2C_GET_STATE(CH_ADDRESS)                 (CH_ADDRESS->STAT >> 3)

#define __I2C_SET_AA(CH_ADDRESS)                __I2C_SET_CTRL_BIT(CH_ADDRESS,__I2C_AA_FLAG)
#define __I2C_CLR_AA(CH_ADDRESS)                __I2C_CLR_CTRL_BIT(CH_ADDRESS,__I2C_AA_FLAG)

#define __I2C_SET_START(CH_ADDRESS)             __I2C_SET_CTRL_BIT(CH_ADDRESS,__I2C_START_FLAG)
#define __I2C_CLR_START(CH_ADDRESS)             __I2C_CLR_CTRL_BIT(CH_ADDRESS,__I2C_START_FLAG)

#define __I2C_SET_STOP(CH_ADDRESS)              __I2C_SET_CTRL_BIT(CH_ADDRESS,__I2C_STOP_FLAG)
#define __I2C_CLR_STOP(CH_ADDRESS)              __I2C_CLR_CTRL_BIT(CH_ADDRESS,__I2C_STOP_FLAG)

#define __I2C_CLR_INT(CH_ADDRESS)               __I2C_CLR_CTRL_BIT(CH_ADDRESS,__I2C_INT_FLAG)

// Lookup tables.
static uint32_t i2cIrqNum[__I2C_MAX_DEVICE] = {IRQ_NUM(I2C0_CH),IRQ_NUM(I2C1_CH),IRQ_NUM(I2C2_CH)};
static uint32_t pwrI2cCh[__I2C_MAX_DEVICE]  = {PWR_I2C_CH(I2C0_CH),PWR_I2C_CH(I2C1_CH),PWR_I2C_CH(I2C2_CH)};
static uint32_t pdivClkI2cCh[__I2C_MAX_DEVICE]  = {PCLK_DIV(I2C0_CH),PCLK_DIV(I2C1_CH),PCLK_DIV(I2C2_CH)};
static uint32_t i2cChannelAddr[__I2C_MAX_DEVICE] = {I2C0_BASE,I2C1_BASE,I2C2_BASE};

/*
 * Below variable i2cAltFunction
 * Row 1 -> Port 0
 */
static const uint8_t i2cAltFunction[1][32] =
{
 //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
  {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}
};
// Lookup tables ends

// Static Variable Declaration
static uint32_t  i2cDeviceCount = __I2C_MAX_DEVICE;
static EPCFI2cDevice_t* i2cDevice[__I2C_MAX_DEVICE];
static EnEPCFBoolean_t i2cChInit[__I2C_MAX_DEVICE] = {enEPCFBoolean_False};
static uint8_t *i2cTxBuffer, *i2cRxBuffer;
static uint8_t i2cSlaveAddress=0;
static volatile uint32_t i2cBytesToRead=0;
static volatile uint32_t i2cBytesRead=0;

static EnEPCFBoolean_t i2cChannelError[__I2C_MAX_DEVICE] = {enEPCFBoolean_False};
static EnEPCFBoolean_t i2cChannelBusy[__I2C_MAX_DEVICE] = {enEPCFBoolean_False};
static EnEPCFBoolean_t i2cBusRelease[__I2C_MAX_DEVICE] = {enEPCFBoolean_False};

// Static Function Declaration
static int8_t __epcfI2cInit(EPCFI2cDevice_t* pI2cDevice, EPCFI2cCfg_t* pConfig);
static void __epcfI2cDataProcessing(EPCFI2cDevice_t* pI2cDevice,uint8_t *data, uint32_t size);

// Function Defination
int8_t epcf_i2c_nativeInit(EPCFI2cDevice_t* pI2cDevice, EPCFI2cCfg_t* pConfig)
{
    int8_t status = EPCF_STATUS_SUCCESS;
    EPCFPinCfg_t i2cPinCfg;

    pI2cDevice->i2cId = pConfig->i2cId;
    pI2cDevice->interruptEnable = pConfig->interruptEnable;
    pI2cDevice->i2cChannelAddr = (I2C_TypeDef*)i2cChannelAddr[pConfig->i2cId];

    i2cDevice[pConfig->i2cId] = pI2cDevice;

    // Hardware configuration
    i2cPinCfg.direction    = 0; // enEPCFGpioDirInput
    i2cPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
    i2cPinCfg.openDrain    = 0; // open Drain disable
    i2cPinCfg.portPin.port = ((EPCFI2cLpc1768Cfg_t*)(pConfig->hardwareCfg))->i2cSDAPin.port;
    i2cPinCfg.portPin.pin  = ((EPCFI2cLpc1768Cfg_t*)(pConfig->hardwareCfg))->i2cSDAPin.pin;

    i2cPinCfg.altFunction = i2cAltFunction[i2cPinCfg.portPin.port][i2cPinCfg.portPin.pin];

    status = epcfPinInit(&i2cPinCfg);
    if(status != EPCF_STATUS_SUCCESS)
      return EPCF_STATUS_ERROR;

    i2cPinCfg.direction    = 1; // enEPCFGpioDirOutput
    i2cPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
    i2cPinCfg.openDrain    = 0; // open Drain disable
    i2cPinCfg.portPin.port = ((EPCFI2cLpc1768Cfg_t*)(pConfig->hardwareCfg))->i2cSCLPin.port;
    i2cPinCfg.portPin.pin  = ((EPCFI2cLpc1768Cfg_t*)(pConfig->hardwareCfg))->i2cSCLPin.pin;

    i2cPinCfg.altFunction = i2cAltFunction[i2cPinCfg.portPin.port][i2cPinCfg.portPin.pin];

    status = epcfPinInit(&i2cPinCfg);
    if(status != EPCF_STATUS_SUCCESS)
      return EPCF_STATUS_ERROR;

    status = __epcfI2cInit(pI2cDevice, pConfig);
    if(status != EPCF_STATUS_SUCCESS)
        return EPCF_STATUS_ERROR;

    i2cDeviceCount--;
    return EPCF_STATUS_SUCCESS;
}

static int8_t __epcfI2cInit(EPCFI2cDevice_t* pI2cDevice, EPCFI2cCfg_t* pConfig)
{
    uint32_t i2cPclk,temp;
    uint8_t dummyRead;

    // power on PWM peripheral
    POWER_ON(pwrI2cCh[pConfig->i2cId]);
    // set peripheral clock divider
    epcfNativeSysSetPclkDiv(NULL, pdivClkI2cCh[pConfig->i2cId], __I2C_CLK_DIV);

    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2CONCLR = __I2C_INT_FLAG|__I2C_START_FLAG|__I2C_AA_FLAG|__I2C_EN_FLAG;

    if(pConfig->generalCallEnable == enEPCFBoolean_True)
        ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2ADR0 |= 0x01;

    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2ADR0 =  pConfig->ownAddress[0]<<1;
    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2ADR1 =  pConfig->ownAddress[1]<<1;
    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2ADR2 =  pConfig->ownAddress[2]<<1;
    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2ADR3 =  pConfig->ownAddress[3]<<1;

    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2MASK0 = pConfig->ownAddressMask[0];
    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2MASK1 = pConfig->ownAddressMask[1];
    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2MASK2 = pConfig->ownAddressMask[2];
    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2MASK3 = pConfig->ownAddressMask[3];

    // Set baudrate
    i2cPclk = epcfNativeSysGetPclk(NULL,pdivClkI2cCh[pConfig->i2cId]);
    temp = i2cPclk / pConfig->baudrate;
    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2SCLH = temp/2;
    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2SCLL = temp - ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2SCLH;

    if(pConfig->interruptEnable == enEPCFBoolean_True)
    {
        // Rx & Tx buffer initialization
        i2cTxBuffer = (uint8_t*)malloc(pConfig->txBufferSize);
        i2cRxBuffer = (uint8_t*)malloc(pConfig->rxBufferSize);

        pcfMemSet(i2cTxBuffer, 0, pConfig->txBufferSize);
        pcfMemSet(i2cRxBuffer, 0, pConfig->rxBufferSize);

        // Fifo Initialization
        pI2cDevice->i2cTxFifo = pcfFifoInit(i2cTxBuffer, pConfig->txBufferSize);
          if(pI2cDevice->i2cTxFifo == NULL)    // EPCF_STATUS_SUCCESS
              return EPCF_STATUS_ERROR;

        pI2cDevice->i2cRxFifo = pcfFifoInit(i2cRxBuffer, pConfig->rxBufferSize);
          if(pI2cDevice->i2cRxFifo == NULL) //EPCF_STATUS_SUCCESS
              return EPCF_STATUS_ERROR;

          NVIC_EnableIRQ(i2cIrqNum[pConfig->i2cId]);
    }

    //Enable ACK
    __I2C_SET_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
    // Enable I2C
    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2CONSET = __I2C_EN_FLAG;

    dummyRead = ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2DAT;    // dummyRead
    i2cChInit[pConfig->i2cId] = enEPCFBoolean_True;
    return EPCF_STATUS_SUCCESS;
}

static void __epcfI2cDataProcessing(EPCFI2cDevice_t* pI2cDevice,uint8_t *data, uint32_t size)
{
    uint8_t status;
    uint32_t index=0;

    while(1)
    {
        while(!(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2CONSET & __I2C_INT_FLAG));
        status = ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2STAT;

        switch(status)
        {
//
// Master mode
//
            case __I2C_M_START:
            case __I2C_M_REP_START:
                    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2DAT = i2cSlaveAddress;
                    __I2C_CLR_START(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                break;
//
// Master transmitter
//
            case __I2C_M_SLA_W_TX_ACK:
            case __I2C_M_DATA_TX_ACK:
                    if( index < size )
                    {
                        ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2DAT = *(data + index);
                            index++;
                    }
                    else
                    {
                        if(i2cBusRelease[pI2cDevice->i2cId] == enEPCFBoolean_True)
                        {
                            __I2C_SET_STOP(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                        }
                        __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                        i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                        return;
                    }
                break;

//
// Master transmitter error conditions
//
            case __I2C_M_ARB_LOST:
            case __I2C_M_SLA_W_TX_NACK:
                    __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));

                    __I2C_SET_STOP(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                    return;
                break;

            case __I2C_M_DATA_TX_NACK:
                if(index == size)
                {
                    if(i2cBusRelease[pI2cDevice->i2cId] == enEPCFBoolean_True)
                    {
                        __I2C_SET_STOP(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    }
                    __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                    return;
                }
                else
                {
                    if(i2cBusRelease[pI2cDevice->i2cId] == enEPCFBoolean_True)
                    {
                        __I2C_SET_STOP(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    }
                    __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                    return;
                }
            break;
//
// Master receiver
//
            case __I2C_M_SLA_R_NACK:
                    __I2C_SET_STOP(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                    return;
                break;

            case __I2C_M_SLA_R_ACK:
                break;

            case __I2C_M_DATA_RX_ACK:
                    *(data + index) = ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2DAT;
                    index++;
                    i2cBytesRead++;

                    if(i2cBytesRead >= i2cBytesToRead-1)
                    {
                        __I2C_CLR_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    }
                break;


            case __I2C_M_DATA_RX_NACK:
                    __I2C_SET_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    *(data + index) = ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2DAT;
                    i2cBytesRead++;
                    index++;
                    if(i2cBusRelease[pI2cDevice->i2cId] == enEPCFBoolean_True)
                    {
                        __I2C_SET_STOP(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    }
                    __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                    return;
            break;

//
// Slave receiver
//
            case __I2C_S_SLA_W_RX_ACK:
            case __I2C_S_ARB_LOST_SLA_W_RX:
            case __I2C_S_GEN_CALL_RX_ACK:
            case __I2C_S_ARB_LOST_GC_RX:
            case __I2C_S_STOP_REP_START:
                break;

            case __I2C_S_SLA_W_DATA_RX_ACK:
            case __I2C_S_GC_DATA_RX_ACK:
                *(data + index) = ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2DAT;
                index++;
                i2cBytesRead++;
                if(i2cBytesRead == i2cBytesToRead)//change
                {
                    __I2C_CLR_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                    return;
                }
            break;

            case __I2C_S_SLA_W_DATA_RX_NACK:
            case __I2C_S_GC_DATA_RX_NACK:
                __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                return;
            break;

//
// Slave transmitter
//
            case __I2C_S_SLA_R_RX_ACK:
            case __I2C_S_ARB_LOST_SLA_R_RX:
            case __I2C_S_DATA_TX_ACK:
                if( index < size )
                {
                    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2DAT = *(data + index);
                    index++;
                }
                else
                {
                    ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr))->I2DAT = 0;
                    __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                    i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                    return;
                }
            break;

            case __I2C_S_DATA_TX_NACK:
            case __I2C_S_LAST_DATA_TX_NACK:
                __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                return;
            break;

            default:
                __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
                i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_False;
                return;
            break;
        }

    __I2C_CLR_INT(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
    }

}

int8_t epcf_i2c_nativeIntEnable(EPCFI2cDevice_t* pI2cDevice)
{
    if(i2cChInit[pI2cDevice->i2cId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;
    NVIC_EnableIRQ(i2cIrqNum[pI2cDevice->i2cId]);
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_i2c_nativeIntDisable(EPCFI2cDevice_t* pI2cDevice)
{
    if(i2cChInit[pI2cDevice->i2cId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;
    NVIC_DisableIRQ(i2cIrqNum[pI2cDevice->i2cId]);
    return EPCF_STATUS_SUCCESS;
}

int32_t epcf_i2c_nativeWrite(EPCFI2cDevice_t* pI2cDevice,EnEPCFBoolean_t masterEnable,uint8_t slaveAddress,const uint8_t* data,uint32_t size,EnEPCFBoolean_t busRelease,EPCFTime_t timeout)
{
    uint32_t index;

    if(i2cChInit[pI2cDevice->i2cId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_True;

//Interrupt Mode
    if(pI2cDevice->interruptEnable == enEPCFBoolean_True)
    {
        for(index = 0; index < size; index++)
        {
            pcfFifoPush(pI2cDevice->i2cTxFifo,*(data+index));
        }
        if(masterEnable == enEPCFBoolean_True)
        {
            i2cBusRelease[pI2cDevice->i2cId] = busRelease;
            i2cSlaveAddress = (uint8_t)(slaveAddress << 1);
            __I2C_CLR_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
            __I2C_SET_START(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
        }
        else
            __I2C_SET_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));

        while(i2cChannelBusy[pI2cDevice->i2cId] == enEPCFBoolean_True);

        if(i2cChannelError[pI2cDevice->i2cId] == enEPCFBoolean_True)
        {
            i2cChannelError[pI2cDevice->i2cId] = enEPCFBoolean_False;
            return EPCF_STATUS_ERROR;
        }
    }
//Polling Mode
    else
    {
        if(masterEnable == enEPCFBoolean_True)
        {
            i2cBusRelease[pI2cDevice->i2cId] = busRelease;
            i2cSlaveAddress = (uint8_t)(slaveAddress << 1);
            __I2C_CLR_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
            __I2C_SET_START(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
        }
        else
            __I2C_SET_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));

        do{
            __epcfI2cDataProcessing(pI2cDevice,data, size);
        }while(i2cChannelBusy[pI2cDevice->i2cId] == enEPCFBoolean_True);
    }

    return EPCF_STATUS_SUCCESS;
}

int32_t epcf_i2c_nativeRead(EPCFI2cDevice_t* pI2cDevice,EnEPCFBoolean_t masterEnable,uint8_t slaveAddress,uint8_t* data,uint32_t size,EnEPCFBoolean_t busRelease,EPCFTime_t timeout)
{
    uint32_t ind, byteRead;

    if(i2cChInit[pI2cDevice->i2cId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    i2cChannelBusy[pI2cDevice->i2cId] = enEPCFBoolean_True;
    i2cBytesToRead = size;

//Interrupt Mode
	if(pI2cDevice->interruptEnable == enEPCFBoolean_True)
	{
	    if(masterEnable == enEPCFBoolean_True)
	    {
	        i2cBusRelease[pI2cDevice->i2cId] = busRelease;
	        i2cSlaveAddress = (uint8_t)(slaveAddress << 1);
	        i2cSlaveAddress |= 0x01;    // Master Read
	        if(size > 1)
	            __I2C_SET_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
	        else
	            __I2C_CLR_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));

	        __I2C_SET_START(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));

	        while(i2cChannelBusy[pI2cDevice->i2cId] == enEPCFBoolean_True);
	    }
	    else
	        __I2C_SET_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));

	    for(ind = 0; ind < size; ind++)
	    {
	        if(pcfFifoIsEmpty(pI2cDevice->i2cRxFifo) == enEPCFBoolean_True)
	            break;
	        *(data + ind) = pcfFifoPop(pI2cDevice->i2cRxFifo);
	    }
	    if(masterEnable == enEPCFBoolean_True)
	    {
	        byteRead = i2cBytesRead;
	        i2cBytesRead = 0;
	    }
	    else
	        byteRead = ind;

	    if(i2cChannelError[pI2cDevice->i2cId] == enEPCFBoolean_True)
	    {
	        i2cChannelError[pI2cDevice->i2cId] = enEPCFBoolean_False;
	        return EPCF_STATUS_ERROR;
	    }
	}
//Polling Mode
	else
	{
	    if(masterEnable == enEPCFBoolean_True)
	    {
	        i2cBusRelease[pI2cDevice->i2cId] = busRelease;
	        i2cSlaveAddress = (uint8_t)(slaveAddress << 1);
	        i2cSlaveAddress |= 0x01;    // Master Read
	        if(size > 1)
	            __I2C_SET_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
	        else
	            __I2C_CLR_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
	        __I2C_SET_START(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));
	    }
	    else
	        __I2C_SET_AA(((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)));

	    do{
	        __epcfI2cDataProcessing(pI2cDevice,data, size);
	    }while(i2cChannelBusy[pI2cDevice->i2cId] == enEPCFBoolean_True);
	    byteRead = i2cBytesRead;
	    i2cBytesRead = 0;
	}
    return byteRead;
}

int32_t epcf_i2c_nativeGetRxBufferCount(EPCFI2cDevice_t* pI2cDevice)
{
    if(i2cChInit[pI2cDevice->i2cId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    return pcfFifoCount(pI2cDevice->i2cRxFifo);
}

int8_t epcf_i2c_nativeRxBufferFlush(EPCFI2cDevice_t* pI2cDevice)
{
    if(i2cChInit[pI2cDevice->i2cId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    pcfFifoFlush(pI2cDevice->i2cRxFifo);
    return EPCF_STATUS_SUCCESS;
}

int32_t epcf_i2c_nativeGetTxBufferCount(EPCFI2cDevice_t* pI2cDevice)
{
    if(i2cChInit[pI2cDevice->i2cId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    return pcfFifoCount(pI2cDevice->i2cTxFifo);
}

int8_t epcf_i2c_nativeTxBufferFlush(EPCFI2cDevice_t* pI2cDevice)
{
    if(i2cChInit[pI2cDevice->i2cId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    pcfFifoFlush(pI2cDevice->i2cTxFifo);
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_i2c_nativeClose(EPCFI2cDevice_t* pI2cDevice)
{
    if(i2cChInit[pI2cDevice->i2cId] != enEPCFBoolean_True)
        return EPCF_STATUS_ERROR;

    __I2C_CLR_CTRL_BIT( ((I2C_TypeDef*)(pI2cDevice->i2cChannelAddr)), __I2C_EN_FLAG);
    POWER_OFF(pwrI2cCh[pI2cDevice->i2cId]);
    return EPCF_STATUS_SUCCESS;
}

uint8_t epcf_i2c_nativeGetDeviceCount()
{
    return i2cDeviceCount;
}

void I2C0_INT_HANDLER(void)
{
    uint8_t status=0;

    status = ((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr))->I2STAT;
    switch(status)
    {
        //
        // Master mode
        //
        case __I2C_M_START:
        case __I2C_M_REP_START:
            ((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr))->I2DAT = i2cSlaveAddress;
            __I2C_CLR_START(((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr)));
            break;
        //
        // Master transmitter
        //
        case __I2C_M_SLA_W_TX_ACK:
        case __I2C_M_DATA_TX_ACK:
            if(pcfFifoIsEmpty(i2cDevice[0]->i2cTxFifo) != enEPCFBoolean_True)
            {
                ((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr))->I2DAT = pcfFifoPop(i2cDevice[0]->i2cTxFifo);
            }
            else
            {
                i2cChannelError[i2cDevice[0]->i2cId]= enEPCFBoolean_False;
                i2cChannelBusy[i2cDevice[0]->i2cId] = enEPCFBoolean_False;
                if(i2cBusRelease[i2cDevice[0]->i2cId] == enEPCFBoolean_True)
                {
                    __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr)));
                }
            }
            break;

        //
        // Master transmitter error conditions
        //
        case __I2C_M_ARB_LOST:
        case __I2C_M_SLA_W_TX_NACK:
        case __I2C_M_DATA_TX_NACK:
            if(pcfFifoIsEmpty(i2cDevice[0]->i2cTxFifo) == enEPCFBoolean_True)
            {
                i2cChannelError[i2cDevice[0]->i2cId] = enEPCFBoolean_True;
            }
            else
            {
                i2cChannelError[i2cDevice[0]->i2cId] = enEPCFBoolean_True;
            }
            pcfFifoFlush(i2cDevice[0]->i2cTxFifo);
            i2cChannelBusy[i2cDevice[0]->i2cId] = enEPCFBoolean_False;
            if(i2cBusRelease[i2cDevice[0]->i2cId] == enEPCFBoolean_True)
            {
                __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr)));
            }
            break;

        //
        // Master reciever
        //
        case __I2C_M_SLA_R_NACK:
            i2cChannelError[i2cDevice[0]->i2cId] = enEPCFBoolean_True;
            i2cChannelBusy[i2cDevice[0]->i2cId] = enEPCFBoolean_False;
            __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr)));
            break;

        case __I2C_M_SLA_R_ACK:
            break;

        case __I2C_M_DATA_RX_ACK:
            pcfFifoPush(i2cDevice[0]->i2cRxFifo,((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr))->I2DAT);
            i2cBytesRead++;
            if(i2cBytesRead >= i2cBytesToRead -1)
            {
                __I2C_CLR_AA(((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr)));
            }
            break;

        case __I2C_M_DATA_RX_NACK:
            pcfFifoPush(i2cDevice[0]->i2cRxFifo,((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr))->I2DAT);
            i2cBytesRead++;
            i2cChannelError[i2cDevice[0]->i2cId] = enEPCFBoolean_False;
            i2cChannelBusy[i2cDevice[0]->i2cId] = enEPCFBoolean_False;
            if(i2cBusRelease[i2cDevice[0]->i2cId] == enEPCFBoolean_True)
            {
                __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr)));
            }
            break;

        //
        // Slave receiver
        //
        case __I2C_S_SLA_W_RX_ACK:
        case __I2C_S_ARB_LOST_SLA_W_RX:
        case __I2C_S_GEN_CALL_RX_ACK:
        case __I2C_S_ARB_LOST_GC_RX:
        case __I2C_S_STOP_REP_START:
            break;

        case __I2C_S_SLA_W_DATA_RX_ACK:
        case __I2C_S_GC_DATA_RX_ACK:
        case __I2C_S_SLA_W_DATA_RX_NACK:
        case __I2C_S_GC_DATA_RX_NACK:
            pcfFifoPush(i2cDevice[0]->i2cRxFifo,((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr))->I2DAT);
            break;

        //
        // Slave trasmitter
        //
        case __I2C_S_SLA_R_RX_ACK:
        case __I2C_S_ARB_LOST_SLA_R_RX:
        case __I2C_S_DATA_TX_ACK:
            if(pcfFifoIsEmpty(i2cDevice[0]->i2cTxFifo) != enEPCFBoolean_True)
            {
                ((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr))->I2DAT = pcfFifoPop(i2cDevice[0]->i2cTxFifo);
            }
            else
            {
                ((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr))->I2DAT = 0;
            }
            break;

        case __I2C_S_DATA_TX_NACK:
        case __I2C_S_LAST_DATA_TX_NACK:
            i2cChannelError[i2cDevice[0]->i2cId] = enEPCFBoolean_False;
            i2cChannelBusy[i2cDevice[0]->i2cId] = enEPCFBoolean_False;
            break;

        default:
            i2cChannelError[i2cDevice[0]->i2cId] = enEPCFBoolean_True;
            i2cChannelBusy[i2cDevice[0]->i2cId] = enEPCFBoolean_False;
            break;
    }
    __I2C_CLR_INT(((I2C_TypeDef*)(i2cDevice[0]->i2cChannelAddr)));
}

void I2C1_INT_HANDLER(void)
{
    uint8_t  status=0;

    status = ((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr))->I2STAT;
    switch(status)
    {
        //
        // Master mode
        //
        case __I2C_M_START:
        case __I2C_M_REP_START:
            ((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr))->I2DAT = i2cSlaveAddress;
            __I2C_CLR_START(((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr)));
            break;
        //
        // Master transmitter
        //
        case __I2C_M_SLA_W_TX_ACK:
        case __I2C_M_DATA_TX_ACK:
            if(pcfFifoIsEmpty(i2cDevice[1]->i2cTxFifo) != enEPCFBoolean_True)
            {
                ((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr))->I2DAT = pcfFifoPop(i2cDevice[1]->i2cTxFifo);
            }
            else
            {
                i2cChannelError[i2cDevice[1]->i2cId] = enEPCFBoolean_False;
                i2cChannelBusy[i2cDevice[1]->i2cId] = enEPCFBoolean_False;
                if(i2cBusRelease[i2cDevice[1]->i2cId] == enEPCFBoolean_True)
                {
                    __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr)));
                }
            }
            break;

        //
        // Master transmitter error conditions
        //
        case __I2C_M_ARB_LOST:
        case __I2C_M_SLA_W_TX_NACK:
        case __I2C_M_DATA_TX_NACK:
            if(pcfFifoIsEmpty(i2cDevice[1]->i2cTxFifo) == enEPCFBoolean_True)
            {
                i2cChannelError[i2cDevice[1]->i2cId] = enEPCFBoolean_True;
            }
            else
            {
                i2cChannelError[i2cDevice[1]->i2cId] = enEPCFBoolean_True;
            }
            pcfFifoFlush(i2cDevice[1]->i2cTxFifo);
            i2cChannelBusy[i2cDevice[1]->i2cId] = enEPCFBoolean_False;
            if(i2cBusRelease[i2cDevice[1]->i2cId] == enEPCFBoolean_True)
            {
                __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr)));
            }
            break;

        //
        // Master reciever
        //
        case __I2C_M_SLA_R_NACK:
            i2cChannelError[i2cDevice[1]->i2cId] = enEPCFBoolean_True;
            i2cChannelBusy[i2cDevice[1]->i2cId] = enEPCFBoolean_False;
            __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr)));
            break;

        case __I2C_M_SLA_R_ACK:
            break;

        case __I2C_M_DATA_RX_ACK:
            pcfFifoPush(i2cDevice[1]->i2cRxFifo,((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr))->I2DAT);
            i2cBytesRead++;
            if(i2cBytesRead >= i2cBytesToRead -1)
            {
                __I2C_CLR_AA(((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr)));
            }
            break;

        case __I2C_M_DATA_RX_NACK:
            pcfFifoPush(i2cDevice[1]->i2cRxFifo,((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr))->I2DAT);
            i2cBytesRead++;
            i2cChannelError[i2cDevice[1]->i2cId] = enEPCFBoolean_False;
            i2cChannelBusy[i2cDevice[1]->i2cId] = enEPCFBoolean_False;
            if(i2cBusRelease[i2cDevice[1]->i2cId] == enEPCFBoolean_True)
            {
                __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr)));
            }
            break;

        //
        // Slave receiver
        //
        case __I2C_S_SLA_W_RX_ACK:
        case __I2C_S_ARB_LOST_SLA_W_RX:
        case __I2C_S_GEN_CALL_RX_ACK:
        case __I2C_S_ARB_LOST_GC_RX:
        case __I2C_S_STOP_REP_START:
            break;

        case __I2C_S_SLA_W_DATA_RX_ACK:
        case __I2C_S_GC_DATA_RX_ACK:
        case __I2C_S_SLA_W_DATA_RX_NACK:
        case __I2C_S_GC_DATA_RX_NACK:
            pcfFifoPush(i2cDevice[1]->i2cRxFifo,((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr))->I2DAT);
            break;

        //
        // Slave trasmitter
        //
        case __I2C_S_SLA_R_RX_ACK:
        case __I2C_S_ARB_LOST_SLA_R_RX:
        case __I2C_S_DATA_TX_ACK:
            if(pcfFifoIsEmpty(i2cDevice[1]->i2cTxFifo) != enEPCFBoolean_True)
                ((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr))->I2DAT = pcfFifoPop(i2cDevice[1]->i2cTxFifo);
            else
                ((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr))->I2DAT = 0;
            break;

        case __I2C_S_DATA_TX_NACK:
        case __I2C_S_LAST_DATA_TX_NACK:
            i2cChannelError[i2cDevice[1]->i2cId] = enEPCFBoolean_False;
            i2cChannelBusy[i2cDevice[1]->i2cId] = enEPCFBoolean_False;
            break;

        default:
            i2cChannelError[i2cDevice[1]->i2cId] = enEPCFBoolean_True;
            i2cChannelBusy[i2cDevice[1]->i2cId] = enEPCFBoolean_False;
            break;
    }
    __I2C_CLR_INT(((I2C_TypeDef*)(i2cDevice[1]->i2cChannelAddr)));
}

void I2C2_INT_HANDLER(void)
{
    uint8_t  status=0;

    status = ((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr))->I2STAT;
    switch(status)
    {
        //
        // Master mode
        //
        case __I2C_M_START:
        case __I2C_M_REP_START:
            ((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr))->I2DAT = i2cSlaveAddress;
            __I2C_CLR_START(((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr)));
            break;
        //
        // Master transmitter
        //
        case __I2C_M_SLA_W_TX_ACK:
        case __I2C_M_DATA_TX_ACK:
            if(pcfFifoIsEmpty(i2cDevice[2]->i2cTxFifo) != enEPCFBoolean_True)
            {
                ((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr))->I2DAT = pcfFifoPop(i2cDevice[2]->i2cTxFifo);
            }
            else
            {
                i2cChannelError[i2cDevice[2]->i2cId] = enEPCFBoolean_False;
                i2cChannelBusy[i2cDevice[2]->i2cId] = enEPCFBoolean_False;
                if(i2cBusRelease[i2cDevice[2]->i2cId] == enEPCFBoolean_True)
                {
                    __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr)));
                }
            }
            break;

        //
        // Master transmitter error conditions
        //
        case __I2C_M_ARB_LOST:
        case __I2C_M_SLA_W_TX_NACK:
        case __I2C_M_DATA_TX_NACK:
            if(pcfFifoIsEmpty(i2cDevice[2]->i2cTxFifo) == enEPCFBoolean_True)
            {
                i2cChannelError[i2cDevice[2]->i2cId] = enEPCFBoolean_True;
            }
            else
            {
                i2cChannelError[i2cDevice[2]->i2cId] = enEPCFBoolean_True;
            }
            pcfFifoFlush(i2cDevice[2]->i2cTxFifo);
            i2cChannelBusy[i2cDevice[2]->i2cId] = enEPCFBoolean_False;
            if(i2cBusRelease[i2cDevice[2]->i2cId] == enEPCFBoolean_True)
            {
                __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr)));
            }
            break;

        //
        // Master reciever
        //
        case __I2C_M_SLA_R_NACK:
            i2cChannelError[i2cDevice[2]->i2cId] = enEPCFBoolean_True;
            i2cChannelBusy[i2cDevice[2]->i2cId] = enEPCFBoolean_False;
            __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr)));
            break;

        case __I2C_M_SLA_R_ACK:
            break;

        case __I2C_M_DATA_RX_ACK:
            pcfFifoPush(i2cDevice[2]->i2cRxFifo,((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr))->I2DAT);
            i2cBytesRead++;
            if(i2cBytesRead >= i2cBytesToRead -1)
            {
                __I2C_CLR_AA(((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr)));
            }
            break;

        case __I2C_M_DATA_RX_NACK:
            pcfFifoPush(i2cDevice[2]->i2cRxFifo,((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr))->I2DAT);
            i2cBytesRead++;
            i2cChannelError[i2cDevice[2]->i2cId] = enEPCFBoolean_False;
            i2cChannelBusy[i2cDevice[2]->i2cId] = enEPCFBoolean_False;
            if(i2cBusRelease[i2cDevice[2]->i2cId] == enEPCFBoolean_True)
            {
                __I2C_SET_STOP(((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr)));
            }
            break;

        //
        // Slave receiver
        //
        case __I2C_S_SLA_W_RX_ACK:
        case __I2C_S_ARB_LOST_SLA_W_RX:
        case __I2C_S_GEN_CALL_RX_ACK:
        case __I2C_S_ARB_LOST_GC_RX:
        case __I2C_S_STOP_REP_START:
            break;

        case __I2C_S_SLA_W_DATA_RX_ACK:
        case __I2C_S_GC_DATA_RX_ACK:
        case __I2C_S_SLA_W_DATA_RX_NACK:
        case __I2C_S_GC_DATA_RX_NACK:
            pcfFifoPush(i2cDevice[2]->i2cRxFifo,((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr))->I2DAT);
            break;

        //
        // Slave trasmitter
        //
        case __I2C_S_SLA_R_RX_ACK:
        case __I2C_S_ARB_LOST_SLA_R_RX:
        case __I2C_S_DATA_TX_ACK:
            if(pcfFifoIsEmpty(i2cDevice[2]->i2cTxFifo) != enEPCFBoolean_True)
            {
                ((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr))->I2DAT = pcfFifoPop(i2cDevice[2]->i2cTxFifo);
            }
            else
            {
                ((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr))->I2DAT = 0;
            }
            break;

        case __I2C_S_DATA_TX_NACK:
        case __I2C_S_LAST_DATA_TX_NACK:
            i2cChannelError[i2cDevice[2]->i2cId] = enEPCFBoolean_False;
            i2cChannelBusy[i2cDevice[2]->i2cId] = enEPCFBoolean_False;
            break;

        default:
            i2cChannelError[i2cDevice[2]->i2cId] = enEPCFBoolean_True;
            i2cChannelBusy[i2cDevice[2]->i2cId] = enEPCFBoolean_False;
            break;
    }
    __I2C_CLR_INT(((I2C_TypeDef*)(i2cDevice[2]->i2cChannelAddr)));
}

