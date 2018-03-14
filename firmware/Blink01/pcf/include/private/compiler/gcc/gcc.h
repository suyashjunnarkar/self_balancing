#ifndef __PCF_INCLUDE_PRIVATE_COMPILER_GCC_GCC_H
#define __PCF_INCLUDE_PRIVATE_COMPILER_GCC_GCC_H

#if !defined(__GNUC__)
	#error "Include this file only if you are using GNU C compiler."
#endif

#if defined(PCF_COMPILER_TYPE)
	#error "Don't define macro PCF_COMPILER_TYPE anywhere else."
#else
		#if (PCF_CONF_COMPILER_TYPE == PCF_COMPILER_GCC)
			#define PCF_COMPILER_TYPE  PCF_COMPILER_GCC
			#undef  PCF_CONF_COMPILER_TYPE
		#endif
#endif

#if defined(PCF_COMPILER_VERSION)
	#error "Don't define macro PCF_LANGUAGE anywhere else."
#endif

#ifdef PCF_LANGUAGE
	#error "Don't define macro PCF_LANGUAGE anywhere else."
#else
	// Defining the Compiler Version No.
	#define PCF_COMPILER_VERSION  (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
	
	#if defined(__STDC__)
		#if !defined(__STDC_VERSION__)
			#define __STDC_VERSION__ 199901L
			#define PCF_LANGUAGE 		PCF_LANGUAGE_C99
			#define PCF_LANGUAGE_NAME 	C
		#else
			//#pragma message "Else __STDC_VERSION__: "
			/* Check for __STD_VERSION__ defined by the different gcc compiler version*/
			#define PCF_LANGUAGE 		PCF_LANGUAGE_C99
			#define PCF_LANGUAGE_NAME 	C
		#endif //#if !defined(__STDC_VERSION__)
	#else
		//#pragma message "Else __STDC__: "
		#define PCF_LANGUAGE  		PCF_LANGUAGE_CPP
		#define PCF_LANGUAGE_NAME	CPP
	#endif //#if defined(__STDC__)

#endif

#if defined(__PCF_FILE__)
	#error "You must not define the macro __PCF_FILE__ anywhere else."
#else
	
	#if defined(__FILE__)
		#define __PCF_FILE__ __FILE__
	#else
		#error "Bad compiler, doesn't define __FILE__. Provide this definition your self."
	#endif // #if defined(__FILE__)
	
#endif //#if defined(__PCF_FILE__)

#if defined(__PCF_LINE__)
	#error "You must not define the macro __PCF_LINE__ anywhere else."
#else
	
	#if defined(__LINE__)
		#define __PCF_LINE__ __LINE__
	#else
		#error "Bad compiler, doesn't define __LINE__. Provide this definition your self."
	#endif //#if defined(__LINE__)
	
#endif //#if defined(__PCF_LINE__)

#if defined(__PCF_FUNC__)
	#error "You must not define the macro __PCF_FUNC__ anywhere else."
#else
//      TODO: Check __func__ gcc macro and update the following Code
//	#if defined (__func__)
//		#define __PCF_FUNC__ __func__
	//#elif defined (__FUNCTION__)
	#if defined (PCF_COMPILER_TYPE)
		#define __PCF_FUNC__ __FUNCTION__
	#else
//		#define __PCF_FUNC__
		#warning "Bad compiler, doesn't define __func__ or __FUNCTION__ . Provide this definition your self."
	#endif //#if defined (__func__)
	
#endif //#if defined(__PCF_FUNC__)

/*
In C, __PRETTY_FUNCTION__ is yet another name for __func__, except that at file
(or, in C++, namespace scope), it evaluates to the string "top level".
In addition, in C++, __PRETTY_FUNCTION__ contains the signature of the function as well as its bare name.
*/

#if defined(PCF_CONF_DEFINES_DECORATED_FUNCTION_NAME) && (PCF_CONF_DEFINES_DECORATED_FUNCTION_NAME == PCF_YES)
	#if defined(__PCF_DECORATED_FUNCTION__)
		#error "You must not define the macro __PCF_DECORATED_FUNCTION__ anywhere else."
	#else
//      TODO: Check __PRETTY_FUNCTION__ gcc macro and update the
//		#if defined (__PRETTY_FUNCTION__)
		#if defined (PCF_COMPILER_TYPE)
			#define __PCF_DECORATED_FUNCTION__  __PRETTY_FUNCTION__
		#else
			#define __PCF_DECORATED_FUNCTION__
		#endif // #if defined (__PRETTY_FUNCTION__)
	#endif // #if defined(__PCF_DECORATED_FUNCTION__)
