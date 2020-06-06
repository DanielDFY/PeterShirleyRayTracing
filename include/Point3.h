#pragma once

#include <Vec3.h>

class Point3 : public Vec3 {
public:
	Point3() = default;
	Point3(double e1, double e2, double e3) : Vec3(e1, e2, e3) {}
	Point3(Vec3 v) : Point3(v.x(), v.y(), v.z()) {}

	Point3& operator+=(const Vec3& v) {
		elem[0] += v.x();
		elem[1] += v.y();
		elem[2] += v.z();
		return *this;
	}
};