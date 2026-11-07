#include "mat3.hpp"
#include "object.hpp"
#include "operations.hpp"
#include "quaternion.hpp"
#include "scene_graph.hpp"
#include "camera.hpp"
#include <unistd.h>
#include "rasterizer.hpp"
#include "triangle.hpp"
#include <chrono>
#include <thread>

void frame(SceneGraph& scene, Camera& camera, Rasterizer& rasterizer);

int main()
{
    using namespace std::chrono;

    int fps = 60;
    const microseconds frame_duration(1000000 / fps); 
    auto next_frame = steady_clock::now();

    int target_lines = 71;
    int target_cols = 281;

    long long unsigned int current_frame = 0;

    Rasterizer rasterizer(target_cols,target_lines);

    SceneGraph scene;
    Camera camera(90, target_cols/float(target_lines), 1, 100);
    scene.addObject(&camera, -1);

    Object o;
    o.setLocalMatrix(translation(Vector3(0, 0, 1.3)));

    Object box; 
    box.createBox(1,1,1);

    scene.addObject(&o, -1);
    scene.addObject( &box, 1);

    while (true) {
        box.setLocalMatrix(multiply(rotation(EulerAngles(0.01 * current_frame, 0.03 * current_frame , 0.02 * current_frame)),translation(Vector3(0,0,0))));
        next_frame += frame_duration;
        frame(scene, camera, rasterizer);
        std::this_thread::sleep_until(next_frame);
        current_frame++;
    }

    endwin();
    return 0;
}

void ApplyMVPToTrianglesAndPassToRasterizer(const std::vector<Triangle>& triangles, const Matrix4x4& mvpMatrix, Rasterizer& rasterizer)
{
    int t = 0;
    for (const auto& triangle : triangles)
    {
        Vector4 v1 = triangle.x();
        Vector4 v2 = triangle.y();
        Vector4 v3 = triangle.z();

        Vector4 transformedV1 = multiply(mvpMatrix, v1);
        Vector4 transformedV2 = multiply(mvpMatrix, v2);
        Vector4 transformedV3 = multiply(mvpMatrix, v3);

        divideByW(transformedV1);
        divideByW(transformedV2);
        divideByW(transformedV3);

        rasterizer.vertexBuffer[t * 6 + 0] = transformedV1;
        rasterizer.vertexBuffer[t * 6 + 1] = triangle.getColor1();
        rasterizer.vertexBuffer[t * 6 + 2] = transformedV2;
        rasterizer.vertexBuffer[t * 6 + 3] = triangle.getColor2();
        rasterizer.vertexBuffer[t * 6 + 4] = transformedV3;
        rasterizer.vertexBuffer[t * 6 + 5] = triangle.getColor3();

        t++;
    }
}


void frame(SceneGraph& scene, Camera& camera, Rasterizer& rasterizer)
{
    scene.updateDirty();
    std::vector<Object*> sceneObjects = scene.getAllObjects();
    std::vector<Object*> objects = camera.cullFrustum(sceneObjects);
    Matrix4x4 viewMatrix = camera.getViewMatrix();
    Matrix4x4 projectionMatrix = camera.getProjectionMatrix();
    for (const auto& obj : objects)
    {
        Matrix4x4 modelMatrix = obj->getWorldMatrix();
        Matrix4x4 mvpMatrix = multiply(projectionMatrix, multiply(viewMatrix, modelMatrix));
        ApplyMVPToTrianglesAndPassToRasterizer(obj->getTriangles(), mvpMatrix, rasterizer);
    }
    rasterizer.NDCtoScreen();
    rasterizer.DrawAllTriangles();
}
