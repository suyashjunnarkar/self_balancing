/**
 *  \file  i2c.h
 *  \brief This file is used to configure a I2c device
 */
 
#ifndef __EPCF_PERIPHERAL_INCLUDE_I2C_I2C_H
#define __EPCF_PERIPHERAL_INCLUDE_I2C_I2C_H

/** \brief  I2c device          */
typedef struct EPCFI2cDevice EPCFI2cDevice_t;

/** \brief I2c address type     */
typedef enum
{
    enEPCFI2cAddress_7bit,          /**< 7bit address type      */
    enEPCFI2cAddress_10bit,         /**< 10bit address type     */
    enEPCFI2cAddressType_Max        /**< Special value for boundary checking    */
}EnEPCFI2cAddressType_t;

/**
 *   I2c configuration structure
 *   
 *   Example to configure I2c device in master mode
 *   EPCFI2cCfg_t I2cConfig =
 *   {
 *       0,                          // I2c id 0
 *       100000,                     // 100khz baudrate
 *       enEPCFI2cAddress_7bit,      // 7bit addressing
 *       {0,0,0,0},                  // Not required in master mode
 *       {0,0,0,0},                  // Not required in master mode
 *       0,                          // Not required in master mode
 *       enEPCFBooleanTrue,          // Enable  interrupt
 *       256,                        // Tx buffer size = 256 bytes
 *       256,                        // Rx buffer size = 256 bytes
 *       NULL                        // No hardware specific config
 *   };
 *   
 *   Example to configure I2c device in slave mode
 *   EPCFI2cCfg_t I2cConfig =
 *   {
 *       0,                          // I2c id 0
 *       0,                          // Not required in slave mode
 *       enEPCFI2cAddress_7bit,      // 7bit addressing
 *       {5,0,0,0},                  // Own address set to 5
 *       {1,0,0,0},                  // 1st bit of address masked. The device will respond to address value 4 and 5
 *       enEPCFBooleanFalse,         // Disable general call
 *       enEPCFBooleanTrue,          // Enable  interrupt
 *       256,                        // Tx buffer size = 256 bytes
 *       256,                        // Rx buffer size = 256 bytes
 *       NULL                        // No hardware specific config
 *   };
 *   
 */
typedef struct 
{
    uint8_t                 i2cId;                  /**< I2c Id. Refer to platform specific header file for appropriate id         */
    
    uint32_t                baudrate;               /**< Baudrate for  communication in bits/second. For standard mode baudrate
                                                     is upto 100kHz and for fast mode upto 400kHz. Refer to your platform specific
                                                     header file for supported baudrate.                                                */

    EnEPCFI2cAddressType_t  addressType;            /**< I2c address type   */
    
    uint16_t                ownAddress[4];          /**< I2c address. It is used to filter packets on the I2c bus.
                                                     This parameter is used when using device in slave mode.
                                                     For example: To configure own address as 5 and using 7bit addressing.
                                                     Set addressType as enEPCFI2cAddress_7bit and value = 0x0005.                       */
    
    uint16_t                ownAddressMask[4];      /**< I2c device address mask. Bits in the mask value set as 1 will not be
                                                     taken into account in determining an address match.
                                                     This parameter is used when using device in slave mode.
                                                     For example: Consider a device with address = 0x0005.
                                                     Now, if ownAddressMask is set to 0x0001 for the device, then it will respond
                                                     to address value 0x0004 and 0x0005.                                                */
    
    EnEPCFBoolean_t         generalCallEnable;      /**< Specifies to enable general call or not
                                                     This parameter is used when using device in slave mode.
                                                     enEPCFBoolean_True  = General call message will be received
                                                     enEPCFBoolean_False = General call message will be ignored                         */

    EnEPCFBoolean_t         interruptEnable;        /**< Specifies to enable I2c interrupt or not
                                                     enEPCFBoolean_True  = To enable I2c interrupt
                                                     enEPCFBoolean_False = To disable I2c interrupt(polling mode)   */

    uint32_t                txBufferSize;           /**< Specifies the transmit buffer size in bytes when using  in interrupt mode
                                                     Pass 0 when I2c is configured in polling mode                                     */

    uint32_t                rxBufferSize;           /**< Specifies the receive buffer size in bytes when using  in interrupt mode
                                                     Pass 0 when I2c is configured in polling mode                                     */
    
    void*                   hardwareCfg;            /**< Hardware platform specific configuration, pass NULL for default configuration  */
}EPCFI2cCfg_t;


