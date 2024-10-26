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
void drawSmallTexturedObjects(GLfloat time);
void drawColoredRings(float radius, float thickness);

// Main Function
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

// Initialization Function
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

// Texture loading function
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

// Function to draw a sphere
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

// Function to draw small textured objects
void drawSmallTexturedObjects(GLfloat time) {
    glBindTexture(GL_TEXTURE_2D, smallTexture);

    // Define small object positions and colors
    GLfloat positions[][3] = {
        {1.2f, 0.0f, 0.0f},
        {-1.2f, 0.5f, 0.0f},
        {0.0f, -1.5f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f},
    };

    // Loop to draw small objects
    for (int i = 0; i < 5; ++i) {
        glPushMatrix();
        // Calculate position based on time for steady circular motion
        GLfloat angleOffset = time + i * (M_PI / 5); // Different starting angles for objects
        GLfloat radius = 1.5f; // Radius of circular motion
        GLfloat xPos = radius * cos(angleOffset);
        GLfloat zPos = radius * sin(angleOffset);

        glTranslatef(xPos, 0.0f, zPos); // Position the small object
        // Set color based on object index
        glColor3f((float)(i % 3), (float)((i + 1) % 3), (float)((i + 2) % 3)); // Different colors

        drawSphere(0.1f, 10, 10); // Small sphere with radius 0.1
        glPopMatrix();
    }
}

// Function to draw colored rings
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

// Function to resize the window
void resize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Display Function
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

    // Get time for movement
    GLfloat time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Get elapsed time in seconds

    // Draw small textured objects
    drawSmallTexturedObjects(time);

    // Draw rotating colored rings
    drawColoredRings(1.2
