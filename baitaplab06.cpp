#include <GL/lut.h">
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>

using namespace std;

// L?p ma tr?n 4x4
class Matrix4x4 {
public:
    float m[4][4];

    Matrix4x4() { identity(); }

    void identity() {
        memset(m, 0, sizeof(m));
        for (int i = 0; i < 4; i++) m[i][i] = 1.0f;
    }

    // Nhân ma tr?n
    Matrix4x4 operator*(const Matrix4x4& mat) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = 0.0f;
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }
        return result;
    }

    // Nhân ma tr?n v?i vector [x,y,z,1]
    void transformPoint(float& x, float& y, float& z) const {
        float xnew = m[0][0]*x + m[0][1]*y + m[0][2]*z + m[0][3];
        float ynew = m[1][0]*x + m[1][1]*y + m[1][2]*z + m[1][3];
        float znew = m[2][0]*x + m[2][1]*y + m[2][2]*z + m[2][3];
        float w = m[3][0]*x + m[3][1]*y + m[3][2]*z + m[3][3];
        
        if (w != 1.0f && w != 0.0f) {
            xnew /= w; ynew /= w; znew /= w;
        }
        x = xnew; y = ynew; z = znew;
    }

    // In ma tr?n
    void print(const char* name) const {
        cout << name << ":" << endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << setw(10) << m[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
};

// 1. Các phép bi?n d?i trong world space
Matrix4x4 translateMatrix(float dx, float dy, float dz) {
    Matrix4x4 mat;
    mat.m[0][3] = dx;
    mat.m[1][3] = dy;
    mat.m[2][3] = dz;
    return mat;
}

Matrix4x4 rotateXMatrix(float angle) {
    float rad = angle * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);
    
    Matrix4x4 mat;
    mat.m[1][1] = c; mat.m[1][2] = -s;
    mat.m[2][1] = s; mat.m[2][2] = c;
    return mat;
}

Matrix4x4 rotateYMatrix(float angle) {
    float rad = angle * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);
    
    Matrix4x4 mat;
    mat.m[0][0] = c;  mat.m[0][2] = s;
    mat.m[2][0] = -s; mat.m[2][2] = c;
    return mat;
}

Matrix4x4 rotateZMatrix(float angle) {
    float rad = angle * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);
    
    Matrix4x4 mat;
    mat.m[0][0] = c; mat.m[0][1] = -s;
    mat.m[1][0] = s; mat.m[1][1] = c;
    return mat;
}

Matrix4x4 rotateAroundAxisMatrix(float x1, float y1, float z1, 
                                float x2, float y2, float z2, float angle) {
    // Vector tr?c quay
    float vx = x2 - x1;
    float vy = y2 - y1;
    float vz = z2 - z1;
    
    // Chu?n hóa vector
    float len = sqrt(vx*vx + vy*vy + vz*vz);
    vx /= len; vy /= len; vz /= len;
    
    float rad = angle * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);
    float t = 1.0f - c;
    
    Matrix4x4 mat;
    mat.m[0][0] = t*vx*vx + c;
    mat.m[0][1] = t*vx*vy - s*vz;
    mat.m[0][2] = t*vx*vz + s*vy;
    
    mat.m[1][0] = t*vx*vy + s*vz;
    mat.m[1][1] = t*vy*vy + c;
    mat.m[1][2] = t*vy*vz - s*vx;
    
    mat.m[2][0] = t*vx*vz - s*vy;
    mat.m[2][1] = t*vy*vz + s*vx;
    mat.m[2][2] = t*vz*vz + c;
    
    // Thêm ph?n t?nh ti?n
    Matrix4x4 trans1 = translateMatrix(-x1, -y1, -z1);
    Matrix4x4 trans2 = translateMatrix(x1, y1, z1);
    
    return trans2 * mat * trans1;
}

// 2. Phép bi?n d?i camera
Matrix4x4 lookAtMatrix(float eyeX, float eyeY, float eyeZ,
                      float centerX, float centerY, float centerZ,
                      float upX, float upY, float upZ) {
    // Tính vector forward (f)
    float fx = centerX - eyeX;
    float fy = centerY - eyeY;
    float fz = centerZ - eyeZ;
    
    // Chu?n hóa forward
    float flen = sqrt(fx*fx + fy*fy + fz*fz);
    fx /= flen; fy /= flen; fz /= flen;
    
    // Tính vector up (u)
    float ux = upX, uy = upY, uz = upZ;
    
    // Tính vector side (s) = f x u
    float sx = fy*uz - fz*uy;
    float sy = fz*ux - fx*uz;
    float sz = fx*uy - fy*ux;
    
    // Chu?n hóa side
    float slen = sqrt(sx*sx + sy*sy + sz*sz);
    sx /= slen; sy /= slen; sz /= slen;
    
    // Tính l?i up vector (u' = s x f)
    ux = sy*fz - sz*fy;
    uy = sz*fx - sx*fz;
    uz = sx*fy - sy*fx;
    
    // T?o ma tr?n view
    Matrix4x4 view;
    view.m[0][0] = sx;   view.m[0][1] = sy;   view.m[0][2] = sz;   view.m[0][3] = -eyeX*sx - eyeY*sy - eyeZ*sz;
    view.m[1][0] = ux;   view.m[1][1] = uy;   view.m[1][2] = uz;   view.m[1][3] = -eyeX*ux - eyeY*uy - eyeZ*uz;
    view.m[2][0] = -fx;  view.m[2][1] = -fy;  view.m[2][2] = -fz;  view.m[2][3] = eyeX*fx + eyeY*fy + eyeZ*fz;
    
    return view;
}

