#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/

/*OpenGL. Draw triangles with GL_POLYGON
* -------------------------------------------------------------------------------- 
* Mac OSX EL Capitan 10.11.4
* NVIDIA GeForce GT 650M 1024 MB 
* 
* Framework dir:
* /System/Library/Frameworks/OpenGL.framework/Libraries
* -------------------------------------------------------------------------------- 
* How to compile
* g++ -o draw_polygon draw_polygon.c -framework GLUT -framework OpenGL 
*/

void drawPolygon(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.8f,0.3f,0.0f); 

    glBegin(GL_POLYGON); 
      glVertex3f(0.5f, 0.2f, 0.0f);
      glVertex3f(-0.3f, 0.5f, 0.0f);
      glVertex3f(-0.5f, -0.6f, 0.0f);
      glVertex3f(-0.2f, -0.4f, 0.0f);
    glEnd();

    glLoadIdentity();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (400,400);
    glutInitWindowPosition (200, 200);
    glutCreateWindow ("Draw GL_TRIANGLES");

    glutDisplayFunc(drawPolygon);

    glutMainLoop();

    return 0;
}
