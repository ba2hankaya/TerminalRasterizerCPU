#ifndef OBJECTDEF
#define OBJECTDEF

#include "mat4.hpp"
#include <cmath>
#include <stdexcept>
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

    Object() : localMatrix(Matrix4x4::Identity()), worldMatrix(localMatrix)
    {
    }

    void setLocalMatrix(const Matrix4x4& m)
    {
        localMatrix = m;
        _isDirty = true;
    }

    virtual void UpdateDirty(Object* parent = nullptr)
    {
        const bool needsUpdate = _isDirty || (parent && parent->parentChanged());
        _parentChanged = needsUpdate;
        if(needsUpdate)
        {
            worldMatrix = parent ? multiply(parent->getWorldMatrix(), localMatrix) : localMatrix;
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

    //AI generated, can't bother calculating triangles to make a box
    // Replace the mesh with a box centered at the local origin.
    void createBox(float width = 1, float height = 1, float depth = 1,
                   Vector4 color = Vector4(1, 1, 1, 1))
    {
        validateDimensions(width, height, depth);
        const float x = width / 2, y = height / 2, z = depth / 2;
        const Vector4 vertices[] = {
            Vector4(-x, -y, -z, 1), Vector4(x, -y, -z, 1),
            Vector4(x, y, -z, 1), Vector4(-x, y, -z, 1),
            Vector4(-x, -y, z, 1), Vector4(x, -y, z, 1),
            Vector4(x, y, z, 1), Vector4(-x, y, z, 1)
        };
        const int faces[][3] = {
            {0, 3, 2}, {0, 2, 1}, // back
            {4, 5, 6}, {4, 6, 7}, // front
            {0, 4, 7}, {0, 7, 3}, // left
            {1, 2, 6}, {1, 6, 5}, // right
            {0, 1, 5}, {0, 5, 4}, // bottom
            {3, 7, 6}, {3, 6, 2}  // top
        };
        triangles.clear();
        triangles.reserve(12);
        for (size_t i = 0; i < 12; ++i)
        {
            const auto& face = faces[i];
            // Alpha is used as a mock brightness; each pair forms one surface.
            Vector4 faceColor = color;
            faceColor.w = color.w * (0.99f - 0.12f * static_cast<float>(i / 2));
            triangles.emplace_back(vertices[face[0]], vertices[face[1]], vertices[face[2]],
                                   faceColor, faceColor, faceColor);
        }
    }

    //also ai generated
    // Replace the mesh with a pyramid centered in its local bounding box.
    // The base lies at y = -height/2; the apex lies at y = height/2.
    void createPyramid(float width = 1, float height = 1, float depth = 1,
                       const Vector4& color = Vector4(1, 1, 1, 1))
    {
        validateDimensions(width, height, depth);
        const float x = width / 2, y = height / 2, z = depth / 2;
        const Vector4 vertices[] = {
            Vector4(-x, -y, -z, 1), Vector4(x, -y, -z, 1),
            Vector4(x, -y, z, 1), Vector4(-x, -y, z, 1),
            Vector4(0, y, 0, 1)
        };
        const int faces[][3] = {
            {0, 1, 2}, {0, 2, 3}, // base
            {0, 4, 1}, {1, 4, 2}, {2, 4, 3}, {3, 4, 0}
        };
        triangles.clear();
        triangles.reserve(6);
        for (const auto& face : faces)
        {
            triangles.emplace_back(vertices[face[0]], vertices[face[1]], vertices[face[2]],
                                   color, color, color);
        }
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

    //Ai generated
    private:
    static void validateDimensions(float width, float height, float depth)
    {
        if (!(width > 0 && height > 0 && depth > 0) ||
            !std::isfinite(width) || !std::isfinite(height) || !std::isfinite(depth))
        {
            throw std::invalid_argument("Shape dimensions must be finite and positive.");
        }
    }
};


#endif
