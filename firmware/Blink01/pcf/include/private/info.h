#ifndef PCF_INCLUDED_PCFINFO_H
#define PCF_INCLUDED_PCFINFO_H


// TODO: Info.h needs to be update properly.

#define PCF_VERSION_MAJOR    0001
#define PCF_VERSION_MINOR    0000
#define PCF_VERSION_BUILD    0000
#define PCF_VERSION          PCF_VERSION_MAJOR + PCF_VERSION_MINOR + PCF_VERSION_BUILD

//////// Checking PCF_CONF_EXPORT_INFO MACRO start//////////////////////////
#if !defined(PCF_CONF_EXPORT_INFO)
  #error "Bad configuration, you must define PCF_CONF_EXPORT_INFO and \
  set it's value either to PCF_YES or PCF_NO."
#endif

#if (PCF_CONF_EXPORT_INFO != PCF_YES) && (PCF_CONF_EXPORT_INFO != PCF_NO)
  #error "Bad configuration, PCF_CONF_EXPORT_INFO must be defined as PCF_YES or PCF_NO."
#endif

#if defined(PCF_EXPORT_INFO)
  #error "Bad code base, don't define PCF_EXPORT_INFO anywhere else."
#endif
//////// Checking PCF_CONF_EXPORT_INFO MACRO end//////////////////////////
//////// Checking PCF_CONF_EXPORT_INFO_AS_API MACRO start//////////////////////////
#if !defined(PCF_CONF_EXPORT_INFO_AS_API)
  #error "Bad configuration, you must define PCF_CONF_EXPORT_INFO_AS_API and \
  set it's value either to PCF_YES or PCF_NO."
#endif

#if (PCF_CONF_EXPORT_INFO_AS_API != PCF_YES) && (PCF_CONF_EXPORT_INFO_AS_API != PCF_NO)
  #error "Bad configuration, PCF_CONF_EXPORT_INFO_AS_API must be defined as PCF_YES or PCF_NO."
#endif

#if defined(PCF_EXPORT_INFO_AS_API)
  #error "Bad code base, don't define PCF_EXPORT_INFO anywhere else."
#endif
//////// Checking PCF_CONF_EXPORT_INFO_AS_API MACRO end//////////////////////////
//////// Checking PCF_CONF_EXPORT_INFO_AS_CLASS MACRO start//////////////////////////
#if !defined(PCF_CONF_EXPORT_INFO_AS_CLASS)
  #error "Bad configuration, you must define PCF_CONF_EXPORT_INFO_AS_CLASS and \
  set it's value either to PCF_YES or PCF_NO."
#endif

#if (PCF_CONF_EXPORT_INFO_AS_CLASS != PCF_YES) && (PCF_CONF_EXPORT_INFO_AS_CLASS != PCF_NO)
  #error "Bad configuration, PCF_CONF_EXPORT_INFO_AS_CLASS must be defined as PCF_YES or PCF_NO."
#endif

#if defined(PCF_EXPORT_INFO_AS_CLASS)
  #error "Bad code base, don't define PCF_CONF_EXPORT_INFO_AS_CLASS anywhere else."
#endif
//////// Checking PCF_CONF_EXPORT_INFO_AS_CLASS MACRO end//////////////////////////

#if defined(PCF_CONF_EXPORT_INFO)
  #if (PCF_CONF_EXPORT_INFO == PCF_YES)
   #define PCF_EXPORT_INFO  PCF_YES
  #endif //#if (PCF_CONF_EXPORT_INFO == PCF_YES)
#endif  //#if defined(PCF_CONF_EXPORT_INFO)

#if defined(PCF_CONF_EXPORT_INFO_AS_API)
  #if (PCF_CONF_EXPORT_INFO_AS_API == PCF_YES)
   #define PCF_EXPORT_INFO_AS_API  PCF_YES
  #endif //#if (PCF_CONF_EXPORT_INFO_AS_API == PCF_YES)
#endif  //#if defined(PCF_CONF_EXPORT_INFO_AS_API)

#if defined(PCF_CONF_EXPORT_INFO_AS_CLASS)
  #if (PCF_CONF_EXPORT_INFO_AS_CLASS == PCF_YES)
   #define PCF_EXPORT_INFO_AS_CLASS  PCF_YES
  #endif //#if (PCF_CONF_EXPORT_INFO_AS_CLASS == PCF_YES)
#endif  //#if defined(PCF_CONF_EXPORT_INFO_AS_CLASS)

#if defined(PCF_EXPORT_INFO)
  #if (PCF_EXPORT_INFO != PCF_NO)
/*
      //Exports same id and name as PCF_ARCH
      extern "C" const char* pcfArch();
      extern "C" int pcfArchID();

      //Exports same id and name as PCF_OS
      extern "C" const char* pcfOs();
      extern "C" int pcfOsId();

      //Exports same id and name as PCF_VERSION
      extern "C" const char* pcfVersion();
      extern "C" int pcfVersionId();

      //Exports same id and name as PCF_COMPILER
      extern "C" const char* pcfCompiler();
      extern "C" int pcfCompilerId();

      //Exports same id and name as PCF_LANGUAGE
      extern "C" const char* pcfLanguage();
      extern "C" int pcfLanguageId();

      //Exports same id and name as PCF_BUILD
      extern "C" const char* pcfBuild();
      extern "C" int pcfBuildId();
*/
  #endif  //#if (PCF_EXPORT_INFO != PCF_NO)
#endif  //#if defined(PCF_EXPORT_INFO)

// Below given macro are not handled they must.
//#define PCF_CONF_EXPORT_INFO_AS_API
#if defined(PCF_EXPORT_INFO_AS_API)
  #if (PCF_EXPORT_INFO_AS_API != PCF_NO)

  #endif  //#if (PCF_EXPORT_INFO != PCF_NO)
#endif  //#if defined(PCF_EXPORT_INFO)

//#define PCF_CONF_EXPORT_INFO_AS_CLASS
#if defined(PCF_EXPORT_INFO_AS_CLASS)
  #if (PCF_EXPORT_INFO_AS_CLASS != PCF_NO)

  #endif  //#if (PCF_EXPORT_INFO_AS_CLASS != PCF_NO)
#endif  //#if defined(PCF_EXPORT_INFO_AS_CLASS)

#undef PCF_CONF_EXPORT_INFO
#undef PCF_CONF_EXPORT_INFO_AS_API
#undef PCF_CONF_EXPORT_INFO_AS_CLASS

#endif // PCF_INCLUDED_PCFINFO_H