/**
 *  \brief This function is used to create a i2c device. Call this function in beginning to initialize the i2c device.
 *         This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer 
 *         while calling i2c functions.
 *  
 *  \param pI2cConfig Pointer to the i2c configuration structure.
 *  
 *  \return On success, it return the pointer to i2c device.
 *          On error, it returns NULL. 
 */
 extern EPCFI2cDevice_t* epcf_i2c_CreateNative(EPCFI2cCfg_t* pI2cConfig);

 #ifdef EPCF_SUPPORT_EXTENDED_I2C
 
/** \brief i2c Controller   */
typedef struct EPCFI2cController EPCFI2cController_t;

/** 
 *  \brief This function is used to create a i2c device in extended mode.
 *  	   Before calling this function, user should create an adapter for communication between host and extended device.
 *         For detail explaination, see ../../../../extended/adapter/adapter.h
 *         Then, user should create a controller for controlling extended device from host.
 *   	   Call this function in beginning to initialize the i2c device. This function allocates memory for the device using malloc() function call and returns a pointer to the device.
 *  	   Pass this device pointer while calling i2c functions.
 *  
 *  \param   pI2cConfig      Pointer to the i2c configuration structure.
 *  \param   pI2cController  Pointer to the i2c Controller to which i2c device will be attached.
 *  
 *  \return On success, it return the pointer to i2c device.
 *         On error, it returns NULL.
 */
extern EPCFI2cDevice_t* epcf_i2c_createExtended(EPCFI2cController_t* pI2cController, EPCFI2cCfg_t* pI2cConfig);

/**
 *  \brief This function returns total number of available i2c devices on an extended controller.
 *  
 *  \param      pI2cController  Pointer to the I2c controller.
 *  
 *  \return Returns the number of available I2c devices on extended bound controller.
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern uint8_t epcf_i2c_extGetDeviceCount(EPCFI2cController_t* pI2cController);

#endif
 
 /**    
 *  \brief This function is used to send data on I2c bus. It can be used in both master and slave mode.
 *         In Interrupt mode, data transmission will be asynchronous and the data is transmitted using
 *         internal software buffer. The function will be non blocking and will return after initiating data
 *         transmission. Use EPCF_I2c_GET_TX_BUFFER_COUNT function to check the status of the transmit buffer.
 *  
 *         In Polling mode, data transmission will be synchronous and calling function will be blocked until
 *         all the data is transmitted or timeout has occurred.
 *  
 *  \param pI2cDevice    Pointer to the I2c device
 *  \param masterEnable  Make it true if want to use this function in master mode.
 *  \param slaveAddress  Address of the slave device
 *  \param data          Pointer to buffer where data to be write is stored
 *  \param size          Total number of bytes to be read
 *  \param busRelease    Make it true if want to release the bus after receiving all data.
 *  \param timeout       timeout value.
 *  
 *  \return  return total number of bytes send over I2c bus. Check status code if return value is less than 0.
 *           Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int32_t epcf_i2c_write(EPCFI2cDevice_t* pI2cDevice,EnEPCFBoolean_t masterEnable,uint8_t slaveAddress,const uint8_t* data,uint32_t size,EnEPCFBoolean_t busRelease,EPCFTime_t timeout);  

/**
 *  \brief This function is used to read data on I2c bus. This function can be used in both master and slave mode.
 *         In Interrupt mode, data receiving is asynchronous and data is received in an internal software buffer.
 *         Use EPCF_I2c_GET_RX_BUFFER_COUNT function to get receive buffer count. When the count is equal to the 
 *         required number of bytes to be read, call EPCF_I2c_READ function to read the buffer.
 *  
 *         In Polling mode, data receiving will be synchronous and calling function will be blocked until
 *         all the data is received or timeout has occurred.
 *  
 *  \param pI2cDevice    Pointer to the I2c device
 *  \param masterEnable  Make it true if want to use this function in master mode.
 *  \param slaveAddress  Address of the slave device
 *  \param data          Pointer to buffer where data read is to be stored
 *  \param size          Total number of bytes to be read
 *  \param busRelease    Make it true if want to release the bus after receiving all data.
 *  \param timeout       timeout value.
 *  
 *  \return  return number of bytes read over I2c bus. Check status code if return value is less than 0.
 *           Refer to "../../common/status.h" header file for the appropriate status codes.
 */
 extern int32_t epcf_i2c_read(EPCFI2cDevice_t* pI2cDevice,EnEPCFBoolean_t masterEnable,uint8_t slaveAddress,uint8_t* data,uint32_t size,EnEPCFBoolean_t busRelease,EPCFTime_t timeout);

