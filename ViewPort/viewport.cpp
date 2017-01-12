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
#include "Const.h"
#include "cameraKeyBoard.h"
#include "AronLib.h"

using namespace Utility;

void init() {
    glEnable(GL_DEPTH_TEST);
}


void draw(){
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1, 1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(-1, -1, 0);
    glEnd();
}
// Draws one frame, the CheckerBoard then the balls, from the current camera
// position.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    draw();
    glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

    glFlush();
    glutSwapBuffers();
}


// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    float aspect = GLfloat(w)/GLfloat(h);
    fprintf(stderr, "w=[%i] h=[%i] aspect=[%f]\n", w, h, aspect);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, aspect, 1.0, 150.0);
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
    glutCreateWindow("Rendering Teacup");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, timer, 0);
    init();
    glutMainLoop();
}
