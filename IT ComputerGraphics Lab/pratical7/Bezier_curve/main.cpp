/*Generate fractal patterns using Bezier  curve . */
#include<windows.h>
#include <GL/glut.h>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

std::vector<float> controlPoints = {100, 100, 200, 500, 400, 500, 500, 100};

// Function to draw a Bezier curve
void drawBezierCurve(std::vector<float> controlPoints) {
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < controlPoints.size(); i += 2) {
        glVertex2f(controlPoints[i], controlPoints[i + 1]);
    }
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1; t += 0.01) {
        float x = 0, y = 0;
        for (int i = 0; i < controlPoints.size(); i += 2) {
            float basis = 1;
            for (int j = 0; j < controlPoints.size() / 2; j++) {
                if (j != i / 2) {
                    basis *= (t - (j / (controlPoints.size() / 2.0))) / ((i / 2.0) - (j / (controlPoints.size() / 2.0)));
                }
            }
            x += controlPoints[i] * basis;
            y += controlPoints[i + 1] * basis;
        }
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to recursively generate Bezier curve fractal
void drawFractal(std::vector<float> controlPoints, int depth) {
    drawBezierCurve(controlPoints);

    if (depth > 0) {
        std::vector<float> newControlPoints;
        for (int i = 0; i < controlPoints.size() - 2; i += 2) {
            float x = (controlPoints[i] + controlPoints[i + 2]) / 2;
            float y = (controlPoints[i + 1] + controlPoints[i + 3]) / 2;
            newControlPoints.push_back(controlPoints[i]);
            newControlPoints.push_back(controlPoints[i + 1]);
            newControlPoints.push_back(x);
            newControlPoints.push_back(y);
        }
        newControlPoints.push_back(controlPoints[controlPoints.size() - 2]);
        newControlPoints.push_back(controlPoints[controlPoints.size() - 1]);
        drawFractal(newControlPoints, depth - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawFractal(controlPoints, 5);
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Bezier Curve Fractal");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
