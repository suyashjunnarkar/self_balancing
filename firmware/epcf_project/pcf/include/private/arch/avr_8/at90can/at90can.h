#ifndef PCF_INCLUDED_AT90CAN_H
#define PCF_INCLUDED_AT90CAN_H

#if !defined(PCF_CONF_ARCH_VARIANT)
#error "Include chain is broken, don't try to include this file directly from \
your code; you will be opening the gates of hell."
#endif

#if (PCF_CONF_ARCH_VARIANT == PCF_GENERIC)
#error "Include chain is broken, don't try to include this file directly from \
your code; you will be opening the gates of hell. Cofigured for generic avr 8 bit \
microcontrollers and yet including a variant specific header."
#endif

#if !defined(__PCF_ARCH)  || !defined(__PCH_AVR_ARCH) || (__PCF_ARCH != __PCH_AVR_ARCH)
#error "Include chain is broken, don't try to include this file directly from \
your code; you will be opening the gates of hell."
#endif

#if defined(PCF_ARCH_VARIANT)
#undef PCF_ARCH_VARIANT
#endif
#define PCF_ARCH_VARIANT PCF_STRINGIFY(AT90CAN)

#define PCF_ARCH_DEVICE_HAS_FPU          PCF_YES
#if !defined(PCF_CONF_ARCH_DEVICE)
#error "Bad configuration, you must provide a valid device in config.h for \
supported avr 8 bit microcontrollers."
#endif

#if (PCF_CONF_ARCH_DEVICE == PCF_NONE)
#error "Bad configuration, you must provide a valid device in config.h for \
supported avr 8 bit microcontrollers."
#endif

#define PCF_DEVICE_INCLUDED_HEADER PCF_CONDITIONAL_INCLUDE_FILE(PCF_CONF_ARCH_DEVICE.h,,,)
#include PCF_DEVICE_INCLUDED_HEADER

#endif  //PCF_INCLUDED_AT90CAN_H