/******************************************************************************
 * File:               MyFirstEngineMacros.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        Macros for managing import/export and inline keywords.
 * Last Modified:      February 10, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

// No include guards for this file - always include it again to override macro
// definitions from other libraries.  Just make sure to include this file after
// all other headers.

#undef IMEXPORT
#undef IMEXPORT_CLASS
#undef DLL_EXPORT
#undef DLL_IMPORT

#ifdef MYFIRSTENGINE_EXPORTS

#if defined _USRDLL
#define IMEXPORT __declspec( dllexport )
#define IMEXPORT_CLASS __declspec( dllexport )
#define DLL_EXPORT __declspec( dllexport )
#define DLL_IMPORT
#elif defined _LIB
#define IMEXPORT
#define IMEXPORT_CLASS
#define DLL_EXPORT
#define DLL_IMPORT
#else
#error Preprocessor must define _USRDLL or _LIB to compile library
#endif

#else

#if defined INCLUDING_STATIC_MY_FIRST_ENGINE_LIBRARY
#define IMEXPORT extern
#define IMEXPORT_CLASS
#define DLL_EXPORT
#define DLL_IMPORT
#elif defined INCLUDING_DYNAMIC_MY_FIRST_ENGINE_LIBRARY
#define IMEXPORT __declspec( dllimport )
#define IMEXPORT_CLASS __declspec( dllimport )
#define DLL_EXPORT
#define DLL_IMPORT __declspec( dllimport )
#else
#error Preprocessor must define either \
INCLUDING_STATIC_MY_FIRST_ENGINE_LIBRARY or \
INCLUDING_DYNAMIC_MY_FIRST_ENGINE_LIBRARY
#endif

#endif
