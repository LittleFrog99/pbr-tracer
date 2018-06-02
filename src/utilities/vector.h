#ifndef VECTOR_H
#define VECTOR_H

#include "stringprint.h"

// Forward Declarations
template <class T>
class Vector2;
template <class T>
class Vector3;
template <class T>
class Point3;
template <class T>
class Point2;
template <class T>
class Normal3;

// Vector Declarations
template <class T>
class Vector2 {
public:
    // Vector2 Public Methods
    inline Vector2() { x = y = 0; }
    inline Vector2(T xx, T yy) : x(xx), y(yy) { }
    explicit Vector2(const Point2<T> &p);
    inline bool hasNaNs() const { return isNaN(x) || isNaN(y); }

    inline Vector2(const Vector2<T> &v) { x = v.x; y = v.y; }
    inline Vector2<T> & operator = (const Vector2<T> &v) { x = v.x; y = v.y; return *this; }
    inline Vector2<T> operator + (const Vector2<T> &v) const { return Vector2(x + v.x, y + v.y); }
    inline Vector2<T> & operator += (const Vector2<T> &v) { x += v.x; y += v.y; return *this; }
    inline Vector2<T> operator - (const Vector2<T> &v) const { return Vector2(x - v.x, y - v.y); }

    inline Vector2<T> & operator -= (const Vector2<T> &v) { x -= v.x; y -= v.y; return *this; }
    inline bool operator == (const Vector2<T> &v) const { return x == v.x && y == v.y; }
    inline bool operator != (const Vector2<T> &v) const { return x != v.x || y != v.y; }

    template <class U>
    inline Vector2<T> operator * (U f) const { return Vector2<T>(f * x, f * y); }

    template <class U>
    inline Vector2<T> &operator*=(U f) { x *= f; y *= f; return *this; }

    template <class U>
    inline Vector2<T> operator / (U f) const {
        Float inv = 1.0 / f;
        return Vector2<T>(x * inv, y * inv);
    }

    template <class U>
    inline Vector2<T> & operator /= (U f) { Float inv = 1.0 / f; x *= inv; y *= inv; return *this; }

    inline Vector2<T> operator - () const { return Vector2<T>(-x, -y); }
    inline T operator [] (int i) const { if (i == 0) return x; return y; }
    inline T & operator [] (int i) { if (i == 0) return x; return y; }
    inline Float lengthSq() const { return x * x + y * y; }
    inline Float length() const { return std::sqrt(lengthSq()); }

    // Vector2 Public Data
    T x, y;
};

template <typename T, typename U>
inline Vector2<T> operator * (U f, const Vector2<T> &v) {
    return v * f;
}

template <class T>
inline ostream & operator << (ostream &os, const Vector2<T> &v) {
    os << "[ " << v.x << ", " << v.y << " ]";
    return os;
}

inline ostream & operator << (ostream &os, const Vector2<Float> &v) {
    os << StringPrint::printf("[ %f, %f ]", v.x, v.y);
    return os;
}