// 3. Các phép chi?u
Matrix4x4 orthoProjectionMatrix(float left, float right, float bottom, float top, float near, float far) {
    Matrix4x4 proj;
    proj.m[0][0] = 2.0f / (right - left);
    proj.m[1][1] = 2.0f / (top - bottom);
    proj.m[2][2] = -2.0f / (far - near);
    proj.m[0][3] = -(right + left) / (right - left);
    proj.m[1][3] = -(top + bottom) / (top - bottom);
    proj.m[2][3] = -(far + near) / (far - near);
    return proj;
}

Matrix4x4 obliqueProjectionMatrix(float theta, float phi) {
    float cotTheta = 1.0f / tan(theta * M_PI / 180.0f);
    float cotPhi = 1.0f / tan(phi * M_PI / 180.0f);
    
    Matrix4x4 proj;
    proj.m[0][2] = cotTheta;
    proj.m[1][2] = cotPhi;
    return proj;
}

Matrix4x4 perspectiveProjectionMatrix(float fovy, float aspect, float near, float far) {
    float f = 1.0f / tan(fovy * M_PI / 360.0f);
    
    Matrix4x4 proj;
    proj.m[0][0] = f / aspect;
    proj.m[1][1] = f;
    proj.m[2][2] = (far + near) / (near - far);
    proj.m[2][3] = (2.0f * far * near) / (near - far);
    proj.m[3][2] = -1.0f;
    proj.m[3][3] = 0.0f;
    return proj;
}

// Hi?n th? k?t qu? d? h?a
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
    
    // V? các tr?c t?a d?
    glBegin(GL_LINES);
    glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(3,0,0); // X
    glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,3,0); // Y
    glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,3); // Z
    glEnd();
    
    glutSwapBuffers();
}

