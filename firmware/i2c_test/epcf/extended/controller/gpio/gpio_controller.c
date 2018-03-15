/**
 * \file  gpio_controller.c
 * \brief This file is used to create GPIO controller
 *  FILE PATH : epcf\source\extended\controller\gpio\gpio_controller.c
 *  			epcf\source\private\gpio_hidden.h
 */

#include "epcf.h"

#define	__EPCF_PRIVATE_GPIO_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,peripheral/,gpio/,gpio_hidden.h)
#include __EPCF_PRIVATE_GPIO_H_INCLUDE
#undef __EPCF_PRIVATE_GPIO_H_INCLUDE

#define __EPCF_PRIVATE_UART_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,peripheral/,uart/,uart_hidden.h)
#include  __EPCF_PRIVATE_UART_H_INCLUDE
#undef __EPCF_PRIVATE_UART_H_INCLUDE

#define PAYLOAD_SIZE_GPIO_RECV				1
#define PAYLOAD_SIZE_GPIO_INIT				5
#define PAYLOAD_SIZE_GPIO_SET				1
#define PAYLOAD_SIZE_GPIO_CLEAR				1
#define PAYLOAD_SIZE_GPIO_SET_DIRECTION		2
#define PAYLOAD_SIZE_GPIO_READ				1
#define PAYLOAD_SIZE_GPIO_GET_DEVICE_COUNT	0

static int8_t _epcfExtendedGpioInit(EPCFGpioDevice_t* pGpioDevice, EPCFGpioCfg_t* pGpioConfig);
static int8_t _epcfExtendedGpioSet(EPCFGpioDevice_t* pGpioDevice);
static int8_t _epcfExtendedGpioClear(EPCFGpioDevice_t* pGpioDevice);
static int8_t _epcfExtendedGpioRead(EPCFGpioDevice_t* pGpioDevice);
static int8_t _epcfExtendedGpioSetDirection(EPCFGpioDevice_t* pGpioDevice, EnEPCFGpioDirection_t direction);
static uint32_t _epcfExtendedGpioGetDeviceCount(EPCFGpioController_t* pGpioController);

#define GPIO_CONTROLLER_HW_CFG					((EPCFGpioControllerHwCfg_t*)(pGpioDevice->controllerConfig->hardwareCfg))

typedef struct
{
	EPCFAdapter_t*          adapter;
}EPCFGpioControllerHwCfg_t;

static EnEPCFBoolean_t gpioControllerInitFlag = enEPCFBoolean_False;

EPCFGpioController_t* epcfCreateGpioController(EPCFAdapter_t *pAdapter)
{
	EPCFGpioController_t* pGpioController=0;
    EPCFGpioControllerHwCfg_t* pGpioControllerHwCfg=0;

	if(gpioControllerInitFlag != enEPCFBoolean_True)
	{
		pGpioController = (EPCFGpioController_t*)malloc(sizeof(EPCFGpioController_t));
		if(pGpioController == NULL)
			return NULL;
        
        pGpioControllerHwCfg = (EPCFGpioControllerHwCfg_t*)malloc(sizeof(EPCFGpioControllerHwCfg_t));
        if(pGpioControllerHwCfg == NULL)
            return NULL;

        pGpioController->gpioInit               = _epcfExtendedGpioInit;
        pGpioController->gpioSet                = _epcfExtendedGpioSet;
        pGpioController->gpioClear              = _epcfExtendedGpioClear;
        pGpioController->gpioRead               = _epcfExtendedGpioRead;
        pGpioController->gpioSetDirection       = _epcfExtendedGpioSetDirection;
        pGpioController->gpioGetDeviceCount     = _epcfExtendedGpioGetDeviceCount;
        pGpioController->hardwareCfg			= pGpioControllerHwCfg;

        ((EPCFGpioControllerHwCfg_t*)(pGpioController->hardwareCfg))->adapter = pAdapter;

		gpioControllerInitFlag = enEPCFBoolean_True;
		return pGpioController;
	}
	else
		return NULL;
}

static int8_t _epcfExtendedGpioInit(EPCFGpioDevice_t* pGpioDevice, EPCFGpioCfg_t* pGpioConfig)
{
	uint8_t txData[PAYLOAD_SIZE_GPIO_INIT]={0}, rxData[PAYLOAD_SIZE_GPIO_RECV]={0};
	uint8_t txDataIndex=0;
	int8_t retVal=0;
	EPCFHeaderCfg_t txHeader;

	txData[txDataIndex++] = (uint8_t)(pGpioConfig->portPin.port);
	txData[txDataIndex++] = (uint8_t)(pGpioConfig->portPin.pin);
	txData[txDataIndex++] = (uint8_t)(pGpioConfig->direction);
	txData[txDataIndex++] = (uint8_t)(pGpioConfig->mode);
	txData[txDataIndex++] = (uint8_t)(pGpioConfig->openDrain);


	txHeader.moduleId 		= MODULE_ID_GPIO;
	txHeader.commandId 		= CMD_GPIO_INIT;
	txHeader.msgType		= enEPCFUseNative;
	txHeader.isResponseMsg 	= enEPCFBoolean_False;
	txHeader.txData			= txData;
	txHeader.txDataSize		= txDataIndex;

	retVal = epcfSendMessage(GPIO_CONTROLLER_HW_CFG->adapter, &txHeader, rxData);
	if(retVal < 0)
		return EPCF_STATUS_ERROR;

	pGpioDevice->extendedGpioDeviceId = rxData[0];
	return EPCF_STATUS_SUCCESS;
}

