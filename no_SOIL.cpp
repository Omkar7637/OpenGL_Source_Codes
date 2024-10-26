#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>

// Global Variables
GLfloat angle = 0.0f;        // Angle for rotation
bool bFullScreen = false;    // Fullscreen toggle
GLuint texture;              // Texture ID

// Function Prototypes
void initialize(void);
void resize(int width, int height);
void display(void);
void update(int value);
void keyboard(unsigned char key, int x, int y);
void uninitialize(void);
void createTexture();

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotating Textured Cube with Lighting");

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

    // Create a texture
    createTexture();

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

void createTexture() {
    // Simple texture data (checkerboard pattern)
    unsigned char textureData[256][256][3];
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            int color = (i / 32 + j / 32) % 2;
            textureData[i][j][0] = color ? 255 : 0; // Red
            textureData[i][j][1] = color ? 255 : 0; // Green
            textureData[i][j][2] = color ? 255 : 0; // Blue
        }
    }

    glGenTextures(1, &texture); // Generate texture ID
    glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
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

    gluLookAt(0.0f, 0.0f, 5.0f,  // Camera position
              0.0f, 0.0f, 0.0f,  // Look at point
              0.0f, 1.0f, 0.0f); // Up vector

    // Rotate the scene based on the angle
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Draw textured cube
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

    glEnd();

    glutSwapBuffers(); // Swap buffers for smooth animation
}

void update(int value) {
    angle += 0.5f; // Increment angle for rotation
    if (angle > 360) angle -= 360; // Reset angle
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, update, 0); // Timer for next frame
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'f': // Toggle fullscreen
            bFullScreen = !bFullScreen;
            if (bFullScreen) {
                glutFullScreen();
            } else {
                glutReshapeWindow(800, 600);
                glutPositionWindow(100, 100);
            }
            break;
        case 27: // ESC key to exit
            exit(0);
            break;
    }
}

void uninitialize(void) {
    glDeleteTextures(1, &texture); // Delete the texture
}
