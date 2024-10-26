#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>

// Global variables
float angleX = 0.0f, angleY = 0.0f;
float rotationSpeed = 1.0f;
GLuint textures[6]; // Array to hold textures
bool bFullScreen = false;

// Lighting variables
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // Light position
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };   // Diffuse light
GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };   // Ambient light

// Function to load textures
void loadTextures() {
    // Create texture data
    GLubyte textureData[2][2][3] = {
        {{255, 0, 0}, {0, 255, 0}},  // Red and Green
        {{0, 0, 255}, {255, 255, 0}} // Blue and Yellow
    };

    glGenTextures(6, textures); // Generate texture IDs

    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

// Function to draw the textured cube
void drawCube() {
    glBegin(GL_QUADS);

    // Front face
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    // Back face
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);

    // Left face
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

    // Right face
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);

    // Top face
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Bottom face
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
}

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
    gluLookAt(0.0f, 0.0f, 5.0f, // Camera position
              0.0f, 0.0f, 0.0f, // Look at point
              0.0f, 1.0f, 0.0f); // Up vector

    // Apply rotation
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // Draw the cube
    drawCube();

    glutSwapBuffers(); // Swap buffers for smooth animation
}

void update(int value) {
    angleX += rotationSpeed;
    angleY += rotationSpeed;
    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, update, 0); // Call update every 16 milliseconds
}

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
        case '+':
            rotationSpeed += 0.1f;
            break;
        case '-':
            rotationSpeed -= 0.1f;
            break;
    }
}

void mouseMotion(int x, int y) {
    angleY += (x - 400) * 0.1f; // Use screen center for mouse movement
    angleX += (300 - y) * 0.1f; // Use screen center for mouse movement
}

void initOpenGL() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D
    glEnable(GL_TEXTURE_2D); // Enable 2D textures

    loadTextures(); // Load textures for the cube

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
    glutCreateWindow("Advanced 3D Rotating Cube");

    initOpenGL();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
