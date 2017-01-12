// This application shows balls bouncing on a CheckerBoard, with no respect
// for the laws of Newtonian Mechanics.  There's a little spotlight to make
// the animation interesting, and arrow keys move the camera for even more
// fun.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

#include "BezierCurve.h"
#include "Curve.h"
#include "Torus.h"
#include "Circle.h"
#include "Cylinder.h"
#include "DrawQuad.h"
#include "Coordinate.h"
#include "Color.h" 
#include "Parabola.h" 
#include "CameraKeyBoard.h" 
#include "Cube.h" 
#include "AronLib.h" 

using namespace Utility;

Parabola para;
Cube cube;


// Application-specific initialization: Set up global lighting parameters
// and create display lists.
void init() {
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, RED);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


void drawCoordinate(void){
    glBegin(GL_LINES); 

      float delta = 0.1f;
      glColor3f(0.0f,1.0f,0.0f); 
      for(int i=-10; i<=10; i++){
          glVertex3f(-1.0f, 0.0f, delta*i);
          glVertex3f(1.0f, 0.0f,  delta*i);
      }

      glColor3f(0.3f,0.7f,0.0f); 
      for(int i=-10; i<=10; i++){
          glVertex3f(-1.0f, delta*i,  0.0f);
          glVertex3f(1.0f,  delta*i,  0.0f);
      }

      glColor3f(1.0f, 0.0f,0.0f);
      for(int i=-10; i<=10; i++){
          glVertex3f(0.0f, -1.0f, delta*i);
          glVertex3f(0.0f, 1.0f,  delta*i);
      }

      glColor3f(0.4f, 0.4f,0.1f);
      for(int i=-10; i<=10; i++){
          glVertex3f(delta*i, -1.0f, 0.0f);
          glVertex3f(delta*i, 1.0f,  0.0f);
      }

      glColor3f(0.0f, 0.0f, 1.0f); 
      for(int i=-10; i<=10; i++){
          glVertex3f(delta*i, 0.0f, -1.0f);
          glVertex3f(delta*i, 0.0f, 1.0f);
      }

      glColor3f(0.0f, 0.5f, 0.5f); 
      for(int i=-10; i<=10; i++){
          glVertex3f(0.0f, delta*i, -1.0f);
          glVertex3f(0.0f, delta*i, 1.0f);
      }
    glEnd();
}


void draw_test(){
    glBegin(GL_LINE_LOOP); //starts drawing of points
        glVertex3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    drawCoordinate();
}

float matrix[16];

// Draws one frame, the CheckerBoard then the balls, from the current camera
// position.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // forward = (0, 0, 0) - (0, 2, 3) = eye -> center

    //getModelViewMatrix(matrix);
//    gluLookAt(-1, 2, 3,
//              0.0, 0.0, 0.0,
//              0.0, 1, 0);

//> 9 / (sqrt 117)
//0.8320502943378436
//> -2 / (sqrt 13)
//-0.5547001962252291
//> 
//[1.000000][0.000000][0.000000][0.000000]
//[0.000000][0.832050][-0.554700][0.000000]
//[0.000000][0.554700][0.832050][-3.605551]
//[0.000000][0.000000][0.000000][1.000000]

    getModelViewMatrix(matrix);

    draw_test();

//    glMatrixMode(GL_PROJECTION);
    //para.draw();
    glFlush();
    glutSwapBuffers();
}

// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

// Requests to draw the next frame.
void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, v);
}

// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bouncing Balls");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, timer, 0);
    //init();

    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

    glutMainLoop();
}
