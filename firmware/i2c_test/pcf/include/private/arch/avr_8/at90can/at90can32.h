#ifndef PCF_INCLUDED_AT90CAN32_H
#define PCF_INCLUDED_AT90CAN32_H

#define __PCF_MIN_DEVICE_CLOCK 8000000
#define __PCF_MAX_DEVICE_CLOCK 16000000

#if !defined(PCF_CONF_ARCH_DEVICE_CLK)
#error "You must define the macro PCF_CONF_ARCH_DEVICE_CLK between \
8000000 to 1600000."
#endif

#if (PCF_CONF_ARCH_DEVICE_CLK <= __PCF_MAX_DEVICE_CLOCK) && \
(PCF_CONF_ARCH_DEVICE_CLK >= __PCF_MIN_DEVICE_CLOCK) 
    #if defined(PCF_ARCH_DEVICE_CLK)
        #undef PCF_ARCH_DEVICE_CLK
    #endif
    #define PCF_ARCH_DEVICE_CLK  PCF_CONF_ARCH_DEVICE_CLK
#else
    #error "Your configuration for device clock isn't correct. Set your value between\
8000000 and 16000000."
#endif                                                   

#if defined(PCF_ARCH_DEVICE)
#undef PCF_ARCH_DEVICE
#endif
#define PCF_ARCH_DEVICE PCF_STRINGIFY(AT90CAN32)

#endif  //PCF_INCLUDED_AT90CAN_H