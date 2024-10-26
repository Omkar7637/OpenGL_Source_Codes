// header files
#include <GL/freeglut.h>
#include <math.h>
#include <stdbool.h>  // For boolean type

// global variable declarations
BOOL bFullScreen = FALSE;

// Global variables for rotation and scale
float angle = 0.0f;         // Rotation angle
float scale_factor = 1.0f;  // Scale factor for the shape
bool growing = true;        // Flag to determine if the shape is growing

// Function prototypes
int initialize(void);
void resize(int, int);
void display(void);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);
void uninitialize(void);

// Entry-point function
int main(int argc, char* argv[])
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Omkar Ankush Kashid");

    // Initialize the scene
    initialize();

    // Register callback functions
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutCloseFunc(uninitialize);

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}

int initialize(void)
{
    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    return 0;
}

void resize(int width, int height)
{
    // Set the viewport
    glViewport(0, 0, width, height);
}

// Display callback function
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

    glPushMatrix();  // Save the current transformation matrix

    // Apply transformations
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Rotate around z-axis
    glScalef(scale_factor, scale_factor, 1.0f);  // Scale the shape

    // Draw a square
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();

    glPopMatrix();  // Restore the transformation matrix

    glutSwapBuffers();  // Swap the front and back buffers

    // Update rotation angle and scale factor for animation
    angle += 1.0f;  // Rotate by 1 degree per frame
    if (growing) {
        scale_factor += 0.01f;
        if (scale_factor >= 1.5f) growing = false;
    } else {
        scale_factor -= 0.01f;
        if (scale_factor <= 0.5f) growing = true;
    }

    glutPostRedisplay();  // Redisplay to animate
}

// Keyboard callback function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:  // Escape key
        glutLeaveMainLoop();
        break;
    case 'F':
    case 'f':
        if (bFullScreen == FALSE)
        {
            glutFullScreen();
            bFullScreen = TRUE;
        }
        else
        {
            glutLeaveFullScreen();
            bFullScreen = FALSE;
        }
        break;
    default:
        break;
    }
}

// Mouse callback function
void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        glutLeaveMainLoop();
        break;
    default:
        break;
    }
}

// Uninitialize function
void uninitialize(void)
{
    // Cleanup code can go here
}
