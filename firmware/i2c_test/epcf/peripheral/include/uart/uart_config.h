/**
 * \file  uart_config.h
 * \brief This file is used to configure a UART device
 */

#ifndef __EPCF_INCLUDED_PERIPHERAL_UART_UART_CONFIG_H
#define __EPCF_INCLUDED_PERIPHERAL_UART_UART_CONFIG_H

#include "uart.h"

#define __EPCF_UART_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/include/uart/,uart_,PCF_ARCH_DEVICE.h)
#include __EPCF_UART_INCLUDE
#undef __EPCF_UART_INCLUDE


 /*
#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
  #if(EPCF_USE_UART == PCF_YES)
    #if (PCF_ARCH == PCF_ARCH_X86)
		#define __EPCF_UART_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/uart/PCF_OS_NAME/,uart_,PCF_ARCH_NAME.h)
		#include __EPCF_UART_INCLUDE
		#undef __EPCF_UART_INCLUDE
    #else
		#define __EPCF_UART_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/uart/,uart_,PCF_ARCH_DEVICE.h)
		#include __EPCF_UART_INCLUDE
		#undef __EPCF_UART_INCLUDE
    #endif
  #endif
#endif

#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
	#if(EPCF_USE_UART == PCF_YES)
		#if (PCF_ARCH == PCF_ARCH_X86)
			#define __EPCF_UART_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/uart/PCF_OS_NAME/,uart_,PCF_ARCH_NAME.h)
			#include __EPCF_UART_INCLUDE
			#undef __EPCF_UART_INCLUDE
		#else
			#define __EPCF_UART_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/uart/,uart_,PCF_ARCH_DEVICE.h)
			#include __EPCF_UART_INCLUDE
			#undef __EPCF_UART_INCLUDE
		#endif
	#endif
	#if(EPCF_EXTENDED_USE_UART == PCF_YES)
		#define __EPCF_UART_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EXTENDED_PATH/,controller/,uart/,uart_controller.h)
		#include __EPCF_UART_INCLUDE
		#undef __EPCF_UART_INCLUDE


		#define _EPCF_EXT_DEVICE_INCLUDE    \
		        PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/port/PCF_EXTENDED_ARCH_NAME/PCF_EXTENDED_ARCH_VARIANT/,\
		                    PCF_EXTENDED_ARCH_DEVICE_VENDOR/PCF_EXTENDED_ARCH_DEVICE/uart/uart_,PCF_EXTENDED_ARCH_DEVICE,_config.h)

        #include _EPCF_EXT_DEVICE_INCLUDE
		#undef _EPCF_EXT_DEVICE_INCLUDE
	#endif
	
#endif
*/

#endif      //__EPCF_INCLUDED_PERIPHERAL_UART_UART_CONFIG_H
