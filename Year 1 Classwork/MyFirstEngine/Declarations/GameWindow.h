/******************************************************************************
 * File:               GameWindow.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Class representing a window managed by the game engine.
 * Last Modified:      February 11, 2014
 * Last Modification:  Adding GameState.
 ******************************************************************************/

#ifndef GAME_WINDOW__H
#define GAME_WINDOW__H

#include "DumbString.h"
#include "GLFW.h"
#include "MathLibrary.h"
#include "NotCopyable.h"
#include <iostream>

#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS GameWindow : public NotCopyable
{
public:

    // Constructors
    GameWindow( const IntPoint2D& ac_roSize = IntPoint2D( 800, 600 ),
                const char* ac_pcTitle = "" );
    GameWindow( unsigned int a_uiWidth, unsigned int a_uiHeight,
                const char* ac_pcTitle = "" );

    // Destructor - actually does work!
    virtual ~GameWindow();

    // Get/Set window properties
    unsigned int GetIndex() const;
    const IntPoint2D& GetSize() const;
    const char* GetTitle() const;
    GameWindow& SetSize( unsigned int a_uiWidth, unsigned int a_uiHeight );
    GameWindow& SetSize( const IntPoint2D& ac_roSize );
    GameWindow& SetTitle( const char* ac_pcTitle );

    // Opening/Closing window
    void CancelClose(); // set flag indicating window shouldn't close
    void Close();   // set flag indicating window should close
    bool IsClosing() const; // does GLFW flag indicate window should be closed?
    bool IsOpen() const;    // does a GLFW object exist?
    bool Open();    // actually create the window with GLFW

    // make/check if current context window
    bool IsCurrent();
    GameWindow& MakeCurrent();

    // advance by frame
    void SwapBuffers();
    static void SwapAllBuffers();

    // Destroy all windows
    static void DestroyAll();

    // Get a specific window
    // if there is no window at the given index, throw exception
    static GameWindow& Get( unsigned int a_uiIndex = 0 );

protected:

    // called when this window is closed
    // redefine in child classes if you want other things to happen
    virtual void OnClose() {}

private:

    // Does the work for all the constructors
    void SetUp();

    // the two steps of opening a window
    void CreateWindow();
    void AdjustFramePadding();

    // close window
    void Destroy(); // destroy the GLFW window object
    void DoClose(); // if still closing after OnClose, destroy.

    // GLFW callback for window close
    static void OnCloseWindow( GLFWwindow* a_poWindow );

    unsigned int m_uiIndex; // identifies the window by its place in the list
    IntPoint2D m_oSize; // pixels available to draw on with OpenGL
    DumbString m_oTitle;    // Window title
    GLFWwindow* m_poWindow; // pointer to the GLFW window object, if open
    IntPoint2D m_oFramePadding; // difference in size between buffer and window

};  // class GameWindow

}   // namespace GameEngine

#ifdef INLINE_IMPLEMENTATION
#include "..\Implementations\GameWindow.inl"
#endif

#endif  // GAME_WINDOW__H
