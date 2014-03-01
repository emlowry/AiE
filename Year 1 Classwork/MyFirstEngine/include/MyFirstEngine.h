/******************************************************************************
 * File:               MyFirstEngine.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        All-inclusive header file for the MyFirstEngine library.
 * Last Modified:      February 25, 2014
 * Last Modification:  Adding includes for recently-implemented classes.
 ******************************************************************************/

#ifndef MY_FIRST_ENGINE__H
#define MY_FIRST_ENGINE__H

#if !(defined INCLUDING_STATIC_MY_FIRST_ENGINE_LIBRARY) && \
    !(defined INCLUDING_INLINE_MY_FIRST_ENGINE_LIBRARY)
#define INCLUDING_DYNAMIC_MY_FIRST_ENGINE_LIBRARY
#endif

#include "..\Declarations\Drawable.h"
#include "..\Declarations\GameEngine.h"
#include "..\Declarations\GameState.h"
#include "..\Declarations\GameWindow.h"
#include "..\Declarations\Quad.h"
#include "..\Declarations\Shader.h"
#include "..\Declarations\ShaderProgram.h"
//TODO include declaration headers

#endif  // MY_FIRST_ENGINE__H