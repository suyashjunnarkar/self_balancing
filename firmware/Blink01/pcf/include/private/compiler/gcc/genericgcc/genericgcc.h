#ifndef __PCF_INCLUDE_PRIVATE_COMPILER_GCC_GENERICGCC_GENERICGCC_H
#define __PCF_INCLUDE_PRIVATE_COMPILER_GCC_GENERICGCC_GENERICGCC_H

#ifdef PCF_COMPILER_FLAVOUR
#error "PCF_COMPILER_FLAVOUR shall not be defined anywhere else."
#else
	#if (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_GENERIC)
		#define PCF_COMPILER_FLAVOUR  genericgcc
	#else
		#error "Bad inclusion of PCF_CONF_COMPILER_FLAVOUR."
	#endif
#endif

#undef PCF_CONF_COMPILER_FLAVOUR

/* TODO: ADD Macro related to the generic GCC test/specific macro here. */

#endif //__PCF_INCLUDE_PRIVATE_COMPILER_GCC_GENERICGCC_GENERICGCC_H
