/******************************************************************************
 * File:               ImExportMacro.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        A macro for adding the correct import/export keyword(s).
 * Last Modified:      February 5, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#if defined COMPILING_MATH_LIBRARY || defined INCLUDING_INLINE_MATH_LIBRARY
#define INLINE_IMPLEMENTATION
#else
#undef INLINE_IMPLEMENTATION
#endif

#ifdef COMPILING_MATH_LIBRARY

#define INLINE

#if defined _DLL
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

#if defined INCLUDING_INLINE_MATH_LIBRARY
#define IMEXPORT
#define IMEXPORT_CLASS
#define IMEXPORT_T_INST
#define EXTERN_T_INST
#elif defined INCLUDING_STATIC_MATH_LIBRARY
#define IMEXPORT extern
#define IMEXPORT_CLASS
#define IMEXPORT_T_INST
#define EXTERN_T_INST extern
#elif defined INCLUDING_DYNAMIC_MATH_LIBRARY
#define IMEXPORT __declspec( dllimport )
#define IMEXPORT_CLASS __declspec( dllimport )
#define IMEXPORT_T_INST __declspec( dllimport )
#define EXTERN_T_INST extern
#else
#error Preprocessor must define either INCLUDING_STATIC_MATH_LIBRARY, \
INCLUDING_DYNAMIC_MATH_LIBRARY, ir INCLUDING_INLINE_MATH_LIBRARY
#endif

#endif
