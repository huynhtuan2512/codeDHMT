//#include <GL/glut.h>
//#include <cmath>
//
//// T?a d? di?m P và Q
//float P[3] = {1.0f, 2.0f, 0.0f};
//float Q[3] = {7.0f, 14.0f, 0.0f};
//
//// Góc quay
//float angle = 30.0f;
//
//// Hàm kh?i t?o
//void init() {
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Màu n?n den
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(-20.0, 20.0, -20.0, 20.0); // Thi?t l?p h? t?a d? 2D
//    glMatrixMode(GL_MODELVIEW);
//}
//
//// Hàm v? du?ng th?ng PQ
//void drawLine() {
//    glBegin(GL_LINES);
//    glVertex3fv(P);
//    glVertex3fv(Q);
//    glEnd();
//}
//
//// Hàm hi?n th?
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glLoadIdentity();
//
//    glColor3f(1.0f, 1.0f, 1.0f); // Màu v? tr?ng
//    drawLine();
//
//    glutSwapBuffers();
//}
//
//// Hàm x? lý s? ki?n bàn phím
//void keyboard(unsigned char key, int x, int y) {
//    switch (key) {
//        case 't': // D?ch chuy?n theo tr?c x
//            P[0] += 5.0f;
//            Q[0] += 5.0f;
//            break;
//        case 'T': // D?ch chuy?n ngu?c l?i theo tr?c x
//            P[0] -= 5.0f;
//            Q[0] -= 5.0f;
//            break;
//        case 'r': // Quay quanh tr?c Oy
//            glPushMatrix();
//            glRotatef(angle, 0.0f, 1.0f, 0.0f);
//            drawLine();
//            glPopMatrix();
//            break;
//        case 'R': // Quay ngu?c l?i quanh tr?c Oy
//            glPushMatrix();
//            glRotatef(-angle, 0.0f, 1.0f, 0.0f);
//            drawLine();
//            glPopMatrix();
//            break;
//        case 'p': // L?y d?i x?ng qua tr?c Ox
//            P[1] = -P[1];
//            Q[1] = -Q[1];
//            break;
//        case 'P': // L?y d?i x?ng qua tr?c Ox (ph?c h?i)
//            P[1] = -P[1];
//            Q[1] = -Q[1];
//            break;
//        case 'f': // L?y d?i x?ng qua tr?c MN (gi? s? MN là tr?c Ox)
//            P[1] = -P[1];
//            Q[1] = -Q[1];
//            break;
//        case 'F': // L?y d?i x?ng qua tr?c MN (ph?c h?i)
//            P[1] = -P[1];
//            Q[1] = -Q[1];
//            break;
//        case 'h': // Quay quanh tr?c MN (gi? s? MN là tr?c Ox)
//            glPushMatrix();
//            glRotatef(angle, 1.0f, 0.0f, 0.0f);
//            drawLine();
//            glPopMatrix();
//            break;
//        case 'H': // Quay ngu?c l?i quanh tr?c MN
//            glPushMatrix();
//            glRotatef(-angle, 1.0f, 0.0f, 0.0f);
//            drawLine();
//            glPopMatrix();
//            break;
//    }
//    glutPostRedisplay();
//}
//
//// Hàm main
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(500, 500);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("Transformations of Line PQ");
//    init();
//    glutDisplayFunc(display);
//    glutKeyboardFunc(keyboard);
//    glutMainLoop();
//    return 0;
//}
