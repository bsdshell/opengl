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
int filling=1; // 0=OFF 1=ON

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

void draw(void){
    GLfloat WHITE[3]   = {1, 1, 1};
    GLfloat RED[3]     = {1, 0, 0};
    GLfloat GREEN[3]   = {0, 1, 0};
    GLfloat MAGENTA[3] = {1, 0, 1};

    GLfloat x0 = 0.0;
    GLfloat y0 = 0.0;
    GLfloat z0 = 0.0;

    GLfloat x1 = 0.0;
    GLfloat y1 = 0.0;
    GLfloat z1 = 0.0;
    GLfloat r = 1.0;
    int len = 20;
    GLfloat dr = (GLfloat)1/len;
    GLfloat delta = (GLfloat)2*M_PI/len;

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    GLfloat lightPosition[] = {0, 2, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glNormal3d(0, 1, 0);

    for(int j=0; j<len; j++){
        if(j % 2 == 0)
            glColor3f(1.0f,0.0f,0.0f); // point color
        else
            glColor3f(0.0f,1.0f,0.0f); // point color

        glBegin(GL_QUAD_STRIP); //starts drawing of points
        GLfloat rq = dr*j;
        GLfloat rq1 = dr*(j + 1);
        for(int i=0; i<=len; i++){
            x0 = rq*sin(delta*i);
            y0 = rq*rq;
            z0 = rq*cos(delta*i); 

            x1 = rq1*sin(delta*i);
            y1 = rq1*rq1;
            z1 = rq1*cos(delta*i); 

            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                         (i + j) % 2 == 0 ? GREEN : MAGENTA);
            glMaterialf(GL_FRONT, GL_SHININESS, 40);
            glVertex3f(x0, y0, z0);
            glVertex3f(x1, y1, z1);
        } 
        glEnd();
    } 
    glPopMatrix();

    glLoadIdentity();
//    glutSwapBuffers();
}

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

    draw();
    //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

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
    case 'w':
        if (filling==0) {
            // Polygon rasterization mode (polygon filled)
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
            filling=1;
        } else {
            // Polygon rasterization mode (polygon outlined)
            glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
            filling=0;
        }
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
