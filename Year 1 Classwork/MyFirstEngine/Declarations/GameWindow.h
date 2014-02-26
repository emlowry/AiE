/******************************************************************************
 * File:               GameWindow.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Class representing a window managed by the game engine.
 * Last Modified:      February 25, 2014
 * Last Modification:  Added functions for clearing the screen.
 ******************************************************************************/

#ifndef GAME_WINDOW__H
#define GAME_WINDOW__H

#include "GLFW.h"
#include "MathLibrary.h"
#include <iostream>
#include <vector>
#include <unordered_map>

#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

using namespace Utility;
using Color::ColorVector;

class IMEXPORT_CLASS GameWindow : public NotCopyable
{
public:

    // Constructors
    GameWindow( const IntPoint2D& ac_roSize = IntPoint2D( 800, 600 ),
                const char* ac_pcTitle = "",
                const ColorVector& ac_roColor = Color::BLACK );
    GameWindow( unsigned int a_uiWidth, unsigned int a_uiHeight,
                const char* ac_pcTitle = "",
                const ColorVector& ac_roColor = Color::BLACK );

    // Destructor - actually does work!
    virtual ~GameWindow();

    // Get/Set window properties
    const ColorVector& GetClearColor() const { return m_oColor; }
    unsigned int GetIndex() const { return m_uiIndex; }
    const IntPoint2D& GetSize() const { return m_oSize; }
    const char* GetTitle() const { return m_oTitle.CString(); }
    GameWindow& SetClearColor( const ColorVector& ac_roColor );
    GameWindow& SetSize( unsigned int a_uiWidth, unsigned int a_uiHeight );
    GameWindow& SetSize( const IntPoint2D& ac_roSize );
    GameWindow& SetTitle( const char* ac_pcTitle );

    // Opening/Closing window
    void CancelClose(); // set the close flag for this window to false
    void Close();   // set the close flag for this window to true
    bool IsClosing() const; // is this window object flagged for closing?
    bool IsOpen() const { return ( nullptr != m_poWindow ); }
    bool Open();    // actually create the window with GLFW

    // make/check if current context window
    bool IsCurrent();
    GameWindow& MakeCurrent();

    // advance by frame
    void SwapBuffers();
    static void SwapAllBuffers();

    // Clear frame buffer of current window
    void Clear() { MakeCurrent(); ClearCurrent(); }
    static void ClearCurrent();

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

    // PIMPLE idiom - this class is only defined in the cpp, so inheritance from
    // an stl container won't result in warnings.
    class WindowList;
    class WindowLookup;

    // the two steps of opening a window
    void CreateWindow();
    void AdjustFramePadding();

    // close window
    void Destroy(); // destroy the GLFW window object
    void DoClose(); // if still closing after OnClose, destroy.

    // GLFW callback for window close
    static void OnCloseWindow( GLFWwindow* a_poWindow );

    // get references to the lists
    static WindowLookup& Lookup() { return *sm_poLookup; }
    static WindowList& List() { return *sm_poList; }

    unsigned int m_uiIndex; // identifies the window by its place in the list
    IntPoint2D m_oSize; // pixels available to draw on with OpenGL
    DumbString m_oTitle;    // Window title
    GLFWwindow* m_poWindow; // pointer to the GLFW window object, if open
    IntPoint2D m_oFramePadding; // difference in size between buffer and window
    ColorVector m_oColor;   // Color after clearing frame buffer

    static WindowLookup* sm_poLookup;
    static WindowList* sm_poList;

};  // class GameWindow

}   // namespace GameEngine

#endif  // GAME_WINDOW__H
