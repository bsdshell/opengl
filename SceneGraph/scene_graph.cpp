#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include "AronLib.h"
#include "CameraKeyBoard.h"
#include <list> 

using namespace std;
using namespace SpaceDraw;
using namespace Utility;
using namespace SpaceDraw;
using namespace SpaceMatrix4;

class SceneNode{
    public:
    std::list<SceneNode*> list;
    SceneNode(){
    }
    public:
    virtual void update(){
        for( std::list<SceneNode*>::iterator i= list.begin(); i != list.end(); i++){
            (*i)->update();
        }
    }
    void addNode(SceneNode* node){
        list.push_back(node);
    }
};

class SceneGraph{
};

class GeometryNode : public SceneNode{
    virtual void update(){
        SceneNode::update();
    }
};

class Box : public GeometryNode{
    float w;
    float mat[16];
    public:
    Box(float w_ = 1.0f){
        w = w_;
    }
    void matrix(){
        glTranslatef(-1.5, 0, 0);
    }
    virtual void update(){
        getModelViewMatrix(mat);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        matrix();
        glBegin(GL_QUADS);
        glVertex3f(-w, +w, 0.0); // top left
        glVertex3f(-w, -w, 0.0); // bottom left
        glVertex3f(+w, -w, 0.0); // bottom right
        glVertex3f(+w, +w, 0.0); // top right
        glEnd();
        glPopMatrix();
    }
};

class Triangle : public GeometryNode{
    void matrix(){
        glTranslatef(1, 0, 0);
    }
    virtual void update(){
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        matrix();
        float alpha = 0.5;
        glBegin(GL_TRIANGLES);
        glColor4f(1.0, 0.0, 0.0, alpha);
        glVertex3f(-1.0, +1.0, 0.0); // top left

        glColor4f(0.0, 1.0, 0.0, alpha);
        glVertex3f(-1.0, -1.0, 0.0); // bottom left

        glColor4f(0.0, 0.0, 1.0, alpha);
        glVertex3f(+1.0, -1.0, 0.0); // bottom right

        glEnd();
        glPopMatrix();
    }
};

Cube cube(0, 0, 0, 0.5);
SimpleCoordinate coor;
Plane plane;

void test1(){
    SceneNode* root = new SceneNode();
    SceneNode* child = new SceneNode();
    SceneNode* child2 = new SceneNode();
    Triangle* tri = new Triangle();
    Box* box = new Box(1);
    child->addNode(tri);
//    child->addNode(box);

    //Box* box1 = new Box(1.0);
    Box* box2 = new Box();
    //child2->addNode(box1);
    child2->addNode(box2);

    root->addNode(child);
    root->addNode(child2);
    root->update();

    delete root;
    delete child;
    delete child2;
    delete tri;
    delete box;
    //delete box1;
}

void test2(){
    Matrix4 m;
//    m.print();
//    Matrix4 t = m.translate(1, 2, 3, 0);
//    t.print();

    Matrix4 id = m.identity();
    id.print();
    Matrix4 m1 = id*id;
    m1.print();
}

static void init(void) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    camera.setTheta(0.5);
}

void drawBox(){
    float alpha = 0.5;
    glBegin(GL_QUADS);
    glColor4f(1.0, 0.0, 0.0, alpha);
    glVertex3f(-1.0, +1.0, 0.0); // top left

    glColor4f(0.0, 1.0, 0.0, alpha);
    glVertex3f(-1.0, -1.0, 0.0); // bottom left

    glColor4f(0.0, 0.0, 1.0, alpha);
    glVertex3f(+1.0, -1.0, 0.0); // bottom right

    glColor4f(0.0, 1.0, 1.0, alpha);
    glVertex3f(+1.0, +1.0, 0.0); // top right
    glEnd();
    camera.print(10, 100);
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
//    drawBox();
//    plane.draw();
    coor.draw();
    test1();
//    test2();
    camera.print(10, 100);
    glFlush();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInitWindowSize(800, 800);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
