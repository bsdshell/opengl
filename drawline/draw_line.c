#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>  /* Header File For The GLut Library*/

/*OpenGL.  Draw lines with GL_LINE_LOOP 
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

//mm0[0]=[0.500000] mm0[1]=[1.000000]
//mm1[0]=[1.000000] mm1[1]=[0.500000]
//  m[0]=[0.750000] m[1]  =[0.750000]
//mm0[0]=[0.250000] mm0[1]=[1.000000]
//mm1[0]=[0.625000] mm1[1]=[0.875000]
//  m[0]=[0.437500] m[1]  =[0.937500]
//mm0[0]=[0.875000] mm0[1]=[0.625000]
//mm1[0]=[1.000000] mm1[1]=[0.250000]
//  m[0]=[0.937500] m[1]  =[0.437500]


GLdouble midu[20][3];
GLdouble midv[20][3];
void bezier_curve(GLdouble p0[3], GLdouble p1[3], GLdouble p2[3], GLdouble mid[20][3], int* kp, int level){
    if(level > 0){
        GLdouble mm0[3];
        mm0[0] = (p0[0] + p1[0])/2;
        mm0[1] = (p0[1] + p1[1])/2;

        GLdouble mm1[3];
        mm1[0] = (p1[0] + p2[0])/2;
        mm1[1] = (p1[1] + p2[1])/2;

        GLdouble m[3];
        GLdouble x = m[0] = (mm0[0] + mm1[0])/2;
        GLdouble y = m[1] = (mm0[1] + mm1[1])/2;

        bezier_curve(p0, mm0, m, mid, kp, level-1);

        mid[*kp][0] = m[0] = x;
        mid[*kp][1] = m[1] = y;

        printf("  mid[%d][0]=[%f] mid[%d][1]=[%f]\n", *kp, mid[*kp][0], *kp, mid[*kp][1]);

        (*kp)++;
        bezier_curve(m, mm1, p2, mid, kp, level-1);
    }
}

void test1(void){
    GLdouble p0[3] = {0, 1, 0};
    GLdouble p1[3] = {1, 1, 0};
    GLdouble p2[3] = {1, 0, 0};
    GLdouble mid[20][3];
    int max_size = 20;
    int kp = 0;
    int level = 3;

    bezier_curve(p0, p1, p2, mid, &kp, level);
    int num_mid = 10;
    for(int i=0; i<max_size; i++){
        for(int j=0; j<2; j++){
            printf("[%d][%d]=[%f] ", i, j, mid[i][j]);
        } 
        printf("\n");
    } 
}

void test2(void){
  for(int i=0; i<3; i++){
    printf("[%d][0]=[%f] [%d][1]=[%f] ", i, midu[i][0], i, midu[i][0]);
  }
}

void draw_bezier_u(){
  for(int i=0; i<15; i++){
    printf("[%d][0]=[%f] [%d][1]=[%f] ", i, midu[i][0], i, midu[i][0]);
    glVertex3f(midu[i][0], midu[i][1], 0.0f);
  }
}

void draw_bezier_v(){
  for(int i=0; i<15; i++){
    printf("[%d][0]=[%f] [%d][1]=[%f] [%d][2]=[%f]", i, midv[i][0], i, midv[i][1], i, midv[i][2]);
    glVertex3f(midv[i][0], midv[i][1], midv[i][2]);
  }
}
void drawLine(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,1.0f,0.0f); // point color

    glBegin(GL_LINE_STRIP); //starts drawing of points
    draw_bezier_u();
    glEnd();

    glBegin(GL_LINE_STRIP); //starts drawing of points
    draw_bezier_v();
    glEnd();

    glBegin(GL_LINE_STRIP); //starts drawing of points
      glVertex3f(0.0f,0.0f,0.0f);
      glVertex3f(1.0f,0.0f,0.0f);
      glVertex3f(1.0f,1.0f,0.0f);
      glVertex3f(0.0f,1.0f,0.0f);
    glEnd();

    glLoadIdentity();
    glutSwapBuffers();
}

void bezier_points_v(){
    GLdouble p0[3] = {1.0f, 0.0f, 0.0f};
    GLdouble p1[3] = {0.0f, 1.0f, 0.0f};
    GLdouble p2[3] = {0.0f, 0.0f, -1.0f};

    int max_size = 20;
    int kp = 0;
    int level = 4;

    bezier_curve(p0, p1, p2, midv, &kp, level);

}
void bezier_points_u(){
    GLdouble p0[3] = {-1.0f, 0.0f, 0.0f};
    GLdouble p1[3] = {0.0f, 1.0f, 0.0f};
    GLdouble p2[3] = {1.0f, 0.0f, 0.0f};

    int max_size = 20;
    int kp = 0;
    int level = 4;

    bezier_curve(p0, p1, p2, midu, &kp, level);

}
int main(int argc, char** argv) {
    bezier_points_u();
    bezier_points_v();
    test2();

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (300,300);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Draw GL_LINE_LOOP");
    glutDisplayFunc(drawLine);

    glutMainLoop();

    return 0;
}
