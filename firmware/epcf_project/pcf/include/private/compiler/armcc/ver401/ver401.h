#ifndef __PCF_INCLUDED_COMPILER_ARMCC_VER401_VER401_H
#define __PCF_INCLUDED_COMPILER_ARMCC_VER401_VER401_H

#error "Armcc Real View compiler  ver 401 support not added in the PCF"
// TODO: Add support for the Real view armcc ver Compiler.

#if 0
#ifdef PCF_COMPILER_FLAVOUR
#error "PCF_COMPILER_FLAVOUR shall not be defined anywhere else."
#else
	#if (PCF_CONF_COMPILER_FLAVOUR == PCF_COMPILER_FLAVOUR_ARMCC_VER401)
		#define PCF_COMPILER_FLAVOUR  ver401
	#else
		#error "Bad inclusion of PCF_CONF_COMPILER_FLAVOUR."
	#endif
#endif

#undef PCF_CONF_COMPILER_FLAVOUR

/*ADD Macro related to the arm-none-eabi-gcc specific macro here.*/

#endif

#endif //__PCF_INCLUDED_COMPILER_ARMCC_VER401_VER401_H
