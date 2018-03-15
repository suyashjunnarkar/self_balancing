#ifndef PCF_INCLUDED_AVR_8_H
#define PCF_INCLUDED_AVR_8_H

#define __PCH_AVR_ARCH 1100111

#if !defined(PCF_ARCH_INCLUDED_HEADER)
    #error "Don't include this file (__PCF_FILE__) from any where else. arch.h includes it \
            based on the parameters passed via config.h"
#endif  

#if !defined(__GNUC__)
    #error "Unsupported compiler, currently PCF only supports GNU GCC (AVR-GCC) \
            compiler for AVR 8 bit microcontrollers."
#endif

#if defined(__AVR_ARCH__) 
    #if  defined( __AVR_ASM_ONLY__)
        #error "Bad AVR Architecture. PCF framework doesn't support AVRs which are \
                only meant to be used with assemblers."    
    #endif
#else
    #error "Bad GCC compiler for AVR. Required macro __AVR_ARCH__ isn't defined."
#endif

#if defined(PCF_ARCH_SIZE)
#undef PCF_ARCH_SIZE
#endif
#define PCF_ARCH_SIZE                8

#if defined(PCF_ARCH_BYTE_ORDER)
#undef PCF_ARCH_BYTE_ORDER
#endif
#define PCF_ARCH_BYTE_ORDER          PCF_ARCH_LITTLE_ENDIAN

#if defined(PCF_ARCH_DEVICE_HAS_FPU)
#undef PCF_ARCH_DEVICE_HAS_FPU
#endif
#define PCF_ARCH_DEVICE_HAS_FPU          PCF_YES


#if (PCF_CONF_ARCH_DEVICE == PCF_GENERIC)
    #include "avr_generic.h"
#else                           
#if !defined(PCF_CONF_ARCH_VARIANT) || (PCF_CONF_ARCH_VARIANT == PCF_NONE)
#error "You have configured for avr_8 architecture, you must choose from one of the \
supported variants."
#endif       

#if defined(PCF_ARCH_DEVICE_VENDOR)
#undef PCF_ARCH_DEVICE_VENDOR  
#endif
#define PCF_ARCH_DEVICE_VENDOR  PCF_STRINGIFY(Atmel)

#define PCF_VARIANT_INCLUDED_HEADER PCF_CONDITIONAL_INCLUDE_FILE(PCF_CONF_ARCH_VARIANT/,PCF_CONF_ARCH_VARIANT.h,,)
#define __PCF_ARCH __PCH_AVR_ARCH
#include PCF_VARIANT_INCLUDED_HEADER
#endif

#endif //PCF_INCLUDED_AVR_8_H