static int8_t _epcfExtendedGpioSet(EPCFGpioDevice_t* pGpioDevice)
{
	int8_t retVal=0;
	uint8_t txData[PAYLOAD_SIZE_GPIO_SET]={0},rxData[PAYLOAD_SIZE_GPIO_RECV];
	uint8_t txDataIndex=0;
	EPCFHeaderCfg_t txHeader;

	txData[txDataIndex++] = pGpioDevice->extendedGpioDeviceId;

	txHeader.moduleId 		= MODULE_ID_GPIO;
	txHeader.commandId 		= CMD_GPIO_SET;
	txHeader.msgType		= enEPCFUseNative;
	txHeader.isResponseMsg 	= enEPCFBoolean_False;
	txHeader.txData			= txData;
	txHeader.txDataSize		= txDataIndex;

	retVal = epcfSendMessage(GPIO_CONTROLLER_HW_CFG->adapter, &txHeader, rxData);
	if(retVal < 0)
		return EPCF_STATUS_ERROR;

	if(rxData[0] == 0)
		return EPCF_STATUS_SUCCESS;

	else
		return rxData[0];
}

static int8_t _epcfExtendedGpioClear(EPCFGpioDevice_t* pGpioDevice)
{
	int8_t retVal=0;
	uint8_t txData[PAYLOAD_SIZE_GPIO_SET]={0},rxData[PAYLOAD_SIZE_GPIO_RECV];
	uint8_t txDataIndex=0;
	EPCFHeaderCfg_t txHeader;

	txData[txDataIndex++] = pGpioDevice->extendedGpioDeviceId;

	txHeader.moduleId 		= MODULE_ID_GPIO;
	txHeader.commandId 		= CMD_GPIO_CLEAR;
	txHeader.msgType		= enEPCFUseNative;
	txHeader.isResponseMsg 	= enEPCFBoolean_False;
	txHeader.txData			= txData;
	txHeader.txDataSize		= txDataIndex;

	retVal = epcfSendMessage(GPIO_CONTROLLER_HW_CFG->adapter, &txHeader, rxData);
	if(retVal < 0)
		return EPCF_STATUS_ERROR;

	if(rxData[0] == 0)
		return EPCF_STATUS_SUCCESS;

	else
		return rxData[0];
}

static int8_t _epcfExtendedGpioRead(EPCFGpioDevice_t* pGpioDevice)
{
	int8_t retVal=0;
	EPCFHeaderCfg_t txHeader;
	uint8_t txData[PAYLOAD_SIZE_GPIO_READ]={0}, rxData[PAYLOAD_SIZE_GPIO_RECV], txDataIndex=0;

	txData[txDataIndex++] = pGpioDevice->extendedGpioDeviceId;

	txHeader.moduleId 		= MODULE_ID_GPIO;
	txHeader.commandId 		= CMD_GPIO_READ;
	txHeader.msgType		= enEPCFUseNative;
	txHeader.isResponseMsg 	= enEPCFBoolean_False;
	txHeader.txData			= txData;
	txHeader.txDataSize		= txDataIndex;

	retVal = epcfSendMessage(GPIO_CONTROLLER_HW_CFG->adapter, &txHeader, rxData);
	if(retVal < 0)
		return EPCF_STATUS_ERROR;

	return rxData[0];
}

static int8_t _epcfExtendedGpioSetDirection(EPCFGpioDevice_t* pGpioDevice, EnEPCFGpioDirection_t direction)
{
	int8_t retVal=0;
	EPCFHeaderCfg_t txHeader;
	uint8_t txData[PAYLOAD_SIZE_GPIO_SET_DIRECTION]={0}, rxData[PAYLOAD_SIZE_GPIO_RECV], txDataIndex=0;

	txData[txDataIndex++] = pGpioDevice->extendedGpioDeviceId;
	txData[txDataIndex++] = direction;

	txHeader.moduleId 		= MODULE_ID_GPIO;
	txHeader.commandId 		= CMD_GPIO_SET_DIRECTION;
	txHeader.msgType		= enEPCFUseNative;
	txHeader.isResponseMsg 	= enEPCFBoolean_False;
	txHeader.txData			= txData;
	txHeader.txDataSize		= txDataIndex;

	retVal = epcfSendMessage(GPIO_CONTROLLER_HW_CFG->adapter, &txHeader, rxData);
	if(retVal == 0)
		return EPCF_STATUS_ERROR;

	return rxData[0];
}

static uint32_t _epcfExtendedGpioGetDeviceCount(EPCFGpioController_t* pGpioController)
{
	int32_t retVal=0;
	EPCFHeaderCfg_t txHeader;
	uint32_t rxData[PAYLOAD_SIZE_GPIO_RECV];

	txHeader.moduleId 		= MODULE_ID_GPIO;
	txHeader.commandId 		= CMD_GPIO_GET_DEVICE_COUNT;
	txHeader.msgType		= enEPCFUseNative;
	txHeader.isResponseMsg 	= enEPCFBoolean_False;
	txHeader.txData			= NULL;
	txHeader.txDataSize		= 0;
	
	retVal = epcfSendMessage(((EPCFGpioControllerHwCfg_t*)(pGpioController->hardwareCfg))->adapter, &txHeader, (uint8_t*)rxData);
	if(retVal < 0)
		return EPCF_STATUS_ERROR;

	return rxData[0];
}
