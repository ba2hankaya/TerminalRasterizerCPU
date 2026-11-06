#include "mat3.hpp"
#include <stdexcept>

float& Matrix3x3::operator()(size_t row, size_t col){
    if(row >= 3 || col >= 3)
    {
        throw std::out_of_range("Index out of bounds.");
    }
    return values[row * 3 + col];
}
const float& Matrix3x3::operator()(size_t row, size_t col) const{
    if(row >= 3 || col >= 3)
    {
        throw std::out_of_range("Index out of bounds.");
    }
    return values[row * 3 + col];
}