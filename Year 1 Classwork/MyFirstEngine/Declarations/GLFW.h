/******************************************************************************
 * File:               GLFW.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Includes the necessary headers and macros for GLFW.
 * Last Modified:      February 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef MY_FIRST_ENGINE__GLFW__H
#define MY_FIRST_ENGINE__GLFW__H

#include "GL\glew.h"

#ifndef GLFW_DLL
#define GLFW_DLL_NOT_ALREADY_DEFINED
#define GLFW_DLL
#endif
#include "GLFW\glfw3.h"
#ifdef GLFW_DLL_NOT_ALREADY_DEFINED
#undef GLFW_DLL
#endif

#endif  // MY_FIRST_ENGINE__GLFW__H
