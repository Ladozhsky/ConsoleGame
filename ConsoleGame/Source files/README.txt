1. DI realized. I created files Dependencies.h and Dependencies.c.
To Dependencies.h I added declatarions of structures and global variables.
To Dependencies.c I added daclarations of the all functions that I use in the main function.

2. Link to the video:
https://drive.google.com/file/d/1ZNAqs-RbWX9rRop-QK1MT7CJxc2-YxR-/view?usp=share_link

3. I made a console arkanoid. In this version, it is designed to pass five different levels, after gaining a certain number of points
the level rises. The field is changing, also the speed of the ball. Not to reach the maximum
result. After completing all the levels, the game ends and the inscription you win appears.

To begin with, I declared a two-dimensional array, assigned all elements of the zero row
special field character. Then I copied the zero string and replaced all array elements except zero and the last one with spaces.
Also, this function takes a level parameter and changes the field depending on it.
Next, I created the racket structure. The racket has the parameters width and coordinates of its appearance. Initialized racket. All functions are called in functions
main. Also created a function for moving the racket. It is taken into account that when moving the racket over the edge of the field, the coordinates will be updated to the extreme value.
Next, we connect the GetKeyState function from the windows.h library. It allows the program to work not only after pressing the button.
Then I made a response to read the characters a and d using this function. When they are pressed, the racket changes its coordinates. And after each click, you need to re-initialize all objects.
To do this, I do a do while loop until the esc button is pressed. Also I found a solution and created a setcur function, when COORD is also a kind of structure so that on every update the cursor is in the top left corner
and there was no screen flickering. And so that the racket does not move so fast, I use the sleep function for 10 milliseconds.
Next, I created the ball structure, initialized it and added it, made the move function. Placed on racket.
Given that the ball will move depending on the angle, I made the float type, and then cast these coordinates to an integer type.
Also made the function of automatic movement of the ball.
I made a variable run, which starts the game on the space button.
Then I found a solution to change the coordinates depending on the angle and rebound from the walls and the racket. Also made the handling of the situation when the ball leaves
outside the field, the game starts again, the ball is on the racket.
Also added a field for the number of hits. At the moment, set 5 hits with a racket to move to the next level.