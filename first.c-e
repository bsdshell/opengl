#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/

/* OpenGL.   This first example shows the use of the OpenGl library
for some simple graphics. */

/* g++ -o glb glb.c -framework GLUT -framework OpenGL
        -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
        -lGL -lGLU -lm -lobjc -lstdc++ */

void display(void) {
    int i;
    double angle;
    glClear(GL_COLOR_BUFFER_BIT);
    for (i=0; i<360; i+=4) {

        glColor3f(float(i)/360.0,1.0,1.0);
        glBegin(GL_LINES);
        glVertex2d(cos(i/57.25779),sin(i/57.25779));
        glVertex2d(cos((i+90)/57.25779),sin((i+90)/57.25779));
        glEnd();

        glColor3f(1.0,float(i)/360.0,1.0);
        glBegin(GL_LINES);
        glVertex2d(cos(i/57.25779),sin(i/57.25779));
        glVertex2d(cos((i*2)/57.25779),sin((i+90)/57.25779));
        glEnd();
    }
    glLoadIdentity();
    glutSwapBuffers();
}

void drawPoint(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0f,1.0f,0.0f); // point color

    glPointSize(10.0f);
    glBegin(GL_POINTS); //starts drawing of points
      glVertex3f(0.5f,0.5f,0.0f);//upper-right corner
      glVertex3f(0.0f,0.0f,0.0f);//lower-left corner
    glEnd();//end drawing of points

    glLoadIdentity();
    glutSwapBuffers();
}

void drawTriangle(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

//    GLfloat vertices[9]={
//        {0.0f, 0.0f, 0.0f},
//        {1.0f, 1.0f, 1.0f},
//        {1.0f, 1.0f, 0.0f}
//    };
//
//    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, vertices);
//    //glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, triangle);
//    glEnableVertexAttribArray(ATTRIB_VERTEX);
//
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//
//

    glEnd();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (300,300);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("OpenGL / C Example - Well House");

    //glutDisplayFunc(display);
    glutDisplayFunc(drawPoint);

    glutMainLoop();

    return 0;
}
