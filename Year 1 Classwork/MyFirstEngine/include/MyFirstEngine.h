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

#include "..\Declarations\AnimatedSprite.h"
#include "..\Declarations\Camera.h"
#include "..\Declarations\CharacterMap.h"
#include "..\Declarations\Drawable.h"
#include "..\Declarations\Font.h"
#include "..\Declarations\Frame.h"
#include "..\Declarations\GameEngine.h"
#include "..\Declarations\GameState.h"
#include "..\Declarations\GameWindow.h"
#include "..\Declarations\HTMLCharacters.h"
#include "..\Declarations\Keyboard.h"
#include "..\Declarations\Mouse.h"
#include "..\Declarations\Quad.h"
#include "..\Declarations\QuadShaderProgram.h"
#include "..\Declarations\Shader.h"
#include "..\Declarations\ShaderProgram.h"
#include "..\Declarations\Sprite.h"
#include "..\Declarations\SpriteShaderProgram.h"
#include "..\Declarations\Texture.h"
#include "..\Declarations\Typewriter.h"

#endif  // MY_FIRST_ENGINE__H
