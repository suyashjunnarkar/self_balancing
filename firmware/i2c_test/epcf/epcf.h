/**
 * \file  epcf.h
 * \brief This file is to be included by the application program in the begining to use epcf framework.
 */

#ifndef __EPCF_EPCF_H
#define __EPCF_EPCF_H

#ifdef _PCF_INTERNAL_DEBUG
#pragma message "EPCF Framework header included."
#endif
#include "./common/epcfDefs.h"
#include "./common/types.h"
#include "./common/portpin.h"
#include "./common/bitmask.h"
#include "./common/status.h"

#include "epcf_board_config.h"
#include "./peripheral/include/epcf_peripheral.h"

#define EPCF_DIR_PATH               PCF_CONF_PLATFORM_PATH/PCF_CONF_PLATFORM_NAME
#define EPCF_DIR_NATIVE_PATH        EPCF_DIR_PATH/native
#define EPCF_DIR_EXTENDED_PATH      EPCF_EXTENDED_PATH/extended

#define _EPCF_PERIPHERAL_INCLUDE   PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,,peripheral/include/,peripheral.h)
#include _EPCF_PERIPHERAL_INCLUDE
#undef _EPCF_PERIPHERAL_INCLUDE

/*

#if defined(EPCF_BUILD_MODE)
#error "Don't define macro EPCF_BUILD_MODE anywhere else."
#else
    #if(EPCF_CONF_BUILD_MODE == EPCF_BUILD_NATIVE)

        #define EPCF_BUILD_MODE  EPCF_BUILD_NATIVE

    #elif(EPCF_CONF_BUILD_MODE == EPCF_BUILD_EXTENDED)

        #define EPCF_BUILD_MODE  EPCF_BUILD_EXTENDED
		#include "epcf_extended_config.h"
       
        #define _EPCF_EXTENDED_INCLUDE   PCF_CONDITIONAL_INCLUDE_FILE(EXTENDED_PATH/,,,extended.h)
        #include _EPCF_EXTENDED_INCLUDE
        #undef _EPCF_EXTENDED_INCLUDE

        #ifndef PCF_EXTENDED_ARCH_NAME
            #error "PCF_EXTENDED_ARCH_NAME not defined"
        #endif

        #define _EPCF_CONTROLLER_INCLUDE     PCF_CONDITIONAL_INCLUDE_FILE(EXTENDED_PATH/,controller/,,controller.h)
        #include _EPCF_CONTROLLER_INCLUDE
        #undef _EPCF_CONTROLLER_INCLUDE

    #else
        #error "Incorrect value for the EPCF_CONF_BUILD_MODE defined in epcf_config.h       \
                There can be 2 values for EPCF_CONF_BUILD_MODE:         \
                1.  EPCF_BUILD_NATIVE                                   \
                2.  EPCF_BUILD_EXTENDED"
    #endif
#endif



#include "../extended/adapter/adapter.h"


#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    #include "../utils/include/epcf_debug_support.h"
#endif

// #if(EPCF_CONF_BUILD_MODE == EPCF_BUILD_EXTENDED)
	// #include "../extended/adapter/adapter.h"
// #endif

*/
#endif // __EPCF_INCLUDED_EPCF_H
