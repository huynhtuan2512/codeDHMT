//#include <GL/glut.h> // S? d?ng thu vi?n GLUT
//
//void myInit(void) {
//    glClearColor(0.7f, 0.7f, 0.7f, 0.0f); // Thi?t l?p màu n?n là xám
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, 640.0, 0.0, 480.0); // Thi?t l?p h? t?a d? 2D
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void myDisplay(void) {
//    int x = 320, y = 240; // T?a d? tâm c?a hình ch? nh?t
//    glClear(GL_COLOR_BUFFER_BIT); // Xóa màn hình v?i màu n?n dã thi?t l?p
//
//    // V? hình ch? nh?t màu d?
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glRecti(x - 100, y - 100, x + 100, y + 100);
//
//    // V? hình ch? nh?t màu vàng và xoay 20 d?
//    glColor3f(1.0f, 1.0f, 0.0f);
//    glPushMatrix(); // Luu ma tr?n hi?n t?i
//    glTranslatef(x, y, 0.0f); // Di chuy?n g?c t?a d? d?n tâm hình ch? nh?t
//    glRotatef(20.0f, 0.0f, 0.0f, 1.0f); // Xoay 20 d? quanh tr?c Z
//    glTranslatef(-x, -y, 0.0f); // Di chuy?n g?c t?a d? tr? l?i v? trí ban d?u
//    glRecti(x - 100, y - 100, x + 100, y + 100); // V? hình ch? nh?t
//    glPopMatrix(); // Khôi ph?c ma tr?n ban d?u
//
//    glFlush(); // Hi?n th? k?t qu?
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv); // Kh?i t?o GLUT
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Thi?t l?p ch? d? hi?n th?
//    glutInitWindowSize(640, 480); // Thi?t l?p kích thu?c c?a s?
//    glutInitWindowPosition(100, 150); // Thi?t l?p v? trí c?a s?
//    glutCreateWindow("Thi du 4.1"); // T?o c?a s? v?i tiêu d?
//    glutDisplayFunc(myDisplay); // Ðang ký hàm callback hi?n th?
//    myInit(); // G?i hàm kh?i t?o
//    glutMainLoop(); // Vòng l?p chính c?a GLUT
//    return 0;
//}
