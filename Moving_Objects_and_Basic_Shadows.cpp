#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables
float angleX = 0.0f, angleY = 0.0f; // Camera angles
float timeElapsed = 0.0f; // Time elapsed for animations
bool bFullScreen = false; // Fullscreen toggle

// Number of moving cubes
#define NUM_CUBES 5
float cubePositions[NUM_CUBES][3]; // Positions of cubes
float cubeColors[NUM_CUBES][3]; // Colors of cubes
float cubeSpeeds[NUM_CUBES][3]; // Speeds of cubes

// Function to initialize cube positions, colors, and speeds
void initCubes() {
    for (int i = 0; i < NUM_CUBES; i++) {
        cubePositions[i][0] = (rand() % 10) - 5; // Random x position
        cubePositions[i][1] = (rand() % 3) - 1;  // Random y position
        cubePositions[i][2] = (rand() % 10) - 5; // Random z position
        cubeColors[i][0] = (float)rand() / RAND_MAX; // Random red
        cubeColors[i][1] = (float)rand() / RAND_MAX; // Random green
        cubeColors[i][2] = (float)rand() / RAND_MAX; // Random blue
        cubeSpeeds[i][0] = ((rand() % 5) + 1) / 10.0f; // Random speed in x
        cubeSpeeds[i][1] = ((rand() % 5) + 1) / 10.0f; // Random speed in y
        cubeSpeeds[i][2] = ((rand() % 5) + 1) / 10.0f; // Random speed in z
    }
}

// Function to draw a cube
void drawCube(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);

    // Front face
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Back face
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left face
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Right face
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Top face
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Bottom face
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
    glPopMatrix();
}

// Function to draw the ground
void drawGround() {
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Ground color
    glNormal3f(0.0f, 1.0f, 0.0f); // Normal pointing up
    glVertex3f(-5.0f, -1.0f, -5.0f);
    glVertex3f(5.0f, -1.0f, -5.0f);
    glVertex3f(5.0f, -1.0f, 5.0f);
    glVertex3f(-5.0f, -1.0f, 5.0f);
    glEnd();
}

// Display function
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
    glLoadIdentity();

    // Move the camera
    gluLookAt(0.0f, 2.0f, 10.0f, // Camera position
              0.0f, 0.0f, 0.0f,  // Look at point
              0.0f, 1.0f, 0.0f); // Up vector

    // Draw cubes
    for (int i = 0; i < NUM_CUBES; i++) {
        // Update position based on speed
        cubePositions[i][0] += cubeSpeeds[i][0] * 0.05f;
        cubePositions[i][1] += cubeSpeeds[i][1] * 0.05f;
        cubePositions[i][2] += cubeSpeeds[i][2] * 0.05f;

        // Change color over time
        cubeColors[i][0] += 0.01f;
        if (cubeColors[i][0] > 1.0f) cubeColors[i][0] = 0.0f;
        
        cubeColors[i][1] += 0.02f;
        if (cubeColors[i][1] > 1.0f) cubeColors[i][1] = 0.0f;

        cubeColors[i][2] += 0.03f;
        if (cubeColors[i][2] > 1.0f) cubeColors[i][2] = 0.0f;

        // Set color for the cube
        glColor3f(cubeColors[i][0], cubeColors[i][1], cubeColors[i][2]);
        drawCube(cubePositions[i][0], cubePositions[i][1], cubePositions[i][2]);
    }

    // Draw the ground
    drawGround();

    glutSwapBuffers(); // Swap buffers for smooth animation
}

// Update function for animation
void update(int value) {
    timeElapsed += 0.01f; // Increment time
    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, update, 0); // Call update every 16 milliseconds
}

// Keyboard function for user input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
        case 'f': // Toggle fullscreen
            if (bFullScreen) {
                glutReshapeWindow(800, 600);
            } else {
                glutFullScreen();
            }
            bFullScreen = !bFullScreen;
            break;
    }
}

// Initialize OpenGL settings
void initOpenGL() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0); // Enable light source

    // Set up light parameters
    GLfloat lightPos[] = { 0.0f, 10.0f, 0.0f, 1.0f }; // Position of the light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // Set light position

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f); // Field of view, aspect ratio, near and far planes
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Advanced OpenGL Scene with Moving Objects and Shadows");

    initCubes(); // Initialize cubes
    initOpenGL(); // Initialize OpenGL settings

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
