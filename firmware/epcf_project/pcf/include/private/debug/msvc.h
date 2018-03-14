#ifndef __PCF_INCLUDED_DEBUG_MSVC_H
#define __PCF_INCLUDED_DEBUG_MSVC_H

//*************************************************************************************
// Section : Checking of Configuration Macro
//*************************************************************************************

// checking compiler macro
#if ( ( !defined(PCF_COMPILER_NAME) ) || ( !defined(PCF_COMPILER_TYPE)) )
	#error "Bad code base, don't include this file directly from your code."
#endif

#if (PCF_COMPILER_TYPE != PCF_COMPILER_MSVC)
	#error "Bad code base, this file is meant to used with MSVC compiler."
#endif

#if !defined(PCF_COMPILER_VERSION)
	#error "Bad code base, PCF_COMPILER_VERSION isn't defined."
#endif

// TO DO: check the following macro testing is needed or not
#if (PCF_COMPILER_VERSION != _MSC_VER)
#error "Bad code base, this file is meant to used with MSVC compiler."
#endif

// checking Langauge macro
#if !defined(PCF_LANGUAGE)
	#error "Bad code base, Required macro PCF_LANGUAGE must be defined by compiler.h."
#endif

#if !defined(PCF_LANGUAGE_NAME)
	#error "Bad code base, PCF_LANGUAGE_NAME must be defined after the inclusion of compiler.h."
#endif

// checking Debug macro
#if !defined(PCF_CONF_ENABLE_DEBUG)
	#error "Bad configuration, you must define PCF_CONF_ENABLE_DEBUG and \
			set it's value either to PCF_YES or PCF_NO."
#endif

#if (PCF_CONF_ENABLE_DEBUG != PCF_YES) && (PCF_CONF_ENABLE_DEBUG != PCF_NO)
	#error "Bad configuration, PCF_CONF_ENABLE_DEBUG must be \
			defined as PCF_YES or PCF_NO."
#endif

#if defined(PCF_ENABLE_DEBUG)
	#error "Bad code base, don't define PCF_ENABLE_DEBUG anywhere else."
#endif

#if !defined(PCF_CONF_HAS_DEBUG_BREAK)
	#error "Bad configuration, you must define PCF_CONF_HAS_DEBUG_BREAK and \
			set it's value either to PCF_YES or PCF_NO."
#endif

#if (PCF_CONF_HAS_DEBUG_BREAK != PCF_YES) && (PCF_CONF_HAS_DEBUG_BREAK != PCF_NO)
	#error "Bad configuration, PCF_CONF_HAS_DEBUG_BREAK must be \
			defined as PCF_YES or PCF_NO."
#endif

#if defined(PCF_HAS_DEBUG_BREAK)
	#error "Bad code base, don't define PCF_HAS_DEBUG_BREAK anywhere else."
#endif

#if !defined(PCF_CONF_ENABLE_MEMORY_DEBUG)
	#error "Bad implementation for debug, PCF_CONF_ENABLE_MEMORY_DEBUG must be defined."
#endif

#if (PCF_CONF_ENABLE_MEMORY_DEBUG != PCF_YES) && (PCF_CONF_ENABLE_MEMORY_DEBUG != PCF_NO)
	#error "Bad configuration, PCF_CONF_ENABLE_MEMORY_DEBUG must be \
			defined as PCF_YES or PCF_NO."
#endif

#if defined(PCF_ENABLE_MEMORY_DEBUG)
	#error "Bad implementation for debug, PCF_ENABLE_MEMORY_DEBUG must not be defined."
#endif

#if !defined(PCF_CONF_ENABLE_RUNTIME_ASSERT)
	#error "Bad configurtion, PCF_CONF_ENABLE_RUNTIME_ASSERT must be defined."
#endif

