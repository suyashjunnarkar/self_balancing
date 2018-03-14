/**
$ ./arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft \
-E -dM - < /dev/null | egrep -i 'thumb|arm|cortex|fp__|version|abi' | sort
#define __ARMEL__ 1
#define __ARM_32BIT_STATE 1
#define __ARM_ARCH 7
#define __ARM_ARCH_7EM__ 1
#define __ARM_ARCH_EXT_IDIV__ 1
#define __ARM_ARCH_ISA_THUMB 2
#define __ARM_ARCH_PROFILE 77
#define __ARM_EABI__ 1
#define __ARM_FEATURE_CLZ 1
#define __ARM_FEATURE_DSP 1
#define __ARM_FEATURE_LDREX 7
#define __ARM_FEATURE_QBIT 1
#define __ARM_FEATURE_SAT 1
#define __ARM_FEATURE_SIMD32 1
#define __ARM_FEATURE_UNALIGNED 1
#define __ARM_FP 12
#define __ARM_NEON_FP 4
#define __ARM_PCS 1
#define __ARM_SIZEOF_MINIMAL_ENUM 1
#define __ARM_SIZEOF_WCHAR_T 4
#define __GXX_ABI_VERSION 1002
#define __SOFTFP__ 1
#define __THUMBEL__ 1
#define __THUMB_INTERWORK__ 1
#define __VERSION__ "4.9.3 20150303 (release) [ARM/embedded-4_9-branch revision 221220]"
#define __VFP_FP__ 1
#define __arm__ 1
#define __thumb2__ 1
#define __thumb__ 1

$ ./arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard \
-mfpu=fpv4-sp-d16 -E -dM - < /dev/null | egrep -i 'thumb|arm|cortex|fp__|version|abi' | sort
#define __ARMEL__ 1
#define __ARM_32BIT_STATE 1
#define __ARM_ARCH 7
#define __ARM_ARCH_7EM__ 1
#define __ARM_ARCH_EXT_IDIV__ 1
#define __ARM_ARCH_ISA_THUMB 2
#define __ARM_ARCH_PROFILE 77
#define __ARM_EABI__ 1
#define __ARM_FEATURE_CLZ 1
#define __ARM_FEATURE_DSP 1
#define __ARM_FEATURE_FMA 1
#define __ARM_FEATURE_LDREX 7
#define __ARM_FEATURE_QBIT 1
#define __ARM_FEATURE_SAT 1
#define __ARM_FEATURE_SIMD32 1
#define __ARM_FEATURE_UNALIGNED 1
#define __ARM_FP 4
#define __ARM_NEON_FP 4
#define __ARM_PCS_VFP 1
#define __ARM_SIZEOF_MINIMAL_ENUM 1
#define __ARM_SIZEOF_WCHAR_T 4
#define __GXX_ABI_VERSION 1002
#define __THUMBEL__ 1
#define __THUMB_INTERWORK__ 1
#define __VERSION__ "4.9.3 20150303 (release) [ARM/embedded-4_9-branch revision 221220]"
#define __VFP_FP__ 1
#define __arm__ 1
#define __thumb2__ 1
#define __thumb__ 1
*/