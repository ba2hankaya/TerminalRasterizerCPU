#ifndef CAMERADEF
#define CAMERADEF

#include "mat4.hpp"
#include "object.hpp"
#include "operations.hpp"
#include <cmath>

class Camera : public Object
{
    private:
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    Matrix4x4 viewMatrix;

    bool isObjectInFrustum(const Object& obj)
    {
        return true; //for testing
    }

    public:
    Camera(float fov = 90, float aspectRatio = 1.0, float nearPlane = 1, float farPlane = 100.0)
    {
        this->fov = fov;
        this->aspectRatio = aspectRatio;
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;

        setLocalMatrix(
            Matrix4x4
            (
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, -1, 0,
                0, 0, 0, 1
            )
        );
    }

    void UpdateDirty()
    {
        Object::UpdateDirty();
        viewMatrix = rigidInverse(getLocalMatrix());
    }

    std::vector<Object*> cullFrustumAndReturnRemaining()
    {
        return std::vector<Object*>();
    }

    std::vector<Object*> cullFrustum(const std::vector<Object>& objects)
    {
        std::vector<Object*> remainingObjects;
        for(const auto& obj : objects)
        {
            if(isObjectInFrustum(obj))
            {
                remainingObjects.push_back(const_cast<Object*>(&obj));
            }
        }
        return remainingObjects;
    }

    Matrix4x4 getViewMatrix()
    {
        return viewMatrix;
    }

    Matrix4x4 getProjectionMatrix()
    {
        float f = 1.0f / tan(fov * 0.5f * (3.14159265358979323846f / 180.0f));
        return Matrix4x4(
            f / aspectRatio, 0, 0, 0,
            0, f, 0, 0,
            0, 0, (farPlane) / (nearPlane - farPlane), (farPlane * nearPlane) / (nearPlane - farPlane),
            0, 0, -1, 0
        );
    }

    void lookAt(const Vector4& target, const Vector4& up = Vector4(0, 1, 0, 0))
    {
        Matrix4x4 currentWorldMatrix = getWorldMatrix();
        Vector4 eye(currentWorldMatrix(0,3), currentWorldMatrix(1,3), currentWorldMatrix(2,3), 1);

        Vector4 w = eye - target;
        w = normalize(w);

        Vector4 u = cross(up, w);
        u = normalize(u);

        Vector4 v = cross(w, u);

        Matrix4x4 lookAtMatrix(
            u.x, v.x, w.x, eye.x,
            u.y, v.y, w.y, eye.y,
            u.z, v.z, w.z, eye.z,
            0,   0,   0,    1
        );

        setLocalMatrix(lookAtMatrix);
    }
};

#endif