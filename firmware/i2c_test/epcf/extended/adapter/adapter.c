/**
 * \file  uart_adapter.c            \
 * \brief This file is used to configure a native UART peripheral in extended mode.
 */

#include "epcf.h"

#if (PCF_ARCH == PCF_ARCH_X86)
    #define __EPCF_UART_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/uart/PCF_OS_NAME/,uart_,PCF_ARCH_NAME.h)
    #include __EPCF_UART_INCLUDE
#else
    #define __EPCF_UART_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/uart/,uart_,PCF_ARCH_DEVICE.h)
    #include __EPCF_UART_INCLUDE
#endif
#undef __EPCF_UART_INCLUDE

#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
    #define EPCF_NATIVE_CREATE_UART(pConfig)                            epcfCreateUart(pConfig)
#elif(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
	#define EPCF_NATIVE_CREATE_UART(pConfig)							epcfCreateUart(NULL,pConfig)
#endif
#define EPCF_NATIVE_UART_WRITE(pDevice,txData,txDataSize,timeout)       epcfNativeUartWrite(pDevice,txData,txDataSize,timeout)
#define EPCF_NATIVE_UART_READ(pDevice,rxData,rxDataSize,timeout)        epcfNativeUartRead(pDevice,rxData,rxDataSize,timeout)
#define EPCF_NATIVE_CLOSE_UART(pDevice)                                 epcfNativeUartClose(pDevice)

static void* _epcfCreateUartAdapter(EPCFAdapter_t* pAdapter, void *pConfig);
static int32_t _epcfUartWrite(EPCFAdapter_t* pAdapter, const uint8_t *txData , uint32_t txDataSize, EPCFTime_t timeout);
static int32_t _epcfUartRead(EPCFAdapter_t* pAdapter, uint8_t *rxData, uint32_t rxDataSize, EPCFTime_t timeout);
static uint8_t _epcfCloseUartAdapter(EPCFAdapter_t* pAdapter);

static int8_t _epcfAdapterAttachCallback(EPCFAdapter_t* pAdapter, epcfCallback_fp pCallback);
static int8_t _epcfAdapterDetachCallback(EPCFAdapter_t* pAdapter, epcfCallback_fp pCallback);

static void* (*epcfCreateDeviceWrapper_fp[])(EPCFAdapter_t*, void*) =
{
    _epcfCreateUartAdapter
};

static uint8_t (*epcfCloseDeviceWrapper_fp[])(EPCFAdapter_t*) =
{
    _epcfCloseUartAdapter
};

EPCFAdapter_t* epcfCreateAdapter(uint8_t adapterId, void *pConfig)
{
    void *pDevice=0;
    EPCFAdapter_t *pAdapter;
    pAdapter = (EPCFAdapter_t *)malloc(sizeof(EPCFAdapter_t));
    if(pAdapter == 0)
        return 0;
    
    pAdapter->adapterId = adapterId;
    pDevice = epcfCreateDeviceWrapper_fp[adapterId](pAdapter, pConfig);
    if(pDevice == 0)
        return NULL;
    
    pAdapter->pDevice = (void*)pDevice;
    return pAdapter;
}

int8_t epcfCloseAdapter(uint8_t adapterId,EPCFAdapter_t* pAdapter)
{
    int8_t status = EPCF_STATUS_SUCCESS;

    status = epcfCloseDeviceWrapper_fp[adapterId](pAdapter);
    if(status != EPCF_STATUS_SUCCESS)
        return status;

    pAdapter = (EPCFAdapter_t*) PCF_NULL;
    return EPCF_STATUS_SUCCESS;
}

static void* _epcfCreateUartAdapter(EPCFAdapter_t* pAdapter, void *pConfig)
{
#if(EPCF_USE_UART == PCF_YES)
    EPCFUartDevice_t *pUartDevice;

    pAdapter->adapterWrite  		= _epcfUartWrite;
    pAdapter->adapterRead  			= _epcfUartRead;
	pAdapter->adapterAttachCallback	= _epcfAdapterAttachCallback;
	pAdapter->adapterDetachCallback	= _epcfAdapterDetachCallback;

    pUartDevice = EPCF_NATIVE_CREATE_UART(pConfig);
    if(pUartDevice == NULL)
        return NULL;
    else
        return pUartDevice;
#else
    return NULL;
#endif
}

static uint8_t _epcfCloseUartAdapter(EPCFAdapter_t* pAdapter)
{
#if(EPCF_USE_UART == PCF_YES)
    int8_t status=0;

    status = EPCF_NATIVE_CLOSE_UART(pAdapter->pDevice);
    if(status != EPCF_STATUS_SUCCESS)
        return status;

    free(pAdapter->pDevice);
    //pAdapter->adapterRead == PCF_NULL;
    //pAdapter->adapterWrite == PCF_NULL;
    return EPCF_STATUS_SUCCESS;
#else
    return EPCF_STATUS_NOT_CONFIGURED;
#endif
}

static int32_t _epcfUartWrite(EPCFAdapter_t *pAdapter, const uint8_t *txData , uint32_t txDataSize, EPCFTime_t timeout)
{
    int32_t retVal;

#if(EPCF_USE_UART == PCF_YES)
    retVal = EPCF_NATIVE_UART_WRITE(pAdapter->pDevice, txData, txDataSize, timeout);
    return retVal;
#else
    return -1;
#endif
}

static int32_t _epcfUartRead(EPCFAdapter_t *pAdapter, uint8_t *rxData, uint32_t rxDataSize, EPCFTime_t timeout)
{
    int32_t retVal;
#if(EPCF_USE_UART == PCF_YES)
    retVal = EPCF_NATIVE_UART_READ(pAdapter->pDevice, rxData, rxDataSize, timeout);
    return retVal;
#else
    return -1;
#endif
}

static int8_t _epcfAdapterAttachCallback(EPCFAdapter_t* pAdapter, epcfCallback_fp pCallback)
{
	
	
}

static int8_t _epcfAdapterDetachCallback(EPCFAdapter_t* pAdapter, epcfCallback_fp pCallback)
{
	
	
}
