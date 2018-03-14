#ifndef __PCF_INCLUDE_PRIVATE_COMPILER_H
#define __PCF_INCLUDE_PRIVATE_COMPILER_H

#include <stdlib.h>
#include <limits.h>

/* Following checks will never fail, but who knows?*/
#if defined(CHAR_BIT)
#if (CHAR_BIT != 8)
#error "Bad C/C++ compiler, CHAR_BIT isn't defined as 8.'"        
#endif
#else
#error "Bad C/C++ compiler, doesn't define CHAR_BIT macro.'"
#endif

#include <stdbool.h>

#if !defined(__bool_true_false_are_defined) 
#error "Bad C/C++ compiler, doesn't define macro \
            __bool_true_false_are_defined"
#endif

#if (__bool_true_false_are_defined != 1) 
#error "Bad C/C++ compiler, doesn't define macro \
            __bool_true_false_are_defined as 1."
#endif

//C++ compiler's compatibility with C compilers
#if !defined(__cplusplus) || !defined(__STDC_LIMIT_MACROS)
#define __STDC_LIMIT_MACROS
#endif
//C++ compiler's compatibility with C compilers
#if !defined(__cplusplus) || !defined(__STDC_CONSTANT_MACROS)
#define __STDC_CONSTANT_MACROS
#endif

#include <stdint.h>

#if (!defined(INT8_MIN)  || !defined(INT8_MAX)   ||  \
     !defined(INT16_MIN) || !defined(INT16_MAX)  ||  \
     !defined(INT32_MIN) || !defined(INT32_MAX)  ||  \
     !defined(INT64_MIN) || !defined(INT64_MAX)  ||  \
     !defined(UINT8_MAX)   ||  \
     !defined(UINT16_MAX)  ||  \
     !defined(UINT32_MAX)  ||  \
     !defined(UINT64_MAX)  ||  \
     !defined(INT_LEAST8_MIN)   || !defined(INT_LEAST8_MAX)   ||  \
     !defined(INT_LEAST16_MIN)  || !defined(INT_LEAST16_MAX)  ||  \
     !defined(INT_LEAST32_MIN)  || !defined(INT_LEAST32_MAX)  ||  \
     !defined(INT_LEAST64_MIN)  || !defined(INT_LEAST64_MAX)  ||  \
     !defined(UINT_LEAST8_MAX)  ||  \
     !defined(UINT_LEAST16_MAX) ||  \
     !defined(UINT_LEAST32_MAX) ||  \
     !defined(UINT_LEAST64_MAX) ||  \
     !defined(INT_FAST8_MIN)   || !defined(INT_FAST8_MAX)   ||  \
     !defined(INT_FAST16_MIN)  || !defined(INT_FAST16_MAX)  ||  \
     !defined(INT_FAST32_MIN)  || !defined(INT_FAST32_MAX)  ||  \
     !defined(INT_FAST64_MIN)  || !defined(INT_FAST64_MAX)  ||  \
     !defined(UINT_FAST8_MAX)  ||  \
     !defined(UINT_FAST16_MAX) ||  \
     !defined(UINT_FAST32_MAX) ||  \
     !defined(UINT_FAST64_MAX))
    #error "Bad C/C++ compiler, one of the required macros is(are) missing."
#endif 

#if (!defined(INTPTR_MIN)  || !defined(INTPTR_MAX)   ||  \
     !defined(UINTPTR_MAX) || !defined(PTRDIFF_MIN)  ||  \
     !defined(PTRDIFF_MAX) || !defined(SIZE_MAX)) 
     
    #error "Bad C/C++ compiler, one of the required macros is(are) missing."
#endif 

