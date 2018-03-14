/**
 * \file    pcf.h
 * \brief   Phi-C Framework basic common build solution which resolves all the dependency
 *          such as compiler, platform between various Phi-framework.
 *          purpose of this system is to resolve various dependency so, that it is possible
 *          to compile the same project using different configuration for various archtecture/os.
 *
 * \note    This file used be the only file which should be include in the project.
 *          Every Project should have a pcf_config.h file which holds all the configuration
 *          related information which is neccessary for using the pcf Build system.
 */

/*List of Macro resolved in this file:
    #define PCF_CONF_IS_PLATFORM                    PCF_YES
    #define PCF_CONF_PLATFORM_NAME
*/

#ifndef __PCF_INCLUDED_INCLUDE_PCF_H
#define __PCF_INCLUDED_INCLUDE_PCF_H

#include "private/defs.h"
#include "pcf_config.h"

#include "private/compiler.h"
#include "private/arch.h"
#include "private/os.h"
#include "private/debug.h"
#include "private/info.h"

//TODO: Adding the PCF_IS_BUILDING support
#ifdef PCF_IS_BUILDING
//#define PCF_CONFIG_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(PCF_,,,config.h)
//Shall include "pcf_config.h"
//#include PCF_CONFIG_INCLUDE
#else

// Resolving the PCF_CONF_PLATFORM Related Macro.
#ifndef PCF_CONF_IS_PLATFORM

// Used for debugging the PCF
#ifdef _PCF_INTERNAL_DEBUG
    #pragma message "PCF_CONF_IS_PLATFORM :" PCF_STRINGIFY(PCF_CONF_IS_PLATFORM)
#endif

    #error "PCF_CONF_IS_PLATFORM must be defined in pcf_config.h\
            YOu must use the Proper pcf_config templates for configuration."
#endif

#ifndef PCF_CONF_PLATFORM_NAME

#ifdef _PCF_INTERNAL_DEBUG
    #pragma message " PCF_CONF_PLATFORM_NAME : " PCF_STRINGIFY(PCF_CONF_PLATFORM_NAME)
#endif

    #error "PCF_CONF_PLATFORM_NAME is not defined and PCF_CONF_IS_PLATFORM is set to PCF_YES. \
            You should pass the appropiate platform name in pcf_config.h using \
            Macro PCF_CONF_PLATFORM_NAME. This is required to include proper header of PLATFORM \
            example : PCF_CONF_PLATFORM_PATH/PCF_CONF_PLATFORM_NAME/PCF_CONF_PLATFORM_PATH.h"
#endif

#ifndef PCF_CONF_PLATFORM_PATH

#ifdef _PCF_INTERNAL_DEBUG
    #pragma message " PCF_CONF_PLATFORM_NAME : " PCF_STRINGIFY(PCF_CONF_PLATFORM_NAME)
#endif

    #error "PCF_CONF_PLATFORM_PATH is not defined and PCF_CONF_IS_PLATFORM is set to PCF_YES. \
            either change configuration or defined the path of your Platform in pcf_config.h in \
            Macro PCF_CONF_PLATFORM_PATH "
#endif


#if PCF_CONF_IS_PLATFORM == PCF_YES
    #define PCF_IS_PLATFORM  PCF_YES
#else
    #define PCF_IS_PLATFORM  PCF_NO
#endif
#undef PCF_CONF_IS_PLATFORM

#if PCF_IS_PLATFORM  == PCF_YES

    // including Framework Platform header files
    // PCF_CONF_PLATFORM_PATH/PCF_CONF_PLATFORM_NAME/PCF_CONF_PLATFORM_PATH.h
    #define _PCF_PLATFORM_INCLUDE     PCF_CONDITIONAL_INCLUDE_FILE(PCF_CONF_PLATFORM_PATH/,PCF_CONF_PLATFORM_NAME/,,PCF_CONF_PLATFORM_NAME.h)
    #include _PCF_PLATFORM_INCLUDE
    #undef _PCF_PLATFORM_INCLUDE

#endif

#endif //  #ifdef PCF_IS_BUILDING

#endif //__PCF_INCLUDED_INCLUDE_PCF_H
