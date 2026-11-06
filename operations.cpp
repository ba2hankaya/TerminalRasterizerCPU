#include "operations.hpp" 
#include "mat3.hpp"
#include <stdexcept>

float dot(const Vector3& u, const Vector3& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector3 cross(const Vector3& u, const Vector3& v)
{
    return Vector3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

Matrix3x3 multiply(const Matrix3x3& m,const Matrix3x3& n)
{
    return Matrix3x3(
        m(0,0) * n(0,0) + m(0,1) * n(1,0) + m(0,2) * n(2,0),
        m(0,0) * n(0,1) + m(0,1) * n(1,1) + m(0,2) * n(2,1),
        m(0,0) * n(0,2) + m(0,1) * n(1,2) + m(0,2) * n(2,2),
        m(1,0) * n(0,0) + m(1,1) * n(1,0) + m(1,2) * n(2,0),
        m(1,0) * n(0,1) + m(1,1) * n(1,1) + m(1,2) * n(2,1),
        m(1,0) * n(0,2) + m(1,1) * n(1,2) + m(1,2) * n(2,2),
        m(2,0) * n(0,0) + m(2,1) * n(1,0) + m(2,2) * n(2,0),
        m(2,0) * n(0,1) + m(2,1) * n(1,1) + m(2,2) * n(2,1),
        m(2,0) * n(0,2) + m(2,1) * n(1,2) + m(2,2) * n(2,2)
    );
}

Vector3 multiply(const Matrix3x3& m,const Vector3& v)
{
    return Vector3(
        m(0,0) * v.x + m(0,1) * v.y + m(0,2) * v.z,
        m(1,0) * v.x + m(1,1) * v.y + m(1,2) * v.z,
        m(2,0) * v.x + m(2,1) * v.y + m(2,2) * v.z
    );
}

float determinant(const Matrix3x3& m)
{
    return m(0,0) * (m(1,1) * m(2,2) - m(1,2) * m(2,1)) -
           m(0,1) * (m(1,0) * m(2,2) - m(1,2) * m(2,0)) +
           m(0,2) * (m(1,0) * m(2,1) - m(1,1) * m(2,0));
}

Matrix3x3 inverse(const Matrix3x3& m)
{
    float det = determinant(m);
    if(det == 0)
    {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }

    float invDet = 1.0f / det;

    return Matrix3x3(
        (m(1,1) * m(2,2) - m(1,2) * m(2,1)) * invDet,
        (m(0,2) * m(2,1) - m(0,1) * m(2,2)) * invDet,
        (m(0,1) * m(1,2) - m(0,2) * m(1,1)) * invDet,
        (m(1,2) * m(2,0) - m(1,0) * m(2,2)) * invDet,
        (m(0,0) * m(2,2) - m(0,2) * m(2,0)) * invDet,
        (m(0,2) * m(1,0) - m(0,0) * m(1,2)) * invDet,
        (m(1,0) * m(2,1) - m(1,1) * m(2,0)) * invDet,
        (m(0,1) * m(2,0) - m(0,0) * m(2,1)) * invDet,
        (m(0,0) * m(1,1) - m(0,1) * m(1,0)) * invDet
    );
}

Matrix3x3 scalarMultiply(const Matrix3x3& m, const float& scalar)
{
    return Matrix3x3(
        m(0,0) * scalar, m(0,1) * scalar, m(0,2) * scalar,
        m(1,0) * scalar, m(1,1) * scalar, m(1,2) * scalar,
        m(2,0) * scalar, m(2,1) * scalar, m(2,2) * scalar
    );
}

Matrix3x3 transpose(const Matrix3x3& m)
{
    return Matrix3x3(
        m(0,0), m(0,1), m(0,2),
        m(1,0), m(1,1), m(1,2),
        m(2,0), m(2,1), m(2,2)
    );
}

Matrix4x4 transpose(const Matrix4x4& m)
{
    return Matrix4x4(
        m(0,0), m(0,1), m(0,2), m(0,3),
        m(1,0), m(1,1), m(1,2), m(1,3),
        m(2,0), m(2,1), m(2,2), m(2,3),
        m(3,0), m(3,1), m(3,2), m(3,3)
    );
}

Matrix4x4 translation(const Vector3& v)
{
    return Matrix4x4(
        1, 0, 0, v.x,
        0, 1, 0, v.y,
        0, 0, 1, v.z,
        0, 0, 0, 1
    );
}

Matrix4x4 scale(const Vector3& v)
{
    return Matrix4x4(
        v.x, 0, 0, 0,
        0, v.y, 0, 0,
        0, 0, v.z, 0,
        0, 0, 0, 1
    );
}

Matrix4x4 rotation(EulerAngles e)
{
    Quaternion q = eulerToQuaternion(e);
    return quaternionToMatrix(q);
}

Matrix4x4 rigidInverse(const Matrix4x4& m)
{
    Matrix3x3 rotationPart(
        m(0,0), m(0,1), m(0,2), 
        m(1,0), m(1,1), m(1,2), 
        m(2,0), m(2,1), m(2,2)
    );

    Matrix3x3 rotationInverse = transpose(rotationPart); 
    Vector3 translationPart = multiply(scalarMultiply(rotationInverse, -1.0f), Vector3(m(0,3), m(1,3), m(2,3)));

    Matrix4x4 result(rotationInverse);
    result(0,3) = translationPart.x;
    result(1,3) = translationPart.y;
    result(2,3) = translationPart.z;

    return result;
}

Matrix4x4 affineInverse(const Matrix4x4& m)
{
    Matrix3x3 affinePart(
        m(0,0), m(0,1), m(0,2), 
        m(1,0), m(1,1), m(1,2), 
        m(2,0), m(2,1), m(2,2)
    );

    Matrix3x3 affineInverse = inverse(affinePart); 
    Vector3 translationPart = multiply(scalarMultiply(affineInverse, -1.0f), Vector3(m(0,3), m(1,3), m(2,3)));

    Matrix4x4 result(affineInverse);
    result(0,3) = translationPart.x;
    result(1,3) = translationPart.y;
    result(2,3) = translationPart.z;

    return result;
}