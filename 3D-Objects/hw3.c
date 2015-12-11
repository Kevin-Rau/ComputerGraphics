#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int axes=0;       //  Display axes
int mode=1;       //  Projection mode
int th=60;         //  Azimuth of view angle
int ph=20;         //  Elevation of view angle
int fov=60;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=12.0;   //  Size of world

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415927/180*(th))
#define Sin(th) sin(3.1415927/180*(th))

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Set projection
 */
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode)
      gluPerspective(fov,asp,dim/4,4*dim);
   //  Orthogonal projection
   else
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}
/*
 *  Draw a house
 *     at (x,y,z)
 *     dimentions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void house(double x, double y, double z,
          double dx, double dy, double dz,
          double th){
  
  const double height = 5;
  const double width = 1.5;
  const double length = 1.2;
  const double bottom = 0.75;

  glPushMatrix();
  
  // Translations
  glTranslated(x, y, z);
  glRotated(th, 0, 1, 0);
  glScaled(dx, dy, dz);

 //Base of the House 
  glBegin(GL_QUADS);
  //  Front
  glColor3f(1,1,1);
  glVertex3f(-1,-1, 1);
  glVertex3f(+1,-1, 1);
  glVertex3f(+1,+1, 1);
  glVertex3f(-1,+1, 1);
  //  Back
  glColor3f(1,1,1);
  glVertex3f(+1,-1,-1);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,+1,-1);
  glVertex3f(+1,+1,-1);
  //  Right
  glColor3f(1,1,1);
  glVertex3f(+1,-1,+1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,+1,-1);
  glVertex3f(+1,+1,+1);
  //  Left
  glColor3f(1,1,1);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,-1,+1);
  glVertex3f(-1,+1,+1);
  glVertex3f(-1,+1,-1);
  //  Top
  glColor3f(0,0,0);
  glVertex3f(-1,+1,+1);
  glVertex3f(+1,+1,+1);
  glVertex3f(+1,+1,-1);
  glVertex3f(-1,+1,-1);
  //  Bottom
  glColor3f(0,0,0);
  glVertex3f(-1,-1,-1);
  glVertex3f(+1,-1,-1);
  glVertex3f(+1,-1,+1);
  glVertex3f(-1,-1,+1);
  glEnd();
  //used quads for the doors reshaping the cube
  glBegin(GL_QUADS);
  glColor3ub(1,0,0);
  //  Front
  glVertex3f(+.2,-1,1.01);
  glVertex3f(-.2,-1,1.01);
  glVertex3f(-.2,0,1.01);
  glVertex3f(+.2,0,1.01);
    //  Right
  glVertex3f(+.2,0,1.01);
  glVertex3f(+.2,-1,1.01);
  glVertex3f(+.2,-1,1.0);
  glVertex3f(+.2,0,1.0);
  //  Left
  glVertex3f(-.2,0,1.01);
  glVertex3f(-.2,-1,1.01);
  glVertex3f(-.2,-1,1.0);
  glVertex3f(-.2,0,1.0);
  glEnd();
  //  Top
  glVertex3f(+.2,0,1.01);
  glVertex3f(+.2,0,1.0);
  glVertex3f(-.2,0,1.0);
  glVertex3f(-.2,0,1.01);


//Roof sections
  glBegin(GL_TRIANGLES);
  // Front
  glColor3ub(30,30,30);
  glVertex3f(+width,+bottom,+length);
  glVertex3f(-width,+bottom,+length);
  glVertex3f(0,+height,+length);
  // Back
  glVertex3f(+width,+bottom,-length);
  glVertex3f(-width,+bottom,-length);
  glVertex3f(0,+height,-length);
  glEnd();
  // Sides 
  glBegin(GL_QUADS);
  // Bottom
  glColor3ub(0,0,0);
  glVertex3f(+width,+bottom,-length);
  glVertex3f(+width,+bottom,+length);
  glVertex3f(-width,+bottom,+length);
  glVertex3f(-width,+bottom,-length);
  // Right side
  glColor3ub(50,50,50);
  glVertex3f(+width,+bottom,-length);
  glVertex3f(+width,+bottom,+length);
  glVertex3f(0,+height,+length);
  glVertex3f(0,+height,-length);
  // Left Side
  glVertex3f(-width,+bottom,-length);
  glVertex3f(-width,+bottom,+length);
  glVertex3f(0,+height,+length);
  glVertex3f(0,+height,-length);  
  glEnd();

  glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{

   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glMatrixMode(GL_MODELVIEW);
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Set view angle
   //glRotatef(ph,1,0,0);
   //glRotatef(th,0,1,0);
 
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

//http://elearning.vtu.ac.in/10/enotes/06CS65/PNU/openGLHouse-PNU.pdf Credit for rotating houses 
  // Draw houses in a circle
  const double radius = 5;
  const double angleStep = 360.0/5;
  double angle = 0;
  int i;
    for(i = 0; i < 5; i++)
    {
        // Push the current matrix now, because we are
        // going to specify the object coordinate system
        // next.
        glPushMatrix();
        // Object Coordinate System
        glRotatef(angle, 0, 1, 0);
        glTranslatef(radius, 0, 0);
        // Render the object itself
        house(-1,0,0 , 1,1,1, 0);
        // Pop the previously pushed matrix, because we are
        // going back to the world coordinate system,
        // before specifying the object coodinate system for the
        // next object.
        glPopMatrix();
        // Increment the angle by angleStep to draw the next house
        
        angle += angleStep;
      
    }
//the plains
  glColor3ub(0,50,0);
  glBegin(GL_QUADS);
  glNormal3f(0,+1,0);
  glVertex3f(-200,-1,-200);
  glVertex3f(-200,-1,200);
  glVertex3f(200,-1,200);
  glVertex3f(200,-1,-200);
  glEnd();


   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");
   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  w key - increase dim
   else if (ch == 'w')
      dim += 0.1;
   //  s key - decrease dim
   else if (ch == 's' && dim>1)
      dim -= 0.1;
   //  Reproject
   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(700,700);
   glutCreateWindow("Houses");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}