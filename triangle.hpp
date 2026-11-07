#ifndef TRIANGLEDEF
#define TRIANGLEDEF

#include "mat4.hpp"

class Triangle
{
    private:
    Vector4 v1;
    Vector4 v2;
    Vector4 v3;
    Vector4 color1;
    Vector4 color2;
    Vector4 color3;
    Vector4 normal;
    public:
    Triangle(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 color1, Vector4 color2, Vector4 color3)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        this->color1 = color1;
        this->color2 = color2;
        this->color3 = color3;
    }
    Vector4 getNormal()
    {
        return normal;
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
    Vector4 getColor1() const
    {
        return color1;
    }
    Vector4 getColor2() const
    {
        return color2;
    }
    Vector4 getColor3() const
    {
        return color3;
    }
    void setColor1(const Vector4& color)
    {
        this->color1 = color;
    }
    void setColor2(const Vector4& color)
    {
        this->color2 = color;
    }
    void setColor3(const Vector4& color)
    {
        this->color3 = color;
    }
};


#endif
