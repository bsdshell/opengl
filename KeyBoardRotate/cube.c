#include <stdio.h>
#include <GLUT/glut.h>

// Max number of vertices (for each object)
#define MAX_VERTICES 2000

// Max number of polygons (for each object)
#define MAX_POLYGONS 2000



/**********************************************************
*
* TYPES DECLARATION
*
*********************************************************/

/*** Our vertex type ***/
typedef struct {
    float x,y,z;
} vertex_type;

/*** The polygon (triangle), 3 numbers that aim 3 vertices ***/
typedef struct {
    int a,b,c;
} polygon_type;

/*** The object type ***/
typedef struct {
    vertex_type vertex[MAX_VERTICES];
    polygon_type polygon[MAX_POLYGONS];
} obj_type, *obj_type_ptr;



/**********************************************************
*
* VARIABLES DECLARATION
*
*********************************************************/

/*** The width and height of your window, change it as you like  ***/
int screen_width=640;
int screen_height=480;

/*** Absolute rotation values (0-359 degrees) and rotiation increments for each frame ***/
double rotation_x=0, rotation_x_increment=0.1;
double rotation_y=0, rotation_y_increment=0.05;
double rotation_z=0, rotation_z_increment=0.03;

/*** Flag for rendering as lines or filled polygons ***/
int filling=1; // 0=OFF 1=ON

/*** And, finally our first object! ***/
obj_type cube = {
    {
        -10, -10,  10,   // vertex v0
        10, -10,  10,   // vertex v1
        10, -10, -10,  // vertex v2
        -10, -10, -10,  // vertex v3
        -10,  10,  10,   // vertex v4
        10,  10,  10,   // vertex v5
        10,  10, -10,  // vertex v6
        -10,  10, -10   // vertex v7
    },
    {
        0, 1, 4,  // polygon v0,v1,v4
        1, 5, 4,  // polygon v1,v5,v4
        1, 2, 5,  // polygon v1,v2,v5
        2, 6, 5,  // polygon v2,v6,v5
        2, 3, 6,  // polygon v2,v3,v6
        3, 7, 6,  // polygon v3,v7,v6
        3, 0, 7,  // polygon v3,v0,v7
        0, 4, 7,  // polygon v0,v4,v7
        4, 5, 7,  // polygon v4,v5,v7
        5, 6, 7,  // polygon v5,v6,v7
        3, 2, 0,  // polygon v3,v2,v0
        2, 1, 0,  // polygon v2,v1,v0
    }
};



/**********************************************************
*
* SUBROUTINE init()
*
* Used to initialize OpenGL and to setup our world
*
*********************************************************/

void  init(void) {
    // This clear the background color to dark blue
    glClearColor(0.0, 0.0, 0.2, 0.0);

    // Type of shading for the polygons
    glShadeModel(GL_SMOOTH);



    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);



    // Projection transformation

    // Specifies which matrix stack is the target for matrix operations
    glMatrixMode(GL_PROJECTION);

    // We initialize the projection matrix as identity
    glLoadIdentity();

    // We define the "viewing volume"
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);


    // We enable the depth test (also called z buffer)
    glEnable(GL_DEPTH_TEST);

    // Polygon rasterization mode (polygon filled)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
}



/**********************************************************
*
* SUBROUTINE resize(int,int)
*
* This routine must be called everytime we resize our window.
*
*********************************************************/

void resize (int width, int height) {
    // We obtain the new screen width values and store it
    screen_width=width;

    // Height value
    screen_height=height;

    // We clear both the color and the depth buffer so to draw the next frame
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);

    // Projection transformation
    glMatrixMode(GL_PROJECTION);

    // We initialize the projection matrix as identity
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);

    // This command redraw the scene (it calls the same routine of glutDisplayFunc)
    glutPostRedisplay ();
}



/**********************************************************
*
* SUBROUTINE keyboard(unsigned char,int,int)
*
* Used to handle the keyboard input (ASCII Characters)
*
*********************************************************/

void keyboard (unsigned char key, int x, int y) {

    switch (key) {

    case ' ':
        rotation_x_increment=0;
        rotation_y_increment=0;
        rotation_z_increment=0;
        break;
    case 'r':
    case 'R':
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
}



/**********************************************************
*
* SUBROUTINE keyboard(int,int,int)
*
* Used to handle the keyboard input (not ASCII Characters)
*
*********************************************************/

void keyboard_s (int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP:
        rotation_x_increment = rotation_x_increment +0.005;
        break;
    case GLUT_KEY_DOWN:
        rotation_x_increment = rotation_x_increment -0.005;
        break;
    case GLUT_KEY_LEFT:
        rotation_y_increment = rotation_y_increment +0.005;
        break;
    case GLUT_KEY_RIGHT:
        rotation_y_increment = rotation_y_increment -0.005;
        break;
    }
}



/**********************************************************
*
* SUBROUTINE display()
*
* This is our main rendering subroutine, called each frame
*
*********************************************************/

void  display(void) {
    int l_index;

    // This clear the background color to dark blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Modeling transformation
    glMatrixMode(GL_MODELVIEW);

    // Initialize the model matrix as identity
    glLoadIdentity();

    // We move the object 50 points forward (the model matrix is multiplied by the
    // translation matrix)
    glTranslatef(0.0,0.0,-50);

    rotation_x = rotation_x + rotation_x_increment;
    rotation_y = rotation_y + rotation_y_increment;
    rotation_z = rotation_z + rotation_z_increment;

    if (rotation_x > 359) rotation_x = 0;
    if (rotation_y > 359) rotation_y = 0;
    if (rotation_z > 359) rotation_z = 0;

    // Rotations of the object (the model matrix is multiplied by the rotation matrices)
    glRotatef(rotation_x,1.0,0.0,0.0);
    glRotatef(rotation_y,0.0,1.0,0.0);
    glRotatef(rotation_z,0.0,0.0,1.0);

    // GlBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    glBegin(GL_TRIANGLES);
    for (l_index=0; l_index<12; l_index++) {
        // Color for the vertex
        glColor3f(1.0,0.0,0.0);
        glVertex3f( cube.vertex[ cube.polygon[l_index].a ].x,    cube.vertex[ cube.polygon[l_index].a ].y,    cube.vertex[ cube.polygon[l_index].a ].z);//Vertex definition
        glColor3f(0.0,1.0,0.0);
        glVertex3f( cube.vertex[ cube.polygon[l_index].b ].x,    cube.vertex[ cube.polygon[l_index].b ].y,    cube.vertex[ cube.polygon[l_index].b ].z);
        glColor3f(0.0,0.0,1.0);
        glVertex3f( cube.vertex[ cube.polygon[l_index].c ].x,    cube.vertex[ cube.polygon[l_index].c ].y,    cube.vertex[ cube.polygon[l_index].c ].z);
    }
    glEnd();

    // This force the execution of OpenGL commands
    glFlush();

    // In double buffered mode we invert the positions of the visible buffer and the writing buffer
    glutSwapBuffers();
}



/**********************************************************
*
* SUBROUTINE WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
*
* The main routine
*
*********************************************************/


// We need to init main correctly so we can pass the parameters to GLUT

int main(int argc, char **argv) {
    // GLUT init stuff
    // pass the arguments to GLUT and tell GLUT to init itself properly first!
    glutInit(&argc, argv);

    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // try the next line too if you want
    // glutInitDisplayString("rgba double depth=24");

    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Rotate Cube");

    /////////////////
    // GLUT Callbacks
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc (resize);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);

    /////////////////
    // init our own OpenGL-specific stuff
    init();

    /////////////////
    // main loop call
    glutMainLoop();

    return(0);
}
