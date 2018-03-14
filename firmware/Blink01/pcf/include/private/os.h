#ifndef __PCF_INCLUDED_OS_H__
#define __PCF_INCLUDED_OS_H__

#if !defined(PCF_CONF_HAS_OS)
#error "You shall not include this file directly in your code."
#endif

#if !defined (PCF_CONF_OS_TYPE)
#error "How come this is possible! Work only on the RHS of config file."
#endif

#if defined(PCF_OS_NAME)
#error "You shall not define PCF_OS_NAME."
#endif

#if defined(PCF_OS_TYPE)
#error "You shall not define PCF_OS_TYPE."
#endif

// checking PCF_CONF_OS_HAS_FILESYSTEM Debug macro 
#if !defined(PCF_CONF_OS_HAS_FILESYSTEM)
	#error "Bad configuration, you must define PCF_CONF_OS_HAS_FILESYSTEM and \
			set it's value either to PCF_YES or PCF_NO."
#endif

#if (PCF_CONF_OS_HAS_FILESYSTEM != PCF_YES) && (PCF_CONF_OS_HAS_FILESYSTEM != PCF_NO)
	#error "Bad configuration, PCF_CONF_OS_HAS_FILESYSTEM must be \
			defined as PCF_YES or PCF_NO."
#endif

#if defined(PCF_OS_HAS_FILESYSTEM)
	#error "Bad code base, don't define PCF_OS_HAS_FILESYSTEM anywhere else."
#endif

#if (PCF_CONF_HAS_OS == PCF_YES)

	#if  (PCF_CONF_OS_TYPE == PCF_OS_NONE)
		#error "You have configured for OS support but have not defined the OS flavour."
	#elif (PCF_IS_ANY_KNOWN_OS(PCF_CONF_OS_TYPE))

		#if (PCF_CONF_OS_TYPE == PCF_OS_LINUX)
			#define PCF_OS_NAME    	pcf_linux
		#elif (PCF_CONF_OS_TYPE == PCF_OS_UC_LINUX)
			#define PCF_OS_NAME 	pcf_uclinux
		#elif (PCF_CONF_OS_TYPE == PCF_OS_WINDOWS)
			#define PCF_OS_NAME 	pcf_windows
		#elif (PCF_CONF_OS_TYPE == PCF_OS_IOS)
			#define PCF_OS_NAME 	pcf_ios
		#elif (PCF_CONF_OS_TYPE == PCF_OS_ANDROID)
			#define PCF_OS_NAME 	pcf_android
		#elif (PCF_CONF_OS_TYPE == PCF_OS_RT_PHIXOS)
			#define PCF_OS_NAME 	pcf_phixos
		#else
			#error "Bad OS, pcf deosn't know about your os. Above, add one more 'elif' \
						and follow the steps to add support for a new OS for pcf."
		#endif
		
		#if defined (PCF_OS_NAME )

			#define __PCF_OS_DEF_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(os/,PCF_OS_NAME/,,PCF_OS_NAME.h)
			#include __PCF_OS_DEF_INCLUDE
			#undef __PCF_OS_DEF_INCLUDE

			/*Below macro should be defined the the File of OS Included on basis of Configuartion done
			  in the configuration file. */
			#if !defined(PCF_OS_TYPE)
			#error "Included OS doesn't define the required macro PCF_OS_TYPE."
			#endif	//#if !defined(PCF_OS_TYPE)

			#if !defined(PCF_PATH_SEPARATOR_CHAR)
			#error "Included OS doesn't define the required macro PCF_PATH_SEPARATOR_CHAR."
			#endif	//#if !defined(PCF_PATH_SEPARATOR_CHAR)

		#endif	//#if defined (PCF_OS_NAME )

	#else
		#error "You have configured for an OS type which isn't currently supported."
	#endif //#if  (PCF_CONF_OS_TYPE == PCF_OS_NONE)

#elif (PCF_CONF_HAS_OS == PCF_NO)
	#define PCF_OS 	PCF_OS_NONE
	#undef  PCF_CONF_OS_TYPE
	#undef  PCF_CONF_OS_HAS_FILESYSTEM
#else
	#error "You shall not be seeing this error ever! Swear on honesty, you didn't change \
	what was above your access."
	
#endif //#if (PCF_CONF_HAS_OS == PCF_YES)

#undef  PCF_CONF_HAS_OS

#endif //__PCF_INCLUDED_OS_H__
