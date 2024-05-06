/*Implement Bresenham  line drawing algorithm to draw: i) Simple Line */
#include<windows.h>
#include <GL/glut.h>
#include <iostream>

int x1, y1, x2, y2;

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void drawLine(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    int x, y, xEnd;

    if (x1 > x2) {
        x = x2;
        y = y2;
        xEnd = x1;
    } else {
        x = x1;
        y = y1;
        xEnd = x2;
    }

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    while (x < xEnd) {
        x++;
        if (p < 0)
            p += twoDy;
        else {
            y++;
            p += twoDyMinusDx;
        }
        glVertex2i(x, y);
    }

    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    std::cout << "Enter two end points of the line to draw:\n";
    std::cout << "Enter Point 1 (x1, y1): ";
    std::cin >> x1 >> y1;
    std::cout << "Enter Point 2 (x2, y2): ";
    std::cin >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bresenham Line Drawing Algorithm");
    glutDisplayFunc(drawLine);
    myInit();
    glutMainLoop();

    return 0;
}
