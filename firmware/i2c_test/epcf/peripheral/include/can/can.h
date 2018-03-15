/**
 * \file  can.h
 * \brief This file is used to configure a Can device
 */

#ifndef __EPCF_INCLUDED_PERIPHERAL_CAN_CAN_H
#define __EPCF_INCLUDED_PERIPHERAL_CAN_CAN_H

#define CAN_DATA_SIZE (sizeof(EPCFCanRxMessage_t))

typedef struct EPCFCanDevice EPCFCanDevice_t;

/** Enumeration for CAN frame format		*/
typedef enum
{
	enEPCFCanFrameFormat_Standard = 0,			/**< CAN standard frame	with 11 bit ID		*/
	enEPCFCanFrameFormat_Extended,				/**< CAN extended frame	with 29 bit ID		*/
	enEPCFCanFrameFormat_Max					/**< Special value for boundary checking	*/
}EnEPCFCanFrameFormat_t;

/**	Enumeration for CAN callback types		*/
typedef enum
{
	enEPCFCanCallback_Buff1TxCallback = 0,		/**< Can Buffer 1 transmission complete interrupt callback	*/
	enEPCFCanCallback_Buff2TxCallback,			/**< Can Buffer 2 transmission complete interrupt callback	*/
	enEPCFCanCallback_Buff3TxCallback,			/**< Can Buffer 3 transmission complete interrupt callback	*/
	enEPCFCanCallback_RxCallback,				/**< Can message received interrupt callback				*/
	enEPCFCanCallback_ErrCallback,				/**< Can Error passive interrupt callback					*/
}EnEPCFCanCallback_t;

/**	Enumeration for CAN message length		*/
typedef enum
{
	enEPCFCanLength_0byte = 0,					/**< CAN Data Length:1 byte to 8 bytes	*/
	enEPCFCanLength_1byte,
	enEPCFCanLength_2byte,
	enEPCFCanLength_3byte,
	enEPCFCanLength_4byte,
	enEPCFCanLength_5byte,
	enEPCFCanLength_6byte,
	enEPCFCanLength_7byte,
	enEPCFCanLength_8byte,
	enEPCFDataLength_Max					/**< Special value for boundary checking	*/
}EnEPCFDataLength_t;

/**	Enumeration for CAN interrupt type	*/
typedef enum
{
	enEPCFCanIntType_None = 0,				/**< CAN Interrupt None		 			*/
	enEPCFCanIntType_RI,					/**< CAN Receiver Interrupt 			*/
	enEPCFCanIntType_TI,					/**< CAN Transmit Interrupt 			*/
	enEPCFCanIntType_TI_RI,					/**< CAN Transmit Receiver Interrupt 	*/
	enEPCFCanIntType_EWI,					/**< CAN Error Warning Interrupt		*/
	enEPCFCanIntType_DOI,					/**< CAN Data Overrun Interrupt			*/
	enEPCFCanIntType_ALI,					/**< CAN Arbitration Loss Interrupt		*/
	enEPCFCanIntType_Max						/**< Special value for boundary checking*/
} EnEPCFIntType_t;

/**	Enumeration for CAN frame type	*/
typedef enum
{
	enEPCFCanFrameType_UnknownFrame = 0,	/**< The frame type is unknown.			*/
	enEPCFCanFrameType_DataFrame,			/**< This value represents a data frame.*/
	enEPCFCanFrameType_ErrorFrame,			/**< This value represents an error frame.*/
	enEPCFCanFrameType_RemoteRequestFrame,	/**< This value represents a remote request.*/
	enEPCFCanFrameType_Overlod,				/**< This value represents an Overlod frame*/
	enEPCFCanFrameType_Max
}EnEPCFCanFrameType_t;

