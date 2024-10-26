#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables
float angleX = 0.0f, angleY = 0.0f; // Cube rotation angles
float rotationSpeed = 1.0f; // Rotation speed
bool bFullScreen = false; // Fullscreen toggle

// Lighting variables
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // Light position
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };   // Diffuse light
GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };   // Ambient light

// Function to draw the textured cube
void drawCube() {
    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    // Back face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);

    // Left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);

    // Top face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Bottom face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
}

// Function to draw the reflection
void drawGround() {
    glBegin(GL_QUADS);
    glColor4f(0.5, 0.5, 0.5, 0.5); // Semi-transparent ground
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

    // Set light properties
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0);   // Enable light source

    // Move the camera
    gluLookAt(0.0f, 2.0f, 10.0f, // Camera position
              0.0f, 0.0f, 0.0f,  // Look at point
              0.0f, 1.0f, 0.0f); // Up vector

    // Apply rotation
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // Draw the reflection
    glPushMatrix();
    glScalef(1.0f, -1.0f, 1.0f); // Reflect over the ground plane
    glColor4f(1.0, 1.0, 1.0, 0.5); // White reflection with some transparency
    drawCube();
    glPopMatrix();

    // Draw the main cube
    glColor3f(1.0, 0.0, 0.0); // Color of the cube
    drawCube();

    // Draw the ground
    drawGround();

    glutSwapBuffers(); // Swap buffers for smooth animation
}

// Update function for animation
void update(int value) {
    angleX += rotationSpeed;
    angleY += rotationSpeed;
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
                glutPositionWindow(100, 100);
            } else {
                glutFullScreen();
            }
            bFullScreen = !bFullScreen;
            break;
        case '+': // Increase rotation speed
            rotationSpeed += 0.1f;
            break;
        case '-': // Decrease rotation speed
            rotationSpeed -= 0.1f;
            break;
    }
}

// Mouse motion function for camera control
void mouseMotion(int x, int y) {
    angleY += (x - 400) * 0.1f; // Use screen center for mouse movement
    angleX += (300 - y) * 0.1f; // Use screen center for mouse movement
}

// Initialize OpenGL settings
void initOpenGL() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_TEXTURE_2D); // Enable 2D textures

    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0);   // Enable light source

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
    glutCreateWindow("Advanced OpenGL Cube with Reflections");

    initOpenGL();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
