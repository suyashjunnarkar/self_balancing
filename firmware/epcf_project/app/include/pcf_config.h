/**
 * \file  epcf_config.h
 * \brief This file is used to configure epcf framework in the begining.
 */

#ifndef __EPCF_INCLUDED_EPCF_CONFIG_H
#define __EPCF_INCLUDED_EPCF_CONFIG_H

///Don't change anything if you aren't sure ...
//This file will be automatically generated for you from the config
//ui

#define YOUR_PLATFORM_PATH          /home/majorviraj/Desktop/Self\ balancing/codes/epcf_project

////////////////////// PCF Info configuration starts /////////////////////////

/**Set this to one if you want to export information
about os, arch, compiler etc. within your binary
for more information about the exported functions
macros, see file "private/pcfinfo.h". */
#define PCF_CONF_EXPORT_INFO                     PCF_NO

/**Set this macro to 1 if you want to embed the information
about the os, compiler, version etc as API functions.
Keeping this macro as 0 and setting PCF_EXPORT_INFO as 1,
defines cetain macros, for more information about the
exported macros, see file "private/pcfinfo.h".*/
#define PCF_CONF_EXPORT_INFO_AS_API              PCF_NO

/**If you pcf is being used for development with C++
compiler, setting this macro to 1 will export the
class pcfInfo, with same methods as above. Default is
1 and is only effective when the value of macro
PCF_LANGUAGE is one the valid macros for C++ language.
For more information about available macros see the file
"private/defs/language.h"*/
#define PCF_CONF_EXPORT_INFO_AS_CLASS            PCF_NO

////////////////////// PCF Info configuration ends /////////////////////////
////////////////////// OS configuration starts     /////////////////////////

/**Enable by setting this macro to PCF_YES or PCF_NO to define that app-
lication or library which is being built requires an OS. Enabling this flag,
requires you to define bare minimum requirements from an OS such as tasks,
mutex, locks and file-system. The flag for shared libraries become availble,
iff an OS is present. When PCF_CONF_HAS_OS is set to PCF_NO, means the
development is bare metal, this condition enables a new configuration choice
for memory protection unit. PCF_CONF_ARCH_HAS_MPU*/
#define PCF_CONF_HAS_OS                          PCF_NO

/**Enable by setting the macro's value to one the defined macros
PCF_OS_XXX in file private/pcfdefs.h, by default it is set as
PCF_OS_NONE (no os)*/
#define PCF_CONF_OS_TYPE                         PCF_OS_NONE

/**Enable by setting this macro to PCF_YES or PCF_NO to define that app-
lication or library which is being built requires a file-system from the OS.
Enabling this flag, requires you to define bare minimum requirements of
a file-system.*/
#define PCF_CONF_OS_HAS_FILESYSTEM               PCF_NO

/**Define this to one of the macros from private/defs.h, a valid
value will be PCF_BUILD_TYPE_XXXX. This macro controls the definition
of entry point main, WinMain (and/or) dll export import macro
definitions.*/
//Configuration
#define PCF_CONF_BUILD_TYPE                      PCF_BUILD_TYPE_APPLICATION

//////////////////////  OS configuration starts       /////////////////////////
//////////////////////  Platform configuration starts /////////////////////////

/**Usually, people use platform and architecture interchangably, the reason
for this is simple, that more than often mainstream software development
revolves around servers and desktop, where before the the arrival of 64Bit
X86 processors, by platform mostly people meant operating system, for PCF,
this isn't the case. It is a unified framework for all C/C++ developement at
PhiRobotics Research Pvt. Ltd., so platform in this case will refer to the
underlying core libraries on top of which the client code is developed. For
example, PhiRoS is a platform which clients can use for robotic application,
the requirements for this platform are certain architecture and OS. Similarly,
PhiMotion is a platform which provides clients to develop applications and
libraries for SoCs in bare metal manner or on the desktop side, with it's
own requirements from the SoC's architecture and(or) the OS.*/
/**Define this as combination of macros PCF_PLATFORM_IS_XXXBIT
from private/defs.h*/
#define PCF_CONF_PLATFORM_BIT_SIZE              PCF_PLATFORM_IS_32BIT

