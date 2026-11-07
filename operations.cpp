#include "operations.hpp" 
#include "mat3.hpp"
#include "mat4.hpp"
#include <cmath>
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

Matrix3x3 multiply(const Matrix3x3& m, const float& scalar)
{
    return Matrix3x3(
        m(0,0) * scalar, m(0,1) * scalar, m(0,2) * scalar,
        m(1,0) * scalar, m(1,1) * scalar, m(1,2) * scalar,
        m(2,0) * scalar, m(2,1) * scalar, m(2,2) * scalar
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

Matrix3x3 transpose(const Matrix3x3& m)
{
    return Matrix3x3(
        m(0,0), m(1,0), m(2,0),
        m(0,1), m(1,1), m(2,1),
        m(0,2), m(1,2), m(2,2)
    );
}

Matrix4x4 transpose(const Matrix4x4& m)
{
    return Matrix4x4(
        m(0,0), m(1,0), m(2,0), m(3,0),
        m(0,1), m(1,1), m(2,1), m(3,1),
        m(0,2), m(1,2), m(2,2), m(3,2),
        m(0,3), m(1,3), m(2,3), m(3,3)
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
    Vector3 translationPart = multiply(multiply(rotationInverse, -1.0f), Vector3(m(0,3), m(1,3), m(2,3)));

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
    Vector3 translationPart = multiply(multiply(affineInverse, -1.0f), Vector3(m(0,3), m(1,3), m(2,3)));

    Matrix4x4 result(affineInverse);
    result(0,3) = translationPart.x;
    result(1,3) = translationPart.y;
    result(2,3) = translationPart.z;

    return result;
}

Vector4 multiply(const Matrix4x4& m, const Vector4& v)
{
    Vector4 result = Vector4(
        m(0,0) * v.x + m(0,1) * v.y + m(0,2) * v.z + m(0,3) * v.w,
        m(1,0) * v.x + m(1,1) * v.y + m(1,2) * v.z + m(1,3) * v.w,
        m(2,0) * v.x + m(2,1) * v.y + m(2,2) * v.z + m(2,3) * v.w,
        m(3,0) * v.x + m(3,1) * v.y + m(3,2) * v.z + m(3,3) * v.w
    );
    return result;
}

Vector4 cross(const Vector4& u, const Vector4& v)
{
    if (u.w != 0 || v.w != 0)
    {
        throw std::invalid_argument("Cross product is only defined for 3D vectors (w must be 0).");
    }
    return Vector4(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x,
       0 
    );
}

Vector4 normalize(const Vector4& v)
{
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length == 0)
    {
        throw std::invalid_argument("Cannot normalize a zero-length vector.");
    }
    return Vector4(v.x / length, v.y / length, v.z / length, 0);
}

void divideByW(Vector4& v)
{
    v.x = v.x / v.w;
    v.y = v.y / v.w;
    v.z = v.z / v.w;
    v.w = v.w / v.w;
}

Matrix4x4 multiply(const Matrix4x4&m , const Matrix4x4& n)
{
    Matrix4x4 r;
    // Row 0
    r(0, 0) = m(0,0)*n(0,0) + m(0,1)*n(1,0) + m(0,2)*n(2,0) + m(0,3)*n(3,0);
    r(0, 1) = m(0,0)*n(0,1) + m(0,1)*n(1,1) + m(0,2)*n(2,1) + m(0,3)*n(3,1);
    r(0, 2) = m(0,0)*n(0,2) + m(0,1)*n(1,2) + m(0,2)*n(2,2) + m(0,3)*n(3,2);
    r(0, 3) = m(0,0)*n(0,3) + m(0,1)*n(1,3) + m(0,2)*n(2,3) + m(0,3)*n(3,3);

    // Row 1
    r(1, 0) = m(1,0)*n(0,0) + m(1,1)*n(1,0) + m(1,2)*n(2,0) + m(1,3)*n(3,0);
    r(1, 1) = m(1,0)*n(0,1) + m(1,1)*n(1,1) + m(1,2)*n(2,1) + m(1,3)*n(3,1);
    r(1, 2) = m(1,0)*n(0,2) + m(1,1)*n(1,2) + m(1,2)*n(2,2) + m(1,3)*n(3,2);
    r(1, 3) = m(1,0)*n(0,3) + m(1,1)*n(1,3) + m(1,2)*n(2,3) + m(1,3)*n(3,3);

    // Row 2
    r(2, 0) = m(2,0)*n(0,0) + m(2,1)*n(1,0) + m(2,2)*n(2,0) + m(2,3)*n(3,0);
    r(2, 1) = m(2,0)*n(0,1) + m(2,1)*n(1,1) + m(2,2)*n(2,1) + m(2,3)*n(3,1);
    r(2, 2) = m(2,0)*n(0,2) + m(2,1)*n(1,2) + m(2,2)*n(2,2) + m(2,3)*n(3,2);
    r(2, 3) = m(2,0)*n(0,3) + m(2,1)*n(1,3) + m(2,2)*n(2,3) + m(2,3)*n(3,3);

    // Row 3
    r(3, 0) = m(3,0)*n(0,0) + m(3,1)*n(1,0) + m(3,2)*n(2,0) + m(3,3)*n(3,0);
    r(3, 1) = m(3,0)*n(0,1) + m(3,1)*n(1,1) + m(3,2)*n(2,1) + m(3,3)*n(3,1);
    r(3, 2) = m(3,0)*n(0,2) + m(3,1)*n(1,2) + m(3,2)*n(2,2) + m(3,3)*n(3,2);
    r(3, 3) = m(3,0)*n(0,3) + m(3,1)*n(1,3) + m(3,2)*n(2,3) + m(3,3)*n(3,3);

    return r;
}

float dot(const Vector4& u, const Vector4& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}
