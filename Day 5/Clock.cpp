#include <windows.h>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

#define LEN 8192

GLdouble scalex = 1, scaley =1, scalez = 1;


void printv(va_list args, const char* format)
{
  char buf[LEN];
  char* ch=buf;
  vsnprintf(buf,LEN,format,args);
  while (*ch)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void printAt(int x, int y, const char* format, ...)
{
  va_list args;
  //glWindowPos2i(x,y);
  va_start(args,format);
  printv(args,format);
  va_end(args);
}
int i;
void print(float x, float y, char *string)
{
//set the position of the text in the window using the x and y coordinates
glRasterPos3f(x,y,-1);
//get the length of the string to display
int len = (int) strlen(string);

//loop to display character by character
for (i = 0; i < len; i++)
{
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
//glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);

}
};

// define glu objects
int about_int=0;
int vflag=0;
GLfloat xt=0.0,yt=0.0,zt=0.0, zs=5.0;

GLUquadricObj *Cylinder;
GLUquadricObj *Disk;

struct tm *newtime;
time_t ltime;
int M_TWOPI=0;
GLfloat rx, ry, rz, angle;

// lighting
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition[]= { 5.0f, 25.0f, 15.0f, 1.0f };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static int light_state = 1; // light on = 1, light off = 0

static void TimeEvent(int te)
{

	rx = 30 * cos( angle );
	ry = 30 * sin( angle );
	rz = 30 * cos( angle );
	angle += 0.01;
	if (angle > M_TWOPI) angle = 0;

	glutPostRedisplay();
	glutTimerFunc( 100, TimeEvent, 1);
}


void init(void)
{


   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   // Lighting is added to scene
   glLightfv(GL_LIGHT1 ,GL_AMBIENT, LightAmbient);
   glLightfv(GL_LIGHT1 ,GL_DIFFUSE, LightDiffuse);
   glLightfv(GL_LIGHT1 ,GL_POSITION, LightPosition);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT1);


   Cylinder = gluNewQuadric();
   gluQuadricDrawStyle( Cylinder, GLU_FILL);
   gluQuadricNormals( Cylinder, GLU_SMOOTH);
   gluQuadricOrientation( Cylinder, GLU_OUTSIDE);
   gluQuadricTexture( Cylinder, GL_TRUE);

   Disk = gluNewQuadric();
   gluQuadricDrawStyle( Disk, GLU_FILL);
   gluQuadricNormals( Disk, GLU_SMOOTH);
   gluQuadricOrientation( Disk, GLU_OUTSIDE);
   gluQuadricTexture( Disk, GL_TRUE);


}

void num()
{
    glColor3f( 0.0, 0.0, 0.0);
	print(-6.1,0.1,"9"); //counting from center
	print(-0.195,-5.9,"12");
	print(-0.1,6.1,"6");
	print(5.9,0.1,"3");
	print(5.0, 3.2,"4");
	print(2.9,5.45,"5");
	print(-3.2,5.45,"7");
	print(-5.4, 3.2,"8");
	print(-5.5, -2.8,"10");
	print(-3.3,-5.05,"11");
	print(5.1, -2.8,"2");
	print(2.9,-5.05,"1");
}

void Draw_gear( void )
{

	int i;
	glPushMatrix();
	gluCylinder(Cylinder, 2.5, 2.5, 1, 16, 16);
	gluDisk(Disk, 0, 2.5, 32, 16);
	glTranslatef(0,0,1);
	glScaled(scalex,scaley,scalez);
    gluDisk(Disk, 0, 2.5, 32, 16);
	glPopMatrix();
    for( i = 0; i < 8; i++)
		{
	    glPushMatrix();
		glTranslatef( 0.0, 0.0, 0.50);
		glRotatef( (360/8) * i, 0.0, 0.0, 1.0);
		glScaled(scalex,scaley,scalez);
		glTranslatef( 3.0, 0.0, 0.0);
		glutSolidCube( 1.0 );
		glPopMatrix();
	    }


}

