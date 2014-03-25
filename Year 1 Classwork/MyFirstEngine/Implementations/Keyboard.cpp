/******************************************************************************
 * File:               Keyboard.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 25, 2014
 * Description:        Class for managing keyboard
 * Last Modified:      March 25, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/GameEngine.h"
#include "../Declarations/GLFW.h"
#include "../Declarations/Keyboard.h"
#include <unordered_map>

//
// File-only helper functions and variables
//
namespace
{

// Store the times when each key was last pressed or released
struct Times
{
    double pressed;
    double released;
    double Time()
    {
        return MyFirstEngine::GameEngine::LastTime() -
                std::max( pressed, released );
    }
};
static std::unordered_map< MyFirstEngine::Keyboard::Key, Times > sg_oKeyTimes;

// press times for key combinations
static Times sg_oAnyKeyTimes = { 0.0, 0.0 };
static Times sg_oShiftKeyTimes = { 0.0, 0.0 };
static Times sg_oCtrlKeyTimes = { 0.0, 0.0 };
static Times sg_oAltKeyTimes = { 0.0, 0.0 };
static Times sg_oSuperKeyTimes = { 0.0, 0.0 };

// how many keys in a given combination are pressed
static unsigned int sg_uiKeysPressed = 0;
static unsigned int sg_uiShiftKeysPressed = 0;
static unsigned int sg_uiCtrlKeysPressed = 0;
static unsigned int sg_uiAltKeysPressed = 0;
static unsigned int sg_uiSuperKeysPressed = 0;

// callback for handling keypresses
void KeyPressCallback( GLFWwindow* a_poWindow, int a_iKey, int a_iScanCode,
                       int a_iAction, int a_iMods )
{
    // check to see if the given key is one that can be tracked
    if( !MyFirstEngine::Keyboard::IsKey( a_iKey ) )
    {
        return;
    }
    MyFirstEngine::Keyboard::Key eKey = (MyFirstEngine::Keyboard::Key)a_iKey;

    // If pressing the key when it was not pressed earlier,
    if( GLFW_PRESS == a_iAction &&
        sg_oKeyTimes[ eKey ].pressed <= sg_oKeyTimes[ eKey ].released )
    {
        // store press time
        sg_oKeyTimes[ eKey ].pressed = MyFirstEngine::GameEngine::LastTime();
        if( 1 == ++sg_uiKeysPressed )
        {
            sg_oAnyKeyTimes.pressed = MyFirstEngine::GameEngine::LastTime();
        }

        // check for modifier key presses
        if( ( MyFirstEngine::Keyboard::LEFT_SHIFT == eKey ||
              MyFirstEngine::Keyboard::RIGHT_SHIFT == eKey ) &&
            1 == ++sg_uiShiftKeysPressed )
        {
            sg_oShiftKeyTimes.pressed = MyFirstEngine::GameEngine::LastTime();
        }
        else if( ( MyFirstEngine::Keyboard::LEFT_CONTROL == eKey ||
                   MyFirstEngine::Keyboard::RIGHT_CONTROL == eKey ) &&
                 1 == ++sg_uiCtrlKeysPressed )
        {
            sg_oCtrlKeyTimes.pressed = MyFirstEngine::GameEngine::LastTime();
        }
        else if( ( MyFirstEngine::Keyboard::LEFT_ALT == eKey ||
                   MyFirstEngine::Keyboard::RIGHT_ALT == eKey ) &&
                 1 == ++sg_uiAltKeysPressed )
        {
            sg_oAltKeyTimes.pressed = MyFirstEngine::GameEngine::LastTime();
        }
        else if( ( MyFirstEngine::Keyboard::LEFT_SUPER == eKey ||
                   MyFirstEngine::Keyboard::RIGHT_SUPER == eKey ) &&
                 1 == ++sg_uiSuperKeysPressed )
        {
            sg_oSuperKeyTimes.pressed = MyFirstEngine::GameEngine::LastTime();
        }
    }
    
    // If releasing the key when it was not pressed earlier,
    else if( GLFW_RELEASE == a_iAction &&
        sg_oKeyTimes[ eKey ].pressed >= sg_oKeyTimes[ eKey ].released )
    {
        // store release time
        sg_oKeyTimes[ eKey ].released = MyFirstEngine::GameEngine::LastTime();
        if( 0 == sg_uiKeysPressed || 0 == --sg_uiKeysPressed )
        {
            sg_oAnyKeyTimes.released = MyFirstEngine::GameEngine::LastTime();
        }

        // check for modifier key releases
        if( ( MyFirstEngine::Keyboard::LEFT_SHIFT == eKey ||
              MyFirstEngine::Keyboard::RIGHT_SHIFT == eKey ) &&
            ( 0 == sg_uiShiftKeysPressed || 0 == --sg_uiShiftKeysPressed ) )
        {
            sg_oShiftKeyTimes.released = MyFirstEngine::GameEngine::LastTime();
        }
        else if( ( MyFirstEngine::Keyboard::LEFT_CONTROL == eKey ||
                   MyFirstEngine::Keyboard::RIGHT_CONTROL == eKey ) &&
                 ( 0 == sg_uiCtrlKeysPressed || 0 == --sg_uiCtrlKeysPressed ) )
        {
            sg_oCtrlKeyTimes.released = MyFirstEngine::GameEngine::LastTime();
        }
        else if( ( MyFirstEngine::Keyboard::LEFT_ALT == eKey ||
                   MyFirstEngine::Keyboard::RIGHT_ALT == eKey ) &&
                 ( 0 == sg_uiAltKeysPressed || 0 == --sg_uiAltKeysPressed ) )
        {
            sg_oAltKeyTimes.released = MyFirstEngine::GameEngine::LastTime();
        }
        else if( ( MyFirstEngine::Keyboard::LEFT_SUPER == eKey ||
                   MyFirstEngine::Keyboard::RIGHT_SUPER == eKey ) &&
                 ( 0 == sg_uiSuperKeysPressed || 0 == --sg_uiSuperKeysPressed ) )
        {
            sg_oSuperKeyTimes.released = MyFirstEngine::GameEngine::LastTime();
        }
    }
}

}   // namespace

//
// Class functions
//
namespace MyFirstEngine
{

// is the given int a valid key?
bool Keyboard::IsKey( int a_i )
{
    return ( 32 == a_i || 39 == a_i || ( 44 <= a_i && 57 >= a_i ) ||
             59 == a_i || 61 == a_i || ( 65 <= a_i && 93 >= a_i ) ||
             96 == a_i || 161 == a_i || 162 == a_i ||
             ( 256 <= a_i && 269 >= a_i ) || ( 280 <= a_i && 284 >= a_i ) ||
             ( 290 <= a_i && 314 >= a_i ) || ( 320 <= a_i && 336 >= a_i ) ||
             ( 340 <= a_i && 348 >= a_i ) );
}

// clean up data
void Keyboard::TerminateInstance()
{
    sg_oKeyTimes.clear();
    sg_oAnyKeyTimes.pressed = 0.0;
    sg_oAnyKeyTimes.released = 0.0;
    sg_oShiftKeyTimes.pressed = 0.0;
    sg_oShiftKeyTimes.released = 0.0;
    sg_oCtrlKeyTimes.pressed = 0.0;
    sg_oCtrlKeyTimes.released = 0.0;
    sg_oAltKeyTimes.pressed = 0.0;
    sg_oAltKeyTimes.released = 0.0;
    sg_oSuperKeyTimes.released = 0.0;
    sg_oSuperKeyTimes.released = 0.0;
    sg_uiKeysPressed = 0;
    sg_uiShiftKeysPressed = 0;
    sg_uiCtrlKeysPressed = 0;
    sg_uiAltKeysPressed = 0;
    sg_uiSuperKeysPressed = 0;
}

//
// Static functions
//

// Is the given key pressed right now?
bool Keyboard::KeyIsPressed( Key a_eKey )
{
    if( 0 == sg_oKeyTimes.count( a_eKey ) )
    {
        return false;
    }
    return sg_oKeyTimes[ a_eKey ].pressed > sg_oKeyTimes[ a_eKey ].released;
}
bool Keyboard::AnyKeyIsPressed()
{
    return ( 0 < sg_uiKeysPressed );
}
bool Keyboard::ShiftIsPressed()
{
    return ( 0 < sg_uiShiftKeysPressed );
}
bool Keyboard::ControlIsPressed()
{
    return ( 0 < sg_uiCtrlKeysPressed );
}
bool Keyboard::AltIsPressed()
{
    return ( 0 < sg_uiAltKeysPressed );
}
bool Keyboard::SuperIsPressed()
{
    return ( 0 < sg_uiSuperKeysPressed );
}

// How long has the given key been pressed/not pressed?
double Keyboard::KeyTime( Key a_eKey )
{
    if( 0 == sg_oKeyTimes.count( a_eKey ) )
    {
        return GameEngine::LastTime();
    }
    return sg_oKeyTimes[ a_eKey ].Time();
}
double Keyboard::AnyKeyTime() { return sg_oAnyKeyTimes.Time(); }
double Keyboard::ShiftTime() { return sg_oShiftKeyTimes.Time(); }
double Keyboard::ControlTime() { return sg_oCtrlKeyTimes.Time(); }
double Keyboard::AltTime() { return sg_oAltKeyTimes.Time(); }
double Keyboard::SuperTime() { return sg_oSuperKeyTimes.Time(); }

// Hook up or unhook the mouse event handlers for the given window
void Keyboard::Register( GameWindow& a_roWindow )
{
    if( nullptr != a_roWindow.m_poWindow )
    {
        glfwSetKeyCallback( a_roWindow.m_poWindow, KeyPressCallback );
    }
}
void Keyboard::Deregister( GameWindow& a_roWindow )
{
    if( nullptr != a_roWindow.m_poWindow )
    {
        glfwSetKeyCallback( a_roWindow.m_poWindow, nullptr );
    }
}

}   // namespace MyFirstEngine
