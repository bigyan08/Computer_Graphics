#include <GL/glut.h>
#include <stdio.h>

// Ellipse parameters
int xc, yc, a, b;

void plotEllipsePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
    glEnd();
}

void drawAxes() {
    glBegin(GL_LINES);
        glVertex2i(-500, 0); glVertex2i(500, 0);   // X-axis
        glVertex2i(0, -500); glVertex2i(0, 500);   // Y-axis
    glEnd();
}

void midpointEllipse() {
    int x = 0, y = b;
    float a2 = a * a;
    float b2 = b * b;

    float p1 = b2 - (a2 * b) + (0.25 * a2);
    plotEllipsePoints(xc, yc, x, y);

    // Region 1
    while ((2 * b2 * x) <= (2 * a2 * y)) {
        x++;
        if (p1 < 0) {
            p1 += 2 * b2 * x + b2;
        } else {
            y--;
            p1 += 2 * b2 * x - 2 * a2 * y + b2;
        }
        plotEllipsePoints(xc, yc, x, y);
    }

    // Region 2
    float p2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;
    while (y > 0) {
        y--;
        if (p2 > 0) {
            p2 -= 2 * a2 * y + a2;
        } else {
            x++;
            p2 += 2 * b2 * x - 2 * a2 * y + a2;
        }
        plotEllipsePoints(xc, yc, x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // white

    drawAxes();
    midpointEllipse();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // black background
    glColor3f(1.0, 1.0, 1.0);          // drawing color
    glPointSize(2.0);                  // point size

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);  // coordinate system
}

int main(int argc, char** argv) {
    printf("Enter center (xc yc) and semi-axes (a b): ");
    scanf("%d %d %d %d", &xc, &yc, &a, &b);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Ellipse Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
