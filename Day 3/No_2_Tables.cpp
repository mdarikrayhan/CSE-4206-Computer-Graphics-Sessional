#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

void triangle(float x1,float y1,float x2,float y2,float x3,float y3)
{
    //the values should be in clockwise order
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex3f(x1, y1, 0);
    glVertex3f(x2, y2, 0);
    glVertex3f(x3, y3, 0);
    glEnd();
}

void rectangle(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float r,float g, float b)
{
    //the values should be in clockwise order
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex3f(x1, y1, 0);
    glVertex3f(x2, y2, 0);
    glVertex3f(x3, y3, 0);
    glVertex3f(x4, y4, 0);
    glEnd();
}

void drawtable(){
    //table top
    rectangle(0,10,20,20,35,17,15,7,1,1,1);

    //table legs
    rectangle(0,0,2,0,2,10,0,10,1,1,1);
    rectangle(18,0,20,0,20,10,18,10,1,1,1);
    rectangle(33,0,35,0,35,17,33,17,1,1,1);
    rectangle(13,0,15,0,15,10,13,10,1,1,1);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    drawtable();
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
