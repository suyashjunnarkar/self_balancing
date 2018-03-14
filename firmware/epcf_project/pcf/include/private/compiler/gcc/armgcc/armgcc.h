#ifndef __PCF_INCLUDE_PRIVATE_COMPILER_GCC_ARMGCC_ARMGCC_H
#define __PCF_INCLUDE_PRIVATE_COMPILER_GCC_ARMGCC_ARMGCC_H

// File Belongs to arm-none-eabi-gcc compiler with version 4.8.4

// TODO: Version based compiler discrimination still needs to be updated.

#ifdef PCF_COMPILER_FLAVOUR
#error "PCF_COMPILER_FLAVOUR shall not be defined anywhere else."
#else
	#if (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_GCC_ARM)
		#define PCF_COMPILER_FLAVOUR  armgcc
	#else
		#error "Bad inclusion of PCF_CONF_COMPILER_FLAVOUR."
	#endif
#endif

#undef PCF_CONF_COMPILER_FLAVOUR

#if (PCF_COMPILER_VERSION != 40804)
//#error "This File is only meant for ARMGCC 4.8.4, include a valid ARM GCC \
//4.8.4 Compiler from config.h"
//#undef PCF_COMPILER_VERSION
#endif

/* TODO: ADD Macro related to the armgcc test/specific macro here. */

#endif //__PCF_INCLUDE_PRIVATE_COMPILER_GCC_ARMGCC_ARMGCC_H
