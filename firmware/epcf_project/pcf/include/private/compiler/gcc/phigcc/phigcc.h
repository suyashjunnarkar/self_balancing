#ifndef __PCF_INCLUDE_PRIVATE_COMPILER_GCC_PHIGCC_PHIGCC_H
#define __PCF_INCLUDE_PRIVATE_COMPILER_GCC_PHIGCC_PHIGCC_H

#error "Phi gcc compiler support not added in the PCF"

#ifdef PCF_COMPILER_FLAVOUR
#error "PCF_COMPILER_FLAVOUR shall not be defined anywhere else."
#else
	#if (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_GENERIC)
		#define PCF_COMPILER_FLAVOUR  genericgcc
	#else
		#error "Bad inclusion of PCF_CONF_COMPILER_FLAVOUR."
	#endif
#endif

#endif

// TODO: Version based compiler discrimination still needs to be updated.
// TODO: ADD Macro related to the phi gcc test/specific macro here.

#endif //__PCF_INCLUDE_PRIVATE_COMPILER_GCC_PHIGCC_PHIGCC_H
