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

//#include "Callback.h"

// Use these macros to simplify declaration of GameState::Singleton classes.
// Derived GameState classes, Singleton or otherwise, will need to implement the
// Draw() and Update() functions.  Non-singleton game states will need to
// implement Clone().
#define SINGLETON_STATE_CLASS( CLASS_NAME ) class CLASS_NAME \
    : public GameState::Singleton< CLASS_NAME >

#define SINGLETON_STATE_PRIVATE( CLASS_NAME ) private: \
    friend GameState::Singleton< CLASS_NAME >; \
    CLASS_NAME(); \
    virtual ~CLASS_NAME();

// Abstract class representing a game state.  Derived classes must implement the
// Update and Draw functions.
class GameState// : public Callback< void >
{
public:

    // No need to define these - default implementations are fine
    GameState() {}
    virtual ~GameState() {}

    template< typename Derived >
    class Singleton;

    // Declared here so calls will be expected to return GameState* and not just
    // Callback<void>*, but made abstract so that derived classes must implement
    // it to compile.
    virtual GameState* Clone() const /*override*/ = 0;

    // Override these in child classes if you want things to happen when this
    // state is set as the current state, when another state is pushed onto the
    // stack above this one, when the state above this one in the stack is
    // popped off, or when this state is removed from the stack of states.
    virtual void OnEnter() {}   // When set as current state...
    virtual void OnExit() {}    // When removed from state stack...
    virtual void OnResume() {}  // When above state is popped from stack...
    virtual void OnSuspend() {} // When another state is pushed above this...

    // Do everything you need to in a given frame.
    void operator()() /*override*/;

    // State that shuts down the game
    static GameState* const END;

private:

    // Draw the game to the screen.
    virtual void Draw() const = 0;

    // Update based on used input
    virtual void HandleInput() = 0;

    // Progress animations, move items with velocity, etc.
    // Collision detection could be handled here or via event handling.
    virtual void Update() = 0;

};

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
class GameState::Singleton : public GameState
{
private:

    class Caller;

public:

    // No need to implement - default implementation is fine
    virtual ~Singleton() {}

    // You should never be able to call a singleton's Clone() function because
    // you should never have access to the singleton instance - only the
    // singleton's private caller class can access that instance, and you can
    // only call on the instance by calling on an instance of that private
    // caller class
    Singleton< Derived >* Clone() const override;
    static const Caller State;

protected:

    // No need to implement - default implementation is fine
    Singleton() {}

    static Derived sm_oInstance;

private:

    // Full declaration of the Caller class, objects of which are the only
    // things that call the singleton instance directly.
    class Caller : public GameState
    {
    public:
        Caller() {}
        virtual ~Caller() {}
        Caller* Clone() const override;
        void OnEnter() override;
        void OnExit() override;
        void OnResume() override;
        void OnSuspend() override;
    private:
        void Draw() const override;
        void HandleInput() override;
        void Update() override;
    };

};

#include "inline/GameState.inl"

#endif  // _GAME_STATE_H_