/** Can configuration structure
	Example to configure can device
	EPCFCanCfg_t canConfig =
	{
		0,							// can id 0
		1000000,					// 1 Mbit/s baudrate
		enEPCFCanIntType_RI			// Receive Interrupt Enable
		256,						// Tx buffer size = 256 bytes
		256,						// Rx buffer size = 256 bytes
		NULL						// No hardware specific config
	};
*/
/** Can Message structure
	Example to configure can message
	EPCFCanCfg_t canConfig =
	{
		enEPCFCanFrameFormat_Extended ,							// Entended format identifier
		0x00001234,												// identifier
		enEPCFCanLength_8byte,									// Length of data feild=8Bytes
		sendData,												// 8 byte data
		EnEPCFCanFrameType_DataFrame							// Frame type= Data frame for data transmission.
	};
*/
/**	\brief	CAN configuration structure				*/
typedef struct
{
	uint8_t					canId;     		/**< Can Id. Refer to platform specific header file for appropriate can id				*/

	uint32_t				baudrate;		/**< Baudrate for CAN communication in bits/second.Baudrate can set upto 1megabits/second.
												 Some of the Standard baud rates are 125 kbit/s, 250 kbit/s, 500 kbit/s and 1 Mbit/s.*/

    EnEPCFIntType_t			interrupt;		/**< This enum describe Interrupt type to be used. **/

	uint32_t				txBufferSize;	/**< Specifies the transmit buffer size in bytes when using can in interrupt mode
													 Pass 0 when using can in polling mode											*/

	uint32_t				rxBufferSize;	/**< Specifies the receive buffer size in bytes when using can in interrupt mode
													 Pass 0 when using can in polling mode											*/

    void*					hardwareCfg;	/**< Hardware platform specific configuration, pass NULL for default configuration		*/
}EPCFCanCfg_t;

/**	\brief	CAN  message header structure				*/
typedef struct
{
	EnEPCFCanFrameFormat_t frameFormat; 	/**< This enum describes identifier Format:
												- enEPCFCanFrameStandard: Standard ID - 11 bit format
												- enEPCFCanFrameExtended: Extended ID - 29 bit format
											*/

	EnEPCFCanFrameType_t frameType; 		/**< This enum describes the type of the CAN frame.
													enEPCFCanFrameType_UnknownFrame
													enEPCFCanFrameType_DataFrame
													enEPCFCanFrameType_ErrorFrame
													enEPCFCanFrameType_RemoteRequestFrame
													enEPCFCanFrameType_Overlod*/
	EnEPCFDataLength_t length; 				/**< Length of data field in bytes,
												- minimum :1 byte
												- maximum :8 bytes
												Select appropriate value from enum EnEPCFDataLen_t
											*/
	uint32_t id; 							/**< CAN identifier value, it depends on "EnEPCFCanFrameFormat_t" value
												- for enEPCFCanFrameStandard, it should be 11 bit identifier
												- for enEPCFCanFrameExtended, it should be 29 bit identifier
											Note : do not missinterpretate term 'id' with canId from EPCFCanCfg_t, here id represents identifier which
											is part of standard can bus frame.
											*/


} EPCFCanMsgHeader_t;

/**	\brief	CAN Receive message structure				*/
typedef struct
{
	EPCFCanMsgHeader_t header;	/**< Message header. Refer \link HbCanMsgHeader \endlink for details		*/
	uint8_t rxData[8];			/**< 8 byte payload data for the message									*/
}EPCFCanRxMessage_t;

/** Enumeration for Can filter mode*/
typedef enum
{
	enEPCFCanFilterModeIdList,             /**< One filter will be able to filter a single message IDs*/
	enEPCFCanFilterModeIdGroup,			   /**< One filter will be able to filter a group of message IDs*/
}EnEPCFCanFilterMode;

/** \brief CAN Filter structure		*/
typedef struct
{
	EPCFCanMsgHeader_t msgHeader[2];/**< msgHeader is an array contatining two elements <br>
										In case of single message filter the element 0 will contain information about the message. <br>
										In case of filtering a group of message elemet 0 will contain the lower bound of the
										range of messages to be filtered and the upper bound will be stored in the second element */
	EnEPCFCanFilterMode mode;    		/**< \see PFEnCanFrameFormat */

}
EPCFCfgFilter;

typedef EPCFCfgFilter* EPCFpCfgFilter;

typedef EPCFCanRxMessage_t* EPCFpCanRxMessage_t;



/**
 * \brief This function is used to create a can device. Call this function in beginning to initialize the can device.
 *        This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer
 *        while calling can functions.
 *
 * \param pCanConfig Pointer to the can configuration structure.
 *
 * \return On success, it return the pointer to can device.
 *         On error, it returns NULL.
 */
