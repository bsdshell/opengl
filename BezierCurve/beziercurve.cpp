#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>

#define W 600
#define H 600

//--------------------------------------------------------------------------------
GLdouble midu[20][3];
GLdouble midv[20][3];
void bezier_curve(GLdouble p0[3], GLdouble p1[3], GLdouble p2[3], GLdouble mid[20][3], int* kp, int level) {
    if(level > 0) {
        GLdouble mm0[3];
        mm0[0] = (p0[0] + p1[0])/2;
        mm0[1] = (p0[1] + p1[1])/2;
        mm0[2] = (p0[2] + p1[2])/2;

        GLdouble mm1[3];
        mm1[0] = (p1[0] + p2[0])/2;
        mm1[1] = (p1[1] + p2[1])/2;
        mm1[2] = (p1[2] + p2[2])/2;

        GLdouble m[3];
        GLdouble x = m[0] = (mm0[0] + mm1[0])/2;
        GLdouble y = m[1] = (mm0[1] + mm1[1])/2;
        GLdouble z = m[2] = (mm0[2] + mm1[2])/2;

        bezier_curve(p0, mm0, m, mid, kp, level-1);

        mid[*kp][0] = m[0] = x;
        mid[*kp][1] = m[1] = y;
        mid[*kp][2] = m[2] = z;

        printf("mid[%d][0]=[%f] mid[%d][1]=[%f] mid[%d][2]=[%f]\n", *kp, mid[*kp][0], *kp, mid[*kp][1], *kp, mid[*kp][2]);

        (*kp)++;
        bezier_curve(m, mm1, p2, mid, kp, level-1);
    }
}

void draw_bezier_u() {
    for(int i=0; i<15; i++) {
        printf("[%d][0]=[%f] [%d][1]=[%f] ", i, midu[i][0], i, midu[i][0]);
        glVertex3f(midu[i][0], midu[i][1], midu[i][2]);
    }
}

void draw_bezier_v() {
    for(int i=0; i<15; i++) {
        printf("[%d][0]=[%f] [%d][1]=[%f] [%d][2]=[%f]", i, midv[i][0], i, midv[i][1], i, midv[i][2]);
        glVertex3f(midv[i][0], midv[i][1], midv[i][2]);
    }
}

void bezier_points_v() {
    GLdouble p0[3] = {0.0f, 0.0f, 1.0f};
    GLdouble p1[3] = {0.0f, 1.0f, 0.0f};
    GLdouble p2[3] = {0.0f, 0.0f, -1.0f};

    int max_size = 20;
    int kp = 0;
    int level = 4;

    bezier_curve(p0, p1, p2, midv, &kp, level);

}
void bezier_points_u() {
    GLdouble p0[3] = {-1.0f, 0.0f, 0.0f};
    GLdouble p1[3] = {0.0f, 1.0f, 0.0f};
    GLdouble p2[3] = {1.0f, 0.0f, 0.0f};

    int max_size = 20;
    int kp = 0;
    int level = 4;

    bezier_curve(p0, p1, p2, midu, &kp, level);

}
//--------------------------------------------------------------------------------


float z_axis[] =
{0.0, 0.0, 1.0};

void
norm(float v[3]) {
    float r;

    r = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    v[0] /= r;
    v[1] /= r;
    v[2] /= r;
}

void
cross(float v1[3], float v2[3], float result[3]) {
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

float
length(float v[3]) {
    float r = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return r;
}

static int winwidth = W, winheight = H;
GLUnurbsObj *nobj;
GLuint surflist, gridlist;

int useglunurbs = 0;
int smooth = 1;
GLboolean tracking = GL_FALSE;
int showgrid = 1;
int showsurf = 1;
int fullscreen = 0;
float modelmatrix[16];
float factor = 0.5;
float bias = 0.002;
int usegments = 4;
int vsegments = 4;

int spindx, spindy;
int startx, starty;
int curx, cury;
int prevx, prevy;       /* to get good deltas using glut */

void redraw(void);

/* Control points of the torus in Bezier form.  Can be rendered
   using OpenGL evaluators. */

void
move(int x, int y) {
    prevx = curx;
    prevy = cury;
    curx = x;
    cury = y;
    if (curx != startx || cury != starty) {
        glutPostRedisplay();
        startx = curx;
        starty = cury;
    }
}

void
button(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON)
        return;
    switch (state) {
    case GLUT_DOWN:
        prevx = curx = startx = x;
        prevy = cury = starty = y;
        spindx = 0;
        spindy = 0;
        tracking = GL_TRUE;
        break;
    case GLUT_UP:
        /*
         * If user released the button while moving the mouse, keep
         * spinning.
         */
        if (x != prevx || y != prevy) {
            spindx = x - prevx;
            spindy = y - prevy;
        }
        tracking = GL_FALSE;
        break;
    }
}

/* Maintain a square window when resizing */
void
reshape(int width, int height) {
    int size;
    size = (width < height ? width : height);
    glViewport((width - size) / 2, (height - size) / 2, size, size);
    glutReshapeWindow(size, size);
    glutPostRedisplay();
}

void
gridmaterials(void) {
    static float front_mat_diffuse[] =
    {1.0, 1.0, 0.4, 1.0};
    static float front_mat_ambient[] =
    {0.1, 0.1, 0.1, 1.0};
    static float back_mat_diffuse[] =
    {1.0, 0.0, 0.0, 1.0};
    static float back_mat_ambient[] =
    {0.1, 0.1, 0.1, 1.0};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, front_mat_ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);
    glMaterialfv(GL_BACK, GL_AMBIENT, back_mat_ambient);
}

