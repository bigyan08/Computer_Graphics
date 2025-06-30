#include <GL/glut.h>
#include <cmath>

float x_offset = 0.0f;

const float PI = 3.14159265358979323846;

void drawCircle(float cx, float cy, float r, int segments = 100) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * float(i) / float(segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawBicycle(float offset) {
    glColor3f(0, 0, 0); // black

    // Frame
    glBegin(GL_LINES);
    glVertex2f(50 + offset, 405); glVertex2f(100 + offset, 405);        // bottom line
    glVertex2f(75 + offset, 375); glVertex2f(125 + offset, 375);        // top line
    glVertex2f(50 + offset, 405); glVertex2f(75 + offset, 375);         // diagonal left
    glVertex2f(100 + offset, 405); glVertex2f(75 + offset, 375);        // diagonal right
    glVertex2f(150 + offset, 405); glVertex2f(100 + offset, 345);       // rear diagonal
    glVertex2f(70 + offset, 370); glVertex2f(80 + offset, 370);         // seat
    glVertex2f(80 + offset, 345); glVertex2f(100 + offset, 345);        // rear connector
    glEnd();

    // Wheels
    drawCircle(150 + offset, 405, 30);
    drawCircle(50 + offset, 405, 30);

    // Ground Line
    glBegin(GL_LINES);
    glVertex2f(0, 436); glVertex2f(700, 436);
    glEnd();

    // Optional: top rectangle animation (imitating a banner or object)
    glBegin(GL_LINE_LOOP);
    glVertex2f(650 - offset, 436); glVertex2f(650 - offset, 500);
    glVertex2f(650 - offset - 100, 500); glVertex2f(650 - offset - 100, 436);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBicycle(x_offset);
    glutSwapBuffers();
}

void timer(int) {
    x_offset += 1.0f;
    if (x_offset > 600) x_offset = 0;
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0); // delay(10)
}

void init() {
    glClearColor(1, 1, 1, 1); // white background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 700, 500,0); // 2D coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bicycle Animation - OpenGL Version of BGI");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
