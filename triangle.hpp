#ifndef TRIANGLEDEF
#define TRIANGLEDEF

#include "mat4.hpp"

class Triangle
{
    private:
    Vector4 v1;
    Vector4 v2;
    Vector4 v3;
    public:
    Triangle(Vector4 v1, Vector4 v2, Vector4 v3)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }
    Vector4 x() const
    {
        return v1;
    }
    Vector4 y() const
    {
        return v2;
    }
    Vector4 z() const
    {
        return v3;
    }
};


#endif
