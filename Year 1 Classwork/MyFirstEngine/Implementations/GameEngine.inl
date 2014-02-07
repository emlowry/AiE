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
#include <iostream>

namespace MyFirstEngine
{

// Destructor doesn't need to do anything
INLINE GameEngine::~GameEngine() {}

// Private default constructor called only to initialize singleton
INLINE GameEngine::GameEngine() : m_bInitialized( false ) {}

//
// STATIC FUNCTIONS
//

// Initialize the game engine
INLINE bool GameEngine::Initialize()
{
    if( !IsInitialized() )
    {
        glfwSetErrorCallback( PrintError );
        Instance().m_bInitialized = ( GL_TRUE == glfwInit() );
        // TODO call other initialization/initialization failure functions
    }
    return IsInitialized();
}
INLINE bool GameEngine::IsInitialized() { return Instance().m_bInitialized; }

// Print error messages to standard error stream.
INLINE void GameEngine::PrintError( int a_iCode, const char* ac_pcDescription )
{
    std::cerr << "ERROR " << a_iCode << ": " << ac_pcDescription << std::endl;
}

// Terminate the game engine
INLINE void GameEngine::Terminate()
{
    if( IsInitialized() )
    {
        glfwTerminate();
        Instance().m_bInitialized = false;
    }
}

}   // namespace MyFirstEngine

#endif  // GAME_ENGINE__INL