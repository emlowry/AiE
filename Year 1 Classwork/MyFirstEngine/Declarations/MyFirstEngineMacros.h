/******************************************************************************
 * File:               MyFirstEngineMacros.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        Macros for managing import/export and inline keywords.
 * Last Modified:      February 5, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

// No include guards for this file - always include it again to override macro
// definitions from other libraries.  Just make sure to include this file after
// all other headers.

#undef INLINE
#undef INLINE_IMPLEMENTATION
#undef IMEXPORT
#undef IMEXPORT_CLASS
#undef IMEXPORT_T_INST
#undef EXTERN_T_INST

#if defined COMPILING_MY_FIRST_ENGINE_LIBRARY || \
    defined INCLUDING_INLINE_MY_FIRST_ENGINE_LIBRARY
#define INLINE_IMPLEMENTATION
#endif

#ifdef COMPILING_MY_FIRST_ENGINE_LIBRARY

#define INLINE

#if defined _USRDLL
#define IMEXPORT __declspec( dllexport )
#define IMEXPORT_CLASS __declspec( dllexport )
#define IMEXPORT_T_INST __declspec( dllexport )
#define EXTERN_T_INST
#elif defined _LIB
#define IMEXPORT
#define IMEXPORT_CLASS
#define IMEXPORT_T_INST
#define EXTERN_T_INST
#else
#error Preprocessor must define _DLL or _LIB to compile library
#endif

#else

#define INLINE inline

#if defined INCLUDING_INLINE_MY_FIRST_ENGINE_LIBRARY
#define IMEXPORT
#define IMEXPORT_CLASS
#define IMEXPORT_T_INST
#define EXTERN_T_INST
#elif defined INCLUDING_STATIC_MY_FIRST_ENGINE_LIBRARY
#define IMEXPORT extern
#define IMEXPORT_CLASS
#define IMEXPORT_T_INST
#define EXTERN_T_INST extern
#elif defined INCLUDING_DYNAMIC_MY_FIRST_ENGINE_LIBRARY
#define IMEXPORT __declspec( dllimport )
#define IMEXPORT_CLASS __declspec( dllimport )
#define IMEXPORT_T_INST __declspec( dllimport )
#define EXTERN_T_INST extern
#else
#error Preprocessor must define either \
INCLUDING_STATIC_MY_FIRST_ENGINE_LIBRARY, \
INCLUDING_DYNAMIC_MY_FIRST_ENGINE_LIBRARY, \
or INCLUDING_INLINE_MY_FIRST_ENGINE_LIBRARY
#endif

#endif
