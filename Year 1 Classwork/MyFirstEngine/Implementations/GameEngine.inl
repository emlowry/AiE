/******************************************************************************
 * File:               GameEngine.inl
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Inline implementations of GameEngine functions.
 * Last Modified:      February 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef GAME_ENGINE__INL
#define GAME_ENGINE__INL

#include "Declarations\GameEngine.h"
#include "Declarations\GLFW.h"
#include "Declarations\MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// Private default constructor called only to initialize singleton
inline GameEngine::GameEngine() : m_bInitialized( false ) {}

// Initialize the game engine
inline bool GameEngine::Initialize()
{
    if( IsInitialized() )
    {
        return true;
    }
    Instance().m_bInitialized = ( GL_TRUE == glfwInit() );
    // TODO call other initialization/initialization failure functions
    return Instance().m_bInitialized;
}
inline bool GameEngine::IsInitialized() { return Instance().m_bInitialized; }

// Terminate the game engine
inline void GameEngine::Terminate()
{
    if( IsInitialized() )
    {
        glfwTerminate();
        Instance().m_bInitialized = false;
    }
}

}   // namespace MyFirstEngine

#endif  // GAME_ENGINE__INL