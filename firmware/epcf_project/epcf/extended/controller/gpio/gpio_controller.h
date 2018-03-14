/**
 * \file  gpio_controller.h
 * \brief This file is used to create GPIO controller.
 */

#ifndef __EPCF_INCLUDED_EXTENDED_CONTROLLER_GPIO_GPIO_CONTROLLER_H
#define __EPCF_INCLUDED_EXTENDED_CONTROLLER_GPIO_GPIO_CONTROLLER_H

#include "gpio_controller_config.h"

typedef struct EPCFAdapter EPCFAdapter_t;
typedef struct EPCFGpioController	EPCFGpioController_t;
typedef struct EPCFGpioDevice		EPCFGpioDevice_t;

#define CMD_GPIO_ACK				0
#define CMD_GPIO_INIT				1
#define CMD_GPIO_SET				2
#define CMD_GPIO_CLEAR				3
#define CMD_GPIO_SET_DIRECTION		4
#define CMD_GPIO_READ				5
#define CMD_GPIO_GET_DEVICE_COUNT	6

//GPIO INIT PAYLOAD
//Tx data bytes: 5bytes, sequence: PORT(1byte) PIN(1byte) DIRECTION(1byte) MODE(1byte) OPENDRAIN(1byte)
//Rx data bytes: 1byte,  sequence: RETURN VALUE(1byte)

//GPIO SET PAYLOAD
//Tx data bytes: 1bytes, sequence: DEVICEID(1byte)
//Rx data bytes: 1bytes, sequence: RETURN VALUE(1byte)

//GPIO CLEAR PAYLOAD
//Tx data bytes: 1bytes, sequence: DEVICEID(1byte)
//Rx data bytes: 1bytes, sequence: RETURN VALUE(1byte)

//GPIO SET DIRECTION PAYLOAD
//Tx data bytes: 2bytes, sequence: DEVICEID(1byte) DIRECTION(1byte)
//Rx data bytes: 1bytes, sequence: RETURN VALUE(1byte)

//GPIO READ PAYLOAD
//Tx data bytes: 1bytes, sequence: DEVICEID(1byte)
//Rx data bytes: 1bytes, sequence: RETURN VALUE(1byte)

//GPIO GET DEVICE COUNT PAYLOAD
//Tx data bytes: 0byte
//Rx data bytes: 1bytes, sequence: RETURN VALUE(4byte)

EPCFGpioController_t* epcfCreateGpioController(EPCFAdapter_t *pAdapter);

#endif //__EPCF_INCLUDED_EXTENDED_CONTROLLER_GPIO_GPIO_CONTROLLER_H
