#pragma once

#include <cmath>

#include <Hittable.h>
#include <helperUtils.h>

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

inline void getSphereUV(const Point3& point, double& u, double& v) {
	const double phi = atan2(point.z(), point.x());
	const double theta = asin(point.y());
	u = 0.5 - phi / (2 * M_PI);		// 1-(phi + M_PI) / (2*M_PI);
	v = theta / M_PI + 0.5;			// (theta + M_PI/2) / M_PI;
}