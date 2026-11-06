#ifndef QUATERNIONDEF
#define QUATERNIONDEF
#include "mat4.hpp"

class EulerAngles
{
    public:
    float pitch;
    float yaw;
    float roll;
    EulerAngles(float pitch = 0, float yaw = 0, float roll = 0)
    {
        this->pitch = pitch;
        this->yaw = yaw;
        this->roll = roll;
    }
};

class Quaternion
{
    public:
    float w;
    float x;
    float y;
    float z;
    Quaternion(float w = 1, float x = 0, float y = 0, float z = 0)
    {
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

Quaternion eulerToQuaternion(const EulerAngles& e);

EulerAngles quaternionToEuler(const Quaternion& q);

Matrix4x4 quaternionToMatrix(const Quaternion& q);

Quaternion matrixToQuaternion(const Matrix4x4& m);

#endif