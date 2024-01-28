#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

void triangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(20, 40, 0);
    glVertex3f(40, 0, 0);
    glEnd();
}
void rectangle()
{
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(10, 5, 0);//left line
    glVertex3f(10, 20, 0);//up line
    glVertex3f(30, 20, 0);//right line
    glVertex3f(30, 5, 0);// bottom line
    glEnd();
}
void line()
{
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(15, 12.5f, 0);
    glVertex3f(25, 12.5f, 0);
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    triangle();
    rectangle();
    line();
    glFlush();
}
void init()
{
    glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
}
int main(int a, char **b)
{
    glutInit(&a, b);
    glutInitWindowSize(1400, 1000);
    glutInitWindowPosition(0, 0);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("basic object....");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
