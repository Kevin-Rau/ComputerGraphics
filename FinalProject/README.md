# Final Project: Bouncing Balls In Space!
## Kevin Rau

Code inspired form Ex13, Ex18, Ex25 and online sources stated in lights.c & textures.c



- 70+ hours in Total. Lots of research on how to correctly animate a ball based on Newtons Equations for projectile motion. 
- WHAT NEEDS TO BE DONE
 For some reason my program was breaking when I was using code from other examples trying to animate the ball 
 bouncing down the stairs since I couldnt understand the equations behind plane-sphere intersection. I also tried to 
 go and implement the ball following a bezier curve and that was complicated as well. At last what I am going to do 
 is animate the ball following a repeated -x^2 curve down the stiars as an animation. I have not gotten this to work so 
 I am going in for office hours to figure this out all week. After that I plan on changing the textures of the stairs
 whenever the ball completes a loop of 1 -x^2 interation triggering the change. I will also add a step where the color of 
 the ball re colors. This should be easy becuase everytime i move the ball it re draws and I can change the color there. 
 
## UPDATED
	I am really proud that I finally made the ball move in a nature that is actual of projectile motion. This was the biggest
	accomplishment thus far because it took me 80% of the time to figure out (tons of trial and error, re-doing whole files of code and research).
	I had to calculate 1000 instances of a 10ms framerate redisplay of each instance of ypos and xpos to get this looking natural in respect to 
	how the program updates the scene. Again, when this was finally figured out it was a breath of fresh air and life was grand. 
	The rest was adding to make the scene what I wanted, ie. changing textures as the ball hits the steps and changing the 
	texture of the ball bouncing down the stiars as well.I am also proud that I made a good looking sky as well as natural 
	lighting on the ball. While this is simple, I feel the animation is what really shines here because I worked hours on 
	hours getting it to look as smooth and natural as possible. 

## Using the Makefile

- Make Object file `make`

- Run Executable `./finalProject`

- Clean Object File `make clean`

## Program Key Bindings/Interaction

- Key bindings:

 - Key bindings
  l          Toggles lighting
  F1         Toggle smooth/flat shading
  F2         Toggle local viewer mode
  F3         Toggle light distance (9 or 18)
  +/-        Change field of view of perspective
  arrows     Change view angle
  PgDn/PgUp  Zoom in and out
  0          Reset view angle
  ESC        Exit
  S/s        Reset the Ball position/Initialize Ball
  M/m        Stop Light/Ball Animation
