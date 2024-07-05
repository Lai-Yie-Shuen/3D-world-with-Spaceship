#include <GL\glut.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
static int windowWidth=800;
static int windowHeight=500;
static float fieldOfView= 60.0;
static float aspectRatio = static_cast<GLdouble> (windowWidth)/windowHeight;
double rotateX  = 0.0;
double rotateY  = 0.0;
double rotateZ  = 0.0;
double posX     = 0.0;
double posY     = 0.0;
double posZ     = 0.0;
double scaleX   = 1.0;
double scaleY   = 1.0;
double scaleZ   = 1.0;
static bool mousePanMode=false;
static bool mouseZoomMode=false;
static bool mouseRotationMode=false;
int mouseX, mouseY;

void myInit(void)
{
   static GLfloat  ambient[] = { 0.1f,  0.1f,  0.1f, 1.0f };
   static GLfloat  diffuse[] = { 0.3f,  0.3f,  0.3f, 1.0f };
   static GLfloat specular[] = { 0.0f,  0.0f,  0.0f, 1.0f };
   static GLfloat  ref[] = { 1.0f,  1.0f,  1.0f, 1.0f };
   static GLfloat position[] = {10.0f, 10.0f, 10.0f, 1.0f };
   short shininess = 128;

	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT, GL_SPECULAR, ref);
    glMateriali(GL_FRONT, GL_SHININESS, shininess);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,aspectRatio, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,10,30, 0,0,0, 0,1,0);
}
//--------------------------------------------------------------------------
void MyModelAxis(void)
{
 float lengthX=15.0,lengthY=15.0,lengthZ=15.0;
 //glDisable(GL_LIGHTING);

 glEnable(GL_LINE_STIPPLE);
 glLineWidth(1);
 glLineStipple(1, 0xffff);

 glBegin(GL_LINES);
   //x-axis
     glColor3f(1,0,0);

     glVertex3f( 0.0, 0.0, 0.0);
     glVertex3f(lengthX, 0.0, 0.0);
   //x-axis arrow
     glVertex3f(    lengthX, 0.0,  0.0);
     glVertex3f(0.9*lengthX, 0.0,  0.05*lengthX);
     glVertex3f(    lengthX, 0.0,  0.0);
     glVertex3f(0.9*lengthX, 0.0, -0.05*lengthX);

   //y-axis
     glColor3f(0,1,0);
     glVertex3f(0.0,  0.0, 0.0);
     glVertex3f(0.0, lengthY, 0.0);
   //y-axis arrow
     glVertex3f(       0.0,     lengthY, 0.0);
     glVertex3f( 0.05*lengthY, 0.9*lengthY, 0.0);
     glVertex3f(       0.0,     lengthY, 0.0);
     glVertex3f(-0.05*lengthY, 0.9*lengthY, 0.0);

   //z-axis
     glColor3f(0,0,1);
     glVertex3f(0.0, 0.0,  0.0);
     glVertex3f(0.0, 0.0, lengthZ);
   //z-axis arrow
     glVertex3f(0.0, 0.0, lengthZ);
     glVertex3f( 0.05*lengthZ, 0.0, 0.9*lengthZ);
     glVertex3f(       0.0, 0.0,     lengthZ);
     glVertex3f(-0.05*lengthZ, 0.0, 0.9*lengthZ);
 glEnd();
 //glEnable(GL_LIGHTING);
}
//--------------------------------------------------------------------------

void gunBoxConnecter()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(1,1,0);
    //bottom
    glVertex3f(0,1,0);
    glVertex3f(0,1,5);
    glVertex3f(3,1,5);
    glVertex3f(3,1,0);
    //top
    glVertex3f(0,2,0);
    glVertex3f(3,2,0);
    glVertex3f(3,2,5);
    glVertex3f(0,2,5);
    //side
    glVertex3f(0,1,0);
    glVertex3f(0,2,0);
    glVertex3f(3,2,0);
    glVertex3f(3,1,0);

    glVertex3f(0,1,5);
    glVertex3f(0,2,5);
    glVertex3f(3,2,5);
    glVertex3f(3,1,5);

    glVertex3f(0,1,0);
    glVertex3f(0,2,0);
    glVertex3f(0,2,5);
    glVertex3f(0,1,5);

    glVertex3f(3,1,0);
    glVertex3f(3,2,0);
    glVertex3f(3,2,5);
    glVertex3f(3,1,5);
    glEnd();
    glPopMatrix();
}

