#include <bits/stdc++.h>
#include <windows.h>
#include <GL/glut.h>

char title[] = "Sahid Minar";
float x = 0, y = 0, z = -7;

void circle(double x, double y, double r, float R, float G, float B)
{
    glBegin(GL_POLYGON);
    {
        glColor3f(R, G, B);
        for (int i = 0; i <= 360; i++)
        {
            glVertex2d(x + r * sin(i), y + r * cos(i));
        }
    }
    glEnd();
}

void rectangle(double x, double y, double l, double h, float R, float G, float B,float z1,float z2)
{
    glBegin(GL_QUADS);
    {
        glColor3f(R, G, B);
        glVertex3f(x, y,z1);
        glVertex3f(x + l, y,z1);
        glVertex3f(x + l, y + h,z2);
        glVertex3f(x, y + h,z2);
    }
    glEnd();
}
void Base()
{
    glMatrixMode(GL_MODELVIEW);
    glTranslated(x, y, z);
    // rectangle(-1.5,-1.5,3,4,0.75,0.75,2.75,-5,0);
    rectangle(-3,-1,6,2,.825,.70,.54,0,-15);//floor
    rectangle(-3,-1.3,6,0.3,1,1,1,0,0);//floor


    rectangle(-6,-2,1,8,1,1,1,-25,-25);//left Pilar
    rectangle(-2,-2,1,8,1,1,1,-25,-25);//right pilar
    rectangle(-6,6,5,1,1,1,1,-25,-25);

    rectangle(-4.7,-2,.2,8,1,1,1,-25,-25);//thin 1
    rectangle(-4.2,-2,.2,8,1,1,1,-25,-25);//thin 1
    rectangle(-3.7,-2,.2,8,1,1,1,-25,-25);//thin 1
    rectangle(-3.2,-2,.2,8,1,1,1,-25,-25);//thin 1
    rectangle(-2.7,-2,.2,8,1,1,1,-25,-25);//thin 1
    rectangle(-2.2,-2,.2,8,1,1,1,-25,-25);//thin 1

    rectangle(0.5,-2,3.5,12,1,1,1,-25,-25);//right pilar

    circle(-0.8, 0.60,0.4,.5, 0, 0);//circle

    glEnd();
    glutSwapBuffers();
}

void display()
{
    Base();
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0)
        height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1500, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(title);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
