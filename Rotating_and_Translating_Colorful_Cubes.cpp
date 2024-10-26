#include <GL/freeglut.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// Global Variables
#define MAX_CUBES 5
typedef struct {
    float x, y, z;        // Position
    float rotation;       // Rotation angle
    float size;           // Size of the cube
    float dx, dy, dz;     // Movement direction
    float red, green, blue; // Color
} Cube;

Cube cubes[MAX_CUBES];
bool bFullScreen = false;

// Function Prototypes
int initialize(void);
void resize(int, int);
void display(void);
void update(int);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void uninitialize(void);
void drawCube(Cube* cube);

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Advanced Animation with Cubes");

    initialize();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutCloseFunc(uninitialize);

    // Set timer for animation
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}

int initialize(void) {
    glEnable(GL_DEPTH_TEST); // Enable depth testing

    // Initialize cubes with random positions, sizes, and speeds
    for (int i = 0; i < MAX_CUBES; i++) {
        cubes[i].x = ((float)rand() / RAND_MAX) * 1.8 - 0.9;  // Random x between -0.9 and 0.9
        cubes[i].y = ((float)rand() / RAND_MAX) * 1.8 - 0.9;  // Random y between -0.9 and 0.9
        cubes[i].z = ((float)rand() / RAND_MAX) * -1.0f;      // Random z for 3D effect
        cubes[i].rotation = 0.0f; 
        cubes[i].size = 0.1f + ((float)rand() / RAND_MAX) * 0.1f;  // Random size between 0.1 and 0.2
        cubes[i].dx = ((float)rand() / RAND_MAX) * 0.01f - 0.005f; // Random dx
        cubes[i].dy = ((float)rand() / RAND_MAX) * 0.01f - 0.005f; // Random dy
        cubes[i].red = ((float)rand() / RAND_MAX);
        cubes[i].green = ((float)rand() / RAND_MAX);
        cubes[i].blue = ((float)rand() / RAND_MAX);
    }
    return 0;
}

void resize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
    glLoadIdentity(); // Load the identity matrix

    gluLookAt(0.0f, 0.0f, 3.0f,  // Camera position
              0.0f, 0.0f, 0.0f,  // Look at point
              0.0f, 1.0f, 0.0f); // Up vector

    // Draw each cube
    for (int i = 0; i < MAX_CUBES; i++) {
        drawCube(&cubes[i]);
    }

    glutSwapBuffers(); // Swap the front and back buffers
}

void drawCube(Cube* cube) {
    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations
    glTranslatef(cube->x, cube->y, cube->z); // Translate to cube's position
    glRotatef(cube->rotation, 1.0f, 1.0f, 0.0f); // Rotate the cube

    // Set color
    glColor3f(cube->red, cube->green, cube->blue);

    // Draw the cube
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(-cube->size, -cube->size, cube->size);
    glVertex3f(cube->size, -cube->size, cube->size);
    glVertex3f(cube->size, cube->size, cube->size);
    glVertex3f(-cube->size, cube->size, cube->size);

    // Back face
    glVertex3f(-cube->size, -cube->size, -cube->size);
    glVertex3f(-cube->size, cube->size, -cube->size);
    glVertex3f(cube->size, cube->size, -cube->size);
    glVertex3f(cube->size, -cube->size, -cube->size);

    // Left face
    glVertex3f(-cube->size, -cube->size, -cube->size);
    glVertex3f(-cube->size, -cube->size, cube->size);
    glVertex3f(-cube->size, cube->size, cube->size);
    glVertex3f(-cube->size, cube->size, -cube->size);

    // Right face
    glVertex3f(cube->size, -cube->size, cube->size);
    glVertex3f(cube->size, -cube->size, -cube->size);
    glVertex3f(cube->size, cube->size, -cube->size);
    glVertex3f(cube->size, cube->size, cube->size);

    // Top face
    glVertex3f(-cube->size, cube->size, -cube->size);
    glVertex3f(cube->size, cube->size, -cube->size);
    glVertex3f(cube->size, cube->size, cube->size);
    glVertex3f(-cube->size, cube->size, cube->size);

    // Bottom face
    glVertex3f(-cube->size, -cube->size, cube->size);
    glVertex3f(-cube->size, -cube->size, -cube->size);
    glVertex3f(cube->size, -cube->size, -cube->size);
    glVertex3f(cube->size, -cube->size, cube->size);
    glEnd();

    glPopMatrix();  // Restore the transformation matrix

    // Update rotation angle for animation
    cube->rotation += 1.0f;  // Rotate by 1 degree per frame

    // Change color over time
    cube->red += 0.01f;  // Increment red component
    cube->green += 0.02f;  // Increment green component
    cube->blue += 0.03f;  // Increment blue component

    // Loop the colors
    if (cube->red > 1.0f) cube->red = 0.0f;
    if (cube->green > 1.0f) cube->green = 0.0f;
    if (cube->blue > 1.0f) cube->blue = 0.0f;
}

void update(int value) {
    // Update the position of each cube
    for (int i = 0; i < MAX_CUBES; i++) {
        cubes[i].x += cubes[i].dx;
        cubes[i].y += cubes[i].dy;

        // Bounce off walls
        if (cubes[i].x + cubes[i].size > 1.0f || cubes[i].x - cubes[i].size < -1.0f) {
            cubes[i].dx *= -1;  // Reverse direction
        }
        if (cubes[i].y + cubes[i].size > 1.0f || cubes[i].y - cubes[i].size < -1.0f) {
            cubes[i].dy *= -1;  // Reverse direction
        }
    }

    glutPostRedisplay();  // Request a redraw
    glutTimerFunc(16, update, 0);  // Call update again after 16 ms (approximately 60 FPS)
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:  // Escape key
            glutLeaveMainLoop();
            break;
        case 'F':
        case 'f':
            // Fullscreen toggle
            if (bFullScreen == FALSE) {
                glutFullScreen();
                bFullScreen = TRUE;
            } else {
                glutReshapeWindow(800, 600);
                bFullScreen = FALSE;
            }
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Add more cubes on mouse click
        for (int i = 0; i < MAX_CUBES; i++) {
            if (cubes[i].size <= 0.1f) { // Limit cube size
                cubes[i].x = (x / 400.0f) - 1.0f; // Convert x to OpenGL coordinates
                cubes[i].y = -((y / 300.0f) - 1.0f); // Convert y to OpenGL coordinates
                cubes[i].z = ((float)rand() / RAND_MAX) * -1.0f; // Set random z
                cubes[i].size = 0.1f; // Set size
                cubes[i].red = ((float)rand() / RAND_MAX);
                cubes[i].green = ((float)rand() / RAND_MAX);
                cubes[i].blue = ((float)rand() / RAND_MAX);
                break; // Only add one cube at a time
            }
        }
    }
}

void uninitialize(void) {
    // Cleanup code if needed
}

