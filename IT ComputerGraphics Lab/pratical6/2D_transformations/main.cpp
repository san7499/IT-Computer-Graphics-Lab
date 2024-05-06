/*Implement following 2D transformations on the object with respect to axis :
i) Scaling ii) Rotation about arbitrary point iii) Reflection*/
#include<windows.h>
#include <GL/glut.h>
#include <cmath>

struct Point {
    float x;
    float y;
};

Point origin = {250, 250}; // Arbitrary point for rotation
float scaleX = 1.5;         // Scaling factor along X-axis
float scaleY = 1.5;         // Scaling factor along Y-axis
float theta = 45.0;         // Rotation angle in degrees
bool reflectX = false;      // Flag for X-axis reflection

void drawPolygon() {
    glBegin(GL_POLYGON);
    glVertex2f(100, 100);
    glVertex2f(200, 100);
    glVertex2f(200, 200);
    glVertex2f(100, 200);
    glEnd();
}

void drawTransformedPolygon() {
    glPushMatrix();

    // Scaling
    glScalef(scaleX, scaleY, 1.0);

    // Rotation about arbitrary point
    glTranslatef(origin.x, origin.y, 0.0);
    glRotatef(theta, 0.0, 0.0, 1.0);
    glTranslatef(-origin.x, -origin.y, 0.0);

    // Reflection
    if (reflectX)
        glScalef(-1.0, 1.0, 1.0);

    glColor3f(1.0, 1.0, 1.0);
    drawPolygon();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawTransformedPolygon();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void menu(int option) {
    switch (option) {
        case 1:
            scaleX = 1.5;
            scaleY = 1.5;
            theta = 45.0;
            reflectX = false;
            break;
        case 2:
            scaleX = 0.5;
            scaleY = 0.5;
            theta = 90.0;
            reflectX = false;
            break;
        case 3:
            scaleX = 1.0;
            scaleY = 1.0;
            theta = 0.0;
            reflectX = true;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations");

    init();
    glutDisplayFunc(display);

    glutCreateMenu(menu);
    glutAddMenuEntry("Scaling and Rotation", 1);
    glutAddMenuEntry("Scaling and Rotation (90 degrees)", 2);
    glutAddMenuEntry("Reflection (X-axis)", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
