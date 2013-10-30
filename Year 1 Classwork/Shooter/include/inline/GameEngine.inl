/******************************************************************************
 * File:               GameEngine.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for GameEngine.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

// Get the current state
inline GameState* GameEngine::GetState()
{
    return sm_oStates.empty() ? nullptr : sm_oStates.top();
}

// Remove the topmost state from the stack
inline void GameEngine::PopState()
{
    sm_oStates.pop();
}

// Add the given state to the top of the stack
inline void GameEngine::PushState( GameState* a_poState )
{
    sm_oStates.push( a_poState );
}

// Run the game
inline void GameEngine::Run()
{
    while( !sm_oStates.empty() )
    {
        sm_oStates.top()->Run();
    }
}

// Set the given state as the only state
inline void GameEngine::SetState( GameState* a_poState )
{
    while( !sm_oStates.empty() )
    {
        sm_oStates.pop();
    }
    if( nullptr != a_poState )
    {
        sm_oStates.push( a_poState );
    }
}