#ifdef	__cplusplus
extern "C" {
#endif

    typedef int8_t        Int8_t;
    typedef int16_t       Int16_t;
    typedef int32_t       Int32_t;
    typedef int64_t       Int64_t;
    typedef uint8_t       Uint8_t;
    typedef uint16_t      Uint16_t;
    typedef uint32_t      Uint32_t;
    typedef uint64_t      Uint64_t;

    typedef int_least8_t    LeastInt8_t;
    typedef int_least16_t   LeastInt16_t;
    typedef int_least32_t   LeastInt32_t;
    typedef int_least64_t   LeastInt64_t;
    typedef uint_least8_t   LeastUint8_t;
    typedef uint_least16_t  LeastUint16_t;
    typedef uint_least32_t  LeastUint32_t;
    typedef uint_least64_t  LeastUint64_t;

    typedef int_fast8_t    FastInt8_t;
    typedef int_fast16_t   FastInt16_t;
    typedef int_fast32_t   FastInt32_t;
    typedef int_fast64_t   FastInt64_t;
    typedef uint_fast8_t   FastUint8_t;
    typedef uint_fast16_t  FastUint16_t;
    typedef uint_fast32_t  FastUint32_t;
    typedef uint_fast64_t  FastUint64_t;

    typedef unsigned char Uchar_t;
    typedef signed char   Char_t;
    typedef const char*   Cstring_t;

#if  !defined(PCF_CONF_PLATFORM_POISON_FLOATS)
#error "PCF_CONF_PLATFORM_POISON_FLOATS must be defined as PCF_YES or PCF_NO."
#endif

#if (PCF_CONF_PLATFORM_POISON_FLOATS == PCF_YES) 
  #define real_t 
  #define Real_t 
  
#elif (PCF_CONF_PLATFORM_POISON_FLOATS == PCF_NO)
  #if !defined(PCF_CONF_REAL_NUMBER_IS_FLOAT)
    #error "PCF_CONF_PLATFORM_POISON_FLOATS must be defined as PCF_YES or PCF_NO."
  #endif

  #if (PCF_CONF_REAL_NUMBER_IS_FLOAT == PCF_YES)
      typedef float real_t;
      typedef real_t Real_t;
  #elif (PCF_CONF_REAL_NUMBER_IS_FLOAT == PCF_NO)
      typedef double real_t;
      typedef real_t Real_t;
  #else
    #error "PCF_CONF_REAL_NUMBER_IS_FLOAT must be defined as PCF_YES or PCF_NO."
  #endif
  
#else
  #error "PCF_CONF_PLATFORM_POISON_FLOATS must be PCF_YES or PCF_NO."
#endif

// Undefining the Utillized Macro's.
#undef PCF_CONF_PLATFORM_POISON_FLOATS
#undef PCF_CONF_REAL_NUMBER_IS_FLOAT


#ifndef PCF_CONF_COMPILER_TYPE
#error "PCF_CONF_COMPILER_TYPE must be defined in config.h"
#endif

#if !PCF_IS_ANY_KNOWN_COMPILER(PCF_CONF_COMPILER_TYPE) 
#error "Unknown compiler has been used, add support for this compiler and define it \
in defs.h, this error will be seen usually by PhiRobotics' internal developers."
#endif

#if defined(PCF_COMPILER_TYPE)
#error "Don't define macro PCF_COMPILER_TYPE anywhere else."
#endif

#if defined(PCF_COMPILER_NAME)
#error "Don't define macro PCF_COMPILER_NAME anywhere else."
#endif

#include <stddef.h>

#if (PCF_CONF_COMPILER_TYPE == PCF_COMPILER_GCC)
#define PCF_COMPILER_NAME gcc
#elif (PCF_CONF_COMPILER_TYPE == PCF_COMPILER_ARMCC)
#define PCF_COMPILER_NAME armcc
#elif (PCF_CONF_COMPILER_TYPE == PCF_COMPILER_MSVC)
#define PCF_COMPILER_NAME msvc
#else
#error "Unknown compiler type, defined correct compiler type in config.h"
#endif

#define PCF_COMPILER_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(compiler/,PCF_COMPILER_NAME/,,PCF_COMPILER_NAME.h)
#include PCF_COMPILER_INCLUDE
#undef PCF_COMPILER_INCLUDE

#if !defined(PCF_COMPILER_TYPE)
#error "PCF_COMPILER_TYPE must be defined. This error is because of bad implementation of \
		PhiRobotics' developer or someone who has added new compiler support."
#endif

#if !defined(PCF_COMPILER_VERSION)
#error "PCF_COMPILER_VERSION must be defined. This error is because of bad implementation of \
		PhiRobotics' developer or someone who has added new compiler support."
#endif

#if !defined(PCF_COMPILER_FLAVOUR)
#error "PCF_COMPILER_FLAVOUR must be defined. This error is because of bad implementation of \
PhiRobotics' developer or someone who has added new compiler support."
#endif

#if !defined(PCF_FORCE_INLINE)
#error "PCF_FORCE_INLINE must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(PCF_NO_INLINE)
#error "PCF_NO_INLINE must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(PCF_NO_RETURN)
#error "PCF_NO_RETURN must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(PCF_INLINE)
#error "PCF_INLINE must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(__PCF_FUNC__)
#error "__PCF_FUNC__ must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(__PCF_LINE__)
#error "__PCF_LINE__ must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(__PCF_FILE__)
#error "__PCF_FILE__ must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(__PCF_DECORATED_FUNCTION__)
#error "__PCF_DECORATED_FUNCTION__ must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(__PCF_SHORT_FILENAME__)
#error "__PCF_SHORT_FILENAME__ must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(PCF_DLL_EXPORT_API)
#error "PCF_DLL_EXPORT_API must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(PCF_DLL_IMPORT_API)
#error "PCF_DLL_IMPORT_API must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(PCF_VISIBLE_API)
#error "PCF_VISIBLE_API must be defined for your compiler and it's \
active flavour."
#endif

#if !defined(PCF_DEPRECATED)
#error "PCF_DEPRECATED must be defined for your compiler and it's \
active flavour."
#endif

//TODO: Add more commonly used macros over here.
//TODO: Discuss with Zain, he had some issues with this. I have tried resolving it.
//We are building the PCF itself, no need to check the user configuration.
//When the user will use this library, PCF_IS_BUILDING macro will get undefined
//control will fall to the next block, where we will honor the user's choice. 
#ifdef PCF_IS_BUILDING

  #if (PCF_CONF_BUILD_TYPE == PCF_BUILD_TYPE_SHARED_LIB)
    #define PCF_API  PCF_DLL_EXPORT_API
  #else
    #define PCF_API
  #endif

#else //PCF is being used, honor the user's choice

  #if (PCF_CONF_BUILD_TYPE == PCF_BUILD_TYPE_SHARED_LIB)
    #define PCF_API  PCF_DLL_EXPORT_API
  #elif (PCF_CONF_BUILD_TYPE == PCF_BUILD_TYPE_STATIC_LIB)
    #define PCF_API
  #elif (PCF_CONF_BUILD_TYPE == PCF_BUILD_TYPE_APPLICATION)
    //#define PCF_API  PCF_DLL_IMPORT_API
	#define PCF_API
  #else
    #error "Unknown build type configuration. Check the value of macro \
            PCF_CONF_BUILD_TYPE in config.h"
  #endif

#endif // PCF_IS_BUILDING

// Undefining the Utillized Macro's.
#undef PCF_CONF_BUILD_TYPE

#ifdef	__cplusplus
}
#endif


#endif //__PCF_INCLUDE_PRIVATE_COMPILER_H
