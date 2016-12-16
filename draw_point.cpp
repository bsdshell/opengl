#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/
#include "MyLib.h"

/*OpenGL. Draw point with GL_POINTS 
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

//class Vector3{
//    public:
//    GLdouble v[3];
//    public:
//    Vector3(){ }
//    public:
//    Vector3(const Vector3& other){
//        this->v[0] = other.v[0];
//        this->v[1] = other.v[1];
//        this->v[2] = other.v[2];
//    }
//    Vector3(GLdouble x, GLdouble y, GLdouble z){ 
//        v[0] = x;
//        v[1] = y;
//        v[2] = z;
//    }
//
//    Vector3(GLdouble arr[3]){ 
//        v[0] = arr[0];
//        v[1] = arr[1];
//        v[2] = arr[2];
//    }
//
//    Vector3& operator=(const Vector3& rhs){
//        this->v[0] = rhs.v[0];
//        this->v[1] = rhs.v[1];
//        this->v[2] = rhs.v[2];
//        return *this; 
//    }
//    Vector3 operator+(Vector3& rhs){
//        Vector3 v; 
//        v.v[0] = this->v[0] + rhs.v[0];
//        v.v[1] = this->v[1] + rhs.v[1];
//        v.v[2] = this->v[2] + rhs.v[2];
//        return v; 
//    }
//    Vector3 operator-(Vector3& rhs){
//        Vector3 v; 
//        v.v[0] = this->v[0] - rhs.v[0];
//        v.v[1] = this->v[1] - rhs.v[1];
//        v.v[2] = this->v[2] - rhs.v[2];
//        return v;
//    }
//    Vector3 operator/(GLdouble n){
//        //Vector3* v = new Vector3(); 
//        Vector3 v; 
//        v.v[0] = this->v[0]/n;
//        v.v[1] = this->v[1]/n;
//        v.v[2] = this->v[2]/n;
//        return v;
//    }
//
//    Vector3 dot(Vector3& rhs){
//        Vector3 v; 
//        v.v[0] = this->v[0] * rhs.v[0];
//        v.v[1] = this->v[1] * rhs.v[1];
//        v.v[2] = this->v[2] * rhs.v[2];
//        return v;
//    }
//};
//
void test1(void){
    Vector3 v1(0, 0, 0);
    Vector3 v2(1, 2, 3);
    Vector3 v3 = v1 + v2;
    printf("[%f] [%f] [%f]\n", v3.v[0], v3.v[1], v3.v[2]);
}

void test2(void){
    Vector3 v2(1, 2, 3);
    Vector3 v3 = v2/2.0;
    printf("[%f] [%f] [%f]\n", v3.v[0], v3.v[1], v3.v[2]);
}

void test3(void){
    Vector3 v1(1, 2, 3);
    Vector3 v2(3, 4, 5);
    Vector3 v3 = v1 - v2;
    printf("[%f] [%f] [%f]\n", v3.v[0], v3.v[1], v3.v[2]);
}

void test4(void){
    Vector3 v1(1, 2, 3);
    Vector3 v2(3, 4, 5);
    Vector3 v3 = v1.dot(v2); 
    printf("[%f] [%f] [%f]\n", v3.v[0], v3.v[1], v3.v[2]);
}
void test5(void){
    Vector3 v1(1, 2, 3);
    Vector3 v3 = v1;
    printf("[%f] [%f] [%f]\n", v3.v[0], v3.v[1], v3.v[2]);
}

void drawPoint(void){
    Vector3* vect = new Vector3(0.0f, 1.0f, 0.0f);
    Vector3 v(0.0f, 1.0f, 0.0f);
    Vector3 v1(0.5f,0.5f,0.0f);
    Vector3 v2(0.0f,0.1f,0.1f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(v.v[0], v.v[1], v.v[2]); // point color

    glPointSize(10.0f);
    glBegin(GL_POINTS); //starts drawing of points
      glVertex3f(v1.v[0], v1.v[1], v1.v[2]);
      glVertex3f(v2.v[0], v2.v[1], v2.v[2]);
    glEnd();

    glLoadIdentity();
    glutSwapBuffers();

    test1();
}

int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize (300,300);
//    glutInitWindowPosition (100, 100);
//    glutCreateWindow ("Draw GL_POINTS");
//
//    glutDisplayFunc(drawPoint);
//
//    glutMainLoop();
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
