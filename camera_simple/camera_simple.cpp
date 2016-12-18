// This application shows balls bouncing on a checkerboard, with no respect
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
#include "Utility.h"

DDLinkedList<Vector3>* ddl_u = new DDLinkedList<Vector3>();
DDLinkedList<Vector3>* ddl_v = new DDLinkedList<Vector3>();
DDLinkedList<Vector3>* ddv4 = new DDLinkedList<Vector3>();
const int MV = 3;
DDLinkedList<Vector3>* ddv[2][MV];
DDLinkedList<Vector3>* listdd[3];

const int MAX_U = 4;
const int MAX_V = 4;
DDLinkedList<Vector3>* ddl_arr[MAX_U][MAX_V];


// Colors
GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0};
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

// A ball.  A ball has a radius, a color, and bounces up and down between
// a maximum height and the xz plane.  Therefore its x and z coordinates
// are fixed.  It uses a lame bouncing algorithm, simply moving up or
// down by 0.05 units at each frame.
class Ball {
    double radius;
    GLfloat* color;
    double maximumHeight;
    double x;
    double y;
    double z;
    int direction;
public:
    Ball(double r, GLfloat* c, double h, double x, double z):
        radius(r), color(c), maximumHeight(h), direction(-1),
        y(h), x(x), z(z) {
    }
    void update() {
        y += direction * 0.05;
        if (y > maximumHeight) {
            y = maximumHeight;
            direction = -1;
        } else if (y < radius) {
            y = radius;
            direction = 1;
        }
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
        glTranslated(x, y, z);
        glutSolidSphere(radius, 30, 30);
        glPopMatrix();
    }
};

// A checkerboard class.  A checkerboard has alternating red and white
// squares.  The number of squares is set in the constructor.  Each square
// is 1 x 1.  One corner of the board is (0, 0) and the board stretches out
// along positive x and positive z.  It rests on the xz plane.  I put a
// spotlight at (4, 3, 7).
class Checkerboard {
    int displayListId;
    int width;
    int depth;
public:
    Checkerboard(int width, int depth): width(width), depth(depth) {}
    double centerx() {
        return width / 2;
    }
    double centerz() {
        return depth / 2;
    }
    void create() {
        displayListId = glGenLists(1);
        glNewList(displayListId, GL_COMPILE);
        GLfloat lightPosition[] = {4, 3, 7, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glBegin(GL_QUADS);
        glNormal3d(0, 1, 0);
        for (int x = 0; x < width - 1; x++) {
            for (int z = 0; z < depth - 1; z++) {
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                             (x + z) % 2 == 0 ? RED : WHITE);
                glVertex3d(x, 0, z);
                glVertex3d(x+1, 0, z);
                glVertex3d(x+1, 0, z+1);
                glVertex3d(x, 0, z+1);
            }
        }
        glEnd();
        glEndList();
    }
    void draw() {
        glCallList(displayListId);
    }
};

// Global variables: a camera, a checkerboard and some balls.
Checkerboard checkerboard(8, 8);
Camera camera;
Ball balls[] = {
    Ball(1, GREEN, 7, 6, 1),
    Ball(1.5, MAGENTA, 6, 3, 4),
    Ball(0.4, WHITE, 5, 1, 7)
};


// Application-specific initialization: Set up global lighting parameters
// and create display lists.
void init() {
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    checkerboard.create();
}

void get_curve_vertex_u() {
    Vector3 v0(-1.0f, 0.0f, 0.0f);
    Vector3 v1(0.0f, 1.0f, 0.0f);
    Vector3 v2(1.0f, 0.0f, 0.0f);

    int level = 3;
    beziercurve(v0, v1, v2, ddl_u, level);
}
void get_curve_vertex_v() {
    Vector3 v0(-1.0f, -1.0f, 0.0f);
    Vector3 v1(-1.0f, 0.0f,  0.0f);
    Vector3 v2(-1.0f, 1.0f,  0.0f);

    Vector3 v3(0.0f, -1.0f, 0.0f);
    Vector3 v4(0.0f, 0.0f, 1.0f);
    Vector3 v5(0.0f, 1.0f, 0.0f);

    Vector3 v6(1.0f, -1.0f, 0.0f);
    Vector3 v7(1.0f, 0.0f, 0.0f);
    Vector3 v8(1.0f, 1.0f, 0.0f);

    for(int j=0; j<2; j++){
        for(int i=0; i<MV; i++){
            ddv[j][i] = new DDLinkedList<Vector3>();
        }
    }

    Vector3 arr[2][3][3] = {
        {{v0, v1, v2},
        {v3, v4, v5},
        {v6, v7, v8}},

        {{v0, v3, v6},
        {v1, v4, v7},
        {v2, v5, v8}},
    };

    for(int j=0; j<2; j++) {
        for(int i=0; i<3; i++) {
            int level = 5;
            beziercurve(arr[j][i][0], arr[j][i][1], arr[j][i][2], ddv[j][i], level);
        }
    }
}


