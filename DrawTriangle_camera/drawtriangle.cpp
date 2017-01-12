#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/
#include "AronLib.h"
#include "CameraKeyBoard.h"
#include "Const.h"

/*OpenGL. Draw point with GL_POINTS 
* -------------------------------------------------------------------------------- 
* Mac OSX EL Capitan 10.11.4
* NVIDIA GeForce GT 650M 1024 MB 
* 
* Framework dir:
* /System/Library/Frameworks/OpenGL.framework/Libraries
* -------------------------------------------------------------------------------- 
* How to compile
*g++ -v -o draw_point draw_point.c -I/Users/cat/myfile/github/cpp/MyLib -framework GLUT -framework OpenGL
*
*/

void initLight(void) 
{
   GLfloat mat_specular[] = { 1.0, 0.0, 0.5, 1.0 };
   GLfloat mat_shininess[] = { 10.0 };
   GLfloat light_position[] = { -1.0, 2.0, 0.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_COLOR_MATERIAL);
}

void drawTriangle(){
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES); //starts drawing of points
      glColor3f(0.0f,1.0f,0.0f); // point color
      glVertex3f(0.0f, 0.0f,0.0f);
      glVertex3f(-1.0f, 0.0f,0.0f);
      glVertex3f(-1.0f, -1.0f,0.0f);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void drawCube(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLE_STRIP); //starts drawing of points
      glColor3f(0.0f,1.0f,0.0f); // point color

      glVertex3f(0.0f, 0.0f,0.0f);
      glVertex3f(1.0f, 0.0f,0.0f);
      glVertex3f(0.0f, 1.0f,0.0f);
      glVertex3f(1.0f, 1.0f,0.0f);

      glVertex3f(0.0f, 1.0f,-1.0f);
      glVertex3f(1.0f, 1.0f,-1.0f);
      glVertex3f(0.0f, 0.0f,-1.0f);
      glVertex3f(1.0f, 0.0f,-1.0f);

      glVertex3f(1.0f, 1.0f,0.0f);
      glVertex3f(1.0f, 0.0f,0.0f);
      glVertex3f(0.0f, 0.0f,-1.0f);
      glVertex3f(0.0f, 0.0f,0.0f);

      glVertex3f(0.0f,1.0f,-1.0f);
      glVertex3f(0.0f,1.0f,0.0f);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500,500);
    glutInitWindowPosition (200, 200);
    glutCreateWindow ("Draw GL_LINE_LOOP");
    initLight();
    glutDisplayFunc(drawTriangle);
//    glutDisplayFunc(drawCube);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutMainLoop();

    return 0;
}
