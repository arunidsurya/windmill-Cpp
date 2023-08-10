
#include <cstdio>
#include <iostream>
#include <GL/glut.h>

GLfloat windmillAngle = 0.0;       // Angle for rotating the windmill blades
GLfloat standAngle = 0.0;          // Angle for rotating the windmill stand
GLfloat baseAngle = 0.0;           // Angle for rotating the windmill base
GLfloat rotationSpeed = 1.0;       // Speed of rotation

void drawBlade()
{
    glBegin(GL_TRIANGLES);
    glColor3f(255,255,255);  // white color for the blades
    glVertex2f(0.0, 0.0);
    glVertex2f(0.2, 0.1);
    glVertex2f(0.2, -0.1);
    glEnd();
}

void drawStand(){

	glColor3f(0.3, 0.3, 0.3);  // Gray color for the base
    glRectf(-0.02, -0.5, 0.02, 0.5);
    glTranslatef(0, -0.6, 0);  // Translate by (x, y, z)
    glEnd();
}

void drawBase(){
	    glColor3f(0.3, 0.3, 0.3);  // Gray color for the base
	    glRectf(-0.1, -0.1, 0.1, 0.1);
	    glTranslatef(0,1.1,0);  // Translate by (x, y, z)
	    glEnd();
}

void drawWindmill()
{
    glPushMatrix();  // Save the current matrix

    drawStand();
    drawBase();

    // Draw the blades
    glRotatef(windmillAngle, 0.0, 0.0, 1.0);  // Rotate the blades
    glScalef(0.8, 0.8, 1.0);  // Scale the blades

    for (int i = 0; i < 4; ++i) {
        drawBlade();  // Draw each blade
        glRotatef(90.0, 0.0, 0.0, 1.0);  // Rotate to the next blade position
    }

    glPopMatrix();  // Restore the previous matrix


}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawWindmill();

    glFlush();

}

void update(int value)
{
    windmillAngle += rotationSpeed;  // Increment the angle for windmill rotation
    standAngle += rotationSpeed;     // Increment the angle for stand rotation
    baseAngle -= rotationSpeed;      // Increment the angle for base rotation

    glutPostRedisplay();  // Mark the current window as needing to be redisplayed

    glutTimerFunc(10, update, 0);  // Call update() again after 10 milliseconds
}

void handleKeypress(unsigned char key, int x, int y)
{
    if (key == '+' && rotationSpeed<10)
        rotationSpeed += 1;  // Increase rotation speed by 1
    else if (key == '-' && rotationSpeed>1)
        rotationSpeed -= 1;  // Decrease rotation speed by 1
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Windmill with Stand and Base");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 5000);  // Call update() initially with a delay of 5 seconds
    glutKeyboardFunc(handleKeypress);  // Register the keyboard callback function

    glutMainLoop();

    return 0;
}

