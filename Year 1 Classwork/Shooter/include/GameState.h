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
#include "Callback.h"

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
    class Singleton : public GameState
    {
    public:
        inline Singleton< Derived >* Clone() const override { return this; }
        static const Callback< void >& State = sm_oWrapper;
    protected:
        Singleton();
    private:
        class Wrapper : public Callback< void >
        {
        public:
            Wrapper( Derived& a_roSingleton ) : m_roCall( a_roSingleton ) {}
            ~Wrapper();
            Wrapper* Clone() const override { return new Wrapper( m_roSingleton ); }
            void operator()() override { m_roSingleton(); }
        private:
            Derived& m_roSingleton;
        };
        static Derived sm_oInstance;
        static Wrapper sm_oWrapper( sm_oInstance );
    };

    // Hash by instance address
    inline std::size_t Hash() const override { return (std::size_t)this; }

    // Do everything you need to in a given frame.
    inline void operator()() override { EventHandler::Run(); Update(); Draw(); }

    // State that shuts down the game
    static GameState* const END;

private:

    // Progress animations, move items with velocity, etc.
    // Collision detection could be handled here or via event handling.
    virtual void Update() = 0;

    // Draw the game to the screen.
    virtual void Draw() const = 0;

};

// State that shuts down the game
GameState* const GameState::END = nullptr;

#endif  // _GAME_STATE_H_