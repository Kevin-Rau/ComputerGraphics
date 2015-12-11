
#include "CSCIx229.h"
#include "stdio.h"
#define GRAVITY 4.9
#define BALL_RADIUS 0.5
#define GROUND_LENGTH 5*dim
#define PI 3.1415927

int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=25.0;   //  Size of world
// Light values
int one       =   1;  // Unit value
int distance  =   18;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  40;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int zh; 
float ylight  =   15;  // Elevation of light
float xpos[] = {13.5, 10.5, 7.5, 4.5, 1.5, -1.5, -4.5, -7.5, -10.5, -13.5,};
float ypos[] = {10.5, 9.5, 8.5, 7.5, 6.5, 5.5, 4.5, 3.5, 2.5, 1.5,};
float yArray[1000];
float xArray[1000];
int startBall;
//int RESETTIME = 10;
unsigned int texture[6]; // Textures Array
int    box=1;
int counter = 0;
int lets_see = 0;


//make a data structure to hold all the information for the ball, way easier this way

typedef struct ball {
   float x;
   float y;
   float z; // Positions
   float vx; float vy; float vz; // Velocities 
   int active; 
} ball;

ball pBall;

//FINALLY ITS OVER THIS TOOK ME LITERALLY 50+ HOURS TO FINALLY FIGURE THIS OUT THANK THE LORD


void CalcPositions(){
   
    float a = -9.8;
    float int_velocity_x = 3.0;
    float int_velocity_y = 3.9;

    int i;


    float frames = 100;
    float dt1 = 0.01;
    float dt2 = 0.01;
    float dt3 = 0.01;
    float dt4 = 0.01;
    float dt5 = 0.01;
    float dt6 = 0.01;
    float dt7 = 0.01;
    float dt8 = 0.01;
    float dt9 = 0.01;
    float dt10 = 0.01;

    float dx;
    float dy;

	//basically what I resorted to was just making two really large arrays because doing the calculations on the
	//fly in the idle function was near impossible for me to figure out

    for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[0] - (int_velocity_x*dt1); 
        dy = ypos[0] + (int_velocity_y*dt1) + 0.5*a*pow(dt1,2); 
        xArray[i] = dx;
        yArray[i] = dy;
        dt1+= 0.01;
    }

        for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[1] - (int_velocity_x*dt2); 
        dy = ypos[1] + (int_velocity_y*dt2) + 0.5*a*pow(dt2,2); 
        xArray[100+i] = dx;
        yArray[100+i] = dy;
        dt2+= 0.01;
    }
        for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[2] - (int_velocity_x*dt3); 
        dy = ypos[2] + (int_velocity_y*dt3) + 0.5*a*pow(dt3,2); 
        xArray[200+i] = dx;
        yArray[200+i] = dy;
        dt3+= 0.01;
    }
        for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[3] - (int_velocity_x*dt4); 
        dy = ypos[3] + (int_velocity_y*dt4) + 0.5*a*pow(dt4,2); 
        xArray[300+i] = dx;
        yArray[300+i] = dy;
        dt4+= 0.01;
    }
        for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[4] - (int_velocity_x*dt5); 
        dy = ypos[4] + (int_velocity_y*dt5) + 0.5*a*pow(dt5,2); 
        xArray[400+i] = dx;
        yArray[400+i] = dy;
        dt5+= 0.01;
    }
        for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[5] - (int_velocity_x*dt6); 
        dy = ypos[5] + (int_velocity_y*dt6) + 0.5*a*pow(dt6,2); 
        xArray[500+i] = dx;
        yArray[500+i] = dy;
        dt6+= 0.01;
    }
        for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[6] - (int_velocity_x*dt7); 
        dy = ypos[6] + (int_velocity_y*dt7) + 0.5*a*pow(dt7,2); 
        xArray[600+i] = dx;
        yArray[600+i] = dy;
        dt7+= 0.01;
    }
        for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[7] - (int_velocity_x*dt8); 
        dy = ypos[7] + (int_velocity_y*dt8) + 0.5*a*pow(dt8,2); 
        xArray[700+i] = dx;
        yArray[700+i] = dy;
        dt8+= 0.01;
    }
        for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[8] - (int_velocity_x*dt9); 
        dy = ypos[8] + (int_velocity_y*dt9) + 0.5*a*pow(dt9,2); 
        xArray[800+i] = dx;
        yArray[800+i] = dy;
        dt9+= 0.01;
    }

        for (i = 0; i <= frames; i++)
    {   
       
        dx = xpos[9] - (int_velocity_x*dt10); 
        dy = ypos[9] + (int_velocity_y*dt10) + 0.5*a*pow(dt10,2); 
        xArray[900+i] = dx;
        yArray[900+i] = dy;
        dt10+= 0.01;
    }
    /*
    int j;
    for(j = 0; j < 100; j++) {
        printf("%f ", xArray[400+ j]);
    }
    printf("\n");*/

   //sanity check to see if i was storing the correct values in the array
  //}
}
void skyVertex(double th,double ph)
{
   glTexCoord2d(th/180.0, ph/190.0 + 0.5); 
                                          
   glVertex3d(Sin(ph)*Cos(th), Sin(th) , Cos(ph)*Cos(th));
}
//this vertex is just for the light source
static void Vertex2(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}
//here is my planet ball bouncing down the stiars. ex18 inspired.
static void Vertex(int th,int ph)
{
   double x = -Sin(th)*Cos(ph);
   double y =  Cos(th)*Cos(ph);
   double z =          Sin(ph);
   glNormal3d(x,y,z);
   glTexCoord2d(th/360.0,ph/180.0+0.5);
   glVertex3d(x,y,z);
}
//found a nice example of this on github that looked better than other sky examples
static void drawSky(double x, double y, double z, double r)
{
   const int d = 5;
   int th, ph = 0;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x, y, z);
   glScaled(r, r, r);

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture[0]);

   //  Latitude bands. Start at 0 for a hemisphere (no need for full sphere)
   for (ph = -90; ph < 90; ph += d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0; th<=360; th+=d)
      {
         skyVertex(th, ph);
         skyVertex(th, ph+d);
      }
      glEnd();
   }
   glDisable(GL_TEXTURE_2D);

   //  Undo transformations
   glPopMatrix();
}

