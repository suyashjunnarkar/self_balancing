
#ifndef __PCF_INCLUDE_PRIVATE_DEFS_H
#define __PCF_INCLUDE_PRIVATE_DEFS_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
Macros which start with "__" and doesn't end with "__" are not meant 
to be used in your code.
*/
#define PCF_UNKNOWN      -1
#define PCF_NONE         -1
#define PCF_GENERIC       1

#define PCF_YES           1
#define PCF_ENABLE        PCF_YES
#define PCF_HAS           PCF_YES

#define PCF_NO            0
#define PCF_DISABLE       PCF_NO
#define PCF_HAS_NOT       PCF_NO

#define PCF_NULL		  ((void*)0)		// NULL Pointer
#define PCF_NUL			  '\0'				// NULL  Char
#define PCF_ARCH_BIG_ENDIAN     1                             
#define PCF_ARCH_LITTLE_ENDIAN  2

#define PCF_DECLARE_VERSION(major, minor, build) (((major) << 16) + ((minor) << 8) + (build))

#define PCF_CHAR_BIT_WIDTH                     8
#define PCF_COMPILE_TIME_ASSERT(expression)    switch(0){case 0:case expression:;}
#define PCF_ASSERT_MIN_BITSIZE(type, size)     PCF_COMPILE_TIME_ASSERT(sizeof(type) * PCF_CHAR_BIT_WIDTH >= size)
#define PCF_ASSERT_EXACT_BITSIZE(type, size)   PCF_COMPILE_TIME_ASSERT(sizeof(type) * PCF_CHAR_BIT_WIDTH == size)
#define PCF_ALLOW_UNUSED_LOCAL(x)              false ? (void)x : (void)0

#define PCF_CONCATE(A,B)					   A##B
#define PCF_IDENT(X) 						   X
#define PCF_STRINGIFY(X)                       PCF_DIRECT_STRINGIFY(X)
#define PCF_DIRECT_STRINGIFY(X)                #X
#define __PCF_USERS_DONT_USE_JOIN_4(W,X,Y,Z)   PCF_STRINGIFY(PCF_IDENT(W)PCF_IDENT(X)PCF_IDENT(Y)PCF_IDENT(Z))
#define PCF_JOIN_W_X_Y_Z(W,X,Y,Z)              __PCF_USERS_DONT_USE_JOIN_4(W,X,Y,Z)

#define PCF_CONDITIONAL_INCLUDE_FILE(PATH, PACKAGE, MODULE, INCLUDE_NAME) \
        	PCF_JOIN_W_X_Y_Z(PATH, PACKAGE, MODULE, INCLUDE_NAME)


//Declares that the platform is 8bit (ATmega128 etc..)
#define PCF_PLATFORM_IS_8BIT                (1)
//Declares that the platform is 16bit (MSP430 etc..)
#define PCF_PLATFORM_IS_16BIT               (PCF_PLATFORM_IS_8BIT << 1)
//Declares that the platform is 32bit (X86, ARM etc..)
#define PCF_PLATFORM_IS_32BIT               (PCF_PLATFORM_IS_16BIT << 1)
//Declares that the platform is 64bit (X64)
#define PCF_PLATFORM_IS_64BIT               (PCF_PLATFORM_IS_32BIT << 1)

#define PCF_ALL_PLATFORMS                   (PCF_PLATFORM_IS_8BIT  | \
                                             PCF_PLATFORM_IS_16BIT | \
                                             PCF_PLATFORM_IS_32BIT | \
                                             PCF_PLATFORM_IS_64BIT)

#define PCF_IS_VALID_PLATFORM(x)     ((x & PCF_ALL_PLATFORMS) != 0)

//Beast with no nonsense
#define PCF_LANGUAGE_C           (1)
#define PCF_LANGUAGE_C99         (PCF_LANGUAGE_C)
#define PCF_LANGUAGE_C11         (PCF_LANGUAGE_C99 << 1)
#define PCF_LANGUAGE_E_C         (PCF_LANGUAGE_C11 << 1)

#define PCF_LANGUAGE_ANY_C       (PCF_LANGUAGE_C99 | \
                                  PCF_LANGUAGE_C11 | PCF_LANGUAGE_E_C)

#define PCF_LANGUAGE_CPP         (PCF_LANGUAGE_E_C << 1)
#define PCF_LANGUAGE_CPP98       (PCF_LANGUAGE_CPP)
#define PCF_LANGUAGE_CPP11       (PCF_LANGUAGE_CPP98 << 1)
#define PCF_LANGUAGE_CPP14       (PCF_LANGUAGE_CPP11 << 1)
#define PCF_LANGUAGE_E_CPP       (PCF_LANGUAGE_CPP14 << 1)
#define PCF_LANGUAGE_CPP_CLI     (PCF_LANGUAGE_E_CPP << 1)

