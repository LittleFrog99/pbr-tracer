#include "stratified.h"

using namespace Sampling;

void StratifiedSampler::startPixel(const Point2i &p) {
    // Generate single stratified samples
    for (size_t i = 0; i < samples1D.size(); i++) {
        sample1D(&samples1D[i][0], xPixelSamples * yPixelSamples, rng, jitterSamples);
        Sampling::shuffle(&samples1D[i][0], xPixelSamples * yPixelSamples, 1, rng);
    }
    for (size_t i = 0; i < samples2D.size(); i++) {
        sample2D(&samples2D[i][0], xPixelSamples, yPixelSamples, rng, jitterSamples);
        Sampling::shuffle(&samples2D[i][0], xPixelSamples * yPixelSamples, 1, rng);
    }

    // Generate arrays of stratified samples
    for (size_t i = 0; i < samples1DArraySizes.size(); i++)
        for (int64_t j = 0; j < samplesPerPixel; j++) {
            int count = samples1DArraySizes[i];
            sample1D(&sampleArray1D[i][j * count], count, rng, jitterSamples);
            Sampling::shuffle(&sampleArray1D[i][j * count], count, 1, rng);
        }
    for (size_t i = 0; i < samples2DArraySizes.size(); i++)
        for (int64_t j = 0; j < samplesPerPixel; j++) {
            int count = samples2DArraySizes[i];
            latinHypercube(&sampleArray2D[i][j * count].x, count, 2, rng);
        }

    PixelSampler::startPixel(p);
}

void StratifiedSampler::sample1D(Float *samples, int nSamples, Random &rng, bool jitter) {
    Float invNSamples = 1.0 / nSamples;
    for (int i = 0; i < nSamples; i++) {
        Float delta = jitter ? rng.uniformFloat() : 0.5f;
        samples[i] = min((i + delta) * invNSamples, Random::ONE_MINUS_EPSILON);
    }
}

void StratifiedSampler::sample2D(Point2f *samples, int nx, int ny, Random &rng, bool jitter) {
    Float dx = 1.0 / nx, dy = 1.0 / ny;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            Float jx = jitter ? rng.uniformFloat() : 0.5f;
            Float jy = jitter ? rng.uniformFloat() : 0.5f;
            samples->x = min((x + jx) * dx, Random::ONE_MINUS_EPSILON);
            samples->y = min((y + jy) * dy, Random::ONE_MINUS_EPSILON);
            ++samples;
        }
}

void StratifiedSampler::latinHypercube(Float *samples, int nSamples, int nDim, Random &rng) {
    // Generate LHS samples along diagonal
    Float invNSamples = 1.0 / nSamples;
    for (int i = 0; i < nSamples; i++)
        for (int j = 0; j < nDim; j++) {
            Float sj = (i + rng.uniformFloat()) * invNSamples;
            samples[nDim * i + j] = min(sj, Random::ONE_MINUS_EPSILON);
        }
    // Permute samples in each dimension
    for (int i = 0; i < nDim; i++)
        for (int j = 0; j < nSamples; j++) {
            int other = j + rng.uniformUInt32(nSamples - j);
            swap(samples[nDim * j + i], samples[nDim * other + i]); // permute each dimension's samples independently
        }
}
