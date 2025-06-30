#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
int x1, y1, x2, y2;
// Function to draw a pixel (OpenGL uses float coordinates)
void drawPixelCartesian(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
// Function to draw X and Y axes
void drawAxes() {
    glBegin(GL_LINES);
    // X-axis
    glVertex2i(-500, 0);
    glVertex2i(500, 0);

    // Y-axis
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
}
// Bresenham's Line Algorithm
void drawLineBLA(int x1, int y1, int x2, int y2) {
    int dx, dy, incx, incy, x, y, p, i;
    dx = x2 - x1;
    dy = y2 - y1;
    incx = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
    incy = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);
    dx = abs(dx);
    dy = abs(dy);
    x = x1;
    y = y1;

    drawPixelCartesian(x, y);
    printf("(%d, %d)\n", x, y);  // Print starting pixel

    if (dx > dy) {
        p = 2 * dy - dx;
        for (i = 0; i < dx; i++) {
            x += incx;
            if (p < 0) {
                p += 2 * dy;
            } else {
                y += incy;
                p += 2 * (dy - dx);
            }
            drawPixelCartesian(x, y);
            printf("(%d, %d)\n", x, y);  // Print each pixel
        }
    } else {
        p = 2 * dx - dy;
        for (i = 0; i < dy; i++) {
            y += incy;
            if (p < 0) {
                p += 2 * dx;
            } else {
                x += incx;
                p += 2 * (dx - dy);
            }
            drawPixelCartesian(x, y);
            printf("(%d, %d)\n", x, y);  // Print each pixel
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // white color
    drawAxes();
    drawLineBLA(x1, y1, x2, y2);
    glFlush();
}
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    glColor3f(1.0, 1.0, 1.0);         // Draw in white
    gluOrtho2D(-500, 500, -500, 500); // Set coordinate system
}
int main(int argc, char **argv) {
    printf("Enter starting point (x1 y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter ending point (x2 y2): ");
    scanf("%d %d", &x2, &y2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Line Algorithm - OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
