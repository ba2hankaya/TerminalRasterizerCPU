
#include "quaternion.hpp"
#include <cmath>

Matrix4x4 quaternionToMatrix(const Quaternion& q)
{
    float xx = q.x * q.x;
    float yy = q.y * q.y;
    float zz = q.z * q.z;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float yz = q.y * q.z;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    float wz = q.w * q.z;

    return Matrix4x4(
        1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
        2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx), 0.0f,
        2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Quaternion matrixToQuaternion(const Matrix4x4& m)
{
    float trace = m(0,0) + m(1,1) + m(2,2);
    float w, x, y, z;

    if(trace > 0)
    {
        float s = 0.5f / sqrt(trace + 1.0f);
        w = 0.25f / s;
        x = (m(2,1) - m(1,2)) * s;
        y = (m(0,2) - m(2,0)) * s;
        z = (m(1,0) - m(0,1)) * s;
    }
    else
    {
        if(m(0,0) > m(1,1) && m(0,0) > m(2,2))
        {
            float s = 2.0f * sqrt(1.0f + m(0,0) - m(1,1) - m(2,2));
            w = (m(2,1) - m(1,2)) / s;
            x = 0.25f * s;
            y = (m(0,1) + m(1,0)) / s;
            z = (m(0,2) + m(2,0)) / s;
        }
        else if(m(1,1) > m(2,2))
        {
            float s = 2.0f * sqrt(1.0f + m(1,1) - m(0,0) - m(2,2));
            w = (m(0,2) - m(2,0)) / s;
            x = (m(0,1) + m(1,0)) / s;
            y = 0.25f * s;
            z = (m(1,2) + m(2,1)) / s;
        }
        else
        {
            float s = 2.0f * sqrt(1.0f + m(2,2) - m(0,0) - m(1,1));
            w = (m(1,0) - m(0,1)) / s;
            x = (m(0,2) + m(2,0)) / s;
            y = (m(1,2) + m(2,1)) / s;
            z = 0.25f * s;
        }
    }
    return Quaternion(w, x, y, z);
}

Quaternion eulerToQuaternion(const EulerAngles& e)
{
    float cy = cos(e.yaw * 0.5f);
    float sy = sin(e.yaw * 0.5f);
    float cp = cos(e.pitch * 0.5f);
    float sp = sin(e.pitch * 0.5f);
    float cr = cos(e.roll * 0.5f);
    float sr = sin(e.roll * 0.5f);

    Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}

EulerAngles quaternionToEuler(const Quaternion& q)
{
    EulerAngles e;

    float sinr_cosp = 2.0f * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
    e.roll = atan2(sinr_cosp, cosr_cosp);

    float sinp = 2.0f * (q.w * q.y - q.z * q.x);
    if (fabs(sinp) >= 1)
        e.pitch = copysign(M_PI / 2, sinp); 
    else
        e.pitch = asin(sinp);

    float siny_cosp = 2.0f * (q.w * q.z + q.x * q.y);
    float cosy_cosp = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    e.yaw = atan2(siny_cosp, cosy_cosp);

    return e;
}