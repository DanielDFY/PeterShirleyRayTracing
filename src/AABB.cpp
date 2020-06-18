#include <AABB.h>

bool AABB::hit(const Ray& r, double tMin, double tMax) const {
    for (int i = 0; i < 3; ++i) {
        const double invD = 1.0f / r.direction()[i];
        const double t0 = (_minPoint[i] - r.origin()[i]) * invD;
        const double t1 = (_maxPoint[i] - r.origin()[i]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        tMin = t0 > tMin ? t0 : tMin;
        tMax = t1 < tMax ? t1 : tMax;
        if (tMax <= tMin)
            return false;
    }
    return true;
}
