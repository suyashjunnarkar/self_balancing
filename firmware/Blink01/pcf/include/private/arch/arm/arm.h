#ifndef __PCF_INCLUDE_PRIVATE_ARCH_ARM_ARM_H
#define __PCF_INCLUDE_PRIVATE_ARCH_ARM_ARM_H
/**
Inclusion of this file requires macro PCF_CONF_ARCH in
config.h to be defined as arm. Currently, the detection
of arch is provided for GCC compilers. In case,
you have defined the PCF_CONF_ARCH as arm and you get
an error from this file, you need to add proper compiler
dependent macro for passing following condition test.
*/

#if defined(PCF_ARCH)
	#error "Don't define macro PCF_ARCH anywhere else."
#else
	#if (PCF_CONF_ARCH == PCF_ARCH_ARM)
		#define PCF_ARCH  PCF_ARCH_ARM
		#undef  PCF_CONF_ARCH
	#endif
#endif

#if !(defined(__arm__) || defined(__thumb__))
	#error "Configured for ARM 32Bit architecture but compiler doesn't \
			pass the detection. If you are using a new compiler which isn't \
			supported by PCF, you must add compiler defined arch macro as one \
			of the conditional, in the above condition."
#endif

//Variant will get handled from here.
#if !defined(PCF_CONF_ARCH_VARIANT)
    #error "bad configuration, you must define PCF_CONF_ARCH_VARIANT in the config.h.  \
			Arm 32bit arhcitecture expects a variant. Define the macro PCF_CONF_ARCH_VARIANT, to \
            a proper value for including the right device."
#endif

#if (PCF_CONF_ARCH_VARIANT != PCF_NONE)

/**
When the following include fails, it means the variant for arm32 isnt' supported by
PCF or the value of macro PCF_CONF_ARCH_VARIANT isn't proper. This macro must evaluate
to a proper file with respect to this one at "PCF_CONF_ARCH_VARIANT/PCF_CONF_ARCH_VARIANT.h",
for example, assume you define PCF_CONF_ARCH_VARIANT as cm0, then the file cm0/cm0.h will
get included.
*/
    #define PCF_ARM_32_VARIANT_INCLUDE      \
                PCF_CONDITIONAL_INCLUDE_FILE(,PCF_CONF_ARCH_VARIANT/,,PCF_CONF_ARCH_VARIANT.h)
    #include PCF_ARM_32_VARIANT_INCLUDE
	#undef PCF_ARM_32_VARIANT_INCLUDE
#endif

#endif //__PCF_INCLUDE_PRIVATE_ARCH_ARM_ARM_H
