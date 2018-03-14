/**
 * \file  spi.h
 * \brief This file is used to configure a Spi device
 */
 
#ifndef __EPCF_INCLUDED_PERIPHERAL_INCLUDE_SPI_SPI_H
#define __EPCF_INCLUDED_PERIPHERAL_INCLUDE_SPI_SPI_H

/** \brief  Spi device          */
typedef struct EPCFSpiDevice EPCFSpiDevice_t;

/** \brief Spi mode       */
typedef enum
{
    enEPCFSpiMode_Master,       /**< Spi in master mode     */
    enEPCFSpiMode_Slave,        /**< Spi in slave mode      */
    enEPCFSpiMode_Max           /**< Special value for boundary checking        */
}EnEPCFSpiMode_t;

/** \brief Spi clock modes       */
typedef enum
{
    enEPCFSpiClockMode_0,       /**< Spi clock mode 0: Phase 0, Polarity 0      */
    enEPCFSpiClockMode_1,       /**< Spi clock mode 1: Phase 0, Polarity 1      */
    enEPCFSpiClockMode_2,       /**< Spi clock mode 2: Phase 1, Polarity 0      */
    enEPCFSpiClockMode_3,       /**< Spi clock mode 3: Phase 1, Polarity 1      */
    enEPCFSpiClockMode_Max      /**< Special value for boundary checking        */
}EnEPCFSpiClockMode_t;

/** \brief Data order of spi data exchange      */
typedef enum
{
    enEPCFSpiBitOrder_Msb,      /**< Most significant bit first             */
    enEPCFSpiBitOrder_Lsb,      /**< Least significant bit first            */
    enEPCFSpiBitOrder_Max       /**< Special value for boundary checking    */
}EnEPCFSpiBitOrder_t;

/** Number of data bits in spi frame     */
typedef enum
{
    enEPCFSpiDataBits_4,    /**< 4 data bits    */
    enEPCFSpiDataBits_5,    /**< 5 data bits    */
    enEPCFSpiDataBits_6,    /**< 6 data bits    */
    enEPCFSpiDataBits_7,    /**< 7 data bits    */
    enEPCFSpiDataBits_8,    /**< 8 data bits    */
    enEPCFSpiDataBits_9,    /**< 9 data bits    */
    enEPCFSpiDataBits_10,   /**< 10 data bits   */
    enEPCFSpiDataBits_11,   /**< 11 data bits   */
    enEPCFSpiDataBits_12,   /**< 12 data bits   */
    enEPCFSpiDataBits_13,   /**< 13 data bits   */
    enEPCFSpiDataBits_14,   /**< 14 data bits   */
    enEPCFSpiDataBits_15,   /**< 15 data bits   */
    enEPCFSpiDataBits_16,   /**< 16 data bits   */
    enEPCFSpiDataBits_Max   /**< Special value for boundary checking    */
}EnEPCFSpiDataBits_t;

/** \breif Interrupt type */
typedef enum
{
    enEPCFSpiIntRx_Overrun,         /**< Enable receive overrun interrupt               */
    enEPCFSpiIntRx_Timeout,         /**< Enable receive timeout interrupt               */
    enEPCFSpiIntRx_BuffHalfFull,    /**< Enable receive buffer half full interrupt      */
    enEPCFSpiInt_Max,               /**<  Special value for boundary checking           */
}EnEPCFSpiIntType;

