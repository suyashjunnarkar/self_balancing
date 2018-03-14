#ifndef __PCF_INCLUDE_PRIVATE_COMPILER_GCC_CYGWIN_CYGWIN_H
#define __PCF_INCLUDE_PRIVATE_COMPILER_GCC_CYGWIN_CYGWIN_H

#error "Cygwin gcc compiler support not added in the PCF"

// TODO: Version based compiler discrimination still needs to be updated.
// TODO: ADD SUPPORT for cygwin gcc Compiler

/*
#ifdef PCF_COMPILER_FLAVOUR
#error "PCF_COMPILER_FLAVOUR shall not be defined anywhere else."
#else
	#if (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_CYGWIN)
		#define PCF_COMPILER_FLAVOUR  cygwin
	#else
		#error "Bad inclusion of PCF_CONF_COMPILER_FLAVOUR."
	#endif
#endif
*/

/* TODO: ADD Macro related to the cygwin GCC test/specific macro here. */

#endif //__PCF_INCLUDE_PRIVATE_COMPILER_GCC_CYGWIN_CYGWIN_H
