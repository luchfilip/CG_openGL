/*source code shared by Marko Klopets, free to use for educational, personal and commercial purposes*/
///////video demo of the code in action: http://www.youtube.com/watch?v=qKTIxw2RvkI//////////////////
 
#include <iostream>
#include <stdlib.h>
 
//the glut and opengl libraries have to be linked correctly
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
using namespace std;
 
//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
        switch (key) {
                case 27: //Escape key
                        exit(0);
        }
}
 
//Initializes 3D rendering
void initRendering() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glClearColor(0.7f, 0.8f, 1.0f, 1.0f); //make the window background a blue-ish tone
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
}
 
//Called when the window is resized
void handleResize(int w, int h) {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}
 
float _angle = 0.0;
 
//Draws the 3D scene
void drawScene() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
 
        glTranslatef(0.0, 0.0, -5.0);
 
        //Add ambient light
        GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
 
        ////Add positioned light
        GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0};
        GLfloat lightPos0[] = {4.0, 0.0, 8.0, 1.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
       
        //Rotates, making sure it rotates around the center of the cube
        glTranslatef(0.5, 1.0, 0.0);
        glRotatef(_angle, 1.0, 1.0, 1.0);
        glTranslatef(-0.5, -1.0, 0.0);
       
 
        glBegin(GL_QUADS);
       
        //Make the 3D cube
 
        //FRONT
        glColor3f(0.0, 1.0, 0.0);
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-0.5, 1.0, 0.0);
        glVertex3f(-0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 1.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
 
        //BACK
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-0.5, 1.0, -1.0);
        glVertex3f(-0.5, 0.0, -1.0);
        glVertex3f(0.5, 0.0, -1.0);
        glVertex3f(0.5, 1.0, -1.0);
 
        //LEFT
        glNormal3f(-1.0, 0.0, 0.0);
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(-0.5, 1.0, -1.0);
        glVertex3f(-0.5, 0.0, -1.0);
        glVertex3f(-0.5, 0.0, 0.0);
        glColor3f(0.3, 1.0, 0.8);
        glVertex3f(-0.5, 1.0, 0.0);
 
        //Right
        glNormal3f(1.0, 0.0, 0.0);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(0.5, 1.0, -1.0);
        glVertex3f(0.5, 0.0, -1.0);
        glColor3f(0.0, 1.0, 1.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 1.0, 0.0);
 
        //BOTTOM
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-0.5, 0.0, -1.0);
        glVertex3f(-0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.0, -1.0);
 
        //TOP
        glColor3f(1.0, 0.0, 0.0);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-0.5, 1.0, -1.0);
        glVertex3f(-0.5, 1.0, 0.0);
        glVertex3f(0.5, 1.0, 0.0);
        glVertex3f(0.5, 1.0, -1.0);
 
        glEnd();
       
        glutSwapBuffers();
}
 
void update(int value) { //function for increasing the angle variable smoothly, keeps it <=360
        _angle += 1.0f;
        if (_angle > 360) {
                _angle -= 360;
        }
       
        glutPostRedisplay();
        glutTimerFunc(25, update, 0);
}
 
int main(int argc, char** argv) {
        //Initialize GLUT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 600);
       
        //Create the window
        glutCreateWindow("Source code by Marko Klopets");
        initRendering();
       
        //Set handler functions
        glutDisplayFunc(drawScene);
        glutKeyboardFunc(handleKeypress);
        glutReshapeFunc(handleResize);
       
        glutTimerFunc(25, update, 0); //Add a timer
       
        glutMainLoop();
        return 0;
}