/*Implement the following polygon filling methods Flood fill */
#include<windows.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void floodFill(int x, int y, float fillColor[3], float oldColor[3]) {
    float interiorColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, interiorColor);
    if (interiorColor[0] == oldColor[0] && interiorColor[1] == oldColor[1] && interiorColor[2] == oldColor[2]) {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        setPixel(x, y);
        floodFill(x + 1, y, fillColor, oldColor);
        floodFill(x - 1, y, fillColor, oldColor);
        floodFill(x, y + 1, fillColor, oldColor);
        floodFill(x, y - 1, fillColor, oldColor);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POLYGON);
    glVertex2i(150, 100);
    glVertex2i(300, 100);
    glVertex2i(350, 200);
    glVertex2i(250, 350);
    glVertex2i(200, 250);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void mouse(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float oldColor[] = {0.0, 0.0, 0.0};
        float fillColor[] = {1.0, 0.0, 0.0};
        floodFill(x, 500-y, fillColor, oldColor);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flood Fill Algorithm");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
