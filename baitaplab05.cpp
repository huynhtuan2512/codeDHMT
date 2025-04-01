#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// L?p ma tr?n 4x4 cho các phép bi?n d?i d?ng nh?t
class Matrix4x4 {
public:
    float m[4][4];

    Matrix4x4() { identity(); }

    void identity() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = (i == j) ? 1.0f : 0.0f;
    }

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

    void transformPoint(float& x, float& y, float& z, float& w) const {
        float xnew = m[0][0]*x + m[0][1]*y + m[0][2]*z + m[0][3]*w;
        float ynew = m[1][0]*x + m[1][1]*y + m[1][2]*z + m[1][3]*w;
        float znew = m[2][0]*x + m[2][1]*y + m[2][2]*z + m[2][3]*w;
        w = m[3][0]*x + m[3][1]*y + m[3][2]*z + m[3][3]*w;
        
        x = xnew; y = ynew; z = znew;
    }

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

// ==================== 1. WORLD SPACE TRANSFORMATIONS ====================

// a. Phép t?nh ti?n
Matrix4x4 translateMatrix(float dx, float dy, float dz) {
    Matrix4x4 mat;
    mat.m[0][3] = dx;
    mat.m[1][3] = dy;
    mat.m[2][3] = dz;
    return mat;
}

// b. Phép quay quanh các tr?c chính
Matrix4x4 rotateXMatrix(float angle) {
    float rad = angle * M_PI / 180.0f;
    Matrix4x4 mat;
    mat.m[1][1] = cos(rad); mat.m[1][2] = -sin(rad);
    mat.m[2][1] = sin(rad); mat.m[2][2] = cos(rad);
    return mat;
}

Matrix4x4 rotateYMatrix(float angle) {
    float rad = angle * M_PI / 180.0f;
    Matrix4x4 mat;
    mat.m[0][0] = cos(rad);  mat.m[0][2] = sin(rad);
    mat.m[2][0] = -sin(rad); mat.m[2][2] = cos(rad);
    return mat;
}

Matrix4x4 rotateZMatrix(float angle) {
    float rad = angle * M_PI / 180.0f;
    Matrix4x4 mat;
    mat.m[0][0] = cos(rad); mat.m[0][1] = -sin(rad);
    mat.m[1][0] = sin(rad); mat.m[1][1] = cos(rad);
    return mat;
}

// c. Phép quay quanh tr?c PQ b?t k?
Matrix4x4 rotateAroundAxisMatrix(float x1, float y1, float z1, 
                                float x2, float y2, float z2, float angle) {
    // Vector tr?c quay PQ
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
    
    // Ma tr?n quay t?ng quát
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
    
    // K?t h?p v?i phép t?nh ti?n v? g?c t?a d? và ngu?c l?i
    Matrix4x4 trans1 = translateMatrix(-x1, -y1, -z1);
    Matrix4x4 trans2 = translateMatrix(x1, y1, z1);
    
    return trans2 * mat * trans1;
}

// ==================== 2. CAMERA TRANSFORMATION ====================

Matrix4x4 lookAtMatrix(float eyeX, float eyeY, float eyeZ,
                      float centerX, float centerY, float centerZ,
                      float upX, float upY, float upZ) {
    // Vector forward (hu?ng nhìn)
    float fx = centerX - eyeX;
    float fy = centerY - eyeY;
    float fz = centerZ - eyeZ;
    
    // Chu?n hóa vector forward
    float flen = sqrt(fx*fx + fy*fy + fz*fz);
    fx /= flen; fy /= flen; fz /= flen;
    
    // Vector up (hu?ng lên)
    float ux = upX, uy = upY, uz = upZ;
    
    // Vector side (right) = forward x up
    float sx = fy*uz - fz*uy;
    float sy = fz*ux - fx*uz;
    float sz = fx*uy - fy*ux;
    
    // Chu?n hóa vector side
    float slen = sqrt(sx*sx + sy*sy + sz*sz);
    sx /= slen; sy /= slen; sz /= slen;
    
    // Tính l?i up vector chính xác: up = side x forward
    ux = sy*fz - sz*fy;
    uy = sz*fx - sx*fz;
    uz = sx*fy - sy*fx;
    
    // Ma tr?n view
    Matrix4x4 view;
    view.m[0][0] = sx;   view.m[0][1] = sy;   view.m[0][2] = sz;   view.m[0][3] = -(eyeX*sx + eyeY*sy + eyeZ*sz);
    view.m[1][0] = ux;   view.m[1][1] = uy;   view.m[1][2] = uz;   view.m[1][3] = -(eyeX*ux + eyeY*uy + eyeZ*uz);
    view.m[2][0] = -fx;  view.m[2][1] = -fy;  view.m[2][2] = -fz;  view.m[2][3] = (eyeX*fx + eyeY*fy + eyeZ*fz);
    
    return view;
}

// ==================== 3. PROJECTION TRANSFORMATIONS ====================