void
surfacematerials(void) {
    static float front_mat_diffuse[] =
    {0.2, 0.7, 0.4, 1.0};
    static float front_mat_ambient[] =
    {0.1, 0.1, 0.1, 1.0};
    static float back_mat_diffuse[] =
    {1.0, 1.0, 0.2, 1.0};
    static float back_mat_ambient[] =
    {0.1, 0.1, 0.1, 1.0};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, front_mat_ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);
    glMaterialfv(GL_BACK, GL_AMBIENT, back_mat_ambient);
}

void
init(void) {
    static float ambient[] =
    {0.0, 0.0, 0.0, 1.0};
    static float diffuse[] =
    {1.0, 1.0, 1.0, 1.0};
    static float position[] =
    {90.0, 90.0, -150.0, 0.0};
    static float lmodel_ambient[] =
    {1.0, 1.0, 1.0, 1.0};

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 1.0, 2.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, modelmatrix);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glFrontFace(GL_CCW);

    glEnable(GL_MAP2_VERTEX_4);
    glClearColor(0.25, 0.25, 0.5, 0.0);

#if GL_EXT_polygon_offset
    glPolygonOffsetEXT(factor, bias);
    glEnable(GL_POLYGON_OFFSET_EXT);
#endif

    nobj = gluNewNurbsRenderer();
#ifdef GLU_VERSION_1_1  /* New GLU 1.1 interface. */
    gluNurbsProperty(nobj, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
#endif

    surflist = glGenLists(1);
    gridlist = glGenLists(1);

    bezier_points_u();
    bezier_points_v();
}

void
redraw(void) {
    int dx, dy;
    float v[3], rot[3];
    float len, ang;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);

    glBegin(GL_LINE_STRIP); //starts drawing of points
    draw_bezier_u();
    glEnd();

    glBegin(GL_LINE_STRIP); //starts drawing of points
    draw_bezier_v();
    glEnd();

    if (tracking) {
        dx = curx - startx;
        dy = cury - starty;
    } else {
        dx = spindx;
        dy = spindy;
    }
    if (dx || dy) {
        dy = -dy;
        v[0] = dx;
        v[1] = dy;
        v[2] = 0;

        len = length(v);
        ang = -len / 600 * 360;
        norm(v);
        cross(v, z_axis, rot);

        /* This is certainly not recommended for programs that care
           about performance or numerical stability: we concatenate
           the rotation onto the current modelview matrix and read
           the matrix back, thus saving ourselves from writing our
           own matrix manipulation routines.  */
        glLoadIdentity();
        glRotatef(ang, rot[0], rot[1], rot[2]);
        glMultMatrixf(modelmatrix);
        glGetFloatv(GL_MODELVIEW_MATRIX, modelmatrix);
    }
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glMultMatrixf(modelmatrix);

    glutSwapBuffers();
}

static void
usage(void) {
    printf("usage: surfgrid [-f]\n");
    exit(-1);
}

/* what to do when a menu item is selected. This function also handles
   keystroke events.  */
void
menu(int item) {
    switch (item) {
    case 'p':
#if GL_EXT_polygon_offset
        if (glIsEnabled(GL_POLYGON_OFFSET_EXT)) {
            glDisable(GL_POLYGON_OFFSET_EXT);
            printf("disabling polygon offset\n");
        } else {
            glEnable(GL_POLYGON_OFFSET_EXT);
            printf("enabling polygon offset\n");
        }
#endif
        break;
    case 'F':
        factor += 0.1;
        printf("factor: %8.4f\n", factor);
        break;
    case 'f':
        factor -= 0.1;
        printf("factor: %8.4f\n", factor);
        break;
    case 'B':
        bias += 0.0001;
        printf("bias:  %8.4f\n", bias);
        break;
    case 'b':
        bias -= 0.0001;
        printf("bias:  %8.4f\n", bias);
        break;
    case 'g':
        showgrid = !showgrid;
        break;
    case 'n':
        useglunurbs = !useglunurbs;
        break;
    case 's':
        smooth = !smooth;
        if (smooth) {
            glShadeModel(GL_SMOOTH);
        } else {
            glShadeModel(GL_FLAT);
        }
        break;
    case 't':
        showsurf = !showsurf;
        break;
    case 'u':
        break;
    case 'U':
        break;
    case 'v':
        break;
    case 'V':
        break;
    case '\033':         /* ESC key: quit */
        exit(0);
        break;
    }
    glutPostRedisplay();
}

/* ARGSUSED1 */
void
key(unsigned char key, int x, int y) {
    menu((int) key);
}

void
animate(void) {
    if (!tracking && (spindx != 0 || spindy != 0))
        glutPostRedisplay();
}

int
main(int argc, char **argv) {
    int i;

    glutInit(&argc, argv);  /* initialize glut, processing
                             arguments */

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
            case 'f':
                fullscreen = 1;
                break;
            default:
                usage();
                break;
            }
        } else {
            usage();
        }
    }

    glutInitWindowSize(winwidth, winheight);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("surfgrid");

    /* set callbacks */
    glutKeyboardFunc(key);
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutMouseFunc(button);
    glutMotionFunc(move);
    glutIdleFunc(animate);

    init();
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}

