#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
void display(){
    //Chair back
    glColor3f(1,1,1);
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    //surface
    glVertex3f(16, 5, 0);
    glVertex3f(26, 5, 0);
    glVertex3f(31, 10, 0);
    glVertex3f(21, 10, 0);
    //front leg left
    glVertex3f(16, 5, 0);
    glVertex3f(16, -7, 0);
    glVertex3f(17.5, -7, 0);
    glVertex3f(17.5, 5, 0);
    //front leg right
    glVertex3f(26, 5, 0);
    glVertex3f(26, -7, 0);
    glVertex3f(24.5, -7, 0);
    glVertex3f(24.5, 5, 0);
    //back leg right
    glVertex3f(31, 10, 0);
   glVertex3f(31, -2, 0);
    glVertex3f(29.5, -2, 0);
    glVertex3f(29.5, 10, 0);
   //back leg left
    glVertex3f(21, 10, 0);
    glVertex3f(21, -2, 0);
    glVertex3f(22.5, -2, 0);
    glVertex3f(22.5, 10, 0);
    //upper back left
    glVertex3f(21, 10, 0);
    glVertex3f(21, 22, 0);
    glVertex3f(22.5, 22, 0);
    glVertex3f(22.5, 10, 0);
    //upper back right
    glVertex3f(31, 10, 0);
    glVertex3f(31, 22, 0);
    glVertex3f(29.5, 22, 0);
    glVertex3f(29.5, 10, 0);
    //Upper back up
    glVertex3f(29.5, 22, 0);
    glVertex3f(21, 22, 0);
    glVertex3f(21, 20.5, 0);
    glVertex3f(29.5, 20.5, 0);
    //upper back middle
    glVertex3f(21, 17, 0);
    glVertex3f(29.5, 17, 0);
    glVertex3f(29.5, 15.5, 0);
    glVertex3f(21, 15.5, 0);
    glEnd();
    glColor3f(1,0,1);
    glColor3f(0.7, 0.9, 0.7);
    glBegin(GL_QUADS);
    glVertex3f(16, 5, 0);
    glVertex3f(26, 5, 0);
    glVertex3f(26, 3.5, 0);
    glVertex3f(16, 3.5, 0);
    glEnd();
    glColor3f(0.7, 0.9, 0.7);
    glBegin(GL_QUADS);
    glVertex3f(26, 5, 0);
    glVertex3f(29.5, 8.5, 0);
    glVertex3f(29.5, 7.0, 0);
    glVertex3f(26, 3.5, 0);
    glEnd();
    //Chair left
    glColor3f(0,0,0);
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    //surface
    glVertex3f(-4, 0, 0);
    glVertex3f(6, 0, 0);
    glVertex3f(11, 5, 0);
    glVertex3f(1, 5, 0);
    //front leg left
    glVertex3f(-4, 0, 0);
    glVertex3f(-4, -12, 0);
    glVertex3f(-2.5, -12, 0);
    glVertex3f(-2.5, 0, 0);
    //front leg right
    glVertex3f(6, 0, 0);
    glVertex3f(6, -12, 0);
    glVertex3f(4.5, -12, 0);
    glVertex3f(4.5, 0, 0);
    //back leg right
    glVertex3f(11, 5, 0);
    glVertex3f(11, -7, 0);
    glVertex3f(9.5, -7, 0);
    glVertex3f(9.5, 5, 0);
    //back leg left
    glVertex3f(1, 5, 0);
    glVertex3f(1, -7, 0);
    glVertex3f(2.5, -7, 0);
    glVertex3f(2.5, 5, 0);
    //upper back left
    glVertex3f(-4, 0, 0);
    glVertex3f(-4, 15, 0);
    glVertex3f(-2.5, 15, 0);
    glVertex3f(-2.5, 0, 0);
    //upper back right
    glVertex3f(1, 5, 0);
    glVertex3f(1, 20, 0);
    glVertex3f(2.5, 20, 0);
    glVertex3f(2.5, 5, 0);
    //upper back up
    glVertex3f(-4, 15, 0);
    glVertex3f(1, 20, 0);
    glVertex3f(1, 18, 0);
    glVertex3f(-4, 13, 0);
    //upper back middle
    glVertex3f(-4, 8, 0);
    glVertex3f(1, 13, 0);
    glVertex3f(1, 11, 0);
    glVertex3f(-4, 6, 0);
    glEnd();
    //front color
    glBegin(GL_QUADS);
    glVertex3f(-4, 0, 0);
    glVertex3f(6, 0, 0);
    glVertex3f(6, -1.5, 0);
    glVertex3f(-4, -1.5, 0);
    //side color
    glVertex3f(6, 0, 0);
    glVertex3f(11, 5, 0);
    glVertex3f(11, 3.5, 0);
    glVertex3f(6, -1.5, 0);
    glEnd();

    //Chair right
    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    //surface
    glVertex3f(31, -5, 0);
    glVertex3f(41, -5, 0);
    glVertex3f(46, 0, 0);
    glVertex3f(36, 0, 0);
    //front leg left
    glVertex3f(31, -5, 0);
    glVertex3f(31, -17, 0);
    glVertex3f(32.5, -17, 0);
    glVertex3f(32.5, -5, 0);
    //front leg right
    glVertex3f(41, -5, 0);
    glVertex3f(41, -17, 0);
    glVertex3f(39.5, -17, 0);
    glVertex3f(39.5, -5, 0);
    //back leg right
    glVertex3f(46, 0, 0);
    glVertex3f(46, -12, 0);
    glVertex3f(44.5, -12, 0);
    glVertex3f(44.5, 0, 0);
    //back leg left
    glVertex3f(36, 0, 0);
    glVertex3f(36, -12, 0);
    glVertex3f(37.5, -12, 0);
    glVertex3f(37.5, 0, 0);
    //upper back left
    glVertex3f(41, -5, 0);
    glVertex3f(41, 10, 0);
    glVertex3f(39.5, 10, 0);
    glVertex3f(39.5, -5, 0);
    //upper back right
    glVertex3f(46, 0, 0);
    glVertex3f(46, 15, 0);
    glVertex3f(44.5, 15, 0);
    glVertex3f(44.5, 0, 0);
    //upper up
    glVertex3f(41, 10, 0);
    glVertex3f(39.5, 10, 0);
    glVertex3f(44.5, 15, 0);
    glVertex3f(46, 15, 0);
    //upper middle
    glVertex3f(41, 5, 0);
    glVertex3f(46, 10, 0);
    glVertex3f(46, 8, 0);
    glVertex3f(41, 3, 0);
    glEnd();

    glBegin(GL_QUADS);
    //front color
    glVertex3f(31, -5, 0);
    glVertex3f(41, -5, 0);
    glVertex3f(41, -6.5, 0);
    glVertex3f(31, -6.5, 0);
    //side color
    glVertex3f(41, -5, 0);
    glVertex3f(46, 0, 0);
    glVertex3f(46, -1.5, 0);
    glVertex3f(41, -6.5, 0);
    glEnd();

    //Table
    glColor3f(0,0,0);
    glColor3f(0.7, 0.6, 0.5);
    glBegin(GL_QUADS);
    //Surface
    glVertex3f(0, 0, 0);
    glVertex3f(30, 0, 0);
    glVertex3f(40, 10, 0);
    glVertex3f(10, 10, 0);
    //Front leg left
    glVertex3f(0, 0, 0);
    glVertex3f(0, -20, 0);
    glVertex3f(2, -20, 0);
    glVertex3f(2, 0, 0);
    //front leg right
    glVertex3f(30, 0, 0);
    glVertex3f(30, -20, 0);
    glVertex3f(28, -20, 0);
    glVertex3f(28, 0, 0);
    //back leg right
    glVertex3f(39.5, 10, 0);
    glVertex3f(39.5, 0, 0);
    glVertex3f(37.5, 0, 0);
    glVertex3f(37.5, 10, 0);
    glVertex3f(39.5, -6.5, 0);
    glVertex3f(39.5, -10, 0);
    glVertex3f(37.5, -10, 0);
    glVertex3f(37.5, -6.5, 0);

    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    glVertex3f(10, -2, 0);
    glVertex3f(0, -2, 0);
    glVertex3f(20, 0, 0);
    glVertex3f(30, 0, 0);
    glVertex3f(30, -2, 0);
    glVertex3f(20, -2, 0);
    glEnd();

    glColor3f(1,1,1);
    glColor3f(0.7, 0.6, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(30, -2, 0);
    glVertex3f(39.5, 7.5, 0);
    glVertex3f(39.5, 9.5, 0);
    glVertex3f(30, 0, 0);
    glEnd();
    glEnd();
    glFlush();
}
void init()
{
    glOrtho(-50.0,50.0,-50.0,50.0,-50.0,50.0);
}
int main(int a,char **b)
{
    glutInit(&a,b);
    glutInitWindowSize(1400,1000);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Table and Chair :");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
