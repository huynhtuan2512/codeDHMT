#include "GL/glut.h"


//Ham thuc hien ve doi tuong

void display(void)

{

//Xoa moi pixel

glClear(GL_COLOR_BUFFER_BIT);


// Ve hinh chu nhat co diem trai-tren (0.25, 0.25, 0.0) va phai-duoi

// (0.75, 0.75, 0.0)

glColor3f (1.0, 1.0, 1.0); //Thiet lap mau ve: mau trang

glBegin(GL_POLYGON); //Bat dau ve da giac

glVertex3f (0.25, 0.25, 0.0); //cac dinh cua da giac

glVertex3f (0.75, 0.25, 0.0);

glVertex3f (0.75, 0.75, 0.0);

glVertex3f (0.25, 0.75, 0.0);

glEnd(); //Ket thuc ve da giac

glFlush (); //Thuc hien qua trinh day ra buffer

}


// Ham khoi tao cac thông so khi chay

void init (void)

{

//Chon mau de xoa nen

glClearColor (0.0, 0.0, 0.0, 0.0); /* mau den */


//Thiet lap cac thong so cho view

glMatrixMode(GL_PROJECTION);

glLoadIdentity();

glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}


int main(int argc, char** argv)

{

glutInit(&argc, argv);


//Khoi tao che do ve single buffer va he mau RGB

glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);


//Khoi tao window kich thuoc 250 x 250

glutInitWindowSize (250, 250);


//Khoi tao window tai vi tri (100,100) tren screen

glutInitWindowPosition (100, 100);

glutCreateWindow ("Lab01 HUYNH DINH TUAN"); // Thay ten SV vao


//Khoi tao mot so che do do hoa

init ();

glutDisplayFunc(display); //Thiet lap ham ve la ham display()

glutMainLoop(); //Bat dau chu trinh lap the hien ve

return 0;

} //main
