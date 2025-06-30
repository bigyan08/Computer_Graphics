#include <GL/glut.h>

void drawText(const char* text) {
    while (*text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *text++);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // First "WRC" - normal size
    glPushMatrix();
        glTranslatef(-0.9f, 0.5f, 0.0f);
        glScalef(0.004f, 0.004f, 1.0f); // scale to fit window
        drawText("WRC");
    glPopMatrix();

    // Second "WRC" - smaller
    glPushMatrix();
        glTranslatef(-0.6f, 0.0f, 0.0f);
        glScalef(0.003f, 0.003f, 1.0f);
        drawText("WRC");
    glPopMatrix();

    // Third "WRC" - even smaller
    glPushMatrix();
        glTranslatef(-0.4f, -0.4f, 0.0f);
        glScalef(0.0015f, 0.0015f, 1.0f);
        drawText("WRC");
    glPopMatrix();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
    glColor3f(0.0, 0.0, 0.0);         // black text
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);        // set coordinate system
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("WRC Scaling");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

