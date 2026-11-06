
#ifndef MAT4OP
#define MAT4OP

#include <cstddef>

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

    float& operator()(size_t row, size_t col);
    const float& operator()(size_t row, size_t col) const;
};

#endif