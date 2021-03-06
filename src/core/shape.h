#ifndef CORE_SHAPE
#define CORE_SHAPE

#include "bounds.h"
#include "interaction.h"
#include "transform.h"

class Shape {
public:
    Shape(const Transform *ObjToWorld, const Transform *WorldToObj, bool revOrient);

    virtual Bounds3f objectBound() const = 0;
    virtual Bounds3f worldBound() const { return (*objectToWorld)(objectBound()); }

    virtual bool intersect(const Ray &ray, float *tHit, SurfaceInteraction *isect,
                           bool testAlphaTexture = true) const = 0;
    virtual bool intersectP(const Ray &ray, bool testAlphaTexture = true) const {
        return intersect(ray, nullptr, nullptr, testAlphaTexture);
    }

    virtual float area() const = 0;

    virtual Interaction sample(const Point2f &u, float *pdf) const = 0;
    virtual float pdf(const Interaction &) const { return 1 / area(); }

    virtual Interaction sample(const Interaction &ref, const Point2f &u, float *pdf) const;
    virtual float pdf(const Interaction &ref, const Vector3f &wi) const;

    // virtual float solidAngle(const Point3f &p, int nSamples = 512) const;

    virtual ~Shape() {}

    const Transform *objectToWorld, *worldToObject;
    const bool reverseOrientation;
    const bool transformSwapsHandedness;
};

#endif // CORE_SHAPE
