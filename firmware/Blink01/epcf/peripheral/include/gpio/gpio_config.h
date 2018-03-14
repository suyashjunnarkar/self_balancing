/**
 * \file  gpio_config.h
 * \brief This file is used to configure a GPIO device
 */

#ifndef __EPCF_INCLUDE_PERIPHERAL_GPIO_GPIO_CONFIG_H
#define __EPCF_INCLUDE_PERIPHERAL_GPIO_GPIO_CONFIG_H

#include "gpio.h"

#define EPCF_GPIO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/include/gpio/,gpio_,PCF_ARCH_DEVICE.h)
#include EPCF_GPIO_INCLUDE
#undef EPCF_GPIO_INCLUDE

//#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
//    #if(EPCF_USE_GPIO == PCF_YES)
//        #define EPCF_GPIO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/include/gpio/,gpio_,PCF_ARCH_DEVICE.h)
//        #include EPCF_GPIO_INCLUDE
//        #undef EPCF_GPIO_INCLUDE
//    #endif
//#endif
//
//#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
//    #if(EPCF_USE_GPIO == PCF_YES)
//        #define EPCF_GPIO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/include/gpio/,gpio_,PCF_ARCH_DEVICE.h)
//        #include EPCF_GPIO_INCLUDE
//        #undef EPCF_GPIO_INCLUDE
//    #endif
//
//    #if(EPCF_EXTENDED_USE_GPIO == PCF_YES)
//        #define EPCF_GPIO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EXTENDED_PATH/,controller/,gpio/,gpio_controller.h)
//        #include EPCF_GPIO_INCLUDE
//        #undef EPCF_GPIO_INCLUDE
//    #endif
//#endif

#endif      //__EPCF_INCLUDE_PERIPHERAL_GPIO_GPIO_CONFIG_H
