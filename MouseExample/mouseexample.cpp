
/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

/* blender renders two spinning icosahedrons (red and green).
   The blending factors for the two icosahedrons vary sinusoidally
   and slightly out of phase.  blender also renders two lines of
   text in a stroke font: one line antialiased, the other not.  */

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Utility.h"
#include<unistd.h> // usleep()

int mousex;
int mousey;
bool mouseleftdown = false;

// mouse
// The GLUT mouse function
void mouse(int button, int state, int x, int y) {
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON) {
        mouseleftdown = (state == GLUT_DOWN);
        glutPostRedisplay();  // Left button has changed; redisplay!
    }
    // Save the mouse position
    mousex = x;
    mousey = y;
}

void
display(void) {
    static GLfloat amb[] =
    {0.4, 0.4, 0.4, 0.0};
    static GLfloat dif[] =
    {1.0, 1.0, 1.0, 0.0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT1);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(0, 1500, 0, 1500);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    /* Rotate text slightly to help show jaggies. */
    glRotatef(0.0, 0.0, 0.0, 1.0);
    glScalef(0.5,0.5,1);
    printFormat(200, 300, "left-click[%i][%i]", mousex, mousey);

    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
}

int
main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Mouse Click");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);


    gluPerspective( /* field of view in degree */ 40.0,
            /* aspect ratio */ 1.0,
            /* Z near */ 1.0, /* Z far */ 10.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
              0.0, 0.0, 0.0,      /* center is at (0,0,0) */
              0.0, 1.0, 0.);      /* up is in positive Y direction */
    glTranslatef(0.0, 0.6, -1.0);

    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
