#pragma once

#include <Hittable.h>

class Sphere : public Hittable {
public:
	Sphere() = delete;
	Sphere(Point3 center, double radius) : Hittable(), _center(center), _radius(radius) {}

	Point3 center() const { return _center; }
	double radius() const { return _radius; }

	bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;

private:
	Point3 _center;
	double _radius;
};