#include <GL/glut.h>
#include <stdbool.h>


typedef enum { RUNNING, GAME_OVER, YOU_WIN } GameState;
GameState gameState = RUNNING;

// Ball
float ballX = 0.0f, ballY = -0.2f;
float ballSpeedX = 0.01f, ballSpeedY = 0.01f;
float ballSize = 0.05f;

// Paddle
float paddleX = 0.0f;
float paddleWidth = 0.3f;
float paddleHeight = 0.05f;

// Blocks
#define MAX_BLOCKS 100
struct Block {
    float x, y;
    bool destroyed;
} blocks[MAX_BLOCKS];
int blockCount = 0;

// Draw rectangle helper
void drawRect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

// Initialize blocks
void initBlocks() {
    blockCount = 0;
    for (float x = -0.9f; x <= 0.9f; x += 0.3f) {
        for (float y = 0.6f; y <= 0.9f; y += 0.15f) {
            blocks[blockCount].x = x;
            blocks[blockCount].y = y;
            blocks[blockCount].destroyed = false;
            blockCount++;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameState == RUNNING) {
        glColor3f(1, 1, 1);
        drawRect(ballX, ballY, ballSize, ballSize);
        drawRect(paddleX, -0.9f, paddleWidth, paddleHeight);

        int i;
        for (i = 0; i < blockCount; i++) {
            if (!blocks[i].destroyed) {
                glColor3f(0.2f + i * 0.05f, 0.5f, 1.0f);
                drawRect(blocks[i].x, blocks[i].y, 0.25f, 0.08f);
            }
        }
    } else {
        // Show end message
        const char *message = (gameState == GAME_OVER) ? "Game Over!" : "You Win!";
        glColor3f(1, 0, 0);
        glRasterPos2f(-0.1f, 0.0f);
        for (int i = 0; message[i] != '\0'; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
        }
    }

    glutSwapBuffers();
}

void update(int value) {
    if (gameState != RUNNING) return;

    // Ball movement
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Wall collision
    if (ballX <= -1.0f || ballX + ballSize >= 1.0f)
        ballSpeedX = -ballSpeedX;
    if (ballY + ballSize >= 1.0f)
        ballSpeedY = -ballSpeedY;

    // Paddle collision
    if (ballY <= -0.85f &&
        ballX + ballSize >= paddleX &&
        ballX <= paddleX + paddleWidth) {
        ballSpeedY = -ballSpeedY;
    }

    // Block collision
    int destroyedCount = 0;
    for (int i = 0; i < blockCount; i++) {
        struct Block *b = &blocks[i];
        if (!b->destroyed &&
            ballX + ballSize >= b->x &&
            ballX <= b->x + 0.25f &&
            ballY + ballSize >= b->y &&
            ballY <= b->y + 0.08f) {
            ballSpeedY = -ballSpeedY;
            b->destroyed = true;
            break;
        }
    }

    // Check win condition
    for (int i = 0; i < blockCount; i++) {
        if (blocks[i].destroyed) destroyedCount++;
    }

    if (destroyedCount == blockCount) {
        gameState = YOU_WIN;
    }

    // Check loss condition
    if (ballY <= -1.0f) {
        gameState = GAME_OVER;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}


void specialKeys(int key, int x, int y) {
    if (gameState != RUNNING) return;
    if (key == GLUT_KEY_LEFT && paddleX > -1.0f)
        paddleX -= 0.05f;
    if (key == GLUT_KEY_RIGHT && paddleX + paddleWidth < 1.0f)
        paddleX += 0.05f;
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Breakout in C - OpenGL");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    initBlocks();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}
