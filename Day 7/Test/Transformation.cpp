#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <windows.h>
#include<GL/gl.h>
#include <GL/glut.h>

#define PI 3.14159265
#define CTRL_COUNT 100

int ctrlPointsCount;
int ctrlPointsX[CTRL_COUNT], ctrlPointsY[CTRL_COUNT];
int X1[3]= {20,25,20}, Y1[3]= {5,24,38};
int X2[3]= {0,-5,0}, Y2[3]= {1,static_cast<int>(0.5),0};
int X3[3]= {22,0,18}, Y3[3]= {30,38,45};
int X4[3]= {28,50,32}, Y4[3]= {30,38,45};
int X5[3]= {18,25,32}, Y5[3]= {45,60,45};
double var = -6;
double rainX = -6;
double rainY;

bool Rain = false;
bool night = false;

//colors  variables
double sky[3] = {19,190,242};
double cloud[3] = {255,255,255};
double sun[3] = {219,230,21};
double tree[3] = {34, 139, 34};
double bush[3] = {127,162,12};
double soil[3] = {199,192,141};
double cowFood[3] = {235,222,164};
double water[3] = {152,222,245};
double building3[3] = {102,102,102};
double building2[3] = {217,217,50};
double building1Box2[3] = {237,237,187};
double building1Box3[3] = {30,186,79};


using namespace std;

double train = 0;
double car1 = 0;
double car2 = 0;
double fly = 0;
double ship = 0;
double ship2 = 0;
double rain = 0;

GLuint LoadTexture(const char * filename)
{
    GLuint texture;
    int width, height;
    unsigned char * data;
    FILE * file;
    file = fopen(filename, "Rb");
    if (file == NULL)
        return 0;
    width = 1024;
    height = 512;
    data = (unsigned char *)malloc(width * height * 3);

    fread(data, width * height * 3, 1, file);
    fclose(file);

    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];
        data[index] = R;
        data[index + 2] = B;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);

    return texture;
}

void draw_cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R,G,B);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < 2*3.1416 )
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*3.1416 )
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}


void drawCloud()
{
    glutSolidSphere(0.4,40,40);
    glScalef(1,0.4,1);
    glTranslatef(-0.1,0,0);
    glBegin(GL_POLYGON);
    glColor3ub(cloud[0], cloud[1], cloud[2]);
    glutSolidSphere(0.7,40,40);
}


void drawTree()
{
    //Tree
    glColor3ub(tree[0], tree[1], tree[2]);

    glPushMatrix();
    glutSolidSphere(0.25,40,40);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15,-0.15,0);
    glutSolidSphere(0.25,40,40);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.15,-0.15,0);
    glutSolidSphere(0.25,40,40);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.3,0);
    glRotatef(90,1,0,0);
    draw_cylinder(0.04,0.7,137, 94, 41);
    glPopMatrix();
}


