//#include <GL/glut.h> // S? d?ng thu vi?n GLUT
//
//void myInit(void) {
//    glClearColor(0.7f, 0.7f, 0.7f, 0.0f); // Thi?t l?p m�u n?n l� x�m
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, 640.0, 0.0, 480.0); // Thi?t l?p h? t?a d? 2D
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void myDisplay(void) {
//    int x = 320, y = 240; // T?a d? t�m c?a h�nh ch? nh?t
//    glClear(GL_COLOR_BUFFER_BIT); // X�a m�n h�nh v?i m�u n?n d� thi?t l?p
//
//    // V? h�nh ch? nh?t m�u d?
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glRecti(x - 100, y - 100, x + 100, y + 100);
//
//    // V? h�nh ch? nh?t m�u v�ng v� xoay 20 d?
//    glColor3f(1.0f, 1.0f, 0.0f);
//    glPushMatrix(); // Luu ma tr?n hi?n t?i
//    glTranslatef(x, y, 0.0f); // Di chuy?n g?c t?a d? d?n t�m h�nh ch? nh?t
//    glRotatef(20.0f, 0.0f, 0.0f, 1.0f); // Xoay 20 d? quanh tr?c Z
//    glTranslatef(-x, -y, 0.0f); // Di chuy?n g?c t?a d? tr? l?i v? tr� ban d?u
//    glRecti(x - 100, y - 100, x + 100, y + 100); // V? h�nh ch? nh?t
//    glPopMatrix(); // Kh�i ph?c ma tr?n ban d?u
//
//    glFlush(); // Hi?n th? k?t qu?
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv); // Kh?i t?o GLUT
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Thi?t l?p ch? d? hi?n th?
//    glutInitWindowSize(640, 480); // Thi?t l?p k�ch thu?c c?a s?
//    glutInitWindowPosition(100, 150); // Thi?t l?p v? tr� c?a s?
//    glutCreateWindow("Thi du 4.1"); // T?o c?a s? v?i ti�u d?
//    glutDisplayFunc(myDisplay); // �ang k� h�m callback hi?n th?
//    myInit(); // G?i h�m kh?i t?o
//    glutMainLoop(); // V�ng l?p ch�nh c?a GLUT
//    return 0;
//}
