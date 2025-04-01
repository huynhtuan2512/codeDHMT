//#include <iostream>
//#include <GL/glut.h>
//using namespace std;
//
//float angle = 0.0f;
//float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
//float Iz = 5.0f;
//int choice, choiceRot;
//
//void init() {
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//    glEnable(GL_DEPTH_TEST);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0, 1.0, 1.0, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void drawCube() {
//    // Thêm màu s?c và các m?t cho cube
//    glBegin(GL_QUADS);
//        // Front face (red)
//        glColor3f(1.0, 0.0, 0.0);
//        glVertex3f(-1.0, -1.0, 1.0);
//        glVertex3f(1.0, -1.0, 1.0);
//        glVertex3f(1.0, 1.0, 1.0);
//        glVertex3f(-1.0, 1.0, 1.0);
//        
//        // Back face (green)
//        glColor3f(0.0, 1.0, 0.0);
//        glVertex3f(-1.0, -1.0, -1.0);
//        glVertex3f(1.0, -1.0, -1.0);
//        glVertex3f(1.0, 1.0, -1.0);
//        glVertex3f(-1.0, 1.0, -1.0);
//        
//        // Thêm các m?t khác tuong t?...
//    glEnd();
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    
//    // Ði?u ch?nh v? trí camera
//    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    
//    glPushMatrix(); // Luu ma tr?n hi?n t?i
//    
//    switch(choice) {
//        case 1: // Perspective
//            glTranslatef(0.0f, 0.0f, -Iz);
//            break;
//        case 2: // Scaling
//            glScalef(scaleX, scaleY, scaleZ);
//            break;
//        case 3: // Rotation
//            switch(choiceRot) {
//                case 1: // X-axis
//                    glRotatef(angle, 1.0, 0.0, 0.0);
//                    break;
//                case 2: // Y-axis
//                    glRotatef(angle, 0.0, 1.0, 0.0);
//                    break;
//                case 3: // Z-axis
//                    glRotatef(angle, 0.0, 0.0, 1.0);
//                    break;
//            }
//            break;
//    }
//    
//    drawCube();
//    glPopMatrix(); // Khôi ph?c ma tr?n
//    
//    glutSwapBuffers();
//}
//
//void reshape(int w, int h) {
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0, (float)w/h, 1.0, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("OpenGL Transformations");
//    
//    init();
//    
//    cout << "Enter your choice:\n1. Translation\n2. Scaling\n3. Rotation\n=> ";
//    cin >> choice;
//    
//    if(choice == 1) {
//        cout << "Enter Iz (translation along Z): ";
//        cin >> Iz;
//    }
//    else if(choice == 2) {
//        cout << "Enter scale factors (sx sy sz): ";
//        cin >> scaleX >> scaleY >> scaleZ;
//    }
//    else if(choice == 3) {
//        cout << "Enter rotation axis (1:X, 2:Y, 3:Z): ";
//        cin >> choiceRot;
//        cout << "Enter rotation angle: ";
//        cin >> angle;
//    }
//    
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutMainLoop();
//    
//    return 0;
//}
