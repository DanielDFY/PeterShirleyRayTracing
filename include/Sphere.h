#pragma once

#include <Hittable.h>

class Sphere : public Hittable {
public:
	Sphere() = delete;
	Sphere(Point3 center, double radius, std::shared_ptr<Material> matPtr = nullptr) :
	Hittable(), _center(center), _radius(radius), _matPtr(std::move(matPtr)) {}

	Point3 center() const { return _center; }
	double radius() const { return _radius; }
	std::shared_ptr<Material> matPtr() const { return _matPtr; };

	bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
	bool boundingBox(double t0, double t1, AABB& outputBox) const override;

private:
	Point3 _center;
	double _radius;
	std::shared_ptr<Material> _matPtr;
};