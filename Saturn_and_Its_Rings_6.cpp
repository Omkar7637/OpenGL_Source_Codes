#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265358979323846

// Global variables
float angleEarth = 0.0f;  // Angle for Earth rotation
float angleRings = 0.0f;  // Angle for rings rotation
bool bFullScreen = false;  // Fullscreen toggle

// Function to draw a sphere (for Earth)
void drawSphere(GLfloat radius, GLint slices, GLint stacks) {
    for (int i = 0; i < slices; ++i) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= stacks; ++j) {
            float theta = (i + 0.0f) * 2.0f * PI / slices;
            float phi = j * PI / stacks;

            // Vertex coordinates
            float x = radius * sin(phi) * cos(theta);
            float y = radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);

            // Texture coordinates
            float s = (float)i / (float)slices;
            float t = (float)j / (float)stacks;

            // Set texture coordinates
            glTexCoord2f(s, t);
            glVertex3f(x, y, z);
            
            theta = (i + 1.0f) * 2.0f * PI / slices;
            x = radius * sin(phi) * cos(theta);
            y = radius * cos(phi);
            z = radius * sin(phi) * sin(theta);

            // Set texture coordinates
            glTexCoord2f(s, t);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

// Function to draw Saturn's rings
void drawRings(float innerRadius, float outerRadius, int numSegments) {
    for (int i = 0; i < numSegments; ++i) {
        float angle = (i * 2.0f * PI) / numSegments; // Angle for the ring segment

        // Set the color of the rings
        glColor3f(0.8f, 0.8f, 0.5f); // Light color for rings

        // Draw the ring as a quad strip
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= 1; ++j) {
            float radius = (j == 0) ? innerRadius : outerRadius;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            glVertex3f(x, 0.0f, z);
        }
        glEnd();
    }
}

// Function to load Earth texture
GLuint loadEarthTexture() {
    GLuint texture;
    unsigned char data[256][256][3]; // Simple texture data for Earth
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            // Generate a simple earth texture with blue (ocean) and green (land)
            if ((i < 128 && j < 128) || (i > 128 && j > 128)) { // Land areas
                data[i][j][0] = 34;   // Red
                data[i][j][1] = 139;  // Green
                data[i][j][2] = 34;   // Blue
            } else { // Ocean areas
                data[i][j][0] = 70;   // Dark Blue
                data[i][j][1] = 130;  // Light Blue
                data[i][j][2] = 180;  // Light Blue
            }
        }
    }

    glGenTextures(1, &texture); // Generate a texture ID
    glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Specify the 2D texture image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    return texture; // Return the texture ID
}

// Function to load textures
GLuint loadSaturnTexture() {
    GLuint texture;
    unsigned char data[256][256][3]; // Simple texture data for Saturn
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            // Generate a simple texture for Saturn
            data[i][j][0] = (unsigned char)(255 - (i % 256)); // Light to dark
            data[i][j][1] = (unsigned char)(i % 128);         // Shade variation
            data[i][j][2] = (unsigned char)((i + j) % 256);   // Blue tint
        }
    }

    glGenTextures(1, &texture); // Generate a texture ID
    glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Specify the 2D texture image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    return texture; // Return the texture ID
}

// Function to draw the scene
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
    glLoadIdentity();

    // Set the light source
    GLfloat lightPos[] = { 0.0f, 5.0f, 10.0f, 1.0f }; // Position of the sun
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Move the camera
    gluLookAt(0.0f, 4.0f, 20.0f, // Camera position
              0.0f, 0.0f, 0.0f, // Look at point
              0.0f, 1.0f, 0.0f); // Up vector

    // Draw Earth
    glPushMatrix();
    glRotatef(angleEarth, 0.0f, 1.0f, 0.0f); // Rotate Earth
    glBindTexture(GL_TEXTURE_2D, loadEarthTexture()); // Bind the texture for Earth
    drawSphere(3.0f, 40, 40); // Draw Earth with a larger radius
    glPopMatrix();

    // Draw Saturn
    glPushMatrix();
    glRotatef(angleEarth * 0.5f, 0.0f, 1.0f, 0.0f); // Rotate Saturn with Earth
    glBindTexture(GL_TEXTURE_2D, loadSaturnTexture()); // Bind the texture for Saturn
    drawSphere(2.0f, 40, 40); // Draw Saturn
    glPopMatrix();

    // Draw Saturn's rings
    glPushMatrix();
    glRotatef(angleRings, 0.0f, 1.0f, 0.0f); // Rotate rings
    drawRings(2.5f, 4.0f, 100); // Draw rings
    glPopMatrix();

    glutSwapBuffers(); // Swap buffers for smooth animation
}

// Update function for animation
void update(int value) {
    angleEarth += 1.0f; // Rotate Earth
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
    glEnable(GL_TEXTURE_2D); // Enable texturing

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f); // Field of view, aspect ratio, near and far planes
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Display mode
    glutInitWindowSize(800, 600); // Window size
    glutCreateWindow("Earth with World Map and Saturn"); // Create window
    initOpenGL(); // Initialize OpenGL
    glutDisplayFunc(display); // Display callback
    glutKeyboardFunc(keyboard); // Keyboard callback
    glutTimerFunc(0, update, 0); // Timer callback for animation
    glutMainLoop(); // Enter the GLUT main loop
    return 0;
}
