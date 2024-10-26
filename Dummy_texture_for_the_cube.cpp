#include <GL/glut.h>
#include <stdbool.h>

// Global variables
float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;
float rotationSpeedX = 0.5f, rotationSpeedY = 0.5f, rotationSpeedZ = 0.5f;
GLuint texture;
bool bFullScreen = false;

// Mouse interaction variables
bool isDragging = false;
int lastMouseX, lastMouseY;

void loadTexture() {
    // Dummy texture for the cube; just using basic color here
    GLubyte textureData[2][2][3] = {
        {{255, 0, 0}, {0, 255, 0}},
        {{0, 0, 255}, {255, 255, 0}}
    };

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void drawCube() {
    glBindTexture(GL_TEXTURE_2D, texture);
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

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
    glLoadIdentity();

    // Move the camera
    gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Apply rotation
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

    // Draw the cube
    drawCube();

    glutSwapBuffers(); // Swap buffers for smooth animation
}

void update(int value) {
    angleX += rotationSpeedX;
    angleY += rotationSpeedY;
    angleZ += rotationSpeedZ;
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
            rotationSpeedX += 0.1f;
            rotationSpeedY += 0.1f;
            rotationSpeedZ += 0.1f;
            break;
        case '-':
            rotationSpeedX -= 0.1f;
            rotationSpeedY -= 0.1f;
            rotationSpeedZ -= 0.1f;
            break;
    }
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            rotationSpeedX += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            rotationSpeedX -= 0.1f;
            break;
        case GLUT_KEY_LEFT:
            rotationSpeedY -= 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            rotationSpeedY += 0.1f;
            break;
    }
}

void mouseMotion(int x, int y) {
    if (isDragging) {
        angleY += (x - lastMouseX) * 0.1f;
        angleX += (y - lastMouseY) * 0.1f;
    }
    lastMouseX = x;
    lastMouseY = y;
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            isDragging = false;
        }
    }
}

void initOpenGL() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D
    glEnable(GL_TEXTURE_2D); // Enable 2D textures

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f); // Field of view, aspect ratio, near and far planes
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix

    loadTexture(); // Load texture for the cube
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Rotating Cube");

    initOpenGL();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