template <class T>
class Vector3 {
public:
    // Vector3 Public Methods
    inline Vector3() { x = y = z = 0; }
    inline Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
    inline Vector3(const Vector3<T> &v) { x = v.x; y = v.y; z = v.z; }
    explicit Vector3(const Point3<T> &p);
    explicit Vector3(const Normal3<T> &n);
    inline bool hasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }

    inline Vector3<T> & operator = (const Vector3<T> &v) { x = v.x; y = v.y; z = v.z; return *this; }
    inline Vector3<T> operator + (const Vector3<T> &v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    inline Vector3<T> & operator += (const Vector3<T> &v) { x += v.x; y += v.y; z += v.z; return *this; }
    inline Vector3<T> operator - (const Vector3<T> &v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    inline Vector3<T> & operator -= (const Vector3<T> &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    inline Vector3<T> operator - () const { return Vector3<T>(-x, -y, -z); }
    inline bool operator == (const Vector3<T> &v) const { return x == v.x && y == v.y && z == v.z; }
    inline bool operator != (const Vector3<T> &v) const { return x != v.x || y != v.y || z != v.z; }

    template <class U>
    inline Vector3<T> operator * (U s) const { return Vector3<T>(s * x, s * y, s * z); }

    template <class U>
    inline Vector3<T> & operator *= (U s) { x *= s; y *= s; z *= s; return *this; }

    template <class U>
    inline Vector3<T> operator / (U f) const {
        Float inv = 1.0 / f;
        return Vector3<T>(x * inv, y * inv, z * inv);
    }

    template <class U>
    Vector3<T> &operator /= (U f) {
        Float inv = 1.0 / f;
        x *= inv; y *= inv; z *= inv;
        return *this;
    }

    inline T operator [] (int i) const { if (i == 0) return x; if (i == 1) return y; return z; }
    inline T & operator [] (int i) { if (i == 0) return x; if (i == 1) return y; return z; }
    inline Float lengthSq() const { return x * x + y * y + z * z; }
    inline Float length() const { return std::sqrt(lengthSq()); }

    // Vector3 Public Data
    T x, y, z;
};

template <class T>
inline ostream & operator << (ostream &os, const Vector3<T> &v) {
    os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return os;
}

inline ostream & operator << (ostream &os, const Vector3<Float> &v) {
    os << StringPrint::printf("[ %f, %f, %f ]", v.x, v.y, v.z);
    return os;
}

typedef Vector2<Float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector3<Float> Vector3f;
typedef Vector3<int> Vector3i;

// Point Declarations
template <class T>
class Point2 {
public:
    inline Point2() { x = y = 0; }
    inline Point2(T xx, T yy) : x(xx), y(yy) { }
    inline Point2(const Point2<T> &p) { x = p.x; y = p.y; }
    inline explicit Point2(const Point3<T> &p) : x(p.x), y(p.y) { }
    inline bool hasNaNs() const { return isNaN(x) || isNaN(y); }

    template <class U>
    inline explicit Point2(const Point2<U> &p) { x = T(p.x); y = T(p.y); }

    template <class U>
    inline explicit Point2(const Vector2<U> &p) { x = T(p.x); y = T(p.y); }

    template <class U>
    inline explicit operator Vector2<U>() const { return Vector2<U>(x, y); }

    inline Point2<T> & operator = (const Point2<T> &p) { x = p.x; y = p.y; return *this; }
    inline Point2<T> operator + (const Vector2<T> &v) const { return Point2<T>(x + v.x, y + v.y); }
    inline Point2<T> & operator += (const Vector2<T> &v) { x += v.x; y += v.y; return *this; }
    inline Vector2<T> operator - (const Point2<T> &p) const { return Vector2<T>(x - p.x, y - p.y); }
    inline Point2<T> operator - (const Vector2<T> &v) const { return Point2<T>(x - v.x, y - v.y); }
    inline Point2<T> operator - () const { return Point2<T>(-x, -y); }
    inline Point2<T> & operator -= (const Vector2<T> &v) {x -= v.x; y -= v.y; return *this; }
    inline Point2<T> & operator += (const Point2<T> &p) { x += p.x; y += p.y; return *this; }
    inline Point2<T> operator + (const Point2<T> &p) const { return Point2<T>(x + p.x, y + p.y); }

    template <class U>
    inline Point2<T> operator * (U f) const { return Point2<T>(f * x, f * y); }

    template <class U>
    inline Point2<T> & operator *= (U f) { x *= f; y *= f; return *this; }

    template <class U>
    inline Point2<T> operator / (U f) const { Float inv = 1.0 / f; return Point2<T>(inv * x, inv * y); }

    template <class U>
    inline Point2<T> & operator /= (U f) {
        Float inv = 1.0 / f;
        x *= inv; y *= inv;
        return *this;
    }

    inline T operator [] (int i) const { if (i == 0) return x; return y; }
    inline T & operator [] (int i) { if (i == 0) return x; return y; }
    inline bool operator == (const Point2<T> &p) const { return x == p.x && y == p.y; }
    inline bool operator != (const Point2<T> &p) const { return x != p.x || y != p.y; }

    T x, y;
};

template <typename T, typename U>
inline Point2<T> operator*(U f, const Point2<T> &p) {
    return p * f;
}

template <class T>
inline ostream & operator << (ostream &os, const Point2<T> &v) {
    os << "[ " << v.x << ", " << v.y << " ]";
    return os;
}

inline ostream & operator << (ostream &os, const Point2<Float> &v) {
    os << StringPrint::printf("[ %f, %f ]", v.x, v.y);
    return os;
}

template <class T>
class Point3 {
public:
    inline Point3() { x = y = z = 0; }
    inline Point3(T x, T y, T z) : x(x), y(y), z(z) { }
    inline Point3(const Point3<T> &p) { x = p.x; y = p.y; z = p.z; }
    inline bool hasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }

    template <class U>
    inline explicit Point3(const Point3<U> &p) : x(p.x), y(p.y), z(p.z) {}

    template <class U>
    inline explicit operator Vector3<U>() const { return Vector3<U>(x, y, z); }

    inline Point3<T> & operator = (const Point3<T> &p) { x = p.x; y = p.y; z = p.z; return *this; }
    inline Point3<T> operator + (const Vector3<T> &v) const { return Point3<T>(x + v.x, y + v.y, z + v.z); }
    inline Point3<T> & operator += (const Vector3<T> &v) { x += v.x; y += v.y; z += v.z; return *this; }
    inline Point3<T> operator - () const { return Point3<T>(-x, -y, -z); }
    inline Vector3<T> operator - (const Point3<T> &p) const { return Vector3<T>(x - p.x, y - p.y, z - p.z); }
    inline Point3<T> operator - (const Vector3<T> &v) const { return Point3<T>(x - v.x, y - v.y, z - v.z); }
    inline Point3<T> & operator -= (const Vector3<T> &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    inline Point3<T> & operator += (const Point3<T> &p) { x += p.x; y += p.y; z += p.z; return *this; }
    inline Point3<T> operator + (const Point3<T> &p) const { return Point3<T>(x + p.x, y + p.y, z + p.z); }

    template <class U>
    inline Point3<T> operator * (U f) const { return Point3<T>(f * x, f * y, f * z); }

    template <class U>
    inline Point3<T> & operator *= (U f) { x *= f; y *= f; z *= f; return *this; }

    template <class U>
    inline Point3<T> operator / (U f) const { Float inv = 1.0 / f; return Point3<T>(inv * x, inv * y, inv * z); }

    template <class U>
    inline Point3<T> & operator /= (U f) {
        Float inv = 1.0 / f;
        x *= inv; y *= inv; z *= inv;
        return *this;
    }

    inline T operator [] (int i) const { if (i == 0) return x; if (i == 1) return y; return z; }
    inline T & operator [] (int i) { if (i == 0) return x; if (i == 1) return y; return z; }
    inline bool operator == (const Point3<T> &p) const { return x == p.x && y == p.y && z == p.z; }
    inline bool operator != (const Point3<T> &p) const { return x != p.x || y != p.y || z != p.z; }

    T x, y, z;
};

template <typename T, typename U>
inline Point3<T> operator * (U f, const Point3<T> &p) {
    return p * f;
}

template <class T>
inline ostream & operator << (ostream &os, const Point3<T> &v) {
    os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return os;
}

inline ostream & operator << (ostream &os, const Point3<Float> &v) {
    os << StringPrint::printf("[ %f, %f, %f ]", v.x, v.y, v.z);
    return os;
}

typedef Point2<Float> Point2f;
typedef Point2<int> Point2i;
typedef Point3<Float> Point3f;
typedef Point3<int> Point3i;

// Normal Declarations
template <class T>
class Normal3 {
public:
    inline Normal3() { x = y = z = 0; }
    inline Normal3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) { }
    inline Normal3<T>(const Normal3<T> &n) { x = n.x; y = n.y; z = n.z; }
    inline explicit Normal3<T>(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {}
    inline bool hasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }

    inline Normal3<T> & operator = (const Normal3<T> &n) { x = n.x; y = n.y; z = n.z; return *this; }
    inline Normal3<T> operator - () const { return Normal3(-x, -y, -z); }
    inline Normal3<T> operator + (const Normal3<T> &n) const { return Normal3<T>(x + n.x, y + n.y, z + n.z); }
    inline Normal3<T> & operator += (const Normal3<T> &n) { x += n.x; y += n.y; z += n.z; return *this; }
    inline Normal3<T> operator - (const Normal3<T> &n) const { return Normal3<T>(x - n.x, y - n.y, z - n.z); }
    inline Normal3<T> & operator -= (const Normal3<T> &n) { x -= n.x; y -= n.y; z -= n.z; return *this; }

    template <class U>
    inline Normal3<T> operator * (U f) const { return Normal3<T>(f * x, f * y, f * z); }

    template <class U>
    inline Normal3<T> & operator *= (U f) { x *= f; y *= f; z *= f; return *this; }

    template <class U>
    inline Normal3<T> operator / (U f) const {
        Float inv = 1.0 / f;
        return Normal3<T>(x * inv, y * inv, z * inv);
    }

    template <class U>
    inline Normal3<T> & operator /= (U f) {
        Float inv = 1.0 / f;
        x *= inv; y *= inv; z *= inv;
        return *this;
    }

    inline Float lengthSq() const { return x * x + y * y + z * z; }
    inline Float length() const { return std::sqrt(lengthSq()); }

    inline bool operator == (const Normal3<T> &n) const { return x == n.x && y == n.y && z == n.z; }
    inline bool operator != (const Normal3<T> &n) const { return x != n.x || y != n.y || z != n.z; }
    inline T operator [] (int i) const { if (i == 0) return x; if (i == 1) return y; return z; }
    inline T & operator [] (int i) { if (i == 0) return x; if (i == 1) return y; return z; }

    T x, y, z;
};

template <typename T, typename U>
inline Normal3<T> operator * (U f, const Normal3<T> &n) {
    return Normal3<T>(f * n.x, f * n.y, f * n.z);
}

template <class T>
inline ostream & operator << (ostream &os, const Normal3<T> &v) {
    os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return os;
}

inline ostream & operator << (ostream &os, const Normal3<Float> &v) {
    os << StringPrint::printf("[ %f, %f, %f ]", v.x, v.y, v.z);
    return os;
}

typedef Normal3<Float> Normal3f;

template<class T>
inline Vector2<T>::Vector2(const Point2<T> &p) : x(p.x), y(p.y) {}

template <class T>
inline Vector3<T>::Vector3(const Point3<T> &p) : x(p.x), y(p.y), z(p.z) {}

template<class T>
inline Vector3<T>::Vector3(const Normal3<T> &n) : x(n.x), y(n.y), z(n.z) {}

namespace Math {
template <typename T>
inline Vector3<T> cross(const Vector3<T> &v1, const Vector3<T> &v2) {
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                      (v1x * v2y) - (v1y * v2x));
}

template <typename T>
inline Vector3<T> cross(const Vector3<T> &v1, const Normal3<T> &v2) {
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                      (v1x * v2y) - (v1y * v2x));
}

