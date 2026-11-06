#include "mat4.hpp"
#include <stdexcept>

float& Matrix4x4::operator()(size_t row, size_t col){
    if(row >= 4 || col >= 4)
    {
        throw std::out_of_range("Index out of bounds.");
    }
    return values[row * 4 + col];
}
const float& Matrix4x4::operator()(size_t row, size_t col) const{
    if(row >= 4 || col >= 4)
    {
        throw std::out_of_range("Index out of bounds.");
    }
    return values[row * 4 + col];
}