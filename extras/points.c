#include<GL/glut.h>

void Render()
{
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Load the identity matrix
    glLoadIdentity();
    
    // Move forward 4 units
    glTranslatef(0.0f, 0.0f, -4.0f);
    
    // Set the color to blue
    glColor3f(0.0f, 0.0f, 1.0f);
    
    // Begin drawing points
    glBegin(GL_POINTS);
        // Draw the first point
        glVertex3f(-0.5f, 0.5f, 0.0f);
        
        // Draw the second point
        glVertex3f(0.5f, -0.5f, 0.0f);
    glEnd();
}