void gunBox()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(1,0,1);
    //bottom
    glVertex3f(0,0,0);
    glVertex3f(0,0,5);
    glVertex3f(3,0,5);
    glVertex3f(3,0,0);
    //top
    glVertex3f(0,3,0);
    glVertex3f(3,3,0);
    glVertex3f(3,3,5);
    glVertex3f(0,3,5);
    //side
    glVertex3f(0,0,0);
    glVertex3f(0,3,0);
    glVertex3f(3,3,0);
    glVertex3f(3,0,0);

    glVertex3f(0,0,5);
    glVertex3f(0,3,5);
    glVertex3f(3,3,5);
    glVertex3f(3,0,5);

    glVertex3f(0,0,0);
    glVertex3f(0,3,0);
    glVertex3f(0,3,5);
    glVertex3f(0,0,5);

    glVertex3f(3,0,0);
    glVertex3f(3,3,0);
    glVertex3f(3,3,5);
    glVertex3f(3,0,5);
    glEnd();
    glPopMatrix();
}

void barrel()
{
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    glPushMatrix();
    // front
    glColor3f(1,0,0);
    gluCylinder(pObj, 0.5f, 0.4f, 2.0f, 26, 1);
    glColor3f(0,0,1);
    gluCylinder(pObj, 0.4f, 0.3f, 4.0f, 26, 1);
    glColor3f(1,0,1);
    gluCylinder(pObj, 0.3f, 0.3f, 6.0f, 26, 1);

    glPopMatrix();
    gluDeleteQuadric(pObj);
}

void weapon()
{
    gunBoxConnecter();
    glTranslatef(3,0,0);
    gunBox();
    glTranslatef(1.5,1.5,5);
    barrel();

    glTranslatef(-3,0,0);
    glTranslatef(-1.5,-1.5,-5);
}

void head()
{
    glPushMatrix();

    //left side
    glBegin(GL_QUADS);
    glColor3f(0,0,1);
    glVertex3f(-4,0,0);
    glVertex3f(-4,-2,0);
    glVertex3f(-4,-2,8);
    glVertex3f(-4,0,8);

    glVertex3f(-4,0,8);
    glVertex3f(-4,-2,8);
    glVertex3f(-1,-2,12);
    glVertex3f(-1,-1,12);

    glVertex3f(-1,-1,12);
    glVertex3f(-1,-2,12);
    glVertex3f(0,-2,12);
    glVertex3f(0,-1,12);

    //right side
    glVertex3f(4,0,0);
    glVertex3f(4,-2,0);
    glVertex3f(4,-2,8);
    glVertex3f(4,0,8);

    glVertex3f(4,0,8);
    glVertex3f(4,-2,8);
    glVertex3f(1,-2,12);
    glVertex3f(1,-1,12);

    glVertex3f(1,-1,12);
    glVertex3f(1,-2,12);
    glVertex3f(0,-2,12);
    glVertex3f(0,-1,12);
    glEnd();

    //top
    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex3f(-4,0,0);
    glVertex3f(-4,0,8);
    glVertex3f(4,0,8);
    glVertex3f(4,0,0);

    glVertex3f(4,0,8);
    glVertex3f(-4,0,8);
    glVertex3f(-1,-1,12);
    glVertex3f(1,-1,12);
    glEnd();

    // bottom
    glBegin(GL_QUADS);
    glVertex3f(-4,-2,0);
    glVertex3f(-4,-2,8);
    glVertex3f(4,-2,8);
    glVertex3f(4,-2,0);

    glVertex3f(4,-2,8);
    glVertex3f(-4,-2,8);
    glVertex3f(-1,-2,12);
    glVertex3f(1,-2,12);
    glEnd();

    // Pilot room
    glBegin(GL_QUADS);
    //left
    glColor3f(0,0,0);
    glVertex3f(-4,0,-4);
    glVertex3f(-4,0,8);
    glVertex3f(-2,2,6);
    glVertex3f(-2,2,-4);
    //right
    glVertex3f(4,0,-4);
    glVertex3f(4,0,8);
    glVertex3f(2,2,6);
    glVertex3f(2,2,-4);
    //top
    glVertex3f(-2,2,6);
    glVertex3f(-2,2,-4);
    glVertex3f(2,2,-4);
    glVertex3f(2,2,6);
    //front
    glVertex3f(-4,0,8);
    glVertex3f(-2,2,6);
    glVertex3f(2,2,6);
    glVertex3f(4,0,8);
    glEnd();
    glPopMatrix();

    glScalef(0.5,0.5,0.5);
    // change position
    glTranslatef(7,-4,6);
    weapon();
    // change back
    glTranslatef(-7,4,-6);

    glScalef(-1,1,1);
    glTranslatef(7,-4,6);
    weapon();

    glTranslatef(-7,4,-6);
    glScalef(-1,1,1);
    glScalef(2,2,2);

}

