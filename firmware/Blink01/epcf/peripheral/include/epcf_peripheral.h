/**
 *  \file       epcf_peripheral.h
 *  \details    All Peripheral are resolved hear.
 *
 */

#ifndef __EPCF_PERIPHERAL_INCLUDE_EPCF_PERIPHERAL_H
#define __EPCF_PERIPHERAL_INCLUDE_EPCF_PERIPHERAL_H

//////////////////////////////  Peripheral System Clock (SYSCLK)    ///////////////////////////

#ifndef EPCF_CONF_USE_SYSCLK
#error "EPCF_CONF_USE_SYSCLK is not defined.  \
        You must use the proper configuration epcf_config.h header."
#endif

#ifdef EPCF_USE_SYSCLK
    #error "Don't define macro EPCF_USE_SYSCLK anywhere else."
#endif

#if (EPCF_CONF_USE_SYSCLK == PCF_YES)

    #if (PCF_IS_PERIPH_SYSCLK == PCF_YES)
        #define EPCF_USE_SYSCLK     PCF_YES
    #else

        #error "Architecture Platform You have seleted don't have the SYSCLK Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_SYSCLK == PCF_NO)
    #define EPCF_USE_SYSCLK     PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_SYSCLK defined in epcf_config.h       \
            There can be 2 values for EPCF_CONF_USE_SYSCLK:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_SYSCLK

//////////////////////////////    Peripheral GPIO              ///////////////////////////

#ifndef EPCF_CONF_USE_GPIO
#error "EPCF_CONF_USE_GPIO is not defined.  \
        You must use the proper configuration epcf_config_headers."
#endif

#ifdef EPCF_USE_GPIO
    #error "Don't define macro EPCF_USE_GPIO anywhere else."
#endif

#if (EPCF_CONF_USE_GPIO == PCF_YES)

    #if (PCF_IS_PERIPH_GPIO == PCF_YES)
        #define EPCF_USE_GPIO   PCF_YES
    #else
        #error "Architecture Platform You have seleted don't have the GPIO Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_GPIO == PCF_NO)
    #define EPCF_USE_GPIO   PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_GPIO defined in epcf_config.h     \
                There can be 2 values for EPCF_CONF_USE_GPIO:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_GPIO

//////////////////////////////    Peripheral UART             ///////////////////////////

#ifndef EPCF_CONF_USE_UART
#error "EPCF_CONF_USE_UART is not defined.  \
        You must use the proper configuration epcf_config_headers."
#endif

#ifdef EPCF_USE_UART
    #error "Don't define macro EPCF_USE_UART anywhere else."
#endif

#if (EPCF_CONF_USE_UART == PCF_YES)

    #if (PCF_IS_PERIPH_UART == PCF_YES)
        #define EPCF_USE_UART   PCF_YES
    #else
        #error "Architecture Platform You have seleted don't have the UART Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_UART == PCF_NO)
    #define EPCF_USE_UART   PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_UART defined in epcf_config.h     \
                There can be 2 values for EPCF_CONF_USE_UART:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_UART

//////////////////////////////    Peripheral TIMER             ///////////////////////////

#ifndef EPCF_CONF_USE_TIMER
#error "EPCF_CONF_USE_TIMER is not defined.  \
        You must use the proper configuration epcf_config_headers."
#endif

#ifdef EPCF_USE_TIMER
    #error "Don't define macro EPCF_USE_TIMER anywhere else."
#endif

#if (EPCF_CONF_USE_TIMER == PCF_YES)

    #if (PCF_IS_PERIPH_TIMER == PCF_YES)
        #define EPCF_USE_TIMER   PCF_YES
    #else
        #error "Architecture Platform You have seleted don't have the TIMER Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_TIMER == PCF_NO)
    #define EPCF_USE_TIMER   PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_TIMER defined in epcf_config.h     \
                There can be 2 values for EPCF_CONF_USE_TIMER:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_TIMER

//////////////////////////////    Peripheral I2C             ///////////////////////////

#ifndef EPCF_CONF_USE_I2C
#error "EPCF_CONF_USE_I2C is not defined.  \
        You must use the proper configuration epcf_config_headers."
#endif

#ifdef EPCF_USE_I2C
    #error "Don't define macro EPCF_USE_I2C anywhere else."
#endif

