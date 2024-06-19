#include<windows.h>
#include<GL/glut.h>
#include<cmath>
char title[]="Basic Code";
double rotate_c=0;
double rotate_d=0;
float x,y,z=-7,sx=1,sy=1,sz=1;
void Panorama()

{
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslated(x,y,z);
    glRotatef( rotate_c, 1.0, 0.0, 0.0);
    glRotatef( rotate_d, 0.0, 1.0, 0.0);
    glScaled(sx, sy, sz);

    glPushMatrix();

    glBegin(GL_QUADS);
    {

        glColor3f(0.25,0.50,1.75);
        glVertex3f(-1.5,2.5,-15);
        glVertex3f(1.5,2.5,-15);
        glVertex3f(1.5,-1.5,-10);
        glVertex3f(-1.5,-1.5,-10);

        glEnd();

        glPopMatrix();
        glutSwapBuffers();


    }
}

void reshape(GLsizei width,GLsizei height)
{
    if(height == 0) height =1;
    GLfloat aspect =(GLfloat)width/(GLfloat)height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,aspect,0.1f,100.0f);

}
float move_unit=0.05;
void windowKey(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'C':
        z+=move_unit;
        break;

    case 'D':
        z-=move_unit;
        break;

    case 'A':
        sx*=2;
        break;

    case 'B':
        sx*=move_unit;;
        break;
    case 'X':
        rotate_c+= 5;
        break;
    case 'Y':
        rotate_d+= 5;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1500,1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(title);
    glutDisplayFunc(Panorama);
    glutKeyboardFunc(windowKey);
    glutReshapeFunc(reshape);
    glutMainLoop();

}
