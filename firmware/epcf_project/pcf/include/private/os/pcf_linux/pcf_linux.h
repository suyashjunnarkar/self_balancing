#ifndef __PCF_INCLUDED_OS_LINUX32_H
#define __PCF_INCLUDED_OS_LINUX32_H

#if (PCF_CONF_OS_TYPE != PCF_OS_LINUX)
#error "Don't include this file, instead include pcf_abstract.h with proper config in place."
#endif

#if defined(PCF_OS_TYPE)
#error "You shall not define PCF_OS_TYPE anywhere else."
#endif

#if !defined(_M_IX86)
// TODO : Remove the warning and add proper error msg
//#warning "This file shall be included for X86 based arch type."
//#error "This file shall be included for X86 based arch type."
#endif

#if defined(linux) && defined(__linux__) &&  defined(__gnu_linux__)
#if (PCF_ARCH == PCF_ARCH_X86)
	#define PCF_OS_TYPE PCF_OS_LINUX
#else
	#error "PCF_ARCH_X86 not define Use proper configuration in your epcf_config.h "
#endif
#else
	#error "Your compiler doesn't shows this as a Linux OS, add the proper compiler based macro \
	to ensure this is being compiled and used on Linux operating system."
#endif

//If your compiler can't figure out how to include this,
//don't use this compiler to build pcf for win32 applications.

#include <stdio.h>
#include <unistd.h>
//#include <string.h>
//#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <termios.h>
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

#endif //__PCF_INCLUDED_OS_WIN32_H
