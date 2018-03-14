#ifndef __PCF_INCLUDED_OS_WIN32_H
#define __PCF_INCLUDED_OS_WIN32_H

#if (PCF_CONF_OS_TYPE != PCF_OS_WINDOWS)
#error "Don't include this file, instead include pcf_abstract.h with proper config in place."
#endif

#if defined(PCF_OS_TYPE)
#error "You shall not define PCF_OS_TYPE anywhere else."
#endif

#if !defined(_M_IX86)
#warning "This file shall be included for X86 based arch type."
//#error "This file shall be included for X86 based arch type."
#endif

//WIN32, _WIN32, __WIN32, __WIN32__
#if defined(_WIN32) && !defined(_WIN64)
#define PCF_OS_TYPE PCF_OS_WIN32
#else
#error "Your compiler doesn't shows this as a Win32 OS, add the proper compiler based macro \
to ensure this is being compiled and used on Win32 operating system."
#endif

//If your compiler can't figure out how to include this,
//don't use this compiler to build pcf for win32 applications.
#include <windows.h>
#include <commdlg.h>		//required by uart driver for PC
// TODO: Specifiy the location of stdio file to be included after discussion.


#if defined(PCF_PATH_SEPARATOR_CHAR)
#error "You shall not define macro PCF_PATH_SEPARATOR_CHAR anywhere else."
#else
#define PCF_PATH_SEPARATOR_CHAR '\\'
#endif

#if (PCF_CONF_OS_HAS_FILESYSTEM == PCF_YES)
    #define PCF_OS_HAS_FILESYSTEM    PCF_YES
	#include <stdio.h>
    #undef PCF_CONF_OS_HAS_FILESYSTEM
#else
	// TODO: Add Error for File System
	#warning "PCF_CONF_OS_HAS_FILESYSTEM is defined as PCF_NO for Windows OS, \
			  so you will not be able to use File System API For Example stdio.h"
#endif

//ToDo::Talk to Zain to handle this part, can we use philib for providing
//threading support.
#ifndef PCF_HAS_PTHREADS
#define PCF_HAS_WINTHREADS
#endif

#endif //__PCF_INCLUDED_OS_WIN32_H