void body()
{
    glPushMatrix();

    glBegin(GL_QUADS);
    glColor3f(1,0,1);
    //left body
    glVertex3f(-4,0,0);
    glVertex3f(-4,-2,0);
    glVertex3f(-6,-2,-4);
    glVertex3f(-6,2,-4);

    glVertex3f(-6,-2,-4);
    glVertex3f(-6,-2,-20);
    glVertex3f(-6,2,-25);
    glVertex3f(-6,2,-4);

    //right body
    glVertex3f(4,0,0);
    glVertex3f(4,-2,0);
    glVertex3f(6,-2,-4);
    glVertex3f(6,2,-4);

    glVertex3f(6,-2,-4);
    glVertex3f(6,-2,-20);
    glVertex3f(6,2,-25);
    glVertex3f(6,2,-4);

    // top body
    glVertex3f(6,2,-4);
    glVertex3f(4,0,0);
    glVertex3f(-4,0,0);
    glVertex3f(-6,2,-4);

    glVertex3f(6,2,-4);
    glVertex3f(6,2,-25);
    glVertex3f(-6,2,-25);
    glVertex3f(-6,2,-4);

    // bottom body
    glVertex3f(6,-2,-4);
    glVertex3f(4,-2,0);
    glVertex3f(-4,-2,0);
    glVertex3f(-6,-2,-4);

    glVertex3f(6,-2,-4);
    glVertex3f(6,-2,-20);
    glVertex3f(-6,-2,-20);
    glVertex3f(-6,-2,-4);

    //backside
    /*glVertex3f(6,-2,-20);
    glVertex3f(-6,-2,-20);
    glVertex3f(-6,2,-20);
    glVertex3f(6,2,-20);*/

    glColor3f(1,1,0);
    glVertex3f(6,-2,-20);
    glVertex3f(-6,-2,-20);
    glVertex3f(-6,2,-25);
    glVertex3f(6,2,-25);
    glEnd();
    glPopMatrix();
}

void fanScript()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(1,1,0);
    //top
    glVertex3f(0,0,0);
    glVertex3f(0,0,10);
    glVertex3f(1,0,10);
    glVertex3f(1,0,0);
    //bottom
    glVertex3f(0,5,0);
    glVertex3f(0,5,10);
    glVertex3f(1,5,10);
    glVertex3f(1,5,0);
    //side
    glVertex3f(0,0,0);
    glVertex3f(0,5,0);
    glVertex3f(0,5,10);
    glVertex3f(0,0,10);

    glVertex3f(0,0,10);
    glVertex3f(1,0,10);
    glVertex3f(1,5,10);
    glVertex3f(0,5,10);

    glVertex3f(1,0,0);
    glVertex3f(1,5,0);
    glVertex3f(1,5,10);
    glVertex3f(1,0,10);

    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,5,0);
    glVertex3f(0,5,0);

    glEnd();
    glPopMatrix();
}

void fan()
{
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    glPushMatrix();
    glColor3f(0,0,1);
    gluSphere(pObj, 1, 25, 25);

    gluCylinder(pObj, 1.0f, 1.0f, 10.0f, 26, 13);

    glTranslatef(0,0,10);
    gluSphere(pObj, 1, 25, 25);

    glPopMatrix();
    gluDeleteQuadric(pObj);

    for (int i = 0; i<360 ; i=i+30)
    {
        glPushMatrix();

            glRotatef(i, 0, 0, 1);
            glTranslatef(-0.5,1,0);
            fanScript();

        glPopMatrix();
    }
}

