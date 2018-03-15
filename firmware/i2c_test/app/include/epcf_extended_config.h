/**
 * \file  extended_config.h
 * \brief This file is used to configure on-board peripherals in the begining.
 */

#ifndef __EPCF_INCLUDED_EXTENDED_CONFIG_H
#define __EPCF_INCLUDED_EXTENDED_CONFIG_H

/**
Set this to PCF_YES or PCF_NO if you want to use the GPIO device
in your application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_EXTENDED_USE_GPIO			PCF_NO

/**
Set this to PCF_YES or PCF_NO if you want to use the UART device
in your Application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_EXTENDED_USE_UART			PCF_NO

/**
Set this to PCF_YES or PCF_NO if you want to use the SPI device
in your Application. See file "private/defs.h for more
discription of PCF_YES and PCF_NO.
*/
#define EPCF_CONF_EXTENDED_USE_SPI			PCF_NO

//////////////////////  Extended configuration ends   /////////////////////////////

#endif //__EPCF_INCLUDED_EXTENDED_CONFIG_H
