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

AABB surroundingBox(AABB box0, AABB box1) {
    const Point3 smallPoint(fmin(box0.minPoint().x(), box1.minPoint().x()),
        fmin(box0.minPoint().y(), box1.minPoint().y()),
        fmin(box0.minPoint().z(), box1.minPoint().z()));

    const Point3 bigPoint(fmax(box0.maxPoint().x(), box1.maxPoint().x()),
        fmax(box0.maxPoint().y(), box1.maxPoint().y()),
        fmax(box0.maxPoint().z(), box1.maxPoint().z()));

    return { smallPoint, bigPoint };
}
