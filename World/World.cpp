//===================================================================
// Task: Texture map a model
//===================================================================

#include <GL\glut.h>
#include <iostream>
#include <stdlib.h>
#include "ReadBMP.h"
#include "ImageManipulation.h"
using namespace std;

int  ScreenWindowWidth  = 800;
int  ScreenWindowHeight = 600;

int WorldWidth = 2000;
int WorldHeight = 2000;
int WorldDeep = 5000;

typedef GLfloat  VertexArray[3];
typedef GLfloat  NormalArray[3];

GLfloat  Xpos   =  0.0;
GLfloat  Ypos   =  0.0;
GLfloat  Zpos   =  0.0;
GLfloat  Xangle =  0.0;
GLfloat  Yangle =  0.0;
GLfloat  XangInc = 5;
GLfloat  YangInc = 5;
double scaleX   = 1.0;
double scaleY   = 1.0;
double scaleZ   = 1.0;
static bool mousePanMode=false;
static bool mouseZoomMode=false;
static bool mouseRotationMode=false;
int mouseX, mouseY;

//Add code here
GLuint textureNumber[3];

//---------------------------------------------------------------------
void Space1()
{
    glBindTexture(GL_TEXTURE_2D, textureNumber[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-5,-5,-5);
    glTexCoord2f(1,0); glVertex3f(5,-5,-5);
    glTexCoord2f(1,1); glVertex3f(5,5,-5);
    glTexCoord2f(0,1); glVertex3f(-5,5,-5);
    glEnd();
}

void Space2()
{
    glBindTexture(GL_TEXTURE_2D, textureNumber[1]);

    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-5,-5,-5);
    glTexCoord2f(1,0); glVertex3f(5,-5,-5);
    glTexCoord2f(1,1); glVertex3f(5,5,-5);
    glTexCoord2f(0,1); glVertex3f(-5,5,-5);
    glEnd();
}

void Space3()
{
    glBindTexture(GL_TEXTURE_2D, textureNumber[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-5,-5,-5);
    glTexCoord2f(1,0); glVertex3f(5,-5,-5);
    glTexCoord2f(1,1); glVertex3f(5,5,-5);
    glTexCoord2f(0,1); glVertex3f(-5,5,-5);
    glEnd();
}
//---------------------------------------------------------------------
void myDisplay(void)
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(1.0, 0.0, 0.0);

   glLoadIdentity();
   gluLookAt(0,0,20, 0,5,0, 0,1,0);

   glPushMatrix();
      glTranslatef(Xpos, Ypos, Zpos);
      glRotatef(Yangle, 0.0, 1.0, 0.0);
      glRotatef(Xangle, 1.0, 0.0, 0.0);
      glScalef(scaleX, scaleY, scaleZ);

	  glEnable(GL_TEXTURE_2D);

	  glScalef(10000,10000,10000);

      Space1();

      glRotatef(-90, 1, 0, 0.0);
      Space2();

      glRotatef(-90, 1, 0, 0.0);
      Space1();

      glRotatef(-90, 1, 0, 0.0);
      Space2();

      glRotatef(90, 0, 1, 0.0);
      Space3();

      glRotatef(-180, 0, 1, 0.0);
      Space3();

   glPopMatrix();
   glFlush();
   glutSwapBuffers();
}

//---------------------------------------------------------------------

void myReshape(int width, int height)
{
  static GLfloat fieldOfViewAngle = 70.0;
  GLfloat windowAspectRatio = WorldWidth / WorldHeight;
  static GLfloat zNear =   0.0;
  static GLfloat zFar  = WorldDeep;

  ScreenWindowWidth  = width;
  ScreenWindowHeight = height;
  glViewport(0,0, width, height);

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(fieldOfViewAngle, windowAspectRatio, zNear, zFar);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}
//---------------------------------------------------------------------
void myInit(void)
{
  MyImageStruct  myImage = { 0, 0, 0 };
  char   *fileNames[] = { "Space1.bmp", "Space2.bmp", "Space3.bmp"};

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glGenTextures(3, textureNumber);
    for (int j=0; j<3; j++)
        {
            ReadBMP(fileNames[j], &myImage);
            CropImageToPowerOf2( &myImage, 128, 128);
            glBindTexture(GL_TEXTURE_2D, textureNumber[j]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,myImage.Width,myImage.Height,0,GL_RGB, GL_UNSIGNED_BYTE,myImage.Pixels);
            free( myImage.Pixels );
         }

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

}
//---------------------------------------------------------------------

void myKeyboard(unsigned char key, int x, int y)
{
  static const GLdouble posInc = 0.1;

  switch (key)
  {
    case 'x' : Xpos -= posInc;  break;
    case 'X' : Xpos += posInc;  break;
    case 'y' : Ypos -= posInc;  break;
    case 'Y' : Ypos += posInc;  break;
    case 'z' : Zpos -= posInc;  break;
    case 'Z' : Zpos += posInc;  break;
	case 'w' : Xangle += XangInc; break;
	case 'W' : Xangle -= XangInc; break;
	case 'q' : Yangle += YangInc; break;
	case 'Q' : Yangle -= YangInc; break;
  }
  myInit();
  glutPostRedisplay();
}
//-------------------------------------------------------------
void myMouse(int button, int state, int x, int y)
{
    y = ScreenWindowHeight-y;
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
void myMotion(int x, int y) {
    y = ScreenWindowHeight - y;
    if(mousePanMode) {
        Xpos += (x - mouseX)*0.01;
        Ypos += (y - mouseY)*0.01;
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
        Xangle += (mouseY - y)*0.5;
        Yangle += (x - mouseX)*0.5;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }

}
//---------------------------------------------------------------------

void mySpecialKey(int key, int x, int y)
{
  static const GLfloat angleInc = 2.0;

  switch (key)
  {
    case GLUT_KEY_DOWN  : Xangle -= angleInc;  break;
    case GLUT_KEY_UP    : Xangle += angleInc;  break;
    case GLUT_KEY_LEFT  : Yangle -= angleInc;  break;
    case GLUT_KEY_RIGHT : Yangle += angleInc;  break;

	case GLUT_KEY_HOME      : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);         break; //draw object in filled mode
	case GLUT_KEY_END       : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);         break; //draw object in wireframe mode
  }
  glutPostRedisplay();

}

//--------------------------------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(ScreenWindowWidth, ScreenWindowHeight);
    glutCreateWindow("Space World");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
    glutSpecialFunc(mySpecialKey);
	myInit();
	cout<<"Press Home and End:To fill or to draw line for the object"<<endl;
	cout<<"Press arrow keys  :To rotate the object"<<endl;
	cout<<"Press x,X,y,Y,z,Z :To translate the object"<<endl;
    glutMainLoop();
    return 0;
}

//---------------------------------------------------------------------

