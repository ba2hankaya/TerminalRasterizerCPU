#ifndef OBJECTDEF
#define OBJECTDEF

#include "mat4.hpp"
#include <vector>
#include "triangle.hpp"
#include "operations.hpp"

class Object
{
    private:
    Matrix4x4 localMatrix;

    Matrix4x4 worldMatrix;

    std::vector<Triangle> triangles;


    bool _isDirty = true;

    bool _parentChanged = false;

    public:

    Object()
    {
    }

    void setLocalMatrix(const Matrix4x4& m)
    {
        localMatrix = m;
        _isDirty = true;
    }

    virtual void UpdateDirty(Object* parent = nullptr)
    {
        if(_isDirty)
        {
            worldMatrix = multiply(parent->getWorldMatrix(), localMatrix);
            _isDirty = false;
        }
    }

    bool isDirty()
    {
        return _isDirty;
    }

    bool parentChanged()
    {
        return _parentChanged;
    }

    void addTriangle(const Triangle& t)
    {
        triangles.push_back(t);
    }

    std::vector<Triangle> getTriangles()
    {
        return triangles;
    }

    Matrix4x4 getLocalMatrix()
    {
        return localMatrix;
    };
    Matrix4x4 getWorldMatrix()
    {
        return worldMatrix;
    };
};


#endif