static void drawSphere(double x, double y, double z, double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex2(th,ph);
         Vertex2(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

static void drawBall(double x, double y, double z, double r)
{
   int th,ph;

   /*
    *
    */

   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  Set texture
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture[lets_see]);
   //  Latitude bands
   for (ph=-90;ph<90;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=5)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      glEnd();
   }

   glDisable(GL_TEXTURE_2D);
   //  Undo transofrmations
   glPopMatrix();
}


//made seperate instances of some blocks
static void stair(double x, double y, double z,
          double dx, double dy, double dz,
          double th){
  
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

  glPushMatrix();
  
  // Translations
  glTranslated(x, y, z);
  glRotated(th, 0, 1, 0);
  glScaled(dx, dy, dz);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

 //first stair 
  glBindTexture(GL_TEXTURE_2D,texture[lets_see+1]);
  glBegin(GL_QUADS);
  //Back
  glNormal3f( 0, 0, 15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5, 0, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5, 0, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+1, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+1, 15);
  //Front
  glNormal3f( 0, 0, -15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5, 0,-15);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5, 0,-15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+1,-15);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+1,-15);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5, 0,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5, 0,-15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+1,-15);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+1,+15);
  //  Left
  //glColor3f(0.5,0.5,0.5);
  glNormal3f( -5, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5, 0,-15);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5, 0,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+1,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+1,-15);
  //  Top
  glNormal3f( 0, +1, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+1,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+1,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+1,-15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+1,-15);
  //  Bottom
  glNormal3f( 0, -1, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5, 0,-15);
  glVertex3f(+5, 0,-15);
  glVertex3f(+5, 0,+15);
  glVertex3f(-5, 0,+15);
  



  //second stair
  //Back
  glNormal3f( 0, 0, 15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+1, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+1, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+2, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+2, 15);
  //Font
  glNormal3f( 0, 0, -12);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+1,-12);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+1,-12);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+2,-12);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+2,-12);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+1,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+1,-12);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+2,-12);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+2,+15);
  //  Left
  //glColor3f(0.5,0.5,0.5);
  glNormal3f( -5, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+1,-12);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+1,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+2,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+2,-12);
  //  Top
  glNormal3f( 0, 2, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+2,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+2,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+2,-12);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+2,-12);
  //  Bottom
  glNormal3f( 0, +1, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5,+1,-12);
  glVertex3f(+5,+1,-12);
  glVertex3f(+5,+1,+15);
  glVertex3f(-5,+1,+15);


  //Third Stair
  //Back
  glNormal3f( 0, 0, 15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+2, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+2, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+3, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+3, 15);
  //Font
  glNormal3f( 0, 0, -9);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+2,-9);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+2,-9);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+3,-9);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+3,-9);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+2,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+2,-9);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+3,-9);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+3,+15);
  //  Left
  glNormal3f( -5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+2,-9);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+2,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+3,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+3,-9);
  //  Top
  glNormal3f( 0, +3, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+3,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+3,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+3,-9);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+3,-9);
  //  Bottom
  glNormal3f( 0, +2, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5,+2,-9);
  glVertex3f(+5,+2,-9);
  glVertex3f(+5,+2,+15);
  glVertex3f(-5,+2,+15);

  //Fourth Stair
  //Back
  glNormal3f( 0, 0, 15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+3, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+3, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+4, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+4, 15);
  //Font
  glNormal3f( 0, 0, -6);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+3,-6);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+3,-6);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+4,-6);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+4,-6);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+3,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+3,-6);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+4,-6);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+4,+15);
  //  Left
  glNormal3f( -5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+3,-6);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+3,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+4,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+4,-6);
  //  Top
  glNormal3f( 0, +4, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+4,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+4,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+4,-6);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+4,-6);
  //  Bottom
  glNormal3f( 0, +3, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5,+3,-6);
  glVertex3f(+5,+3,-6);
  glVertex3f(+5,+3,+15);
  glVertex3f(-5,+3,+15);


  //Fifth Stair
  //Back
  glNormal3f( 0, 0, 15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+4, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+4, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+5, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+5, 15);
  //Font
  glNormal3f( 0, 0, -3);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+4,-3);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+4,-3);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+5,-3);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+5,-3);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+4,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+4,-3);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+5,-3);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+5,+15);
  //  Left
  glNormal3f( -5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+4,-3);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+4,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+5,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+5,-3);
  //  Top
  glNormal3f( 0, +5, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+5,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+5,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+5,-3);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+5,-3);
  //  Bottom
  glNormal3f( 0, +4, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5,+4,-3);
  glVertex3f(+5,+4,-3);
  glVertex3f(+5,+4,+15);
  glVertex3f(-5,+4,+15);


  //Sixth Stair
  //Back
  glNormal3f( 0, 0, +15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+5, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+5, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+6, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+6, 15);
  //Font
  glNormal3f( 0, 0, -0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+5,0);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+5,0);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+6,0);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+6,0);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+5,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+5,0);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+6,0);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+6,+15);
  //  Left
  glNormal3f( -5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+5,0);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+5,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+6,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+6,0);
  //  Top
  glNormal3f( 0, +6, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+6,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+6,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+6,0);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+6,0);
  //  Bottom
  glNormal3f( 0, +5, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5,+5,0);
  glVertex3f(+5,+5 ,0);
  glVertex3f(+5,+5,+15);
  glVertex3f(-5,+5,+15);


  //Seventh Stair
  //Back
  glNormal3f( 0, 0, 15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+6, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+6, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+7, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+7, 15);
  //Font
  glNormal3f( 0, 0, +3);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+6,+3);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+6,+3);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+7,+3);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+7,+3);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+6,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+6,+3);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+7,+3);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+7,+15);
  //  Left
  glNormal3f( -5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+6,+3);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+6,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+7,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+7,+3);
  //  Top
  glNormal3f( 0, +7, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+7,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+7,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+7,+3);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+7,+3);
  //  Bottom
  glNormal3f( 0, +6, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5,+6,+3);
  glVertex3f(+5,+6,+3);
  glVertex3f(+5,+6,+15);
  glVertex3f(-5,+6,+15);


  //Eigth Stair
  //Back
  glNormal3f( 0, 0, 15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+7, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+7, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+8, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+8, 15);
  //Font
  glNormal3f( 0, 0, +6);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+7,+6);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+7,+6);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+8,+6);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+8,+6);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+7,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+7,+6);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+8,+6);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+8,+15);
  //  Left
  glNormal3f( -5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+7,+6);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+7,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+8,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+8,+6);
  //  Top
  glNormal3f( 0, +8, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+8,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+8,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+8,+6);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+8,+6);
  //  Bottom
  glNormal3f( 0, +7, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5,+7,+6);
  glVertex3f(+5,+7,+6);
  glVertex3f(+5,+7,+15);
  glVertex3f(-5,+7,+15);


  //Ninth Stair
  //Back
  glNormal3f( 0, 0, 15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+8, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+8, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+9, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+9, 15);
  //Font
  glNormal3f( 0, 0, +9);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+8,+9);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+8,+9);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+9,+9);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+9,+9);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+8,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+8,+9);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+9,+9);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+9,+15);
  //  Left
  glNormal3f( -5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+8,+9);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+8,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+9,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+9,+9);
  //  Top
  glNormal3f( 0, +9, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+9,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+9,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+9,+9);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+9,+9);
  //  Bottom
  glNormal3f( 0, +8, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5,+8,+9);
  glVertex3f(+5,+8,+9);
  glVertex3f(+5,+8,+15);
  glVertex3f(-5,+8,+15);


  //Tenth Stair
  //Back
  glNormal3f( 0, 0, 15);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+9, 15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+9, 15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+10, 15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+10, 15);
  //Font
  glNormal3f( 0, 0, +12);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+9,+12);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+9,+12);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+10,+12);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+10,+12);
  //  Right
  glNormal3f(+5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(+5,+9,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+9,+12);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+10,+12);
  glTexCoord2f(0.0, 5.0); glVertex3f(+5,+10,+15);
  //  Left
  glNormal3f( -5, 0, 0);
  //glColor3f(0.5,0.5,0.5);
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+9,+12);
  glTexCoord2f(5.0, 0.0); glVertex3f(-5,+9,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(-5,+10,+15);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+10,+12);
  //  Top
  glNormal3f( 0, +10, 0);
  //glColor3f(0.5,0.5,0.5);;
  glTexCoord2f(0.0, 0.0); glVertex3f(-5,+10,+15);
  glTexCoord2f(5.0, 0.0); glVertex3f(+5,+10,+15);
  glTexCoord2f(5.0, 5.0); glVertex3f(+5,+10,+12);
  glTexCoord2f(0.0, 5.0); glVertex3f(-5,+10,+12);
  //  Bottom
  glNormal3f( 0, +9, 0);
  //glColor3f(0.5,0.5,0.5);
  glVertex3f(-5,+9,+12);
  glVertex3f(+5,+9,+12);
  glVertex3f(+5,+9,+15);
  glVertex3f(-5,+9,+15);


  glEnd();
  glDisable(GL_POLYGON_OFFSET_FILL);
  glDisable(GL_TEXTURE_2D); 
  glPopMatrix();
}

