#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/

/*OpenGL. Draw triangles with GL_TRIANGLES 
* -------------------------------------------------------------------------------- 
* Mac OSX EL Capitan 10.11.4
* NVIDIA GeForce GT 650M 1024 MB 
* 
* Framework dir:
* /System/Library/Frameworks/OpenGL.framework/Libraries
* -------------------------------------------------------------------------------- 
* How to compile
* g++ -o draw_point draw_point.c -framework GLUT -framework OpenGL 
*
*/

void drawTriangle(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0f,1.0f,0.0f); // point color

    glBegin(GL_TRIANGLES); 
      glVertex3f(0.5f, 0.5f, 0.0f);
      glVertex3f(-0.5f, 0.5f, 0.0f);
      glVertex3f(-0.5f, -0.5f, 0.0f);
    glEnd();

    glLoadIdentity();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (300,300);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Draw GL_TRIANGLES");

    glutDisplayFunc(drawTriangle);

    glutMainLoop();

    return 0;
}
