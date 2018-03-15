/**
 * \file  spi.c
 * \brief This file is used to configure a SPI device.
 */

#include "pcf.h"

#define   __EPCF_SPI_HIDDEN_INCLUDE     PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,spi/,spi_hidden.h)
#include  __EPCF_SPI_HIDDEN_INCLUDE
#undef    __EPCF_SPI_HIDDEN_INCLUDE

#if PCF_ENABLE_DEBUG == PCF_ENABLE
    #define _SPI_DEBUG  PCF_ENABLE
#else
    #define _SPI_DEBUG  PCF_DISABLE
#endif // PCF_ENABLE_DEBUG == PCF_ENABLE

EPCFSpiDevice_t* epcf_spi_createNative(EPCFSpiCfg_t* pSpiConfig)
{
    EPCFSpiDevice_t* pSpiDevice;
    int8_t status=0;
    // Parameter Checking
    if(pSpiConfig == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
    if(pSpiConfig->bitOrder >= enEPCFSpiBitOrder_Max)
    {
	   //TODO: ADD Debug Log
	   return PCF_NULL;
    }
    if(pSpiConfig->clockMode >= enEPCFSpiClockMode_Max)
    {
	   //TODO: ADD Debug Log
	   return PCF_NULL;
    }
    if(pSpiConfig->dataBits >= enEPCFSpiDataBits_Max)
    {
	   //TODO: ADD Debug Log
	   return PCF_NULL;
    }
    if(epcf_spi_getDeviceCount())
    {
        pSpiDevice = (EPCFSpiDevice_t *)malloc(sizeof(EPCFSpiDevice_t));
        if (pSpiDevice == (EPCFSpiDevice_t *)PCF_NULL)
        {
            //TODO: ADDED Debug Log
            return PCF_NULL;
        }

        pSpiDevice->controllerConfig = PCF_NULL;

        status = epcf_Spi_nativeInit(pSpiDevice, pSpiConfig);
        if(status != 0)
        {
            //TODO: ADDED Debug Log
            return PCF_NULL;
        }

        return pSpiDevice;
    }
    else{
        //TODO: ADDED Debug Log
        return NULL;
    }
}

#ifdef EPCF_SUPPORT_EXTENDED_SPI
EPCFSpiDevice_t* epcf_spi_createExtended(EPCFSpiController_t* pSpiController, EPCFSpiCfg_t* pSpiConfig)
{
    EPCFSpiDevice_t* pSpiDevice;
    int8_t status = 0;

    if(pSpiController == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
    if(pSpiConfig == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }

    if(epcf_spi_extGetDeviceCount(pSpiController))
    {
        pUartDevice = (EPCFUartDevice_t*)malloc(sizeof(EPCFUartDevice_t));
        if(pUartDevice == PCF_NULL){
            //TODO: ADDED Debug Log
            return PCF_NULL;
        }

        pSpiDevice->controllerConfig = pSpiController;

        status = pUartController->spiInit(pSpiDevice, pSpiConfig);
        if(status != 0){
            //TODO: ADDED Debug Log
            return PCF_NULL;
        }

        return pUartDevice;
    }
    else{
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
}

#endif

int8_t epcf_spi_close(EPCFSpiDevice_t* pSpiDevice)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeClose(pSpiDevice);
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiClose(pSpiDevice);
    }
    return retVal;
}

int8_t epcf_spi_registerSlaveDevice(EPCFSpiDevice_t* pSpiDevice,EPCFPortPin_t slaveSelectPin)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeRegisterSlaveDevice(pSpiDevice, slaveSelectPin);
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiRegisterSlave(pSpiDevice,slaveSelectPin);
    }
    return retVal;
}

int8_t epcf_spi_deRegisterSlaveDevice(EPCFSpiDevice_t* pSpiDevice,uint8_t slaveId)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeDeRegisterSlaveDevice(pSpiDevice, slaveId);
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiDeRegisterSlave(pSpiDevice,slaveId);
    }
    return retVal;
}

int8_t epcf_spi_slaveSelect(EPCFSpiDevice_t* pSpiDevice, uint8_t slaveId)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeSlaveSelect(pSpiDevice, slaveId);
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiSlaveSelect(pSpiDevice,slaveId);
    }
    return retVal;
}

