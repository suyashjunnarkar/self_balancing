#ifndef __PCF_INCLUDED_ARMCC_H
#define __PCF_INCLUDED_ARMCC_H

#error "Armcc Real View compiler support not added in the PCF"
// TODO: Add support for the Real view armcc Compiler.


#if 0

#if !defined(__CC_ARM)
	#error "Include this file only if you are using ARMCC compiler."
#endif

#if defined(PCF_COMPILER_TYPE)
	#error "Don't define macro PCF_COMPILER_TYPE anywhere else."
#else
		#if (PCF_CONF_COMPILER_TYPE == PCF_COMPILER_ARMCC)
			#define PCF_COMPILER_TYPE  PCF_COMPILER_ARMCC
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
	#define PCF_COMPILER_VERSION  (__ARMCC_VERSION)
	
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
		#define __PCF_FILE__    __FILE__
	#else
		#error "Bad compiler, doesn't define __FILE__. Provide this definition your self."
	#endif // #if defined(__FILE__)
	
#endif //#if defined(__PCF_FILE__)

#if defined(__PCF_LINE__)
	#error "You must not define the macro __PCF_LINE__ anywhere else."
#else
	
	#if defined(__LINE__)
		#define __PCF_LINE__    __LINE__
	#else
		#error "Bad compiler, doesn't define __LINE__. Provide this definition your self."
	#endif //#if defined(__LINE__)
	
#endif //#if defined(__PCF_LINE__)

#if defined(__PCF_FUNC__)
	#error "You must not define the macro __PCF_FUNC__ anywhere else."
#else
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
//		#if defined (__PRETTY_FUNCTION__)
		#if defined (PCF_COMPILER_TYPE)
			#define __PCF_DECORATED_FUNCTION__ __PRETTY_FUNCTION__
		#else
//			#define __PCF_DECORATED_FUNCTION__
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

#define PCF_FORCE_INLINE                __attribute__((always_inline))
#define PCF_NO_INLINE                   __declspec(noinline)
#define PCF_NO_RETURN                   __declspec(noreturn)
#define PCF_ASM                         __asm
#define PCF_INLINE                      __inline
#define PCF_C_PACKED                    __attribute__((packed))

#define PCF_DLL_IMPORT_API              __declspec(dllimport)
#define PCF_DLL_EXPORT_API              __declspec(dllexport)
#define PCF_DEPRECATED                  __attribute__((deprecated))
#define PCF_VISIBLE_API

#pragma anon_unions


#if !defined(PCF_CONF_COMPILER_FLAVOUR)
	#error "Can't use GCC compiler without a valid flavour. Define it in config.h."
#else

#if (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_ARMCC_VER401)
#define PCF_COMPILER_FLAVOUR_NAME ver401
#else
#error "Unknown compiler type, defined correct compiler type in config.h"
#endif
	
#define _PCF_COMPILER_FLAVOUR_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(./,PCF_COMPILER_FLAVOUR_NAME/,,PCF_COMPILER_FLAVOUR_NAME.h)
#include _PCF_COMPILER_FLAVOUR_INCLUDE
#undef __PCF_COMPILER_FLAVOUR_INCLUDE

#endif // #if !defined(PCF_CONF_COMPILER_FLAVOUR)


#if !defined(PCF_COMPILER_FLAVOUR)
	#error "Included compiler doesn't define the required macro PCF_COMPILER_FLAVOUR."
#endif // #if !defined(PCF_COMPILER_FLAVOUR)

#endif //0

#endif  //__PCF_INCLUDED_GCC_H
