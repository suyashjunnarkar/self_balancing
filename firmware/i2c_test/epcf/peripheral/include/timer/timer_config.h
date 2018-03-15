/**
 * \file  timer_config.h
 * \brief This file is used to configure a TIMER device
 */

#ifndef __EPCF_INCLUDED_PERIPHERAL_TIMER_TIMER_CONFIG_H
#define __EPCF_INCLUDED_PERIPHERAL_TIMER_TIMER_CONFIG_H

#include "timer.h"

#define __EPCF_TIMER_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/include/timer/,timer_,PCF_ARCH_DEVICE.h)
#include __EPCF_TIMER_INCLUDE
#undef __EPCF_TIMER_INCLUDE

/*
#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
	#if(EPCF_USE_TIMER == PCF_YES)
		#define __EPCF_TIMER_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/include/timer/,timer_,PCF_ARCH_DEVICE.h)
		#include __EPCF_TIMER_INCLUDE
		#undef __EPCF_TIMER_INCLUDE
	#endif
#endif

#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
	#if(EPCF_USE_TIMER == PCF_YES)
		#define __EPCF_TIMER_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/timer/,timer_,PCF_ARCH_DEVICE.h)
		#include __EPCF_TIMER_INCLUDE
		#undef __EPCF_TIMER_INCLUDE
	#endif

	#if(EPCF_EXTENDED_USE_TIMER == PCF_YES)
		#define __EPCF_TIMER_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EXTENDED_PATH/,controller/,timer/,timer_controller.h)
		#include __EPCF_TIMER_INCLUDE
		#undef __EPCF_TIMER_INCLUDE
	#endif
#endif
*/

#endif      //__EPCF_INCLUDED_PERIPHERAL_TIMER_TIMER_CONFIG_H