void Draw_clock( GLfloat cx, GLfloat cy, GLfloat cz )
{

  int hour_ticks , sec_ticks;
  glPushMatrix();
  glTranslatef(cx,cy,cz);
  glScaled(scalex,scaley,scalez);
  glRotatef( 180, 1.0, 0.0, 0.0);

  glPushMatrix(); // Draw clock face
  glTranslatef( 0, 0, 1.0);
  glScaled(scalex,scaley,scalez);
  gluDisk(Disk, 0, 6.75, 32, 16);
  glPopMatrix();

  glPushMatrix();// Draw hour hand
  glColor3f(0.95, 0.75, 0.75);
  glTranslatef( 0, 0, 0.0);
  glScaled(scalex,scaley,scalez);
  glRotatef( (360/12) * newtime->tm_hour  + (1/12.0)*6*(newtime->tm_min), 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 2.0);
  glScaled(scalex,scaley,scalez);
  Draw_gear();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  glScaled(scalex,scaley,scalez);
  gluCylinder(Cylinder, 0.75, 0, 4, 16, 16);
  glPopMatrix();

  glPushMatrix();// Draw minute hand
  glColor3f(1.0, 0.5, 1.0);
  glTranslatef( 0, 0, 0.0);
  glScaled(scalex,scaley,scalez);
  glRotatef( (360/60) * newtime->tm_min, 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 3.0);
  glScalef(0.5, 0.5, 1.0);
  glScaled(scalex,scaley,scalez);
  Draw_gear();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  glScaled(scalex,scaley,scalez);
  gluCylinder(Cylinder, 0.5, 0, 6, 16, 16);
  glPopMatrix();

  glPushMatrix();// Draw second hand
  glColor3f(1.0, 0.0, 0.5);
  glTranslatef( 0, 0, -0.0);
  glScaled(scalex,scaley,scalez);
  glRotatef( (360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 4.0);
  glScaled(scalex,scaley,scalez);
  glScalef(0.25, 0.25, 1.0);
  Draw_gear();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  glScaled(scalex,scaley,scalez);
  gluCylinder(Cylinder, 0.25, 0, 6, 16, 16);
  glPopMatrix();

glPushMatrix(); // Draw numbers
  glTranslatef( 0, 0, 0.0);
  glScaled(scalex,scaley,scalez);
  num();
glPopMatrix();


 for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
	  {
	  glPushMatrix();// Draw next arm axis.
      glColor3f(0.10, 0.5, 0.7); // give it a color
	  glTranslatef(0.0, 0.0, 0.0);
	glScaled(scalex,scaley,scalez);
	  glRotatef( ((360/12) * hour_ticks), 0.0, 0.0, 1.0);
      glTranslatef( 6.0, 0.0, 0.0);
	  glutSolidCube(0.75);

      glPopMatrix();
  }

glColor3f(0.10, 0.5, 0.7);

  for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
	 {
   	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
	glScaled(scalex,scaley,scalez);
	glTranslatef(6.0, 0.0, 0.0);
	glutSolidCube(0.25);
	glPopMatrix();
	}


  glPopMatrix();

}




void myKey(unsigned char key, int x, int y)
{
	if(key == '+')
	{
		scalex += 0.1;
		scaley += 0.1;
		scalez += 0.1;
	}
	if(key == '-')
	{
		scalex -= 0.1;
		scaley -= 0.1;
		scalez -= 0.1;
	}
}


void display_clock()
{
	time(&ltime); // Get time
  newtime = localtime(&ltime); // Convert to local time

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // easy way to put text on the screen.
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-8.0, 8.0, -8.0, 8.0, 1.0, 60.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);

  // Put view state on screen
  glColor3f( 1.0, 1.0, 1.0);
  printAt(0,620,"");
  printAt(0,600,"");


      printAt(120,10, asctime(newtime));


 	if (light_state == 1)
	  {
	   glEnable(GL_LIGHTING);
	   glEnable(GL_COLOR_MATERIAL);  // Enable for lighting
      }else
	  {
	  glDisable(GL_LIGHTING);
	  glDisable(GL_COLOR_MATERIAL);  // Disable for lighting
  }

Draw_clock( 0.0, 0.0, -14.0);
glutSwapBuffers();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
	 display_clock();
	 glFlush();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
}

void options(int id)
{
 switch(id)
 {

  case 1:
	  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	about_int= abs(about_int - 1);
	  break;
  case 2:
	  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	   light_state = abs(light_state - 1);
      break;
  case 3 :
	  exit(0);
 }
 }

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (50, 50);
   glutCreateWindow (argv[0]);
   glutSetWindowTitle("GLclock");
   init ();
   glutCreateMenu(options);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(myKey);
   glutTimerFunc( 10, TimeEvent, 1);
   glutMainLoop();
   return 0;
}