template <typename T>
inline Vector3<T> cross(const Normal3<T> &v1, const Vector3<T> &v2) {
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                      (v1x * v2y) - (v1y * v2x));
}

template <typename T>
inline Vector3<T> normalize(const Vector3<T> &v) {
    return v / v.length();
}

template <typename T>
inline T minComp(const Vector3<T> &v) {
    return min(v.x, min(v.y, v.z));
}

template <typename T>
inline T maxComp(const Vector3<T> &v) {
    return max(v.x, max(v.y, v.z));
}

template <typename T>
inline int maxDim(const Vector3<T> &v) {
    return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

template <typename T>
inline Vector3<T> min(const Vector3<T> &p1, const Vector3<T> &p2) {
    return Vector3<T>(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
}

template <typename T>
inline Vector3<T> max(const Vector3<T> &p1, const Vector3<T> &p2) {
    return Vector3<T>(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
}

template <typename T>
inline Vector3<T> permute(const Vector3<T> &v, int x, int y, int z) {
    return Vector3<T>(v[x], v[y], v[z]);
}

template <typename T>
inline void coordSystem(const Vector3<T> &v1, Vector3<T> *v2,
                             Vector3<T> *v3) {
    if (abs(v1.x) > abs(v1.y))
        *v2 = Vector3<T>(-v1.z, 0, v1.x) / sqrt(v1.x * v1.x + v1.z * v1.z);
    else
        *v2 = Vector3<T>(0, v1.z, -v1.y) / sqrt(v1.y * v1.y + v1.z * v1.z);
    *v3 = cross(v1, *v2);
}

template <typename T>
inline Float dot(const Vector2<T> &v1, const Vector2<T> &v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline Float absDot(const Vector2<T> &v1, const Vector2<T> &v2) {
    return abs(dot(v1, v2));
}

template <typename T>
inline Vector2<T> normalize(const Vector2<T> &v) {
    return v / v.length();
}

template <typename T>
inline Vector2<T> abs(const Vector2<T> &v) {
    return Vector2<T>(abs(v.x), abs(v.y));
}

template <typename T>
inline Float dist(const Point3<T> &p1, const Point3<T> &p2) {
    return (p1 - p2).length();
}

template <typename T>
inline Float distSq(const Point3<T> &p1, const Point3<T> &p2) {
    return (p1 - p2).lengthSq();
}

template <typename T>
inline Point3<T> lerp(Float t, const Point3<T> &p0, const Point3<T> &p1) {
    return (1 - t) * p0 + t * p1;
}

template <typename T>
inline Point3<T> min(const Point3<T> &p1, const Point3<T> &p2) {
    return Point3<T>(min(p1.x, p2.x), min(p1.y, p2.y),
                     min(p1.z, p2.z));
}

template <typename T>
inline Point3<T> max(const Point3<T> &p1, const Point3<T> &p2) {
    return Point3<T>(max(p1.x, p2.x), max(p1.y, p2.y),
                     max(p1.z, p2.z));
}

template <typename T>
inline Point3<T> floor(const Point3<T> &p) {
    return Point3<T>(floor(p.x), floor(p.y), floor(p.z));
}

template <typename T>
inline Point3<T> ceil(const Point3<T> &p) {
    return Point3<T>(ceil(p.x), ceil(p.y), ceil(p.z));
}

template <typename T>
inline Point3<T> abs(const Point3<T> &p) {
    return Point3<T>(abs(p.x), abs(p.y), abs(p.z));
}

template <typename T>
inline Float dist(const Point2<T> &p1, const Point2<T> &p2) {
    return (p1 - p2).length();
}

template <typename T>
inline Float distSq(const Point2<T> &p1, const Point2<T> &p2) {
    return (p1 - p2).lengthSq();
}

template <typename T>
inline Point2<T> floor(const Point2<T> &p) {
    return Point2<T>(floor(p.x), floor(p.y));
}

template <typename T>
inline Point2<T> ceil(const Point2<T> &p) {
    return Point2<T>(ceil(p.x), ceil(p.y));
}

template <typename T>
inline Point2<T> lerp(Float t, const Point2<T> &v0, const Point2<T> &v1) {
    return (1 - t) * v0 + t * v1;
}

template <typename T>
inline Point2<T> min(const Point2<T> &pa, const Point2<T> &pb) {
    return Point2<T>(min(pa.x, pb.x), min(pa.y, pb.y));
}

template <typename T>
inline Point2<T> max(const Point2<T> &pa, const Point2<T> &pb) {
    return Point2<T>(max(pa.x, pb.x), max(pa.y, pb.y));
}

template <typename T>
inline Point3<T> permute(const Point3<T> &p, int x, int y, int z) {
    return Point3<T>(p[x], p[y], p[z]);
}

template <typename T>
inline Normal3<T> normalize(const Normal3<T> &n) {
    return n / n.length();
}

template <typename T>
inline T dot(const Normal3<T> &n1, const Vector3<T> &v2) {
    return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
}

template <typename T>
inline T dot(const Vector3<T> &v1, const Normal3<T> &n2) {
    return v1.x * n2.x + v1.y * n2.y + v1.z * n2.z;
}

template <typename T>
inline T dot(const Normal3<T> &n1, const Normal3<T> &n2) {
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T>
inline T absDot(const Normal3<T> &n1, const Vector3<T> &v2) {
    return abs(n1.x * v2.x + n1.y * v2.y + n1.z * v2.z);
}

template <typename T>
inline T absDot(const Vector3<T> &v1, const Normal3<T> &n2) {
    return abs(v1.x * n2.x + v1.y * n2.y + v1.z * n2.z);
}

template <typename T>
inline T absDot(const Normal3<T> &n1, const Normal3<T> &n2) {
    return abs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
}

template <typename T>
inline Normal3<T> faceforward(const Normal3<T> &n, const Vector3<T> &v) {
    return (dot(n, v) < 0.f) ? -n : n;
}

template <typename T>
inline Normal3<T> faceforward(const Normal3<T> &n, const Normal3<T> &n2) {
    return (dot(n, n2) < 0.f) ? -n : n;
}

template <typename T>
inline Vector3<T> faceforward(const Vector3<T> &v, const Vector3<T> &v2) {
    return (dot(v, v2) < 0.f) ? -v : v;
}

template <typename T>
inline Vector3<T> faceforward(const Vector3<T> &v, const Normal3<T> &n2) {
    return (dot(v, n2) < 0.f) ? -v : v;
}

template <typename T>
inline Normal3<T> abs(const Normal3<T> &v) {
    return Normal3<T>(abs(v.x), abs(v.y), abs(v.z));
}

}

#endif // VECTOR_H
