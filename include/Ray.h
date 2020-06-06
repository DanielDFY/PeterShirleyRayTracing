#pragma once

#include <Point3.h>
#include <Vec3.h>

class Ray {
public:
	Ray() = default;
	Ray(const Point3& origin, const Vec3& direction)
		: ori(origin), dir(direction) {}

	Point3 origin() const { return ori; }
	Vec3 direction() const { return dir; }

	Point3 at(double t) const { return ori + t * dir;}

private:
	Point3 ori;
	Vec3 dir;	// may not be unit length
};