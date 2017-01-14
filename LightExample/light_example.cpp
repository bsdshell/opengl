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

Cube cube(0, 0, 0, 0.5);

static void init(void) {
    glShadeModel(GL_FLAT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void drawPolygon(){

    GLfloat cyan[] = {0.f, .8f, .8f, 1.f};

    GLfloat light1_position[] = {1.0, 1.0, 1.0, 0.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light1_position);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);

    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glVertex3f(-1, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, -1);
    glVertex3f(-1, 0, -1);
    glEnd(); 
    
    char buffer[50];
    sprintf(buffer, "[%f][%f][%f]", camera.getX(), camera.getY(), camera.getZ());
    printFormatNew(100, 100, buffer); 
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
    drawPolygon();
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
    glutInitWindowSize(600, 600);
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
