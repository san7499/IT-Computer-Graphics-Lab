/*Generate fractal patterns using Koch Curve */
#include<windows.h>
#include <GL/glut.h>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Function to draw Koch curve
void drawKochCurve(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    } else {
        float deltaX = (x2 - x1) / 3;
        float deltaY = (y2 - y1) / 3;

        float x3 = x1 + deltaX;
        float y3 = y1 + deltaY;

        float x4 = (x1 + x2) / 2 + (sqrt(3) / 6) * (y1 - y2);
        float y4 = (y1 + y2) / 2 + (sqrt(3) / 6) * (x2 - x1);

        float x5 = x1 + 2 * deltaX;
        float y5 = y1 + 2 * deltaY;

        drawKochCurve(x1, y1, x3, y3, depth - 1);
        drawKochCurve(x3, y3, x4, y4, depth - 1);
        drawKochCurve(x4, y4, x5, y5, depth - 1);
        drawKochCurve(x5, y5, x2, y2, depth - 1);
    }
}

// Function to display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    drawKochCurve(100, 300, 700, 300, 4);
    glEnd();

    glFlush();
}

// Function to initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Koch Curve Fractal");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
