#ifndef PCF_INCLUDED_DEBUG_C_ARMCC_H
#define PCF_INCLUDED_DEBUG_C_ARMCC_H

#if !defined(PCF_CONF_ENABLE_DEBUG)
#error "Bad configuration, PCF_CONF_ENABLE_DEBUG macro must be defined."
#endif

#if !defined(PCF_COMPILER_NAME) || !defined(PCF_COMPILER_TYPE)
#error "Bad code base, don't include this file directly from your code."
#endif

#if (PCF_COMPILER_TYPE != PCF_COMPILER_ARMCC)
#error "Bad code base, this file is meant to used with MSVC compiler."
#endif

#if !defined(PCF_COMPILER_VERSION)
#error "Bad code base, PCF_COMPILER_VERSION isn't defined."
#endif

//#if (PCF_COMPILER_VERSION != 40804)
//#error "Bad code base, this file is meant to used with Arm_gcc ver 4.8.4 compiler."
//#endif

#if !defined(PCF_CONF_ENABLE_DEBUG)
#error "Bad configuration, you must define PCF_CONF_ENABLE_DEBUG and \
set it's value either to PCF_YES or PCF_NO."
#endif

#if (PCF_CONF_ENABLE_DEBUG == PCF_YES)
	#if defined(_DEBUG) && (_DEBUG == 1)
	#define PCF_ENABLE_DEBUG PCF_YES
	#else
	#define PCF_ENABLE_DEBUG PCF_NO
	#endif
#elif (PCF_CONF_ENABLE_DEBUG == PCF_NO)
	#define PCF_ENABLE_DEBUG PCF_NO
#else
	#error "Bad configuration, PCF_CONF_ENABLE_DEBUG must be \
			defined as PCF_YES or PCF_NO."
#endif

#undef PCF_CONF_ENABLE_DEBUG

#define __PCF_COMPILER_FOUND_DEBUG_MODE
#if (PCF_ENABLE_DEBUG == PCF_YES)
    #if(PCF_CONF_HAS_DEBUG_BREAK == PCF_YES)
      #define PCF_HAS_DEBUG_BREAK PCF_YES
      #define pcf_debug_break_if(__CONDITION__) if (__CONDITION__) {__builtin_trap();}
    #endif

    #if(PCF_CONF_ENABLE_MEMORY_DEBUG == PCF_YES)
      #define _CRTDBG_MAP_ALLOC
      #ifdef _malloca
        #undef _malloca
      #endif

      //#include <crtdbg.h>
      #define __PCF_DEBUG_NEW new(_NORMAL_BLOCK, __PCF_FILE__, __PCF_LINE__)
      #define new __PCF_DEBUG_NEW
      //Handle the malloc, realloc etc S
      #define PCF_ENABLE_MEMORY_DEBUG PCF_YES
    #endif
#else
  #define PCF_HAS_DEBUG_BREAK PCF_NO
  #define PCF_ENABLE_MEMORY_DEBUG PCF_NO
  #define pcf_debug_break_if(__CONDITION__)
#endif

//Handle PCF_ENABLE_RUNTIME_ASSERT is not Defined in the File
// and PCF_CONF_ENABLE_RUNTIME_ASSERT is not Handled in this file.

#undef PCF_CONF_HAS_DEBUG_BREAK
#undef PCF_CONF_ENABLE_MEMORY_DEBUG
#undef PCF_CONF_ENABLE_RUNTIME_ASSERT

#endif // PCF_INCLUDED_DEBUG_C_GCC_H
