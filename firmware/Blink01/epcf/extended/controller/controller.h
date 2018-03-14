/**
 * \file  extended.h
 * \brief This file is to be included by the application program in the begining to use epcf framework.
 */

#ifndef __EPCF_INCLUDED_EXTENDED_CONTROLLER_H
#define __EPCF_INCLUDED_EXTENDED_CONTROLLER_H

#if defined(EPCF_EXTENDED_USE_GPIO)
#error "Don't define macro EPCF_EXTENDED_USE_GPIO anywhere else."
#else
	#if(EPCF_CONF_EXTENDED_USE_GPIO == PCF_YES)
		#define EPCF_EXTENDED_USE_GPIO	PCF_YES
	#elif(EPCF_CONF_EXTENDED_USE_GPIO == PCF_NO)
		#define EPCF_EXTENDED_USE_GPIO	PCF_NO
	#else
		#error "Incorrect value for the EPCF_CONF_EXTENDED_USE_GPIO defined in extended_config.h		\
		There can be 2 values for EPCF_CONF_EXTENDED_USE_GPIO: 		\
		1.	PCF_YES													\
		2.	PCF_NO"
	#endif
#endif
#undef EPCF_CONF_EXTENDED_USE_GPIO

#if defined(EPCF_EXTENDED_USE_UART)
#error "Don't define macro EPCF_EXTENDED_USE_UART anywhere else."
#else
	#if(EPCF_CONF_EXTENDED_USE_UART == PCF_YES)
		#define EPCF_EXTENDED_USE_UART	PCF_YES
	#elif(EPCF_CONF_USE_EXTENDED_UART == PCF_NO)
		#define EPCF_EXTENDED_USE_UART	PCF_NO
	#else
		#error "Incorrect value for the EPCF_CONF_EXTENDED_USE_UART defined in extended_config.h		\
		There can be 2 values for EPCF_CONF_EXTENDED_USE_UART: 		\
		1.	PCF_YES												\
		2.	PCF_NO"
	#endif
#endif
#undef EPCF_CONF_EXTENDED_USE_UART

#endif // __EPCF_INCLUDED_EXTENDED_H__
