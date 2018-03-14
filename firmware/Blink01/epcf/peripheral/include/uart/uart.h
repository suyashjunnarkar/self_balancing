/**
 * \file  uart.h
 * \brief This file is used to configure a Uart device
 */

#ifndef __EPCF_INCLUDED_PERIPHERAL_INCLUDE_UART_UART_H
#define __EPCF_INCLUDED_PERIPHERAL_INCLUDE_UART_UART_H


/** \brief  Uart device         */
typedef struct EPCFUartDevice EPCFUartDevice_t;

/** \brief  Uart supported baudrate  */
typedef enum
{
    enEPCFUartBaudrate_2400 = 0,    /**< Baudrate 2400    */
    enEPCFUartBaudrate_4800,        /**< Baudrate 4800    */
    enEPCFUartBaudrate_9600,        /**< Baudrate 9600    */
    enEPCFUartBaudrate_19200,       /**< Baudrate 19200   */
    enEPCFUartBaudrate_38400,       /**< Baudrate 38400   */
    enEPCFUartBaudrate_57600,       /**< Baudrate 57600   */
    enEPCFUartBaudrate_115200,      /**< Baudrate 115200  */
    enEPCFUartBaudrate_Max          /**< Special value for boundary checking    */
}EnEPCFUartBaudrate_t;

/** \brief Uart supported data bits   */
typedef enum
{
    enEPCFUartDatabits_5 = 5,   /**< Databits 5  */
    enEPCFUartDatabits_6 = 6,   /**< Databits 6  */
    enEPCFUartDatabits_7 = 7,   /**< Databits 7  */
    enEPCFUartDatabits_8 = 8,   /**< Databits 8  */
    enEPCFUartDatabits_Max      /**< Special value for boundary checking    */
}EnEPCFUartDataBits_t;

/** \brief  Uart supported parity bits */
typedef enum
{
    enEPCFUartParity_None = 0,  /**< No parity           */
    enEPCFUartparity_Odd,       /**< Odd parity          */
    enEPCFUartParity_Even,      /**< Even parity         */
    enEPCFUartParity_One,       /**< Forced one parity   */
    enEPCFUartParity_Zero,      /**< Forced zero parity  */
    enEPCFUartParity_Max        /**< Special value for boundary checking    */
}EnEPCFUartParity_t;

/** \brief  Enumeration for number of stop bits to use for UART channel  */
typedef enum
{
    enEPCFUartStopBits_1  = 1,  /**< One stop bit   */
    enEPCFUartStopBits_2  = 2,  /**< Two stop bits  */
    enEPCFUartStopBits_Max       /**< Special value for boundary checking   */
}EnEPCFUartStopBits_t;

typedef enum {
	enEPCFUartIntType_None = 0,				/**< Uart Interrupt None		 			*/
	enEPCFUartIntType_RX,					/**< Uart Receiver Interrupt 			*/
	enEPCFUartIntType_TX,					/**< Uart Transmit Interrupt 			*/
	enEPCFIntType_Max						/**< Special value for boundary checking*/
} EnEPCFUartIntType_t;

typedef struct EPCFUartCfg
{
    uint8_t                 uartId;             /**< Uart Id. Refer to platform specific header file for appropriate uart id  */
    
    EnEPCFUartBaudrate_t    baudrate;           /**< Baudrate for uart communication in bits/second                           */
    
    EnEPCFUartDataBits_t    dataBits;           /**< Specifies number of data bits in uart frame                              */
    
    EnEPCFUartParity_t      parity;             /**< Specifies parity to be used for communication                            */
    
    EnEPCFUartStopBits_t    stopBits;           /**< Specifies number of stop bits                                            */
    
    EnEPCFBoolean_t     interruptEnable;    /**< Specifies to enable uart interrupt or not     */
                                                     
    uint32_t                txBufferSize;       /**< Specifies the transmit buffer size in bytes when using uart in interrupt mode
                                                     Pass 0 when uart is configured in polling mode                                 */
    
    uint32_t                rxBufferSize;       /**< Specifies the receive buffer size in bytes when using uart in interrupt mode
                                                     Pass 0 when uart is configured in polling mode                                 */

    void*                   hardwareCfg;        /**< Hardware platform specific configuration, pass NULL for default configuration  */
}EPCFUartCfg_t;