extern EPCFCanDevice_t* epcf_can_createNative(EPCFCanCfg_t* pCanConfig);
/**
 * \brief This function is used to enable the can interrupt.It can be disabled by epcf_can_intDisable function.
 *
 * \param pCanDevice  Pointer to the can device.
 * \param intType     interrupt type to generate an interrupt.Refer Enum EnEPCFIntType_t.
 *
 * \return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_can_intEnable(EPCFCanDevice_t* pCanDevice,EnEPCFIntType_t intType);

/**
 * \brief This function is used to disable the can interrupt.
 * 		  The device can be enabled again by epcf_can_intEnable function.
 *
 * \param pCanDevice  Pointer to the can device.
 * \param intType     interrupt type to generate an interrupt.Refer Enum EnEPCFIntType_t.
 * \return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_can_intDisable(EPCFCanDevice_t* pCanDevice,EnEPCFIntType_t intType);
/**
 * \brief This function is used to attach an can interrupt callback according to the interrupt type selected while
 *		  enabling interrupt
 *
 * \param pCanDevice  Pointer to the can device.
 * \param intType     interrupt type to generate an interrupt.Refer Enum EnEPCFIntType_t.
 * \param callback    User callback to be attached for respective interrupt.
 *
 * \return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 */
extern int8_t epcf_can_intAttachCallback(EPCFCanDevice_t* pCanDevice,EnEPCFCanCallback_t intType,epcfCallbackWithArg_fp pCallback);
/**
 * \brief This function is used to detach a can interrupt callback according to the interrupt type selected .
 *
 * \param pCanDevice  Pointer to the can device.
 * \param intType     interrupt type to generate an interrupt.Refer Enum EnEPCFIntType_t.
 *
 * \return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 */
extern int8_t epcf_can_intDetachCallback(EPCFCanDevice_t* pCanDevice,EnEPCFCanCallback_t intType);

/**
 * \brief This function is used to get number of bytes received in can receive  buffer.
 *
 * \param pCanDevice Pointer to the can device
 *
 * \return  return total number of received bytes
 *
 * \note Use this function only when using can in interrupt mode
 */
extern uint32_t epcf_can_getRxBufferCount(EPCFCanDevice_t* pCanDevice);

/**
 * \brief This function is used to flush can receive  buffer.
 *
 * \param pCanDevice Pointer to the can device
 *
 * \return  return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note Use this function only when using can in interrupt mode
 */

extern int8_t epcf_can_rxBufferFlush(EPCFCanDevice_t* pCanDevice);

 /**
 * \brief This function is used to get number of bytes pending in can transmit  buffer.
 *
 * \param pCanDevice Pointer to the can device
 *
 * \return  return total number of pending bytes
 *
 * \note Use this function only when using can in interrupt mode
 */
 
extern uint32_t epcf_can_getTxBufferCount(EPCFCanDevice_t* pCanDevice);

/**
 * \brief This function is used to flush can transmit buffer.
 *
 * \param pCanDevice Pointer to the can device
 * 
 * \return  return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note Use this function only when using can in interrupt mode
 */
extern int8_t epcf_can_txBufferFlush(EPCFCanDevice_t* pCanDevice);
/**
* \brief This function returns whether fifo is empty or not.
*
* \param pCanDevice 	Pointer to the can device.
* \return 				return boolean status,enEPCFBoolean_True if fifo is empty and enEPCFBoolean_False if fifo is not empty
*/
extern EnEPCFBoolean_t epcf_can_getRxFifoEmpty(EPCFCanDevice_t* pCanDevice);
/**
* \brief This function is used to set message header for CAN message.
*
* \param pCanDevice		Pointer to the can device
* \param pMsgHeader     Pointer to structure of message header.
*
* \return 	return status.
*			Refer to "../../common/status.h" header file for the appropriate status codes.
*
*/

extern int8_t epcf_can_setMsgHeader(EPCFCanDevice_t* pCanDevice,EPCFCanMsgHeader_t* pMsgHeader);
 /**
 * \brief This function is used to send data on CAN bus.
 *		  -Interrupt mode :- It is mandatory to select interrupt as enEPCFCanIntType_TI_RI or enEPCFCanIntType_TI
 *		   in CAN configuration structure to use this function in Interrupt mode.Data transmission
 *		   will be asynchronous and the data is transmitted using internal transmit buffer.
 *		   The function will  be non blocking and will return after initiating data  transmission.
 *		   Use epcf_can_getTxBufferCount function to check the status of the transmit buffer.
 *		  -Poling mode :- It is mandatory to select interrupt type as enEPCFCanIntType_None in CAN configuration structure to
 * 		   use this function in Poling mode.Data transmission will be synchronous and calling function will be blocked until
 *         all the data is transmitted or timeout has occurred.
 *
 *
 * \param pCanDevice	Pointer to the can device
 * \param data        	Pointer to buffer where data to be written is stored.
 * \param size        	Total number of bytes to send
 * \param timeout		timeout value.
 *
 * \return 	return total number of bytes send over can bus. Check status code if return value is less than 0.
 *			Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 */
