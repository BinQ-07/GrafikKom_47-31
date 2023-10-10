#define _USE_MATH_DEFINES 

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Global variables for adjusting the monitor board
GLfloat boardWidth = 10.0f;  // Initial width of the board
GLfloat boardHeight = 6.0f; // Initial height of the board
GLfloat boardDepth = 0.1f;  // Initial depth of the board
GLfloat boardXRotation = 0.0f; // Initial rotation around the X-axis
GLfloat boardYRotation = 0.0f; // Initial rotation around the Y-axis
GLfloat boardZRotation = 0.0f;


// Function to draw the 3D monitor and stand
void drawMonitor() {
    glPushMatrix();
    glRotatef(boardYRotation, 0.0f, 1.0f, 0.0f); // Apply Y-axis rotation
    glRotatef(boardXRotation, 1.0f, 0.0f, 0.0f); // Apply X-axis rotation
    glRotatef(boardZRotation, 0.0f, 0.0f, 1.0f);

    // Papan tulis
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -(boardDepth / 2)); 
    glScalef(boardWidth, boardHeight, boardDepth);
    glutSolidCube(1.0f); 
    glPopMatrix();

    // Pinggiran bawah
   glColor3f(0.7f, 0.7f, 0.7f); // 
   glPushMatrix();
   glTranslatef(0.0f, -boardHeight / 2, -(boardDepth / 2)); // 
    glScalef(boardWidth, 0.5f, boardDepth); // 
    glutSolidCube(1.0f); // 
    glPopMatrix();

    // Pinggiran atas
    glColor3f(0.7f, 0.7f, 0.7f); 
    glPushMatrix();
    
    glTranslatef(0.0f, boardHeight / 2, -(boardDepth / 2)); // 
    glScalef(boardWidth, 0.5f, boardDepth); // 
    glutSolidCube(1.0f); 
    glPopMatrix();

    //Pinggiran kanan
    glColor3f(0.7f, 0.7f, 0.7f);  
    glPushMatrix();
    
    glTranslatef(boardWidth/2, 0.0f, -(boardDepth / 2));
    glScalef(0.5f, boardHeight + 0.5f, boardDepth); 
    glutSolidCube(1.0f); 
    glPopMatrix();

    //Pinggiran kiri
    glColor3f(0.7f, 0.7f, 0.7f); 
    glPushMatrix();
    
    glTranslatef(- boardWidth / 2, 0.0f, -(boardDepth / 2)); // 
    glScalef(0.5f, boardHeight + 0.5f, boardDepth); // 
    glutSolidCube(1.0f); 
    glPopMatrix();

    //tempat spidol
    glColor3f(0.5f, 0.5f, 0.5f); // 
    glPushMatrix();
    
   
    glTranslatef(0.0f, -boardHeight / 2, -0.5f); // 
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(boardWidth, 1.0f, boardDepth); // 
    glutSolidCube(1.0f); // 
    glPopMatrix();

    glPopMatrix(); 
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the background color to white
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Set the camera position and view
    gluLookAt(0.0, 0.0, -20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw the 3D monitor
    drawMonitor();

    glutSwapBuffers();
}

// Reshape callback function
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard callback function for adjusting parameters
void keyboard(unsigned char key, int x, int y) {
    switch (key) {

    case 'z':
        boardZRotation += 5.0f; // Rotate board upward
        break;
    case 'x':
        boardZRotation -= 5.0f; // Rotate board upward
        break;

    case 27: // Escape key
        exit(0);
        break;
    }

    glutPostRedisplay(); // Request a redraw
}

void SpecialKey(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP:
        boardXRotation += 5.0f; // Rotate board upward
        break;
    case GLUT_KEY_LEFT:
        boardYRotation -= 5.0f; // Rotate board left
        break;
    case GLUT_KEY_RIGHT:
        boardYRotation += 5.0f; // Rotate board right
        break;
    case GLUT_KEY_DOWN:
        boardXRotation -= 5.0f; // Rotate board downward
        break;
    }
    glutPostRedisplay();
}

/*void mouseWheel(int wheel, int direction, int x, int y)
{
    // Increment/decrement size of current point (at the back of vector points)
    // depending on the direction of rotation of the mouse wheel.
    (direction > 0) ? tempZ++ : tempZ--;
    //points.back().setSize(tempSize);

    glutPostRedisplay();
}*/

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Papan Tulis");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKey);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}