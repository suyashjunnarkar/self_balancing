#ifndef __EPCF_INCLUDED_PERIPHERAL_COMMON_STATUS_H
#define __EPCF_INCLUDED_PERIPHERAL_COMMON_STATUS_H

//Common Error codes
#define EPCF_STATUS_SUCCESS			 	 0
#define EPCF_STATUS_ERROR				-1
#define EPCF_STATUS_INVALID_ARGS		-2
#define EPCF_STATUS_NOT_SUPPORTED		-3
#define EPCF_STATUS_NOT_CONFIGURED		-4
#define EPCF_STATUS_ALREADY_CONFIGURED	-5
#define EPCF_STATUS_NO_MEMORY			-6
#define EPCF_STATUS_TIMEOUT				-7
#define EPCF_STATUS_BUSY				-8
#define EPCF_STATUS_UNKNOWN				-9

//EPCF specific
#define EPCF_STATUS_NO_DEVICE					-20
#define EPCF_STATUS_INVALID_USER_DATA_SIZE		-21

//Network specific
#define EPCF_STATUS_PACKET_ERROR		-40
#define EPCF_STATUS_INVALID_COMMAND		-41
#define EPCF_STATUS_CRC_ERROR			-42

//Common communication codes
#define EPCF_STATUS_MAX_DEVICES_CONNECTED  -10

//I2C status codes
#define EPCF_STATUS_I2C_DONE			-50 	/**< Transfer done successfully 		*/
#define EPCF_STATUS_I2C_NAK				-51		/**< NAK received during transfer 		*/
#define EPCF_STATUS_I2C_ARBLOST			-52		/**< Arbitration lost during transfer 	*/
#define EPCF_STATUS_I2C_BUSERR			-53		/**< Bus error in I2C transfer 			*/
#define EPCF_STATUS_I2C_BUSY			-54		/**< I2C is busy doing transfer 		*/
#define EPCF_STATUS_I2C_SLAVENAK		-55		/**< NAK received after SLA+W or SLA+R 	*/

//File System status code
#define EPCF_STATUS_FILE_NOT_FOUND			-70 	/**< File Not found 		*/
#define EPCF_STATUS_PATH_NOT_FOUND			-71		/**< Path Not found			*/
#define EPCF_STATUS_TOO_MANY_OPEN_FILES		-72		/**< Too Many Open Files    */
#define EPCF_STATUS_ACCESS_DENIED			-73		/**< Access Denied {OS }	*/
#define EPCF_STATUS_INVALID_HANDLE			-74		/**< Invalid Handle         */

#endif /* __EPCF_INCLUDED_PERIPHERAL_COMMON_STATUS_H 	*/
