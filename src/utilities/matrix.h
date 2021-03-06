#ifndef UTILITY_MATRIX
#define UTILITY_MATRIX

#include "stringprint.h"

class Matrix4x4 {
public:
    Matrix4x4() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = (i == j);
    }

    Matrix4x4(float mat[4][4]) {
        memcpy(m, mat, 16 * sizeof(float));
    }

    Matrix4x4(float t00, float t01, float t02, float t03,
              float t10, float t11, float t12, float t13,
              float t20, float t21, float t22, float t23,
              float t30, float t31, float t32, float t33)
    {
        m[0][0] = t00; m[0][1] = t01; m[0][2] = t02; m[0][3] = t03;
        m[1][0] = t10; m[1][1] = t11; m[1][2] = t12; m[1][3] = t13;
        m[2][0] = t20; m[2][1] = t21; m[2][2] = t22; m[2][3] = t23;
        m[3][0] = t30; m[3][1] = t31; m[3][2] = t32; m[3][3] = t33;
    }

    Matrix4x4 transpose() const {
        return Matrix4x4(m[0][0], m[1][0], m[2][0], m[3][0],
                m[0][1], m[1][1], m[2][1], m[3][1],
                m[0][2], m[1][2], m[2][2], m[3][2],
                m[0][3], m[1][3], m[2][3], m[3][3]);
    }

    Matrix4x4 operator * (const Matrix4x4 &mat) const {
        Matrix4x4 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r.m[i][j] = m[i][0] * mat.m[0][j] + m[i][1] * mat.m[1][j] +
                            m[i][2] * mat.m[2][j] + m[i][3] * mat.m[3][j];
        return r;
    }

    bool operator == (const Matrix4x4 &mat) const {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (m[i][j] != mat.m[i][j]) return false;
        return true;
    }

    bool operator != (const Matrix4x4 &mat) const {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (m[i][j] != mat.m[i][j]) return true;
        return false;
    }

    friend ostream & operator << (ostream &os, const Matrix4x4 &m) {
        os << STRING_PRINTF("[ [ %f, %f, %f, %f ] "
                                  "[ %f, %f, %f, %f ] "
                                  "[ %f, %f, %f, %f ] "
                                  "[ %f, %f, %f, %f ] ]",
                                  m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3],
                m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3],
                m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3],
                m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);
        return os;
    }

    void print(FILE *f) const {
        fprintf(f, "[ ");
        for (int i = 0; i < 4; ++i) {
            fprintf(f, "  [ ");
            for (int j = 0; j < 4; ++j) {
                fprintf(f, "%f", m[i][j]);
                if (j != 3) fprintf(f, ", ");
            }
            fprintf(f, " ]\n");
        }
        fprintf(f, " ] ");
    }

    Matrix4x4 inverse() const;

    float m[4][4];
};

#endif // UTILITY_MATRIX
