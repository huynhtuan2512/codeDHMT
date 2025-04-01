//#include <stdio.h>
//#include <cstring>
//#include <cmath>
//#include <GL/glut.h>
//
//void init(void) 
//{
//   glClearColor (0.0, 0.0, 0.0, 0.0);
//   glShadeModel (GL_FLAT);
//}
//
//void myDrawModel()
//{
//	glColor3f( 0.0f, 1.0f, 0.0f );
//	glBegin(GL_LINE_LOOP);
//    glVertex3f(-2, 0, 0); //P0
//    glVertex3f(0, 0, 1.5);  //P1
//    glVertex3f(0, 2.5, 0); //P2
//	glEnd();
//}//myDrawModel
//
//void printOPENGL_MATRIX(int model, char str[]) {
//// Get the modelview matrix
//  GLfloat M[16];
//  int row, col, index;
//  /* retrieve the current modelview matrix. this is after you ve applied all of the transforms */
//  
//  if (model == 1)
//  {
//	  glGetFloatv(GL_MODELVIEW_MATRIX, M); // (MODELVIEW= MODEL+ VIEWING)
//	  printf("\n[%s] GL_MODELVIEW_MATRIX\n", str);
//  }
//  if (model == 2)
//  {
//	  glGetFloatv(GL_PROJECTION_MATRIX, M); // (MODELVIEW= MODEL+ VIEWING)
//	  printf("\n[%s] GL_PROJECTION_MATRIX\n", str);
//  }
//
//  for (row = 0; row < 4; row++) {
//    for (col = 0, index = row; col < 4; col++, index+=4) { printf("%3.3f  ", M[index]); }
//    printf("\n");
//  }
//}
//
//void myTranslate(double tx, double ty, double tz)
//{
//}
// 
//void myScale(double sx, double sy, double sz)
//{
//}
// 
//void myRotateX(double angle)
//{
//}
// 
//void myRotateY(double angle)
//{
//}
// 
//void myRotateZ(double angle)
//{
//}
// 
//void myRotate(double angle, double x, double y, double z)
//{
//}
// 
//void myRotateLine(double angle, double xa, double ya, double za, double xb, double yb, double zb)
////Quay quanh 2 ?iem A, B
//{
//}
// 
//void myLookAt(double eyex, double eyey, double eyez, double centerx,
//      double centery, double centerz, double upx, double upy,
//      double upz)
//{
//}
// 
//void myOrtho(double left, double right, double bottom, double top, double zNear, double zFar)
//{
//}
// 
//void myPerspective(double fovy, double aspect, double zNear, double zFar)
//{
//}
// 
//void mySymmetricLine(double xa, double ya, double za, double xb, double yb, double zb)
////Finding a Point Symmetric with Respect to a Line
//{
//}
// 
//void mySymmetricPlan(double ...)
////Finding a Point Symmetric with Respect to a plan
//{
//}
//
//// Xay dung ham myFrustum theo ma tran cua OpenGL
//void myFrustum(double l, double r, double b, double t, double n, double f)
//{
//    double M[4][4];
//    M[0][0] = 2.f*n/(r-l);
//    M[0][1] = M[0][2] = M[0][3] = 0.f;
//
//    M[1][1] = 2.*n/(t-b);
//    M[1][0] = M[1][2] = M[1][3] = 0.f;
//
//    M[2][0] = (r+l)/(r-l);
//    M[2][1] = (t+b)/(t-b);
//    M[2][2] = -(f+n)/(f-n);
//    M[2][3] = -1.f;
//
//    M[3][2] = -2.f*(f*n)/(f-n);
//    M[3][0] = M[3][1] = M[3][3] = 0.f;
//    glMultMatrixd(&M[0][0]);
//    
//}
//
//void display(void)
//{
//   glClear (GL_COLOR_BUFFER_BIT);
//   glColor3f (1.0, 1.0, 1.0);
//   
//   glLoadIdentity ();             /* clear the matrix */   
//   printOPENGL_MATRIX(1, "1. Identity matrix initiation");
//
//   glTranslatef(1.0f, 2.0f, 3.0f);      /* modeling transformation */ 
//   printOPENGL_MATRIX(1, "3. Model matrix");
//
//   gluLookAt(10, 0, 0, 0, 0, 0, 0, 0, 1);
//   printOPENGL_MATRIX(1, "2. Camera matrix");  
//   gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
// 
//   myDrawModel();   
//   glFlush ();
//}
//
//void reshape (int w, int h)
//{
//   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
//   glMatrixMode (GL_PROJECTION);   
//   glLoadIdentity ();
//   
//   myFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
//   //glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
//   printOPENGL_MATRIX(2, "4. Projection matrice");
//      
//   glMatrixMode (GL_MODELVIEW);
//}
//
//
//int main(int argc, char** argv)
//{
//   glutInit(&argc, argv);
//   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
//   glutInitWindowSize (600, 800); 
//   glutInitWindowPosition (100, 100);
//   glutCreateWindow (argv[0]);
//   init ();
//   glutDisplayFunc(display); 
//   glutReshapeFunc(reshape);
//   glutMainLoop();
//   return 0;
//}