/**
 * \brief This function is used to create an uart device. Call this function in beginning to initialize the device.
 *        This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer
 *        while calling uart functions.
 *
 * \param pUartConfig Pointer to the uart configuration structure.
 *
 * \return On success, it return the pointer to uart device.
 *         On error, it returns NULL.
 */
extern EPCFUartDevice_t* epcf_uart_createNative(EPCFUartCfg_t* pUartConfig);

#ifdef	EPCF_SUPPORT_EXTENDED_UART

/** \brief  uart controller structure    */
typedef struct EPCFUartController EPCFUartController_t;

/**
 * \brief This function is used to create an extended uart device .
 *        Before calling this function, user should create an adapter for communication between host and extended device.
 *        For detail explaination, see ../../../../extended/adapter/adapter.h
 *        Then, user should create a controller for controlling extended device from host.
 *        This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer
 *        while calling other uart functions.
 *  
 * \param pUartController pointer to uart controller structure
 * \param pUartConfig Pointer to the uart configuration structure.
 *  
 * \return On success, it return the pointer to uart device.
 *          On error, it returns NULL.
 */
extern EPCFUartDevice_t* epcf_uart_createExtended(EPCFUartController_t* pUartController, EPCFUartCfg_t* pUartConfig);

/**
 * \brief This function is used to get the total number of available uart devices in extended mode.
 *  
 * \param pUartController pointer to uart controller structure
 *
 * \return number of uart channels available to work on
 */
extern uint8_t epcf_uart_extGetDeviceCount(EPCFUartController_t* pUartController);

#endif	//EPCF_SUPPORT_EXTENDED_UART