#else
	#define __PCF_DECORATED_FUNCTION__
#endif //#if defined(PCF_CONF_DEFINES_DECORATED_FUNCTION_NAME) && (PCF_CONF_DEFINES_DECORATED_FUNCTION_NAME == PCF_YES)

#undef PCF_CONF_DEFINES_DECORATED_FUNCTION_NAME

#if defined(PCF_CONF_DEFINES_SHORT_FILENAME) && (PCF_CONF_DEFINES_SHORT_FILENAME == PCF_YES)
	#if defined(__PCF_SHORT_FILENAME__)
		#error "You must not define the macro __PCF_SHORT_FILENAME__ anywhere else."
	#else
		
		#include <string.h>
		#define __PCF_SHORT_FILENAME__ (strchr(__PCF_FILE__, PCF_PATH_SEPARATOR_CHAR) ? \
																			strchr(__PCF_FILE__, PCF_PATH_SEPARATOR_CHAR) + 1 : __PCF_FILE__)
		
	#endif //#if defined(__PCF_SHORT_FILENAME__)
#else
	#define __PCF_SHORT_FILENAME__
#endif //#if defined(PCF_CONF_DEFINES_SHORT_FILENAME) && (PCF_CONF_DEFINES_SHORT_FILENAME == PCF_YES)

#undef PCF_CONF_DEFINES_SHORT_FILENAME
#define PCF_FASTCALL 					//__fastcall
#define PCF_FORCE_INLINE                __attribute__((always_inline))
#define PCF_NO_INLINE                   __attribute__((noinline))
#define PCF_NO_RETURN                   __attribute__((__noreturn__))
#define PCF_ASM                         __asm
#define PCF_INLINE                      inline
#define PCF_C_PACKED                    __attribute__((packed))
#define PCF_C_UNUSED_ARG                __attribute__((__unused__))
/*
TODO:  Macro Should be tested before Adding to the PCF_BUILD
#define PCF_FORMAT(type,fmt,first)      __attribute__((__format__(type, fmt, first)))
#define PCF_C_UNUSED_ARG(type,arg)      __attribute__((__unused__)) type arg
#define PCF_C_LIKELY(x)                 __builtin_expect(!!(x), 1)
#define PCF_C_UNLIKELY(x)               __builtin_expect(!!(x), 0)
#define PCF_C_TYPEOF_OR_PGENERIC(type)  typeof(type)
*/

#define PCF_DLL_IMPORT_API              __attribute__((dllimport))
#define PCF_DLL_EXPORT_API              __attribute__((dllexport))
#define PCF_DEPRECATED                  __attribute__((deprecated))
#define PCF_VISIBLE_API

#if !defined(PCF_CONF_COMPILER_FLAVOUR)
	#error "Can't use GCC compiler without a valid flavour. Define it in config.h."
#else

#if (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_ARM)
#define PCF_COMPILER_FLAVOUR_NAME armgcc
#elif (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_AVR)
#define PCF_COMPILER_FLAVOUR_NAME avrgcc
#elif (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_CYGWIN)
#define PCF_COMPILER_FLAVOUR_NAME cygwin
#elif (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_MINGW)
#define PCF_COMPILER_FLAVOUR_NAME mingw
#elif (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_PHIGCC)
#define PCF_COMPILER_FLAVOUR_NAME phigcc
#elif (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_GENERIC)
#define PCF_COMPILER_FLAVOUR_NAME genericgcc
#else
#error "Unknown compiler type, defined correct compiler type in config.h"
#endif
	
#define PCF_COMPILER_FLAVOUR_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(./,PCF_COMPILER_FLAVOUR_NAME/,,PCF_COMPILER_FLAVOUR_NAME.h)
#include PCF_COMPILER_FLAVOUR_INCLUDE
#undef PCF_COMPILER_FLAVOUR_INCLUDE

#endif // #if !defined(PCF_CONF_COMPILER_FLAVOUR)

#if !defined(PCF_COMPILER_FLAVOUR)
	#error "Included compiler doesn't define the required macro PCF_COMPILER_FLAVOUR."
#endif // #if !defined(PCF_COMPILER_FLAVOUR)

#if !defined(PCF_COMPILER_VERSION)
	#error "Included compiler doesn't define the required macro PCF_COMPILER_VERSION."
#endif // #if !defined(PCF_COMPILER_VERSION)

#endif  //__PCF_INCLUDE_PRIVATE_COMPILER_GCC_GCC_H