extern int8_t epcf_can_write(EPCFCanDevice_t* pCanDevice,const uint8_t* data, uint32_t size,EPCFTime_t timeout);

 /**
 * \brief This function is used to read data on CAN bus.
 *		  -Interrupt mode :- It is mandatory to select interrupt as enEPCFCanIntType_TI_RI or enEPCFCanIntType_RI
 *		   in CAN configuration structure to use this function in Interrupt mode.Data Reception
 *		   will be asynchronous and the data is received using internal receive buffer.
 *		   Use epcf_can_getRxBufferCount and epcf_can_getRxFifoEmpty function to check the status of the transmit buffer.
 *		  -Poling mode :- It is mandatory to select interrupt type as enEPCFCanIntType_None in CAN configuration structure to
 * 		   use this function in Poling mode.Data reception will be synchronous and calling function will be blocked until
 *         all the data is transmitted or timeout has occurred.
 *
 *
 * \param pCanDevice	Pointer to the can device
 * \param pRxMessage	Pointer to the structure where data will be stored
 * \param timeout		timeout value.
 *
 * \return 	return number of bytes read over can bus. Check status code if return value is less than 0.
 *			Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note
 */
extern int8_t epcf_can_read(EPCFCanDevice_t*  pCanDevice,EPCFpCanRxMessage_t rxMessage,EPCFTime_t timeout);

 /**
 * \brief This function is used to close the can device. It will free the memory allocated by the can device.
 *
 * \param pCanDevice Pointer to the can device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_can_close(EPCFCanDevice_t* pCanDevice);
 /**
 * \brief This function is used to get the total number of available can devices.
 *
 * \return Returns the number of available can devices.
 */
extern int8_t epcf_can_getDeviceCount(EPCFCanDevice_t* pCanDevice);
 /**
 * \brief This function is used to set acceptance filter for CAN receiver to receive required message id.
 *
 * \param pCanDevice 	Pointer to the can device.
 * \param pFilterConfig Pointer to the can configuration structure.
 * \return 				return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_can_filterInit(EPCFCanDevice_t* pCanDevice,EPCFpCfgFilter pFilterConfig);
/**
* \brief This function provides interface to read transmission error counter.
*
* \param pCanDevice 	Pointer to the can device.
* \param errCount 		Pointer to byte to which the function should write error counter value.
* \return 				return status. Refer to "../../common/status.h" header file for the appropriate status codes.
*/
extern int8_t epcf_can_getTxErrCounter(EPCFCanDevice_t* pCanDevice,uint8_t* errCount);
/**
* \brief This function provides interface to read reception error counter.
*
* \param pCanDevice 	Pointer to the can device.
* \param errCount 		Pointer to byte to which the function should write error counter value.
* \return 				return status. Refer to "../../common/status.h" header file for the appropriate status codes.
*/
extern int8_t epcf_can_getRxErrCounter(EPCFCanDevice_t* pCanDevice,uint8_t* errCount);
/**
* \brief This function gets interrupt status for given channel.
*
* \param pCanDevice 	Pointer to the can device.
* \param status 		pointer to Interrupt status.
* \return 				return status. Refer to "../../common/status.h" header file for the appropriate status codes.
*/
extern int8_t epcf_can_getIntStatus(EPCFCanDevice_t* pCanDevice,uint32_t* status);
/**
* \brief This function gets Control status for given channel.
*
* \param pCanDevice 	Pointer to the can device.
* \param status 		pointer to Interrupt status.
* \return 				return status. Refer to "../../common/status.h" header file for the appropriate status codes.
*/
extern int8_t epcf_can_getCtrlStatus(EPCFCanDevice_t* pCanDevice,uint32_t* status);



#ifdef EPCF_USING_MT_ENV
// TODO : Adding the Support for EPCF_USING_MT_ENV
// TODO : Add Comments for Function Discription.
/**
 *  \brief
 *
 *  \param      pCanDevice      Pointer to the can device.
 *
 * \return  Returns the lock status for can device.
 */
extern int8_t epcf_can_lock(EPCFCanDevice_t* pCanDevice);

/**
 *  \brief
 *
 *  \param      pI2cDevice      Pointer to the i2c device.
 *
 * \return  Returns the unlock status for i2c device.
 */
extern int8_t epcf_can_unlock(EPCFCanDevice_t* pCanDevice);
#endif


#endif      //__EPCF_INCLUDED_PERIPHERAL_CAN_CAN_H