static float Rotation=0;
void Spin()
{
    glRotatef(Rotation, 0, 0, 1);
    fan();
}

void turbo()
{
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    glPushMatrix();
    // front
    glColor3f(0,0,1);
    gluCylinder(pObj, 1.3f, 1.3f, 5.0f, 26, 1);
    //back
    glColor3f(1,0,1);
    glScalef(1,1,-1);
    gluCylinder(pObj, 1.3f, 0.8f, 2.0f, 26, 5);

    glPopMatrix();
    gluDeleteQuadric(pObj);

    glScalef(0.2,0.2,0.2);
    // Fan
    fan();
    // Spin the fan
    /*Spin();

    glFlush();
    Rotation = Rotation + 0.5;
    glutPostRedisplay();
    glRotatef(Rotation, 0, 0, 0);*/
    glScalef(5,5,5);
}

void missileBody()
{
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    glColor3f(1,1,1);
    // Missile body
    glPushMatrix();
    gluDisk(pObj, 0, 1.0, 26, 13);
    gluCylinder(pObj, 1.0f, 1.0f, 10.0f, 26, 13);
    glPopMatrix();
    // Missile head
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glScalef(1,1,3);
    glTranslatef(0,0,3);
    gluSphere(pObj, 1.0f, 26, 26);
    glTranslatef(0,0,-3);
    glPopMatrix();
    gluDeleteQuadric(pObj);
}

void missileTail()
{
    // Missile tail
    glPushMatrix();
    glBegin(GL_QUADS);
    glTranslatef(-1,0,0);
    //bottom
    glVertex3f(0,0,-1);
    glVertex3f(0,0,3);
    glVertex3f(1,0,3);
    glVertex3f(1,0,-1);
    //top
    glVertex3f(0,2,0);
    glVertex3f(0,3,-2);
    glVertex3f(1,3,-2);
    glVertex3f(1,2,0);
    //side
    glColor3f(1,0,0);
    glVertex3f(1,0,-1);
    glVertex3f(1,3,-2);
    glVertex3f(1,2,0);
    glVertex3f(1,0,3);

    glVertex3f(0,0,-1);
    glVertex3f(0,3,-2);
    glVertex3f(0,2,0);
    glVertex3f(0,0,3);
    //front
    glColor3f(0,0,1);
    glVertex3f(0,2,0);
    glVertex3f(1,2,0);
    glVertex3f(1,0,3);
    glVertex3f(0,0,3);
    //backside
    glVertex3f(0,3,-2);
    glVertex3f(1,3,-2);
    glVertex3f(1,0,-1);
    glVertex3f(0,0,-1);

    glEnd();
    glPopMatrix();
}

void missile()
{
    missileBody();

    for (int i = 0; i<360 ; i=i+90)
    {
        glPushMatrix();

            glRotatef(i, 0, 0, 1);
            glTranslatef(-0.5,0.5,2);
            missileTail();
            glTranslatef(0.5,-0.5,-2);
        glPopMatrix();
    }

}

