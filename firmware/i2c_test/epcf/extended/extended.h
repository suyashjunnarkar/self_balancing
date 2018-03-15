/**
 * \file  extended.h
 * \brief This file is to be included by the application program in the begining to use epcf framework.
 */

#ifndef __EPCF_INCLUDED_EXTENDED_H
#define __EPCF_INCLUDED_EXTENDED_H

#define __EPCF_PACKET_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,extended/,packet/,packet.h)
#include __EPCF_PACKET_INCLUDE
#undef __EPCF_PACKET_INCLUDE

#define __EPCF_ERROR_DETECT_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,utils/,include/,epcf_error_detection.h)
#include __EPCF_ERROR_DETECT_INCLUDE
#undef __EPCF_ERROR_DETECT_INCLUDE

//config includes
#if defined(EPCF_EXTENDED_USE_GPIO)
	#if(EPCF_EXTENDED_USE_GPIO == PCF_YES)
		#include "../peripheral/gpio/gpio_config.h"
	#endif
#else
	#if(EPCF_CONF_EXTENDED_USE_GPIO == PCF_NO)
		#warning "Extended GPIO not addded by" PCF_STRINGIFY(PCF_ARCH_DEVICE)
	#endif
#endif

#if defined(EPCF_EXTENDED_USE_UART)
	#if (EPCF_EXTENDED_USE_UART == PCF_YES)
		#include "../peripheral/uart/uart_config.h"
	#endif
#else
	#if(EPCF_CONF_EXTENDED_USE_UART == PCF_NO)
		#warning "Extended UART not added by" PCF_STRINGIFY(PCF_ARCH_DEVICE)
	#endif
#endif


//resolving epcf_extended_config MACROS

// Extended Configuration ARCH MACRO

#if !defined(PCF_CONF_EXTENDED_ARCH)
    #error "bad configuration, you must define PCF_CONF_EXTENDED_ARCH in \
            the epcf_extended_arch_config.h"
#endif

#if defined(PCF_EXTENDED_ARCH_NAME)
   #error "Don't define macro PCF_EXTENDED_ARCH_NAME anywhere else."
#endif


#if (PCF_CONF_EXTENDED_ARCH == PCF_ARCH_AVR)
    #define PCF_EXTENDED_ARCH_NAME      avr
#elif (PCF_CONF_EXTENDED_ARCH == PCF_ARCH_ARM)
    #define PCF_EXTENDED_ARCH_NAME      arm
#elif (PCF_CONF_EXTENDED_ARCH == PCF_ARCH_X86)
    #define PCF_EXTENDED_ARCH_NAME      x86
#else
#error "Unknown ARCHITECTURE type, defined correct arch type in epcf_extended_arch_config.h"
#endif

#if (PCF_CONF_EXTENDED_ARCH == PCF_ARCH_ARM)

    //Variant will get handled from here.
    //#define PCF_CONF_EXTENDED_ARCH_VARIANT                   cm3
    //#define PCF_CONF_EXTENDED_ARCH_DEVICE_VENDOR             nxp
    //#define PCF_CONF_EXTENDED_ARCH_DEVICE                    lpc1768

    #if !defined(PCF_CONF_EXTENDED_ARCH_VARIANT)
        #error "bad configuration, you must define PCF_CONF_EXTENDED_ARCH_VARIANT in the epcf_extended_arch_config.h."
    #endif

    #if !defined(PCF_CONF_EXTENDED_ARCH_DEVICE_VENDOR)
        #error "bad configuration, you must define PCF_CONF_EXTENDED_ARCH_DEVICE_VENDOR     \
                in the epcf_extended_arch_config.h."
    #endif

    #if !defined(PCF_CONF_EXTENDED_ARCH_DEVICE)
        #error "bad configuration, you must define PCF_CONF_EXTENDED_ARCH_DEVICE     \
                in the epcf_extended_arch_config.h."
    #endif

    #define PCF_EXTENDED_ARCH_VARIANT              cm3
    #define PCF_EXTENDED_ARCH_DEVICE_VENDOR        nxp
    #define PCF_EXTENDED_ARCH_DEVICE               lpc1768

