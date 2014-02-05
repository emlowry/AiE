/******************************************************************************
 * File:               ImExportMacro.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        A macro for adding the correct import/export keyword(s).
 * Last Modified:      February 4, 2014
 * Last Modification:  Added macro for inlining functions unless compiling for
 *                      the library.
 ******************************************************************************/

#ifndef IM_EXPORT_MACRO__H
#define IM_EXPORT_MACRO__H

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
#elif defined STATIC_MATH__H
#define IMEXPORT extern
#define IMEXPORT_CLASS
#define IMEXPORT_T_INST
#define EXTERN_T_INST extern
#elif defined DYNAMIC_MATH__H
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

#ifdef MATH_LIBRARY_SUPPRESS_INLINE
#define INLINE
#else
#define INLINE inline
#endif

#endif  // IM_EXPORT_MACRO__H
