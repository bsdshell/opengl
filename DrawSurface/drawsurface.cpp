// This application shows balls bouncing on a CheckerBoard, with no respect
// for the laws of Newtonian Mechanics.  There's a little spotlight to make
// the animation interesting, and arrow keys move the camera for even more
// fun.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

#include "BezierCurve.h"
#include "Curve.h"
#include "Torus.h"
#include "CheckerBoard.h"
#include "Circle.h"
#include "Cylinder.h"
#include "DrawQuad.h"
#include "Coordinate.h"
#include "Color.h"
#include "Const.h"
#include "BezierSurfaceBatch.h"
#include "ReadTeapot.h"
#include "cameraKeyBoard.h"

// Global variables: a camera, a CheckerBoard and some balls.
CheckerBoard checker_board(9, 9);
//Camera camera;

DDLinkedList<Vector3>* ddl_arr[4];
Curve* curveListu[4];
Curve* curveListv[50];
Node<Vector3>* currArr[500];

Vector3 p0(-1, 0, 0);
Vector3 p1(0, 1, 0);
Vector3 p2(1, 0, 0);
Curve* curve = new Curve(p0, p1, p2);

Vector3 p00(-1, 0, 0);
Vector3 p11(0, 1, 0);
Vector3 p22(1, 1, 0);
Vector3 p33(2, 0, 0);

Curve* curve4 = new Curve(p00, p11, p22, p33);
GLfloat curveColor0[3] = {1.0, 0.0, 0.0};
GLfloat curveColor1[3] = {0.0, 1.0, 0.0};
GLfloat curveColor2[3] = {0.0, 0.0, 1.0};
GLfloat curveColor3[3] = {1.0, 1.0, 0.0};

Torus torus(1, 1, 1, 8, 25);
Torus torus2(20, 40);
Circle circle(1, 1, 1, 20);
Cylinder cylinder(1, 1, 0.2, 20);
DrawQuad draw_quad;
Coordinate co(8);

GLfloat xx = 1.0;
GLfloat yy = 1.0;
GLfloat zz = 1.0;
GLfloat myarr[4][4][3] = {
    {
        {0.0, 0.0, 0.0f},
        {1.0, 1.0, 0.0f},
        {2.0, 1.0, 0.0f},
        {3.0, 0.0, 0.0f}
    },
    {
        {0.0, 0.0, 0.0f + xx},
        {1.0, 5.0, 0.0f + xx},
        {2.0, 5.0, 0.0f + xx},
        {3.0, 0.0, 0.0f + xx}
    },
    {
        {0.0, 0.0, 0.0f + 2*xx},
        {1.0, -3.0, 0.0f + 2*xx},
        {2.0, -2.0, 0.0f + 2*xx},
        {3.0, 0.0, 0.0f + 2*xx}
    },
    {
        {0.0, 0.0, 0.0f + 3*xx},
        {1.0, 1.0, 0.0f + 3*xx},
        {2.0, 1.0, 0.0f + 3*xx},
        {3.0, 0.0, 0.0f + 3*xx}
    }
};

//GLfloat myarr[4][4][3] = {
//    {
//        {0.409091,0.772727,0.0},
//        {0.409091,0.772727,-0.229091},
//        {0.229091,0.772727,-0.409091},
//        {0.0,0.772727,-0.409091}
//    },
//    {
//        {0.409091,0.886364,0.0},
//        {0.409091,0.886364,-0.229091},
//        {0.229091,0.886364,-0.409091},
//        {0.0,0.886364,-0.409091}
//    },
//    {
//        {0.454545,0.886364,0.0},
//        {0.454545,0.886364,-0.254545},
//        {0.254545,0.886364,-0.454545},
//        {0.0,0.886364,-0.454545}
//    },
//    {
//        {0.454545,0.772727,0.0},
//        {0.454545,0.772727,-0.254545},
//        {0.254545,0.772727,-0.454545},
//        {0.0,0.772727,-0.454545}
//    }
//};
//

BezierSurfaceBatch bezier(myarr);

BezierSurfaceBatch* bez[26]; 

float arrf[26][4][4][3];
ReadTeapot readTeapot("teacup", arrf);

void initCurve() {
    for(int i=0; i<4; i++) {
        ddl_arr[i] = new DDLinkedList<Vector3>();
    }

    Vector3 p0(-1, 0, 0);
    Vector3 p1(0, 1, 0);
    Vector3 p2(1, 1, 0);
    Vector3 p3(2, 0, 0);
    curveListu[0] = new Curve(p0, p1, p2, p3);
    curveListu[0]->setColor(curveColor0);
    ddl_arr[0] = curveListu[0]->ddl;

    Vector3 p4(-1, 0, 0.5);
    Vector3 p5(0, -1, 0.5);
    Vector3 p6(1, 1 + 2, 0.5);
    Vector3 p7(2, 0, 0.5);
    curveListu[1] = new Curve(p4, p5, p6, p7);
    curveListu[1]->setColor(curveColor1);
    ddl_arr[1] = curveListu[1]->ddl;

    Vector3 p8(-1, 0, 1.0);
    Vector3 p9(0, 1 + 2, 1.0);
    Vector3 p10(1, -1 , 1.0);
    Vector3 p11(2, 0, 1.0);
    curveListu[2] = new Curve(p8, p9, p10, p11);
    curveListu[2]->setColor(curveColor2);
    ddl_arr[2] = curveListu[2]->ddl;

    Vector3 p12(-1, 0, 1.5);
    Vector3 p13(0, 1, 1.5);
    Vector3 p14(1, 1, 1.5);
    Vector3 p15(2, 0, 1.5);
    curveListu[3] = new Curve(p12, p13, p14, p15);
    curveListu[3]->setColor(curveColor3);
    ddl_arr[3] = curveListu[3]->ddl;

    for(int i=0; i<4; i++) {
        pp(ddl_arr[i]->count());
        curveListu[i]->draw();
    }

    Node<Vector3>* curr0 = ddl_arr[0]->head;
    Node<Vector3>* curr1 = ddl_arr[1]->head;
    Node<Vector3>* curr2 = ddl_arr[2]->head;
    Node<Vector3>* curr3 = ddl_arr[3]->head;

    // take first 4 curves only
    int k=0;
    while(k < 21) {
        curveListv[k] = new Curve(curr0->data, curr1->data, curr2->data, curr3->data);
        curveListv[k]->draw();
        curr0 = curr0->next;
        curr1 = curr1->next;
        curr2 = curr2->next;
        curr3 = curr3->next;
        k++;
    }

    for(int i=0; i<21; i++) {
        currArr[i] = curveListv[i]->ddl->head;
    }

    int count = 0;
    while(count < curveListv[0]->ddl->count()) {
        glBegin(GL_LINE_STRIP); //starts drawing of points
        for(int i=0; i<21; i++) {
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(currArr[i]->data.v[0], currArr[i]->data.v[1], currArr[i]->data.v[2]);
            currArr[i] = currArr[i]->next;
        }
        count++;
        glEnd();
    }
}

// Application-specific initialization: Set up global lighting parameters
// and create display lists.
void init() {
    for(int i=0; i<26; i++){
        bez[i] = new BezierSurfaceBatch(arrf[i]);
        bez[i]->create();
    } 

    glEnable(GL_DEPTH_TEST);
}

// Draws one frame, the CheckerBoard then the balls, from the current camera
// position.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    for(int i=0; i<26; i++){
        bez[i]->draw();
    } 

    glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

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

// Requests to draw the next frame.
void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, v);
}


// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bouncing Balls");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, timer, 0);
    init();
    glutMainLoop();
}
