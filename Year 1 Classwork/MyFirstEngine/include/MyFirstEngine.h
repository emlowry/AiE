/******************************************************************************
 * File:               MyFirstEngine.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        All-inclusive header file for the MyFirstEngine library.
 * Last Modified:      February 4, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef MY_FIRST_ENGINE__H
#define MY_FIRST_ENGINE__H

#if !(defined INCLUDING_STATIC_MY_FIRST_ENGINE_LIBRARY) && \
    !(defined INCLUDING_INLINE_MY_FIRST_ENGINE_LIBRARY)
#define INCLUDING_DYNAMIC_MY_FIRST_ENGINE_LIBRARY
#endif

#include "..\Declarations\Comparable.h"
#include "..\Declarations\DumbString.h"
#include "..\Declarations\GameEngine.h"
#include "..\Declarations\GameState.h"
#include "..\Declarations\GameWindow.h"
#include "..\Declarations\Hashable.h"
#include "..\Declarations\NotCopyable.h"
#include "..\Declarations\Shader.h"
#include "..\Declarations\Singleton.h"
//TODO include declaration headers

#endif  // MY_FIRST_ENGINE__H
