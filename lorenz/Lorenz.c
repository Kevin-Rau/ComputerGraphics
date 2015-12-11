#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>


#define INPUT_LINE_LENGTH 80
int numPts = 200000;
double th=0;  //  Rotation angle
float pts[200000][3];

//viewing parameters
static GLfloat view_rotx = 25.0, view_roty = 50.0, view_rotz = 35.0;
static GLfloat view_posz = 60.0;


/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;
//program iterations 
int iter = 0;
int iterInc = 10;


void output( int text_pos, char *string)
{
  glColor3f( 255, 255, 255 );
  
  glWindowPos2i(5 , text_pos);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        
    glRotatef(view_rotx, 1.0, 0.0, 0.0);
    glRotatef(view_roty, 0.0, 1.0, 0.0);
    glRotatef(view_rotz, 0.0, 0.0, 1.0);

    glBegin(GL_LINE_STRIP);
    int i = 0;
    
    while( i < iter && i < numPts ) {
        glColor3fv(pts[i]);
        glVertex3fv(pts[i++]);
    }
    glEnd();
    
    if( iter < numPts ) {
        if( iter + iterInc > numPts ) iter = numPts;
        else iter+=iterInc;
    }
    
    glFlush();

    //outputs options to change the params of the program
    output(65, "Move with arrow keys   q,a,w,s,e,d: Change Lorenz Params");
    output(45, "r: Restart                              f: Finish");
    output(25, "t: Increase Speed               g: Decrease Speed");
    output(5, "y: Inc Zoom Z axis               h: Dec Zoom Z axis");
    glutSwapBuffers();
    glPopMatrix();
    
}
//from gears to change the window size
static void reshape(int width, int height) {
  GLfloat h = (GLfloat) height / (GLfloat) width;

  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0, 5.0, -h*2, h*2, 1.0, 300.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -60.0);
}
//used to rotate the viewing 
static void special(int k, int x, int y) {
    switch (k) {
        case GLUT_KEY_UP:
            view_rotx += 5.0;
            break;
        case GLUT_KEY_DOWN:
            view_rotx -= 5.0;
            break;
        case GLUT_KEY_LEFT:
            view_roty += 5.0;
            break;
        case GLUT_KEY_RIGHT:
            view_roty -= 5.0;
            break;
        default:
            return;
    }
  glutPostRedisplay();
}


//basic lorenz
static void lorenz(void) {
    int i;
    /*  Coordinates  */
    float x = pts[0][0] = 1;
    float y = pts[0][1] = 1;
    float z = pts[0][2] = 1;
    /*  Time step  */
    float dt = 0.001;

    for (i=0;i<numPts-1;i++)
    {   
        float dx = s*(y-x);
        float dy = x*(r-z)-y;
        float dz = x*y - b*z;
        x += dt*dx;
        y += dt*dy;
        z += dt*dz;
        
        pts[i+1][0] = x;
        pts[i+1][1] = y;
        pts[i+1][2] = z;
        
    }
}
//keyboard function keys to interact with the program
static void key(unsigned char k, int x, int y) {

    switch (k) {

        case 'r':
            iter = 0;
            break;
        case 'f':
            iter = numPts;
            break;
        case 't':
            iterInc += 5;
            break;
        case 'g':
            if( iterInc - 5 >- 0 ) iterInc -= 5;
            break;
        case 'y':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            view_posz -= 1;
            gluLookAt(0,0,view_posz,0.0,0.0,0.0,0.0,1.0,0.0);
            break;
        case 'h':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            view_posz += 1;
            gluLookAt(0,0,view_posz,0.0,0.0,0.0,0.0,1.0,0.0);
            break;
        case 'q':
            s += 0.5;
            lorenz();
            break;
        case 'a':
            s -= 0.5;
            lorenz();
            break;
        case 'w':
            b += 0.5;
            lorenz();
            break;
        case 's':
            b -= 0.5;
            lorenz();
            break;
        case 'e':
            r += 0.5;
            lorenz();
            break;
        case 'd':
            r -= 0.5;
            lorenz();
            break;
        default:
            return;
    }
    glutPostRedisplay();
}
//http://openglut.sourceforge.net/lorenz_8c.html credit for this function given here 


static void idle(void) {
    iter+=iterInc;
    glutPostRedisplay();
}



int main(int argc,char* argv[]) {
    lorenz();
    
    glutInit(&argc,argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    
    glutCreateWindow("My Lorenz Attractor");
    
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    //glutKeyboardFunc(changeVar);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    return 0;
}