#define PCF_LANGUAGE_ANY_CPP     (PCF_LANGUAGE_CPP98 | PCF_LANGUAGE_CPP11 | \
                                  PCF_LANGUAGE_CPP14 | PCF_LANGUAGE_E_CPP | \
                                  PCF_LANGUAGE_CPP_CLI) 

#define PCF_LANGUAGE_ANY         ( PCF_LANGUAGE_ANY_C | PCF_LANGUAGE_ANY_CPP )

/*
// TODO: After Updation remove this comment.
// Macro defined by Pranay Sir.
#define PCF_COMPILER_MINGW              (1)
#define PCF_COMPILER_CYGWIN             (PCF_COMPILER_MINGW << 1)
#define PCF_COMPILER_MSVC               (PCF_COMPILER_CYGWIN << 1)
#define PCF_COMPILER_GCC                (PCF_COMPILER_MSVC << 1)
#define PCF_COMPILER_GCC_AVR8           (PCF_COMPILER_GCC << 1)
#define PCF_COMPILER_GCC_AVR32          (PCF_COMPILER_GCC_AVR8 << 1)
#define PCF_COMPILER_PHIGCC_ARM         (PCF_COMPILER_GCC_AVR32 << 1)
#define PCF_COMPILER_GENERIC_GCC_ARM    (PCF_COMPILER_PHIGCC_ARM << 1)
                               
#define PCF_COMPILER_ANY                (PCF_COMPILER_MINGW |  PCF_COMPILER_CYGWIN | \
                                         PCF_COMPILER_MSVC  |  PCF_COMPILER_GCC | \
                                         PCF_COMPILER_GCC_AVR8 | PCF_COMPILER_GCC_AVR32 | \
                                         PCF_COMPILER_GENERIC_GCC_ARM | PCF_COMPILER_PHIGCC_ARM)

#define PCF_IS_ANY_KNOWN_COMPILER(x)     ((x & PCF_COMPILER_ANY) != 0)
*/
// COMPILER
#define PCF_COMPILER_GCC                (1)
#define PCF_COMPILER_MSVC               (PCF_COMPILER_GCC << 1)
#define PCF_COMPILER_ARMCC              (PCF_COMPILER_MSVC << 1)
                               
#define PCF_COMPILER_ANY                (PCF_COMPILER_GCC |  PCF_COMPILER_MSVC | PCF_COMPILER_ARMCC )                           
#define PCF_IS_ANY_KNOWN_COMPILER(x)    ((x & PCF_COMPILER_ANY) != 0)

// GCC COMPILER FLAVOUR
#define PCF_COMPILER_FLAVOUR_GCC_ARM        (1)
#define PCF_COMPILER_FLAVOUR_GCC_AVR        (PCF_COMPILER_FLAVOUR_GCC_ARM << 1)
#define PCF_COMPILER_FLAVOUR_GCC_CYGWIN     (PCF_COMPILER_FLAVOUR_GCC_AVR << 1)
#define PCF_COMPILER_FLAVOUR_GCC_MINGW      (PCF_COMPILER_FLAVOUR_GCC_CYGWIN << 1)
#define PCF_COMPILER_FLAVOUR_GCC_PHIGCC     (PCF_COMPILER_FLAVOUR_GCC_MINGW << 1)
#define PCF_COMPILER_FLAVOUR_GCC_GENERIC    (PCF_COMPILER_FLAVOUR_GCC_PHIGCC << 1)

#define PCF_COMPILER_FLAVOUR_GCC_ANY        (PCF_COMPILER_FLAVOUR_GCC_ARM    | PCF_COMPILER_FLAVOUR_GCC_AVR     | \
					     PCF_COMPILER_FLAVOUR_GCC_CYGWIN | PCF_COMPILER_FLAVOUR_GCC_MINGW   | \
					     PCF_COMPILER_FLAVOUR_GCC_PHIGCC | PCF_COMPILER_FLAVOUR_GCC_GENERIC )

#define PCF_IS_ANY_KNOWN_COMPILER_FLAVOUR_GCC(x)      ((x & PCF_COMPILER_FLAVOUR_GCC_ANY) != 0)