/**
 * \brief This function is used to send data over uart channel. Use this function in interrupt mode.
 *        Data transmission will be asynchronous and the data is transmmitted using 
 *        internal software buffer. The function will be non blocking and will return after initiating data 
 *        transmission. Use epcf_uart_getTxBufferCount function to check the status of the transmit buffer.
 *
 *        In Polling mode, data transmission will be synchronous and calling function will be blocked until
 *        all the data is transmitted or timeout has occurred.
 *  
 * \param pUartDevice Pointer to uart device structure.
 * \param data        Pointer to buffer where data to be written is stored.
 * \param size        Total number of bytes to send
 * \param timeout     Timeout value.
 
 *  \return return total number of bytes sent over uart channel. Check status code in case return value is less than 0.
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int32_t epcf_uart_write(EPCFUartDevice_t* pUartDevice, const uint8_t* data, uint32_t size, EPCFTime_t timeout);

/**
 * \brief This function is used to write string data on uart channel.
 *        In Interrupt mode, data transmission will be asynchronous and the data is transmmitted using 
 *        internal software buffer. The function will be non blocking and will return after initiating data 
 *        transmission. Use epcf_uart_getTxBufferCount function to check the status of the transmit buffer.
 *
 *        In Polling mode, data transmission will be synchronous and calling function will be blocked until
 *        all the data is transmitted or timeout has occurred.
 *  
 * \param pUartDevice Pointer to uart device structure.
 * \param data        Pointer to buffer where string to be written is stored.
 * \param timeout     Timeout value.
 *  
 * \return return total number of bytes sent over uart channel. Check status code in case return value is less than 0.
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int32_t epcf_uart_writeString(EPCFUartDevice_t* pUartDevice, const uint8_t* data, EPCFTime_t timeout);

/**
 * \brief This function is used to read data on uart channel.
 *        In Interrupt mode, data receiving is asyncronous and data is received in an internal software buffer.
 *        Use epcf_uart_getRxBufferCount function to get receive buffer count. When the count is equal to the 
 *        required number of bytes to be read, call EPCF_UART_READ function to read the buffer.
 *
 *        In Polling mode, data receiving will be synchronous and calling function will be blocked until
 *        all the data is received or timeout has occurred.
 *  
 * \param pUartDevice Pointer to uart device structure.
 * \param data        Pointer to buffer where data to be stored after read operation.
 * \param size        Total number of bytes to send
 * \param timeout     Timeout value.
 *  
 * \return return total number of bytes read over uart channel. Check status code in case return value is less than 0.
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int32_t epcf_uart_read(EPCFUartDevice_t* pUartDevice, uint8_t* data, uint32_t size, EPCFTime_t timeout);

/**
 * \brief This function is used to enable the uart interrupt.It uart be disabled by epcf_uart_intDisable function.
 *
 * \param pUartDevice  Pointer to the uart device.
 * \param intType     interrupt type to generate an interrupt.Refer Enum EnEPCFUartIntType_t.
 *
 * \return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_Uart_intEnable(EPCFUartDevice_t* pUartDevice,EnEPCFUartIntType_t intType);

/**
 * \brief This function is used to disable the uart interrupt. 
 * 		  The device uart be enabled again by epcf_Uart_intEnable function.
 *
 * \param pUartDevice  Pointer to the uart device.
 * \param intType     interrupt type to generate an interrupt.Refer Enum EnEPCFUartIntType_t.
 *
 * \return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_uart_intDisable(EPCFUartDevice_t* pUartDevice,EnEPCFUartIntType_t intType);

/**
 * \brief This function is used to get number of bytes received in uart receive buffer.
 *  
 * \param pUartDevice Pointer to uart device structure.
 *  
 * \return return total number of received bytes
 *  
 * \note Use this function only when uart is configured in interrupt mode.
 */
extern int32_t epcf_uart_getRxBufferCount(EPCFUartDevice_t* pUartDevice);

/**
 * \brief This function is used to flush uart receive buffer.
 *  
 * \param pUartDevice Pointer to uart device structure.
 *  
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *  
 * \note Use this function only when uart is configured in interrupt mode.
 */
extern int8_t epcf_uart_rxBufferFlush(EPCFUartDevice_t* pUartDevice);

/**
 * \brief This function is used to get number of bytes pending in uart transmit buffer.
 *  
 * \param pUartDevice Pointer to uart device structure.
 *  
 * \return return total number of pending bytes
 *  
 * \note Use this function only when uart is configured in interrupt mode.
 */
extern int32_t epcf_uart_getTxBufferCount(EPCFUartDevice_t* pUartDevice);

/**
 * \brief This function is used to flush uart transmit buffer.
 *  
 * \param pUartDevice Pointer to uart device structure.
 *  
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *  
 * \note Use this function only when uart is configured in interrupt mode.
 */
extern int8_t epcf_uart_txBufferFlush(EPCFUartDevice_t* pUartDevice);

 /**
 * \brief This function is used to close the uart device. It will free the memory allocated by the uart device.
 *
 * \param pUartDevice Pointer to the uart device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_uart_close(EPCFUartDevice_t* pUartDevice);

 /**
 * \brief This function is used to get the total number of available uart devices.
 *
 * \return Returns the number of available uart devices.
 */
extern uint8_t epcf_uart_getDeviceCount();


#ifdef EPCF_USING_MT_ENV
//ToDo: Adding support for EPCF_USING_MT_ENV
//ToDo: Add comment for function description
extern int8_t epcf_uart_lock(EPCFUartDevice_t* pUartDevice);
extern int8_t epcf_uart_unlock(EPCFUartDevice_t* pUartDevice);

#endif	//EPCF_USING_MT_ENV


#endif      //__EPCF_INCLUDED_PERIPHERAL_INCLUDE_UART_UART_H
