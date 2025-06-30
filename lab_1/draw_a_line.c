#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float x_start, y_start, x_end, y_end;

// Draw a pixel
void drawPixel(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

// DDA Line Drawing Algorithm
void DDA(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    float xi = dx / steps;
    float yi = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        drawPixel(round(x), round(y));
        x += xi;
        y += yi;
    }
}

// Draw X and Y axes
void drawAxes() {
    glColor3f(0.5, 0.5, 0.5); // Gray axes
    glBegin(GL_LINES);
    glVertex2f(-320, 0);
    glVertex2f(320, 0);   // X-axis

    glVertex2f(0, -240);
    glVertex2f(0, 240);   // Y-axis
    glEnd();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    glColor3f(1.0, 1.0, 1.0); // White line
    DDA(x_start, y_start, x_end, y_end);

    glFlush();
}

// OpenGL init
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);               // Black background
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);       // Center origin in window
}

int main(int argc, char** argv) {
    printf("Enter x1 y1: ");
    scanf("%f %f", &x_start, &y_start);
    printf("Enter x2 y2: ");
    scanf("%f %f", &x_end, &y_end);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("DDA Line Drawing with Axes");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
