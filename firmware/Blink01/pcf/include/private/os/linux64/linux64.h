#ifndef __PCF_INCLUDED_OS_LINUX_64_H
#define __PCF_INCLUDED_OS_LINUX_64_H

#if (PCF_CONF_OS_TYPE != PCF_OS_LINUX_64)
#error "Don't include this file, instead include pcf_abstract.h with proper config in place."
#endif

#if defined(PCF_OS_TYPE)
#error "You shall not define PCF_OS_TYPE anywhere else."
#endif

#if !defined(_M_X64)
#warning "This file shall be included for X86 based arch type."
//#error "This file shall be included for X86 based arch type."
#endif

#if defined(linux) && defined(__linux__) &&  defined(__gnu_linux__) && defined (linux)
	#if (PCF_ARCH == PCF_ARCH_X86_64)
		#define PCF_OS_TYPE PCF_OS_LINUX_64
	#else
		#error "PCF_ARCH_X86_64 not define Use proper configuration in your epcf_config.h "
	#endif
#else
	#error "Your compiler doesn't shows this as a Linux64 OS, add the proper compiler based macro \
	to ensure this is being compiled and used on Linux64 operating system."
#endif

//If your compiler can't figure out how to include this,
//don't use this compiler to build pcf for Linux 64 applications.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/termios.h>
#include <fcntl.h>
//#include <ncurses.h>

#if defined(PCF_PATH_SEPARATOR_CHAR)
#error "You shall not define macro PCF_PATH_SEPARATOR_CHAR anywhere else."
#else
#define PCF_PATH_SEPARATOR_CHAR '\\'
#endif

//ToDo::Talk to Zain to handle this part, can we use philib for providing
//threading support.
//#ifndef PCF_HAS_PTHREADS
//#define PCF_HAS_WINTHREADS
//#endif

#endif //__PCF_INCLUDED_OS_LINUX_64_H