/** Spi configuration structure     
    Example to configure spi device in master mode
    EPCFSpiCfg_t spiConfig = 
    {
        0,                          // spi id 0
        100000,                     // 100khz baudrate
        enEPCFSpiMode_Master,       // Configure spi in master mode
        enEPCFSpiClockMode_0,       // Set clock mode 0
        enEPCFSpiBitOrder_Msb,      // MSB to be transmitted first
        enEPCFSpiDataBits_8,        // 8 data bits in spi frame
        enEPCFBooleanTrue,          // Enable spi interrupt
        256,                        // Tx buffer size = 256 bytes
        256,                        // Rx buffer size = 256 bytes
        NULL                        // No hardware specific config
    };
    
    Example to configure spi device in slave mode
    EPCFSpiCfg_t spiConfig = 
    {
        0,                          // spi id 0
        100000,                     // 100khz baudrate
        enEPCFSpiMode_Slave,        // Configure spi in slave mode
        enEPCFSpiClockMode_0,       // Set clock mode 0
        enEPCFSpiBitOrder_Msb,      // MSB to be transmitted first
        enEPCFSpiDataBits_16,       // 16 data bits in spi frame
        enBooleanFalse,             // Disable spi interrupt
        0,                          // Not required in polling mode
        0,                          // Not required in polling mode
        NULL                        // No hardware specific config
    };
*/
typedef struct 
{
    uint8_t                 spiId;              /**< Spi Id. Refer to platform specific header file for appropriate spi id          */
    
    uint32_t                baudrate;           /**< Baudrate for spi communication in bits/second  */
    
    EnEPCFSpiMode_t         spiMode;            /**< Specifies spi mode                             */
    
    EnEPCFSpiClockMode_t    clockMode;          /**< Specifies spi clock mode                       */
    
    EnEPCFSpiBitOrder_t     bitOrder;           /**< Specifies bit order for spi data exchange      */
    
    EnEPCFSpiDataBits_t     dataBits;           /**< Specifies number of data bits in spi frame     */
    
    EnEPCFBoolean_t         interruptEnable;    /**< Specifies to enable spi interrupt or not       */

    EnEPCFSpiIntType        intType;            /**< Specifies interrupt type                       */
    
    uint32_t                txBufferSize;       /**< Specifies the transmit buffer size in bytes when using spi in interrupt mode
                                                     Pass 0 when spi is configured in polling mode                                  */
    
    uint32_t                rxBufferSize;       /**< Specifies the receive buffer size in bytes when using spi in interrupt mode
                                                     Pass 0 when spi is configured in polling mode                                  */

    void*                   hardwareCfg;        /**< Hardware platform specific configuration, pass NULL for default configuration  */
}EPCFSpiCfg_t;



/**
 * \brief This function is used to create an spi device. Call this function in beginning to initialize the device.
 *        This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer 
 *        while calling spi functions.
 *
 * \param pSpiConfig Pointer to the spi configuration structure.
 *
 * \return On success, it return the pointer to spi device.
 *         On error, it returns NULL. 
 */
extern EPCFSpiDevice_t* epcf_spi_createNative(EPCFSpiCfg_t* pSpiConfig);

#ifdef  EPCF_SUPPORT_EXTENDED_SPI

typedef struct EPCFSpiController EPCFSpiController_t;

/**
 *  \brief This function is used to create an spi device in extended mode.
 *          Before calling this function, user should create an adapter for communication between host and extended device.
 *          For detail explaination, see ../../../../extended/adapter/adapter.h
 *          Then, user should create a controller for controlling extended device from host.
 *          Call this function in beginning to initialize the device. This function allocates memory for the device using malloc() function call and returns a pointer to the device.
 *          Pass this device pointer while calling spi functions.
 *
 *  \param pSpiController Pointer to the spi controller structure.
 *  \param pSpiConfig Pointer to the spi configuration structure.
 *
 *  \return On success, it return the pointer to spi device.
 *         On error, it returns NULL. 
 */
extern EPCFSpiDevice_t* epcf_spi_createExtended(EPCFSpiController_t* pSpiController, EPCFSpiCfg_t* pSpiConfig);

 /**
 *  \brief This function is used to get the total number of available spi devices in extended mode.
 *  
 *  \param pSpiController Pointer to the spi controller structure.
 *
 *  \return Returns the number of available spi devices.
 */
extern uint8_t epcf_spi_extGetDeviceCount(EPCFSpiController_t* pSpiController);

#endif

/**
 *  \brief This function is used to register a spi slave device. Call this function once in the begining to register slaveSelectPin of the
 *         slave device should be registered before doing any read write operation for that device.
 *         The function will return a slaveId which can be used to select and unselect the slave device using epcf_spi_slaveSelect and
 *         epcf_spi_slaveDeSelect function respectively.
 *  
 *  \param  pSpiDevice      Pointer to the spi device
 *  \param  slaveSelectPin  slaveSelectPin information of the slave device
 *  
 *  \return return slaveId. Check status code in case return value is less than 0. 
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note   Use this function only when using spi in master mode.
 */
extern int8_t epcf_spi_registerSlaveDevice(EPCFSpiDevice_t* pSpiDevice,EPCFPortPin_t slaveSelectPin);

