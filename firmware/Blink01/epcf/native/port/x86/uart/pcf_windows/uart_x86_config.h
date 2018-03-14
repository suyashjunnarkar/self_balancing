/**
 * \file    uart_x86_32_config.h
 * \brief   Native Uart Driver Configuration for windows(32bit) on x86(32bit) architecture.
 *
 */

#ifndef __EPCF_INCLUDED_NATIVE_PORT_X86_32_UART_WIN32_CONFIG_H
#define __EPCF_INCLUDED_NATIVE_PORT_X86_32_UART_WIN32_CONFIG_H

/** \brief Maximum UART channel				*/
#define UART_MAX_CHANNEL		256			//In Windows10

/// Remove this After wards
#define EPCF_UART_USE_FIFO      1
#if(EPCF_UART_USE_FIFO != 0)
/**
 *  \brief Define size in bytes for internal software buffer.
 *  \note The buffer size should be a non-zero and power of 2 number.
 */
  #define EPCF_UART_BUFFER_SIZE       12
#endif  // #if(EPCF_UART_USE_FIFO != 0)

#if(EPCF_UART_USE_FIFO != 0)
//epcf\utils\source\epcf_fifo.c
	#define __EPCF_UTIL_FIFO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,utils/,include/,epcf_fifo.h)
	#include  __EPCF_UTIL_FIFO_INCLUDE
	#undef __EPCF_UTIL_FIFO_INCLUDE
	
  //#warning EPCF_UART_USE_FIFO is enabled for interrupt based communication
  #if( (EPCF_UART_BUFFER_SIZE == 0) || ((UART0_BUFFER_SIZE & (UART0_BUFFER_SIZE - 1)) != 0) )
    #error EPCF_UART_BUFFER_SIZE cannot be zero. EPCF_UART_BUFFER_SIZE should be power of 2
  #endif
#endif  // #if(EPCF_UART_USE_FIFO != 0)

#endif      // __EPCF_INCLUDED_NATIVE_PORT_X86_32_UART_WIN32_CONFIG_H

