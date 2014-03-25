/******************************************************************************
 * File:               Mouse.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 25, 2014
 * Description:        Class for managing mouse input
 * Last Modified:      March 25, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef MOUSE__H
#define MOUSE__H

#include "GameWindow.h"
#include "MathLibrary.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS Mouse : public Utility::InitializeableSingleton< Mouse >
{
    friend class Utility::InitializeableSingleton< Mouse >;
public:

    // Mouse buttons
    enum Button
    {
        BUTTON_1 = 0,
        BUTTON_2 = 1,
        BUTTON_3 = 2,
        BUTTON_4 = 3,
        BUTTON_5 = 4,
        BUTTON_6 = 5,
        BUTTON_7 = 6,
        BUTTON_8 = 7,

        LEFT_BUTTON = BUTTON_1,
        MIDDLE_BUTTON = BUTTON_3,
        RIGHT_BUTTON = BUTTON_2,

        BUTTON_COUNT = 8
    };

    virtual ~Mouse() {}

    // Is a button pressed?  How long has it been in that state?
    static bool ButtonIsPressed( Button m_eButton = LEFT_BUTTON );
    static double ButtonTime( Button m_eButton = LEFT_BUTTON );
    static bool LeftButtonIsPressed()
    { return ButtonIsPressed( LEFT_BUTTON ); }
    static double LeftButtonTime()
    { return ButtonTime( LEFT_BUTTON ); }
    static bool MiddleButtonIsPressed()
    { return ButtonIsPressed( MIDDLE_BUTTON ); }
    static double MiddleButtonTime()
    { return ButtonTime( MIDDLE_BUTTON ); }
    static bool RightButtonIsPressed()
    { return ButtonIsPressed( RIGHT_BUTTON ); }
    static double RightButtonTime()
    { return ButtonTime( RIGHT_BUTTON ); }

    // Where is the cursor's last reported position, in pixels, relative to the
    // center of the given window (+y = up) and is it even in said window?  If
    // no window is given, use main window. If window isn't valid GLFW window,
    // return origin.
    static Point2D Position( GameWindow* a_poWindow = nullptr );

    // Hook up or unhook the mouse event handlers for the given window
    static void Register( GameWindow& a_roWindow );
    static void Deregister( GameWindow& a_roWindow );

    // What game window, if any, is the cursor currently in?
    static GameWindow* Window();

    // When did the window the cursor is in (if any) last change"
    static double WindowChangeTime();

private:

    Mouse() {}

    virtual void InitializeInstance() override;
    virtual void TerminateInstance() override;

};  // class Mouse

}   // namespace MyFirstEngine

#endif  // MOUSE__H