void get_curve_vertex_4(){
    Vector3* arr[3][3];
    Vector3 v0(-1.0f, 0.0f + 1.0f, 0.0f);
    Vector3 v1(0.0f, 0.0f + 1.0f,  0.0f);
    Vector3 v2(1.0f, 0.0f + 1.0f,  0.0f);
    Vector3 v3(2.0f, 0.0f + 1.0f,  0.0f);

    Vector3 p0(0.0f, 0.0f + 0.5f, 0.0f);

    int len = 3;
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            arr[i][j] = new Vector3(p0.v[0] + j, p0.v[1] + i, p0.v[2]); 
        } 
    } 

//    Vector3 v0(-1.0f, 0.0f, 0.0f);
//    Vector3 v1(0.0f, 0.0f,  0.0f);
//    Vector3 v2(1.0f, 0.0f,  0.0f);
//    Vector3 v3(2.0f, 0.0f,  0.0f);

    //beziercurve4(v0, v1, v2, v3, ddv4, level);

    int level = 10;
    for(int i=0; i<3; i++){
        beziercurve4(*arr[i][0], *arr[i][1], *arr[i][2], *arr[i][3], ddl_arr[0][i], level);
    }

    int count = ddl_arr[0][0]->count();
    Vector3** array = new Vector3*[MAX_U];
    for(int i=0; i<MAX_U; i++){
        array[i] = new Vector3[count];
        Node<Vector3>* curr = ddl_arr[0][i]->head;
        int k=0;
        while(curr){
            array[i][k] = curr->data;
            curr = curr->next;
            k++;
        }
    }
    
    DDLinkedList<Vector3>* dlist = new DDLinkedList<Vector3>();
    for(int i=0; i<count; i++){
        //beziercurve4(*arr[0][i], *arr[1][i], *arr[2][i], *arr[3][i], ddl_arr[1][i], level);
        beziercurve(array[0][i], array[1][i], array[2][i], dlist, level);
    }
}
void draw_surface(){
    Vector3* arr[3][3];
    Vector3 p0(0.0f, 0.0f + 0.5f, 0.0f);

    int len = 3;
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            arr[i][j] = new Vector3(p0.v[0] + j, p0.v[1] + i, p0.v[2]); 
        } 
    } 

    int level = 3;
    for(int i=0; i<3; i++){
        beziercurve(*arr[i][0], *arr[i][1], *arr[i][2], listdd[i], level);
    }
    
//    for(int i=0; i<len; i++){
//        for(int j=0; j<len; j++){
//            delete arr[i][j];
//        } 
//    } 
}

void draw_curve_4() {
    int len = 2; 
    for(int j=0; j<len; j++){
        for(int i=0; i<MAX_U; i++){
            glBegin(GL_LINE_STRIP);
            glNormal3d(0, 1, 0);
            int c = 0;
            Node<Vector3>* curr = ddl_arr[j][i]->head;
            while(curr) {
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c % 2 == 0 ? RED : WHITE);
                Vector3 v = curr->data;
                glVertex3d(v.v[0], v.v[1], v.v[2]);
                c++;
                curr = curr->next;
            }
            glEnd();
        } 
    } 
}

void draw_curve_u() {
    glBegin(GL_LINE_STRIP);
    glNormal3d(0, 1, 0);
    int c = 0;
    Node<Vector3>* curr = ddl_u->head;


    while(curr) {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c % 2 == 0 ? RED : WHITE);
        Vector3 v = curr->data;
        glVertex3d(v.v[0], v.v[1], v.v[2]);
        curr = curr->next;
        c++;
    }
    glEnd();
}

void draw_curve_v() {
    for(int j=0; j<2; j++) {
        for(int i=0; i<MV; i++) {
            glBegin(GL_LINE_STRIP);
            glNormal3d(0, 1, 0);
            int c = 0;
            Node<Vector3>* curr = ddv[j][i]->head;
            while(curr) {
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c % 2 == 0 ? RED : WHITE);
                Vector3 v = curr->data;
                glVertex3d(v.v[0], v.v[1], v.v[2]);
                curr = curr->next;
                c++;
            }
            glEnd();
        }
    }

}

// Draws one frame, the checkerboard then the balls, from the current camera
// position.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              checkerboard.centerx(), 0.0, checkerboard.centerz(),
              0.0, 1.0, 0.0);
    checkerboard.draw();

//  for (int i = 0; i < sizeof balls / sizeof(Ball); i++) {
//    balls[i].update();
//  }

    //draw_curve_u();
    //draw_curve_v();
    //draw_curve_4();
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
    //get_curve_vertex_u();
    //get_curve_vertex_v();
    //get_curve_vertex_4();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutTimerFunc(100, timer, 0);
    init();
    glutMainLoop();
}
