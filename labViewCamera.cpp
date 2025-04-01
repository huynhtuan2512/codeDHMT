//#include<windows.h>
//#include<cstdio>
//#include<cmath>
//#include<GL/glut.h>
//
//using namespace std;
//
//double camera_angle = 0.0;
//#define PI 3.1415926535897932
//
//void highTriangle()
//{
//	glBegin(GL_LINE_LOOP);
//		glVertex3f(0.0,0.0,0.0);
//		glVertex3f(0.0,1.0,0.0);
//		glVertex3f(1.0,0.0,0.0);
//	glEnd();
//
//	glBegin(GL_LINE_LOOP);
//		glVertex3f(0.0,0.0,0.0);
//		glVertex3f(0.0,1.0,0.0);
//		glVertex3f(0.0,0.0,1.0);
//	glEnd();
//}
//
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	
//	double eyex = 25.0*cos(camera_angle*PI/180.0);
//	double eyez = 25.0*sin(camera_angle*PI/180.0);
//	/*gluLookAt(
//              eyex,25.0,-eyez,  
//			  0.0,0.0,0.0,
//			  0.0,1.0,0.0
//		);
//	*/
//	gluLookAt(
//              25.0,25.0,-25.0,  
//			  0.0,0.0,0.0,
//			  0.0,1.0,0.0
//		);
//	//camera_angle = camera_angle + 1.0; // advance camera by 5 degree;
//	//if(camera_angle > 360.0) camera_angle = 0.0;
//
//	//write display codes
//	glMatrixMode(GL_MODELVIEW);
//	glColor3f(0.3,0.3,0.3);
//#define EXTX 14
//#define EXTZ 14
//	glBegin(GL_LINES);
//		double x  = -(double)EXTX;
//		for(int i = 1; i<=2*EXTX+1; i++)
//		{
//			glVertex3f(x,0.0,-15.0);
//			glVertex3f(x,0.0,15.0);
//			x += 1.0;
//		}
//	glEnd();
//	glBegin(GL_LINES);
//		double z = -(double)EXTZ;
//		for(int i = 1; i<=2*EXTZ+1; i++)
//		{
//			glVertex3f(-15.0,0.0,z);
//			glVertex3f(15.0,0.0,z);
//			z += 1.0;
//		}
//	glEnd();
//	glColor3f(1.0,1.0,1.0); // white
//	glBegin(GL_LINE_LOOP);		
//		glVertex3f(-15.0,0.0,15.0);
//		glVertex3f(15.0,0.0,15.0);
//		glVertex3f(15.0,0.0,-15.0);
//		glVertex3f(-15.0,0.0,-15.0);
//	glEnd();
//
//glColor3f(1.0,1.0,1.0);
//
//	glPushMatrix();
//	glColor3f(1.0,1.0,0.0);
//		glTranslated(5.0,1.0,5.0);
//		glRotatef(camera_angle,1.0,0.0,0.0);
//		glutWireCube(5.0);
//	
//	glPopMatrix();
//
//	glPushMatrix();
//	
//		glColor3f(0.0,1.0,1.0);
//		glTranslated(-8.0,0.0,8.0);
//		glScalef(5.0,5.0,5.0);
//		
//		glRotatef(camera_angle,0.0,0.0,1.0);
//		highTriangle();
//		glPopMatrix();
//
//	glutSwapBuffers();
//}
//
//void spinDisplay(void)
//{
//	camera_angle = camera_angle + 1.0;
//	if(camera_angle > 360.0) camera_angle = camera_angle - 360.0;
//	glutPostRedisplay();
//}
//
//void mouse(int button, int state, int x, int y)
//{
//		switch(button)
//		{
//		case GLUT_LEFT_BUTTON:
//				if(state==GLUT_DOWN) glutIdleFunc(spinDisplay);
//				break;
//		case GLUT_MIDDLE_BUTTON:
//			if(state==GLUT_DOWN) glutIdleFunc(NULL);
//			break;
//		default:
//			break;
//		}
//}//mouse
//
//void init(void)
//{
//	glClearColor(0.0,0.0,0.0,0.0); // black color	
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(70,1,0.1,100.0);
//}//init
//
//int main(int argc, char **argv)
//{
//	glutInit(&argc,argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize (500,500);
//	glutInitWindowPosition (0, 0);
//	glutCreateWindow("Hello 3D");
//	init(); // init display modes
//	glutDisplayFunc(display); // display update
//	glutMouseFunc(mouse);
//	glutMainLoop();
//	return 0;
//}//end

