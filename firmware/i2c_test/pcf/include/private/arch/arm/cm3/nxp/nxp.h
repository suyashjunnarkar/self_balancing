#ifndef __PCF_INCLUDE_PRIVATE_ARCH_ARM_NXP_NXP_H
#define __PCF_INCLUDE_PRIVATE_ARCH_ARM_NXP_NXP_H

/**
Inclusion of this file requires macro PCF_CONF_ARCH_DEVICE_VENDOR in
config.h to be defined as nxp.
*/

#if defined(PCF_ARCH_DEVICE_VENDOR)
	#error "Don't define macro PCF_COMPILER_TYPE anywhere else."
#else

#if (PCF_CONF_ARCH_DEVICE_VENDOR == nxp)
	#define PCF_ARCH_DEVICE_VENDOR  nxp
	#undef  PCF_CONF_ARCH_DEVICE_VENDOR
#endif

#endif

//Device will get handled from here.
#if !defined(PCF_CONF_ARCH_DEVICE)
    #error "bad configuration, you must define PCF_CONF_ARCH_DEVICE in 	\
            the config.h. Arm 32bit arhcitecture expects a variant. Define the macro PCF_CONF_ARCH_DEVICE, to \
            a proper value for including the right device."
#endif

#if (PCF_CONF_ARCH_DEVICE != PCF_NONE)

    #define __PCF_ARCH_DEVICE_INCLUDE  PCF_CONDITIONAL_INCLUDE_FILE(,PCF_CONF_ARCH_DEVICE/, \
                                                                  ,PCF_CONF_ARCH_DEVICE.h)

/**When the following include fails, it means the device for nxp isnt' supported by
PCF or the value of macro PCF_CONF_ARCH_DEVICE isn't proper. This macro must evaluate
to a proper file with respect to this one at "PCF_CONF_ARCH_VARIANT/PCF_CONF_ARCH_VARIANT.h",
for example, assume you define PCF_CONF_ARCH_DEVICE as lpc1768, then the file lpc1768/lpc1768.h will
get included.*/
    #include __PCF_ARCH_DEVICE_INCLUDE
	#undef	__PCF_ARCH_DEVICE_INCLUDE
#endif

#if !defined(PCF_ARCH_DEVICE)
#error "PCF_ARCH_DEVICE must be defined. This error is because of bad implementation of \
		PhiRobotics' developer or someone who has added new compiler support."
#endif

#endif //__PCF_INCLUDE_PRIVATE_ARCH_ARM_NXP_NXP_H
