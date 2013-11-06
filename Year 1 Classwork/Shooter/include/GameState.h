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

#include "Callback.h"

// Use these macros to simplify declaration of GameState::Singleton classes.
// Derived GameState classes, Singleton or otherwise, will need to implement the
// Draw() and Update() functions.  Non-singleton game states will need to
// implement Clone().
#define SINGLETON_STATE_CLASS( CLASS_NAME ) class CLASS_NAME \
    : public GameState::Singleton< CLASS_NAME >

#define SINGLETON_STATE_PRIVATE( CLASS_NAME ) private: \
    friend GameState::Singleton< CLASS_NAME >; \
    CLASS_NAME();

// Abstract class representing a game state.  Derived classes must implement the
// Update and Draw functions.
class GameState : public Callback< void >
{
public:

    template< typename Derived >
    class Singleton;

    // Declared here so calls will be expected to return GameState* and not just
    // Callback<void>*, but made abstract so that derived classes must implement
    // it to compile.
    virtual GameState* Clone() const override = 0;

    // Do everything you need to in a given frame.
    void operator()() override;

    // State that shuts down the game
    static GameState* const END;

private:

    // Progress animations, move items with velocity, etc.
    // Collision detection could be handled here or via event handling.
    virtual void Update() = 0;

    // Draw the game to the screen.
    virtual void Draw() const = 0;

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

    // You should never be able to call a singleton's Clone() function because
    // you should never have access to the singleton instance - only the
    // singleton's private caller class can access that instance, and you can
    // only call on the instance by calling on an instance of that private
    // caller class
    Singleton< Derived >* Clone() const override;
    static const Caller State;

protected:

    Singleton();

private:

    class Caller : public GameState
    {
    public:
        Caller();
        virtual ~Caller();
        Caller* Clone() const override;
    private:
        void Update() override;
        void Draw() const override;
    };

    static Derived sm_oInstance;

};

#include "inline/GameState.inl"

#endif  // _GAME_STATE_H_