// MSVC COMPILER FLAVOUR
#define PCF_COMPILER_FLAVOUR_MSVC_2010      (1)
#define PCF_COMPILER_FLAVOUR_MSVC_2013      (PCF_COMPILER_FLAVOUR_MSVC_2010 << 1)
#define PCF_COMPILER_FLAVOUR_MSVC_2015      (PCF_COMPILER_FLAVOUR_MSVC_2013 << 1)

#define PCF_COMPILER_FLAVOUR_MSVC_ANY        (PCF_COMPILER_FLAVOUR_MSVC_2010 |  PCF_COMPILER_FLAVOUR_MSVC_2013 | \
					      PCF_COMPILER_FLAVOUR_MSVC_2015)

#define PCF_IS_ANY_KNOWN_COMPILER_FLAVOUR_MSVC(x)     ((x & PCF_COMPILER_FLAVOUR_MSVC_ANY) != 0)

// ARM COMPILER FLAVOUR
#define PCF_COMPILER_FLAVOUR_ARMCC_VER401	(1)

// OS
#define PCF_OS_NONE                 (0)
#define PCF_OS_LINUX                (1)
#define PCF_OS_ULINUX               (PCF_OS_LINUX << 1)
#define PCF_OS_WINDOWS              (PCF_OS_ULINUX << 1)
#define PCF_OS_IOS                  (PCF_OS_WINDOWS << 1)
#define PCF_OS_ANDROID              (PCF_OS_IOS << 1)
#define PCF_OS_RT_PHIXOS            (PCF_OS_ANDROID << 1)

#define PCF_OS_ANY                  (PCF_OS_LINUX  | PCF_OS_WINDOWS  |  PCF_OS_IOS  | 	\
                                     PCF_OS_ANDROID   | PCF_OS_RT_PHIXOS )

#define PCF_IS_ANY_KNOWN_OS(x)      ((x & PCF_OS_ANY) != 0)

// APPLICATION TYPE
#define PCF_BUILD_TYPE_NONE         1
#define PCF_BUILD_TYPE_SHARED_LIB   1
#define PCF_BUILD_TYPE_STATIC_LIB   2
#define PCF_BUILD_TYPE_APPLICATION  3

// ARCHITECHTURE
// ARCH MACRO should be used in the PCF_CONF_ARCH in your config file
#define PCF_ARCH_ARM              (1)
#define PCF_ARCH_AVR              (PCF_ARCH_ARM << 1)
#define PCF_ARCH_X86              (PCF_ARCH_AVR << 1)

#define PCF_ARCH_ANY              (PCF_ARCH_ARM | PCF_ARCH_AVR | \
				      	  	  	  PCF_ARCH_X86)

#define PCF_IS_ANY_KNOWN_ARCH(x) 	 ((x & PCF_ARCH_ANY) != 0)

// ARM ARCH VARIANT MACRO should be used in the PCF_CONF_ARCH_VARIANT in your config file.
#define PCF_ARCH_ARM_VARIANT_CA5     (1)
#define PCF_ARCH_ARM_VARIANT_CM0     (PCF_ARCH_ARM_VARIANT_CA5 << 1)
#define PCF_ARCH_ARM_VARIANT_CM3     (PCF_ARCH_ARM_VARIANT_CM0 << 1)
#define PCF_ARCH_ARM_VARIANT_CM4     (PCF_ARCH_ARM_VARIANT_CM3 << 1)

#define PCF_ARCH_ARM_VARIANT_ANY     (PCF_ARCH_ARM_VARIANT_CA5 | PCF_ARCH_ARM_VARIANT_CM0 | \
                                     PCF_ARCH_ARM_VARIANT_CM3 | PCF_ARCH_ARM_VARIANT_CM4)
                             
#define PCF_IS_ANY_KNOWN_ARCH_ARM_VARIANT(x)     ((x & PCF_ARCH_ARM_VARIANT_ANY) != 0)


// AVR ARCH VARIANT MACRO should be used in the PCF_CONF_ARCH_VARIANT in your config file.
// x86 ARCH VARIANT MACRO should be used in the PCF_CONF_ARCH_VARIANT in your config file.
// x86_64 ARCH VARIANT MACRO should be used in the PCF_CONF_ARCH_VARIANT in your config file.

//
#define PCF_LANGUAGE_MINIMAL_C       PCF_LANGUAGE_C99
#define PCF_LANGUAGE_MINIMAL_CPP     PCF_LANGUAGE_CPP98

#ifdef	__cplusplus
}
#endif


#endif //__PCF_INCLUDE_PRIVATE_DEFS_H
