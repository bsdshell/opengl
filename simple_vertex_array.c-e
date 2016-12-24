#include <assert.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>

/*
* OpenGL. Draw Triangle with Vertex Array
* -------------------------------------------------------------------------------- 
* Mac OSX EL Capitan 10.11.4
* NVIDIA GeForce GT 650M 1024 MB 
* 
* OpenGL and GLUT dir:
* /System/Library/Frameworks/OpenGL.framework/Libraries
* -------------------------------------------------------------------------------- 
* How to compile
* g++ -o simple_vertex_array simple_vertex_array.c -framework GLUT -framework OpenGL
*
*/

typedef float vector3[3];

static vector3 vertices[] = {
    { 0.0,   0.0,   0.0 },
    { 100.0, 0.0,   0.0 },
    { 100.0, 100.0, 0.0 }
};

static void
reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1.0, 100.0);

    assert(glGetError() == GL_NO_ERROR);
}

static void
display(void) {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f,1.0f,0.0f); // point color

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslated(10.0, 10.0, 0.0);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();

    glutSwapBuffers();
}

int
main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Draw Vertex Array Triangle");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(glutPostRedisplay);

    glutMainLoop();
    return 0;
}
