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

Matrix3x3 transpose(const Matrix3x3& m)
{
    return Matrix3x3(
        m(0,0), m(0,1), m(0,2),
        m(1,0), m(1,1), m(1,2),
        m(2,0), m(2,1), m(2,2)
    );
}