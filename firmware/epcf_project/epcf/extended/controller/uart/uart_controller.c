/**
 * \file  uart_controller.c
 * \brief This file is used to create UART controller
 *  FILE PATH : epcf\source\extended\controller\uart\uart_controller.c
 *              epcf\source\private\uart_hidden.h
 */
 
 
#include "epcf.h"

#define __EPCF_UTILS_UART_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,utils/,include/,epcf_string.h)
#include  __EPCF_UTILS_UART_H_INCLUDE
#undef __EPCF_UTILS_UART_H_INCLUDE

#define __EPCF_PRIVATE_UART_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,peripheral/,uart/,uart_hidden.h)
#include  __EPCF_PRIVATE_UART_H_INCLUDE
#undef __EPCF_PRIVATE_UART_H_INCLUDE


#define MAX_BUFFER_SIZE     68

static int8_t _epcfExtendedUartInit(EPCFUartDevice_t* pUartDevice, EPCFUartCfg_t* pUartConfig);
static int8_t _epcfExtendedUartClose(EPCFUartDevice_t* pUartDevice);
static int32_t _epcfExtendedUartWrite(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout);
static int32_t _epcfExtendedUartWriteBlocking(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout);
static int32_t _epcfExtendedUartWriteString(EPCFUartDevice_t* pUartDevice, const uint8_t* data, EPCFTime_t timeout);
static int32_t _epcfExtendedUartRead(EPCFUartDevice_t* pUartDevice, uint8_t * data, uint32_t size, EPCFTime_t timeout);
static uint32_t _epcfExtendedUartGetDeviceCount(EPCFUartController_t* pUartController);
static int32_t _epcfExtendedUartGetRxBufferCount(EPCFUartDevice_t* pUartDevice);
static int8_t _epcfExtendedUartRxBufferFlush(EPCFUartDevice_t* pUartDevice);
static int32_t _epcfExtendedUartGetTxBufferCount(EPCFUartDevice_t* pUartDevice);
static int8_t _epcfExtendedUartTxBufferFlush(EPCFUartDevice_t* pUartDevice);

static uint8_t txData[MAX_BUFFER_SIZE] = {0};
static uint8_t rxData[MAX_BUFFER_SIZE] = {0};
static EnEPCFBoolean_t uartControllerInitFlag = enEPCFBoolean_False;

#define UART_CONTROLLER_HW_CFG(Device)                  ((EPCFUartControllerHwCfg_t*)(Device->controllerConfig->hardwareCfg))

typedef struct
{
    EPCFAdapter_t*       adapter;
}EPCFUartControllerHwCfg_t;

EPCFUartController_t* epcfCreateUartController(EPCFAdapter_t *pAdapter)
{
    EPCFUartController_t *pUartController = 0;
    EPCFUartControllerHwCfg_t *pUartHwController = 0;
    
    if(uartControllerInitFlag != enEPCFBoolean_True)
    {
        pUartController = (EPCFUartController_t*)malloc(sizeof(EPCFUartController_t));
        if(pUartController == NULL)
            return NULL;
        
        pUartHwController = (EPCFUartControllerHwCfg_t*)malloc(sizeof(EPCFUartControllerHwCfg_t));
        if(pUartHwController == NULL)
            return NULL;

        pUartController->uartInit 			= _epcfExtendedUartInit;
        pUartController->uartWrite 			= _epcfExtendedUartWrite;
        pUartController->uartWriteBlocking	= _epcfExtendedUartWriteBlocking;
        pUartController->uartWriteString 	= _epcfExtendedUartWriteString;
        pUartController->uartRead 			= _epcfExtendedUartRead;
        pUartController->uartGetDeviceCount = _epcfExtendedUartGetDeviceCount;
        pUartController->uartRxBufferCount 	= _epcfExtendedUartGetRxBufferCount;
        pUartController->uartRxBufferFlush 	= _epcfExtendedUartRxBufferFlush;
        pUartController->uartTxBufferCount 	= _epcfExtendedUartGetTxBufferCount;
        pUartController->uartTxBufferFlush 	= _epcfExtendedUartTxBufferFlush;
        pUartController->uartClose 			= _epcfExtendedUartClose;
        pUartController->hardwareCfg 		= pUartHwController;
        
        ((EPCFUartControllerHwCfg_t*)pUartController->hardwareCfg)->adapter = pAdapter;

        uartControllerInitFlag = enEPCFBoolean_True;
        return pUartController;
    }
    else
        return NULL;
}

