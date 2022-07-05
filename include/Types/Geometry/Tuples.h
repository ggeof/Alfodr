#ifndef __TUPLES_H__
#define __TUPLES_H__


namespace Alfodr{

#pragma region Vecteurs
    template<typename T>
    struct Vec1 {
        T x; 
        Vec1(T _x) { x = _x;}
    };

    template<typename T>
    struct Vec2 : public Vec1<T> {
        T y; 
        Vec2(T _x, T _y) : Vec1<T>(_x) { y = _y; }
    };

    template<typename T>
    struct Vec3 : public Vec2<T> {
        T z; 
        Vec3(T _x, T _y, T _z) : Vec2<T>(_x, _y) { z = _z; }
    };
#pragma endregion

#pragma region Definition des points

    template <typename T = float>
    using Point1D = Vec1<T>;

    template <typename T = float>
    using Point2D = Vec2<T>;

    template <typename T = float>
    using Point3D = Vec3<T>;


#pragma endregion

#pragma region Operators of vectors

    template<typename T>
    Vec1<T> operator+(const Vec1<T> v1, const Vec1<T>& v2) {return Vec1<T>(v1.x+v2.x);}
    template<typename T>
    Vec1<T> operator-(const Vec1<T> v1, const Vec1<T>& v2) {return Vec1<T>(v1.x-v2.x);}
    template<typename T>
    Vec1<T> operator/(const Vec1<T> v1, const Vec1<T>& v2) {return Vec1<T>(v1.x/v2.x);}
    template<typename T>
    Vec1<T> operator*(const Vec1<T> v1, const Vec1<T>& v2) {return Vec1<T>(v1.x*v2.x);}
    template<typename T>
    bool operator==(const Vec1<T> v1, const Vec1<T>& v2) {return v1.x==v2.x;}
    template<typename T>
    bool operator!=(const Vec1<T> v1, const Vec1<T>& v2) {return v1.x!=v2.x;}


    template<typename T>
    Vec1<T> operator+(const Vec1<T> v1, const T var[1]) {return Vec1<T>(v1.x+var[0]);}
    template<typename T>
    Vec1<T> operator-(const Vec1<T> v1, const T var[1]) {return Vec1<T>(v1.x-var[0]);}
    template<typename T>
    Vec1<T> operator/(const Vec1<T> v1, const T var[1]) {return Vec1<T>(v1.x/var[0]);}
    template<typename T>
    Vec1<T> operator*(const Vec1<T> v1, const T var[1]) {return Vec1<T>(v1.x*var[0]);}



    template<typename T>
    Vec2<T> operator+(const Vec2<T> v1, const Vec2<T>& v2) {return Vec2<T>(v1.x+v2.x, v1.y+v2.y);}
    template<typename T>
    Vec2<T> operator-(const Vec2<T> v1, const Vec2<T>& v2) {return Vec2<T>(v1.x-v2.x, v1.y-v2.y);}
    template<typename T>
    Vec2<T> operator/(const Vec2<T> v1, const Vec2<T>& v2) {return Vec2<T>(v1.x/v2.x, v1.y/v2.y);}
    template<typename T>
    Vec2<T> operator*(const Vec2<T> v1, const Vec2<T>& v2) {return Vec2<T>(v1.x*v2.x, v1.y*v2.y);}
    template<typename T>
    bool operator==(const Vec2<T> v1, const Vec2<T>& v2) {return v1.x==v2.x && v1.y == v2.y;}
    template<typename T>
    bool operator!=(const Vec2<T> v1, const Vec2<T>& v2) {return v1.x!=v2.x || v1.y != v2.y;}


    template<typename T>
    Vec2<T> operator+(const Vec2<T> v1, const T var[2]) {return Vec2<T>(v1.x+var[0], v1.y+var[1]);}
    template<typename T>
    Vec2<T> operator-(const Vec2<T> v1, const T var[2]) {return Vec2<T>(v1.x-var[0], v1.y-var[1]);}
    template<typename T>
    Vec2<T> operator/(const Vec2<T> v1, const T var[2]) {return Vec2<T>(v1.x/var[0], v1.y/var[1]);}
    template<typename T>
    Vec2<T> operator*(const Vec2<T> v1, const T var[2]) {return Vec2<T>(v1.x*var[0], v1.y*var[1]);}


    template<typename T>
    Vec3<T> operator+(const Vec3<T> v1, const Vec3<T>& v2) {return Vec3<T>(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);}
    template<typename T>
    Vec3<T> operator-(const Vec3<T> v1, const Vec3<T>& v2) {return Vec3<T>(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);}
    template<typename T>
    Vec3<T> operator/(const Vec3<T> v1, const Vec3<T>& v2) {return Vec3<T>(v1.x/v2.x, v1.y/v2.y, v1.z/v2.z);}
    template<typename T>
    Vec3<T> operator*(const Vec3<T> v1, const Vec3<T>& v2) {return Vec3<T>(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);}
    template<typename T>
    bool operator==(const Vec3<T> v1, const Vec3<T>& v2) {return v1.x==v2.x && v1.y == v2.y && v1.z == v2.z;}
    template<typename T>
    bool operator!=(const Vec3<T> v1, const Vec3<T>& v2) {return v1.x!=v2.x || v1.y != v2.y || v1.z != v2.z;}


    template<typename T>
    Vec3<T> operator+(const Vec3<T> v1, const T var[3]) {return Vec3<T>(v1.x+var[0], v1.y+var[1], v1.x+var[2]);}
    template<typename T>
    Vec3<T> operator-(const Vec3<T> v1, const T var[3]) {return Vec3<T>(v1.x-var[0], v1.y-var[1], v1.x-var[2]);}
    template<typename T>
    Vec3<T> operator/(const Vec3<T> v1, const T var[3]) {return Vec3<T>(v1.x/var[0], v1.y/var[1], v1.x/var[2]);}
    template<typename T>
    Vec3<T> operator*(const Vec3<T> v1, const T var[3]) {return Vec3<T>(v1.x*var[0], v1.y*var[1], v1.x*var[2]);}


#pragma endregion


}

#endif // __TUPLES_H__