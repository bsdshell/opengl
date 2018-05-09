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

static void init(void) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    camera.setTheta(0.5);
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


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
    coor.draw();
    drawBox();
    glFlush();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInitWindowSize(800, 800);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