// Menu chính
void mainMenu() {
    int choice;
    float x, y, z;
    float x1, y1, z1, x2, y2, z2;
    float angle, theta, phi;
    float fovy, aspect, near, far;
    float left, right, bottom, top;
    
    do {
        cout << "\n=== MENU CHINH ===" << endl;
        cout << "1. Bien doi trong world space" << endl;
        cout << "2. Bien doi sang camera space" << endl;
        cout << "3. Chieu sang projection space" << endl;
        cout << "4. Hien thi do hoa" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon: ";
        cin >> choice;
        
        switch(choice) {
            case 1: // World space transformations
            {
                cout << "\nNhap toa do diem Pw (x y z): ";
                cin >> x >> y >> z;
                
                int subChoice;
                do {
                    cout << "\n=== BIEN DOI WORLD SPACE ===" << endl;
                    cout << "1. Tinh tien" << endl;
                    cout << "2. Quay quanh truc OX" << endl;
                    cout << "3. Quay quanh truc OY" << endl;
                    cout << "4. Quay quanh truc OZ" << endl;
                    cout << "5. Quay quanh truc PQ tuy y" << endl;
                    cout << "0. Quay lai" << endl;
                    cout << "Lua chon: ";
                    cin >> subChoice;
                    
                    switch(subChoice) {
                        case 1:
                        {
                            float dx, dy, dz;
                            cout << "Nhap vector tinh tien (dx dy dz): ";
                            cin >> dx >> dy >> dz;
                            Matrix4x4 trans = translateMatrix(dx, dy, dz);
                            trans.print("Ma tran tinh tien");
                            trans.transformPoint(x, y, z);
                            cout << "Diem sau tinh tien: (" << x << ", " << y << ", " << z << ")\n";
                            break;
                        }
                        case 2:
                        {
                            cout << "Nhap goc quay (do): ";
                            cin >> angle;
                            Matrix4x4 rot = rotateXMatrix(angle);
                            rot.print("Ma tran quay quanh truc X");
                            rot.transformPoint(x, y, z);
                            cout << "Diem sau quay: (" << x << ", " << y << ", " << z << ")\n";
                            break;
                        }
                        case 3:
                        {
                            cout << "Nhap goc quay (do): ";
                            cin >> angle;
                            Matrix4x4 rot = rotateYMatrix(angle);
                            rot.print("Ma tran quay quanh truc Y");
                            rot.transformPoint(x, y, z);
                            cout << "Diem sau quay: (" << x << ", " << y << ", " << z << ")\n";
                            break;
                        }
                        case 4:
                        {
                            cout << "Nhap goc quay (do): ";
                            cin >> angle;
                            Matrix4x4 rot = rotateZMatrix(angle);
                            rot.print("Ma tran quay quanh truc Z");
                            rot.transformPoint(x, y, z);
                            cout << "Diem sau quay: (" << x << ", " << y << ", " << z << ")\n";
                            break;
                        }
                        case 5:
                        {
                            cout << "Nhap toa do diem P (x y z): ";
                            cin >> x1 >> y1 >> z1;
                            cout << "Nhap toa do diem Q (x y z): ";
                            cin >> x2 >> y2 >> z2;
                            cout << "Nhap goc quay (do): ";
                            cin >> angle;
                            Matrix4x4 rot = rotateAroundAxisMatrix(x1, y1, z1, x2, y2, z2, angle);
                            rot.print("Ma tran quay quanh truc PQ");
                            rot.transformPoint(x, y, z);
                            cout << "Diem sau quay: (" << x << ", " << y << ", " << z << ")\n";
                            break;
                        }
                    }
                } while (subChoice != 0);
                break;
            }
                
            case 2: // Camera space transformation
            {
                cout << "\nNhap toa do diem Pw (x y z): ";
                cin >> x >> y >> z;
                
                cout << "Nhap vi tri camera (eyeX eyeY eyeZ): ";
                cin >> x1 >> y1 >> z1;
                cout << "Nhap diem nhin (centerX centerY centerZ): ";
                cin >> x2 >> y2 >> z2;
                
                Matrix4x4 view = lookAtMatrix(x1, y1, z1, x2, y2, z2, 0, 1, 0);
                view.print("Ma tran view (camera)");
                
                float xc = x, yc = y, zc = z;
                view.transformPoint(xc, yc, zc);
                cout << "Diem trong camera space: (" << xc << ", " << yc << ", " << zc << ")\n";
                break;
            }
                
            case 3: // Projection transformations
            {
                cout << "\nNhap toa do diem Pc (x y z): ";
                cin >> x >> y >> z;
                
                int projChoice;
                cout << "\n=== LOAI PHEP CHIEU ===" << endl;
                cout << "1. Chieu song song (orthographic)" << endl;
                cout << "2. Chieu xien (oblique)" << endl;
                cout << "3. Chieu truc giao" << endl;
                cout << "4. Chieu phoi canh (perspective)" << endl;
                cout << "Lua chon: ";
                cin >> projChoice;
                
                Matrix4x4 proj;
                switch(projChoice) {
                    case 1:
                        cout << "Nhap cac tham so (left right bottom top near far): ";
                        cin >> left >> right >> bottom >> top >> near >> far;
                        proj = orthoProjectionMatrix(left, right, bottom, top, near, far);
                        proj.print("Ma tran chieu song song");
                        break;
                    case 2:
                        cout << "Nhap goc theta va phi (do): ";
                        cin >> theta >> phi;
                        proj = obliqueProjectionMatrix(theta, phi);
                        proj.print("Ma tran chieu xien");
                        break;
                    case 3:
                        cout << "Nhap cac tham so (left right bottom top near far): ";
                        cin >> left >> right >> bottom >> top >> near >> far;
                        proj = orthoProjectionMatrix(left, right, bottom, top, near, far);
                        proj.print("Ma tran chieu truc giao");
                        break;
                    case 4:
                        cout << "Nhap fovy, aspect, near, far: ";
                        cin >> fovy >> aspect >> near >> far;
                        proj = perspectiveProjectionMatrix(fovy, aspect, near, far);
                        proj.print("Ma tran chieu phoi canh");
                        break;
                    default:
                        cout << "Lua chon khong hop le!\n";
                        continue;
                }
                
                float xp = x, yp = y, zp = z;
                proj.transformPoint(xp, yp, zp);
                cout << "Diem trong projection space: (" << xp << ", " << yp << ", " << zp << ")\n";
                break;
            }
                
            case 4: // Hi?n th? d? h?a
            {
                int argc = 1;
                char* argv[1] = {(char*)"Transformations"};
                glutInit(&argc, argv);
                glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
                glutInitWindowSize(800, 600);
                glutCreateWindow("Bien Doi 3D");
                
                glEnable(GL_DEPTH_TEST);
                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                
                glutDisplayFunc(display);
                glutMainLoop();
                break;
            }
                
            case 0:
                break;
                
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

int main() {
    mainMenu();
    return 0;
}