/**
 *  \brief This function is used to unregister a spi slave device. No operation on the slave device is possible once it is 
 *         unregistered. Register the slave device again to operate on the device once it is unregistered.
 *
 *  \param  pSpiDevice      Pointer to the spi device
 *  \param  slaveId         slaveId returned by epcf_spi_registerSlaveDevice function
 *  
 *  \return Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note   Use this function only when using spi in master mode.
 */
extern int8_t epcf_spi_deRegisterSlaveDevice(EPCFSpiDevice_t* pSpiDevice,uint8_t slaveId);

/**
 * \brief This function is used to select the slave device on the spi bus before starting any communication with the device.
 *
 * \param   pSpiDevice      Pointer to the spi device
 * \param   slaveId         slaveId of the slave device
 *
 * \return  Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note   Use this function only when using spi in master mode.
 */
extern int8_t epcf_spi_slaveSelect(EPCFSpiDevice_t* pSpiDevice, uint8_t slaveId);

/**
 * \brief This function is used to unselect the slave device after communication with the device is finished.
 *
 * \param   pSpiDevice      Pointer to the spi device
 * \param   slaveId         slaveId of the slave device
 *
 * \return  Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note   Use this function only when using spi in master mode.
 */
extern int8_t epcf_spi_slaveDeSelect(EPCFSpiDevice_t* pSpiDevice, uint8_t slaveId);

/**
 * \brief This function is used to exchange a single frame over spi bus. It can be used in both master and slave mode.
 *        The size of the frame is according to setting of the dataBits field in spi configuration.
 *        The calling function will be blocked until the data frame is exchanged or timeout has occurred.
 *        The function is a blocking call in both interrupt and polling mode.
 *
 * \param   pSpiDevice  Pointer to the spi device
 * \param   txData      data frame to be transmitted
 * \param   rxData      Pointer to the data frame where received data will be stored
 * \param   timeout     timeout value
 
 * \return  returns 1 when frame is successfully exchanged. Check status code in case return value is less than 0. 
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note    Master mode(master write):
 *          1. Call epcf_spi_slaveSelect function to select the slave device.
 *          2. Call epcf_spi_exchange function to exchange a single frame from the slave device.
 *          3. Call epcf_spi_slaveDeSelect function to unselect the slave device.
 *
 *          Slave mode(Slave write): 
 *          Call this function to write data to the master device.
 */
extern int8_t epcf_spi_exchange(EPCFSpiDevice_t* pSpiDevice,uint16_t txData,uint16_t* rxData,EPCFTime_t timeout);

 /**    
 * \brief This function is used to send data on spi bus. It can be used in both master and slave mode.
 *        In Interrupt mode, data transmission will be asynchronous and the data is transmitted using
 *        internal software buffer. The function will be non blocking and will return after initiating data 
 *        transmission. Use epcf_spi_getTxBufferCount function to check the status of the transmit buffer.
 *
 *        In Polling mode, data transmission will be synchronous and calling function will be blocked until
 *        all the data is transmitted or timeout has occurred.
 *
 * \param pSpiDevice    Pointer to the spi device
 * \param data          Pointer to buffer where data to be written is stored
 * \param size          Total number of bytes to send
 * \param timeout       timeout value.
 *
 * \return  return total number of bytes send over spi bus. Check status code if return value is less than 0. 
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note    If value of dataBits is set to greater than 8 bits. Then, 2 consecutive bytes will represent
 *          1 single frame. In this case value of size should be in a multiple of 2. If the value of size
 *          is an odd value, then a 0 is padded as the last byte of the data.
 *
 *          Master mode(master write):
 *          1. Call epcf_spi_slaveSelect function to select the slave device.
 *          2. Call epcf_spi_write function to send data to the slave.
 *          3. Call epcf_spi_slaveDeSelect function to de-select the slave device after data transmission is completed.
 *
 *          Slave mode(Slave write): 
 *          Call this function to write data to the master device.
 */