//I wanted to add some trees so here is the trunks, couldn't find nice code to make a better top part 
static void drawCylinder(double r, double h, double x, double y, double z, int rotation)
{
   const int SIDE_COUNT = 100;
   glPushMatrix();

   glTranslated(x, y, z);
   glRotated(rotation, 1, 1, 0); 
   glScaled(r, h, r);

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture[4]);
   glColor3f(1, 1, 1);
   glBegin(GL_QUAD_STRIP); 
   int i = 0;
   for (; i <= SIDE_COUNT; i++) {     
       float angle = i*((1.0/SIDE_COUNT) * (2*PI));
       glTexCoord2f(1 - 2*(float)i/SIDE_COUNT, 1);
       glNormal3d( cos(angle), 0, sin(angle) );
       glVertex3d( 1*cos(angle), 0, 1*sin(angle) );
       glTexCoord2f(1 - 2*(float)i/SIDE_COUNT, 0);
       glVertex3d( 1*cos(angle), 1, 1*sin(angle) );   }
   glEnd();
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}
//branhces that for some reason dont want to reflect light. 
static void triangle(double x, double y)
{
  glPushMatrix();
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(-1, -1);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
  //glColor3f(1,1,1);
  glBindTexture(GL_TEXTURE_2D,texture[5]);
  glBegin (GL_TRIANGLES);
      glNormal3f(0,0,1);
      //glColor4f(0, 0.5, 0, 0.75);
      glTexCoord2f(0,0); glVertex3f(x, 8, y); 
      glTexCoord2f(5,0); glVertex3f(x+2, 4, y-2); 
      glTexCoord2f(2,5); glVertex3f(x-2, 4, y+2); 
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}