/**Enable this flag to remove the floating point use from your
development. All floating type declarations will generate compile time
error. This is usually true for mcus like ATmeag8, LPC1768, etc.*/
#define PCF_CONF_PLATFORM_POISON_FLOATS         PCF_NO

/**Enable this to define the fixed point support. In case there is a
known impplementation for the chosen platform and architecture, it
will be included otherwise you will end up with a compile time error
to add the support for fixed point mathematics on your own.*/
#define PCF_CONF_PLATFORM_HAS_FIXED_POINT       PCF_NO

/**Define this to PCF_YES or PCF_NO, this setting governs the
definition of type real_t, if the following macro is set to PCF_YES,
real_t is typedefed to float, for PCF_NO it is defined as double and
for poisoned float platform it is defined as blank, which will result
in compilation error if a variable is declared using "real_t x".*/
#define PCF_CONF_REAL_NUMBER_IS_FLOAT           PCF_YES

/**If defined to PCF_YES then there must exist a path to platform file
relative to this file. $PathToPlatform/$PlatformName/$PlatformName.h this file will
get automatically included, all platform specific requirements shall be
handled in this file, don't define anything which is compiler, os, arch
specific within the platform file. Update the compiler files accordingly
which will result in version change of PCF itself.*/
#define PCF_CONF_IS_PLATFORM                    PCF_YES

/**Define this to the name of the platform which you are developing or
planning to use. For example, if you are developing a platform you will
name it here for the first time and client code will be able to use
it, subsequently in their own application. All additional includes and
configuration is handled automatically, once this is defined. You can
keep it blank but define PCF_IS_PLATFORM macro as PCF_NO.
*/
#define PCF_CONF_PLATFORM_NAME                  epcf
#define PCF_CONF_PLATFORM_PATH			YOUR_PLATFORM_PATH

//////////////////////  Platform configuration ends  //////////////////////////

//////////////////////  Architecture configuration starts /////////////////////

/**Define this to X86, X86_64, AVR, ARM etc ...*/
#define PCF_CONF_ARCH                           PCF_ARCH_ARM

/**You can keep this as blank in case the architecture you
are developing for doesn't has sub-family. Usually,
for ARM  you will define the following macro PCF_CONF_ARCH_VARIANT
as CM0, CM3, CM4 etc.. are used to include the relevant
header file which handles the architecture specific macros.
Consider your application is built around ARM Cortex-M3, you will
define PCF_CONF_ARCH as "arm" and PCF_CONF_ARCH_VARIANT as "cm3",
this will result in inclusion of a file relative to include folder
with path, "arch/arm/cm3/cm3.h", further handling of the devies and
manufacturer specific information will he handled by this file.
In case, PCF_CONF_ARCH is defined as "x86" and "PCF_CONF_ARCH_VARIANT"
is left blank, it will result in inclusion of a file arch/x86.h
relative to include directory. If an arch requires the definition
of variant and the variant requires a device definition. You must
define the following configuration parameters to their right value.*/
#define PCF_CONF_ARCH_VARIANT                   cm3
/**More than often for embedded system projects,
you need to define this as the vendor of the device, you are
developing for. For example, ATmega128 is manufactured by ATmel, but
avr_8 as srch automatically concludes that. Hence in this case this is
ineffective. Sometimes it will be required, the decision is
taken by the supported architecture, for example in case of ARM
Cortex-M3, you will need to define it as per the supported vendors
LPC, STM32 etc; this will be the same name as the name of directory
in the directory CM0 and cm0.h will demand this macro to be well defined,
or else you will get an error from the corresponding file.*/
#define PCF_CONF_ARCH_DEVICE_VENDOR             nxp
/**When you develop with a valid configuration with a device,
you can check against the definition of macro PCF_INCLUDED_DEVICE_ID,
later in your client code. If the inclusion was successful it's value will be
same as */
#define PCF_CONF_ARCH_DEVICE                    lpc1768
/**Define the macro as per the CPU clock of your board. Expected value is
in Hertzs, which means, you shall define 16MHz as 16000000 and not 16. The
device which is supported by framework will check for the minimum and maximum
value, if the cofigured value is correct, it will result in most appropriate
value of acceptable clock and PCF_ARCH_DEVICE_CLK will get defined which you
can use in your code for generating various values.*/
// clock for the device should be defined
#define PCF_CONF_ARCH_DEVICE_CLK                100000000
/**Defining the above parameters with correct values will result in
definition of following macros with appropriate values. Client code
can check against these values during development.
PCF_ARCH_SIZE, PCF_ARCH_BYTE_ORDER, PCF_ARCH_DEVICE_HAS_FPU,
PCF_ARCH_DEVICE_VENDOR,  PCF_ARCH_VARIANT (as a string),
PCF_ARCH_DEVICE (as a string) and PCF_ARCH_DEVICE_CLK
*/

