//#include <GL/glut.h>
//#include <cmath>
//
//// Góc quay c?a v?t th?
//float angle = 0.0f;
//
//void init() {
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//}
//
//void reshape(int w, int h) {
//    if (h == 0) h = 1;
//    float aspect = (float)w / (float)h;
//    
//    glViewport(0, 0, w, h);
//    
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    
//    glTranslatef(0.0f, 0.0f, -5.0f);
//    glRotatef(angle, 0.0f, 1.0f, 0.0f);
//    
//    glBegin(GL_QUADS);
//        // M?t tru?c
//        glColor3f(1.0f, 0.0f, 0.0f);
//        glVertex3f(-1.0f, -1.0f, 1.0f);
//        glVertex3f(1.0f, -1.0f, 1.0f);
//        glVertex3f(1.0f, 1.0f, 1.0f);
//        glVertex3f(-1.0f, 1.0f, 1.0f);
//
//        // M?t sau
//        glColor3f(0.0f, 1.0f, 0.0f);
//        glVertex3f(-1.0f, -1.0f, -1.0f);
//        glVertex3f(-1.0f, 1.0f, -1.0f);
//        glVertex3f(1.0f, 1.0f, -1.0f);
//        glVertex3f(1.0f, -1.0f, -1.0f);
//
//        // M?t trên
//        glColor3f(0.0f, 0.0f, 1.0f);
//        glVertex3f(-1.0f, 1.0f, -1.0f);
//        glVertex3f(-1.0f, 1.0f, 1.0f);
//        glVertex3f(1.0f, 1.0f, 1.0f);
//        glVertex3f(1.0f, 1.0f, -1.0f);
//    glEnd();
//    
//    glutSwapBuffers();
//}
//
//void update(int value) {
//    angle += 1.0f;
//    if (angle > 360) {
//        angle -= 360;
//    }
//    glutPostRedisplay();
//    glutTimerFunc(16, update, 0);
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Perspective Projection");
//    
//    init();
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutTimerFunc(16, update, 0);
//    
//    glutMainLoop();
//    return 0;
//}

