#pragma once

#include <Point3.h>
#include <Ray.h>

class AABB {
public:
	AABB() = default;
	AABB(const Point3& minPoint, const Point3& maxPoint)
		: _minPoint(minPoint), _maxPoint(maxPoint) {}

	Point3 minPoint() const { return _minPoint; }
	Point3 maxPoint() const { return _maxPoint; }

	bool hit(const Ray& r, double tMin, double tMax) const;

private:
	Point3 _minPoint;
	Point3 _maxPoint;
};