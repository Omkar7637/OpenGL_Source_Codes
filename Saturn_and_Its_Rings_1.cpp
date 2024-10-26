#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

// Global variables
float angleSaturn = 0.0f;   // Angle for Saturn rotation
float angleRings = 0.0f;    // Angle for rings rotation
bool bFullScreen = false;    // Fullscreen toggle

// Function to draw a sphere (for Saturn)
void drawSphere(GLfloat radius, GLint slices, GLint stacks) {
    struct {
        GLfloat x, y, z, nx, ny, nz, s, t;
    } vertices[2000];
    int index = 0;

    // Generate vertices for the sphere
    for (int i = 0; i < slices; ++i) {
        for (int j = 0; j < stacks; ++j) {
            float theta = i * 2.0f * PI / slices;  // Spherical coordinate
            float phi = j * PI / stacks;            // Spherical coordinate
            vertices[index].x = radius * sin(phi) * cos(theta);
            vertices[index].y = radius * cos(phi);
            vertices[index].z = radius * sin(phi) * sin(theta);
            vertices[index].nx = vertices[index].x / radius; // Normal
            vertices[index].ny = vertices[index].y / radius; // Normal
            vertices[index].nz = vertices[index].z / radius; // Normal
            vertices[index].s = (float)i / slices; // Texture coordinates
            vertices[index].t = (float)j / stacks; // Texture coordinates
            index++;
        }
    }

    // Draw sphere using the vertices
    for (int i = 0; i < slices; ++i) {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= stacks; ++j) {
            glNormal3f(vertices[i * stacks + j].nx, vertices[i * stacks + j].ny, vertices[i * stacks + j].nz);
            glVertex3f(vertices[i * stacks + j].x, vertices[i * stacks + j].y, vertices[i * stacks + j].z);
            glNormal3f(vertices[((i + 1) % slices) * stacks + j].nx, vertices[((i + 1) % slices) * stacks + j].ny, vertices[((i + 1) % slices) * stacks + j].nz);
            glVertex3f(vertices[((i + 1) % slices) * stacks + j].x, vertices[((i + 1) % slices) * stacks + j].y, vertices[((i + 1) % slices) * stacks + j].z);
        }
        glEnd();
    }
}

// Function to draw Saturn's rings
void drawRings(float innerRadius, float outerRadius, int numSegments) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSegments; ++i) {
        float angle = (i * 2.0f * PI) / numSegments; // Angle for the ring segment

        // Inner ring
        float xInner = innerRadius * cos(angle);
        float zInner = innerRadius * sin(angle);
        glVertex3f(xInner, 0.0f, zInner);
        // Outer ring
        float xOuter = outerRadius * cos(angle);
        float zOuter = outerRadius * sin(angle);
        glVertex3f(xOuter, 0.0f, zOuter);
    }
    glEnd();
}

// Function to draw the scene
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
    glLoadIdentity();

    // Set the light source
    GLfloat lightPos[] = { 0.0f, 5.0f, 10.0f, 1.0f }; // Position of the sun
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    // Move the camera
    gluLookAt(0.0f, 2.0f, 20.0f, // Camera position
              0.0f, 0.0f, 0.0f, // Look at point
              0.0f, 1.0f, 0.0f); // Up vector

    // Draw Saturn
    glPushMatrix();
    glRotatef(angleSaturn, 0.0f, 1.0f, 0.0f); // Rotate Saturn
    glColor3f(1.0f, 0.8f, 0.5f); // Color of Saturn
    drawSphere(2.0f, 40, 40); // Draw Saturn
    glPopMatrix();

    // Draw Saturn's rings
    glPushMatrix();
    glRotatef(angleRings, 0.0f, 1.0f, 0.0f); // Rotate rings
    glColor3f(0.8f, 0.8f, 0.8f); // Color of rings
    drawRings(2.5f, 4.0f, 100); // Draw rings
    glPopMatrix();

    // Draw shadows
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f); // Shadow color
    glBegin(GL_QUADS); // Shadow on the ground
    glVertex3f(-10.0f, -0.1f, -10.0f);
    glVertex3f(10.0f, -0.1f, -10.0f);
    glVertex3f(10.0f, -0.1f, 10.0f);
    glVertex3f(-10.0f, -0.1f, 10.0f);
    glEnd();
    glPopMatrix();

    glutSwapBuffers(); // Swap buffers for smooth animation
}

// Update function for animation
void update(int value) {
    angleSaturn += 1.0f; // Rotate Saturn
    angleRings += 2.0f;  // Rotate rings faster
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
    glutCreateWindow("Saturn with Rings");

    initOpenGL(); // Initialize OpenGL settings

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
