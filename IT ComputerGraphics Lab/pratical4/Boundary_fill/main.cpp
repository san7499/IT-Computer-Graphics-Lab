/*Implement the following polygon filling methods Boundary fill */
#include<windows.h>
#include <GL/glut.h>

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void boundaryFill(int x, int y, float fillColor[3], float borderColor[3]) {
    float interiorColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, interiorColor);
    if ((interiorColor[0] != borderColor[0] || interiorColor[1] != borderColor[1] || interiorColor[2] != borderColor[2]) &&
        (interiorColor[0] != fillColor[0] || interiorColor[1] != fillColor[1] || interiorColor[2] != fillColor[2])) {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        setPixel(x, y);
        boundaryFill(x + 1, y, fillColor, borderColor);
        boundaryFill(x - 1, y, fillColor, borderColor);
        boundaryFill(x, y + 1, fillColor, borderColor);
        boundaryFill(x, y - 1, fillColor, borderColor);
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
        float borderColor[] = {1.0, 1.0, 1.0};
        float fillColor[] = {1.0, 0.0, 0.0};
        boundaryFill(x, 500-y, fillColor, borderColor);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Boundary Fill Algorithm");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
