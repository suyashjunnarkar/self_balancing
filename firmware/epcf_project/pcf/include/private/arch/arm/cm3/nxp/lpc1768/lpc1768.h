#ifndef __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_H
#define __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_H

/**
Inclusion of this file requires macro PCF_CONF_ARCH_DEVICE in
config.h to be defined as lpc1768.
*/

#if defined(PCF_ARCH_DEVICE)
	#error "Don't define macro PCF_ARCH_DEVICE anywhere else."
#else

#if (PCF_CONF_ARCH_DEVICE == lpc)
	#define PCF_ARCH_DEVICE			lpc1768
	#undef  PCF_CONF_ARCH_DEVICE
#endif

#endif

#if !defined(PCF_CONF_ARCH_DEVICE_CLK)
	#error "Don't define macro PCF_COMPILER_TYPE anywhere else."
#else
    // TODO: Add properly the PCF_ARCH_DEVICE_CLK
	#define PCF_ARCH_DEVICE_CLK PCF_CONF_ARCH_DEVICE_CLK
#endif
//#undef PCF_CONF_ARCH_DEVICE_CLK

#ifdef _PCF_INTERNAL_DEBUG
#pragma message "PCF_ARCH_DEVICE_CLK :" PCF_STRINGIFY(PCF_ARCH_DEVICE_CLK)
#endif

#include "./lpc1768_regmap.h"
#include "./lpc1768_regdefs.h"
#include "./lpc1768_config.h"

#endif	//__PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_H