void wing()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    // Big part
    //top
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(-5,0,-1);
    glVertex3f(-5,0,-4);
    glVertex3f(0,0,-5);
    //bottom
    glVertex3f(0,-1,0);
    glVertex3f(-5,-1,-1);
    glVertex3f(-5,-1,-4);
    glVertex3f(0,-1,-5);
    //left
    glVertex3f(0,0,0);
    glVertex3f(-5,0,-1);
    glVertex3f(-5,-1,-1);
    glVertex3f(0,-1,0);
    //right side
    glVertex3f(0,0,-5);
    glVertex3f(-5,0,-4);
    glVertex3f(-5,-1,-4);
    glVertex3f(0,-1,-5);

    //middle part
    //top
    glColor3f(1,0,0);
    glVertex3f(-5,0,-1);
    glVertex3f(-6,0,2);
    glVertex3f(-6,0,-8);
    glVertex3f(-5,0,-4);
    //bottom
    glColor3f(1,0,0);
    glVertex3f(-5,-1,-1);
    glVertex3f(-6,-1,2);
    glVertex3f(-6,-1,-8);
    glVertex3f(-5,-1,-4);
    //side
    glColor3f(1,1,1);
    glVertex3f(-6,0,2);
    glVertex3f(-6,-1,2);
    glVertex3f(-6,-1,-8);
    glVertex3f(-6,0,-8);

    glColor3f(1,1,0);
    glVertex3f(-6,0,2);
    glVertex3f(-6,-1,2);
    glVertex3f(-5,-1,-1);
    glVertex3f(-5,0,-4);

    glVertex3f(-6,0,-8);
    glVertex3f(-6,-1,-8);
    glVertex3f(-5,-1,-4);
    glVertex3f(-5,0,-4);

    //Small part
    // top
    glColor3f(0,1,1);
    glVertex3f(-6,0,-1);
    glVertex3f(-9,-1,-2);
    glVertex3f(-9,-1,-3);
    glVertex3f(-6,0,-4);
    //bottom
    glVertex3f(-6,-1,-1);
    glVertex3f(-9,-2,-2);
    glVertex3f(-9,-2,-3);
    glVertex3f(-6,-1,-4);
    //left side
    glVertex3f(-6,0,-1);
    glVertex3f(-9,-1,-2);
    glVertex3f(-9,-2,-2);
    glVertex3f(-6,-1,-1);
    //right side
    glVertex3f(-6,0,-4);
    glVertex3f(-9,-1,-3);
    glVertex3f(-9,-2,-3);
    glVertex3f(-6,-1,-4);
    //front
    glVertex3f(-9,-1,-2);
    glVertex3f(-9,-1,-3);
    glVertex3f(-9,-2,-3);
    glVertex3f(-9,-2,-2);
    glEnd();

    glPopMatrix();

    glTranslatef(-3,-2.3,-6);
    turbo();
    glTranslatef(3,2.3,6);

    glScalef(0.4,0.4,0.4);
    glTranslatef(-23.3,-4,-12);
    missile();
    glTranslatef(23.3,4,12);
    glScalef(2.5,2.5,2.5);
}

void wings()
{
    glTranslatef(-5,0,-8);
    glScaled(1.5,1.5,1.5);
    glColor3f(0,1,1);
    wing();

    glScaled(-1,1,1);
    glTranslatef(-7,0,0);
    glColor3f(0,1,1);
    wing();
}

void tail()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    //bottom
    glVertex3f(0,0,-2);
    glVertex3f(0,0,6);
    glVertex3f(1,0,6);
    glVertex3f(1,0,-2);
    //top
    glVertex3f(0,6,0);
    glVertex3f(0,7,-4);
    glVertex3f(1,7,-4);
    glVertex3f(1,6,0);
    //side
    glColor3f(1,0,0);
    glVertex3f(1,0,-2);
    glVertex3f(1,7,-4);
    glVertex3f(1,6,0);
    glVertex3f(1,0,6);

    glVertex3f(0,0,-2);
    glVertex3f(0,7,-4);
    glVertex3f(0,6,0);
    glVertex3f(0,0,6);
    //front
    glColor3f(0,0,1);
    glVertex3f(0,6,0);
    glVertex3f(1,6,0);
    glVertex3f(1,0,6);
    glVertex3f(0,0,6);
    //backside
    glVertex3f(0,7,-4);
    glVertex3f(1,7,-4);
    glVertex3f(1,0,-2);
    glVertex3f(0,0,-2);

    glEnd();
    glPopMatrix();
}

void spaceship()
{
    head();
    body();
    glTranslatef(0,1.5,0);
    wings();
    glTranslatef(3.2,0,-8);
    tail();
}


//------------------------------------------------------------------------
static float translateZ=0;
static bool launch1=0, launch2=0;
static int first=0, second=0;
void myDisplayFunc(void)
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);

     MyModelAxis();
     //glTranslatef(4,0,20);
     spaceship();

