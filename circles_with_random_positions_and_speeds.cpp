#include <GL/freeglut.h>
#include <math.h>
#include <stdbool.h>

// Global Variables
#define MAX_CIRCLES 5
typedef struct {
    float x, y;            // Position
    float radius;         // Radius
    float dx, dy;         // Movement direction
    float red, green, blue; // Color
} Circle;

Circle circles[MAX_CIRCLES];

// Function Prototypes
int initialize(void);
void resize(int, int);
void display(void);
void update(int);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void uninitialize(void);

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Advanced Animation");

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
    // Initialize circles with random positions and speeds
    for (int i = 0; i < MAX_CIRCLES; i++) {
        circles[i].x = ((float) rand() / RAND_MAX) * 1.8 - 0.9;  // Random x between -0.9 and 0.9
        circles[i].y = ((float) rand() / RAND_MAX) * 1.8 - 0.9;  // Random y between -0.9 and 0.9
        circles[i].radius = 0.05f;
        circles[i].dx = ((float) rand() / RAND_MAX) * 0.02 - 0.01;  // Random dx between -0.01 and 0.01
        circles[i].dy = ((float) rand() / RAND_MAX) * 0.02 - 0.01;  // Random dy between -0.01 and 0.01
        circles[i].red = ((float) rand() / RAND_MAX);
        circles[i].green = ((float) rand() / RAND_MAX);
        circles[i].blue = ((float) rand() / RAND_MAX);
    }
    return 0;
}

void resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

    // Draw each circle
    for (int i = 0; i < MAX_CIRCLES; i++) {
        glColor3f(circles[i].red, circles[i].green, circles[i].blue);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(circles[i].x, circles[i].y);  // Center of the circle
        for (int j = 0; j <= 20; j++) {  // Draw a circle
            float angle = 2.0f * 3.14159f * (float) j / 20;
            glVertex2f(circles[i].x + circles[i].radius * cosf(angle), circles[i].y + circles[i].radius * sinf(angle));
        }
        glEnd();
    }

    glutSwapBuffers();  // Swap the front and back buffers
}

void update(int value) {
    for (int i = 0; i < MAX_CIRCLES; i++) {
        circles[i].x += circles[i].dx;
        circles[i].y += circles[i].dy;

        // Bounce off walls
        if (circles[i].x + circles[i].radius > 1.0f || circles[i].x - circles[i].radius < -1.0f) {
            circles[i].dx *= -1;  // Reverse direction
        }
        if (circles[i].y + circles[i].radius > 1.0f || circles[i].y - circles[i].radius < -1.0f) {
            circles[i].dy *= -1;  // Reverse direction
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
                glutLeaveFullScreen();
                bFullScreen = FALSE;
            }
            break;
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glutLeaveMainLoop();
    }
}

void uninitialize(void) {
    // Cleanup code can go here
}