void drawBush()
{
    glBegin(GL_TRIANGLES);
    glColor3ub(bush[0],bush[1],bush[2]);
    glVertex3f(0,0,0);
    glVertex3f(0.3,0,0);
    glVertex3f(0.4,0.6,0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(bush[0],bush[1],bush[2]);
    glVertex3f(0.2,0,0);
    glVertex3f(0.5,0,0);
    glVertex3f(0.55,0.4,0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(bush[0],bush[1],bush[2]);
    glVertex3f(-0.1,0,0);
    glVertex3f(0.1,0,0);
    glVertex3f(0.2,0.5,0);
    glEnd();

}

void bezierCoefficients(int n,int *c)
{

    int k,i;
    for(k=0; k<=n; k++)
    {
        c[k]=1;
        for(i=n; i>=k+1; i--)
            c[k]*=i;
        for(i=n-k; i>=2; i--)
            c[k]/=i;
    }

}

void drawCurve()
{
    glPushMatrix();
    int cp[4][2]= {{10,10},{100,200},{200,50},{300,300}};
    int c[4],k,n=3;
    float x,y,u,blend;

    bezierCoefficients(n,c);

    glColor3f(1.0,0.0,0.0);
    glLineWidth(20.0);
    glBegin(GL_LINE_STRIP);
    for(u=0; u<1.0; u+=0.01)
    {
        x=0;
        y=0;
        for(k=0; k<4; k++)
        {
            blend=c[k]*pow(u,k)*pow(1-u,n-k);
            x+=cp[k][0]*blend;
            y+=cp[k][1]*blend;
        }
        glVertex2f(x,y);


    }

    glEnd();
    glPopMatrix();
}


void drawEllipse(void)
{
    GLint i;
    GLfloat xradius=3.5;
    GLfloat yradius=2;
    const GLfloat DEG2RAD = 3.14159/180;

    glColor3ub(23,145,62);

    glBegin(GL_POLYGON);
    for (i=0; i < 360; i++)
    {
        float degInRad = i*DEG2RAD;
        glVertex2f ( cos (degInRad) *xradius,  sin (degInRad) *yradius);
    }
    glEnd();
}

void drawRedEllipse(void)
{
    GLint i;
    GLfloat xradius=3.5;
    GLfloat yradius=2;
    const GLfloat DEG2RAD = 3.14159/180;

    glColor3ub(242,46,49);

    glBegin(GL_POLYGON);
    for (i=0; i < 360; i++)
    {
        float degInRad = i*DEG2RAD;
        glVertex2f ( cos (degInRad) *xradius,  sin (degInRad) *yradius);
    }
    glEnd();
}

void drawFlower()
{
    glPushMatrix() ;
    glTranslatef(5,5,1) ;
    glRotatef(90,0,0,1) ;
    glColor3ub(23,145,62);
    drawEllipse() ;
    glPopMatrix() ;

    //right petal
    glPushMatrix() ;
    glTranslatef(1.25, 7.5,1);
    glRotatef(20,0,0,1) ;
    glScalef(1.1,1.1, 0.0);
    glColor3ub(23,145,62);
    drawEllipse() ;
    glPopMatrix() ;

    //left petal
    glPushMatrix() ;
    glTranslatef(8.7, 7.5,1) ;
    glRotatef(160,0,0,1) ;
    glScalef(1.1,1.1, 0.0);
    glColor3ub(23,145,62);
    drawEllipse() ;
    glPopMatrix() ;

}


void drawRedFlower()
{

    glPushMatrix() ;
    glTranslatef(5,5,1) ;
    glRotatef(90,0,0,1) ;
    glScalef(1.1,1.1, 0.0);
    glColor3ub(23,145,62);
    drawRedEllipse() ;
    glPopMatrix() ;

    //right petal
    glPushMatrix() ;
    glTranslatef(1.25, 7.5,1);
    glRotatef(20,0,0,1) ;
    glScalef(1.1,1.1, 0.0);
    glColor3ub(23,145,62);
    drawRedEllipse() ;
    glPopMatrix() ;

    //left petal
    glPushMatrix() ;
    glTranslatef(8.7, 7.5,1) ;
    glRotatef(160,0,0,1) ;
    glScalef(1.1,1.1, 0.0);
    glColor3ub(23,145,62);
    drawRedEllipse() ;
    glPopMatrix() ;
}

void dp(GLint cx,GLint cy)
{

    glColor3ub(237,52,52);
    glBegin(GL_POINTS);
    glVertex2i(cx,cy);
    glEnd();

}

void pix(GLint h,GLint k,GLint x,GLint y)
{
    glColor3ub(237,52,52);
    dp(x+h,y+k);
    dp(x+h,-y+k);
    dp(-x+h,-y+k);
    dp(-x+h,y+k);
    dp(y+h,x+k);
    dp(y+h,-x+k);
    dp(-y+h,-x+k);
    dp(-y+h,x+k);

}
void cd(GLint h,GLint k,GLint r)
{
    glColor3ub(237,52,52);
    GLint d=1-r,x=0,y=r;
    while(y>x)
    {
        pix(h,k,x,y);
        if(d<0)
            d+=2*x+3;
        else
        {
            d+=2*(x-y)+5;
            --y;
        }
        ++x;
    }
    pix(h,k,x,y);
}

void drawHeli()
{
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(0.01,0.01,1);

    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(0.3,0.3,1);
    glColor3ub(237,52,52);

    //*************************Body Of HELICOPTER*************************************

    glBegin(GL_POLYGON);
    glColor3ub(23,40,230);
    glVertex2i(20,850);
    glVertex2i(30,820);
    glVertex2i(100,820);
    glVertex2i(110,800);
    glVertex2i(200,800);
    glVertex2i(200,815);
    glVertex2i(190,830);
    glVertex2i(180,830);
    glVertex2i(170,860);
    glVertex2i(155,860);
    glVertex2i(150,870);
    glVertex2i(135,860);
    glVertex2i(115,860);
    glVertex2i(100,825);
    glVertex2i(30,850);
    glEnd();

    //********************End of Body of Helicopter****************


    //**********************************Tire, Tail and Fan of Helicopter***************************************
    cd(142,890,20);
    cd(170,790,5);
    cd(130,790,5);
    cd(22,850,10);
    //**********************************End of Tire, Tail and Fan of Helicopter***************************************

    //*****************************************Bullets of Helicopter*************************************************
    glBegin(GL_TRIANGLES);
    glVertex2i(200,800);
    glVertex2i(200,815);
    glVertex2i(215,808);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2i(200,800);
    glVertex2i(200,815);
    glVertex2i(215,808);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2i(200,800);
    glVertex2i(200,815);
    glVertex2i(215,808);
    glEnd();
    glPopMatrix();


    glPopMatrix();
}



void drawRoad()
{
    glPushMatrix();
    glTranslatef(0,-0.08,-0.25);
    glScalef(25,0.8,1);
    glColor3ub(128,128,128);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.06,0);

    glPushMatrix();
    glTranslatef(-1,0,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,0,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,0,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,0,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5,0,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,0,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,0,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3,0,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPopMatrix();
}



void drawPlane()
{
    //body
    glPushMatrix();
    glTranslatef(0,-1,0);
    glScalef(5,0.8,0.1);
    glColor3f(1,1,1);
    glutSolidCube(0.2);
    glPopMatrix();

    //head
    glPushMatrix();
    glTranslatef(0.5,-0.92,0);
    glScalef(0.15,0.16,1);
    glRotatef(90,0,0,-1);
    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(0.5,1,0);
    glEnd();
    glPopMatrix();

    //tail
    glPushMatrix();
    glTranslatef(-0.5,-0.92,0);
    glScalef(0.2,0.2,1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glVertex3f(0.3,1,0);
    glVertex3f(1,0,0);
    glEnd();
    glPopMatrix();

    //left wing
    glPushMatrix();
    glTranslatef(0,-0.92,0);
    glScalef(0.2,0.3,1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(0.2,1,0);
    glVertex3f(-0.5,1,0);
    glEnd();
    glPopMatrix();

    //left wing
    glPushMatrix();
    glTranslatef(-0.1,-1.48,0);
    glScalef(0.2,0.4,1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(0.7,0,0);
    glVertex3f(1.5,1,0);
    glVertex3f(0.5,1,0);
    glEnd();
    glPopMatrix();


}

void drawRainbow()
{
    float i;
    float px = -0.2;
    float py = -0.5;
    float side_length = -0.7;
    float r = 1.625; // sculling constant for a 500:800
    float sectx = px+side_length;
    float secty = py;
    float topx =  px+(side_length/2.0);
    float topy =  (py+side_length*-0.866*r);


    float hit = 0.7; // Where to hit [0,1]


    // `cept` is computing where the light ray will hit the prism
    float ceptx =sectx-(hit*(side_length/2.0));
    float cepty =-1.73205*r*hit*(side_length/2.0)+py;

    // These are the parameters for the spread of the inside refraction
    hit = 0.4; // Where to on the right side, [0,1]
    float exitxU = (px+side_length/2.0)-hit*side_length/2.0;
    float exityU = (-1.73205*r*(1-hit)*(side_length/2.0))+py;
    hit=0.1;  // Try changing this number
    float exitxL=(px+side_length/2.0)-hit*side_length/2.0;
    float exityL=(-1.73205*r*(1-hit)*(side_length/2.0))+py;


    // #Draw the rainbow tail
    // The rainbow is made of 50 small rectangles that have rainbow shading. They are painted one after the other but the y coordinate is mapped to a sine wave. The height of the rainbow slices are based on the refraction triangle boundaries in the prism.
    float dx=exitxL;
    float dy=exityL;
    float w=0.014;
    float step=(exityL-exityU)/5.0;
    for(i=0; i<50; i++)
    {
        glBegin(GL_QUAD_STRIP);

        glColor3f(1,0,0);
        glVertex2f(dx,dy);
        glVertex2f(dx+w,dy);

        glColor3f(1,0.6,0);
        glVertex2f(dx,dy-step);
        glVertex2f(dx+w,dy-step);

        glColor3f(1,1,0);
        glVertex2f(dx,dy-step*2);
        glVertex2f(dx+w,dy-step*2);

        glColor3f(0.2,1,0);
        glVertex2f(dx,dy-step*3);
        glVertex2f(dx+w,dy-step*3);

        glColor3f(0,0.6,1);
        glVertex2f(dx,dy-step*4);
        glVertex2f(dx+w,dy-step*4);

        glColor3f(0.4,0.2,1);
        glVertex2f(dx,dy-step*5);
        glVertex2f(dx+w,dy-step*5);
        glEnd();

        dx+=w;
        dy+=0.01*sin(i*3.14/5.0);

    }
}


void drawRain()
{
    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,-0.1,0);
        glVertex3f(rainX,-0.2,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,-0.4,0);
        glVertex3f(rainX,-0.5,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,-0.7,0);
        glVertex3f(rainX,-0.8,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,-1,0);
        glVertex3f(rainX,-1.1,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,-1.3,0);
        glVertex3f(rainX,-1.4,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,-1.6,0);
        glVertex3f(rainX,-1.7,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,-1.9,0);
        glVertex3f(rainX,-2,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,0.1,0);
        glVertex3f(rainX,0.2,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,0.4,0);
        glVertex3f(rainX,0.5,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,0.7,0);
        glVertex3f(rainX,0.8,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,1,0);
        glVertex3f(rainX,1.1,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,1.3,0);
        glVertex3f(rainX,1.4,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,1.6,0);
        glVertex3f(rainX,1.7,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;

    for(int i=0; i<100; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(rainX,1.9,0);
        glVertex3f(rainX,2,0);
        glEnd();
        rainX += 0.1;
    }

    rainX = -6;
}


void drawBird()
{
    glPushMatrix();
    int i;

    GLfloat mm=0.182f;
    GLfloat nn=.801f;
    GLfloat radiusmm =.01f;
    int triangleAmount = 100;
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(225, 225, 208);
    glVertex2f(mm, nn); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            mm + (radiusmm * cos(i *  twicePi / triangleAmount)),
            nn + (radiusmm * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(225, 225, 208 );
    glVertex2f(0.1f,0.8f);
    glVertex2f(0.11f,0.79f);
    glVertex2f(0.12f,0.78f);
    glVertex2f(0.16f,0.77f);
    glVertex2f(0.19f,0.79f);
    glVertex2f(0.201f,0.8f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(217, 217, 217);
    glVertex2f(0.175f,0.8f);
    glVertex2f(0.15f,0.8f);
    glVertex2f(0.14f,0.84f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3ub(242, 242, 242 );
    glVertex2f(0.175f,0.8f);
    glVertex2f(0.144f,0.8f);
    glVertex2f(0.12f,0.83f);
    glEnd();
    /////2nd bird////
    glBegin(GL_POLYGON);
    glColor3ub(225, 225, 208 );
    glVertex2f(-0.02f,0.8f);
    glVertex2f(-0.01f,0.79f);
    glVertex2f(0.0f,0.78f);
    glVertex2f(0.04f,0.77f);
    glVertex2f(0.07f,0.79f);
    glVertex2f(0.081f,0.8f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(217, 217, 217);
    glVertex2f(0.055f,0.8f);
    glVertex2f(0.03f,0.8f);
    glVertex2f(0.02f,0.84f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3ub(242, 242, 242 );
    glVertex2f(0.055f,0.8f);
    glVertex2f(0.024f,0.8f);
    glVertex2f(0.0f,0.83f);
    glEnd();

    GLfloat mmm=0.062f;
    GLfloat nnn=.801f;
    GLfloat radiusmmm =.01f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(225, 225, 208);
    glVertex2f(mmm, nnn); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            mmm + (radiusmmm * cos(i *  twicePi / triangleAmount)),
            nnn + (radiusmmm * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    /////3rd bird/////
    glBegin(GL_POLYGON);
    glColor3ub(225, 225, 208 );
    glVertex2f(-0.72f,0.8f);
    glVertex2f(-0.71f,0.79f);
    glVertex2f(-0.7f,0.78f);
    glVertex2f(-0.66f,0.77f);
    glVertex2f(-0.63f,0.79f);
    glVertex2f(-0.619f,0.8f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(217, 217, 217);
    glVertex2f(-0.645f,0.8f);
    glVertex2f(-0.67f,0.8f);
    glVertex2f(-0.68f,0.84f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(242, 242, 242 );
    glVertex2f(-0.645f,0.8f);
    glVertex2f(-0.676f,0.8f);
    glVertex2f(-0.7f,0.83f);
    glEnd();

    GLfloat mmmm=-0.638f;
    GLfloat nnnn=.801f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(225, 225, 208);
    glVertex2f(mmmm,nnnn); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            mmmm + (radiusmmm * cos(i *  twicePi / triangleAmount)),
            nnnn + (radiusmmm * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    ////4th bird////
    GLfloat mmmmm=-0.518f;
    GLfloat nnnnn=.801f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(225, 225, 208);
    glVertex2f(mmmmm, nnnnn); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            mmmmm + (radiusmm * cos(i *  twicePi / triangleAmount)),
            nnnnn + (radiusmm * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(225, 225, 208 );
    glVertex2f(-0.6f,0.8f);
    glVertex2f(-0.59f,0.79f);
    glVertex2f(-0.58f,0.78f);
    glVertex2f(-0.54f,0.77f);
    glVertex2f(-0.51f,0.79f);
    glVertex2f(-0.499f,0.8f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(217, 217, 217);
    glVertex2f(-0.525f,0.8f);
    glVertex2f(-0.55f,0.8f);
    glVertex2f(-0.56f,0.84f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(242, 242, 242 );
    glVertex2f(-0.525f,0.8f);
    glVertex2f(-0.556f,0.8f);
    glVertex2f(-0.58f,0.83f);
    glEnd();
    glPopMatrix();

}

void drawBird2()
{
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(1, 0.5, 0);
    glVertex3f(1, 0.5, 0);
    glVertex3f(0, 1, 0);
    glEnd();
    glPopMatrix();
}



//Initializes 3D rendering
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;

//Draws the 3D scene
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units

    //Sky
    glPushMatrix();
    glScalef(7,3,2);
    glTranslatef(0,1.21,0);
    glColor3ub(sky[0], sky[1], sky[2]);
    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glEnd();
    glPopMatrix();

    //Ground
    glPushMatrix();
    glTranslatef(0,-3.68,0);
    glScalef(6,4,1);
    glColor3ub(soil[0],soil[1],soil[2]);
    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glEnd();
    glPopMatrix();

    //SUN
    glPushMatrix();
    glTranslatef(0,-_angle,0);
    glTranslatef(4,3,0);
    glScalef(1,1,0.1);
    glColor3ub(sun[0], sun[1], sun[2]);
    glutSolidSphere(0.4,40,40);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(_angle,0,0);

    //Cloud
    glPushMatrix();
    glColor3ub(cloud[0], cloud[1], cloud[2]);
    glTranslatef(-1,2.3,0);
    drawCloud();
    glPopMatrix();

    //Cloud
    glPushMatrix();
    glColor3ub(cloud[0], cloud[1], cloud[2]);
    glScalef(0.7,0.7,1);
    glTranslatef(1,2.5,0);
    drawCloud();
    glPopMatrix();

    //Cloud
    glPushMatrix();
    glColor3ub(cloud[0], cloud[1], cloud[2]);
    glScalef(0.7,0.7,1);
    glTranslatef(1,2.5,0);
    drawCloud();
    glPopMatrix();


    //Cloud
    glPushMatrix();
    glColor3ub(cloud[0], cloud[1], cloud[2]);
    glScalef(0.7,0.7,1);
    glTranslatef(2.6,2.7,0);
    drawCloud();
    glPopMatrix();


    //Cloud
    glPushMatrix();
    glColor3ub(cloud[0], cloud[1], cloud[2]);
    glTranslatef(-3.6,2.0,0);
    drawCloud();
    glPopMatrix();

    glPopMatrix();
    glTranslatef(0,0,0.1);

    //tree
    glPushMatrix();
    glScalef(0.7,0.7,1);
    glTranslatef(-4,1.4,0);
    drawTree();
    glPopMatrix();

    //tree
    glPushMatrix();
    glScalef(0.7,0.7,1);
    glTranslatef(-6,1.4,0);
    drawTree();
    glPopMatrix();

    //tree
    glPushMatrix();
    glScalef(0.7,0.7,1);
    glTranslatef(-5.5,1.4,0);
    drawTree();
    glPopMatrix();

    //tree
    glPushMatrix();
    glScalef(0.7,0.7,1);
    glTranslatef(0,1.4,0);
    drawTree();
    glPopMatrix();

    //tree
    glPushMatrix();
    glScalef(0.7,0.7,1);
    glTranslatef(-1,1.4,0);
    drawTree();
    glPopMatrix();

    //tree
    glPushMatrix();
    glScalef(0.7,0.7,1);
    glTranslatef(2,1.4,0);
    drawTree();
    glPopMatrix();

    //tree
    glPushMatrix();
    glScalef(0.7,0.7,1);
    glTranslatef(4,1.4,0);
    drawTree();
    glPopMatrix();



    //tree
    glPushMatrix();
    glScalef(0.7,0.7,1);
    glTranslatef(6,1.4,0);
    drawTree();
    glPopMatrix();



    //tree
    glPushMatrix();

    glScalef(0.7,0.7,1);
    glTranslatef(6.5,1.4,0);
    drawTree();
    glPopMatrix();



    //tree
    glPushMatrix();
    glTranslatef(-2,1,0);
    glScalef(0.7,0.7,1);
    drawTree();
    glPopMatrix();

    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(-5,0.3,0);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(-4.5,0.3,0);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(-3.5,0.3,0);
    glScalef(0.8,0.8,1);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(-3,0.3,0);
    glScalef(1.5,1.5,1);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(-1.5,0.3,0);
    glScalef(1,2,1);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(-1,0.3,0);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(2,0.3,0);
    glScalef(1,2,1);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(2.5,0.3,0);
    glScalef(1,2,1);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(3.5,0.3,0);
    glScalef(0.8,0.8,1);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(4,0.3,0);
    glScalef(0.8,0.8,1);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(0,0.3,0);
    glScalef(0.8,0.8,1);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(0.3,0.3,0);
    glScalef(0.8,0.8,1);
    drawBush();
    glPopMatrix();

    //bush
    glPushMatrix();
    glTranslatef(0.6,0.3,0);
    glScalef(1,1.3,1);
    drawBush();
    glPopMatrix();

    //Train
    glPushMatrix();
    glScalef(0.2, 0.2, 0.1);
    glTranslatef(9, 2.5, 1);
    glTranslatef(-train, 0, 0);
    glPopMatrix();

    //house 1
    glPushMatrix();
    glTranslatef(-3,-1,0.5);
    glScalef(0.7,0.7,1);
    glPopMatrix();

    //house 2
    glPushMatrix();
    glTranslatef(-3.8,-1,0);
    glScalef(0.7,0.7,1);
    glPopMatrix();

    //house3
    glPushMatrix();
    glTranslatef(-4,-1.3,0.5);
    glScalef(0.7,0.7,1);
    glPopMatrix();


    //tree
    glPushMatrix();
    glTranslatef(-3.5,-0.5,0.5);
    glScalef(0.8,0.8,1);
    drawTree();
    glPopMatrix();

    //tree
    glPushMatrix();
    glTranslatef(-3.2,-0.8,0.5);
    glScalef(0.8,0.8,1);
    drawTree();
    glPopMatrix();

    //circle tree
    glPushMatrix();
    glTranslatef(-5,-0.95,0);
    glScalef(1,1,0.2);
    glColor3ub(38, 171, 80);
    glutSolidSphere(0.55,40,40);
    glPopMatrix();

    //circle tree 2
    glPushMatrix();
    glTranslatef(-4.5,-0.9,0);
    glScalef(1,1,0.1);
    glColor3ub(14, 125, 49);
    glutSolidSphere(0.55,40,40);
    glPopMatrix();

    //Building
    glPushMatrix();
    glTranslatef(2.8,-0.5,1);
    glScalef(0.003,0.003,1);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.24,0.8,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.43,0.8,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.24,0.45,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.43,0.45,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.24,0.07,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.43,0.07,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.24,-0.15,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.43,-0.15,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();


    //2nd building

    glPushMatrix();
    glTranslatef(0.47,0,0);

    glPushMatrix();
    glTranslatef(3.24,0.8,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.43,0.8,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.24,0.45,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.43,0.45,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.24,0.07,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.43,0.07,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.24,-0.15,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    //buiding 1 WIndow
    glPushMatrix();
    glTranslatef(3.43,-0.15,1);
    glColor3f(1,1,1);
    glScalef(1,1,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    glPopMatrix();


    //building 3 windows
    glPushMatrix();
    glTranslatef(0,0.1,0);

    glPushMatrix();
    glTranslatef(4.25,-0.15,1);
    glColor3f(1,1,1);
    glScalef(1,1.5,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.25,0.15,1);
    glColor3f(1,1,1);
    glScalef(1,1.5,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.25,0.45,1);
    glColor3f(1,1,1);
    glScalef(1,1.5,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.25,0.75,1);
    glColor3f(1,1,1);
    glScalef(1,1.5,0.1);
    glutSolidCube(0.12);
    glPopMatrix();

    glPopMatrix();

    //water circle
    glPushMatrix();
    glColor3ub(water[0],water[1],water[2]);
    glTranslatef(4.5,-3,1.2);
    glScalef(1.3,0.8,0.1);
    glutSolidSphere(3,80,80);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(140,82,41);
    glTranslatef(4.5,-3,0);
    glScalef(1.3,0.8,0.1);
    glutSolidSphere(3.5,80,80);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(163,147,135);
    glTranslatef(4.5,-3,1.1);
    glScalef(1.3,0.8,0.1);
    glutSolidSphere(3.2,80,80);
    glPopMatrix();


    //pol ar gada
    glPushMatrix();
    glTranslatef(-2.2,-0.8,1);
    glScalef(0.4,0.8,1);
    glRotatef(180,0,0,1);
    glColor3ub(cowFood[0],cowFood[1],cowFood[2]);
    GLfloat midY = 0.001;
    GLfloat midX = 0.001;
    GLfloat y = 0;
    glBegin(GL_POLYGON);
    for(GLfloat x = -1; x <= 1.05; x+=0.05)
    {
        y = x*x;
        glVertex2f(midX + x, midY + y);
    }
    glEnd();
    glPopMatrix();


    //house 2
    glPushMatrix();
    glTranslatef(-1,-1.7,0);
    glScalef(0.7,0.7,1);
    glPopMatrix();

    //house 2
    glPushMatrix();
    glTranslatef(-0.7,-1.7,-0.5);
    glScalef(0.7,0.7,1);
    glPopMatrix();


    //flower on water
    glPushMatrix();
    glTranslatef(3.5,-1.8,1);
    glScalef(0.02,0.02,1);
    glRotatef(180,0,0,1);
    drawFlower();
    glPopMatrix();

    //flower on water
    glPushMatrix();
    glTranslatef(3.2,-1.8,1);
    glScalef(0.02,0.02,1);
    glRotatef(180,0,0,1);
    drawFlower();
    glPopMatrix();

    //flower on water
    glPushMatrix();
    glTranslatef(3.4,-1.6,1);
    glScalef(0.02,0.02,1);
    glRotatef(180,0,0,1);
    drawFlower();
    glPopMatrix();

    //Red flower
    glPushMatrix();
    glTranslatef(-0.2,-1.8,1);
    glScalef(0.015,0.015,1);
    glRotatef(180,0,0,1);
    drawRedFlower();
    glPopMatrix();

    //Red flower
    glPushMatrix();
    glTranslatef(-0.1,-1.9,1);
    glScalef(0.015,0.015,1);
    glRotatef(180,0,0,1);
    drawRedFlower();
    glPopMatrix();

    //Red flower
    glPushMatrix();
    glTranslatef(-0.3,-1.9,1);
    glScalef(0.015,0.015,1);
    glRotatef(180,0,0,1);
    drawRedFlower();
    glPopMatrix();




    //road
    glPushMatrix();
    drawRoad();
    glPopMatrix();







    //heli
    glPushMatrix();
    glTranslatef(fly,-1,0);
    glTranslatef(-6,0,0);
    //glScalef(1,1,1);
    drawHeli();
    glPopMatrix();

    //plane
    glPushMatrix();
    glTranslatef(fly,0,0);
    glTranslatef(-16,3,0);
    drawPlane();
    glPopMatrix();

    if(Rain && !night)
    {
        //rain
        glPushMatrix();
        glTranslatef(0,-rain,3);
        glRotatef(10,0,0,1);
        drawRain();
        glPopMatrix();

        //rainbow
        glPushMatrix();
        glTranslatef(-3,1,0);
        glScalef(4,1.5,1);
        drawRainbow();
        glPopMatrix();
    }

    if(Rain && night)
    {
        //rain
        glPushMatrix();
        glTranslatef(0,-rain,3);
        glRotatef(10,0,0,1);
        drawRain();
        glPopMatrix();

    }

    glPushMatrix();
    glTranslatef(ship, 0, 0);
    glTranslatef(0, 2, 0);

    //draw Bird
    glPushMatrix();
    drawBird();
    glPopMatrix();

    //draw Bird
    glPushMatrix();
    glTranslatef(0, 0, 1);
    glScalef(0.05, 0.05, 1);
    drawBird2();
    glPopMatrix();

    //draw Bird
    glPushMatrix();
    glTranslatef(-0.1, 0, 1);
    glScalef(0.05, 0.05, 1);
    drawBird2();
    glPopMatrix();

    //draw Bird
    glPushMatrix();
    glTranslatef(-0.1, 0.1, 1);
    glScalef(0.05, 0.05, 1);
    drawBird2();
    glPopMatrix();

    //draw Bird
    glPushMatrix();
    glTranslatef(-0.1, -0.1, 1);
    glScalef(0.05, 0.05, 1);
    drawBird2();
    glPopMatrix();

    //draw Bird
    glPushMatrix();
    glTranslatef(-0.2, -0.1, 1);
    glScalef(0.05, 0.05, 1);
    drawBird2();
    glPopMatrix();

    //draw Bird
    glPushMatrix();
    glTranslatef(-0.2, -0.2, 1);
    glScalef(0.05, 0.05, 1);
    drawBird2();
    glPopMatrix();

    //draw Bird
    glPushMatrix();
    glTranslatef(-0.2, 0, 1);
    glScalef(0.05, 0.05, 1);
    drawBird2();
    glPopMatrix();

    //draw Bird
    glPushMatrix();
    glTranslatef(-0.2, 0.1, 1);
    glScalef(0.05, 0.05, 1);
    drawBird2();
    glPopMatrix();

    //draw Bird
    glPushMatrix();
    glTranslatef(-0.2, 0.2, 1);
    glScalef(0.05, 0.05, 1);
    drawBird2();
    glPopMatrix();


    glPopMatrix();

    glutSwapBuffers();
}

void update(int value)
{
    _angle += 0.002f;

    glutPostRedisplay(); //Tell GLUT that the Panorama has changed

    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}




void flyAnimation(int value)
{


    fly += 0.04f;
    if(fly>25.0f)
    {
        //move=true;
        fly = -10.0f;
    }

    glutPostRedisplay();

    glutTimerFunc(25, flyAnimation, 0);
}



void rainAnimation(int value)
{
    rain += 0.02f;
    if(rain>0.1f)
    {
        //move=true;
        rain = -0.1f;
    }
    glutPostRedisplay();

    glutTimerFunc(25, rainAnimation, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':

        Rain = true;
        if(!night)
        {
            sky[0] = 128;
            sky[1] = 137;
            sky[2] = 140;
            cloud[0] = 87;
            cloud[1] = 98;
            cloud[2] = 102;
            sun[0] = 128;
            sun[1] = 137;
            sun[2] = 140;
            PlaySound(TEXT("rain.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
        }

        if(night && Rain)
        {
            sun[0] = 77;
            sun[1] = 77;
            sun[2] = 77;
            PlaySound(TEXT("rain.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
        }
        break;

    case 's':
        Rain = false;
        if(!night)
        {
            sky[0] = 19;
            sky[1] = 190;
            sky[2] = 242;
            cloud[0] = 255;
            cloud[1] = 255;
            cloud[2] = 255;
            sun[0] = 219;
            sun[1] = 230;
            sun[2] = 21;
            tree[0] = 34;
            tree[1] = 139;
            tree[2] = 34;
            bush[0] = 127;
            bush[1] = 162;
            bush[2] = 12;
            soil[0] = 199;
            soil[1] = 192;
            soil[2] = 141;
            cowFood[0] = 235;
            cowFood[1] = 222;
            cowFood[2] = 164;
            water[0] = 152;
            water[1] = 222;
            water[2] = 245;
            double building2[3] = {217,217,50};
            building2[0] = 217;
            building2[1] = 217;
            building2[2] = 50;
            building1Box2[0] = 237;
            building1Box2[1] = 237;
            building1Box2[2] = 187;
            building1Box3[0] = 30;
            building1Box3[1] = 186;
            building1Box3[2] = 79;
            PlaySound(TEXT("sun.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
        }
        if(!Rain && night)
        {
            sun[0] = 255;
            sun[1] = 255;
            sun[2] = 255;
            PlaySound(TEXT("night.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
        }
        break;

    case 'n':
        night = true;
        if(night && !Rain)
        {
            sky[0] = 77;
            sky[1] = 77;
            sky[2] = 77;
            cloud[0] = 125;
            cloud[1] = 125;
            cloud[2] = 125;
            sun[0] = 255;
            sun[1] = 255;
            sun[2] = 255;
            tree[0] = 125;
            tree[1] = 125;
            tree[2] = 125;
            bush[0] = 125;
            bush[1] = 125;
            bush[2] = 125;
            soil[0] = 123;
            soil[1] = 128;
            soil[2] = 28;
            cowFood[0] = 128;
            cowFood[1] = 103;
            cowFood[2] = 28;
            water[0] = 68;
            water[1] = 142;
            water[2] = 201;
            building2[0] = 102;
            building2[1] = 102;
            building2[2] = 102;
            building1Box2[0] = 102;
            building1Box2[1] = 102;
            building1Box2[2] = 102;
            building1Box3[0] = 102;
            building1Box3[1] = 102;
            building1Box3[2] = 102;
            PlaySound(TEXT("night.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
        }
        else if(night && Rain)
        {
            sky[0] = 77;
            sky[1] = 77;
            sky[2] = 77;
            cloud[0] = 125;
            cloud[1] = 125;
            cloud[2] = 125;
            sun[0] = 77;
            sun[1] = 77;
            sun[2] = 77;
            tree[0] = 125;
            tree[1] = 125;
            tree[2] = 125;
            bush[0] = 125;
            bush[1] = 125;
            bush[2] = 125;
            soil[0] = 123;
            soil[1] = 128;
            soil[2] = 28;
            cowFood[0] = 128;
            cowFood[1] = 103;
            cowFood[2] = 28;
            water[0] = 68;
            water[1] = 142;
            water[2] = 201;
            building2[0] = 102;
            building2[1] = 102;
            building2[2] = 102;
            building1Box2[0] = 102;
            building1Box2[1] = 102;
            building1Box2[2] = 102;
            building1Box3[0] = 102;
            building1Box3[1] = 102;
            building1Box3[2] = 102;
        }

        break;

    case 'd':
        night = false;

        if(!Rain)
        {
            sky[0] = 19;
            sky[1] = 190;
            sky[2] = 242;
            cloud[0] = 255;
            cloud[1] = 255;
            cloud[2] = 255;
            sun[0] = 219;
            sun[1] = 230;
            sun[2] = 21;
            tree[0] = 34;
            tree[1] = 139;
            tree[2] = 34;
            bush[0] = 127;
            bush[1] = 162;
            bush[2] = 12;
            soil[0] = 199;
            soil[1] = 192;
            soil[2] = 141;
            cowFood[0] = 235;
            cowFood[1] = 222;
            cowFood[2] = 164;
            water[0] = 152;
            water[1] = 222;
            water[2] = 245;
            building2[0] = 217;
            building2[1] = 217;
            building2[2] = 50;
            building1Box2[0] = 237;
            building1Box2[1] = 237;
            building1Box2[2] = 187;
            building1Box3[0] = 30;
            building1Box3[1] = 186;
            building1Box3[2] = 79;
            PlaySound(TEXT("sun.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
        }
        if(Rain && !night)
        {
            sky[0] = 128;
            sky[1] = 137;
            sky[2] = 140;
            cloud[0] = 87;
            cloud[1] = 98;
            cloud[2] = 102;
            sun[0] = 128;
            sun[1] = 137;
            sun[2] = 140;
            tree[0] = 34;
            tree[1] = 139;
            tree[2] = 34;
            bush[0] = 127;
            bush[1] = 162;
            bush[2] = 12;
            soil[0] = 199;
            soil[1] = 192;
            soil[2] = 141;
            cowFood[0] = 235;
            cowFood[1] = 222;
            cowFood[2] = 164;
            water[0] = 152;
            water[1] = 222;
            water[2] = 245;
            building2[0] = 217;
            building2[1] = 217;
            building2[2] = 50;
            building1Box2[0] = 237;
            building1Box2[1] = 237;
            building1Box2[2] = 187;
            building1Box3[0] = 30;
            building1Box3[1] = 186;
            building1Box3[2] = 79;
            PlaySound(TEXT("rain.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
        }
        break;
    }
}

int main(int argc, char** argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1300, 700);
    //Create the window
    glutCreateWindow("Transformations");
    initRendering();
    //Set handler functions
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutTimerFunc(250, update, 0); //Add a timer

    glutTimerFunc(25, flyAnimation, 0); //Add a timer
    glutTimerFunc(25, rainAnimation, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