/**
 *  \brief This function is used to enable the I2c interrupt.It can be disabled by epcf_i2c_intDisable() function.
 *  
 *  \param pI2cDevice  Pointer to the I2c device.
 *  \param intType     interrupt type to generate an interrupt.Refer Enum EnEPCFIntType_t.
 *  
 *  \return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_i2c_intEnable(EPCFI2cDevice_t* pI2cDevice);

/**
 *  \brief This function is used to disable the I2c interrupt.
 *         The device can be enabled again by epcf_i2c_intEnable() function.
 *  
 *  \param pI2cDevice  Pointer to the I2c device.
 *  \param intType     interrupt type to generate an interrupt.Refer Enum EnEPCFIntType_t.
 *  \return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_i2c_intDisable(EPCFI2cDevice_t* pI2cDevice);
  
 /**
 *  This function is used to get number of bytes received in I2c receive buffer.
 *  
 *  \param pI2cDevice Pointer to the I2c device
 *  
 *  \return  return total number of received bytes
 *  
 *  \note Use this function only when I2c is configured in interrupt mode
 */
extern int32_t epcf_i2c_getRxBufferCount(EPCFI2cDevice_t* pI2cDevice);

/**
 *  This function is used to flush I2c receive buffer.
 *  
 *  \param pI2cDevice Pointer to the I2c device
 *  
 *  \return  return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *  
 *  \note Use this function only when I2c is configured in interrupt mode
 */
extern int8_t epcf_i2c_rxBufferFlush(EPCFI2cDevice_t* pI2cDevice);
  

 /**
 *  This function is used to get number of bytes pending in I2c transmit buffer.
 *  
 *  \param pI2cDevice Pointer to the I2c device
 *  
 *  \return  return total number of pending bytes
 *  
 *  \note Use this function only when I2c is configured in interrupt mode
 */
extern int32_t epcf_i2c_getTxBufferCount(EPCFI2cDevice_t* pI2cDevice);

/**
 *  This function is used to flush I2c transmit buffer.
 *  
 *  \param pI2cDevice Pointer to the I2c device
 *  
 *  \return  return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *  
 *  \note Use this function only when I2c is configured in interrupt mode
 */
extern int8_t epcf_i2c_txBufferFlush(EPCFI2cDevice_t* pI2cDevice);

 /**
 *  \brief This function is used to close the I2c device. It will free the memory allocated by the I2c device.
 *  
 *  \param pI2cDevice Pointer to the I2c device.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_i2c_close(EPCFI2cDevice_t* pI2cDevice);

 /**
 *  \brief This function is used to get the total number of available I2c devices.
 *  
 *  \return Returns the number of available I2c devices.
 */
extern uint8_t epcf_i2c_getDeviceCount();

#ifdef EPCF_USING_MT_ENV
// TODO : Adding the Support for EPCF_USING_MT_ENV
// TODO : Add Comments for Function Discription.
/**
 *  \brief
 *  
 *  \param      pI2cDevice      Pointer to the i2c device. 
 *
 * \return  Returns the lock status for i2c device.
 */
extern int8_t epcf_i2c_lock(EPCFI2cDevice_t* pI2cDevice);

/**
 *  \brief
 *  
 *  \param      pI2cDevice      Pointer to the i2c device. 
 *
 * \return  Returns the unlock status for i2c device.
 */
extern int8_t epcf_i2c_unlock(EPCFI2cDevice_t* pI2cDevice);
#endif

#endif      //__EPCF_PERIPHERAL_INCLUDE_I2C_I2C_H
