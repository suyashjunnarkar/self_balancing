#ifndef __PCF_INCLUDED_DEBUG_H
#define __PCF_INCLUDED_DEBUG_H

//*************************************************************************************
// Section : Checking of Configuration Macro
//*************************************************************************************

#if !defined(PCF_COMPILER_TYPE)
	#error "Bad code base, compiler.h must be included before debug.h which defines \
			PCF_COMPILER_TYPE."
#endif

#if !(PCF_IS_ANY_KNOWN_COMPILER(PCF_COMPILER_TYPE))
	#error "Bad compiler configuration."
#endif

#if !defined(PCF_COMPILER_NAME)
	#error "Bad code base, compiler.h must be included before debug.h which defines PCF_COMPILER_NAME."
#endif

// Including PCF_COMPILER_NAME.h file
#define  __PCF_DEBUG_LANGUAGE_COMPILER_INCLUDE  PCF_CONDITIONAL_INCLUDE_FILE(debug/,,,PCF_COMPILER_NAME.h)
#include __PCF_DEBUG_LANGUAGE_COMPILER_INCLUDE
#undef   __PCF_DEBUG_LANGUAGE_COMPILER_INCLUDE

// Validiation Macro Checking

#if defined(PCF_CONF_ENABLE_DEBUG)
#error "Bad implementation for debug, PCF_CONF_ENABLE_DEBUG must be undefined."
#endif

#if !defined(PCF_ENABLE_DEBUG)
#error "Bad implementation for debug, PCF_ENABLE_DEBUG must be defined."
#endif

#if defined(PCF_CONF_HAS_DEBUG_BREAK)
#error "Bad implementation for debug, PCF_CONF_HAS_DEBUG_BREAK must be undefined."
#endif

#if !defined(PCF_HAS_DEBUG_BREAK)
#error "Bad implementation for debug, PCF_HAS_DEBUG_BREAK must be defined."
#endif

#if defined(PCF_CONF_ENABLE_MEMORY_DEBUG)
#error "Bad implementation, PCF_CONF_ENABLE_MEMORY_DEBUG must be undefined."
#endif

#if !defined(PCF_ENABLE_MEMORY_DEBUG)
#error "Bad implementation for debug, PCF_ENABLE_MEMORY_DEBUG must be undefined"
#endif

#if defined(PCF_CONF_ENABLE_RUNTIME_ASSERT)
#error "Bad implementation, PCF_CONF_ENABLE_MEMORY_DEBUG must be undefined."
#endif

#if !defined(PCF_ENABLE_RUNTIME_ASSERT)
#error "Bad implementation for debug, PCF_ENABLE_RUNTIME_ASSERT must be undefined"
#endif

#endif //PCF_INCLUDED_DEBUG_H

