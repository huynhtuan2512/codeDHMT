//#include <windows.h> // for MS Windows
//#include <GL/glut.h> // GLUT, include glu.h and gl.h
//
//// Global variables to store transformation states
//float angle = 0.0f; // Rotation angle
//float dx = 0.0f, dy = 0.0f; // Translation distances
//bool reflectX = false; // Reflection state
//
///* Initialize OpenGL Graphics */
//void init() {
//    // Set "clearing" or background color
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
//    glMatrixMode(GL_MODELVIEW); // To operate on Model-View matrix
//    glLoadIdentity(); // Reset the model-view matrix
//
//    // Apply transformations
//    glTranslatef(dx, dy, 0.0f); // Apply translation
//    glRotatef(angle, 0.0f, 0.0f, 1.0f); // Apply rotation
//    if (reflectX) {
//        glScalef(1.0f, -1.0f, 1.0f); // Reflect over the X-axis
//    }
//
//    // Draw the triangle
//    glBegin(GL_TRIANGLES); // Each set of 3 vertices form a triangle
//    glColor3f(0.0f, 0.0f, 1.0f); // Blue
//    glVertex2f(-0.3f, -0.2f);
//    glVertex2f(0.3f, -0.2f);
//    glVertex2f(0.0f, 0.3f);
//    glEnd();
//
//    glFlush(); // Render now
//}
//
///* Handler for window re-size event */
//void reshape(GLsizei width, GLsizei height) {
//    // Compute aspect ratio of the new window
//    if (height == 0) height = 1; // To prevent divide by 0
//    GLfloat aspect = (GLfloat)width / (GLfloat)height;
//
//    // Set the viewport to cover the new window
//    glViewport(0, 0, width, height);
//
//    // Set the aspect ratio of the clipping area to match the viewport
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    if (width >= height) {
//        // aspect >= 1, set the height from -1 to 1, with larger width
//        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
//    } else {
//        // aspect < 1, set the width to -1 to 1, with larger height
//        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
//    }
//}
//
///* Keyboard input processing */
//void keyboard(unsigned char key, int x, int y) {
//    switch (key) {
//    case 'r': // Rotate 30 degrees
//        angle += 30.0f;
//        if (angle >= 360.0f) angle -= 360.0f;
//        break;
//    case 't': // Translate by (10, 10)
//        dx += 0.1f;
//        dy += 0.1f;
//        break;
//    case 'x': // Reflect over the X-axis
//        reflectX = !reflectX;
//        break;
//    }
//    glutPostRedisplay(); // Request display update
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv); // Initialize GLUT
//    glutInitWindowSize(640, 480); // Set the window's initial width & height - non-square
//    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
//    glutCreateWindow("HUYNH DINH TUAN - Modelview matrix");
//    glutDisplayFunc(display); // Register callback handler for window re-paint event
//    glutReshapeFunc(reshape); // Register callback handler for window re-size event
//    glutKeyboardFunc(keyboard); // Register callback handler for keyboard input event
//    init(); // Our own OpenGL initialization
//    glutMainLoop(); // Enter the infinite event-processing loop
//    return 0;
//}
