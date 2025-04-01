//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <GL/glut.h>
//
//using namespace std;
//
//struct Vertex {
//    float x, y, z;
//};
//
//vector<Vertex> vertices;
//
//void readInputFile(const char* filename) {
//    ifstream file(filename);
//    if (!file) {
//        cerr << "Không th? m? file!" << endl;
//        exit(1);
//    }
//    Vertex v;
//    while (file >> v.x >> v.y >> v.z) {
//        vertices.push_back(v);
//    }
//    file.close();
//}
//
//void printMatrix(const GLfloat matrix[16]) {
//    cout << "Ma tr?n bi?n d?i h? quan sát:" << endl;
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            cout << matrix[i * 4 + j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//}
//
//void drawObject() {
//    glColor3f(1.0, 1.0, 1.0);
//    glBegin(GL_QUADS);
//    for (size_t i = 0; i < vertices.size(); i++) {
//        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
//    }
//    glEnd();
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    GLfloat matrix[16];
//    
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(60.0, 1.0, 1.0, 10.0);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(2.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    
//    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
//    printMatrix(matrix);
//    drawObject();
//    glutSwapBuffers();
//}
//
//void init() {
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//}
//
//int main(int argc, char** argv) {
//    readInputFile("input.txt");
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(600, 600);
//    glutCreateWindow("Perspective Projection");
//    init();
//    glutDisplayFunc(display);
//    glutMainLoop();
//    return 0;
//}

