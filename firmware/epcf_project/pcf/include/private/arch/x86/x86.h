#ifndef __PCF_INCLUDED_ARCH_X86_H
#define __PCF_INCLUDED_ARCH_X86_H

#if !defined(PCF_CONF_PLATFORM_BIT_SIZE)
//   TODO:  error msg should be added
#error "You shall not include this file directly in your code."
#endif

#if !defined(PCF_CONF_ARCH)
//   TODO:  error msg should be added
#error "You shall not include this file directly in your code."
#endif

#if defined(PCF_ARCH)
//   TODO:  error msg should be added
#endif

#if defined(PCF_ARCH_DEVICE)
//   TODO:  error msg should be added
#endif

#if defined(PCF_ARCH_SIZE)
//   TODO:  error msg should be added
#endif

#if defined(PCF_PLATFORM_BIT_SIZE)
//   TODO:  error msg should be added
#endif

#if defined(PCF_BYTE_ORDER)
//   TODO:  error msg should be added
#endif

#if (PCF_CONF_PLATFORM_BIT_SIZE == PCF_PLATFORM_IS_8BIT)
	#define  PCF_PLATFORM_BIT_SIZE    PCF_PLATFORM_IS_8BIT
#elif (PCF_CONF_PLATFORM_BIT_SIZE == PCF_PLATFORM_IS_16BIT)
	#define  PCF_PLATFORM_BIT_SIZE    PCF_PLATFORM_IS_16BIT
#elif (PCF_CONF_PLATFORM_BIT_SIZE == PCF_PLATFORM_IS_32BIT)
	#define  PCF_PLATFORM_BIT_SIZE    PCF_PLATFORM_IS_32BIT
#elif (PCF_CONF_PLATFORM_BIT_SIZE == PCF_PLATFORM_IS_64BIT)
	#define  PCF_PLATFORM_BIT_SIZE    PCF_PLATFORM_IS_64BIT
#else
#error "Platform Bit Size in Unkonwn by System. 	        \
	You must defined PCF_CONF_PLATFORM_BIT_SIZE             \
        as  PCF_PLATFORM_IS_8BIT or PCF_PLATFORM_IS_16BIT or    \
	PCF_PLATFORM_IS_32BIT or PCF_PLATFORM_IS_64BIT."

#endif



/**
Inclusion of this file requires macro PCF_CONF_ARCH in
config.h to be defined as x86. Currently, the detection
of arch is provided for MinGW, MSVC and GCC compilers. In 
case, you have defined the PCF_CONF_ARCH as "x86" and 
you get an error from this file, you need to add proper 
compiler dependent macro for passing following condition 
test.
*/
#if ( PCF_CONF_ARCH == PCF_ARCH_X86)
	#define PCF_ARCH         PCF_ARCH_X86
	#define PCF_ARCH_DEVICE	 PCF_ARCH_X86
#else
//   TODO: Add appropicate error
//	#error ""
#endif



#if (PCF_PLATFORM_BIT_SIZE == PCF_PLATFORM_IS_32BIT)

	#if defined(_X86_) ||   \
	    defined(_M_IX86) || \
	    defined(i386) || defined(__i386) || defined(__i386__)

		#define PCF_ARCH_SIZE          32
		#define PCF_BYTE_ORDER         PCF_ARCH_LITTLE_ENDIAN
		
	#else
	#error "Configured for X86 32Bit architecture but compiler doesn't \
		pass the detection. If you are using a new compiler which isn't \
		supported by PCF, you must add compiler defined arch macro as one \
		of the conditional, in the above condition."
	#endif

#elif (PCF_PLATFORM_BIT_SIZE == PCF_PLATFORM_IS_64BIT)

	#if defined(_M_X64)   || defined(_M_IA64) || \
	    defined(_M_AMD64)  || defined(__amd64__) || defined(__amd64) || \
	    defined(__x86_64__) || defined(__x86_64) || \
	    defined(__ia64__) || defined(_IA64)  || defined(__IA64__)


		#define PCF_ARCH_SIZE           64
		#define PCF_BYTE_ORDER        	PCF_ARCH_LITTLE_ENDIAN
	#else
		#error "Configured for X86 64Bit architecture but compiler doesn't \
		pass the detection. If you are using a new compiler which isn't \
		supported by PCF, you must add compiler defined arch macro as one \
		of the conditional, in the above condition."
	#endif
#else
#error "Configured for PCF_ARCH_X86 with bit size PCF_PLATFORM_BIT_SIZE which \
		is not supportted by the EPCF Framework"
#endif

// undefining the Utilized Macro
#undef  PCF_CONF_PLATFORM_BIT_SIZE
#undef  PCF_CONF_ARCH

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
		1.	PCF_YES										\
		2.	PCF_NO"
	#endif
#endif
#undef EPCF_CONF_USE_UART

//Handle SSE,AVX,MMX over here

#endif //__PCF_INCLUDED_ARCH_X86_H