/* plane();

 if(launch1 == 1 && translateZ >= -40)
 {
     glPushMatrix();
     glTranslatef(0,0,translateZ);
     if(first == 1)
        FirstSetOfMissiles();
     if(second == 1)
        SecondSetOfMissiles();
     glPopMatrix();
 }

if(first == 0 && second == 0)
{
    FirstSetOfMissiles();
    SecondSetOfMissiles();
}
else if(first == 1 && second == 0)
{
    SecondSetOfMissiles();
}
else if(first == 0 && second == 1)
{
    FirstSetOfMissiles();
}*/

 glPopMatrix();
 glFlush();
 glutSwapBuffers();
 if(launch1==1)
 {
     translateZ = translateZ - 0.01;
 }


 glutPostRedisplay();
}
//--------------------------------------------------------------------------
void myReshapeFunc(int width, int height)
{
 windowWidth  = width;
 windowHeight = height;
 glViewport(0, 0, width, height);
}
//--------------------------------------------------------------------------
void myKeyboardFunc(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'f' :
    case 'F' : if(second == 1)
                  second = 3;
               if(first == 0)
                  first = 1;
               else if(first == 1)
                  first = 3;
               launch1 = 1, translateZ = 0;
               break;

    case 's' :
    case 'S' : if(first == 1)
                  first = 3;
               if(second == 0)
                  second = 1;
               else if(second == 1)
                  second = 3;
               launch1 = 1, translateZ = 0;
               break;

    case 'r' :
    case 'R' : first = 0, second = 0, launch1 = 0;
               break;
    case 27  : exit(1); break;
  }
  glFlush();
  glutPostRedisplay();
}
//--------------------------------------------------------------------------
void mySpecialFunc(int key, int x, int y)
{
  switch (key)
  {

 	case GLUT_KEY_F1    : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                             break;
	case GLUT_KEY_F2    : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                             break;
  }
  glutPostRedisplay();
}
//--------------------------------------------------------------------------
void myMouseFunc(int button, int state, int x, int y)
{
    y = windowHeight-y;
    switch (button) {
      case GLUT_MIDDLE_BUTTON:
          if (state==GLUT_DOWN && !mousePanMode) {
              mouseX = x;
              mouseY = y;
              mousePanMode = true;
          }
          if (state==GLUT_UP &&  mousePanMode) {
              mousePanMode = false;
          }
          break;
      case GLUT_RIGHT_BUTTON:
          if (state==GLUT_DOWN && !mouseZoomMode) {
              mouseY = y;
              mouseZoomMode = true;
          }
          if (state==GLUT_UP && mouseZoomMode) {
              mouseZoomMode = false;
          }
          break;
      case GLUT_LEFT_BUTTON:
          if (state==GLUT_DOWN && !mouseRotationMode) {
              mouseX = x;
              mouseY = y;
              mouseRotationMode = true;
          }
          if (state==GLUT_UP &&  mouseRotationMode) {
              mouseRotationMode = false;
          }
		  break;
    }

}
//--------------------------------------------------------------------------
void myMotionFunc(int x, int y) {
    y = windowHeight - y;
    if(mousePanMode) {
        posX += (x - mouseX)*0.01;
        posY += (y - mouseY)*0.01;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
    if(mouseZoomMode) {
        GLdouble inc = (mouseY - y)*0.01;
        scaleX += inc;
        scaleY += inc;
        scaleZ += inc;
        if(scaleX < 0.1) scaleX = 0.1;
        if(scaleY < 0.1) scaleY = 0.1;
        if(scaleZ < 0.1) scaleZ = 0.1;
        mouseY = y;
        glutPostRedisplay();
    }
    if(mouseRotationMode) {
        rotateX += (mouseY - y)*0.5;
        rotateY += (x - mouseX)*0.5;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }

}
//--------------------------------------------------------------------------
int main( int argc, char **argv)
{
 glutInit(&argc, argv);

 glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
 glutInitWindowPosition(100, 100);
 glutInitWindowSize(windowWidth, windowHeight);
 glutCreateWindow("Spaceship");

 myInit();
 glutDisplayFunc(myDisplayFunc);
 glutReshapeFunc(myReshapeFunc);
 glutKeyboardFunc(myKeyboardFunc);
 glutSpecialFunc(mySpecialFunc);
 glutMotionFunc(myMotionFunc);
 glutMouseFunc(myMouseFunc);
 cout<<"Press letter "<<endl;
 cout<<"r or R to reload missiles " <<endl;
 cout<<"f or F to launch first set of missiles "<<endl;
 cout<<"s or S to launch second set of missiles "<<endl;
 glutMainLoop(); // Display everything and wait
 return 0;
}
