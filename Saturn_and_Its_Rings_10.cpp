#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global Variables
GLfloat angle = 0.0f;  // Angle for rotation
GLfloat ringAngle = 0.0f; // Angle for ring rotation
bool bFullScreen = false; // Fullscreen toggle
GLuint texture = 0; // Earth texture ID
GLuint smallTexture = 0; // Texture for small objects

// Function Prototypes
void initialize(void);
void resize(int width, int height);
void display(void);
void update(int value);
void keyboard(unsigned char key, int x, int y);
void uninitialize(void);
GLuint loadTexture(const char* filename);
void drawSphere(float radius, int slices, int stacks);
void drawSmallTexturedObjects();
void drawColoredRings(float radius, float thickness);

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Textured Earth with Small Objects and Colored Rings");

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

    // Load the textures (replace with actual filenames)
    texture = loadTexture("earth_texture.bmp"); // Earth texture
    smallTexture = loadTexture("small_texture.bmp"); // Texture for small objects

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
    GLuint textureID;
    // Placeholder for texture loading logic
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image data here (implement your texture loading)
    return textureID; // Return the loaded texture ID
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

void drawSmallTexturedObjects() {
    glBindTexture(GL_TEXTURE_2D, smallTexture);
    
    // Draw small objects at different positions on the Earth
    glPushMatrix();
    glTranslatef(1.2f, 0.0f, 0.0f); // Position 1
    drawSphere(0.1f, 10, 10); // Small sphere with radius 0.1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f, 0.5f, 0.0f); // Position 2
    drawSphere(0.1f, 10, 10); // Small sphere with radius 0.1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.5f, 0.0f); // Position 3
    drawSphere(0.1f, 10, 10); // Small sphere with radius 0.1
    glPopMatrix();
}

void drawColoredRings(float radius, float thickness) {
    glPushMatrix();
    glRotatef(ringAngle, 0.0f, 1.0f, 0.0f); // Rotate rings

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i += 10) {
        float theta = i * M_PI / 180.0f;
        float x1 = radius * cos(theta);
        float z1 = radius * sin(theta);
        float x2 = (radius + thickness) * cos(theta);
        float z2 = (radius + thickness) * sin(theta);

        // Set colors for rings
        glColor3f((float)(i % 255) / 255.0f, 0.5f, (float)(255 - (i % 255)) / 255.0f);
        
        glVertex3f(x1, 0.0f, z1);
        glVertex3f(x2, 0.0f, z2);
    }
    glEnd();
    
    glPopMatrix();
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

    // Draw small textured objects
    drawSmallTexturedObjects();

    // Draw rotating colored rings
    drawColoredRings(1.2f, 0.05f); // Rings with radius 1.2 and thickness 0.05

    glutSwapBuffers(); // Swap buffers for animation
}

void update(int value) {
    angle += 0.5f; // Update angle for rotation
    ringAngle += 1.0f; // Update ring angle for rotation
    if (angle > 360) {
        angle -= 360; // Wrap angle
    }
    if (ringAngle > 360) {
        ringAngle -= 360; // Wrap ring angle
    }

    glutPostRedisplay(); // Request to redraw the scene
    glutTimerFunc(16, update, 0); // Update at ~60 frames per second
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
        case 'F':
            if (bFullScreen) {
                glutLeaveFullScreen();
                bFullScreen = false;
            } else {
                glutFullScreen();
                bFullScreen = true;
            }
            break;
        case 27: // Escape key
            uninitialize();
            exit(0);
            break;
    }
}

void uninitialize(void) {
    glDeleteTextures(1, &texture); // Delete texture
    glDeleteTextures(1, &smallTexture); // Delete small texture
}
