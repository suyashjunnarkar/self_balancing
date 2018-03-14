#ifndef __PCF_INCLUDED_DEBUG_GCC_H
#define __PCF_INCLUDED_DEBUG_GCC_H

//*************************************************************************************
// Section : Checking of Configuration Macro
//*************************************************************************************

// checking compiler macro
#if ( ( !defined(PCF_COMPILER_NAME) ) || ( !defined(PCF_COMPILER_TYPE)) )
	#error "Bad code base, don't include this file directly from your code."
#endif

#if (PCF_COMPILER_TYPE != PCF_COMPILER_GCC)
	#error "Bad code base, this file is meant to used with GCC compiler."
#endif

#if !defined(PCF_COMPILER_VERSION)
	#error "Bad code base, PCF_COMPILER_VERSION isn't defined."
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

// 	TODO:ADD The MAcro as per the Following Requirement
//		AKSED Requiement of __PCF_COMPILER_FOUND_DEBUG_MODE Macro
//		#ifdef _DEBUG
//			#define __PCF_COMPILER_FOUND_DEBUG_MODE		PCF_YES
//		#else
//			#define __PCF_COMPILER_FOUND_DEBUG_MODE		PCF_NO
//		#endif
//

// PCF_ENABLE_DEBUG
#if (PCF_CONF_ENABLE_DEBUG == PCF_YES)

	#define PCF_ENABLE_DEBUG    PCF_ENABLE
	
    // Including PCF_LANGAUGE/debug.h file
	#define __PCF_DEBUG_LANGUAGE_INCLUDE 	PCF_CONDITIONAL_INCLUDE_FILE(,PCF_LANGUAGE_NAME/,,debug.h)
	#include __PCF_DEBUG_LANGUAGE_INCLUDE
	#undef __PCF_DEBUG_LANGUAGE_INCLUDE

	// Checking the macro
	#ifdef PCF_DEBUG_MODE

	// Defining all the PCF_DEBUG_MACRO
	#define _PCF_CHECK_FOR_NULL_POINTER(__PTR_TO_CHECK__)							\
			if( !(__PTR_TO_CHECK__) )												\
			   pcfDebugReportError(__PCF_FILE__,__PCF_LINE__,#__PTR_TO_CHECK__);

	#define _PCF_ASSERT(___CONDITION__)          \
			if (!(___CONDITION__)) 				\
				pcfDebugAssert(#___CONDITION__, __PCF_FILE__, __PCF_LINE__, (Cstring_t)0);

	#define _PCF_ASSERT_WITH_MSG(___CONDITION__, __TEXT_MESSAGE__)  \
        		if (!(___CONDITION__)) 			\
					pcfDebugAssert(#___CONDITION__, __PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__);

	#define _PCF_DEBUG()  						\
				pcfDebugDebugger(__PCF_FILE__,__PCF_LINE__,(Cstring_t)0, (uint8_t)0)

	#define _PCF_DEBUG_MSG_TYPE(__TEXT_MESSAGE__,__MSG_TYPE__)    \
            	pcfDebugDebugger(__PCF_FILE__,__PCF_LINE__,__TEXT_MESSAGE__,	\
            			(uint8_t)__MSG_TYPE__)

	#define _PCF_DEBUG_INFO(__TEXT_MESSAGE__)    \
            	pcfDebugDebugger(__PCF_FILE__,__PCF_LINE__,__TEXT_MESSAGE__,	\
            			(uint8_t)PCF_DEBUG_MESSAGE_TYPE_INFO)

	#define _PCF_DEBUG_ERROR(__TEXT_MESSAGE__)   \
            	pcfDebugDebugger(__PCF_FILE__,__PCF_LINE__,__TEXT_MESSAGE__,	\
            			(uint8_t)PCF_DEBUG_MESSAGE_TYPE_ERROR)

	#define _PCF_REPORT_ERROR() 					\
				pcfDebugReportError(__PCF_FILE__,__PCF_LINE__,(Cstring_t)0)

	#define _PCF_REPORT_ERROR_WITH_MSG(__TEXT_MESSAGE__)  			\
        		pcfDebugReportError(__PCF_FILE__,__PCF_LINE__,__TEXT_MESSAGE__)

	#define _PCF_REPORT_ERROR_WITH_MSG_CODE(__TEXT_MESSAGE__, __ERROR_CODE__)				\
				pcfDebugReportErrorErrCode(__PCF_FILE__, __PCF_LINE__, 					\
							__TEXT_MESSAGE__, __ERROR_CODE__)

	#define _PCF_REPORT_UNEXPECTED_ERROR()							\
				pcfDebugReportUnexpectedError(__PCF_FILE__, __PCF_LINE__,(Cstring_t)0)

	#define _PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG(__TEXT_MESSAGE__) 							\
            	pcfDebugReportUnexpectedError(__PCF_FILE__,			\
            				__PCF_LINE__, __TEXT_MESSAGE__)

	#define _PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG_CODE(__TEXT_MESSAGE__, __ERROR_CODE__) 	\
            	pcfDebugReportUnexpectedErrorErrCode(__PCF_FILE__, __PCF_LINE__,		\
            				__TEXT_MESSAGE__, __ERROR_CODE__)

	#define _PCF_REPORT_TO_STDERROR(__TEXT_MESSAGE__)				\
				fprintf(stderr, "pcf:error(%s:%d:%s)", __PCF_FILE__, __PCF_LINE__, __TEXT_MESSAGE__)

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
		#define PCF_ENABLE_RUNTIME_ASSERT	PCF_YES
	#else
		#define PCF_ENABLE_RUNTIME_ASSERT	PCF_NO
	#endif

	#else
		#error "Bad Debug Support, Valid debug macro not defined in your PCF_Langauge/debug.h"
	#endif	// #ifdef PCF_DEBUG_MODE
	#undef PCF_DEBUG_MODE

#elif (PCF_CONF_ENABLE_DEBUG == PCF_NO)
	#define PCF_ENABLE_DEBUG    				PCF_NO
	#define PCF_HAS_DEBUG_BREAK					PCF_NO
	#define PCF_ENABLE_MEMORY_DEBUG				PCF_NO
	#define PCF_ENABLE_RUNTIME_ASSERT			PCF_NO
	#define __PCF_COMPILER_FOUND_DEBUG_MODE		PCF_NO

    #define _PCF_CHECK_FOR_NULL_POINTER(__PTR_TO_CHECK__)
	#define _PCF_ASSERT(___CONDITION__)
	#define _PCF_ASSERT_WITH_MSG(___CONDITION__, __TEXT_MESSAGE__)
	#define _PCF_DEBUG()
	#define _PCF_DEBUG_INFO(__TEXT_MESSAGE__)
	#define _PCF_DEBUG_ERROR(__TEXT_MESSAGE__)
	#define _PCF_REPORT_ERROR()
	#define _PCF_REPORT_ERROR_WITH_MSG(__TEXT_MESSAGE__)
	#define _PCF_REPORT_ERROR_WITH_MSG_CODE(__TEXT_MESSAGE__, __ERROR_CODE__)
	#define _PCF_REPORT_UNEXPECTED_ERROR()
	#define _PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG(__TEXT_MESSAGE__)
	#define _PCF_REPORT_UNEXPECTED_ERROR_WITH_MSG_CODE(__TEXT_MESSAGE__, __ERROR_CODE__)
	#define _PCF_REPORT_TO_STDERROR(__TEXT_MESSAGE__)

#else
	#error "Bad configuration, PCF_CONF_ENABLE_DEBUG must be \
			defined as PCF_YES or PCF_NO."
#endif	//#if (PCF_ENABLE_DEBUG == PCF_YES)

#undef PCF_CONF_ENABLE_DEBUG
#undef PCF_CONF_HAS_DEBUG_BREAK
#undef PCF_CONF_ENABLE_MEMORY_DEBUG
#undef PCF_CONF_ENABLE_RUNTIME_ASSERT
#undef __PCF_COMPILER_FOUND_DEBUG_MODE

#if (PCF_HAS_DEBUG_BREAK == PCF_YES)
	#define PCF_DEBUG_BREAK_IF(__CONDITION__) 		if (__CONDITION__) {__builtin_trap();}
#else
	#define PCF_DEBUG_BREAK_IF(__CONDITION__)
#endif

#if (PCF_ENABLE_MEMORY_DEBUG == PCF_YES)
	//TODO: PCF_ENABLE_MEMORY_DEBUG Feature
	//#pragma message "TO DO: PCF_ENABLE_MEMORY_DEBUG Feature" PCF_STRINGIFY(__PCF_FILE__)
	//#define _CRTDBG_MAP_ALLOC
	//#ifdef _malloca
	//#undef _malloca
	//#endif

	//#include <crtdbg.h>
	//#define __PCF_DEBUG_NEW new(_NORMAL_BLOCK, __PCF_FILE__, __PCF_LINE__)
	//#define new __PCF_DEBUG_NEW
	//Handle the malloc, realloc etc S

#endif

#if (PCF_ENABLE_RUNTIME_ASSERT == PCF_YES)
	//TODO: PCF_ENABLE_RUNTIME_ASSERT Feature
	// Handle PCF_ENABLE_RUNTIME_ASSERT is not Defined in the File
	// and PCF_CONF_ENABLE_RUNTIME_ASSERT is not Handled in this file.
	// #pragma message "TODO: PCF_ENABLE_RUNTIME_ASSERT Feature" PCF_STRINGIFY(__PCF_FILE__)

#endif

#endif // __PCF_INCLUDED_DEBUG_GCC_H