#if (EPCF_CONF_USE_I2C == PCF_YES)

    #if (PCF_IS_PERIPH_I2C == PCF_YES)
        #define EPCF_USE_I2C   PCF_YES
    #else
        #error "Architecture Platform You have seleted don't have the I2C Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_I2C == PCF_NO)
    #define EPCF_USE_I2C   PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_I2C defined in epcf_config.h     \
                There can be 2 values for EPCF_CONF_USE_I2C:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_I2C
//////////////////////////////    Peripheral CAN             ///////////////////////////

#ifndef EPCF_CONF_USE_CAN
#error "EPCF_CONF_USE_CAN is not defined.  \
        You must use the proper configuration epcf_config_headers."
#endif

#ifdef EPCF_USE_CAN
    #error "Don't define macro EPCF_USE_CAN anywhere else."
#endif

#if (EPCF_CONF_USE_CAN == PCF_YES)

    #if (PCF_IS_PERIPH_CAN == PCF_YES)
        #define EPCF_USE_CAN   PCF_YES
    #else
        #error "Architecture Platform You have seleted don't have the CAN Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_CAN == PCF_NO)
    #define EPCF_USE_CAN   PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_CAN defined in epcf_config.h     \
                There can be 2 values for EPCF_CONF_USE_CAN:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_CAN
//////////////////////////////    Peripheral PWM             ///////////////////////////

#ifndef EPCF_CONF_USE_PWM
#error "EPCF_CONF_USE_PWM is not defined.  \
        You must use the proper configuration epcf_config_headers."
#endif

#ifdef EPCF_USE_PWM
    #error "Don't define macro EPCF_USE_PWM anywhere else."
#endif

#if (EPCF_CONF_USE_PWM == PCF_YES)

    #if (PCF_IS_PERIPH_PWM == PCF_YES)
        #define EPCF_USE_PWM   PCF_YES
    #else
        #error "Architecture Platform You have seleted don't have the PWM Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_PWM == PCF_NO)
    #define EPCF_USE_PWM   PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_PWM defined in epcf_config.h     \
                There can be 2 values for EPCF_CONF_USE_PWM:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_PWM

//////////////////////////////    Peripheral ADC             ///////////////////////////

#ifndef EPCF_CONF_USE_ADC
#error "EPCF_CONF_USE_ADC is not defined.  \
        You must use the proper configuration epcf_config_headers."
#endif

#ifdef EPCF_USE_ADC
    #error "Don't define macro EPCF_USE_ADC anywhere else."
#endif

#if (EPCF_CONF_USE_ADC == PCF_YES)

    #if (PCF_IS_PERIPH_ADC == PCF_YES)
        #define EPCF_USE_ADC   PCF_YES
    #else
        #error "Architecture Platform You have seleted don't have the ADC Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_ADC == PCF_NO)
    #define EPCF_USE_ADC   PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_ADC defined in epcf_config.h     \
                There can be 2 values for EPCF_CONF_USE_ADC:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_ADC

#if (EPCF_CONF_USE_WDT == PCF_YES)

    #if (PCF_IS_PERIPH_WDT == PCF_YES)
        #define EPCF_USE_WDT   PCF_YES
    #else
        #error "Architecture Platform You have seleted don't have the WDT Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_WDT == PCF_NO)
    #define EPCF_USE_WDT   PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_WDT defined in epcf_config.h     \
                There can be 2 values for EPCF_CONF_USE_WDT:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_WDT

#if (EPCF_CONF_USE_SPI == PCF_YES)

    #if (PCF_IS_PERIPH_SPI == PCF_YES)
        #define EPCF_USE_SPI   PCF_YES
    #else
        #error "Architecture Platform You have seleted don't have the SPI Peripheral.\
                 You must Pass the appropiate Architecture in the pcf_config.h . \
                 If you are adding support to new Architecture check your architecture file \
                 in the pcf/arch/...../yourArchitecture.h file. \
                 PCF_CONF_ARCH_DEVICE : " PCF_STRINGIFY(PCF_ARCH_DEVICE)
    #endif

#elif(EPCF_CONF_USE_SPI == PCF_NO)
    #define EPCF_USE_SPI   PCF_NO
#else
    #error "Incorrect value for the EPCF_CONF_USE_SPI defined in epcf_config.h     \
                There can be 2 values for EPCF_CONF_USE_SPI:         \
                1.  PCF_YES                                             \
                2.  PCF_NO"
#endif
#undef EPCF_CONF_USE_SPI

#endif /* __EPCF_PERIPHERAL_INCLUDE_EPCF_PERIPHERAL_H */
