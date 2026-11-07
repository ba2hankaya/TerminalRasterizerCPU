#ifndef RASTERIZERDEF
#define RASTERIZERDEF

#include "mat4.hpp"
#include "operations.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ncurses.h>

class Rasterizer
{
    private:
    int width;
    int height;

    Matrix4x4 viewportMatrix;

    char transparencyGradient[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

    public:
    Vector4 vertexBuffer[20000]; // Assuming a maximum of 20000 vertices
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

        initscr();
        noecho();
        cbreak();
        curs_set(FALSE);

        memset(vertexBuffer, 0x00, sizeof(vertexBuffer));
    }

    void NDCtoScreen()
    {
        for (int i = 0; i < 20000; i++)
        {
            vertexBuffer[i] = multiply(viewportMatrix, vertexBuffer[i]);
        }
    }

    void DrawAllTriangles()
    {
        ClearScreen();
        for (int i = 0; i  + 5 < 20000; i += 6)
        {
            DrawTriangle(vertexBuffer[i], vertexBuffer[i + 1], vertexBuffer[i + 2], vertexBuffer[i + 3], vertexBuffer[i + 4], vertexBuffer[i + 5]);
        }
        memset(vertexBuffer, 0x00, sizeof(vertexBuffer));
        refresh();
    }

    private:
    void DrawTriangle(const Vector4& v1, const Vector4& color1, const Vector4& v2, const Vector4& color2, const Vector4& v3, const Vector4& color3)
    {
        int minX, minY, maxX, maxY;
        GetBoundingBox(v1, v2, v3, minX, minY, maxX, maxY);
        MSAA(minX, minY, maxX, maxY, v1, v2, v3);
    }

    void MSAA(const int& minx, const int& miny, const int& maxx, const int& maxy, const Vector4& v1, const Vector4& v2, const Vector4& v3)
    {

        for(int x = minx; x <= maxx; x += 1)
        {
            for(int y = miny; y <= maxy; y += 1)
            {
                float centerX = x + 0.5f;
                float centerY = y + 0.5f;

                float edge1 = (v2.x - v1.x) * (centerY - v1.y) - (v2.y - v1.y) * (centerX - v1.x);
                float edge2 = (v3.x - v2.x) * (centerY - v2.y) - (v3.y - v2.y) * (centerX - v2.x);
                float edge3 = (v1.x - v3.x) * (centerY - v3.y) - (v1.y - v3.y) * (centerX - v3.x);

                if(edge1 <= 0 && edge2 <= 0 && edge3 <= 0)
                {
                    edge1 = -edge1;
                    edge2 = -edge2;
                    edge3 = -edge3;
                }

                if(edge1 >= 0 && edge2 >= 0 && edge3 >= 0)
                {
                    int screenX = static_cast<int>(x);
                    int screenY = static_cast<int>(y);

                    if(screenX >= 0 && screenX < width && screenY >= 0 && screenY < height)
                    {
                        mvaddch(screenY, screenX, '@');
                    }
                }
            }
        }
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
};

#endif