static int8_t _epcfExtendedUartInit(EPCFUartDevice_t* pUartDevice, EPCFUartCfg_t* pUartConfig)
{
    uint8_t txDataIndex=0;
    int8_t retValue=0;
    EPCFHeaderCfg_t txHeader;

    pcfMemSet((uint8_t*)txData, 0, (uint32_t)MAX_BUFFER_SIZE);
    pcfMemSet((uint8_t*)rxData, 0, (uint32_t)MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartConfig->uartId;
    txDataIndex += 1;

    txData[txDataIndex] = pUartConfig->baudrate;
    txDataIndex += 1;

    txData[txDataIndex] = pUartConfig->dataBits;
    txDataIndex += 1;

    txData[txDataIndex] = pUartConfig->parity;
    txDataIndex += 1;

    txData[txDataIndex] = pUartConfig->stopBits;
    txDataIndex += 1;

    txData[txDataIndex] = pUartConfig->interruptEnable;
    txDataIndex += 1;

    txData[txDataIndex] = (uint8_t)(pUartConfig->rxBufferSize);
    txDataIndex += 1;
    txData[txDataIndex] = (uint8_t)(((pUartConfig->rxBufferSize)>>8) & 0xFF);
    txDataIndex += 1;

    txData[txDataIndex] = (uint8_t)(pUartConfig->txBufferSize);
    txDataIndex += 1;
    txData[txDataIndex] = (uint8_t)(((pUartConfig->txBufferSize)>>8) & 0xFF);
    txDataIndex += 1;
	
	if(pUartConfig->hardwareCfg != NULL)
	{
	    txHeader.moduleId       = MODULE_ID_UART;
	    txHeader.commandId      = CMD_UART_GET_HARDWARE_CFG_SIZE;
        txHeader.msgType        = enEPCFUseNative;
        txHeader.isResponseMsg  = enEPCFBoolean_False;
        txHeader.txData         = NULL;
        txHeader.txDataSize     = 0;

        retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
        if(retValue < EPCF_STATUS_SUCCESS)
            return EPCF_STATUS_ERROR;

        retValue = pcfMemCopy(&txData[txDataIndex],pUartConfig->hardwareCfg, rxData[0]);
        if(retValue != 0 && retValue != rxData[0])
            return EPCF_STATUS_ERROR;

		txDataIndex += rxData[0];
	}
	
    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_INIT;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

    retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
    if(retValue < EPCF_STATUS_SUCCESS)
        return EPCF_STATUS_ERROR;

    pUartDevice->extendedUartDeviceId = rxData[0];
    return EPCF_STATUS_SUCCESS;
}

static int8_t _epcfExtendedUartClose(EPCFUartDevice_t* pUartDevice)
{
    uint8_t txDataIndex=0;
	int8_t retValue=0;
	EPCFHeaderCfg_t txHeader;

    pcfMemSet(txData, 0, MAX_BUFFER_SIZE);
    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartDevice->extendedUartDeviceId;
    txDataIndex += 1;

    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_CLOSE;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

    retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
    if(retValue<0)
        return -1;

    return rxData[0];
}

static int32_t _epcfExtendedUartWrite(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout)
{
    uint8_t txDataIndex=0, index;
	int8_t retValue=0;
    int32_t recvData=0;
    EPCFHeaderCfg_t txHeader;

    if(size > 64)
        return EPCF_STATUS_INVALID_USER_DATA_SIZE;

    pcfMemSet(txData, 0, MAX_BUFFER_SIZE);
    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartDevice->extendedUartDeviceId;
    txDataIndex += 1;

    for(index=0; index<size; index++)
    {
        txData[txDataIndex] = *(data+index);
        txDataIndex++;
    }

    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_WRITE;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

    retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
    if(retValue<0)
        return EPCF_STATUS_ERROR;

    recvData = (int32_t)((rxData[3]<<24)|(rxData[2]<<16)|(rxData[1]<<8)|rxData[0]);
    return recvData;
}

static int32_t _epcfExtendedUartWriteBlocking(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout)
{
    uint8_t txDataIndex=0, index;
	int8_t retValue=0;
    int32_t recvData=0;
    EPCFHeaderCfg_t txHeader;

    if(size > 64)
        return EPCF_STATUS_INVALID_USER_DATA_SIZE;

    pcfMemSet(txData, 0, MAX_BUFFER_SIZE);
    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartDevice->extendedUartDeviceId;
    txDataIndex += 1;

    for(index=0; index<size; index++)
    {
        txData[txDataIndex] = *(data+index);
        txDataIndex++;
    }

    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_WRITE_BLOCKING;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

    retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
    if(retValue<0)
        return EPCF_STATUS_ERROR;

    recvData = (int32_t)((rxData[3]<<24)|(rxData[2]<<16)|(rxData[1]<<8)|rxData[0]);
    return recvData;
}

static int32_t _epcfExtendedUartWriteString(EPCFUartDevice_t* pUartDevice, const uint8_t* data, EPCFTime_t timeout)
{
    uint8_t txDataIndex=0, index;
	int8_t retValue=0;
    int32_t recvData=0;
    EPCFHeaderCfg_t txHeader;

    if(pcfStrLen(data)>64)
        return EPCF_STATUS_INVALID_USER_DATA_SIZE;

    pcfMemSet(txData, 0, MAX_BUFFER_SIZE);
    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartDevice->extendedUartDeviceId;
    txDataIndex += 1;

    for(index=0; *(data+index)!=0; index++)
    {
        txData[txDataIndex] = *(data+index);
        txDataIndex++;
    }

    txData[txDataIndex] = '\0';
    txDataIndex++;


    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_WRITE_STRING;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

    retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
    if(retValue<0)
        return -1;

    recvData = (int32_t)((rxData[3]<<24)|(rxData[2]<<16)|(rxData[1]<<8)|rxData[0]);
    return recvData;
}

static int32_t _epcfExtendedUartRead(EPCFUartDevice_t* pUartDevice, uint8_t * data, uint32_t size, EPCFTime_t timeout)
{
    uint8_t txDataIndex=0;
	int8_t retValue=0;
    int32_t recvData=0;
    EPCFHeaderCfg_t txHeader;

    if(size > 64)
        return EPCF_STATUS_INVALID_USER_DATA_SIZE;

    pcfMemSet(txData, 0, MAX_BUFFER_SIZE);
    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartDevice->extendedUartDeviceId;
    txDataIndex += 1;

    txData[txDataIndex] = (uint8_t)size;
    txDataIndex += 1;

    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_READ;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

    retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData); // data will be received here
    if(retValue<0)
        return -1;

    pcfMemCopy(data, rxData+4, size);

	recvData = (int32_t)((rxData[3]<<24)|(rxData[2]<<16)|(rxData[1]<<8)|rxData[0]);
	return recvData;
}