#if (PCF_CONF_ENABLE_RUNTIME_ASSERT != PCF_YES) && (PCF_CONF_ENABLE_RUNTIME_ASSERT != PCF_NO)
	#error "Bad configuration, PCF_CONF_ENABLE_RUNTIME_ASSERT must be \
			defined as PCF_YES or PCF_NO."
#endif

#if defined(PCF_ENABLE_RUNTIME_ASSERT)
	#error "Bad code base, PCF_ENABLE_RUNTIME_ASSERT must not be defined anywhere else."
#endif

#if defined (__PCF_COMPILER_FOUND_DEBUG_MODE)
	#error "Bad configuration, __PCF_COMPILER_FOUND_DEBUG_MODE shall not be \
			defined anywhere else."
#endif

//*************************************************************************************
// Section : Setting Parameter based on Configuration Macro
//*************************************************************************************

// PCF_ENABLE_DEBUG
#if (PCF_CONF_ENABLE_DEBUG == PCF_YES)

	#define PCF_ENABLE_DEBUG    PCF_YES
	//#define __PCF_COMPILER_FOUND_DEBUG_MODE		PCF_YES
	// Including PCF_LANGAUGE/debug.h file
	#define __PCF_DEBUG_LANGUAGE_INCLUDE 	PCF_CONDITIONAL_INCLUDE_FILE(,PCF_LANGUAGE_NAME/,,debug.h)
	#include __PCF_DEBUG_LANGUAGE_INCLUDE
	#undef __PCF_DEBUG_LANGUAGE_COMPILER_INCLUDE

	// Checking the macro
	#ifndef PCF_DEBUG_MODE
		#error "Bad Debug Support, Valid debug macro not defined in your PCF_Langauge/debug.h"
	#endif
	#undef PCF_DEBUG_MODE

	// Defining all the PCF_DEBUG_MACRO
	#define PCF_DEBUG()     					pcf_DebugSupport_debugger(__PCF_FILE__, __PCF_LINE__)
	#define PCF_DEBUG_INFO(__TEXT_MESSAGE__)    \
            pcf_DebugSupport_debuggerMsg(__PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__, (uint8_t)1)

	#define PCF_DEBUG_ERROR(__TEXT_MESSAGE__)   \
            pcf_DebugSupport_debuggerMsg(__PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__, (uint8_t)2)

	#define PCF_REPORT_ERROR() 					pcf_DebugSupport_reportError(__PCF_FILE__, __PCF_LINE__)
	#define PCF_REPORT_ERROR_WITH_MSG(__TEXT_MESSAGE__)  				\
        	pcf_DebugSupport_reportErrorMsg(__PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__)

	#define PCF_REPORT_UNEXPECTED_ERROR()		pcf_DebugSupport_reportUnexpectedError(__PCF_FILE__, __PCF_LINE__)
	#define PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG(__TEXT_MESSAGE__) 		\
            pcf_DebugSupport_reportUnexpectedErrorMsg(__PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__)

	#define PCF_REPORT_TO_STDERROR(__TEXT_MESSAGE__)	\
			fprintf(stderr, "pcf:error(%s:%d:%s)", __PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__)

	#define PCF_ASSERT(___CONDITION__)          \
        		if (!(___CONDITION__)) 			\
					pcf_DebugSupport_assert(#___CONDITION__, __PCF_FILE__, __PCF_LINE__, (Cstring_t)0);	\
				else (void) 0

	#define PCF_ASSERT_WITH_MSG(___CONDITION__, __TEXT_MESSAGE__)  \
        		if (!(___CONDITION__)) 			\
					pcf_DebugSupport_assert(#___CONDITION__, __PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__);	\
             	 else (void) 0

	#define PCF_CHECK_FOR_NULL_POINTER(__PTR_TO_CHECK__)	\
        		if (!(__PTR_TO_CHECK__)) 					\
					pcf_DebugSupport_checkForNullPointer(#__PTR_TO_CHECK__, __PCF_FILE__, __PCF_LINE__); 	\
				else (void) 0

	#if(PCF_CONF_HAS_DEBUG_BREAK == PCF_YES)
		#define PCF_HAS_DEBUG_BREAK		PCF_YES
	#else
		#define PCF_HAS_DEBUG_BREAK		PCF_NO
	#endif

	#if(PCF_CONF_ENABLE_MEMORY_DEBUG == PCF_YES)
		#define PCF_ENABLE_MEMORY_DEBUG		PCF_YES
	#else
		#define PCF_ENABLE_MEMORY_DEBUG		PCF_NO
	#endif

	#if(PCF_CONF_ENABLE_RUNTIME_ASSERT == PCF_YES)
		#define PCF_ENABLE_RUNTIME_ASSERT		PCF_YES
	#else
		#define PCF_ENABLE_RUNTIME_ASSERT		PCF_NO
	#endif

#elif (PCF_CONF_ENABLE_DEBUG == PCF_NO)
	#define PCF_ENABLE_DEBUG    		PCF_NO
	#define PCF_HAS_DEBUG_BREAK			PCF_NO
	#define PCF_ENABLE_MEMORY_DEBUG		PCF_NO

	// TODO: ASK Requiement of __PCF_COMPILER_FOUND_DEBUG_MODE Macro
    //#define __PCF_COMPILER_FOUND_DEBUG_MODE		PCF_NO
    #define PCF_DEBUG()
	#define PCF_DEBUG_INFO(__TEXT_MESSAGE__)
	#define PCF_DEBUG_ERROR(__TEXT_MESSAGE__)
	#define PCF_REPORT_ERROR()
	#define PCF_REPORT_ERROR_WITH_MSG(__TEXT_MESSAGE__)
	#define PCF_REPORT_UNEXPECTED_ERROR()
	#define PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG(__TEXT_MESSAGE__)
	#define PCF_REPORT_TO_STDERROR(__TEXT_MESSAGE__)
	#define PCF_ASSERT(___CONDITION__)
	#define PCF_ASSERT_WITH_MSG(___CONDITION__, __TEXT_MESSAGE__)
	#define PCF_CHECK_FOR_NULL_POINTER(__PTR_TO_CHECK__)

#else
	#error "Bad configuration, PCF_CONF_ENABLE_DEBUG must be \
			defined as PCF_YES or PCF_NO."
#endif	//#if (PCF_ENABLE_DEBUG == PCF_YES)

#undef PCF_COMF_ENABLE_DEBUG
#undef PCF_CONF_HAS_DEBUG_BREAK
#undef PCF_CONF_ENABLE_MEMORY_DEBUG
#undef PCF_CONF_ENABLE_RUNTIME_ASSERT

#if (PCF_HAS_DEBUG_BREAK == PCF_YES)
	#define PCF_DEBUG_BREAK_IF(__CONDITION__) if (__CONDITION__) {__debugbreak();}
#else
	#define PCF_DEBUG_BREAK_IF(__CONDITION__)
#endif

#if (PCF_ENABLE_MEMORY_DEBUG == PCF_YES)

	#define _CRTDBG_MAP_ALLOC
	#ifdef _malloca
		#undef _malloca
	#endif

	#include <crtdbg.h>
	#define __PCF_DEBUG_NEW new(_NORMAL_BLOCK, __PCF_FILE__, __PCF_LINE__)
	#define new __PCF_DEBUG_NEW
	//Handle the malloc, realloc etc S

#endif

#if (PCF_ENABLE_RUNTIME_ASSERT == PCF_YES)

// Handle PCF_ENABLE_RUNTIME_ASSERT is not Defined in the File
// and PCF_CONF_ENABLE_RUNTIME_ASSERT is not Handled in this file.
// #pragma message "TO DO: PCF_ENABLE_RUNTIME_ASSERT Feature" PCF_STRINGIFY(__PCF_FILE__)

#endif


#endif  //__PCF_INCLUDED_DEBUG_MSVC_H
