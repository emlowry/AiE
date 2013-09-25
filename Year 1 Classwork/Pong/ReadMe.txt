NOTE:  As of September 25, 2013, this program has suddenly become unable to find
the AiE Static Framework DLL file, despite repeated uninstall/reinstalls of the
Framework, unless it's right there in the output bin directory.  Even then, it
mysteriously crashes when calling the framework's Initialize function, so I
can't debug anything.  Creating a new project and copying over the source,
header, and image files fixes nothing.

Due to this problem, I am unable to verify that the menu works as intended.  I
do know that match scores are stored correctly after matches are won and that
lists of scores display correctly when HighScores::Draw() is called, but whether
or not the rest of the menu works I have no way of knowing.

Because nothing is working properly, I have submitted only the files that I
personally created, not any of the files generated or copied in by Visual Studio
on project creation.

Following is the original ReadMe file content:

================================================================================
                   PONG: Starring Venus and Serena Williams!
================================================================================

To play the game, compile this project in Microsoft Visual Studio 2010 (or
later) on a computer with the AIE Static Framework installed, then either run it
from Visual Studio or find the Pong_d.exe file in the project bin directory and
run it directly.

On startup, you should see a menu that will allow you to select a difficulty
level and decide whether the left player (Serena Williams), the right player
(Venus Williams), or both should be controlled by keyboard input.

As the menu should tell you, the left player can be moved up and down using the
'W' and 'S' keys on your keyboard, while the right player can be controlled
using the UP and DOWN keys.  Begin the match by pressing the ENTER or SPACE key.

If a player fails to intercept the ball before it reaches the back of their
side of the field, then the other player scores a point and will serve the ball
to start the next round.  The match ends when one player has at least four
points and is ahead of their opponent by at least two points.

A match in progress can be paused using any of the ESCAPE, PAUSE/BREAK, HOME,
END, BACKSPACE, ENTER, or SPACE keys.  From the paused screen, the game may
either be resumed by pressing any of the PAUSE/BREAK, ENTER, or SPACE keys or
cancelled using any of the ESCAPE, HOME, END, or BACKSPACE keys.

A completed match may be automatically entered into the list of high scores.
The top five scores for points earned by a human, fastest wins by a human, and
slowest losses by a human, for each difficulty level, can be viewed from the
High Scores tab of the main menu.

Enjoy!

================================================================================
          ReadMe.txt created by Elizabeth Lowry on September 24, 2013
================================================================================
