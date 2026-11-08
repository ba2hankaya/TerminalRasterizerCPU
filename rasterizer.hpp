#ifndef RASTERIZERDEF
#define RASTERIZERDEF

#include "mat4.hpp"
#include "operations.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
#include <ncurses.h>
#include <limits.h>

class Rasterizer
{
    private:
    int width;
    int height;

    Matrix4x4 viewportMatrix;

    char transparencyGradient[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

    public:
    Vector4 vertexBuffer[20000]; // Assuming a maximum of 20000 vertices
    float* depthBuffer;
    Rasterizer(int width, int height)
    {
        this->width = width;
        this->height = height;

        this->viewportMatrix = Matrix4x4(
            width / 2.0f, 0, 0, width / 2.0f,
            0, -height / 2.0f, 0, height / 2.0f,
            0, 0, 1, 0,
            0, 0, 0, 1
        );

        depthBuffer = new float[width * height];

        initscr();
        noecho();
        cbreak();
        curs_set(FALSE);

        ClearVertexBuffer();
        ClearDepthBuffer();
    }

    ~Rasterizer()
    {
        delete [] depthBuffer;
    }

    void NDCtoScreen(int sizeBuffer)
    {
        for (int i = 0; i < sizeBuffer; i += 2)
        {
            vertexBuffer[i] = multiply(viewportMatrix, vertexBuffer[i]);
        }
    }

    void DrawAllTriangles(int sizeBuffer)
    {
        ClearScreen();
        for (int i = 0; i  + 5 < sizeBuffer; i += 6)
        {
            DrawTriangle(vertexBuffer[i], vertexBuffer[i + 1], vertexBuffer[i + 2], vertexBuffer[i + 3], vertexBuffer[i + 4], vertexBuffer[i + 5]);
        }
        ClearVertexBuffer();
        ClearDepthBuffer();
        refresh();
    }

    private:
    void DrawTriangle(const Vector4& v1, const Vector4& color1, const Vector4& v2, const Vector4& color2, const Vector4& v3, const Vector4& color3)
    {
        int minX, minY, maxX, maxY;
        GetBoundingBox(v1, v2, v3, minX, minY, maxX, maxY);
        MSAA(minX, minY, maxX, maxY, v1, v2, v3, color1, color2, color3);
    }

    void MSAA(const int& minx, const int& miny, const int& maxx, const int& maxy, const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& c1,const Vector4& c2,const Vector4& c3)
    {

        for(int x = minx; x <= maxx; x += 1)
        {
            for(int y = miny; y <= maxy; y += 1)
            {
                float centerX = x + 0.5f;
                float centerY = y + 0.5f;

                float edge12 = (v2.x - v1.x) * (centerY - v1.y) - (v2.y - v1.y) * (centerX - v1.x);
                float edge23 = (v3.x - v2.x) * (centerY - v2.y) - (v3.y - v2.y) * (centerX - v2.x);
                float edge13 = (v1.x - v3.x) * (centerY - v3.y) - (v1.y - v3.y) * (centerX - v3.x);

                if(edge12 <= 0 && edge23 <= 0 && edge13 <= 0)
                {
                    edge12 = -edge12;
                    edge23 = -edge23;
                    edge13 = -edge13;
                }

                if(edge12 >= 0 && edge23 >= 0 && edge13 >= 0)
                {
                    int screenX = static_cast<int>(x);
                    int screenY = static_cast<int>(y);

                    if(screenX >= 0 && screenX < width && screenY >= 0 && screenY < height)
                    {
                        float depth = InterpolateAttribute(v1, v2, v3, edge12, edge23, edge13);
                        if(depthBuffer[y * width + x] > depth)
                        {
                            mvaddch(screenY, screenX, transparencyGradient[int(floor(c3.w * 10))]);
                            depthBuffer[y * width + x] = depth;
                        }
                    }
                }
            }
        }
    }

    template<typename T>
    float InterpolateAttribute(T a1, T a2, T a3, const float& e12, const float& e23, const float& e13)
    {
        float sum = e12 + e23 + e13;
        float alpha1 = e23 / sum;
        float alpha2 = e13 / sum;
        float alpha3 = e12 / sum;

        float interpolatedDepth = alpha1 * a1.z + alpha2 * a2.z + alpha3 * a3.z;
        return  interpolatedDepth;
    }

    void GetBoundingBox(const Vector4& v1, const Vector4& v2, const Vector4& v3, int& minX, int& minY, int& maxX, int& maxY)
    {
        minX = static_cast<int>(std::floor(std::min({v1.x, v2.x, v3.x})));
        minY = static_cast<int>(std::floor(std::min({v1.y, v2.y, v3.y})));
        maxX = static_cast<int>(std::ceil(std::max({v1.x, v2.x, v3.x})));
        maxY = static_cast<int>(std::ceil(std::max({v1.y, v2.y, v3.y})));
    }

    void ClearScreen()
    {
        clear();
    }

    void ClearDepthBuffer()
    {
        std::fill_n(depthBuffer, width * height, std::numeric_limits<float>::max());
    }

    void ClearVertexBuffer()
    {
        memset(vertexBuffer, 0x00, sizeof(vertexBuffer));
    }
};

#endif
