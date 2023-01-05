#include <bits/stdc++.h>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>

void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);                     
    glEnable(GL_DEPTH_TEST);  
    glDepthFunc(GL_LEQUAL);    
    glShadeModel(GL_SMOOTH); 
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
}
void cylinder(double radius, double height){
    double theta = 2 * acos(-1) / 50;
    glPushMatrix();
        glBegin(GL_QUAD_STRIP);
        for(int i = 0; i < 50; i++){
            auto x = radius * cos(theta * i);
            auto y = height / 2;
            auto z = radius * sin(theta * i);
            glVertex3d(x, y, z);
            glVertex3d(x, -y, z);
        }
        glEnd();
    glPopMatrix();
}
void addcolor(int r, int g, int b){
    glColor3d(r / 255.0, g / 255.0, b / 255.0);
}
double viewangle = 0;
double animationangle = 0;
int direction = 1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);    
 
    glLoadIdentity(); 
    glTranslated(0, -10, -50);  
    glRotated(viewangle, 0, 1, 0);
    addcolor(165, 165, 165);
    glutSolidSphere(5, 50, 50);
    glPushMatrix();
        glTranslated(10, 0, 0);  
        glutSolidSphere(5, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-10, 0, 0);  
        glutSolidSphere(5, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(20, 0, 0);
        if(animationangle > 0){
            glTranslated(0, 20, 0);
            glRotated(animationangle, 0, 0, 1);
            glTranslated(0, -20, 0);
        }
        glutSolidSphere(5, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-20, 0, 0);
        if(animationangle < 0){
            glTranslated(0, 20, 0);
            glRotated(animationangle, 0, 0, 1);
            glTranslated(0, -20, 0);
        }
        glutSolidSphere(5, 50, 50);
    glPopMatrix();

    glTranslated(0, 4, 0);
    addcolor(125, 125, 125);
    glPushMatrix();
        glTranslated(-25, 0, -25);
        cylinder(3, 40);
    glPopMatrix();
    glPushMatrix();
        glTranslated(25, 0, -25);
        cylinder(3, 40);
    glPopMatrix();
    glPushMatrix();
        glTranslated(25, 0, 25);
        cylinder(3, 40);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-25, 0, 25);
        cylinder(3, 40);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 20, 25);
        glRotated(90, 0, 0, 1);
        cylinder(3, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 20, -25);
        glRotated(90, 0, 0, 1);
        cylinder(3, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(25, 20, -25);
        glutSolidSphere(3, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-25, 20, 25);
        glutSolidSphere(3, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(25, 20, 25);
        glutSolidSphere(3, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-25, 20, -25);
        glutSolidSphere(3, 50, 50);
    glPopMatrix();

    addcolor(230, 230, 230);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3d(10, 20, 25);
    glVertex3d(10, -4, 0);
    glVertex3d(10, 20, -25);
    glVertex3d(10, -4, 0);
    glVertex3d(0, 20, 25);
    glVertex3d(0, -4, 0);
    glVertex3d(0, 20, -25);
    glVertex3d(0, -4, 0);
    glVertex3d(-10, 20, 25);
    glVertex3d(-10, -4, 0);
    glVertex3d(-10, 20, -25);
    glVertex3d(-10, -4, 0);
    glEnd();

    glPushMatrix();
        if(animationangle < 0){
            glTranslated(-20, 20, 25);
            glRotated(animationangle, 0, 0, 1);
            glTranslated(20, -20, -25);
        }
        glBegin(GL_LINES);
        glVertex3d(-20, 20, 25);
        glVertex3d(-20, -4, 0);
        glVertex3d(-20, 20, -25);
        glVertex3d(-20, -4, 0);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        if(animationangle > 0){
            glTranslated(20, 20, 25);
            glRotated(animationangle, 0, 0, 1);
            glTranslated(-20, -20, -25);
        }
        glBegin(GL_LINES);
        glVertex3d(20, 20, 25);
        glVertex3d(20, -4, 0);
        glVertex3d(20, 20, -25);
        glVertex3d(20, -4, 0);
        glEnd();
    glPopMatrix();

    if(animationangle > 40) direction = -1; 
    else if(animationangle < -40) direction = 1;
    animationangle += ((40 - abs(animationangle)) / 38 + 0.01) * direction * 1.7;
    glutSwapBuffers();  
}
void timer(int value) {
    glutPostRedisplay();      
    glutTimerFunc(17, timer, 0);
}
void reshape(GLsizei width, GLsizei height) {   
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
    glViewport(0, 0, width, height);
 
    glMatrixMode(GL_PROJECTION);  

    glLoadIdentity();   
    gluPerspective(80.0, aspect, 0.1, 100.0);
}
void keybd(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            viewangle--;
            break;
        case GLUT_KEY_RIGHT:
            viewangle++;
            break;
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);         
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1600, 900);    
    glutInitWindowPosition(50, 50); 
    glutCreateWindow("20102924"); 
    glutDisplayFunc(display);     
    glutReshapeFunc(reshape);   
    glutSpecialFunc(keybd);  
    initGL();                     
    glutTimerFunc(0, timer, 0);  
    glutMainLoop();                
    return 0;
}
