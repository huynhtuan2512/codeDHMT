#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Mã sinh viên: 123456789 -> x=1, y=2, z=3
float xobj = 1.0f, yobj = 2.0f, zobj = 3.0f;

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

// 1. World space transformations
Matrix4x4 translateMatrix(float dx, float dy, float dz) {
    Matrix4x4 mat;
    mat.m[0][3] = dx;
    mat.m[1][3] = dy;
    mat.m[2][3] = dz;
    return mat;
}

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

Matrix4x4 rotateAroundAxisMatrix(float x1, float y1, float z1, 
                                float x2, float y2, float z2, float angle) {
    float vx = x2 - x1;
    float vy = y2 - y1;
    float vz = z2 - z1;
    
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
    
    Matrix4x4 trans1 = translateMatrix(-x1, -y1, -z1);
    Matrix4x4 trans2 = translateMatrix(x1, y1, z1);
    
    return trans2 * mat * trans1;
}

// 2. Camera transformation
Matrix4x4 lookAtMatrix(float eyeX, float eyeY, float eyeZ,
                      float centerX, float centerY, float centerZ,
                      float upX, float upY, float upZ) {
    float fx = centerX - eyeX;
    float fy = centerY - eyeY;
    float fz = centerZ - eyeZ;
    
    float flen = sqrt(fx*fx + fy*fy + fz*fz);
    fx /= flen; fy /= flen; fz /= flen;
    
    float ux = upX, uy = upY, uz = upZ;
    
    float sx = fy*uz - fz*uy;
    float sy = fz*ux - fx*uz;
    float sz = fx*uy - fy*ux;
    
    float slen = sqrt(sx*sx + sy*sy + sz*sz);
    sx /= slen; sy /= slen; sz /= slen;
    
    ux = sy*fz - sz*fy;
    uy = sz*fx - sx*fz;
    uz = sx*fy - sy*fx;
    
    Matrix4x4 view;
    view.m[0][0] = sx;   view.m[0][1] = sy;   view.m[0][2] = sz;   view.m[0][3] = -eyeX*sx - eyeY*sy - eyeZ*sz;
    view.m[1][0] = ux;   view.m[1][1] = uy;   view.m[1][2] = uz;   view.m[1][3] = -eyeX*ux - eyeY*uy - eyeZ*uz;
    view.m[2][0] = -fx;  view.m[2][1] = -fy;  view.m[2][2] = -fz;  view.m[2][3] = eyeX*fx + eyeY*fy + eyeZ*fz;
    
    return view;
}

// 3. Projection transformations
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
    
    glBegin(GL_LINES);
    glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(3,0,0);
    glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,3,0);
    glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,3);
    glEnd();
    
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1,1,0); glVertex3f(xobj, yobj, zobj);
    glEnd();
    
    glutSwapBuffers();
}

void worldTransformations() {
    cout << "\n=== BIEN DOI WORLD SPACE ===" << endl;
    cout << "Diem ban dau Pobj: (" << xobj << ", " << yobj << ", " << zobj << ")\n";
    
    // T?nh ti?n
    Matrix4x4 T = translateMatrix(2, 1, 3);
    T.print("Ma tran tinh tien (dx=2, dy=1, dz=3)");
    float xw = xobj, yw = yobj, zw = zobj;
    T.transformPoint(xw, yw, zw);
    cout << "Diem sau tinh tien Pw: (" << xw << ", " << yw << ", " << zw << ")\n";
    
    // Quay quanh tr?c X 30 d?
    Matrix4x4 Rx = rotateXMatrix(30);
    Rx.print("Ma tran quay 30 do quanh truc X");
    Rx.transformPoint(xw, yw, zw);
    cout << "Diem sau quay X Pw: (" << xw << ", " << yw << ", " << zw << ")\n";
    
    // Quay quanh tr?c PQ v?i P(1,1,1), Q(2,3,4), góc 45 d?
    Matrix4x4 RPQ = rotateAroundAxisMatrix(1,1,1, 2,3,4, 45);
    RPQ.print("Ma tran quay 45 do quanh truc PQ (P(1,1,1), Q(2,3,4))");
    RPQ.transformPoint(xw, yw, zw);
    cout << "Diem sau quay PQ Pw: (" << xw << ", " << yw << ", " << zw << ")\n";
}

void cameraTransformation() {
    cout << "\n=== BIEN DOI CAMERA SPACE ===" << endl;
    float xw = xobj, yw = yobj, zw = zobj;
    translateMatrix(2,1,3).transformPoint(xw,yw,zw);
    rotateXMatrix(30).transformPoint(xw,yw,zw);
    
    cout << "Diem Pw: (" << xw << ", " << yw << ", " << zw << ")\n";
    
    Matrix4x4 view = lookAtMatrix(5,5,5, 0,0,0, 0,1,0);
    view.print("Ma tran view (eye=(5,5,5), center=(0,0,0), up=(0,1,0))");
    
    float xcam = xw, ycam = yw, zcam = zw;
    view.transformPoint(xcam, ycam, zcam);
    cout << "Diem trong camera space Pcam: (" << xcam << ", " << ycam << ", " << zcam << ")\n";
}

void projectionTransformations() {
    cout << "\n=== BIEN DOI PROJECTION SPACE ===" << endl;
    float xcam = 0, ycam = 0, zcam = -8.66025f; // Giá tr? t? bu?c tru?c
    
    // Phép chi?u song song
    Matrix4x4 ortho = orthoProjectionMatrix(-10,10,-10,10,0.1f,100);
    ortho.print("Ma tran chieu song song (left=-10,right=10,bottom=-10,top=10,near=0.1,far=100)");
    float xclip = xcam, yclip = ycam, zclip = zcam;
    ortho.transformPoint(xclip, yclip, zclip);
    cout << "Diem trong clip space (ortho): (" << xclip << ", " << yclip << ", " << zclip << ")\n";
    
    // Phép chi?u ph?i c?nh
    Matrix4x4 persp = perspectiveProjectionMatrix(60, 1.0f, 0.1f, 100);
    persp.print("Ma tran chieu phoi canh (fovy=60,aspect=1,near=0.1,far=100)");
    xclip = xcam; yclip = ycam; zclip = zcam;
    persp.transformPoint(xclip, yclip, zclip);
    cout << "Diem trong clip space (persp): (" << xclip << ", " << yclip << ", " << zclip << ")\n";
}

int main(int argc, char** argv) {
    // 1. World space transformations
    worldTransformations();
    
    // 2. Camera transformation
    cameraTransformation();
    
    // 3. Projection transformations
    projectionTransformations();
    
    // Hi?n th? d? h?a
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Transformations");
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