static void theTrees(){
  drawCylinder(0.2, 4.0, -13.0, -0.0, -10.0, 0);
  //triangle(-13.0, -10.0);

  drawCylinder(0.2, 4.0, 15.0, -0.0, 10.0, 0);
  //triangle(15.0, 10.0);

  drawCylinder(0.2, 4.0, -17.0, -0.0, 5.0, 0);
  //triangle(-10.0, 5.0);

  drawCylinder(0.2, 4.0, 18.0, -0.0, 0.0, 0);
  //triangle(18.0, 0.0);

  drawCylinder(0.2, 4.0, 7.0, -0.0, -7.0, 0);
  //triangle(7.0, -7.0);

  drawCylinder(0.2, 4.0, -10.0, -0.0, 7.0, 0);
  //triangle(-10.0, 7.0);

  drawCylinder(0.2, 4.0, 14.0, -0.0, 15.0, 0);
  //triangle(14.0, 15.0);

  drawCylinder(0.2, 4.0, -16.0, -0.0, -18.0, 0);
  //triangle(-16.0, -18.0);
}
//so the lighting actually works, just texture is really bright, doesn't show that well
static void theGrounds()
{
  
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

  int k;
  int j;
  glBindTexture(GL_TEXTURE_2D, texture[3]);
  glBegin(GL_QUADS);
  
  for(j = 0; j <= 40; j++)
  {
    for(k = 0;k <= 40; k++)
    {
      
 
      //glColor3ub(0,35,0);
      glNormal3f(0,+1,0);
      glTexCoord2f(0,0); glVertex3f(-20+j,0, 19-k);
      glTexCoord2f(1,0); glVertex3f( -19+j,0,19-k);
      glTexCoord2f(1,1); glVertex3f(-19+j,0,20-k);
      glTexCoord2f(0,1); glVertex3f(-20+j,0, 20-k);
    
    }

  }
  //glDisable(GL_TEXTURE_2D);
  glEnd();
  glDisable(GL_TEXTURE_2D);

}

