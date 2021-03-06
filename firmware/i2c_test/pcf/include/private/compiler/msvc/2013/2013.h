#ifndef __PCF_INCLUDE_PRIVATE_COMPILER_MSVC_2013_H
#define __PCF_INCLUDE_PRIVATE_COMPILER_MSVC_2013_H

#if !defined(_MSC_VER)
#error "Include this file only if you are using microsoft visual studio compiler."
#endif

#if (_MSC_VER != 1800)
#error "This file is only meant for VS2013, include a valid VS compiler \
from config.h"
#endif                         
#ifdef PCF_COMPILER_FLAVOUR
#error "PCF_COMPILER_FLAVOUR shall not be defined anywhere else."
#endif
#define PCF_COMPILER_FLAVOUR  2013

#endif // __PCF_INCLUDE_PRIVATE_COMPILER_MSVC_2013_H
