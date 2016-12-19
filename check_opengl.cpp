#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>

int main (int argc, char** argv) {
    const GLubyte* renderer;
    const GLubyte* version;

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_3_2_CORE_PROFILE | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize (640, 480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("OpenGL");

    /* get version info */
    renderer = glGetString (GL_RENDERER);
    version = glGetString (GL_VERSION);
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported: %s\n", version);

    /*
    init ();
    glutDisplayFunc (display);
    glutMainLoop ();
    */

    return 0;
}
