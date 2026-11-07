#ifndef MAT3OP
#define MAT3OP

#include <cstddef>

class Vector3
{
    public:
    float x;
    float y;
    float z;
    Vector3(float x = 0, float y = 0, float z = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

class Matrix3x3 
{   
private:
    float values[9];
public:
    Matrix3x3(){}

    Matrix3x3(const float& a,const float& b,const float& c,const float& d, const float& e, const float& f, const float& g,const float& h, const float& i)
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
    }

    static Matrix3x3 Identity()
    {
        return Matrix3x3(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        );
    }

    float& operator()(size_t row, size_t col);
    const float& operator()(size_t row, size_t col) const;
};

#endif
