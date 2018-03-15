#ifndef __PCF_INCLUDE_ARCH_ARM_32_CM3_H
#define __PCF_INCLUDE_ARCH_ARM_32_CM3_H

/**
Inclusion of this file requires macro PCF_CONF_ARCH_VARIANT in
config.h to be defined as cm3. Currently, the detection
of arch is provided for GCC compilers. In case,
you have defined the PCF_CONF_ARCH_VARIANT as cm3 and you get
an error from this file, you need to add proper compiler
dependent macro for passing following condition test.
*/

#if defined(PCF_ARCH_VARIANT)
	#error "Don't define macro PCF_COMPILER_TYPE anywhere else."
#else
	#if (PCF_CONF_ARCH_VARIANT == cm3)
		#define PCF_ARCH_VARIANT  cm3
		#undef  PCF_CONF_ARCH_VARIANT
	#endif
#endif

//Add compiler defined MACROS according to the the architecture variant.
#if ( __ARMEL__ != 1 )
	/*#error "Configured for CM3 architecture but compiler doesn't \
            pass the detection. for __ARMEL__ "*/
#elif ( __ARMEL__ == 1 )

	#if (__ARM_ARCH != 7)
		#error "Configured for CM3 architecture but compiler doesn't \
			pass the detection. for __ARM_ARCH "
	#endif

	#if (__ARM_ARCH_7M__ != 1 )
		#error "Configured for CM3 architecture but compiler doesn't \
			pass the detection. for __ARM_ARCH_7M__ "
	#endif

	#if (__ARM_ARCH_PROFILE != 77 )
		#error "Configured for CM3 architecture but compiler doesn't \
			pass the detection. for __ARM_ARCH_PROFILE "
	#endif

	#if (__ARM_EABI__ != 1 )
		#error "Configured for CM3 architecture but compiler doesn't \
			pass the detection. for __ARM_EABI__ "
	#endif

#else
	#error "Configured for CM3 architecture but compiler doesn't \
			pass the detection. If you are using a new compiler which isn't \
			supported by PCF, you must add compiler defined arch macro as one \
			of the conditional, in the above condition."
#endif

//Vendor will get handled from here.
#if !defined(PCF_CONF_ARCH_DEVICE_VENDOR)
    #error "bad configuration, you must define PCF_CONF_ARCH_DEVICE_VENDOR in \
            the config.h"
#endif

#if (PCF_CONF_ARCH_DEVICE_VENDOR != PCF_NONE)

    #define __PCF_CM3_VENDOR_INCLUDE  PCF_CONDITIONAL_INCLUDE_FILE(,PCF_CONF_ARCH_DEVICE_VENDOR/, \
                                                                  ,PCF_CONF_ARCH_DEVICE_VENDOR.h)

/**When the following include fails, it means the vendor for cm3 isnt' supported by
PCF or the value of macro PCF_CONF_ARCH_DEVICE_VENDOR isn't proper. This macro must evaluate
to a proper file with respect to this one at "PCF_CONF_ARCH_DEVICE_VENDOR/PCF_CONF_ARCH_DEVICE_VENDOR.h",
for example, assume you define PCF_CONF_ARCH_DEVICE_VENDOR as lpc, then the file lpc/lpc.h will
get included.*/
    #include __PCF_CM3_VENDOR_INCLUDE
	#undef __PCF_CM3_VENDOR_INCLUDE
#endif

#endif //__PCF_INCLUDED_ARCH_ARM_32_CM3_H

/**
#define __ARMEL__ 1
#define __ARM_32BIT_STATE 1
#define __ARM_ARCH 7
#define __ARM_ARCH_7M__ 1
#define __ARM_ARCH_EXT_IDIV__ 1
#define __ARM_ARCH_ISA_THUMB 2
#define __ARM_ARCH_PROFILE 77
#define __ARM_EABI__ 1
#define __ARM_FEATURE_CLZ 1
#define __ARM_FEATURE_LDREX 7
#define __ARM_FEATURE_QBIT 1
#define __ARM_FEATURE_SAT 1
#define __ARM_FEATURE_UNALIGNED 1
#define __ARM_FP 12
#define __ARM_NEON_FP 4
#define __ARM_PCS 1
#define __ARM_SIZEOF_MINIMAL_ENUM 1
#define __ARM_SIZEOF_WCHAR_T 4
#define __THUMBEL__ 1
#define __THUMB_INTERWORK__ 1
#define __VERSION__ "4.9.3 20150303 (release) [ARM/embedded-4_9-branch revision 221220]"
#define __arm__ 1
#define __thumb2__ 1
#define __thumb__ 1
*/