extern int8_t epcf_spi_write(EPCFSpiDevice_t* pSpiDevice,const uint8_t* data,uint32_t size,EPCFTime_t timeout);

 /**
 * \brief This function is used to read data on spi bus. This function can be used in both master and slave mode.
 *        In Interrupt mode, data receiving is asynchronous and data is received in an internal software buffer.
 *        Use epcf_spi_getRxBufferCount function to get receive buffer count. When the count is equal to the 
 *        required number of bytes to be read, call epcf_spi_read function to read the buffer.
 *
 *        In Polling mode, data receiving will be synchronous and calling function will be blocked until
 *        all the data is received or timeout has occurred.
 *
 * \param pSpiDevice    Pointer to the spi device
 * \param data          Pointer to buffer where data to be read is stored
 * \param size          Total number of bytes to be read
 * \param timeout       timeout value.
 *
 * \return  return number of bytes read over spi bus. Check status code if return value is less than 0. 
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note    If value of dataBits is set to greater than 8 bits. Then, 2 consecutive bytes will represent
 *          1 single frame. In this case value of size should be in a multiple of 2. If the value of size
 *          is an odd value, then a 0 is padded as the last byte of the data.
 * 
 *          Master mode(master read):
 *          1. Call epcf_spi_slaveSelect function to select the slave device.
 *          2. Call epcf_spi_read function to read data from the slave.
 *          3. Call epcf_spi_slaveDeSelect function to de-select the slave device after data reception is completed.
 *
 *          Slave mode(slave read):
 *          Call this function to read data received from the master device.
 */
extern int8_t epcf_spi_read(EPCFSpiDevice_t* pSpiDevice,uint8_t* data,uint32_t size,EPCFTime_t timeout);

/**
 * \brief This function is used to enable the spi interrupt.It can be disabled by a call to the function epcfNativeSpiIntDisable.
 *
 *  \param pSpiDevice Pointer to the spi device.
 *  \param intType type of interrupt
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_spi_intEnable(EPCFSpiDevice_t* pSpiDevice,EnEPCFSpiIntType intType);

/**
 * \brief This function is used to disable the spi interrupt.It can be enable by a call to the function epcfNativeSpiIntEnable.
 *
 *  \param pSpiDevice Pointer to the spi device.
 *  \param intType type of interrupt
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_spi_intDisable(EPCFSpiDevice_t* pSpiDevice , EnEPCFSpiIntType intType);

/**
 * This function is used to get number of bytes received in spi receive buffer.
 *
 * \param pSpiDevice Pointer to the spi device
 * 
 * \return  return total number of received bytes
 *
 * \note Use this function only when spi is configured in interrupt mode
 */
extern int32_t epcf_spi_getRxBufferCount(EPCFSpiDevice_t* pSpiDevice);

/**
 * This function is used to flush spi receive buffer.
 *
 * \param pSpiDevice Pointer to the spi device
 * 
 * \return  return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note Use this function only when spi is configured in interrupt mode
 */
extern int8_t epcf_spi_rxBufferFlush(EPCFSpiDevice_t* pSpiDevice);

 /**
 * This function is used to get number of bytes pending in spi transmit buffer.
 *
 * \param pSpiDevice Pointer to the spi device
 * 
 * \return  return total number of pending bytes
 *
 * \note Use this function only when spi is configured in interrupt mode
 */
extern int32_t epcf_spi_getTxBufferCount(EPCFSpiDevice_t* pSpiDevice);

/**
 * This function is used to flush spi transmit buffer.
 *
 * \param pSpiDevice Pointer to the spi device
 * 
 * \return  return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note Use this function only when spi is configured in interrupt mode
 */
extern int8_t epcf_spi_txBufferFlush(EPCFSpiDevice_t* pSpiDevice);

 /**
 * \brief This function is used to close the spi device. It will free the memory allocated by the spi device.
 *
 * \param pSpiDevice Pointer to the spi device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_spi_close(EPCFSpiDevice_t* pSpiDevice);

 /**
 * \brief This function is used to get the total number of available spi devices.
 *
 * \return Returns the number of available spi devices.
 */
extern uint8_t epcf_spi_getDeviceCount();

#ifdef EPCF_USING_MT_ENV
//ToDo: Adding support for EPCF_USING_MT_ENV
//ToDo: Add comment for function description
extern int8_t epcf_spi_lock(EPCFSpiDevice_t* pSpiDevice);
extern int8_t epcf_spi_unlock(EPCFSpiDevice_t* pSpiDevice);

#endif  //EPCF_USING_MT_ENV

#endif      //__EPCF_INCLUDED_PERIPHERAL_INCLUDED_SPI_SPI_H
