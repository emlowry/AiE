/******************************************************************************
 * File:               GameState.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Base classes for game states.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "EventHandler.h"

#define SINGLETON_STATE_CLASS( CLASS_NAME ) class CLASS_NAME \
    : public GameState::Singleton< CLASS_NAME >

#define SINGLETON_STATE_PRIVATE( CLASS_NAME ) private: \
    friend GameState::Singleton< CLASS_NAME >; \
    CLASS_NAME(); \
    CLASS_NAME( const CLASS_NAME &a_roOriginal ); \
    CLASS_NAME & operator=( const CLASS_NAME &a_roOriginal );

// Abstract class representing a game state.  Derived classes must implement the
// Update and Draw functions.
class GameState
{
public:

    // Abstract class representing a singleton game state.  Uses the Curiously
    // Recurring Template Pattern idiom so that the derived classes only have to
    // implement Update() and Draw().  Derived classes are declared like so:
    //
    // class DerivedState // final // C++11
    //     : public GameState::Singleton< DerivedState > //, other base classes
    // {
    // 
    //     // ... class public and protected declarations...
    //
    // private:
    //     friend GameState::Singleton< DerivedState >;
    //     DerivedState();
    //     DerivedState( const DerivedState& a_roOriginal );
    //     DerivedState& operator=( const DerivedState& a_roOriginal );
    //
    //     // ... the rest of the class private declarations...
    //
    // };
    //
    // Or, to use the simplifying macros:
    //
    // SINGLETON_STATE_CLASS( DerivedState ) //, other base classes
    // {
    // 
    //     // ... class public and protected declarations...
    //
    // SINGLETON_STATE_PRIVATE( DerivedState )
    // 
    //     // ... the rest of the class private declarations...
    //
    // };
    template< typename Derived >
    class Singleton : public GameState
    {
    public:
        static inline GameState* State() { return &sm_oInstance; }
    protected:
        Singleton();
    private:
        Singleton( const Singleton& a_roOriginal );
        Singleton& operator=( const Singleton& a_roOriginal );
        static Derived sm_oInstance;
    };

    // Do everything you need to in a given frame.
    inline void Run() { EventHandler::Run(); Update(); Draw(); }

private:

    // Progress animations, move items with velocity, etc.
    // Collision detection could be handled here or via event handling.
    virtual void Update() = 0;

    // Draw the game to the screen.
    virtual void Draw() const = 0;

};

#endif  // _GAME_STATE_H_