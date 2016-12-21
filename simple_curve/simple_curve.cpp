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

// Colors
GLfloat RED[] = {1, 0, 0};
GLfloat WHITE[] = {1, 1, 1};
GLfloat GREEN[] = {0, 1, 0};
GLfloat MAGENTA[] = {1, 0, 1};

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
        if (y > dy) y -= dy;
    }
};

// A CheckerBoard class.  A CheckerBoard has alternating red and white
// squares.  The number of squares is set in the constructor.  Each square
// is 1 x 1.  One corner of the board is (0, 0) and the board stretches out
// along positive x and positive z.  It rests on the xz plane.  I put a
// spotlight at (4, 3, 7).
//class Checkerboard {
//    int displayListId;
//    int width;
//    int depth;
//public:
//    Checkerboard(int width, int depth): width(width), depth(depth) {}
//    double centerx() {
//        return width / 2;
//    }
//    double centerz() {
//        return depth / 2;
//    }
//    void create() {
//        displayListId = glGenLists(1);
//        glNewList(displayListId, GL_COMPILE);
//        GLfloat lightPosition[] = {4, 3, 7, 1};
//        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//        glBegin(GL_QUADS);
//        glNormal3d(0, 1, 0);
//        for (int x = 0; x < width - 1; x++) {
//            for (int z = 0; z < depth - 1; z++) {
//                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
//                             (x + z) % 2 == 0 ? RED : WHITE);
//                glVertex3d(x, 0, z);
//                glVertex3d(x+1, 0, z);
//                glVertex3d(x+1, 0, z+1);
//                glVertex3d(x, 0, z+1);
//            }
//        }
//        glEnd();
//        glEndList();
//    }
//    void draw() {
//        glCallList(displayListId);
//    }
//};
//
//
// Global variables: a camera, a CheckerBoard and some balls.
CheckerBoard checker_board(9, 9);
Camera camera;

Curve* c = new Curve();
Torus torus(1, 1, 1, 8, 25);
Torus torus2(20, 40);
Circle circle(1, 1, 1, 20);
Cylinder cylinder(1, 1, 0.2, 20);
DrawQuad draw_quad;
Coordinate co(8);

// Application-specific initialization: Set up global lighting parameters
// and create display lists.
void init() {
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, RED);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    checker_board.setColor(GREEN, WHITE);
    checker_board.create();
}

// Draws one frame, the CheckerBoard then the balls, from the current camera
// position.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
//    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
//              checker_board.centerx(), 0.0, checker_board.centerz(),
//              0.0, 1.0, 0.0);
    checker_board.draw();
    c->draw();
    //torus(8, 25);
//    torus.draw();
    torus2.draw();
    //glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);


    //circle.draw();
//    glTranslatef(0.0, 0.0, -1.0);
//    glRotatef(60, 1.0, 0.0, 0.0);
//    glRotatef(-20, 0.0, 0.0, 1.0);

    //cylinder.draw();
    draw_quad.draw();
    co.draw();
    
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
