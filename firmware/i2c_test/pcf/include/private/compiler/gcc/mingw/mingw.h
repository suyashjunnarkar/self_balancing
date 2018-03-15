#ifndef __PCF_INCLUDED_COMPILER_GCC_MINGW_H
#define __PCF_INCLUDED_COMPILER_GCC_MINGW_H

#ifdef PCF_COMPILER_FLAVOUR
#error "PCF_COMPILER_FLAVOUR shall not be defined anywhere else."
#else
	#if (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_MINGW)
		#define PCF_COMPILER_FLAVOUR  mingw
	#else
		#error "Bad inclusion of PCF_CONF_COMPILER_FLAVOUR."
	#endif
#endif

#undef PCF_CONF_COMPILER_FLAVOUR

// TODO: Version based compiler discrimination still needs to be updated.
// TODO: ADD Macro related to the mingw gcc test/specific macro here.

#endif //__PCF_INCLUDED_COMPILER_GCC_MINGW_H
