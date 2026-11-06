#ifndef OPERATIONSDEF
#define OPERATIONSDEF
#include "mat4.hpp"
#include "mat3.hpp"


Vector3 multiply(const Matrix3x3& m,const Vector3& v);

float dot(const Vector3& u, const Vector3& v);

Vector3 cross(const Vector3& u, const Vector3& v);

Matrix3x3 multiply(const Matrix3x3& m,const Matrix3x3& n);

Matrix3x3 inverse(const Matrix3x3& m);

Matrix3x3 transpose(const Matrix3x3& m);

Vector4 multiply(const Matrix4x4& m,const Vector4& v);

float dot(const Vector4& u, const Vector4& v);

Matrix4x4 multiply(const Matrix4x4& m,const Matrix4x4& n);

Matrix4x4 affineInverse(const Matrix4x4& m);

Matrix4x4 inverse(const Matrix4x4& m);

Matrix4x4 rigidInverse(const Matrix4x4& m);

Matrix4x4 translation(const Vector3& v);

Matrix4x4 scale(const Vector3& v);

Matrix4x4 rotation(const float& angleX, const float& angleY, const float& angleZ);

Matrix4x4 transpose(const Matrix4x4& m);

#endif