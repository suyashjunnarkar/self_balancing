/**
 * \file  can_config.h
 * \brief This file is used to configure a CAN device
 */

#ifndef __EPCF_INCLUDED_PERIPHERAL_CAN_CAN_CONFIG_H
#define __EPCF_INCLUDED_PERIPHERAL_CAN_CAN_CONFIG_H

#include "can.h"

#define __EPCF_CAN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/include/can/,can_,PCF_ARCH_DEVICE.h)
#include __EPCF_CAN_INCLUDE
#undef __EPCF_CAN_INCLUDE
//
//#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
//  #if(EPCF_USE_CAN == PCF_YES)
//    #if (PCF_ARCH == PCF_ARCH_X86)
//		#define __EPCF_CAN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/can/PCF_OS_NAME/,can_,PCF_ARCH_NAME.h)
//		#include __EPCF_CAN_INCLUDE
//		#undef __EPCF_CAN_INCLUDE
//    #else
//		#define __EPCF_CAN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/can/,can_,PCF_ARCH_DEVICE.h)
//		#include __EPCF_CAN_INCLUDE
//		#undef __EPCF_CAN_INCLUDE
//    #endif
//  #endif
//#endif
//
//#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
//	#if(EPCF_USE_CAN == PCF_YES)
//		#if (PCF_ARCH == PCF_ARCH_X86)
//			#define __EPCF_CAN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/can/PCF_OS_NAME/,can_,PCF_ARCH_NAME.h)
//			#include __EPCF_CAN_INCLUDE
//			#undef __EPCF_CAN_INCLUDE
//		#else
//			#define __EPCF_CAN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/can/,can_,PCF_ARCH_DEVICE.h)
//			#include __EPCF_CAN_INCLUDE
//			#undef __EPCF_CAN_INCLUDE
//		#endif
//	#endif
//	#if(EPCF_EXTENDED_USE_CAN == PCF_YES)
//		#define __EPCF_CAN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EXTENDED_PATH/,controller/,can/,can_controller.h)
//		#include __EPCF_CAN_INCLUDE
//		#undef __EPCF_CAN_INCLUDE
//	#endif
//
//#endif

#endif      //__EPCF_INCLUDED_PERIPHERAL_CAN_CAN_CONFIG_H
