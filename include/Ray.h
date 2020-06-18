#pragma once

#include <Point3.h>
#include <Vec3.h>

class Ray {
public:
	Ray() = default;
	Ray(const Point3& origin, const Vec3& direction, double time = 0.0)
		: _origin(origin), _direction(direction), _time(time) {}

	Point3 origin() const { return _origin; }
	Vec3 direction() const { return _direction; }
	double time() const { return _time; }

	Point3 at(double t) const { return _origin + t * _direction;}

private:
	Point3 _origin;
	Vec3 _direction;	// may not be unit length
	double _time;
};