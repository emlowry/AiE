/******************************************************************************
 * File:               Macros.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        Macros for managing import/export and inline keywords.
 * Last Modified:      February 4, 2014
 * Last Modification:  Added macro for inlining functions unless compiling for
 *                      the library.
 ******************************************************************************/

// No include guards for this file - always include it again to override macro
// definitions from other libraries.  Just make sure to include this file after
// all other headers.
// #ifndef MACROS__H
// #define MACROS__H

#ifdef COMPILING_MY_FIRST_ENGINE_LIBRARY

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
#endif

#else

#define INLINE inline

#if defined INCLUDING_STATIC_MY_FIRST_ENGINE_LIBRARY
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
#define IMEXPORT
#define IMEXPORT_CLASS
#define IMEXPORT_T_INST
#define EXTERN_T_INST
#endif

#endif

// No include guards for this file - always include it again to override macro
// definitions from other libraries.  Just make sure to include this file after
// all other headers.
// #endif  // MACROS__H
