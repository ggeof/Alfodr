#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Tuples.h"

namespace Alfodr
{
    
template<typename T>
struct Rectangle
{
    T left;
    T top;
    T right;
    T bottom;

    Rectangle(T _left, T _top, T _right, T _bottom) : left(_left), top(_top), right(_right), bottom(_bottom) {}; 
};

} // namespace Alfodr



#endif // __GEOMETRY_H__