int8_t epcf_spi_slaveDeSelect(EPCFSpiDevice_t* pSpiDevice, uint8_t slaveId)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeSlaveDeSelect(pSpiDevice, slaveId);
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiSlaveDeSelect(pSpiDevice,slaveId);
    }
    return retVal;
}

int8_t epcf_spi_exchange(EPCFSpiDevice_t* pSpiDevice, uint16_t txData, uint16_t* rxData, EPCFTime_t timeout)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
    if(rxData == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeExchange(pSpiDevice, txData ,rxData ,timeout );
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiExchange(pSpiDevice,txData,rxData,timeout);
    }
    return retVal;
}

int8_t epcf_spi_write(EPCFSpiDevice_t* pSpiDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
    if(data == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeWrite(pSpiDevice, data ,size ,timeout );
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiWrite(pSpiDevice, data ,size ,timeout );
    }
    return retVal;
}

int8_t epcf_spi_read(EPCFSpiDevice_t* pSpiDevice, uint8_t* data, uint32_t size, EPCFTime_t timeout)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
    if(data == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeRead(pSpiDevice, data ,size ,timeout );
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiRead(pSpiDevice, data ,size ,timeout );
    }
    return retVal;
}

int8_t epcf_spi_intEnable(EPCFSpiDevice_t* pSpiDevice,EnEPCFSpiIntType intType)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
    if(intType >= enEPCFSpiInt_Max){
        //TODO: ADDED Debug Log
        return EPCF_STATUS_INVALID_ARGS;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeIntEnable(pSpiDevice,intType );
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiIntEnable(pSpiDevice, intType );
    }
    return retVal;
}

int8_t epcf_spi_intDisable(EPCFSpiDevice_t* pSpiDevice,EnEPCFSpiIntType intType)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
    if(intType >= enEPCFSpiInt_Max){
        //TODO: ADDED Debug Log
        return EPCF_STATUS_INVALID_ARGS;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeIntDisable(pSpiDevice,intType );
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiIntDisable(pSpiDevice, intType );
    }
    return retVal;
}

int32_t epcf_spi_getRxBufferCount(EPCFSpiDevice_t* pSpiDevice)
{
    int32_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeGetRxBufferCount(pSpiDevice);
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiGetRxBufferCount(pSpiDevice );
    }
    return retVal;
}

int8_t epcf_spi_rxBufferFlush(EPCFSpiDevice_t* pSpiDevice)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeRxBufferFlush(pSpiDevice);
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiRxBufferFlush(pSpiDevice );
    }
    return retVal;
}

int32_t epcf_spi_getTxBufferCount(EPCFSpiDevice_t* pSpiDevice)
{
    int32_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeGetTxBufferCount(pSpiDevice);
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiTxBufferCount(pSpiDevice );
    }
    return retVal;
}

int8_t epcf_spi_txBufferFlush(EPCFSpiDevice_t* pSpiDevice)
{
    int8_t retVal=0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    if(pSpiDevice->controllerConfig == NULL)
    {
        retVal = epcf_spi_nativeTxBufferFlush(pSpiDevice);
    }
    else
    {
        retVal = pSpiDevice->controllerConfig->spiTxBufferFlush(pSpiDevice );
    }
    return retVal;
}

uint8_t epcf_spi_getDeviceCount()
{
    uint8_t retVal=0;

    retVal = epcf_spi_nativeGetDeviceCount();
    return retVal;
}

#ifdef EPCF_USING_MT_ENV
//ToDo: Adding support for EPCF_USING_MT_ENV
int8_t epcf_spi_lock(EPCFSpiDevice_t* pSpiDevice)
{
    int8_t retVal = 0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    retVal = EPCF_STATUS_NOT_SUPPORTED;
    return retVal;
}

int8_t epcf_spi_unlock(EPCFSpiDevice_t* pSpiDevice)
{
    int8_t retVal = 0;

#if _SPI_DEBUG == PCF_ENABLE
    // Parameter Checking
    if(pSpiDevice == PCF_NULL){
        //TODO: ADDED Debug Log
        return PCF_NULL;
    }
#endif //_SPI_DEBUG

    retVal = EPCF_STATUS_NOT_SUPPORTED;
    return retVal;
}

#endif  //EPCF_USING_MT_ENV
