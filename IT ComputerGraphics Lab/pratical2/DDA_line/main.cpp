/*Implement DDA line drawing algorithm to draw Simple Line*/
#include<windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

int x1, y_1, x2, y2;

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
    float dx, dy, steps, xInc, yInc, x, y;

    dx = x2 - x1;
    dy = y2 - y_1;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xInc = dx / steps;
    yInc = dy / steps;

    x = x1;
    y = y_1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    for (int i = 0; i < steps; i++)
    {
        x += xInc;
        y += yInc;
        glVertex2i(round(x), round(y));
    }

    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    std::cout << "Enter two end points of the line to draw:\n";
    std::cout << "Enter Point 1 (x1, y1): ";
    std::cin >> x1 >> y_1;
    std::cout << "Enter Point 2 (x2, y2): ";
    std::cin >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("DDA Line Drawing Algorithm");
    glutDisplayFunc(drawLine);
    myInit();
    glutMainLoop();

    return 0;
}
