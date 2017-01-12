#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/

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

void drawPoint(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,1.0f,0.0f); // point color
    glPointSize(10.0f);

    glBegin(GL_POINTS); //starts drawing of points
      //glVertex3f(0.5f,0.5f,-1.0f);
      glVertex3f(0.0f,0.0f,-1.0f);
    glEnd();

    glLoadIdentity();
    glutSwapBuffers();
}

void drawCoordinate(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5f,0.5f,1.0f); // point color
    glBegin(GL_LINE); 
      //glVertex3f(0.5f,0.5f,-1.0f);
      glVertex3f(-1.0f, 0.0f, -1.0f);
      glVertex3f(1.0f, 0.0f, -1.0f);
      glVertex3f(0.0f, 0.0f, -1.0f);
      glVertex3f(1.0f, 0.0f, -1.0f);
    glEnd();

    glLoadIdentity();
    glutSwapBuffers();
}

void display(void){
    //drawPoint();
    drawCoordinate();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}


void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, v);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (300,300);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Draw GL_POINTS");
    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);
    glutMainLoop();

    return 0;
}
