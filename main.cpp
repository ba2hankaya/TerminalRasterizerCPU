#include "object.hpp"
#include "scene_graph.hpp"
#include "camera.hpp"
#include <unistd.h>
#include "rasterizer.hpp"
#include <chrono>
#include <thread>

void frame(SceneGraph& scene, Camera& camera, Rasterizer& rasterizer);

int main()
{
    using namespace std::chrono;

    int fps = 60;
    const microseconds frame_duration(1000000 / fps); 
    auto next_frame = steady_clock::now();

    int target_lines = 100;
    int target_cols = 100;

    printf("\e[8;%d;%dt", target_lines, target_cols);
    fflush(stdout);

    usleep(50000);
    Rasterizer rasterizer(target_lines, target_cols);

    SceneGraph scene;
    Camera camera(90, 1.0, 1, 100);
    scene.addObject(&camera, -1);

    while (true) {
        next_frame += frame_duration;
        frame(scene, camera, rasterizer);
        std::this_thread::sleep_until(next_frame);
    }

    return 0;
}

void ApplyMVPToTrianglesAndPassToRasterizer(const std::vector<Triangle>& triangles, const Matrix4x4& mvpMatrix, Rasterizer& rasterizer)
{
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

        rasterizer.vertexBuffer[0] = transformedV1;
        rasterizer.vertexBuffer[1] = triangle.getColor1();
        rasterizer.vertexBuffer[2] = transformedV2;
        rasterizer.vertexBuffer[3] = triangle.getColor2();
        rasterizer.vertexBuffer[4] = transformedV3;
        rasterizer.vertexBuffer[5] = triangle.getColor3();
    }
}


void frame(SceneGraph& scene, Camera& camera, Rasterizer& rasterizer)
{
    scene.updateDirty();
    std::vector<Object*> objects = camera.cullFrustum(scene.getAllObjects());
    Matrix4x4 viewMatrix = camera.getWorldMatrix();
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
