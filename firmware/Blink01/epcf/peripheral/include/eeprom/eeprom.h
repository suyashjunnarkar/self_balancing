/**
 *  \file  eeprom.h
 *  \brief This file is used to configure a Eeprom device
 */
 
#ifndef __EPCF_INCLUDED_PERIPHERAL_INCLUDE_EEPROM_EEPROM_H
#define __EPCF_INCLUDED_PERIPHERAL_INCLUDE_EEPROM_EEPROM_H

/** \brief  Eeprom device           */
typedef struct EPCFEepromDevice EPCFEepromDevice_t;

/** \brief 8-bit read/write mode of eeprom      */
typedef enum
{
    enEPCFEepromDataBits_8,     /**< 8-bits eeprom read/write               */
    enEPCFEepromDataBits_16,    /**< 16-bits eeprom read/write              */
    enEPCFEepromDataBits_32,    /**< 32-bits eeprom read/write              */
    enEPCFEepromDataBits_Max    /**< Special value for boundary checking    */
}EnEPCFEepromDataBits_t;

/**
 *  \brief  Eeprom configuration structure      
 *  
 *  Example to configure eeprom device:
 *  
 *  EPCFEepromCfg_t eepromConfig = 
 *  {
 *    enEPCFEepromDataBits_8,   // 8-bits eeprom read/write
 *    0                         // Page management not supported
 *    enEPCFBooleanFalse,       // Disable eeprom interrupt
 *    0,                        // Not required in polling mode
 *    0,                        // Not required in polling mode
 *    NULL                      // No hardware specific config
 *  };
 */
typedef struct
{
    EnEPCFEepromDataBits_t  dataBits;           /**< Specifies number of bits for eeprom read/write operations                      */
    
    uint32_t                pageSize;           /**< Specifies page size in bytes. Pass 0 if page management is not supported       */
    
    EnEPCFBoolean_t         interruptEnable;    /**< Specifies to enable eeprom interrupt or not
                                                     enEPCFBooleanTrue  = To enable eeprom interrupt
                                                     enEPCFBooleanFalse = To disable eeprom interrupt(polling mode)                 */

    uint32_t                txBufferSize;       /**< Specifies the write buffer size in bytes when using eeprom in interrupt mode
                                                     Pass 0 when eeprom is configured in polling mode                               */

    uint32_t                rxBufferSize;       /**< Specifies the read buffer size in bytes when using eeprom in interrupt mode
                                                     Pass 0 when eeprom is configured in polling mode                               */

    void*                   hardwareCfg;        /**< Hardware platform specific configuration, pass NULL for default configuration  */
}EPCFEepromCfg_t;

/**
 *  \brief This function is used to create an eeprom device. Call this function in beginning to initialize the device.
 *         This function allocates memory for the device using malloc() function call and returns a pointer to the device. 
 *         Pass this device pointer while calling eeprom functions.
 *
 *  \param pEepromConfig Pointer to the eeprom configuration structure.
 *
 *  \return On success, it return the pointer to eeprom device.
 *          On error, it returns NULL. 
 */
extern EPCFEepromDevice_t* epcf_eeprom_CreateNative(EPCFEepromCfg_t* pEepromConfig);

#ifdef EPCF_SUPPORT_EXTENDED_EEPROM

/** \brief Eeprom Controller   */
typedef struct EPCFEepromController EPCFEepromController_t;

/** 
 *  \brief  This function is used to create a eeprom device in extended mode. Before calling this function,
 *  		user should create an adapter for communication between host and extended device.
 *        	For detail explaination, see ../../../../extended/adapter/adapter.h
 *        	Then, user should create a controller for controlling extended device from host.
 *   	  	Call this function in beginning to initialize the eeprom device. 
 *  		This function allocates memory for the device using malloc() function call and returns a pointer to the device.
 *  		Pass this device pointer while calling eeprom functions.
 *   
 *  \param   pEepromConfig   Pointer to the eeprom configuration structure.
 *  \param   pEepromController  Pointer to the eeprom Controller to which eeprom device will be attached.
 *   
 *  \return On success, it return the pointer to eeprom device.
 *          On error, it returns NULL.
 */
extern EPCFEepromDevice_t* epcf_eeprom_createExtended(EPCFEepromController_t* pEepromController, EPCFEepromCfg_t* pEepromConfig);