// a. Phép chi?u song song (orthographic)
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

// b. Phép chi?u xiên (oblique)
Matrix4x4 obliqueProjectionMatrix(float theta, float phi) {
    float cotTheta = 1.0f / tan(theta * M_PI / 180.0f);
    float cotPhi = 1.0f / tan(phi * M_PI / 180.0f);
    
    Matrix4x4 proj;
    proj.m[0][2] = cotTheta;
    proj.m[1][2] = cotPhi;
    return proj;
}

// c. Phép chi?u tr?c giao (orthographic - gi?ng a)
// (S? d?ng l?i hàm orthoProjectionMatrix)

// d. Phép chi?u ph?i c?nh (perspective)
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

// ==================== DEMO CHUONG TRÌNH ====================

void demoWorldTransformations() {
    cout << "=== 1. WORLD SPACE TRANSFORMATIONS ===" << endl;
    
    // Ði?m ban d?u
    float x = 1.0f, y = 2.0f, z = 3.0f, w = 1.0f;
    cout << "Diem ban dau P: (" << x << ", " << y << ", " << z << ", " << w << ")" << endl;
    
    // a. Phép t?nh ti?n
    Matrix4x4 T = translateMatrix(2.0f, 1.0f, -1.0f);
    T.print("Ma tran tinh tien (dx=2, dy=1, dz=-1)");
    T.transformPoint(x, y, z, w);
    cout << "Sau tinh tien Pw: (" << x << ", " << y << ", " << z << ", " << w << ")" << endl;
    
    // b. Phép quay quanh tr?c X 30 d?
    Matrix4x4 Rx = rotateXMatrix(30.0f);
    Rx.print("Ma tran quay 30 do quanh truc X");
    Rx.transformPoint(x, y, z, w);
    cout << "Sau quay X Pw: (" << x << ", " << y << ", " << z << ", " << w << ")" << endl;
    
    // c. Phép quay quanh tr?c PQ (P(1,1,0), Q(2,3,1)) 45 d?
    Matrix4x4 RPQ = rotateAroundAxisMatrix(1.0f, 1.0f, 0.0f, 2.0f, 3.0f, 1.0f, 45.0f);
    RPQ.print("Ma tran quay 45 do quanh truc PQ (P(1,1,0)->Q(2,3,1))");
    RPQ.transformPoint(x, y, z, w);
    cout << "Sau quay PQ Pw: (" << x << ", " << y << ", " << z << ", " << w << ")" << endl;
}

void demoCameraTransformation() {
    cout << "\n=== 2. CAMERA TRANSFORMATION ===" << endl;
    
    // Gi? s? di?m sau các phép bi?n d?i world space
    float xw = 3.5f, yw = 1.8f, zw = 2.2f, w = 1.0f;
    cout << "Diem Pw: (" << xw << ", " << yw << ", " << zw << ", " << w << ")" << endl;
    
    // Camera t?i (5,5,5), nhìn vào (0,0,0), up (0,1,0)
    Matrix4x4 view = lookAtMatrix(5.0f, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    view.print("Ma tran view (eye=(5,5,5), center=(0,0,0), up=(0,1,0))");
    
    view.transformPoint(xw, yw, zw, w);
    cout << "Diem trong camera space Pc: (" << xw << ", " << yw << ", " << zw << ", " << w << ")" << endl;
}

void demoProjectionTransformations() {
    cout << "\n=== 3. PROJECTION TRANSFORMATIONS ===" << endl;
    
    // Gi? s? di?m trong camera space
    float xc = 0.8f, yc = -1.2f, zc = -6.5f, w = 1.0f;
    cout << "Diem Pc: (" << xc << ", " << yc << ", " << zc << ", " << w << ")" << endl;
    
    // a. Phép chi?u song song
    Matrix4x4 ortho = orthoProjectionMatrix(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    ortho.print("Ma tran chieu song song (left=-10,right=10,bottom=-10,top=10,near=0.1,far=100)");
    float x = xc, y = yc, z = zc, wc = w;
    ortho.transformPoint(x, y, z, wc);
    cout << "Sau chieu song song Pclip: (" << x << ", " << y << ", " << z << ", " << wc << ")" << endl;
    
    // d. Phép chi?u ph?i c?nh
    Matrix4x4 persp = perspectiveProjectionMatrix(60.0f, 1.33f, 0.1f, 100.0f);
    persp.print("Ma tran chieu phoi canh (fovy=60,aspect=1.33,near=0.1,far=100)");
    x = xc; y = yc; z = zc; wc = w;
    persp.transformPoint(x, y, z, wc);
    cout << "Sau chieu phoi canh Pclip: (" << x << ", " << y << ", " << z << ", " << wc << ")" << endl;
}

int main() {
    // Demo các phép bi?n d?i
    demoWorldTransformations();
    demoCameraTransformation();
    demoProjectionTransformations();
    
    return 0;
}
