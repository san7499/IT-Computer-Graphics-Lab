/*Implement animation principles for any object*/
#include<windows.h>
#include <GL/glut.h>
#include <cmath>

// Global variables
GLfloat ballRadius = 0.2f; // Radius of the bouncing ball
GLfloat ballX = 0.0f;      // X-coordinate of the ball
GLfloat ballY = 0.0f;      // Y-coordinate of the ball
GLfloat ballXSpeed = 0.02f; // Speed of the ball along the X-axis
GLfloat ballYSpeed = 0.0f;  // Speed of the ball along the Y-axis
GLfloat gravity = -0.001f;  // Gravity

// Initialize OpenGL
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    glMatrixMode(GL_MODELVIEW); // Switch to the modelview matrix
    glLoadIdentity();           // Load the identity matrix

    // Translate the ball to its current position
    glTranslatef(ballX, ballY, 0.0f);

    // Draw the ball
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180;
        glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
    }
    glEnd();

    glutSwapBuffers(); // Swap the front and back buffers to display the rendered image
}

// Update function for animation
void update(int value) {
    // Update the position of the ball
    ballX += ballXSpeed;
    ballY += ballYSpeed;

    // Apply gravity
    ballYSpeed += gravity;

    // Check for collision with walls
    if (ballX + ballRadius > 1.0f || ballX - ballRadius < -1.0f) {
        ballXSpeed = -ballXSpeed; // Reverse the X direction
    }
    if (ballY + ballRadius > 1.0f || ballY - ballRadius < -1.0f) {
        ballYSpeed = -ballYSpeed; // Reverse the Y direction
    }

    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, update, 0); // Call the update function again after 16 milliseconds (about 60 FPS)
}

// Reshape callback function
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Set the viewport to cover the new window
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix
    glLoadIdentity(); // Load the identity matrix
    glOrtho(-1, 1, -1, 1, -1, 1); // Set an orthogonal projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set the display mode
    glutInitWindowSize(500, 500); // Set the window size
    glutCreateWindow("Bouncing Ball Animation"); // Create a window with the given title
    glutDisplayFunc(display); // Set the display callback function
    glutReshapeFunc(reshape); // Set the reshape callback function
    glutTimerFunc(16, update, 0); // Call the update function for the first time
    initGL(); // Initialize OpenGL
    glutMainLoop(); // Enter the GLUT event loop
    return 0;
}
