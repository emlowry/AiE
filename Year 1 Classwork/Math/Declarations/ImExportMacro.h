/******************************************************************************
 * File:               ImExportMacro.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        A macro for adding the correct import/export keyword(s).
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef IM_EXPORT_MACRO__H
#define IM_EXPORT_MACRO__H

#if defined STATIC_MATH__H
#define IMEXPORT extern
#define IMEXPORT_CLASS
#define IMEXPORT_T_INST extern
#elif defined DYNAMIC_MATH__H
#define IMEXPORT __declspec( dllimport )
#define IMEXPORT_CLASS __declspec( dllimport )
#define IMEXPORT_T_INST __declspec( dllimport ) extern
#elif defined COMPILING_DLL
#define IMEXPORT __declspec( dllexport )
#define IMEXPORT_CLASS __declspec( dllexport )
#define IMEXPORT_T_INST __declspec( dllexport )
#else
#define IMEXPORT
#define IMEXPORT_CLASS
#define IMEXPORT_T_INST
#endif

#endif  // IM_EXPORT_MACRO__H
