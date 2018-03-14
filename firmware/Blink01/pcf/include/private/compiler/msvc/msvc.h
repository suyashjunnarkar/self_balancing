#ifndef __PCF_INCLUDE_PRIVATE_COMPILER_MSVC_MSVC_H
#define __PCF_INCLUDE_PRIVATE_COMPILER_MSVC_MSVC_H


#if !defined(_MSC_VER)
#error "Include this file only if you are using microsoft visual studio compiler."
#endif

#if defined(PCF_COMPILER_TYPE)
#error "Don't define macro PCF_COMPILER_TYPE anywhere else."
#else
#define PCF_COMPILER_TYPE  PCF_COMPILER_MSVC
#undef  PCF_CONF_COMPILER_TYPE
#endif

#if defined(PCF_COMPILER_VERSION)
#error "Don't define macro PCF_LANGUAGE anywhere else."
#endif

#define PCF_COMPILER_VERSION  _MSC_VER

//In case you are planning to configure MSVC as C compiler
//read this https://msdn.microsoft.com/en-us/library/b0084kay.aspx
//specially how to enable __STDC__ macro 
#ifdef PCF_LANGUAGE
#error "Don't define macro PCF_LANGUAGE anywhere else.'"
#else
	#if defined(__STDC__)
		#if !defined(__STDC_VERSION__) //MSVC doesn't define this, so we will (C99).
		#define __STDC_VERSION__   199901L
		#define PCF_LANGUAGE       PCF_LANGUAGE_C99
		#define PCF_LANGUAGE_NAME  C
		#endif
	#else
		#define PCF_LANGUAGE       PCF_LANGUAGE_CPP
		#define PCF_LANGUAGE_NAME  CPP
	#endif //#if defined(__STDC__)
#endif //#ifdef PCF_LANGUAGE

#if defined(__PCF_FILE__)
#error "You must not define the macro __PCF_FILE__ anywhere else.
#else
#if defined(__FILE__)
#define __PCF_FILE__ __FILE__
#else
#error "Bad compiler, doesn't define __FILE__. Provide this definition your self"
#endif
#endif

#if defined(__PCF_LINE__)
#error "You must not define the macro __PCF_LINE__ anywhere else.
#else
#if defined(__LINE__)
#define __PCF_LINE__ __LINE__
#else
#error "Bad compiler, doesn't define __LINE__. Provide this definition your self"
#endif
#endif

#if defined(__PCF_FUNC__)
#error "You must not define the macro __PCF_FUNC__ anywhere else.
#else
#define __PCF_FUNC__ __FUNCTION__       
#endif



#if defined(PCF_DEFINES_DECORATED_FUNCTION_NAME) && (PCF_DEFINES_DECORATED_FUNCTION_NAME == 1)
#if defined(__PCF_DECORATED_FUNCTION__)
#error "You must not define the macro __PCF_DECORATED_FUNCTION__ anywhere else.
#else
#define __PCF_DECORATED_FUNCTION__ __FUNCSIG__
#endif
#else
#define __PCF_DECORATED_FUNCTION__
#endif


#if defined(PCF_DEFINES_SHORT_FILENAME) && (PCF_DEFINES_SHORT_FILENAME == 1)
#if defined(__PCF_SHORT_FILENAME__)
#error "You must not define the macro __PCF_SHORT_FILENAME__ anywhere else.
#else 
#include<cstring>
#define __PCF_SHORT_FILENAME__ (std::strchr(__PCF_FILE__, PCF_PATH_SEPARATOR_CHAR) ? \
                std::strchr(__PCF_FILE__, PCF_PATH_SEPARATOR_CHAR) + 1 : __PCF_FILE__)
#endif
#else
#define __PCF_SHORT_FILENAME__
#endif

#define PCF_FORCE_INLINE        __forceinline
#define PCF_NO_INLINE           __declspec(noinline)
#define PCF_NO_RETURN           __declspec(noreturn)
#define PCF_INLINE              __inline
#define PCF_DLL_EXPORT_API      __declspec(dllexport)
#define PCF_DLL_IMPORT_API      __declspec(dllimport)
#define PCF_VISIBLE_API  
#define PCF_DEPRECATED          __declspec(deprecated)


#if !defined(PCF_CONF_COMPILER_FLAVOUR)
    #error "Can't use msvc compiler without a valid flavour. Define it in config.h."
#else
    #define PCF_COMPILER_FLAVOUR_INCLUDE    PCF_CONDITIONAL_INCLUDE_FILE(./,PCF_CONF_COMPILER_FLAVOUR/,,PCF_CONF_COMPILER_FLAVOUR.h)
    #include PCF_COMPILER_FLAVOUR_INCLUDE
    #undef PCF_COMPILER_FLAVOUR_INCLUDE
#endif

#endif  //__PCF_INCLUDE_PRIVATE_COMPILER_MSVC_MSVC_H
