
/*
* Sat Oct 15 02:37:11 PDT 2016
* --------------------------------------------------------------------------------
* Apple LLVM version 7.3.0 (clang-703.0.29)
* Target: x86_64-apple-darwin15.4.0
* Thread model: posix
* InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
* --------------------------------------------------------------------------------
* OS EL Capitan 10.11.4 (15E65)
* Graphic Card: NVIDIA GeForce GT 650M 1024 MB
* --------------------------------------------------------------------------------
* Compile:
* g++ -o cube cube.cpp -I /opt/X11/include/GL/glext.h -framework GLUT -framework OpenGL -framework Cocoa
*/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <sstream>
#include <iomanip>

using std::stringstream;
using std::cout;
using std::endl;
using std::ends;

// GLUT CALLBACK functions
void displayCB();
void reshapeCB(int w, int h);
void timerCB(int millisec);

void initGL();
int  initGLUT(int argc, char **argv);
bool initSharedMem();
void initLights();
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
void toPerspective();
void draw();


// constants
const int   SCREEN_WIDTH    = 400;
const int   SCREEN_HEIGHT   = 300;
const float CAMERA_DISTANCE = 10.0f;
const int   TEXT_WIDTH      = 8;
const int   TEXT_HEIGHT     = 13;


// global variables
void *font = GLUT_BITMAP_8_BY_13;
int screenWidth;
int screenHeight;
float cameraAngleX;
float cameraAngleY;
float cameraDistance;
int drawMode;
int maxVertices;
int maxIndices;

#ifdef _WIN32
// glDrawRangeElements() defined in OpenGL v1.2 or greater
PFNGLDRAWRANGEELEMENTSPROC pglDrawRangeElements = 0;
#define glDrawRangeElements pglDrawRangeElements
#endif



// cube ///////////////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

// vertex coords array for glDrawArrays() =====================================
// A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
// of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 108 floats (36 * 3 = 108).
GLfloat vertices1[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
                        -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

                        1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
                        1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

                        1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
                        -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

                        -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
                        -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

                        -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
                        1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

                        1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
                        -1, 1,-1,   1, 1,-1,   1,-1,-1
                      };    // v6-v5-v4

// normal array
GLfloat normals1[]  = { 0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
                        0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

                        1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

                        0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

                        -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
                        -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

                        0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
                        0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

                        0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
                        0, 0,-1,   0, 0,-1,   0, 0,-1
                      };    // v6-v5-v4

// color array
GLfloat colors1[]   = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
                        1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

                        1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
                        0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

                        1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
                        0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

                        1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
                        0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

                        0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
                        1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

                        0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
                        0, 1, 0,   0, 1, 1,   0, 0, 1
                      };    // v6-v5-v4


///////////////////////////////////////////////////////////////////////////////
// draw cube at upper-right corner with glDrawArrays
// A cube has only 8 vertices, but each vertex is shared for 3 different faces,
// which have different normals. Therefore, we need more than 8 vertex data to
// draw a cube. Since each face has 2 triangles, we need 6 vertices per face.
// (2 * 3 = 6) And, a cube has 6 faces, so, the total number of vertices for
// drawing a cube is 36 (= 6 faces * 6 vertices).
// Note that there are some duplicated vertex data for glDrawArray() because
// the vertex data in the vertex array must be sequentially placed in memory.
// For a cube, there are 24 unique vertex data and 12 redundant vertex data in
// the vertex array.
///////////////////////////////////////////////////////////////////////////////
void draw() {
    // enble and specify pointers to vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normals1);
    glColorPointer(3, GL_FLOAT, 0, colors1);
    glVertexPointer(3, GL_FLOAT, 0, vertices1);

    glPushMatrix();
    glTranslatef(2, 2, 0);                  // move to upper-right corner

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}






///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    // init global vars
    initSharedMem();

    // init GLUT and GL
    initGLUT(argc, argv);
    initGL();

    // check max of elements vertices and elements indices that your video card supports
    // Use these values to determine the range of glDrawRangeElements()
    // The constants are defined in glext.h
    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxVertices);
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxIndices);

    // the last GLUT call (LOOP)
    // window will be shown and display callback is triggered by events
    // NOTE: this call never return main().
    glutMainLoop(); /* Start GLUT event-processing loop */

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// initialize GLUT for windowing
///////////////////////////////////////////////////////////////////////////////
int initGLUT(int argc, char **argv) {
    // GLUT stuff for windowing
    // initialization openGL window.
    // it is called before any other GLUT routine
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

    glutInitWindowSize(screenWidth, screenHeight);  // window size

    glutInitWindowPosition(100, 100);               // window location

    // finally, create a window with openGL context
    // Window will not displayed until glutMainLoop() is called
    // it returns a unique ID
    int handle = glutCreateWindow(argv[0]);     // param is the title of window

    // register GLUT callback functions
    glutDisplayFunc(displayCB);

    glutTimerFunc(33, timerCB, 33);             // redraw only every given millisec
    glutReshapeFunc(reshapeCB);

    return handle;
}



///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void initGL() {
    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

    // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    initLights();
}



///////////////////////////////////////////////////////////////////////////////
// initialize global variables
///////////////////////////////////////////////////////////////////////////////
bool initSharedMem() {
    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;
    cameraAngleX = cameraAngleY = 0.0f;
    cameraDistance = CAMERA_DISTANCE;
    maxVertices = maxIndices = 0;

    return true;
}


///////////////////////////////////////////////////////////////////////////////
// initialize lights
///////////////////////////////////////////////////////////////////////////////
void initLights() {
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
}

///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}

///////////////////////////////////////////////////////////////////////////////
// set the projection matrix as perspective
///////////////////////////////////////////////////////////////////////////////
void toPerspective() {
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);

    // set perspective viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)(screenWidth)/screenHeight, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void displayCB() {
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // save the initial ModelView matrix before modifying ModelView matrix
    glPushMatrix();

    glTranslatef(0, 0, -cameraDistance);
    glRotatef(80, 1, 0, 0);   // pitch
    glRotatef(60, 0, 1, 0);   // heading

    draw();        // with glDrawArrays()

    glPopMatrix();
    glutSwapBuffers();
}

void reshapeCB(int w, int h) {
    screenWidth = w;
    screenHeight = h;
    toPerspective();
}

void timerCB(int millisec) {
    glutTimerFunc(millisec, timerCB, millisec);
    glutPostRedisplay();
}

