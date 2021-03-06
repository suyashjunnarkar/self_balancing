/**
 * \file  extInt_config.h
 * \brief This file is used to configure a External Interrupt device
 */

#ifndef __EPCF_INCLUDE_PERIPHERAL_EXTINT_EXTINT_CONFIG_H
#define __EPCF_INCLUDE_PERIPHERAL_EXTINT_EXTINT_CONFIG_H

#define EPCF_EXTINT_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,peripheral/,extInt/,extInt.h)
#include  EPCF_EXTINT_INCLUDE
#undef EPCF_EXTINT_INCLUDE


#if(EPCF_BUILD_MODE == EPCF_BUILD_NATIVE)
    #if(EPCF_USE_EXTINT == PCF_YES)
        #define EPCF_EXTINT_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/extInt/,extInt_,PCF_ARCH_DEVICE.h)
        #include EPCF_EXTINT_INCLUDE
        #undef EPCF_EXTINT_INCLUDE
    #endif
#endif

#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    #if(EPCF_USE_EXTINT == PCF_YES)
        #define EPCF_EXTINT_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(NATIVE_PATH/,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/PCF_ARCH_DEVICE/extInt/,extInt_,PCF_ARCH_DEVICE.h)
        #include EPCF_EXTINT_INCLUDE
        #undef EPCF_EXTINT_INCLUDE
    #endif

    #if(EPCF_EXTENDED_USE_EXTINT == PCF_YES)
        #define EPCF_EXTINT_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EXTENDED_PATH/,controller/,extInt/,extInt_controller.h)
        #include EPCF_EXTINT_INCLUDE
        #undef EPCF_EXTINT_INCLUDE
    #endif
#endif

#endif      //__EPCF_INCLUDE_PERIPHERAL_EXTINT_EXTINT_CONFIG_H
