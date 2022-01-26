#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Tuples.h"

namespace Alfodr
{
    
template<typename T>
struct Rectangle
{
    T originX;
    T originY;
    T sizeX;
    T sizeY;

    Rectangle(T _originX, T _originY, T _sizeX, T _sizeY) : originX(_originX), originY(_originY), sizeX(_sizeX), sizeY(_sizeY) {}; 
};

} // namespace Alfodr



#endif // __GEOMETRY_H__