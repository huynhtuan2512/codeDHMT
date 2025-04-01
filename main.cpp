/////////////////////////////////////////////////////////////////////////////////
//// matrix.cpp
//// ==========
//// Example of understanding OpenGL transform matrix(GL_MODELVIEW)
/////////////////////////////////////////////////////////////////////////////////
//
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif
//
//#include <cstdlib>
//#include <iostream>
//#include <sstream>
//#include <iomanip>
//#include "Matrices.h"
//#include "Vectors.h"
//
//using std::stringstream;
//using std::cout;
//using std::endl;
//using std::ends;
//
////==================================================
//
/////////////////////////////////////////////////////////////////////////////////
//// Matrice.cpp
//// ===========
//// NxN Matrix Math classes
////
//// All matrices are row major. (OpenGL uses column-major matrix)
//// | 0 1 |    | 0 1 2 |    |  0  1  2  3 |
//// | 2 3 |    | 3 4 5 |    |  4  5  6  7 |
////            | 6 7 8 |    |  8  9 10 11 |
////                         | 12 13 14 15 |
////
/////////////////////////////////////////////////////////////////////////////////
//
//#include <cmath>
//#include <algorithm>
//#include "Matrices.h"
//
//const float DEG2RAD = 3.141593f / 180;
//
/////////////////////////////////////////////////////////////////////////////////
//// return the determinant of 2x2 matrix
/////////////////////////////////////////////////////////////////////////////////
//float Matrix2::getDeterminant()
//{
//    return m[0] * m[3] - m[1] * m[2];
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// inverse of 2x2 matrix
//// If cannot find inverse, set identity matrix
/////////////////////////////////////////////////////////////////////////////////
//Matrix2& Matrix2::invert()
//{
//    float determinant = m[0] * m[3] - m[1] * m[2];
//    if(fabs(determinant) <= 0.00001f)
//    {
//        return identity();
//    }
//
//    float tmp = m[0];   // copy the first element
//    float invDeterminant = 1.0f / determinant;
//    m[0] =  invDeterminant * m[3];
//    m[1] = -invDeterminant * m[1];
//    m[2] = -invDeterminant * m[2];
//    m[3] =  invDeterminant * tmp;
//
//    return *this;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// return determinant of 3x3 matrix
/////////////////////////////////////////////////////////////////////////////////
//float Matrix3::getDeterminant()
//{
//    return m[0] * (m[4] * m[8] - m[5] * m[7]) -
//           m[1] * (m[3] * m[8] - m[5] * m[6]) +
//           m[2] * (m[3] * m[7] - m[4] * m[6]);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// inverse 3x3 matrix
//// If cannot find inverse, set identity matrix
/////////////////////////////////////////////////////////////////////////////////
//Matrix3& Matrix3::invert()
//{
//    float determinant, invDeterminant;
//    float tmp[9];
//
//    tmp[0] = m[4] * m[8] - m[5] * m[7];
//    tmp[1] = m[2] * m[7] - m[1] * m[8];
//    tmp[2] = m[1] * m[5] - m[2] * m[4];
//    tmp[3] = m[5] * m[6] - m[3] * m[8];
//    tmp[4] = m[0] * m[8] - m[2] * m[6];
//    tmp[5] = m[2] * m[3] - m[0] * m[5];
//    tmp[6] = m[3] * m[7] - m[4] * m[6];
//    tmp[7] = m[1] * m[6] - m[0] * m[7];
//    tmp[8] = m[0] * m[4] - m[1] * m[3];
//
//    // check determinant if it is 0
//    determinant = m[0] * tmp[0] + m[1] * tmp[3] + m[2] * tmp[6];
//    if(fabs(determinant) <= 0.00001f)
//    {
//        return identity(); // cannot inverse, make it idenety matrix
//    }
//
//    // divide by the determinant
//    invDeterminant = 1.0f / determinant;
//    m[0] = invDeterminant * tmp[0];
//    m[1] = invDeterminant * tmp[1];
//    m[2] = invDeterminant * tmp[2];
//    m[3] = invDeterminant * tmp[3];
//    m[4] = invDeterminant * tmp[4];
//    m[5] = invDeterminant * tmp[5];
//    m[6] = invDeterminant * tmp[6];
//    m[7] = invDeterminant * tmp[7];
//    m[8] = invDeterminant * tmp[8];
//
//    return *this;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// transpose 4x4 matrix
/////////////////////////////////////////////////////////////////////////////////
//Matrix4& Matrix4::transpose()
//{
//    std::swap(m[1],  m[4]);
//    std::swap(m[2],  m[8]);
//    std::swap(m[3],  m[12]);
//    std::swap(m[6],  m[9]);
//    std::swap(m[7],  m[13]);
//    std::swap(m[11], m[14]);
//
//    return *this;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// inverse 4x4 matrix
/////////////////////////////////////////////////////////////////////////////////
//Matrix4& Matrix4::invert()
//{
//    // If the 4th row is [0,0,0,1] then it is affine matrix and
//    // it has no projective transformation.
//    if(m[12] == 0 && m[13] == 0 && m[14] == 0 && m[15] == 1) this->invertAffine();
//    else this->invertGeneral();
//    return *this;
//}
//
//
//
/////////////////////////////////////////////////////////////////////////////////
//// compute the inverse of 4x4 Euclidean transformation matrix
////
//// Euclidean transformation is translation, rotation, and reflection.
//// With Euclidean transform, only the position and orientation of the object
//// will be changed. Euclidean transform does not change the shape of an object
//// (no scaling). Length and angle are reserved.
////
//// Use inverseAffine() if the matrix has scale and shear transformation.
////
//// M = [ R | T ]
////     [ --+-- ]    (R denotes 3x3 rotation/reflection matrix)
////     [ 0 | 1 ]    (T denotes 1x3 translation matrix)
////
//// y = M*x  ->  y = R*x + T  ->  x = R^-1*(y - T)  ->  x = R^T*y - R^T*T
//// (R is orthogonal,  R^-1 = R^T)
////
////  [ R | T ]-1    [ R^T | -R^T * T ]    (R denotes 3x3 rotation matrix)
////  [ --+-- ]   =  [ ----+--------- ]    (T denotes 1x3 translation)
////  [ 0 | 1 ]      [  0  |     1    ]    (R^T denotes R-transpose)
/////////////////////////////////////////////////////////////////////////////////
//Matrix4& Matrix4::invertEuclidean()
//{
//    // transpose 3x3 rotation matrix part
//    // | R^T | 0 |
//    // | ----+-- |
//    // |  0  | 1 |
//    float tmp;
//    tmp = m[1];  m[1] = m[4];  m[4] = tmp;
//    tmp = m[2];  m[2] = m[8];  m[8] = tmp;
//    tmp = m[6];  m[6] = m[9];  m[9] = tmp;
//
//    // compute translation part -R^T * T
//    // | 0 | -R^T x |
//    // | --+------- |
//    // | 0 |   0    |
//    float x = m[3];
//    float y = m[7];
//    float z = m[11];
//    m[3]  = -(m[0] * x + m[1] * y + m[2] * z);
//    m[7]  = -(m[4] * x + m[5] * y + m[6] * z);
//    m[11] = -(m[8] * x + m[9] * y + m[10]* z);
//
//    // last row should be unchanged (0,0,0,1)
//
//    return *this;
//}
//
//
//
/////////////////////////////////////////////////////////////////////////////////
//// compute the inverse of a 4x4 affine transformation matrix
////
//// Affine transformations are generalizations of Euclidean transformations.
//// Affine transformation includes translation, rotation, reflection, scaling,
//// and shearing. Length and angle are NOT preserved.
//// M = [ R | T ]
////     [ --+-- ]    (R denotes 3x3 rotation/scale/shear matrix)
////     [ 0 | 1 ]    (T denotes 1x3 translation matrix)
////
//// y = M*x  ->  y = R*x + T  ->  x = R^-1*(y - T)  ->  x = R^-1*y - R^-1*T
////
////  [ R | T ]-1   [ R^-1 | -R^-1 * T ]
////  [ --+-- ]   = [ -----+---------- ]
////  [ 0 | 1 ]     [  0   +     1     ]
/////////////////////////////////////////////////////////////////////////////////
//Matrix4& Matrix4::invertAffine()
//{
//    // R^-1
//    Matrix3 r(m[0],m[1],m[2], m[4],m[5],m[6], m[8],m[9],m[10]);
//    r.invert();
//    m[0] = r[0];  m[1] = r[1];  m[2] = r[2];
//    m[4] = r[3];  m[5] = r[4];  m[6] = r[5];
//    m[8] = r[6];  m[9] = r[7];  m[10]= r[8];
//
//    // -R^-1 * T
//    float x = m[3];
//    float y = m[7];
//    float z = m[11];
//    m[3]  = -(r[0] * x + r[1] * y + r[2] * z);
//    m[7]  = -(r[3] * x + r[4] * y + r[5] * z);
//    m[11] = -(r[6] * x + r[7] * y + r[8] * z);
//
//    // last row should be unchanged (0,0,0,1)
//    //m[12] = m[13] = m[14] = 0.0f;
//    //m[15] = 1.0f;
//
//    return * this;
//}
//
//
//
/////////////////////////////////////////////////////////////////////////////////
//// inverse matrix using matrix partitioning (blockwise inverse)
//// It devides a 4x4 matrix into 4 of 2x2 matrices. It works in case of where
//// det(A) != 0. If not, use the generic inverse method
//// inverse formula.
//// M = [ A | B ]    A, B, C, D are 2x2 matrix blocks
////     [ --+-- ]    det(M) = |A| * |D - ((C * A^-1) * B)|
////     [ C | D ]
////
//// M^-1 = [ A' | B' ]   A' = A^-1 - (A^-1 * B) * C'
////        [ ---+--- ]   B' = (A^-1 * B) * -D'
////        [ C' | D' ]   C' = -D' * (C * A^-1)
////                      D' = (D - ((C * A^-1) * B))^-1
////
//// NOTE: I wrap with () if it it used more than once.
////       The matrix is invertable even if det(A)=0, so must check det(A) before
////       calling this function, and use invertGeneric() instead.
/////////////////////////////////////////////////////////////////////////////////
//Matrix4& Matrix4::invertProjective()
//{
//    // partition
//    Matrix2 a(m[0], m[1], m[4], m[5]);
//    Matrix2 b(m[2], m[3], m[6], m[7]);
//    Matrix2 c(m[8], m[9], m[12], m[13]);
//    Matrix2 d(m[10], m[11], m[14], m[15]);
//
//    // pre-compute repeated parts
//    a.invert();             // A^-1
//    Matrix2 ab = a * b;     // A^-1 * B
//    Matrix2 ca = c * a;     // C * A^-1
//    Matrix2 cab = ca * b;   // C * A^-1 * B
//    Matrix2 dcab = d - cab; // D - C * A^-1 * B
//
//    // check determinant if |D - C * A^-1 * B| = 0
//    //NOTE: this function assumes det(A) is already checked. if |A|=0 then,
//    //      cannot use this function.
//    float determinant = dcab[0] * dcab[3] - dcab[1] * dcab[2];
//    if(fabs(determinant) <= 0.00001f)
//    {
//        return identity();
//    }
//
//    // compute D' and -D'
//    Matrix2 d1 = dcab;      //  (D - C * A^-1 * B)
//    d1.invert();            //  (D - C * A^-1 * B)^-1
//    Matrix2 d2 = -d1;       // -(D - C * A^-1 * B)^-1
//
//    // compute C'
//    Matrix2 c1 = d2 * ca;   // -D' * (C * A^-1)
//
//    // compute B'
//    Matrix2 b1 = ab * d2;   // (A^-1 * B) * -D'
//
//    // compute A'
//    Matrix2 a1 = a - (ab * c1); // A^-1 - (A^-1 * B) * C'
//
//    // assemble inverse matrix
//    m[0] = a1[0];  m[1] = a1[1]; /*|*/ m[2] = b1[0];  m[3] = b1[1];
//    m[4] = a1[2];  m[5] = a1[3]; /*|*/ m[6] = b1[2];  m[7] = b1[3];
//    /*-----------------------------+-----------------------------*/
//    m[8] = c1[0];  m[9] = c1[1]; /*|*/ m[10]= d1[0];  m[11]= d1[1];
//    m[12]= c1[2];  m[13]= c1[3]; /*|*/ m[14]= d1[2];  m[15]= d1[3];
//
//    return *this;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// compute the inverse of a general 4x4 matrix using Cramer's Rule
//// If cannot find inverse, return indentity matrix
//// M^-1 = adj(M) / det(M)
/////////////////////////////////////////////////////////////////////////////////
//Matrix4& Matrix4::invertGeneral()
//{
//    // get cofactors of minor matrices
//    float cofactor0 = getCofactor(m[5],m[6],m[7], m[9],m[10],m[11], m[13],m[14],m[15]);
//    float cofactor1 = getCofactor(m[4],m[6],m[7], m[8],m[10],m[11], m[12],m[14],m[15]);
//    float cofactor2 = getCofactor(m[4],m[5],m[7], m[8],m[9], m[11], m[12],m[13],m[15]);
//    float cofactor3 = getCofactor(m[4],m[5],m[6], m[8],m[9], m[10], m[12],m[13],m[14]);
//
//    // get determinant
//    float determinant = m[0] * cofactor0 - m[1] * cofactor1 + m[2] * cofactor2 - m[3] * cofactor3;
//    if(fabs(determinant) <= 0.00001f)
//    {
//        return identity();
//    }
//
//    // get rest of cofactors for adj(M)
//    float cofactor4 = getCofactor(m[1],m[2],m[3], m[9],m[10],m[11], m[13],m[14],m[15]);
//    float cofactor5 = getCofactor(m[0],m[2],m[3], m[8],m[10],m[11], m[12],m[14],m[15]);
//    float cofactor6 = getCofactor(m[0],m[1],m[3], m[8],m[9], m[11], m[12],m[13],m[15]);
//    float cofactor7 = getCofactor(m[0],m[1],m[2], m[8],m[9], m[10], m[12],m[13],m[14]);
//
//    float cofactor8 = getCofactor(m[1],m[2],m[3], m[5],m[6], m[7],  m[13],m[14],m[15]);
//    float cofactor9 = getCofactor(m[0],m[2],m[3], m[4],m[6], m[7],  m[12],m[14],m[15]);
//    float cofactor10= getCofactor(m[0],m[1],m[3], m[4],m[5], m[7],  m[12],m[13],m[15]);
//    float cofactor11= getCofactor(m[0],m[1],m[2], m[4],m[5], m[6],  m[12],m[13],m[14]);
//
//    float cofactor12= getCofactor(m[1],m[2],m[3], m[5],m[6], m[7],  m[9], m[10],m[11]);
//    float cofactor13= getCofactor(m[0],m[2],m[3], m[4],m[6], m[7],  m[8], m[10],m[11]);
//    float cofactor14= getCofactor(m[0],m[1],m[3], m[4],m[5], m[7],  m[8], m[9], m[11]);
//    float cofactor15= getCofactor(m[0],m[1],m[2], m[4],m[5], m[6],  m[8], m[9], m[10]);
//
//    // build inverse matrix = adj(M) / det(M)
//    // adjugate of M is the transpose of the cofactor matrix of M
//    float invDeterminant = 1.0f / determinant;
//    m[0] =  invDeterminant * cofactor0;
//    m[1] = -invDeterminant * cofactor4;
//    m[2] =  invDeterminant * cofactor8;
//    m[3] = -invDeterminant * cofactor12;
//
//    m[4] = -invDeterminant * cofactor1;
//    m[5] =  invDeterminant * cofactor5;
//    m[6] = -invDeterminant * cofactor9;
//    m[7] =  invDeterminant * cofactor13;
//
//    m[8] =  invDeterminant * cofactor2;
//    m[9] = -invDeterminant * cofactor6;
//    m[10]=  invDeterminant * cofactor10;
//    m[11]= -invDeterminant * cofactor14;
//
//    m[12]= -invDeterminant * cofactor3;
//    m[13]=  invDeterminant * cofactor7;
//    m[14]= -invDeterminant * cofactor11;
//    m[15]=  invDeterminant * cofactor15;
//
//    return *this;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// return determinant of 4x4 matrix
/////////////////////////////////////////////////////////////////////////////////
//float Matrix4::getDeterminant()
//{
//    return m[0] * getCofactor(m[5],m[6],m[7], m[9],m[10],m[11], m[13],m[14],m[15]) -
//           m[1] * getCofactor(m[4],m[6],m[7], m[8],m[10],m[11], m[12],m[14],m[15]) +
//           m[2] * getCofactor(m[4],m[5],m[7], m[8],m[9], m[11], m[12],m[13],m[15]) -
//           m[3] * getCofactor(m[4],m[5],m[6], m[8],m[9], m[10], m[12],m[13],m[14]);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// compute cofactor of 3x3 minor matrix without sign
//// input params are 9 elements of the minor matrix
//// NOTE: The caller must know its sign.
/////////////////////////////////////////////////////////////////////////////////
//float Matrix4::getCofactor(float m0, float m1, float m2,
//                           float m3, float m4, float m5,
//                           float m6, float m7, float m8)
//{
//    return m0 * (m4 * m8 - m5 * m7) -
//           m1 * (m3 * m8 - m5 * m6) +
//           m2 * (m3 * m7 - m4 * m6);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// translate this matrix by (x, y, z)
/////////////////////////////////////////////////////////////////////////////////
//Matrix4& Matrix4::translate(const Vector3& v)
//{
//    return translate(v.x, v.y, v.z);
//}
//
//Matrix4& Matrix4::translate(float x, float y, float z)
//{
//    m[0] += m[12]*x;   m[1] += m[13]*x;   m[2] += m[14]*x;   m[3] += m[15]*x;
//    m[4] += m[12]*y;   m[5] += m[13]*y;   m[6] += m[14]*y;   m[7] += m[15]*y;
//    m[8] += m[12]*z;   m[9] += m[13]*z;   m[10]+= m[14]*z;   m[11]+= m[15]*z;
//    return *this;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// uniform scale
/////////////////////////////////////////////////////////////////////////////////
//Matrix4& Matrix4::scale(float s)
//{
//    return scale(s, s, s);
//}
//
//Matrix4& Matrix4::scale(float x, float y, float z)
//{
//    m[0] = m[0]*x;   m[1] = m[1]*x;   m[2] = m[2]*x;   m[3] = m[3]*x;
//    m[4] = m[4]*y;   m[5] = m[5]*y;   m[6] = m[6]*y;   m[7] = m[7]*y;
//    m[8] = m[8]*z;   m[9] = m[9]*z;   m[10]= m[10]*z;  m[11]= m[11]*z;
//    return *this;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// build a rotation matrix with given angle(degree) and rotation axis, then
//// multiply it with this object
/////////////////////////////////////////////////////////////////////////////////
//Matrix4& Matrix4::rotate(float angle, const Vector3& axis)
//{
//    return rotate(angle, axis.x, axis.y, axis.z);
//}
//
//Matrix4& Matrix4::rotate(float angle, float x, float y, float z)
//{
//    float c = cosf(angle * DEG2RAD);    // cosine
//    float s = sinf(angle * DEG2RAD);    // sine
//    float xx = x * x;
//    float xy = x * y;
//    float xz = x * z;
//    float yy = y * y;
//    float yz = y * z;
//    float zz = z * z;
//
//    // build rotation matrix
//    Matrix4 m;
//    m[0] = xx * (1 - c) + c;
//    m[1] = xy * (1 - c) - z * s;
//    m[2] = xz * (1 - c) + y * s;
//    m[3] = 0;
//    m[4] = xy * (1 - c) + z * s;
//    m[5] = yy * (1 - c) + c;
//    m[6] = yz * (1 - c) - x * s;
//    m[7] = 0;
//    m[8] = xz * (1 - c) - y * s;
//    m[9] = yz * (1 - c) + x * s;
//    m[10]= zz * (1 - c) + c;
//    m[11]= 0;
//    m[12]= 0;
//    m[13]= 0;
//    m[14]= 0;
//    m[15]= 1;
//
//    // multiply it
//    *this = m * (*this);
//
//    return *this;
//}
//
//Matrix4& Matrix4::rotateX(float angle)
//{
//    float c = cosf(angle * DEG2RAD);
//    float s = sinf(angle * DEG2RAD);
//    float m4 = m[4], m5 = m[5], m6 = m[6],  m7 = m[7],
//          m8 = m[8], m9 = m[9], m10= m[10], m11= m[11];
//
//    m[4] = m4 * c + m8 *-s;
//    m[5] = m5 * c + m9 *-s;
//    m[6] = m6 * c + m10*-s;
//    m[7] = m7 * c + m11*-s;
//    m[8] = m4 * s + m8 * c;
//    m[9] = m5 * s + m9 * c;
//    m[10]= m6 * s + m10* c;
//    m[11]= m7 * s + m11* c;
//
//    return *this;
//}
//
//Matrix4& Matrix4::rotateY(float angle)
//{
//    float c = cosf(angle * DEG2RAD);
//    float s = sinf(angle * DEG2RAD);
//    float m0 = m[0], m1 = m[1], m2 = m[2],  m3 = m[3],
//          m8 = m[8], m9 = m[9], m10= m[10], m11= m[11];
//
//    m[0] = m0 * c + m8 * s;
//    m[1] = m1 * c + m9 * s;
//    m[2] = m2 * c + m10* s;
//    m[3] = m3 * c + m11* s;
//    m[8] = m0 *-s + m8 * c;
//    m[9] = m1 *-s + m9 * c;
//    m[10]= m2 *-s + m10* c;
//    m[11]= m3 *-s + m11* c;
//
//    return *this;
//}
//
//Matrix4& Matrix4::rotateZ(float angle)
//{
//    float c = cosf(angle * DEG2RAD);
//    float s = sinf(angle * DEG2RAD);
//    float m0 = m[0], m1 = m[1], m2 = m[2],  m3 = m[3],
//          m4 = m[4], m5 = m[5], m6 = m[6],  m7 = m[7];
//
//    m[0] = m0 * c + m4 *-s;
//    m[1] = m1 * c + m5 *-s;
//    m[2] = m2 * c + m6 *-s;
//    m[3] = m3 * c + m7 *-s;
//    m[4] = m0 * s + m4 * c;
//    m[5] = m1 * s + m5 * c;
//    m[6] = m2 * s + m6 * c;
//    m[7] = m3 * s + m7 * c;
//
//    return *this;
//}
//
//
////===================================================
//
//// GLUT CALLBACK functions
//void displayCB();
//void reshapeCB(int w, int h);
//void timerCB(int millisec);
//void idleCB();
//void keyboardCB(unsigned char key, int x, int y);
//void mouseCB(int button, int stat, int x, int y);
//void mouseMotionCB(int x, int y);
//
//void initGL();
//int  initGLUT(int argc, char **argv);
//bool initSharedMem();
//void clearSharedMem();
//void initLights();
//void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
//void drawString(const char *str, int x, int y, float color[4], void *font);
//void drawString3D(const char *str, float pos[3], float color[4], void *font);
//void showInfo();
//void toOrtho();
//void toPerspective();
//void drawAxis(float size=2.5f);
//void drawModel();
//void anglesToMatrix(const Vector3 angles, Matrix4& matrix);
//Matrix4 setFrustum(float l, float r, float b, float t, float n, float f);
//Matrix4 setFrustum(float fovY, float aspectRatio, float front, float back);
//Matrix4 setOrthoFrustum(float l, float r, float b, float t, float n, float f);
//
//// constants
//const int   SCREEN_WIDTH    = 400;
//const int   SCREEN_HEIGHT   = 300;
//const float CAMERA_DISTANCE = 6.0f;
//const int   TEXT_WIDTH      = 8;
//const int   TEXT_HEIGHT     = 13;
////const float DEG2RAD         = 3.141593f / 180;
//
//// global variables
//void *font = GLUT_BITMAP_8_BY_13;
//int screenWidth;
//int screenHeight;
//bool mouseLeftDown;
//bool mouseRightDown;
//float mouseX, mouseY;
//float cameraAngleX;
//float cameraAngleY;
//float cameraDistance;
//int drawMode = 0;
//Matrix4 matrixView;
//Matrix4 matrixModel;
//Matrix4 matrixModelView;    // = matrixView * matrixModel
//Matrix4 matrixProjection;
//
/////////////////////////////////////////////////////////////////////////////////
//int main(int argc, char **argv)
//{
//
///*
//    // Matrix4 usage examples =================================================
//    // Note that Matrix4 is row-major order
//
//    // create (construct) matrix
//    float a[16] = { 2,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,2 };
//    Matrix4 m1;                                             // with default ctor
//    Matrix4 m2(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);            // with 16 elements
//    Matrix4 m3(a);                                          // with array
//    Matrix4 m4(m3);                                         // with copy ctor, same as Matrix4 m4 = m3;
//    //std::cout << m4 << std::endl;
//
//    // accessors (getter/setter)
//    m1.set(a);                                              // init with array
//    m2.set(3,3,3,3, 3,3,3,3, 3,3,3,3, 3,3,3,3);             // init with 16 elements
//    m3 = m2;                                                // init with assignemt operator (=)
//    const float* a1 = m1.get();                             // return pointer to matrix elements
//    const float* a2 = m2.getTranspose();                    // return transposed matrix elements
//
//    // subscript operator [] to access each element
//    m1[0] = 3;
//    std::cout << "FIRST ELEMENT: " << m1[0] << std::endl;
//    std::cout << " LAST ELEMENT: " << m1[15] << "\n\n";
//
//    // comparison (exact)
//    if(m1 == m2)
//        std::cout << "COMPARISON: EQUAL\n\n";
//    else
//        std::cout << "COMPARISON: NOT EQUAL\n\n";
//
//    // addition
//    m3 = m1 + m2;                                           // M3 = M1 + M2
//    std::cout << "ADD:\n" << m3 << std::endl;
//
//    // subtraction
//    m3 = m1 - m2;                                           // M3 = M1 - M2
//    std::cout << "SUBTRACT:\n" << m3 << std::endl;
//
//    // multiplication
//    m3 = m1 * m2;                                           // M3 = M1 * M2
//    m3 *= m1;                                               // M3 = M3 * M1 (= glMultMatrixf(M1))
//    std::cout << "MULTIPLY:\n" << m3 << std::endl;
//
//    // scalar product (pre-mult only, not available M * s)
//    m3 = 5 * m1;                                            // s * M
//    std::cout << "SCALAR PRODUCT:\n" << m3 << std::endl;
//
//    // vector multiplication
//    Vector3 v1 = Vector3(2,2,2);
//    Vector3 v2;
//    v2 = m1 * v1;                                           // vector product: M * v
//    std::cout << "VECTOR MULTIPLY 1: " << v2 << std::endl;
//    v2 = v1 * m1;                                           // pre-product: v * M
//    std::cout << "VECTOR MULTIPLY 2: " << v2 << "\n\n";
//
//    // transpose
//    m3.set(1,1,1,1, 2,2,2,2, 3,3,3,3, 4,4,4,4);
//    m3.transpose();                                         // transpose
//    std::cout << "TRANSPOSE:\n" << m3 << std::endl;
//
//    // inverse of non-singluar
//    m3.set(1,0,0,0, 0,2,0,0, 0,0,3,0, 0,0,0,4);             // non-singular M
//    m3.invert();                                            // inverse
//    std::cout << "INVERSE:\n" << m3 << std::endl;
//
//    // invert Euclidean (rotation/reflection only)
//    m3.set(-1,0,0,1, 0,0.70711f,-0.70711f,2, 0,0.70711f,0.70711f,3, 0,0,0,1);
//    m3.invertEuclidean();                                   // inverse explicitly
//    std::cout << "INVERSE EUCLIDEAN:\n" << m3 << std::endl;
//
//    // translate transform
//    m3.identity();
//    m3.translate(1, 2, 3);                                  // = glTranslatef(x, y, z)
//    //m3.translate(v1);
//    std::cout << "TRANSLATE:\n" << m3 << std::endl;
//
//    // rotate transform with degree
//    m3.identity();
//    m3.rotate(45, 1,0,0);                                   // = glRotatef(a, 1,0,0)
//    std::cout << "ROTATE:\n" << m3 << std::endl;
//
//    // rotate on basis axis (degree)
//    m3.rotateX(10);                                         // = glRotatef(10, 1,0,0)
//    m3.rotateY(20);                                         // = glRotatef(20, 0,1,0)
//    m3.rotateZ(30);                                         // = glRotatef(30, 0,0,1)
//
//    // scale
//    m3.identity();
//    m3.scale(1, 2, 3);                                      // = glScalef(x, y, z)
//    std::cout << "SCALE:\n" << m3 << std::endl;
//*/
//    //=========================================================================
//
//    // init global vars
//    initSharedMem();
//
//    // init GLUT and GL
//    initGLUT(argc, argv);
//    initGL();
//
//    // the last GLUT call (LOOP)
//    // window will be shown and display callback is triggered by events
//    // NOTE: this call never return main().
//    glutMainLoop(); /* Start GLUT event-processing loop */
//
//    return 0;
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//// draw the local axis of an object
/////////////////////////////////////////////////////////////////////////////////
//void drawAxis(float size)
//{
//    glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
//    glDisable(GL_LIGHTING);
//
//    // draw axis
//    glLineWidth(3);
//    glBegin(GL_LINES);
//        glColor3f(1, 0, 0);
//        glVertex3f(0, 0, 0);
//        glVertex3f(size, 0, 0);
//        glColor3f(0, 1, 0);
//        glVertex3f(0, 0, 0);
//        glVertex3f(0, size, 0);
//        glColor3f(0, 0, 1);
//        glVertex3f(0, 0, 0);
//        glVertex3f(0, 0, size);
//    glEnd();
//    glLineWidth(1);
//
//    // draw arrows(actually big square dots)
//    glPointSize(5);
//    glBegin(GL_POINTS);
//        glColor3f(1, 0, 0);
//        glVertex3f(size, 0, 0);
//        glColor3f(0, 1, 0);
//        glVertex3f(0, size, 0);
//        glColor3f(0, 0, 1);
//        glVertex3f(0, 0, size);
//    glEnd();
//    glPointSize(1);
//
//    // restore default settings
//    glEnable(GL_LIGHTING);
//    glDepthFunc(GL_LEQUAL);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// draw a model (tetrahedron)
/////////////////////////////////////////////////////////////////////////////////
//void drawModel()
//{
//    glColor3f(1, 1, 1);
//    glBegin(GL_TRIANGLES);
//    glNormal3f(0.6667f, 0.6667f, 0.3334f);
//    glVertex3f(1, 0, 0);
//    glVertex3f(0, 1, 0);
//    glVertex3f(0, 0, 2);
///*
//    glNormal3f(-0.6667f, 0.6667f, 0.3334f);
//    glVertex3f(-1, 0, 0);
//    glVertex3f(0, 0, 2);
//    glVertex3f(0, 1, 0);
//
//    glNormal3f(0, 0, -1);
//    glVertex3f(1, 0, 0);
//    glVertex3f(0, 0, 2);
//    glVertex3f(-1, 0, 0);
//
//    glNormal3f(0, -1, 0);
//    glVertex3f(1, 0, 0);
//    glVertex3f(-1, 0, 0);
//    glVertex3f(0, 1, 0);
// */
//    glEnd();
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// initialize GLUT for windowing
/////////////////////////////////////////////////////////////////////////////////
//int initGLUT(int argc, char **argv)
//{
//    // GLUT stuff for windowing
//    // initialization openGL window.
//    // it is called before any other GLUT routine
//    glutInit(&argc, argv);
//
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode
//
//    glutInitWindowSize(screenWidth, screenHeight);  // window size
//
//    glutInitWindowPosition(100, 100);           // window location
//
//    // finally, create a window with openGL context
//    // Window will not displayed until glutMainLoop() is called
//    // it returns a unique ID
//    int handle = glutCreateWindow(argv[0]);     // param is the title of window
//
//    // register GLUT callback functions
//    glutDisplayFunc(displayCB);
//    glutTimerFunc(33, timerCB, 33);             // redraw only every given millisec
//    //glutIdleFunc(idleCB);                       // redraw whenever system is idle
//    glutReshapeFunc(reshapeCB);
//    glutKeyboardFunc(keyboardCB);
//    glutMouseFunc(mouseCB);
//    glutMotionFunc(mouseMotionCB);
//
//    return handle;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// initialize OpenGL
//// disable unused features
/////////////////////////////////////////////////////////////////////////////////
//void initGL()
//{
//    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment
//
//    // enable /disable features
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_CULL_FACE);
//
//    // enable /disable features
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_LINE_SMOOTH);
//
//     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//    glEnable(GL_COLOR_MATERIAL);
//
//    glClearColor(0, 0, 0, 0);                   // background color
//    glClearStencil(0);                          // clear stencil buffer
//    glClearDepth(1.0f);                         // 0 is near, 1 is far
//    glDepthFunc(GL_LEQUAL);
//
//    initLights();
//}
//
//
//
/////////////////////////////////////////////////////////////////////////////////
//// write 2d text using GLUT
//// The projection matrix must be set to orthogonal before call this function.
/////////////////////////////////////////////////////////////////////////////////
//void drawString(const char *str, int x, int y, float color[4], void *font)
//{
//    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
//    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
//    glDisable(GL_TEXTURE_2D);
//
//    glColor4fv(color);          // set text color
//    glRasterPos2i(x, y);        // place text position
//
//    // loop all characters in the string
//    while(*str)
//    {
//        glutBitmapCharacter(font, *str);
//        ++str;
//    }
//
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_LIGHTING);
//    glPopAttrib();
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// draw a string in 3D space
/////////////////////////////////////////////////////////////////////////////////
//void drawString3D(const char *str, float pos[3], float color[4], void *font)
//{
//    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
//    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
//    glDisable(GL_TEXTURE_2D);
//
//    glColor4fv(color);          // set text color
//    glRasterPos3fv(pos);        // place text position
//
//    // loop all characters in the string
//    while(*str)
//    {
//        glutBitmapCharacter(font, *str);
//        ++str;
//    }
//
//    glDisable(GL_TEXTURE_2D);
//    glEnable(GL_LIGHTING);
//    glPopAttrib();
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// initialize global variables
/////////////////////////////////////////////////////////////////////////////////
//bool initSharedMem()
//{
//    screenWidth = SCREEN_WIDTH;
//    screenHeight = SCREEN_HEIGHT;
//
//    mouseLeftDown = mouseRightDown = false;
//    mouseX = mouseY = 0;
//
//    cameraAngleX = cameraAngleY = 0;
//    cameraDistance = CAMERA_DISTANCE;
//
//    drawMode = 0; // 0:fill, 1: wireframe, 2:points
//
//    return true;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// initialize lights
/////////////////////////////////////////////////////////////////////////////////
//void initLights()
//{
//    // set up light colors (ambient, diffuse, specular)
//    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
//    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
//    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
//    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);
//
//    // position the light
//    float lightPos[4] = {0, 0, 20, 1}; // positional light
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//
//    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// set camera position and lookat direction
/////////////////////////////////////////////////////////////////////////////////
//void setCamera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ)
//{
//    Vector3 eye(eyeX, eyeY, eyeZ);
//    Vector3 center(centerX, centerY, centerZ);
//    Vector3 up(0, 1, 0); // assume the camera is always straight up (no roll)
//
//    Vector3 forward = (eye - center).normalize();
//    Vector3 left = up.cross(forward).normalize();
//    up = forward.cross(left); // up vector is unit length here
//
//    // set inverse of rotation matrix: M^-1 = M^T if it is Euclidean transform
//    matrixView.identity();
//    matrixView.setRow(0, left);
//    matrixView.setRow(1, up);
//    matrixView.setRow(2, forward);
//
//    // set translation column
//    // The result is product of rotation(Mr) and translation (Mt): Mv = Mr * Mt
//    Vector3 trans(left.dot(-eye), up.dot(-eye), forward.dot(-eye));
//    matrixView.setColumn(3, trans);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// display info messages
/////////////////////////////////////////////////////////////////////////////////
//void showInfo()
//{
//    // backup current model-view matrix
//    glPushMatrix();                     // save current modelview matrix
//    glLoadIdentity();                   // reset modelview matrix
//
//    // set to 2D orthogonal projection
//    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
//    glPushMatrix();                     // save current projection matrix
//    glLoadIdentity();                   // reset projection matrix
//    gluOrtho2D(0, screenWidth, 0, screenHeight); // set to orthogonal projection
//
//    float color[4] = {1, 1, 1, 1};
//
//    stringstream ss;
//    ss << std::fixed << std::setprecision(3);
//
//    drawString("=== View Matrix ===", 0, screenHeight-TEXT_HEIGHT, color, font);
//    ss << "[" << std::setw(8) << matrixView[0] << std::setw(8) << matrixView[1] << std::setw(8) << matrixView[2] << std::setw(8) << matrixView[3] << "]" << ends;
//    drawString(ss.str().c_str(), 0, screenHeight-(2*TEXT_HEIGHT), color, font);
//    ss.str("");
//    ss << "[" << std::setw(8) << matrixView[4] << std::setw(8) << matrixView[5] << std::setw(8) << matrixView[6] << std::setw(8) << matrixView[7] << "]" << ends;
//    drawString(ss.str().c_str(), 0, screenHeight-(3*TEXT_HEIGHT), color, font);
//    ss.str("");
//    ss << "[" << std::setw(8) << matrixView[8] << std::setw(8) << matrixView[9] << std::setw(8) << matrixView[10]<< std::setw(8) << matrixView[11]<< "]" << ends;
//    drawString(ss.str().c_str(), 0, screenHeight-(4*TEXT_HEIGHT), color, font);
//    ss.str("");
//    ss << "[" << std::setw(8) << matrixView[12]<< std::setw(8) << matrixView[13]<< std::setw(8) << matrixView[14]<< std::setw(8) << matrixView[15]<< "]" << ends;
//    drawString(ss.str().c_str(), 0, screenHeight-(5*TEXT_HEIGHT), color, font);
//    ss.str("");
//
//    drawString("=== Model Matrix ===", 0, 4*TEXT_HEIGHT, color, font);
//    ss << "[" << std::setw(8) << matrixModel[0] << std::setw(8) << matrixModel[1] << std::setw(8) << matrixModel[2] << std::setw(8) << matrixModel[3] << "]" << ends;
//    drawString(ss.str().c_str(), 0, 3*TEXT_HEIGHT, color, font);
//    ss.str("");
//    ss << "[" << std::setw(8) << matrixModel[4] << std::setw(8) << matrixModel[5] << std::setw(8) << matrixModel[6] << std::setw(8) << matrixModel[7] << "]" << ends;
//    drawString(ss.str().c_str(), 0, 2*TEXT_HEIGHT, color, font);
//    ss.str("");
//    ss << "[" << std::setw(8) << matrixModel[8] << std::setw(8) << matrixModel[9] << std::setw(8) << matrixModel[10]<< std::setw(8) << matrixModel[11]<< "]" << ends;
//    drawString(ss.str().c_str(), 0, TEXT_HEIGHT, color, font);
//    ss.str("");
//    ss << "[" << std::setw(8) << matrixModel[12]<< std::setw(8) << matrixModel[13]<< std::setw(8) << matrixModel[14]<< std::setw(8) << matrixModel[15]<< "]" << ends;
//    drawString(ss.str().c_str(), 0, 0, color, font);
//    ss.str("");
//
//    // unset floating format
//    ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
//
//    // restore projection matrix
//    glPopMatrix();                   // restore to previous projection matrix
//
//    // restore modelview matrix
//    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
//    glPopMatrix();                   // restore to previous modelview matrix
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// set projection matrix as orthogonal
/////////////////////////////////////////////////////////////////////////////////
//void toOrtho()
//{
//    // set viewport to be the entire window
//    glViewport(0, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);
//
//    // set orthographic viewing frustum
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
//
//    // switch to modelview matrix in order to set scene
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// set the projection matrix as perspective
/////////////////////////////////////////////////////////////////////////////////
//void toPerspective()
//{
//    // set viewport to be the entire window
//    glViewport(0, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);
//
//    // set perspective viewing frustum
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(60.0f, (float)(screenWidth)/screenHeight, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip
//
//    // switch to modelview matrix in order to set scene
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// convert Euler angles(x,y,z) to matrix4
//// Each column of the rotation matrix represents left, up and forward axis.
//// The order of rotation is Roll->Yaw->Pitch (Rx*Ry*Rz)
//// Rx: rotation about X-axis, pitch
//// Ry: rotation about Y-axis, yaw(heading)
//// Rz: rotation about Z-axis, roll
////    Rx           Ry          Rz
//// |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |
//// |0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|
//// |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|
/////////////////////////////////////////////////////////////////////////////////
//void anglesToMatrix(const Vector3 angles, Matrix4& matrix)
//{
//    const float DEG2RAD = 3.141593f / 180;
//    float sx, sy, sz, cx, cy, cz, theta;
//    Vector3 left, up, forward;
//
//    // rotation angle about X-axis (pitch)
//    theta = angles.x * DEG2RAD;
//    sx = sinf(theta);
//    cx = cosf(theta);
//
//    // rotation angle about Y-axis (yaw)
//    theta = angles.y * DEG2RAD;
//    sy = sinf(theta);
//    cy = cosf(theta);
//
//    // rotation angle about Z-axis (roll)
//    theta = angles.z * DEG2RAD;
//    sz = sinf(theta);
//    cz = cosf(theta);
//
//    // determine left axis
//    left.x = cy*cz;
//    left.y = sx*sy*cz + cx*sz;
//    left.z = -cx*sy*cz + sx*sz;
//
//    // determine up axis
//    up.x = -cy*sz;
//    up.y = -sx*sy*sz + cx*cz;
//    up.z = cx*sy*sz + sx*cz;
//
//    // determine forward axis
//    forward.x = sy;
//    forward.y = -sx*cy;
//    forward.z = cx*cy;
//
//    // write back to matrix
//    matrix.setColumn(0, left);
//    matrix.setColumn(1, up);
//    matrix.setColumn(2, forward);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// set a perspective frustum with 6 params similar to glFrustum()
//// (left, right, bottom, top, near, far)
//// Note: this is for row-major notation. OpenGL needs transpose it
/////////////////////////////////////////////////////////////////////////////////
//Matrix4 setFrustum(float l, float r, float b, float t, float n, float f)
//{
//    Matrix4 mat;
//    mat[0]  =  2 * n / (r - l);
//    mat[2]  =  (r + l) / (r - l);
//    mat[5]  =  2 * n / (t - b);
//    mat[6]  =  (t + b) / (t - b);
//    mat[10] = -(f + n) / (f - n);
//    mat[11] = -(2 * f * n) / (f - n);
//    mat[14] = -1;
//    mat[15] =  0;
//    return mat;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// set a symmetric perspective frustum with 4 params similar to gluPerspective
//// (vertical field of view, aspect ratio, near, far)
/////////////////////////////////////////////////////////////////////////////////
//Matrix4 setFrustum(float fovY, float aspectRatio, float front, float back)
//{
//    float tangent = tanf(fovY/2 * DEG2RAD);   // tangent of half fovY
//    float height = front * tangent;           // half height of near plane
//    float width = height * aspectRatio;       // half width of near plane
//
//    // params: left, right, bottom, top, near, far
//    return setFrustum(-width, width, -height, height, front, back);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// set a orthographic frustum with 6 params similar to glOrtho()
//// (left, right, bottom, top, near, far)
//// Note: this is for row-major notation. OpenGL needs transpose it
/////////////////////////////////////////////////////////////////////////////////
//Matrix4 setOrthoFrustum(float l, float r, float b, float t, float n, float f)
//{
//    Matrix4 mat;
//    mat[0]  =  2 / (r - l);
//    mat[3]  =  -(r + l) / (r - l);
//    mat[5]  =  2 / (t - b);
//    mat[7]  =  -(t + b) / (t - b);
//    mat[10] = -2 / (f - n);
//    mat[11] = -(f + n) / (f - n);
//    return mat;
//}
//
////=============================================================================
//// CALLBACKS
////=============================================================================
//
//void displayCB()
//{
//    // clear buffer
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//    // save the initial ModelView matrix before modifying ModelView matrix
//    glPushMatrix();
//
//    // tramsform camera
//    matrixView.identity();
//    matrixView.rotate(cameraAngleY, 0, 1, 0);
//    matrixView.rotate(cameraAngleX, 1, 0, 0);
//    matrixView.translate(0, 0, -cameraDistance);
//    // The equivalent code for using OpenGL routine is:
//    // glTranslatef(0, 0, -cameraDistance);
//    // glRotatef(cameraAngleX, 1, 0, 0);   // pitch
//    // glRotatef(cameraAngleY, 0, 1, 0);   // heading
//
//    // Copy view matrix to OpenGL
//    glLoadMatrixf(matrixView.getTranspose());
//    // Compute model matrix
//    matrixModel.identity();
//    //matrixModel.rotateZ(45);        // rotate 45 degree on Z-axis
//    matrixModel.rotateY(45);        // rotate 45 degree on Y-axis
//    matrixModel.translate(0, 1, 0); // move 2 unit up
//
//    // Compute modelview matrix
//    matrixModelView = matrixView * matrixModel;
//
//    // Copy modelview matrix to OpenGL
//    glLoadMatrixf(matrixModelView.getTranspose());
//
//    drawAxis();
//    drawModel();
//
//    // Draw info messages
//    showInfo();
//    glPopMatrix();
//    glutSwapBuffers();
//}
//
//
//void reshapeCB(int w, int h)
//{
//    screenWidth = w;
//    screenHeight = h;
//
//    // set viewport to be the entire window
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//
//    // set perspective viewing frustum
//    glMatrixMode(GL_PROJECTION);
//    matrixProjection = setFrustum(45, (float)w/h, 1.0f, 100.0f);
//    glLoadMatrixf(matrixProjection.getTranspose());
//    // The equivalent OpenGL call
//    // gluPerspective(45.0f, (float)(w)/h, 1.0f, 100.0f); // FOV, AspectRatio, NearClip, FarClip
//
//    // DEBUG
//    std::cout << "===== Projection Matrix =====\n";
//    std::cout << matrixProjection << std::endl;
//
//    // switch to modelview matrix in order to set scene
//    glMatrixMode(GL_MODELVIEW);
//}
//
//
//void timerCB(int millisec)
//{
//    glutTimerFunc(millisec, timerCB, millisec);
//    glutPostRedisplay();
//}
//
//
//void idleCB()
//{
//    glutPostRedisplay();
//}
//
//
//void keyboardCB(unsigned char key, int x, int y)
//{
//    switch(key)
//    {
//    case 27: // ESCAPE
//        exit(0);
//        break;
//    case ' ':
//        break;
//    case 'd': // switch rendering modes (fill -> wire -> point)
//    case 'D':
//        drawMode = ++drawMode % 3;
//        if(drawMode == 0)        // fill mode
//        {
//            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//            glEnable(GL_DEPTH_TEST);
//            glEnable(GL_CULL_FACE);
//        }
//        else if(drawMode == 1)  // wireframe mode
//        {
//            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//            glDisable(GL_DEPTH_TEST);
//            glDisable(GL_CULL_FACE);
//        }
//        else                    // point mode
//        {
//            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
//            glDisable(GL_DEPTH_TEST);
//            glDisable(GL_CULL_FACE);
//        }
//        break;
//
//    default:
//        ;
//    }
//}
//
//
//void mouseCB(int button, int state, int x, int y)
//{
//    mouseX = x;
//    mouseY = y;
//
//    if(button == GLUT_LEFT_BUTTON)
//    {
//        if(state == GLUT_DOWN)
//        {
//            mouseLeftDown = true;
//        }
//        else if(state == GLUT_UP) mouseLeftDown = false;
//    }
//
//    else if(button == GLUT_RIGHT_BUTTON)
//    {
//        if(state == GLUT_DOWN)
//        {
//            mouseRightDown = true;
//        }
//        else if(state == GLUT_UP) mouseRightDown = false;
//    }
//}
//
//void mouseMotionCB(int x, int y)
//{
//    if(mouseLeftDown)
//    {
//        cameraAngleY += (x - mouseX);
//        cameraAngleX += (y - mouseY);
//        mouseX = x;
//        mouseY = y;
//    }
//    if(mouseRightDown)
//    {
//        cameraDistance -= (y - mouseY) * 0.2f;
//        mouseY = y;
//    }
//}//end

