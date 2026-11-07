#ifndef OPERATIONSDEF
#define OPERATIONSDEF
#include "mat4.hpp"
#include "mat3.hpp"
#include "quaternion.hpp"

Vector3 multiply(const Matrix3x3& m,const Vector3& v);

float dot(const Vector3& u, const Vector3& v);

Vector3 cross(const Vector3& u, const Vector3& v);

Matrix3x3 multiply(const Matrix3x3& m,const Matrix3x3& n);

Matrix3x3 inverse(const Matrix3x3& m);

Matrix3x3 transpose(const Matrix3x3& m);

Matrix3x3 multiply(const Matrix3x3& m, const float& scalar);

Vector4 multiply(const Matrix4x4& m,const Vector4& v);

float dot(const Vector4& u, const Vector4& v);

Matrix4x4 multiply(const Matrix4x4& m,const Matrix4x4& n);

Matrix4x4 affineInverse(const Matrix4x4& m);

Matrix4x4 rigidInverse(const Matrix4x4& m);

Matrix4x4 translation(const Vector3& v);

Matrix4x4 scale(const Vector3& v);

Matrix4x4 rotation(EulerAngles e);

Matrix4x4 transpose(const Matrix4x4& m);

Vector3 calculateNormal(const Vector4& v1, const Vector4& v2, const Vector4& v3);

void divideByW(Vector4& v);

Vector4 cross(const Vector4& u, const Vector4& v);

Vector4 normalize(const Vector4& v);

Matrix4x4 multiply(const Matrix4x4&m , const Matrix4x4& n);

#endif
