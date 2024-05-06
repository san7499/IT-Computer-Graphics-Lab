/*Implement Cohen Sutherland polygon clipping method to clip the polygon with respect the
viewport and window  */
#include<windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

const int x_max = 300;
const int y_max = 300;
const int x_min = 100;
const int y_min = 100;

int computeCode(int x, int y) {
    int code = INSIDE;
    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;
    return code;
}

void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int codeOut = code1 ? code1 : code2;
            int x, y;
            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
        glFlush();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // Drawing the window
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x_min, y_min);
    glVertex2i(x_max, y_min);
    glVertex2i(x_max, y_max);
    glVertex2i(x_min, y_max);
    glEnd();

    // Drawing the polygon
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 50);
    glVertex2i(250, 50);
    glVertex2i(250, 150);
    glVertex2i(150, 150);
    glEnd();

    // Clipping the polygon with respect to the window
    cohenSutherlandClip(150, 50, 250, 50);
    cohenSutherlandClip(250, 50, 250, 150);
    cohenSutherlandClip(250, 150, 150, 150);
    cohenSutherlandClip(150, 150, 150, 50);

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Polygon Clipping Algorithm");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