#endif

#undef PCF_CONF_EXTENDED_ARCH

// Extended Configuration OS MACRO

/*
#if !defined(PCF_CONF_EXTENDED_HAS_OS)
#error "You shall not include this file directly in your code."
#endif

#if !defined (PCF_CONF_EXTENDED_OS_TYPE)
#error "How come this is possible! Work only on the RHS of config file."
#endif

#if defined(PCF_EXTENDED_OS_NAME)
#error "You shall not define PCF_EXTENDED_OS_NAME."
#endif

#if defined(PCF_EXTENDED_OS_TYPE)
#error "You shall not define PCF_EXTENDED_OS_TYPE."
#endif

#if (PCF_CONF_EXTENDED_HAS_OS == PCF_YES)

	#if  (PCF_CONF_EXTENDED_OS_TYPE == PCF_OS_NONE)
		#error "You have configured for OS support but have not defined the OS flavour."
	#elif (PCF_IS_ANY_KNOWN_OS(PCF_CONF_EXTENDED_OS_TYPE))

		#if (PCF_CONF_EXTENDED_OS_TYPE == PCF_OS_LINUX)
			#define PCF_EXTENDED_OS_NAME	pcf_linux
		#elif (PCF_CONF_EXTENDED_OS_TYPE == PCF_OS_UC_LINUX)
			#define PCF_EXTENDED_OS_NAME 	pcf_uclinux
		#elif (PCF_CONF_EXTENDED_OS_TYPE == PCF_OS_WINDOWS)
			#define PCF_EXTENDED_OS_NAME 	pcf_windows
		#elif (PCF_CONF_EXTENDED_OS_TYPE == PCF_OS_IOS)
			#define PCF_EXTENDED_OS_NAME 	pcf_ios
		#elif (PCF_CONF_EXTENDED_OS_TYPE == PCF_OS_ANDROID)
			#define PCF_EXTENDED_OS_NAME 	pcf_android
		#elif (PCF_CONF_EXTENDED_OS_TYPE == PCF_OS_RT_PHIXOS)
			#define PCF_EXTENDED_OS_NAME 	pcf_phixos
		#else
			#error "Bad OS, pcf deosn't know about your os. Above, add one more 'elif' \
						and follow the steps to add support for a new OS for pcf."

		#endif //#if (PCF_CONF_EXTENDED_OS_TYPE == PCF_OS_LINUX_32)
		
	//#if defined (PCF_EXTENDED_OS_NAME )

	//#define __PCF_OS_DEF_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(os/,PCF_EXTENDED_OS_NAME/,,PCF_EXTENDED_OS_NAME.h)
	//	#include __PCF_OS_DEF_INCLUDE
	//	#undef __PCF_OS_DEF_INCLUDE

    //Below macro should be defined the the File of OS Included on basis of Configuartion done
	//	  in the configuration file.
	//	#if !defined(PCF_OS_TYPE)
	//	#error "Included OS doesn't define the required macro PCF_OS_TYPE."
	//	#endif	//#if !defined(PCF_OS_TYPE)

	//	#if !defined(PCF_PATH_SEPARATOR_CHAR)
	//	#error "Included OS doesn't define the required macro PCF_PATH_SEPARATOR_CHAR."
	//	#endif	//#if !defined(PCF_PATH_SEPARATOR_CHAR)

	//#endif	//#if defined (PCF_OS_NAME )

	//#else
	//	#error "You have configured for an OS type which isn't currently supported."
	//#endif //#if  (PCF_CONF_OS_TYPE == PCF_OS_NONE)

	#elif (PCF_CONF_EXTENDED_HAS_OS == PCF_NO)
		#define PCF_OS 	PCF_OS_NONE
		#undef  PCF_CONF_EXTENDED_OS_TYPE
	#else
		#error "You shall not be seeing this error ever! Swear on honesty, you didn't change \
		what was above your access."
	#endif
	
#endif //#if (PCF_CONF_HAS_OS == PCF_YES)

#undef  PCF_CONF_EXTENDED_HAS_OS

*/






#endif // __EPCF_INCLUDED_EXTENDED_H__
