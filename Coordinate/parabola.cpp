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
#include "Torus.h"
#include "Circle.h"
#include "Cylinder.h"
#include "DrawQuad.h"
#include "Coordinate.h"
#include "Color.h" 
#include "Parabola.h" 
#include "CameraKeyBoard.h" 
#include "AronLib.h" 

using namespace Utility;
using namespace SpaceDraw;

Parabola para;
SimpleCoordinate coor;
Cylinder cylinder(0, 0, 2);

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


//void drawCoordinate(float width = 1.0, int num=10){
//    glBegin(GL_LINES); 
//      float delta = width/num;
//      glColor3f(0.0f, width, 0.0f); 
//      for(int i=-num; i<=num; i++){
//          glVertex3f(-width, 0.0f, delta*i);
//          glVertex3f(width, 0.0f,  delta*i);
//      }
//
//      glColor3f(0.3f,0.7f,0.0f); 
//      for(int i=-num; i<=num; i++){
//          glVertex3f(-width, delta*i,  0.0f);
//          glVertex3f(width,  delta*i,  0.0f);
//      }
//
//      glColor3f(width, 0.0f,0.0f);
//      for(int i=-num; i<=num; i++){
//          glVertex3f(0.0f, -width, delta*i);
//          glVertex3f(0.0f, width,  delta*i);
//      }
//
//      glColor3f(0.4f, 0.4f,0.1f);
//      for(int i=-num; i<=num; i++){
//          glVertex3f(delta*i, -width, 0.0f);
//          glVertex3f(delta*i, width,  0.0f);
//      }
//
//      glColor3f(0.0f, 0.0f, width); 
//      for(int i=-num; i<=num; i++){
//          glVertex3f(delta*i, 0.0f, -width);
//          glVertex3f(delta*i, 0.0f, width);
//      }
//
//      glColor3f(0.0f, 0.5f, 0.5f); 
//      for(int i=-num; i<=num; i++){
//          glVertex3f(0.0f, delta*i, -width);
//          glVertex3f(0.0f, delta*i, width);
//      }
//    glEnd();
//}
//

void draw_test(){
//    glBegin(GL_LINE_LOOP); //starts drawing of points
//        glVertex3f(1.0f, 1.0f, 0.0f);
//        glVertex3f(0.0f, 0.0f, 0.0f);
//        glVertex3f(1.0f, -1.0f, 0.0f);
//    glEnd();
//    drawCoordinate(2.0);
    coor.draw();
    char buffer[50];
    sprintf(buffer, "[%f][%f][%f]", camera.getX(), camera.getY(), camera.getZ());
    printFormatNew(50, 50, buffer);
    cylinder.draw();
}

float matrix[16];

// Draws one frame, the CheckerBoard then the balls, from the current camera
// position.
void display() {
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
    getModelViewMatrix(matrix);

    draw_test();

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
    glutCreateWindow("Lighting example");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, timer, 0);

    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

    glutMainLoop();
}
