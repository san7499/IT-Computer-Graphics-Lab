/*Implement Bresenham circle drawing algorithm to draw any object */
#include<windows.h>
#include <GL/glut.h>
#include <iostream>

#include <GL/glut.h>
#include <cmath>

int xc, yc, r;

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawCircle(int xc, int yc, int x, int y) {
    setPixel(xc+x, yc+y);
    setPixel(xc-x, yc+y);
    setPixel(xc+x, yc-y);
    setPixel(xc-x, yc-y);
    setPixel(xc+y, yc+x);
    setPixel(xc-y, yc+x);
    setPixel(xc+y, yc-x);
    setPixel(xc-y, yc-x);
}

void bresenhamCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (x <= y) {
        drawCircle(xc, yc, x, y);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        drawCircle(xc, yc, x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    bresenhamCircle(xc, yc, r);
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char** argv) {
    printf("Enter the center of the circle (x, y): ");
    scanf("%d %d", &xc, &yc);
    printf("Enter the radius of the circle: ");
    scanf("%d", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