static void drawProject(){



  
  stair(-1,0,0 , 1,1,1, 0);




}
void drawScene()
{
    drawProject();
    theTrees();
    theGrounds();
    if( pBall.active )
   {
        float Position[]  = {pBall.z,pBall.y,pBall.x};
        //  Draw light position as ball (still no lighting here)
        //glColor3f(0.0,0.1,0.0);
        drawBall(Position[0],Position[1],Position[2] , 0.5);
   } 

}




/*
 *  OpenGL calls this routine to display the scene
 */
void display()
{

   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,1);
        drawSphere(Position[0],Position[1],Position[2] , 0.1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
     glDisable(GL_LIGHTING);

   //  Draw scene
   drawSky(0, -10, 0, 2*GROUND_LENGTH);
   drawScene();
   triangle(-13.0, -10.0);
   triangle(15.0, 10.0);
   triangle(-17.0, 5.0);
   triangle(18.0, 0.0);
   triangle(7.0, -7.0);
   triangle(-10.0, 7.0);
   triangle(14.0, 15.0);
   triangle(-16.0, -18.0);
   //glDisable(GL_LIGHTING);

   if ( pBall.y == 0.5)
   {
       startBall = 0;
   }
	//double check to make sure that the ball will re-animate 
   glDisable(GL_LIGHTING);


   glColor3f(1, 1, 1);
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
     th,ph,dim,fov,mode?"Perpsective":"Orthogonal",light?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,25);
      Print("YPos=%f XPos=%f Light Distance=%d Elevation=%.1f",pBall.y, pBall.x,distance,ylight);
      
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
//restart the ball at the initial position
void resetBall(int stop)
{
  if (stop == 1)
  {
   counter  = 0;
   pBall.active = 1;
   pBall.x = 13.5;
   pBall.vx = 0.0;
   pBall.y = 10.5;
   pBall.vy = 0.0;
   pBall.z = 0;
   pBall.vz = 0.0;
 }
}

