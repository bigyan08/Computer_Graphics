#include <GL/glut.h>
#include <stdio.h>

int xc, yc, r;

void plotCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    glEnd();
}

void drawAxes() {
    glBegin(GL_LINES);
        glVertex2i(-500, 0);
        glVertex2i(500, 0);   // X-axis
        glVertex2i(0, -500);
        glVertex2i(0, 500);   // Y-axis
    glEnd();
}

void midpointCircle() {
    int x = 0, y = r;
    float p = 1.25 - r;
    plotCirclePoints(xc, yc, x, y);

    while (x <= y) {
        x++;
        if (p < 0) {
            p += 2*x + 1;
        } else {
            y--;
            p += 2*(x - y) + 1;
        }
        plotCirclePoints(xc, yc, x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // white

    drawAxes();
    midpointCircle();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // black background
    glColor3f(1.0, 1.0, 1.0);          // drawing color
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);  // setting coordinate system
}

int main(int argc, char** argv) {
    printf("Enter center (xc yc) and radius r: ");
    scanf("%d %d %d", &xc, &yc, &r);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
