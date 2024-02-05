#include <bits/stdc++.h>
#include <windows.h>
#include <GL/glut.h>
using namespace std;
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
void rectangle(double x, double y, double l, double h, float R, float G, float B)
{
    glBegin(GL_POLYGON);
    {
        glColor3f(R, G, B);
        glVertex2d(x, y);
        glVertex2d(x + l, y);
        glVertex2d(x + l, y + h);
        glVertex2d(x, y + h);
    }
    glEnd();
}
void BangladeshFlag(double x=0, double y=0, double sz=3)
{
    glClear(GL_COLOR_BUFFER_BIT);
    double l = 40, h = 24, pw = 2, ph = 30, bw = 2, bh = 2, nob = 4;
    //glClear(GL_COLOR_BUFFER_BIT);
    l = 10 * sz;
    h = 6 * sz;
    ph = (l / 4) * 4;
    pw = (h / 12);
    bw = pw;
    bh = pw;
    nob = 4;
    rectangle(x, y, l, h, 0, 0.5, 0);                 // flag green part
    circle(l / 2 + x, h / 2 + y, l / 5, 1, 0, 0);     // flag red part
    rectangle(x - pw, y - ph, pw, pw+ph + h, 1, 0.5, 0); // poll with brown color
    for (int i = 1; i <= nob; i++)
    {
        rectangle(x - pw - (bw * i), y - ph - (bh * i), pw + 2 * (bw * i), bh, (0.3 + i * 0.1), 0.5, 0.5); // base
    }
    Sleep(30);
    glEnd();
    glFlush();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    double sz = 3.5;
    BangladeshFlag(0,0,sz);
    /*
    for(sz=0.1;sz<=3.5;sz+=0.1){

        if(sz>=3.3){
            sz=0.1;
        }
    }*/


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
