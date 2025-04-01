//#include <GL/glut.h>
//#include <iostream>
//
//using namespace std;
//
//const int win_width = 800;
//const int win_height = 800;
//float Angle = 0.0;
//GLuint object;
//
//void drawModel() {
//    glColor3f(1.0, 0.0, 0.0);
//    glutSolidTeapot(1.0); // V? ?m trà 3D làm v?t th? m?u
//}
//
//void createDisplayList() {
//    object = glGenLists(1);
//    glNewList(object, GL_COMPILE);
//    drawModel();
//    glEndList();
//}
//
//void myDisplay() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // Top left: Top view
//    glViewport(0, win_height / 2, win_width / 2, win_height / 2);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
//    gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glCallList(object);
//
//    // Top right: Right view
//    glViewport(win_width / 2, win_height / 2, win_width / 2, win_height / 2);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
//    gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glCallList(object);
//
//    // Bottom left: Front view
//    glViewport(0, 0, win_width / 2, win_height / 2);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
//    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glCallList(object);
//
//    // Bottom right: Rotating perspective view
//    glViewport(win_width / 2, 0, win_width / 2, win_height / 2);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(70.0, 1.0, 1.0, 50.0);
//    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glRotatef(30.0, 1.0, 0.0, 0.0);
//    glRotatef(Angle, 0.0, 1.0, 0.0);
//    glCallList(object);
//
//    glutSwapBuffers();
//}
//
//void update(int value) {
//    Angle += 2.0;
//    if (Angle > 360.0) Angle -= 360.0;
//    glutPostRedisplay();
//    glutTimerFunc(30, update, 0);
//}
//
//void init() {
//    glEnable(GL_DEPTH_TEST);
//    createDisplayList();
//}
//
//int main(int argc, char **argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(win_width, win_height);
//    glutCreateWindow("Projection Views");
//
//    init();
//    glutDisplayFunc(myDisplay);
//    glutTimerFunc(30, update, 0);
//    glutMainLoop();
//
//    return 0;
//}