//WORKS AND ITS BEAUTIFUL IM SO HAPPY
//This took me 3 different refactorings, over 10 helper functions and over a week of research only to
//figure out that I was really overthinking this whole thing
void runBall(int toggle)
{
   if (toggle>0)
      move = !move;
   //  Increment light/ball position
   else {
      zh = (zh+1)%360;
        counter = counter+ 1;
		
        pBall.x = xArray[counter];
        pBall.y = yArray[counter];
        if (counter == 1000){
          counter = 0;
        }
        else if(counter == 200 || counter == 400 || counter == 600 ||counter == 800 ||counter == 1000)
        {
			lets_see += 1;
			if (lets_see == 5){
				lets_see = 0;
			}
		}
		 
}
   
  if (move && toggle>=0) glutTimerFunc(10,runBall,0);
   //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}


//code that was broken made so many functions to try and get this to work. 
//(this isn't even close to how many functions i really made before
    /*

  g_counter = value + 1; 
  glutPostRedisplay();
  glutTimerFunc(GAP, myTimer, g_counter);



    float timeAtReset = glutGet(GLUT_ELAPSED_TIME)/10.0;
    
    float timeSinceReset = (glutGet(GLUT_ELAPSED_TIME)/10.0) - timeAtReset;
    int a = (int)(timeSinceReset+0.5);
 
    pBall.x = xArray[a];
    pBall.y = yArray[a];
      }

*/


   /*   
   if(startBall)
   { 
      pBall.vx = 3.0;
      pBall.vy = 3.9;
      //float x0 = pBall.x;
      //float y0 = pBall.y;
      float dt = 0.01;
   
      int i = -1;
      yArray[i+=1];

      pBall.x -= dt*pBall.vx;
      yArray[i] = ypos[1] + (dt*pBall.vy - GRAVITY*pow(dt, 2));
      pBall.y += yArray[i];

      pBall.x = xArray[i];
      pBall.y = yArray[i];
      
      i = i +1;
   }*/

/*
void idle2()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}
*/

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
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   else if (key == GLUT_KEY_F3)
      distance = (distance==9) ? 18 : 9;
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      inc = (inc==10)?3:10;
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode?fov:0,asp,dim);
  
   glutPostRedisplay();
   //runBall(-1);
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{

   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Switch projection mode
   else if (ch == 'p' || ch == 'P')
      mode = 1+mode;
   //  Toggle light/animation
   else if (ch == 'm' || ch == 'M')
      runBall(1);

   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
	//draw/reset the ball position
    else if (ch == 's' || ch == 'S')
    {
      resetBall(1);
    }
	

   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Animate if requested
   runBall(-1);
   glutPostRedisplay();
   //runBall(-1);
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
   Project(mode?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   CalcPositions();
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Kevin Rau - Final Project");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);

   texture[0] = LoadTexBMP("skynight.bmp");
   texture[1] = LoadTexBMP("bood.bmp");
   texture[2] = LoadTexBMP("earth.bmp");
   texture[3] = LoadTexBMP("grass.bmp");
   texture[4] = LoadTexBMP("wood.bmp");
   texture[5] = LoadTexBMP("leaf.bmp");




   runBall(1);


   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
