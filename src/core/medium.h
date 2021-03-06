#ifndef CORE_MEDIUM
#define CORE_MEDIUM

#include "ray.h"
#include "spectrum.h"
#include "memory.h"
#include "stringprint.h"

struct MediumInteraction;
class Sampler;

class PhaseFunction {
public:
    virtual ~PhaseFunction() {}
    virtual float compute_p(const Vector3f &wo, const Vector3f &wi) const = 0;
    virtual float sample_p(const Vector3f &wo, Vector3f *wi, const Point2f &u) const = 0;
    virtual string toString() const = 0;
};

class HenyeyGreenstein : public PhaseFunction {
public:
    HenyeyGreenstein(float g) : g(g) {}

    float compute_p(const Vector3f &wo, const Vector3f &wi) const {
        return phase(dot(wo, wi), g);
    }

    float sample_p(const Vector3f &wo, Vector3f *wi, const Point2f &u) const;

    string toString() const {
        return STRING_PRINTF("[ HenyeyGreenstein g: %f ]", g);
    }

    inline static float phase(float cosTheta, float g) {
        float denom = 1 + g * g + 2 * g * cosTheta;
        return INV_FOUR_PI * (1 - g * g) / (denom * sqrt(denom));
    }

private:
    const float g;
};

class Medium {
public:
    virtual ~Medium() {}
    virtual Spectrum compute_Tr(const Ray &ray, Sampler &sampler) const = 0;
    virtual Spectrum sample(const Ray &ray, Sampler &sampler, MemoryArena &arena,
                            MediumInteraction *mi) const = 0;
    virtual Spectrum get_sigma_s(const MediumInteraction *mi) const = 0;
};

struct MediumInterface {
    MediumInterface() : inside(nullptr), outside(nullptr) {}
    MediumInterface(const Medium *medium) : inside(medium), outside(medium) {}
    MediumInterface(const Medium *inside, const Medium *outside)
        : inside(inside), outside(outside) {}

    bool isMediumTransition() const { return inside != outside; }

    const Medium *inside, *outside;
};

#endif // CORE_MEDIUM
