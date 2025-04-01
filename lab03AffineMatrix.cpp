//#include <math.h>
//#include <GL/glut.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>
//#include <iomanip>
//
//typedef float Matrix4x4[4][4];
//Matrix4x4 Matrix;
//
////Khoi tao cac bien toan cuc
////Khoi tao mang chua toa do cac dinh cua hinh lap phuong
//float points[8][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
//float pointsFin[8][3];					//Mang cac toa do sau khi bien doi
//float TransDistX, TransDistY, TransDistZ; //Tinh tien theo huong X, Y, Z
//float ScaleX, ScaleY, ScaleZ;             //Ty le theo X, Y, Z
//float Theta;          					//Goc quay
//float x, y, z;     
//float x1, y11, z1, x2, y2, z2;
//int choice, choiceRef;
//
////Tinh toan toa do cac dinh
//void inputPoint(float a)
//{
//    points[0][0] = 2 * a + 10;
//    points[0][1] = 2 * a + 10;
//    points[0][2] = 2 * a + 10;
//    
//    points[1][0] = 10;
//    points[1][1] = 2 * a + 10;
//    points[1][2] = 2 * a + 10;
//    
//    points[2][0] = 10;
//    points[2][1] = 10;
//    points[2][2] = 2 * a + 10;
//    
//    points[3][0] = 2 * a + 10;
//    points[3][1] = 10;
//    points[3][2] = 2 * a + 10;
//
//    points[4][0] = 2 * a + 10;
//    points[4][1] = 2 * a + 10;
//    points[4][2] =  10;
//    
//    points[5][0] = 10;
//    points[5][1] = 2 * a + 10;
//    points[5][2] = 10;
//    
//    points[6][0] = 10;
//    points[6][1] = 10;
//    points[6][2] = 10;
//    
//    points[7][0] = 2 * a + 10;
//    points[7][1] = 10;
//    points[7][2] = 10;
//}
//
//// Khoi tao ma tran don vi
//void matrixSetIdentity(Matrix4x4 m) 
//{
//    int i, j;
//    for (i = 0; i < 4; i++)
//    {
//        for (j = 0; j < 4; j++)
//        {
//            m[i][j] = (i == j);
//        }
//    }
//}
//
//// Nhan 2 ma tran a, b; Gan ket qua vao ma tran b
//void matrixMul(Matrix4x4 a, Matrix4x4 b)
//{
//    int i, j;
//    Matrix4x4 tmp;
//    for (i = 0; i < 4; i++)
//    {
//        for (j = 0; j < 4; j++)
//        {
//   tmp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
//        }
//    }
//    for (i = 0; i < 4; i++)
//    {
//        for (j = 0; j < 4; j++)
//        {
//            Matrix[i][j] = tmp[i][j];
//        }
//    }
//}
//
////In ma tran
//void printMatrix(Matrix4x4 b){
//	for (int i=0;i<4;i++){
//		std::cout << std::endl << std::setw(5) << "|" << std::setw(10);
//		for (int j=0;j<4;j++){
//			std::cout << std::setw(10);
//			std::cout << b[i][j];
//			if(j==3) std::cout << std::setw(3)<< "|";
//    	}
//    }
//	std::cout << std::endl << std::endl;
//}
//
////In toa do cac dinh cua khoi lap phuong
//void printPoint(float a[8][3]){
//	
//	for (int i=0;i<8;i++){
//		std::cout << std::fixed;
//		std::cout << std::setprecision(2);
//		std::cout << std::setw(10) << "Dinh " << (i+1) << ": ";
//		std::cout << "(" << std::setw(3);
//		for (int j=0;j<3;j++){
//			std::cout << std::setw(10);
//			std::cout << a[i][j];
//			if(j==2) std::cout << std::setw(3)<< ")" << std::endl;
//			else std::cout << ",";
//    	}
//	}
//	std::cout << std::endl;
//}
//
////Bien doi tinh tien
//void Translate(int tx, int ty, int tz)
//{
//    Matrix4x4 m;
//    matrixSetIdentity(m);
//    m[0][3] = tx;
//    m[1][3] = ty;
//    m[2][3] = tz;
//    matrixMul(m, Matrix);
//    printf("Ma tran tinh tien:");
//    printMatrix(Matrix);
//}
//
////Bien doi ty le
//void Scale(float sx, float sy, float sz)
//{
//    Matrix4x4 m;
//    matrixSetIdentity(m);
//    m[0][0] = sx;
//    m[1][1] = sy;
//    m[2][2] = sz;
//    matrixMul(m, Matrix);
//    printf("Ma tran ty le:");
//    printMatrix(m);
//}
//
////Bien doi quay theo truc X
//void RotateX(float angle)
//{
//    Matrix4x4 m;
//    matrixSetIdentity(m);
//    angle = angle * 22 / 1260;
//    m[1][1] = cos(angle);
//    m[1][2] = -sin(angle);
//    m[2][1] = sin(angle);
//    m[2][2] = cos(angle);
//    matrixMul(m, Matrix);
//    printf("Ma tran quay theo X:");
//    printMatrix(m);
//}
//
////Bien doi quay theo truc Y
//void RotateY(float angle)
//{
//    Matrix4x4 m;
//    matrixSetIdentity(m);
//    angle = angle * 22 / 1260;
//    m[0][0] = cos(angle);
//    m[0][2] = sin(angle);
//    m[2][0] = -sin(angle);
//    m[2][2] = cos(angle);
//    matrixMul(m, Matrix);
//    printf("Ma tran quay theo Y:");
//    printMatrix(m);
//}
//
////Bien doi quay theo truc Z
//void RotateZ(float angle)
//{
//    Matrix4x4 m;
//    matrixSetIdentity(m);
//    angle = angle * 22 / 1260;
//    m[0][0] = cos(angle);
//    m[0][1] = -sin(angle);
//    m[1][0] = sin(angle);
//    m[1][1] = cos(angle);
//    matrixMul(m, Matrix);
//    printf("Ma tran quay theo Z:");
//    printMatrix(m);
//}
//
////Bien doi doi xung
//void Reflect(void)
//{
//    Matrix4x4 m;
//    matrixSetIdentity(m);
//    switch (choiceRef)
//    {
//    case 1:
//        m[2][2] = -1;
//        break;
//    case 2:
//        m[0][0] = -1;
//        break;
//    case 3:
//        m[1][1] = -1;
//        break;
//    }
//    matrixMul(m, Matrix);
//    printf("Ma tran doi xung:");
//    printMatrix(m);
//}
//
////Ve duong thang di qua A(x1,y11,z1) va B(x2,y2,z2)
//void DrawRotLine(void)
//{
//	glBegin(GL_LINES);
//	glColor3f(1.0f, 1.0f, 0.0f);
//	glLineWidth(10.0f);
//    glVertex3s(x1 - x * 500, y11 - y * 500, z1 - z * 500);
//    glVertex3s(x2 + x * 500, y2 + y * 500, z2 + z * 500);
//    glEnd();
//}
//
////Bien doi toa do cac dinh theo yeu cau (tinh tien, ty le, quay, doi xung)
//void TransPoints(void)
//{
//    int i, k;
//    float tmp;
//    for (k = 0; k < 8; k++)
//        for (i = 0; i < 3; i++)
//            pointsFin[k][i] = Matrix[i][0] * points[k][0] + Matrix[i][1] * points[k][1] + Matrix[i][2] * points[k][2] + Matrix[i][3];
//    
//    printf("\tCac dinh sau bien doi: \n");
//    printPoint(pointsFin);
//}
//
////Ve cac truc toa do
//void drawCoordinateAxisZ()
//{
//    glLineWidth(2.0f);
//    glBegin(GL_LINES);
//    glVertex3f(0.0f, 0.0f, 0.0f);
//    glVertex3f(0.0f, 0.0f, 2000.0f);
//    glEnd();
//    glLineWidth(1.0f);
//}
//
//void drawCoordinateAxisX()
//{
//    glPushMatrix();
//    glRotatef(90.0f, 0.0f, 2000.0f, 0.0f);
//    drawCoordinateAxisZ();
//    glPopMatrix();
//}
//
//void drawCoordinateAxisY()
//{
//    glPushMatrix();
//    glRotatef(-90.0f, 2000.0f, 0.0f, 0.0f);
//    drawCoordinateAxisZ();
//    glPopMatrix();
//}
//
//void drawFrame()
//{
//    glLineWidth(2.0f);
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//    glColor3f(0.0f, 0.0f, 0.0f);
//    glPopMatrix();
//    glMatrixMode(GL_MODELVIEW);
//    glLineWidth(1.0f);
//}
//
////Ve cac truc toa do
//void drawCoordinateAxis()
//{
//    glColor3f(0.0f, 0.0f, 1.0f);
//    drawCoordinateAxisZ();
//    glColor3f(0.0f, 1.0f, 0.0f);
//    drawCoordinateAxisY();
//    glColor3f(1.0f, 0.0f, 0.0f);
//    drawCoordinateAxisX();
//}
//
////Ve khoi lap phuong theo toa do cac dinh
//void Draw(float a[8][3])
//{
//    int i;
//    glColor3f(0.7, 0.4, 0.7);
//    glBegin(GL_POLYGON);
//    glVertex3f(a[0][0], a[0][1], a[0][2]);
//    glVertex3f(a[1][0], a[1][1], a[1][2]);
//    glVertex3f(a[2][0], a[2][1], a[2][2]);
//    glVertex3f(a[3][0], a[3][1], a[3][2]);
//    glEnd();
//
//    i = 0;
//    glColor3f(0.8, 0.6, 0.5);
//    glBegin(GL_POLYGON);
//    glVertex3s(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
//    glVertex3s(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
//    glVertex3s(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
//    glVertex3s(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
//    glEnd();
//    glColor3f(0.2, 0.4, 0.7);
//    glBegin(GL_POLYGON);
//    glVertex3f(a[0][0], a[0][1], a[0][2]);
//    glVertex3f(a[3][0], a[3][1], a[3][2]);
//    glVertex3f(a[7][0], a[7][1], a[7][2]);
//    glVertex3f(a[4][0], a[4][1], a[4][2]);
//    glEnd();
//
//    i = 1;
//    glColor3f(0.5, 0.4, 0.3);
//    glBegin(GL_POLYGON);
//    glVertex3s(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
//    glVertex3s(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
//    glVertex3s(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
//    glVertex3s(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
//    glEnd();
//
//    i = 2;
//    glColor3f(0.5, 0.6, 0.2);
//    glBegin(GL_POLYGON);
//    glVertex3s(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
//    glVertex3s(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
//    glVertex3s(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
//    glVertex3s(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
//    glEnd();
// 
//    i = 4;
//    glColor3f(0.7, 0.3, 0.4);
//    glBegin(GL_POLYGON);
//    glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
//    glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
//    glVertex3f(a[2 + i][0], a[2 + i][1], a[2 + i][2]);
//    glVertex3f(a[3 + i][0], a[3 + i][1], a[3 + i][2]);
//    glEnd();
//}
//
////Hien thi
//void display(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    drawFrame();
//    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
//    drawCoordinateAxis();
//    glColor3f(1.0, 0.0, 0.0);
//    Draw(points);
//    matrixSetIdentity(Matrix);
//    
//    switch (choice)
//    {
//    case 1:
//        Translate(TransDistX, TransDistY, TransDistZ);
//        break;
//    case 2:
//        Scale(ScaleX, ScaleY, ScaleZ);
//        Translate(0, 0, 300);
//        break;
//    case 3:
//    	{
//        DrawRotLine();
//        float MOD = sqrt((x2 - x1) * (x2 - x1) + (y2 - y11) * (y2 - y11) + (z2 - z1) * (z2 - z1));
//        x = (x2 - x1) / MOD;
//        y = (y2 - y11) / MOD;
//        z = (z2 - z1) / MOD;
//        Translate(-x1, -y11, -z1);
//        float ThetaDash;
//        ThetaDash = 1260 * atan(y / z) / 22;
//        RotateX(ThetaDash);
//        RotateY(1260 * asin(-x) / 22);
//        RotateZ(Theta);
//        printf("Bien doi nguoc lai:\n");
//        RotateY(1260 * asin(x) / 22);
//        RotateX(-ThetaDash);
//        Translate(x1, y11, z1);
//        break;
//    	}
//    case 4:
//        Reflect();
//        break;
//    }
//    TransPoints();
//    Draw(pointsFin);
//    glFlush();
//}
//
////Khoi tao
//void init(void)
//{
//    glOrtho(-1000.0, 1000.0, -500.0, 500.0, -500.0, 500.0);
//    glEnable(GL_DEPTH_TEST);		//Hien thi theo chieu sau cua vat the
//}
//
//int main(int argc, char **argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(1362, 750);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("HUYNH DINH TUAN");
//    init();
//
//    //Nhap canh
//    float a;
//    printf("Nhap do dai canh (Vi du 120) ");
//    scanf("%f", &a);
//    inputPoint(a/2.0);
//    printf("\tCac dinh ban dau:\n");
//	printPoint(points);
//	
//    printf("Chon phep bien doi:\n1.Tinh tien\n2.Ty le\n3.Quay\n4.Doi xung\n=>");
//    scanf("%d", &choice);
//    switch (choice)
//    {
//    case 1:
//        printf("Nhap gia tri tinh tien theo X, Y, Z (Vi du: 50 0 0)\n=>");
//        scanf("%f%f%f", &TransDistX, &TransDistY, &TransDistZ);
//        break;
//    case 2:
//        printf("Nhap gia tri ty le theo X, Y, Z\n=>");
//        scanf("%f%f%f", &ScaleX,&ScaleY, &ScaleZ);
//        break;
//    case 3:
//        printf("Nhap toa do 2 diem (x1,y1,z1) & (x2,y2,z2)\n =>");
//        printf("Nhap gia tri x1 ,y1, z1:\n");
//        scanf("%f %f %f", &x1, &y11, &z1);
//        printf("   Nhap gia tri x2 ,y2, z2:\n");
//        scanf("%f %f %f", &x2, &y2, &z2);
//        printf("Nhap gia tri goc quay: ");
//        scanf("%f", &Theta);
//        break;
//    case 4:
//        printf("Chon mat phang doi xung:\n1.Oxy\n2.Oyz\n3.Oxz\n=>");
//        scanf("%d", &choiceRef);
//        break;
//    default:
//        printf("Gia tri khong hop le!!!\n");
//        return 0;
//    }
//    glutDisplayFunc(display);
//    glutMainLoop();
//    return 0;
//}//main

