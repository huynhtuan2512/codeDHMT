//#include <GL/glut.h>
//#include <iostream>
//#include <iomanip>
//#include <cmath>
//#include <cstring>
//
//using namespace std;
//
//// Bi?n toàn c?c luu t?a d? di?m
//float xobj = 0.0f, yobj = 0.0f, zobj = 0.0f;
//
//// Ma tr?n 4x4
//class Matrix4x4 {
//public:
//    float m[4][4];
//
//    Matrix4x4() { identity(); }
//
//    void identity() {
//        memset(m, 0, sizeof(m));
//        for (int i = 0; i < 4; i++) m[i][i] = 1.0f;
//    }
//
//    // Nhân ma tr?n
//    Matrix4x4 operator*(const Matrix4x4& mat) const {
//        Matrix4x4 result;
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j < 4; j++) {
//                result.m[i][j] = 0.0f;
//                for (int k = 0; k < 4; k++) {
//                    result.m[i][j] += m[i][k] * mat.m[k][j];
//                }
//            }
//        }
//        return result;
//    }
//
//    // Nhân ma tr?n v?i vector [x,y,z,1]
//    void transformPoint(float& x, float& y, float& z) const {
//        float xnew = m[0][0]*x + m[0][1]*y + m[0][2]*z + m[0][3];
//        float ynew = m[1][0]*x + m[1][1]*y + m[1][2]*z + m[1][3];
//        float znew = m[2][0]*x + m[2][1]*y + m[2][2]*z + m[2][3];
//        x = xnew; y = ynew; z = znew;
//    }
//
//    // In ma tr?n
//    void print(const char* name) const {
//        cout << name << ":" << endl;
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j < 4; j++) {
//                cout << setw(10) << m[i][j];
//            }
//            cout << endl;
//        }
//        cout << endl;
//    }
//};
//
//// T?o ma tr?n t?nh ti?n
//Matrix4x4 translateMatrix(float dx, float dy, float dz) {
//    Matrix4x4 mat;
//    mat.m[0][3] = dx;
//    mat.m[1][3] = dy;
//    mat.m[2][3] = dz;
//    return mat;
//}
//
//// T?o ma tr?n quay quanh tr?c X
//Matrix4x4 rotateXMatrix(float angle) {
//    float rad = angle * M_PI / 180.0f;
//    float c = cos(rad);
//    float s = sin(rad);
//    
//    Matrix4x4 mat;
//    mat.m[1][1] = c; mat.m[1][2] = -s;
//    mat.m[2][1] = s; mat.m[2][2] = c;
//    return mat;
//}
//
//// T?o ma tr?n quay quanh tr?c Y
//Matrix4x4 rotateYMatrix(float angle) {
//    float rad = angle * M_PI / 180.0f;
//    float c = cos(rad);
//    float s = sin(rad);
//    
//    Matrix4x4 mat;
//    mat.m[0][0] = c;  mat.m[0][2] = s;
//    mat.m[2][0] = -s; mat.m[2][2] = c;
//    return mat;
//}
//
//// T?o ma tr?n quay quanh tr?c Z
//Matrix4x4 rotateZMatrix(float angle) {
//    float rad = angle * M_PI / 180.0f;
//    float c = cos(rad);
//    float s = sin(rad);
//    
//    Matrix4x4 mat;
//    mat.m[0][0] = c; mat.m[0][1] = -s;
//    mat.m[1][0] = s; mat.m[1][1] = c;
//    return mat;
//}
//
//// T?o ma tr?n quay quanh tr?c tùy ý PQ
//Matrix4x4 rotateAroundAxisMatrix(float x1, float y1, float z1, 
//                                float x2, float y2, float z2, float angle) {
//    // Vector tr?c quay
//    float vx = x2 - x1;
//    float vy = y2 - y1;
//    float vz = z2 - z1;
//    
//    // Chu?n hóa vector
//    float len = sqrt(vx*vx + vy*vy + vz*vz);
//    vx /= len; vy /= len; vz /= len;
//    
//    float rad = angle * M_PI / 180.0f;
//    float c = cos(rad);
//    float s = sin(rad);
//    float t = 1.0f - c;
//    
//    Matrix4x4 mat;
//    mat.m[0][0] = t*vx*vx + c;
//    mat.m[0][1] = t*vx*vy - s*vz;
//    mat.m[0][2] = t*vx*vz + s*vy;
//    
//    mat.m[1][0] = t*vx*vy + s*vz;
//    mat.m[1][1] = t*vy*vy + c;
//    mat.m[1][2] = t*vy*vz - s*vx;
//    
//    mat.m[2][0] = t*vx*vz - s*vy;
//    mat.m[2][1] = t*vy*vz + s*vx;
//    mat.m[2][2] = t*vz*vz + c;
//    
//    // Thêm ph?n t?nh ti?n
//    Matrix4x4 trans1 = translateMatrix(-x1, -y1, -z1);
//    Matrix4x4 trans2 = translateMatrix(x1, y1, z1);
//    
//    return trans2 * mat * trans1;
//}
//
//// Hi?n th? k?t qu? d? h?a
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
//    
//    // V? các tr?c t?a d?
//    glBegin(GL_LINES);
//    glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(3,0,0); // X
//    glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,3,0); // Y
//    glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,3); // Z
//    glEnd();
//    
//    // V? di?m g?c
//    glPointSize(10);
//    glBegin(GL_POINTS);
//    glColor3f(1,1,0); glVertex3f(xobj, yobj, zobj);
//    glEnd();
//    
//    glutSwapBuffers();
//}
//
//// Nh?p t?a d? di?m
//void inputPoint() {
//    cout << "=== NHAP TOA DO DIEM ===" << endl;
//    cout << "Nhap toa do x: ";
//    cin >> xobj;
//    cout << "Nhap toa do y: ";
//    cin >> yobj;
//    cout << "Nhap toa do z: ";
//    cin >> zobj;
//    cout << "Da nhap diem: (" << xobj << ", " << yobj << ", " << zobj << ")\n";
//}
//
//// Menu ch?n tr?c quay (bao g?m c? PQ)
//void rotateAxisMenu() {
//    int choice;
//    float angle;
//    
//    cout << "\n=== CHON TRUC QUAY ===" << endl;
//    cout << "1. Quay quanh truc OX" << endl;
//    cout << "2. Quay quanh truc OY" << endl;
//    cout << "3. Quay quanh truc OZ" << endl;
//    cout << "4. Quay quanh truc PQ (tuy y)" << endl;
//    cout << "0. Quay lai" << endl;
//    cout << "Lua chon: ";
//    cin >> choice;
//    
//    if (choice >= 1 && choice <= 4) {
//        cout << "Nhap goc quay (do): ";
//        cin >> angle;
//        
//        Matrix4x4 rot;
//        switch(choice) {
//            case 1:
//                rot = rotateXMatrix(angle);
//                rot.print("Ma tran quay quanh truc X");
//                break;
//            case 2:
//                rot = rotateYMatrix(angle);
//                rot.print("Ma tran quay quanh truc Y");
//                break;
//            case 3:
//                rot = rotateZMatrix(angle);
//                rot.print("Ma tran quay quanh truc Z");
//                break;
//            case 4:
//            {
//                float x1, y1, z1, x2, y2, z2;
//                cout << "Nhap toa do diem P (x y z): ";
//                cin >> x1 >> y1 >> z1;
//                cout << "Nhap toa do diem Q (x y z): ";
//                cin >> x2 >> y2 >> z2;
//                rot = rotateAroundAxisMatrix(x1, y1, z1, x2, y2, z2, angle);
//                rot.print("Ma tran quay quanh truc PQ");
//                break;
//            }
//        }
//        rot.transformPoint(xobj, yobj, zobj);
//        cout << "Diem sau quay: (" << xobj << ", " << yobj << ", " << zobj << ")\n";
//    }
//}
//
//// Menu chính sau khi nh?p di?m
//void mainMenuAfterInput() {
//    int choice;
//    
//    do {
//        cout << "\n=== MENU BIEN DOI ===" << endl;
//        cout << "1. Tinh tien" << endl;
//        cout << "2. Quay va quay quanh truc PQ" << endl;
//        cout << "3. Hien thi do hoa" << endl;
//        cout << "0. Thoat" << endl;
//        cout << "Lua chon: ";
//        cin >> choice;
//        
//        switch(choice) {
//            case 1: // T?nh ti?n
//            {
//                float dx, dy, dz;
//                cout << "Nhap vector tinh tien (dx dy dz): ";
//                cin >> dx >> dy >> dz;
//                Matrix4x4 trans = translateMatrix(dx, dy, dz);
//                trans.print("Ma tran tinh tien");
//                trans.transformPoint(xobj, yobj, zobj);
//                cout << "Diem sau tinh tien: (" << xobj << ", " << yobj << ", " << zobj << ")\n";
//                break;
//            }
//                
//            case 2: // Quay
//                rotateAxisMenu();
//                break;
//                
//            case 3: // Hi?n th? d? h?a
//            {
//                int argc = 1;
//                char* argv[1] = {(char*)"Transformations"};
//                glutInit(&argc, argv);
//                glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//                glutInitWindowSize(800, 600);
//                glutCreateWindow("Bien Doi Diem 3D");
//                
//                glEnable(GL_DEPTH_TEST);
//                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//                
//                glutDisplayFunc(display);
//                glutMainLoop();
//                break;
//            }
//                
//            case 0:
//                break;
//                
//            default:
//                cout << "Lua chon khong hop le!\n";
//        }
//    } while (choice != 0);
//}
//
//int main() {
//    // B?t bu?c nh?p di?m tru?c
//    inputPoint();
//    
//    // Sau khi nh?p di?m, hi?n th? menu 3 l?a ch?n
//    mainMenuAfterInput();
//    
//    return 0;
//}

