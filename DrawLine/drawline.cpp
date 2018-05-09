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

void drawLine(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,1.0f,0.0f); // point color
    glPointSize(10.0f);
    
    glBegin(GL_LINE_LOOP); //starts drawing of points
      glVertex3f(0.0f, 0.0f,0.0f);
      glVertex3f(1.0f,0.0f,0.0f);
      glVertex3f(1.0f,1.0f,0.0f);
      glVertex3f(0.0f,1.0f,0.0f);
    glEnd();

    glLoadIdentity();
    glutSwapBuffers();
}

void draw(void){
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat z = 0.0;
    GLfloat r = 1.0;

    GLfloat WHITE[3] = {1, 1, 1};
    GLfloat RED[3] = {1, 0, 0};
    GLfloat GREEN[3] = {0, 1, 0};
    GLfloat MAGENTA[3] = {1, 0, 1};
    int len = 20;
    GLfloat dr = (GLfloat)1/len;

    GLfloat pi = 2*M_PI; 
    GLfloat delta = (GLfloat)pi/len;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,1.0f,0.0f); // point color
    glPointSize(10.0f);

    glPushMatrix();
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, -1.0f, -1.0f);
    for(int j=0; j<len; j++){
        if(j % 2 == 0)
            glColor3f(1.0f,0.0f,0.0f); // point color
        else
            glColor3f(0.0f,1.0f,0.0f); // point color

        
        glBegin(GL_LINE_LOOP); //starts drawing of points
        for(int i=0; i<len; i++){
            x = r*sin(delta*i);
            y = (dr*j)*(dr*j);
            z = r*cos(delta*i); 
            glVertex3f(x, y, z);
        } 
        glEnd();
    } 
    glPopMatrix();

    glLoadIdentity();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500,500);
    glutInitWindowPosition (200, 200);
    glutCreateWindow ("Draw GL_LINE_LOOP");
    //glutDisplayFunc(drawLine);
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