//////////////////////  Architecture configuration ends   /////////////////////

//////////////////////     Compiler configuration starts  /////////////////////
/**Define the following macro to one of the PCF_COMPILER_XXX, based on this
definition, proper compiler header will be included automatically. For example
if you are building using MSVC 2013, then you shall set PCF_CONF_COMPILER_TYPE
to PCF_COMPILER_MSVC and PCF_CONF_COMPILER_FLAVOUR as 2013. This will result in
inclusion of file private/compiler/msvc/msvc.h which in turn will process the 
flavour type to include private/compiler/msvc/2013/2013.h.
*/
#define PCF_CONF_COMPILER_TYPE                      PCF_COMPILER_GCC
#define PCF_CONF_COMPILER_FLAVOUR                   PCF_COMPILER_FLAVOUR_GCC_ARM
/**Define this macro to 0 or 1, it results in definition of macro
__PCF_DECORATED_FUNCTION__, which is used in debug stubs. Anyways this
macro must be defined, if not supported by the compiler,
then keep it blank.*/
#define PCF_CONF_DEFINES_DECORATED_FUNCTION_NAME    PCF_YES
/**Define this macro to 0 or 1, it results in definition of macro
__PCF_SHORT_FILENAME__, which is used in debbug stubs. Anyways this macro
must be defined, if not supported by the compiler, then keep it blank.*/
#define PCF_CONF_DEFINES_SHORT_FILENAME             PCF_YES


//////////////////////      Compiler configuration ends   /////////////////////

/**Shall be defined as either PCF_YES or PCF_NO.If defined as PCF_YES,
compiler's support is investigated, build system support is investigated 
for various macros which could alter the behavior of binary built for debug
mode or release.
Defining following macro doesn't gurantee that the support for debugging,
assertion etc. will be available or not, you must 
*/
#define PCF_CONF_ENABLE_DEBUG                       PCF_NO

/**If defined as PCF_YES, then it is responsibility of the compiler to
provide a valid macro pcf_debug_break_if(__BOOLEAN_EXPRESSION__), this
is usually available for MSVC, for others need some investigation and 
implementation.
*/
#define PCF_CONF_HAS_DEBUG_BREAK                    PCF_NO
/**If defined as PCF_YES, then it is responsibility of the implementer to
provide proper implementation of "new", malloc, realloc, calloc, free and delete
as per the language C or CPP.*/
#define PCF_CONF_ENABLE_MEMORY_DEBUG                PCF_NO  //

#define PCF_CONF_ENABLE_RUNTIME_ASSERT              PCF_NO

//
// NOTE: PCF_CHAR_IS_UNSIGNED is not handle in any file of pcf_build. ASK_sir
//
#define PCF_CHAR_IS_UNSIGNED                        PCF_NO

#endif //__EPCF_INCLUDED_EPCF_CONFIG_H
