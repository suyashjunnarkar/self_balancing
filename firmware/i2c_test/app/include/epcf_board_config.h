/**
 * \file  board_config.h
 * \brief This file is used to configure on-board peripherals in the begining.
 */

#ifndef __EPCF_INCLUDED_BOARD_CONFIG_H
#define __EPCF_INCLUDED_BOARD_CONFIG_H


///////////////////////	Board Configuration starts ////////////////////////////////////
//We can also move this MACROS in a seperate file like board_config.h

/**
Set this to PCF_YES or PCF_NO if you want to use the SYSCLK
in your application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_USE_SYSCLK	PCF_YES

/**
Set this to PCF_YES or PCF_NO if you want to use the GPIO device
in your application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_USE_GPIO		PCF_YES

/**
Set this to PCF_YES or PCF_NO if you want to use the UART device
in your Application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_USE_UART		PCF_YES

/**
Set this to PCF_YES or PCF_NO if you want to use the TIMER device
in your Application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_USE_TIMER		PCF_NO

/**
Set this to PCF_YES or PCF_NO if you want to use the SPI device
in your Application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_USE_SPI		PCF_NO

/**
Set this to PCF_YES or PCF_NO if you want to use the I2C device
in your Application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_USE_I2C		PCF_YES

/**
Set this to PCF_YES or PCF_NO if you want to use the ADC device
in your Application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_USE_ADC		PCF_NO

/**
Set this to PCF_YES or PCF_NO if you want to use the PWM device
in your Application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_USE_PWM		PCF_NO

/**
Set this to PCF_YES or PCF_NO if you want to use the CAN device
in your Application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_USE_CAN		PCF_NO

//////////////////////  Board configuration ends   /////////////////////////////

#endif //__EPCF_INCLUDED_BOARD_CONFIG_H__
