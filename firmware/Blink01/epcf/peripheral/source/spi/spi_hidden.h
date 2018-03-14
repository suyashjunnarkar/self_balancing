/**
 * \file    spi_hidden.h
 * \brief   hidden header file for SPI Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *          It contains SpiDevice and SpiController structure definition.
 *
 */

#ifndef __EPCF_INCLUDE_PRIVATE_SPI_SPI_HIDDEN_H
#define __EPCF_INCLUDE_PRIVATE_SPI_SPI_HIDDEN_H
typedef struct EPCFSpiController     EPCFSpiController_t;
typedef struct EPCFSpiDevice         EPCFSpiDevice_t;
typedef struct EPCFAdapter           EPCFAdapter_t;

typedef int8_t (*epcfSpiInit_fp)(EPCFSpiDevice_t*, EPCFSpiCfg_t*);
typedef int8_t (*epcfSpiRegisterSlaveDevice_fp)(EPCFSpiDevice_t* ,EPCFPortPin_t );
typedef int8_t (*epcfSpiDeRegisterSlaveDevice_fp)(EPCFSpiDevice_t* ,uint8_t );
typedef int8_t (*epcfSpiSlaveSelect_fp)(EPCFSpiDevice_t* , uint8_t );
typedef int8_t (*epcfSpiSlaveDeSelect_fp)(EPCFSpiDevice_t* , uint8_t );
typedef int8_t (*epcfSpiExchange_fp)(EPCFSpiDevice_t* ,uint16_t ,uint16_t* ,EPCFTime_t );
typedef int32_t (*epcfSpiWrite_fp)(EPCFSpiDevice_t* ,const uint8_t* ,uint32_t ,EPCFTime_t );
typedef int32_t (*epcfSpiRead_fp)(EPCFSpiDevice_t* ,uint8_t* ,uint32_t,EPCFTime_t );
typedef int32_t (*epcfSpiGetRxBufferCount_fp)(EPCFSpiDevice_t* );
typedef int8_t (*epcfSpiRxBufferFlush_fp)(EPCFSpiDevice_t* );
typedef int32_t (*epcfSpiGetTxBufferCount_fp)(EPCFSpiDevice_t* );
typedef int8_t (*epcfSpiTxBufferFlush_fp)(EPCFSpiDevice_t* );
typedef int8_t (*epcfSpiIntEnable_fp)(EPCFSpiDevice_t* ,EnEPCFSpiIntType );
typedef int8_t (*epcfSpiIntDisable_fp)(EPCFSpiDevice_t*  , EnEPCFSpiIntType );
typedef int8_t (*epcfSpiClose_fp)(EPCFSpiDevice_t* );
typedef uint8_t (*epcfSpiGetDeviceCount_fp)(EPCFSpiController_t* pSpiController);


typedef struct EPCFSpiDevice
{
    EPCFSpiController_t*    controllerConfig;
    uint8_t                 spiId;
    void*                   SpiChannelAddr;
    PCFFifoDesc_t           *spiTxFifo;
    PCFFifoDesc_t           *spiRxFifo;
    EnEPCFSpiBitOrder_t     bitOrder;
    EnEPCFBoolean_t         interruptEnable;         
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedSpiDeviceId;         // ID Returned from the Device.
#endif
}EPCFSpiDevice_t;

typedef struct EPCFSpiController
{
    epcfSpiInit_fp                      spiInit;
    epcfSpiRegisterSlaveDevice_fp       spiRegisterSlave;
    epcfSpiDeRegisterSlaveDevice_fp     spiDeRegisterSlave;
    epcfSpiSlaveSelect_fp               spiSlaveSelect;
    epcfSpiSlaveDeSelect_fp             spiSlaveDeSelect;
    epcfSpiExchange_fp                  spiExchange;
    epcfSpiWrite_fp                     spiWrite;
    epcfSpiRead_fp                      spiRead;
    epcfSpiGetRxBufferCount_fp          spiGetRxBufferCount;
    epcfSpiRxBufferFlush_fp             spiRxBufferFlush;
    epcfSpiGetTxBufferCount_fp          spiTxBufferCount;
    epcfSpiTxBufferFlush_fp             spiTxBufferFlush;
    epcfSpiIntEnable_fp                 spiIntEnable;
    epcfSpiIntDisable_fp                spiIntDisable;
    epcfSpiClose_fp                     spiClose;
    epcfSpiGetDeviceCount_fp            spiGetDeviceCount;
    void                               *hardwareCfg;
}EPCFSpiController_t;
#endif      //  #ifndef __EPCF_INCLUDE_PRIVATE_SPI_SPI_HIDDEN_H
