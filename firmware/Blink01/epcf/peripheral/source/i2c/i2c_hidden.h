/**
 * \file    i2c_hidden.h
 * \brief   hidden header file for I2C Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *
 */

#ifndef __EPCF_PERIPHERAL_SOURCE_I2C_I2C_HIDDEN_H
#define __EPCF_PERIPHERAL_SOURCE_I2C_I2C_HIDDEN_H


typedef struct EPCFI2cController EPCFI2cController_t;
typedef struct EPCFI2cDevice EPCFI2cDevice_t;

typedef struct EPCFI2cDevice
{
	EPCFI2cController_t*    controllerConfig;
    uint8_t             	i2cId;
    void*               	i2cChannelAddr;
    EnEPCFBoolean_t     	interruptEnable;
    PCFFifoDesc_t       	*i2cTxFifo;
    PCFFifoDesc_t       	*i2cRxFifo;
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedI2cDeviceId;         // ID Returned from the Device.
#endif	
}EPCFI2cDevice_t;



#endif      //  __EPCF_PERIPHERAL_SOURCE_I2C_I2C_HIDDEN_H
