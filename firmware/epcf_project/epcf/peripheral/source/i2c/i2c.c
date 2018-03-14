/**
 * \file  i2c.c
 * \brief This file is used to configure a I2C device
 */

#include "pcf.h"

#define __EPCF_PRIVATE_I2C_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,i2c/,i2c_hidden.h)
#include  __EPCF_PRIVATE_I2C_H_INCLUDE
#undef __EPCF_PRIVATE_I2C_H_INCLUDE


EPCFI2cDevice_t* epcf_i2c_CreateNative(EPCFI2cCfg_t* pI2cConfig)
{
    EPCFI2cDevice_t* pI2cDevice;
    int8_t status=0;

    if(epcf_i2c_nativeGetDeviceCount())
    {
        pI2cDevice = (EPCFI2cDevice_t *)malloc(sizeof(EPCFI2cDevice_t));
        if (pI2cDevice == NULL)
            return NULL;

        status = epcf_i2c_nativeInit(pI2cDevice, pI2cConfig);
        if(status != 0)
            return NULL;

        return pI2cDevice;
    }
    else
        return NULL;
}

#ifdef EPCF_SUPPORT_EXTENDED_I2C
EPCFI2cDevice_t* epcf_i2c_createExtended(EPCFI2cController_t* pI2cController, EPCFI2cCfg_t* pI2cConfig)
{
	EPCFI2cDevice_t* pI2cDevice;
	int8_t status = 0;

	if(epcf_i2c_extGetDeviceCount(pI2cController))
	{
		pI2cDevice = (EPCFI2cDevice_t*)malloc(sizeof(EPCFI2cDevice_t));
		if(pI2cDevice == NULL)
			return NULL;

		pI2cDevice->controllerConfig = pI2cController;

		status = pI2cController->i2cInit(pI2cDevice, pI2cConfig);
		if(status != 0)
			return NULL;

		return pI2cDevice;
	}
	else
		return NULL;
}
#endif

int32_t epcf_i2c_write(EPCFI2cDevice_t* pI2cDevice,EnEPCFBoolean_t masterEnable,uint8_t slaveAddress,const uint8_t* data,uint32_t size,EnEPCFBoolean_t busRelease,EPCFTime_t timeout)
{
	int32_t status=0;

	if(pI2cDevice->controllerConfig == NULL)
	{
		status = epcf_i2c_nativeWrite(pI2cDevice,masterEnable,slaveAddress,data,size,busRelease,timeout);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int32_t epcf_i2c_read(EPCFI2cDevice_t* pI2cDevice,EnEPCFBoolean_t masterEnable,uint8_t slaveAddress,uint8_t* data,uint32_t size,EnEPCFBoolean_t busRelease,EPCFTime_t timeout)
{
	int32_t status=0;

	if(pI2cDevice->controllerConfig == NULL)
	{
		status = epcf_i2c_nativeRead(pI2cDevice,masterEnable,slaveAddress,data,size,busRelease,timeout);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_i2c_intEnable(EPCFI2cDevice_t* pI2cDevice)
{
	int8_t status=0;

	if(pI2cDevice->controllerConfig == NULL)
	{
		status = epcf_i2c_nativeIntEnable(pI2cDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_i2c_intDisable(EPCFI2cDevice_t* pI2cDevice)
{
	int8_t status=0;

	if(pI2cDevice->controllerConfig == NULL)
	{
		status = epcf_i2c_nativeIntDisable(pI2cDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int32_t epcf_i2c_getRxBufferCount(EPCFI2cDevice_t* pI2cDevice)
{
	int32_t status=0;

	if(pI2cDevice->controllerConfig == NULL)
	{
		status = epcf_i2c_nativeGetRxBufferCount(pI2cDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_i2c_rxBufferFlush(EPCFI2cDevice_t* pI2cDevice)
{
	int8_t status=0;

	if(pI2cDevice->controllerConfig == NULL)
	{
		status = epcf_i2c_nativeRxBufferFlush(pI2cDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int32_t epcf_i2c_getTxBufferCount(EPCFI2cDevice_t* pI2cDevice)
{
	int32_t status=0;

	if(pI2cDevice->controllerConfig == NULL)
	{
		status = epcf_i2c_nativeGetTxBufferCount(pI2cDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_i2c_txBufferFlush(EPCFI2cDevice_t* pI2cDevice)
{
	int8_t status=0;

	if(pI2cDevice->controllerConfig == NULL)
	{
		status = epcf_i2c_nativeTxBufferFlush(pI2cDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

int8_t epcf_i2c_close(EPCFI2cDevice_t* pI2cDevice)
{
	int8_t status=0;

	if(pI2cDevice->controllerConfig == NULL)
	{
		status = epcf_i2c_nativeClose(pI2cDevice);
	}
	else
	{
//		TODO: controller structure is not defined
	}
	return status;
}

uint8_t epcf_i2c_getDeviceCount()
{
	uint8_t status=0;
	status = epcf_i2c_nativeGetDeviceCount();
	return status;
}

uint8_t epcf_i2c_extGetDeviceCount(EPCFI2cController_t* pI2cController)
{
	uint8_t status=0;
//	TODO: controller structure is not defined
	return status;
}



