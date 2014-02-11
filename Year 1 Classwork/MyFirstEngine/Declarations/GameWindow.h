/******************************************************************************
 * File:               GameWindow.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Class representing a window managed by the game engine.
 * Last Modified:      February 10, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef GAME_WINDOW__H
#define GAME_WINDOW__H

#include "DumbString.h"
#include "GLFW.h"
#include "MathLibrary.h"
#include "NotCopyable.h"
#include <functional>
#include <vector>
#include <unordered_map>

#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS GameWindow : public NotCopyable
{
public:

    // prevent typing errors
    typedef std::vector< GameWindow* >::size_type WindowIndex;

    // Constructors
    GameWindow( const IntPoint2D& ac_roSize = IntPoint2D( 800, 600 ),
                const char* ac_pcTitle = "" );
    GameWindow( unsigned int a_uiWidth, unsigned int a_uiHeight,
                const char* ac_pcTitle = "" );

    // Destructor - actually does work!
    virtual ~GameWindow();

    // Get/Set window properties
    WindowIndex GetIndex() const { return m_uiIndex; }
    const IntPoint2D& GetSize() const { return m_oSize; }
    const char* GetTitle() const { return m_oTitle.CString(); }
    void SetSize( unsigned int a_uiWidth, unsigned int a_uiHeight );
    void SetSize( const IntPoint2D& ac_roSize );
    void SetTitle( const char* ac_pcTitle );

    // Opening/Closing window
    void CancelClose(); // set flag indicating window shouldn't close
    void Close();   // set flag indicating window should close
    bool IsClosing() const; // does GLFW flag indicate window should be closed?
    bool IsOpen() const;    // does a GLFW object exist?
    bool Open();    // actually create the window with GLFW

    // Destroy all windows
    static void DestroyAll();

    // Get a specific window
    // if window system is not initialized, throw exception
    // if there is no window at the given index, throw exception
    static GameWindow& Get( WindowIndex a_uiIndex = 0 );

protected:

    // called when this window is closed
    // redefine in child classes if you want other things to happen
    virtual void OnClose() {}

private:

    // prevent typing errors
    typedef std::vector< GameWindow* > WindowSet;
    typedef std::unordered_map< GLFWwindow*, WindowIndex > WindowLookup;

    // Does the work for all the constructors
    void SetUp();

    // close window
    void Destroy(); // destroy the GLFW window object
    void DoClose(); // called when window closed - if still closing after OnClose, destroy.

    // Get a map for looking up window index based on GLFW window object pointer
    static WindowLookup& Lookup();

    // GLFW callback for window close
    static void OnCloseWindow( GLFWwindow* a_poWindow );

    // Get a vector of pointers to all the managed windows
    static WindowSet& Windows();

    WindowIndex m_uiIndex;
    IntPoint2D m_oSize;
    DumbString m_oTitle;
    GLFWwindow* m_poWindow;

};  // class GameWindow

}   // namespace GameEngine

#ifdef INLINE_IMPLEMENTATION
#include "Implementations\GameWindow.inl"
#endif

#endif  // GAME_WINDOW__H