/**
 *   \brief This function returns total number of available eeprom devices on an extended controller.
 *   
 *   \param      pEepromController  Pointer to the eeprom controller.
 *   
 *   \return Returns the number of available eeprom devices on extended bound controller.
 *           Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern epcf_eeprom_extGetDeviceCount(EPCFEepromController_t* pEepromController);

#endif

 /**    
 *  \brief This function is used to write data in eeprom memory.
 *         In Interrupt mode, write operation will be asynchronous and the data is written using 
 *         internal software buffer. The function will be non blocking and will return after initiating data 
 *         write operation. Use epcf_eeprom_getTxBufferCount function to check the status of the write buffer.
 *
 *         In Polling mode, data write operation will be synchronous and calling function will be blocked until
 *         all the data is written or timeout has occurred.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  \param offset        Address offset.Refer to platform specific header file for appropriate address range
 *                       Write operations to a misaligned address will result in an error response.
 *                       For example: a 32-bit(dataBits = enEPCFEepromDataBits_32) write operation to an address offset 
 *                       other than a multiple of 0x4 will result into error.
 *  \param data          Pointer to buffer where data to be written is stored
 *  \param size          Total number of bytes to write
 *  \param timeout       timeout value
 *
 *  \return  return total number of bytes written in eeprom memory. Check status code if return value is less than 0. 
 *           Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note    If value of dataBits is set to greater than 8 bits. Then, 2 consecutive bytes will represent
 *           1 single data word. In this case value of size should be in a multiple of 2. If the value of size
 *           is an odd value, then a 0 is padded as the last byte of the data.
 */
extern int32_t epcf_eeprom_write(EPCFEepromDevice_t* pEepromDevice,uint32_t offset,uint8_t* data,uint32_t size,EPCFTime_t timeout);

 /**
 *  \brief This function is used to read data from eeprom memory.
 *         In Interrupt mode, data read is asyncronous and data is read in an internal software buffer.
 *         Use epcf_eeprom_getRxBufferCount function to get read buffer count. When the count is equal to the 
 *         required number of bytes to be read, call epcf_eeprom_read function to read the buffer.
 *
 *         In Polling mode, data read will be synchronous and calling function will be blocked until
 *         all the data is received or timeout has occurred.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  \param offset        Address offset. Refer to platform specific header file for appropriate address range
 *                       Read operations to a misaligned address will result in an error response.
 *                       For example: a 32-bit(dataBits = enEPCFEepromDataBits_32) read operation to an address offset other
 *                       than a multiple of 0x4 will result into error.
 *  \param data          Pointer to buffer where data to be read is stored
 *  \param size          Total number of bytes to be read
 *  \param timeout       timeout value
 *
 *  \return  return number of bytes read from eeprom memory. Check status code if return value is less than 0. 
 *           Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note    If value of dataBits is set to greater than 8 bits. Then, 2 consecutive bytes will represent
 *           1 single data word. In this case value of size should be in a multiple of 2. If the value of size
 *           is an odd value, then a 0 is padded as the last byte of the data.
 */
extern int32_t epcf_eeprom_read(EPCFEepromDevice_t* pEepromDevice,uint32_t offset,uint8_t* data,uint32_t size,EPCFTime_t timeout);
 
 /**
 *  \brief This function is used to erase data from eeprom memory.
 *         Calling function will be blocked until all the data is erased or timeout has occurred.
 *         The function is a blocking call in both interrupt and polling mode.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  \param offset        Address offset.Refer to platform specific header file for appropriate address range
 *                       Erase operations to a misaligned address will result in an error response.
 *                       For example: a 32-bit(dataBits = enEPCFEepromDataBits_32) erase operation to an address offset other
 *                       than a multiple of 0x4 will result into error.
 *  \param size          Total number of bytes to erase
 *  \param timeout       timeout value
 *
 *  \return  return total number of bytes erased from eeprom memory. Check status code if return value is less than 0. 
 *           Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_eeprom_erase(EPCFEepromDevice_t* pEepromDevice,uint32_t offset,uint32_t size,EPCFTime_t timeout);

 /**    
 *  \brief This function is used to write data in a page in eeprom memory.
 *         In Interrupt mode, write operation will be asynchronous and the data is written using 
 *         internal software buffer. The function will be non blocking and will return after initiating data 
 *         write operation. Use epcf_eeprom_getTxBufferCount function to check the status of the write buffer.
 *
 *         In Polling mode, data write operation will be synchronous and calling function will be blocked until
 *         all the data is written or timeout has occurred.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  \param pageAddress   Address of the specific page of eeprom
 *  \param offset        Address offset.Refer to platform specific header file for appropriate address range
 *                       Write operations to a misaligned address will result in an error response.
 *                       For example: a 32-bit(dataBits = enEPCFEepromDataBits_32) write operation to an address offset
 *                       other than a multiple of 0x4 will result into error.
 *  \param data          Pointer to buffer where data to be written is stored
 *  \param size          Total number of bytes to write.
 *  \param timeout       timeout value
 *
 *  \return  return total number of bytes written in eeprom memory. Check status code if return value is less than 0. 
 *           Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note    If page management is not supported in the eeprom this function will return an appropriate error response.
 *
 *           If value of dataBits is set to greater than 8 bits. Then, 2 consecutive bytes will represent
 *           1 single data word. In this case value of size should be in a multiple of 2. If the value of size
 *           is an odd value, then a 0 is padded as the last byte of the data.
 */
