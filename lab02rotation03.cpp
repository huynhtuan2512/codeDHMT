//#include <GL/glut.h>
//
//#include <GL/gl.h>
//
//
//static GLfloat spin = 0.0; // Goc quay hien tai cua hinh chu nhat
//
//
//void init(void)
//
//{
//
//glClearColor(0.0, 0.0, 0.0, 0.0);
//
//glShadeModel(GL_FLAT);
//
//}
//
//void display(void)
//
//{
//
//glClear(GL_COLOR_BUFFER_BIT);
//
//glPushMatrix();
//
//glRotatef(spin, 0.0, 0.0, 1.0); // Xoay mot goc spin quanh truc z
//
//glColor3f(1.0, 1.0, 1.0); // Mau ve cho hcn(mau trang)
//
//glRectf(-25.0, -25.0, 25.0, 25.0); // ve hcn
//
//glPopMatrix();
//
//glutSwapBuffers(); // Hoan doi 2 buffer
//
//}
//
//void spinDisplay(void)
//
//{
//
//spin = spin + 2.0; // Xoay them 2 deg cho moi lan lap
//
//if(spin > 360.0) spin = spin - 360.0;
//
//glutPostRedisplay(); // Thuc hien viec ve lai
//
//}
//
//
//void reshape(int w, int h)
//
//{
//
//glViewport(0, 0,(GLsizei) w,(GLsizei) h);
//
//glMatrixMode(GL_PROJECTION);
//
//glLoadIdentity();
//
//glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
//
//glMatrixMode(GL_MODELVIEW);
//
//glLoadIdentity();
//
//}
//
//
//// Thao tac xu ly chuot
//
//void mouse(int button, int state, int x, int y)
//
//{
//
//switch(button) {
//
//case GLUT_LEFT_BUTTON: // Nhan chuot trai
//
//if(state == GLUT_DOWN)
//
//glutIdleFunc(spinDisplay); // Khi idle thi chay ham spinDisplay
//
//break;
//
//case GLUT_MIDDLE_BUTTON: // Nhan nut giua
//
//if(state == GLUT_DOWN) //glutIdleFunc(NULL);
//
//break;
//
//default: break;
//
//}
//
//}
//
//
//int main(int argc, char** argv)
//
//{
//
//glutInit(&argc, argv);
//
//// Khai bao su dung che do double buffer
//
//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//
//glutInitWindowSize(250, 250);
//
//glutInitWindowPosition(100, 100);
//
//glutCreateWindow("HUYNH DINH TUAN - Modelview matrix");
//
//init();
//
//glutDisplayFunc(display);
//
//glutReshapeFunc(reshape); // Xu ly su kien cua so bi thay doi kich thuoc
//
//glutMouseFunc(mouse); // Dang ky ham mouse cho su kien ve chuot
//
//glutMainLoop();
//
//return 0;
//
//}//main
