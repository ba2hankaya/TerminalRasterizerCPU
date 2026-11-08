
#ifndef MAT4OP
#define MAT4OP

#include <cstddef>
#include "mat3.hpp"
class Vector4
{
    public:
    float x;
    float y;
    float z;
    float w;
    Vector4(float x = 0, float y = 0, float z = 0, float w = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Vector4 operator-(const Vector4& other) const
    {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    Vector4 operator+(const Vector4& other) const
    {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }
};

class Matrix4x4 
{   
private:
    float values[16];
public:
    Matrix4x4(){}

    Matrix4x4(const float& a,const float& b,const float& c,const float& d, const float& e, const float& f, const float& g,const float& h, const float& i, const float& j, const float& k, const float& l, const float& m, const float& n, const float& o, const float& p)
    {
        values[0] = a;
        values[1] = b;
        values[2] = c;
        values[3] = d;
        values[4] = e;
        values[5] = f;
        values[6] = g;
        values[7] = h;
        values[8] = i;
        values[9] = j;
        values[10] = k;
        values[11] = l;
        values[12] = m;
        values[13] = n;
        values[14] = o;
        values[15] = p;
    }

    Matrix4x4(const Matrix3x3& m)
    {
        values[0] = m(0,0);
        values[1] = m(0,1);
        values[2] = m(0,2);
        values[3] = 0;
        values[4] = m(1,0);
        values[5] = m(1,1);
        values[6] = m(1,2);
        values[7] = 0;
        values[8] = m(2,0);
        values[9] = m(2,1);
        values[10] = m(2,2);
        values[11] = 0;
        values[12] = 0;
        values[13] = 0;
        values[14] = 0;
        values[15] = 1;
    }

    static Matrix4x4 Identity()
    {
        return Matrix4x4(Matrix3x3::Identity());
    }

    float& operator()(size_t row, size_t col);
    const float& operator()(size_t row, size_t col) const;
};

#endif