extern int32_t epcf_eeprom_pageWrite(EPCFEepromDevice_t* pEepromDevice,uint32_t pageAddress,uint32_t offset,uint8_t* data,uint32_t size,EPCFTime_t timeout);

 /**
 *  \brief This function is used to read data from a page in eeprom memory.
 *         In Interrupt mode, data read is asyncronous and data is read in an internal software buffer.
 *         Use epcf_eeprom_getRxBufferCount function to get read buffer count. When the count is equal to the 
 *         required number of bytes to be read, call epcf_eeprom_read function to read the buffer.
 *
 *         In Polling mode, data read will be synchronous and calling function will be blocked until
 *         all the data is received or timeout has occurred.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  \param pageAddress   Address of the specific page of eeprom
 *  \param offset        Address offset. Refer to platform specific header file for appropriate address range
 *                       Read operations to a misaligned address will result in an error response.
 *                       For example: a 32-bit(dataBits = enEPCFEepromDataBits_32) read operation to an address offset other
 *                       than a multiple of 0x4 will result into error.
 *  \param data          Pointer to buffer where data to be read is stored
 *  \param size          Total number of bytes to be read
 *  \param timeout       timeout value
 *
 *  \return  return number of bytes read from eeprom memory. Check status code if return value is less than 0. 
 *           Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note    If page management is not supported in the eeprom this function will return an appropriate error response.
 *            
 *           If value of dataBits is set to greater than 8 bits. Then, 2 consecutive bytes will represent
 *           1 single data word. In this case value of size should be in a multiple of 2. If the value of size
 *           is an odd value, then a 0 is padded as the last byte of the data.
 */
extern int32_t epcf_eeprom_pageRead(EPCFEepromDevice_t* pEepromDevice,uint32_t pageAddress,uint32_t offset,uint8_t* data,uint32_t size,EPCFTime_t timeout);
 
 /**
 *  \brief This function is used to erase a page in eeprom memory.
 *         Calling function will be blocked until all the data is erased or timeout has occurred.
 *         The function is a blocking call in both interrupt and polling mode.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  \param pageAddress   Address of the specific page of eeprom
 *  \param timeout       timeout value
 *
 *  \return  Check status code if return value is less than 0. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note    If page management is not supported in the eeprom this function will return an appropriate error response.
 */
extern int8_t epcf_eeprom_pageErase(EPCFEepromDevice_t* pEepromDevice,uint32_t pageAddress,EPCFTime_t timeout);

 /**
 *  This function is used to get number of bytes read in eeprom read buffer.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  
 *  \return  return total number of read bytes
 *
 *  \note Use this function only when eeprom is configured in interrupt mode
 */
extern int32_t epcf_eeprom_getRxBufferCount(EPCFEepromDevice_t* pEepromDevice);

/**
 *  This function is used to flush eeprom read buffer.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  
 *  \return  return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note Use this function only when Eeprom is configured in interrupt mode
 */
extern int8_t epcf_eeprom_rxBufferFlush(EPCFEepromDevice_t* pEepromDevice);

/**
 *  This function is used to get number of bytes pending in eeprom write buffer.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  
 *  \return  return total number of pending bytes
 *
 *  \note Use this function only when eeprom is configured in interrupt mode
 */
extern int32_t epcf_eeprom_getTxBufferCount(EPCFEepromDevice_t* pEepromDevice);

/**
 *  This function is used to flush eeprom write buffer.
 *
 *  \param pEepromDevice Pointer to the eeprom device
 *  
 *  \return  return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note Use this function only when eeprom is configured in interrupt mode
 */
extern int8_t epcf_eeprom_txBufferFlush(EPCFEepromDevice_t* pEepromDevice);

 /**
 *  \brief This function is used to close the eeprom device. It will free the memory allocated by the eeprom device.
 *
 *  \param pEepromDevice Pointer to the eeprom device.
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_eeprom_close(EPCFEepromDevice_t* pEepromDevice);


 /**
 *  \brief This function is used to get the total number of available eeprom devices.
 *
 *  \return Returns the number of available eeprom devices.
 */
extern int8_t epcf_eeprom_getDeviceCount();

#ifdef EPCF_USING_MT_ENV
// TODO : Adding the Support for EPCF_USING_MT_ENV
// TODO : Add Comments for Function Discription.
/**
 *  \brief
 *  
 *  \param      pEepromDevice      Pointer to the eeprom device. 
 *
 * \return  Returns the lock status for eeprom device.
 */
extern int8_t epcf_eeprom_lock(EPCFEepromDevice_t* pEepromDevice);

/**
 *  \brief
 *  
 *  \param      pEepromDevice      Pointer to the eeprom device. 
 *
 * \return  Returns the unlock status for eeprom device.
 */
extern int8_t epcf_eeprom_unlock(EPCFEepromDevice_t* pEepromDevice);
#endif
#endif      //__EPCF_INCLUDED_PERIPHERAL_INCLUDE_EEPROM_EEPROM_H