static uint32_t _epcfExtendedUartGetDeviceCount(EPCFUartController_t* pUartController)
{
    int8_t retValue=0;
    EPCFHeaderCfg_t txHeader;

    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_GET_DEVICE_COUNT;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = NULL;
    txHeader.txDataSize     = 0;

    retValue = epcfSendMessage(((EPCFUartControllerHwCfg_t*)(pUartController->hardwareCfg))->adapter, &txHeader, rxData);
    if(retValue < 0)
        return -1;

    return rxData[0];
}

static int32_t _epcfExtendedUartGetRxBufferCount(EPCFUartDevice_t* pUartDevice)
{
    uint8_t txDataIndex=0;
	int8_t retValue=0;
    int32_t recvData=0;
    EPCFHeaderCfg_t txHeader;

    pcfMemSet(txData, 0, MAX_BUFFER_SIZE);
    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartDevice->extendedUartDeviceId;
    txDataIndex += 1;

    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_GET_RX_BUFFER_COUNT;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

    retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
    if(retValue<0)
        return -1;

    recvData = (int32_t)((rxData[3]<<24)|(rxData[2]<<16)|(rxData[1]<<8)|rxData[0]);
    return recvData;
}

static int8_t _epcfExtendedUartRxBufferFlush(EPCFUartDevice_t* pUartDevice)
{
    uint8_t txDataIndex=0;
	int8_t retValue=0;
    EPCFHeaderCfg_t txHeader;

    pcfMemSet(txData, 0, MAX_BUFFER_SIZE);
    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartDevice->extendedUartDeviceId;
    txDataIndex += 1;

    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_GET_RX_BUFFER_FLUSH;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

    retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
    if(retValue<0)
        return -1;

    return rxData[0];
}

static int32_t _epcfExtendedUartGetTxBufferCount(EPCFUartDevice_t* pUartDevice)
{
    uint8_t txDataIndex=0;
	int8_t retValue=0;
    int32_t recvData=0;
    EPCFHeaderCfg_t txHeader;

    pcfMemSet(txData, 0, MAX_BUFFER_SIZE);
    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartDevice->extendedUartDeviceId;
    txDataIndex += 1;

    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_GET_TX_BUFFER_COUNT;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

    retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
    if(retValue<0)
        return -1;

    recvData = (int32_t)((rxData[3]<<24)|(rxData[2]<<16)|(rxData[1]<<8)|rxData[0]);
    return recvData;
}

static int8_t _epcfExtendedUartTxBufferFlush(EPCFUartDevice_t* pUartDevice)
{
    uint8_t txDataIndex=0;
	int8_t retValue=0;
    EPCFHeaderCfg_t txHeader;

    pcfMemSet(txData, 0, MAX_BUFFER_SIZE);
    pcfMemSet(rxData, 0, MAX_BUFFER_SIZE);

    txData[txDataIndex] = pUartDevice->extendedUartDeviceId;
    txDataIndex += 1;

    txHeader.moduleId       = MODULE_ID_UART;
    txHeader.commandId      = CMD_UART_GET_TX_BUFFER_FLUSH;
    txHeader.msgType        = enEPCFUseNative;
    txHeader.isResponseMsg  = enEPCFBoolean_False;
    txHeader.txData         = txData;
    txHeader.txDataSize     = txDataIndex;

	retValue = epcfSendMessage(UART_CONTROLLER_HW_CFG(pUartDevice)->adapter, &txHeader, rxData);
    if(retValue<0)
        return -1;

    return rxData[0];
}
