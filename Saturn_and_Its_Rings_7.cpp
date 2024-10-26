#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global Variables
GLfloat angle = 0.0f;  // Angle for rotation
bool bFullScreen = false; // Fullscreen toggle
GLuint texture; // Texture ID

// Function Prototypes
void initialize(void);
void resize(int width, int height);
void display(void);
void update(int value);
void keyboard(unsigned char key, int x, int y);
void uninitialize(void);
GLuint loadTexture(const char* filename);
void drawSphere(float radius, int slices, int stacks);

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Textured Earth");

    initialize();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutCloseFunc(uninitialize);

    // Set timer for animation
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}

void initialize(void) {
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_TEXTURE_2D); // Enable texture mapping

    // Load the texture (a placeholder, replace with actual filename)
    texture = loadTexture("earth_texture.jpg"); // Replace with a valid Earth texture image

    // Lighting setup
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 0.0f, 1.0f, 1.0f, 0.0f }; // Directional light

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0);   // Enable light source
}

GLuint loadTexture(const char* filename) {
    GLuint texture;
    // Implement your texture loading code here
    return texture; // Return the loaded texture ID
}

void drawSphere(float radius, int slices, int stacks) {
    for (int i = 0; i < slices; i++) {
        float lat0 = M_PI * (-0.5 + (float)(i) / slices);
        float z0 = radius * sin(lat0);
        float zr0 = radius * cos(lat0);

        float lat1 = M_PI * (-0.5 + (float)(i + 1) / slices);
        float z1 = radius * sin(lat1);
        float zr1 = radius * cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= stacks; j++) {
            float lng = 2 * M_PI * (float)(j) / stacks;
            float x = cos(lng);
            float y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glTexCoord2f((float)(j) / stacks, (float)i / slices);
            glVertex3f(x * zr0, y * zr0, z0);

            glNormal3f(x * zr1, y * zr1, z1);
            glTexCoord2f((float)(j) / stacks, (float)(i + 1) / slices);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

void resize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity(); // Load identity matrix

    gluLookAt(0.0f, 0.0f, 5.0f, // Camera position
              0.0f, 0.0f, 0.0f, // Look at point
              0.0f, 1.0f, 0.0f); // Up vector

    // Rotate the scene based on the angle
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Draw the Earth sphere
    glBindTexture(GL_TEXTURE_2D, texture);
    drawSphere(1.0f, 50, 50); // Sphere with radius 1.0, 50 slices, 50 stacks

    glutSwapBuffers(); // Swap buffers for animation
}

void update(int value) {
    angle += 0.5f; // Update angle for rotation
    if (angle > 360) {
        angle -= 360; // Wrap angle
    }

    glutPostRedisplay(); // Request display update
    glutTimerFunc(16, update, 0); // Call update again after 16ms
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC key
        exit(0);
        break;
    case 'f':
    case 'F':
        if (!bFullScreen) {
            glutFullScreen();
            bFullScreen = true;
        } else {
            glutReshapeWindow(800, 600);
            bFullScreen = false;
        }
        break;
    }
}

void uninitialize(void) {
    // Cleanup code if needed
}
