#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
void display()
{
    //Line

    glBegin(GL_QUADS);//Table
    {
        glColor3f(0,1,0);

        glVertex3f(-30, 10, 0);
        glVertex3f(-21, 15, 0);
        glVertex3f(-1, 15, 0);
        glVertex3f(-11, 10, 0);

        glVertex3f(-29, 0, 0);
        glVertex3f(-29, 10, 0);
        glVertex3f(-28, 10, 0);
        glVertex3f(-28, 0, 0);

        glVertex3f(-21, 3, 0);
        glVertex3f(-21, 12, 0);
        glVertex3f(-20, 12, 0);
        glVertex3f(-20, 3, 0);

        glVertex3f(-12, 0, 0);
        glVertex3f(-12, 10, 0);
        glVertex3f(-11, 10, 0);
        glVertex3f(-11, 0, 0);
        glVertex3f(-2, 3, 0);
        glVertex3f(-2, 15, 0);
        glVertex3f(-3, 15, 0);
        glVertex3f(-3, 3, 0);

        glEnd();
        glFlush();

    }

    glBegin(GL_QUADS);//chair
    {
    glColor3f(1,1,1);

    glVertex3f(3, 10, 0);
    glVertex3f(5, 15, 0);
    glVertex3f(15, 15, 0);
    glVertex3f(17, 10, 0);

    glVertex3f(3, 0, 0);
    glVertex3f(3, 10, 0);
    glVertex3f(4, 10, 0);
    glVertex3f(4, 0, 0);

    glVertex3f(5, 3, 0);
    glVertex3f(5, 32, 0);
    glVertex3f(6, 32, 0);
    glVertex3f(6, 3, 0);

    glVertex3f(16, 0, 0);
    glVertex3f(16, 10, 0);
    glVertex3f(17, 10, 0);
    glVertex3f(17, 0, 0);

    glVertex3f(14, 3, 0);
    glVertex3f(14, 32, 0);
    glVertex3f(15, 32, 0);
    glVertex3f(15, 3, 0);

    glVertex3f(5, 32, 0);
    glVertex3f(5, 30, 0);
    glVertex3f(15, 30, 0);
    glVertex3f(15, 32, 0);

    glVertex3f(5, 28, 0);
    glVertex3f(5, 26, 0);
    glVertex3f(15, 26, 0);
    glVertex3f(15, 28, 0);

    glVertex3f(5, 24, 0);
    glVertex3f(5, 22, 0);
    glVertex3f(15, 22, 0);
    glVertex3f(15, 24, 0);

    glEnd();
    glFlush();
    }
}

void init()
{

    glOrtho(-50.0, 50.0, -50.0, 50.0,-50.0, 50.0);
}

int main(int a, char **b)
{

    glutInit(&a, b);
    glutInitWindowSize(1400,1000);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Table and Chair....");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
