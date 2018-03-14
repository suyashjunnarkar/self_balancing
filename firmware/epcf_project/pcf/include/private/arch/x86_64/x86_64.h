#ifndef __PCF_INCLUDED_ARCH_X86_64_H
#define __PCF_INCLUDED_ARCH_X86_64_H

/**
Inclusion of this file requires macro PCF_CONF_ARCH in
config.h to be defined as x86_64. Currently, the detection
of arch is provided for MinGW, MSVC and GCC compilers. In case,
you have defined the PCF_CONF_ARCH as x86_64 and you get
an error from this file, you need to add proper compiler
dependent macro for passing following condition test.
*/
#if defined(_M_X64)   || defined(_M_IA64) || \
    defined(_M_AMD64)  || defined(__amd64__) || defined(__amd64) || \
    defined(__x86_64__) || defined(__x86_64) || \
    defined(__ia64__) || defined(_IA64)  || defined(__IA64__)

#if defined(PCF_ARCH)
	#error "Don't define macro PCF_ARCH anywhere else."
#else
	#define PCF_ARCH         PCF_ARCH_X86_64
	#define PCF_ARCH_DEVICE	 PCF_ARCH_X86_64
	#undef  PCF_CONF_ARCH
#endif

#else
#error "Configured for X86 64Bit architecture but compiler doesn't \
        pass the detection. If you are using a new compiler which isn't \
        supported by PCF, you must add compiler defined arch macro as one \
        of the conditional, in the above condition."
#endif

#if defined(PCF_ARCH_SIZE)
#undef PCF_ARCH_SIZE
#endif
#define PCF_ARCH_SIZE                64

#if defined(PCF_CONF_BYTE_ORDER)
#undef PCF_CONF_BYTE_ORDER
#endif

//command to find on linus is lscpu
#define PCF_BYTE_ORDER             PCF_ARCH_LITTLE_ENDIAN

//Native peripheral MACROS
#if defined(EPCF_USE_UART)
#error "Don't define macro EPCF_USE_UART anywhere else."
#else
	#if(EPCF_CONF_USE_UART == PCF_YES)
		#define EPCF_USE_UART	PCF_YES
	#elif(EPCF_CONF_USE_UART == PCF_NO)
		#define EPCF_USE_UART	PCF_NO
	#else
		#error "Incorrect value for the EPCF_CONF_USE_UART defined in epcf_config.h		\
		There can be 2 values for EPCF_CONF_USE_UART: 		\
		1.	PCF_YES												\
		2.	PCF_NO"
	#endif
#endif
#undef EPCF_CONF_USE_UART

//Handle SSE,MMX over here.

#endif  //__PCF_INCLUDED_ARCH_X86_64_H
