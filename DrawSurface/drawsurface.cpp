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

// A camera.  It moves horizontally in a circle centered at the origin of
// radius 10.  It moves vertically straight up and down.
class Camera {
    double theta;      // determines the x and z positions
    double y;          // the current y position
    double dTheta;     // increment in theta for swinging the camera around
    double dy;         // increment in y for moving the camera up/down
public:
    Camera(): theta(-1.2), y(3), dTheta(0.04), dy(0.2) {}
    double getX() {
        return 10 * cos(theta);
    }
    double getY() {
        return y;
    }
    double getZ() {
        return 10 * sin(theta);
    }
    void moveRight() {
        theta += dTheta;
    }
    void moveLeft() {
        theta -= dTheta;
    }
    void moveUp() {
        y += dy;
    }
    void moveDown() {
        //if (y > dy) y -= dy;
        y -= dy;
    }
};

// Global variables: a camera, a CheckerBoard and some balls.
CheckerBoard checker_board(9, 9);
Camera camera;

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

//class BezierSurfaceBatch {
//    static int const PSIZE = 4;
//    Vector3 arr[PSIZE][PSIZE];
//    Curve* cListu[PSIZE];
//    Curve** cListv = NULL;
//    int nCurve = 0;
//
//    public:
//    BezierSurfaceBatch(GLfloat arrf[PSIZE][PSIZE][3]) {
//        for(int i=0; i<PSIZE; i++) {
//            for(int j=0; j<PSIZE; j++) {
//                arr[i][j] = Vector3(arrf[i][j]);
//            }
//        }
//    }
//    void create() {
//        Node<Vector3>* curr[PSIZE];
//        for(int i=0; i<PSIZE; i++) {
//            cListu[i] = new Curve(arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
//            curr[i] = cListu[i]->ddl->head;
//        }
//
//        nCurve = cListu[0]->ddl->count();
//        int k = 0;
//        cListv = new Curve*[nCurve];
//        while(k < nCurve) {
//            cListv[k] = new Curve(curr[0]->data, curr[1]->data, curr[2]->data, curr[3]->data);
//            for(int i=0; i<PSIZE; i++) {
//                curr[i] = curr[i]->next;
//            }
//            k++;
//        }
//    }
//    void draw() {
//        // initial four control points in u direction
//        // u direction
//        for(int i=0; i<PSIZE; i++) {
//            cListu[i]->setColor(curveColor2);
//            cListu[i]->draw();
//        }
//        // each four control points for each bezier curve in v direction
//        for(int i=0; i<nCurve; i++) {
//            cListv[i]->setColor(curveColor1);
//            cListv[i]->draw();
//        }
//    }
//    ~BezierSurfaceBatch() {
//        for(int i=0; i<PSIZE; i++) {
//            delete cListu[i];
//        }
//
//        for(int i=0; i<nCurve; i++) {
//            delete cListv[i];
//        }
//        if(cListv)
//            delete cListv;
//        cListv = NULL;
//    }
//};
//
BezierSurfaceBatch bezier(myarr);

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
    bezier.create();
    glEnable(GL_DEPTH_TEST);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, RED);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
//    glMaterialf(GL_FRONT, GL_SHININESS, 30);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    checker_board.setColor(GREEN, WHITE);
//    checker_board.create();
}

// Draws one frame, the CheckerBoard then the balls, from the current camera
// position.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    //checker_board.draw();
    //curve->draw();
    //curve4->draw();
//    torus2.draw();
//    draw_quad.draw();
//    co.draw();

//    initCurve();
    bezier.draw();
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

// Moves the camera according to the key pressed, then ask to refresh the
// display.
void special(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT:
        camera.moveLeft();
        break;
    case GLUT_KEY_RIGHT:
        camera.moveRight();
        break;
    case GLUT_KEY_UP:
        camera.moveUp();
        break;
    case GLUT_KEY_DOWN:
        camera.moveDown();
        break;
    }
    glutPostRedisplay();
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
    glutSpecialFunc(special);
    glutTimerFunc(100, timer, 0);
    init();
    glutMainLoop();
}
