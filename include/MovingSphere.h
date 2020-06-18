#pragma once

#include <Hittable.h>
#include <memory.h>

class MovingSphere : public Hittable {
public:
	MovingSphere() = default;
	MovingSphere(
		Point3 center0,
		Point3 center1,
		double time0,
		double time1,
		double radius,
		std::shared_ptr<Material> matPtr
	) : _center0(center0), _center1(center1),
	_time0(time0), _time1(time1), _radius(radius),
	_matPtr(std::move(matPtr)) { }

	bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;

	Point3 center(double time) const {
		return _center0 + ((time - _time0) / (_time1 - _time0)) * (_center1 - _center0);
	}

private:
	Point3 _center0, _center1;
	double _time0, _time1;
	double _radius;
	std::shared_ptr<Material> _matPtr;
};