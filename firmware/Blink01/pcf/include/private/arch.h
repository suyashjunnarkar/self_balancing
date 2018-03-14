#ifndef __PCF_INCLUDE_PRIVATE_ARCH_H
#define __PCF_INCLUDE_PRIVATE_ARCH_H

#if !defined(PCF_CONF_ARCH)
    #error "bad configuration, you must define PCF_CONF_ARCH in the config.h"
#endif

#if defined(PCF_ARCH_NAME)
    #error "Don't define macro PCF_ARCH_NAME anywhere else."
#endif

#if (PCF_CONF_ARCH == PCF_ARCH_AVR)
#define PCF_ARCH_NAME 	avr
#elif (PCF_CONF_ARCH == PCF_ARCH_ARM)
#define PCF_ARCH_NAME arm
#elif (PCF_CONF_ARCH == PCF_ARCH_X86)
#define PCF_ARCH_NAME x86
#else
#error "Unknown ARCHITECTURE type, defined correct arch type in epcf_config.h"
#endif

#if defined(PCF_CONF_ARCH)
	#define PCF_ARCH_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(arch/, PCF_ARCH_NAME/,,PCF_ARCH_NAME.h)
	#include PCF_ARCH_INCLUDE
	#undef PCF_ARCH_INCLUDE
#endif

#endif  //__PCF_INCLUDE_PRIVATE_ARCH_H
