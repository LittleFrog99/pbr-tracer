#ifndef UTILITY_COMMON
#define UTILITY_COMMON

/* Common Included Headers */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <glog/logging.h>

/* Macros */
#ifndef DOUBLE_AS_FLOAT
typedef float Float;
#else
typedef double Float;
#endif

#define SQ(x) (x) * (x)
#define ALLOCA(TYPE, COUNT) (TYPE *)alloca((COUNT) * sizeof(TYPE))

/* Type Definitions */
class RGBSpectrum;
class SampledSpectrum;
typedef RGBSpectrum Spectrum;
// typedef SampledSpectrum Spectrum;
class ParamSet;

using namespace std;

struct Options {
    Options() {
        cropWindow[0][0] = 0;
        cropWindow[0][1] = 1;
        cropWindow[1][0] = 0;
        cropWindow[1][1] = 1;
    }
    int nThreads = 0;
    bool quickRender = false;
    bool quiet = false;
    bool cat = false, toPly = false;
    string imageFile;
    // x0, x1, y0, y1
    Float cropWindow[2][2];
};

namespace Math {

/* Global Constants */
static constexpr Float PI = 3.14159265358979323846;
static constexpr Float INV_PI = 0.31830988618379067154;
static constexpr Float INV_TWO_PI = 0.15915494309189533577;
static constexpr Float INV_FOUR_PI = 0.07957747154594766788;
static constexpr Float PI_OVER_TWO = 1.57079632679489661923;
static constexpr Float PI_OVER_FOUR = 0.78539816339744830961;
static constexpr Float SQRT_TWO = 1.41421356237309504880;
static constexpr Float MACHINE_EPSILON = numeric_limits<Float>::epsilon() * 0.5;
static constexpr Float SHADOW_EPSILON = 0.0001f;

/* Utility Inline Funtions */
template <class T, class U, class V>
inline T clamp(T value, U low, V high) {
    if (value < low) return low;
    else if (value > high) return high;
    else return value;
}

template <class T>
inline T mod(T a, T b) {
    T result = a - (a/b) * b;
    return T(result < 0 ? (result + b) : result);
}

inline Float mod(Float a, Float b) {
    return fmod(a, b);
}

inline Float radians(Float degrees) {
    return (PI / 180) * degrees;
}

inline Float degrees(Float radians) {
    return (180 / PI) * radians;
}

inline uint32_t floatToBits(float f) {
    uint32_t ui;
    memcpy(&ui, &f, sizeof(float));
    return ui;
}

inline float bitsToFloat(uint32_t ui) {
    float f;
    memcpy(&f, &ui, sizeof(uint32_t));
    return f;
}

inline uint64_t floatToBits(double f) {
    uint64_t ui;
    memcpy(&ui, &f, sizeof(double));
    return ui;
}

inline double bitsToFloat(uint64_t ui) {
    double f;
    memcpy(&f, &ui, sizeof(uint64_t));
    return f;
}

inline float nextFloatUp(float v) {
    if (isinf(v) && v > 0.0f) return v;
    if (v == -0.0f) v = 0.0f;
    uint32_t ui = floatToBits(v);
    if (v >= 0.0f)
        ++ui;
    else
        --ui;
    return bitsToFloat(ui);
}

inline float nextFloatDown(float v) {
    // Handle infinity and positive zero for _NextFloatDown()_
    if (isinf(v) && v < 0.) return v;
    if (v == 0.f) v = -0.f;
    uint32_t ui = floatToBits(v);
    if (v > 0)
        --ui;
    else
        ++ui;
    return bitsToFloat(ui);
}

inline double nextFloatUp(double v, int delta = 1) {
    if (isinf(v) && v > 0.) return v;
    if (v == -0.0) v = 0.0;
    uint64_t ui = floatToBits(v);
    if (v >= 0.)
        ui += delta;
    else
        ui -= delta;
    return bitsToFloat(ui);
}

inline double nextFloatDown(double v, int delta = 1) {
    if (isinf(v) && v < 0.) return v;
    if (v == 0.f) v = -0.f;
    uint64_t ui = floatToBits(v);
    if (v > 0.)
        ui -= delta;
    else
        ui += delta;
    return bitsToFloat(ui);
}

inline constexpr Float gamma(int n) {
    return (n * MACHINE_EPSILON) / (1 - n * MACHINE_EPSILON);
}

inline Float log2(Float x) {
    static const Float invLog2 = 1.442695040888963387004650940071;
    return log(x) * invLog2;
}

inline int log2Int(uint32_t v) {
    return 31 - __builtin_clz(v);
}

template <typename T>
inline constexpr bool isPowerOf2(T v) {
    return v && !(v & (v - 1));
}

inline int32_t roundUpPow2(int32_t v) {
    v--;
    v |= v >> 1; v |= v >> 2;
    v |= v >> 4; v |= v >> 8;
    v |= v >> 16;
    return v + 1;
}

inline int64_t roundUpPow2(int64_t v) {
    v--;
    v |= v >> 1; v |= v >> 2;
    v |= v >> 4; v |= v >> 8;
    v |= v >> 16; v |= v >> 32;
    return v + 1;
}

inline int countTrailingZeros(uint32_t v) {
    return __builtin_ctz(v);
}

inline int findInterval(int size, function<bool(int)> compare) {
    int first = 0, length = size;
    while (length > 0) {
        int half = length >> 1, middle = first + half;
        if (compare(middle)) {
            first = middle + 1;
            length -= half + 1;
        } else
            length = half;
    }
    return clamp(first - 1, 0, size - 2);
}

template <class T>
inline T lerp(Float t, T v1, T v2) {
    return (1 - t) * v1 + t * v2;
}

inline bool solveQuadratic(Float a, Float b, Float c, Float *t0, Float *t1) {
    Float discr = b * b - 4.0 * a * c;
    if (discr < 0) return false;
    Float rtDiscr = sqrt(discr);
    Float q;
    if (b < 0) q = -.5 * (b - rtDiscr);
    else q = -.5 * (b + rtDiscr);
    *t0 = q / a;
    *t1 = c / q;
    if (*t0 > *t1) swap(*t0, *t1);
    return true;
}

inline bool solveLinear2x2(const Float A[2][2], const Float B[2], Float *x0, Float *x1) {
    Float det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    if (std::abs(det) < 1e-10f) return false;
    *x0 = (A[1][1] * B[0] - A[0][1] * B[1]) / det;
    *x1 = (A[0][0] * B[1] - A[1][0] * B[0]) / det;
    if (isnan(*x0) || isnan(*x1)) return false;
    return true;
}

}

using namespace Math;

#endif // UTILITY_COMMON
