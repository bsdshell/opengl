#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Const.h"
#include "Cube.h"
#include "CameraKeyBoard.h"

Cube cube;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cube.draw();
    glutSwapBuffers();
}

void
init(void) {

    /* Use depth buffering for hidden surface elimination. */
    glEnable(GL_DEPTH_TEST);

    /* Setup the view of the cube. */
    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
            /* aspect ratio */ 1.0,
            /* Z near */ 1.0, /* Z far */ 10.0);
    glMatrixMode(GL_MODELVIEW);
//    gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
//              0.0, 0.0, 0.0,      /* center is at (0,0,0) */
//              0.0, 1.0, 0.);      /* up is in positive Y direction */

    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    /* Adjust cube position to be asthetic angle. */
    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(60, 1.0, 0.0, 0.0);
    glRotatef(-20, 0.0, 0.0, 1.0);
}

// Requests to draw the next frame.
void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, v);
}

int
main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("red 3D lighted cube");
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, timer, 0);
    init();
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
