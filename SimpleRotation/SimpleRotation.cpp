#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include "AronLib.h"
#include "CameraKeyBoard.h"

using namespace SpaceDraw;
using namespace Utility;
using namespace SpaceDraw;

Cube cube(0, 0, 0, 0.5);
SimpleCoordinate coor;
Plane plane;

static void init(void) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    camera.setTheta((double)M_PI/2);
    camera.setAlpha(0.0);
}

void drawBox(){
    float alpha = 0.5;
    glBegin(GL_QUADS);
    glColor4f(1.0, 0.0, 0.0, alpha);
    glVertex3f(-1.0, +1.0, 0.0); // top left

    glColor4f(0.0, 1.0, 0.0, alpha);
    glVertex3f(-1.0, -1.0, 0.0); // bottom left

    glColor4f(0.0, 0.0, 1.0, alpha);
    glVertex3f(+1.0, -1.0, 0.0); // bottom right

    glColor4f(0.0, 1.0, 1.0, alpha);
    glVertex3f(+1.0, +1.0, 0.0); // top right
    glEnd();
    camera.print(10, 100);
}


double initX = -1;
double initY = -1;

double initX1 = -1;
double initY1 = -1;

Circle circle(initX, initY, 0.05, 10);
Circle circle1(initX1, initY1, 0.03, 20);
double delta = initX;
double alpha1 = initX1;
double off = 0.0;

double parabola(double x, double off){
    return -(x - off + 1)*(x - off + 1) + 1;
}

double parabola(double x){
    return -x*x + 1.2;
}
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
//    drawBox();
    plane.draw();
    coor.draw();

    double x = delta;
    double y = parabola(x, off);
    circle.move(x, y, 0);
    circle.draw();

    circle1.move(alpha1, parabola(alpha1), 0);
    circle1.draw();
    alpha1 += 0.009;

    cerr<<"x="<<x<<endl;
    cerr<<"y="<<y<<endl;
    delta += 0.01;
    if(delta >= 1.0){
        off = 2.0;
    }

    camera.print(10, 100);
    glFlush();
}


void delayFrame(int millisec) {
    glutTimerFunc(millisec, delayFrame, millisec);
    glutPostRedisplay();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    int millisec = 20;
    glutInitWindowSize(800, 800);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutDisplayFunc(display);

    // delay n millisecond, sleep, slow frame, delay frame
    glutTimerFunc(millisec, delayFrame, millisec);             // redraw only every given millisec

    glutMainLoop();
    return 0;
}
