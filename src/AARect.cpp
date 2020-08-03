#include <AARect.h>

bool XYRect::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
	const double t = (_k - r.origin().z()) / r.direction().z();
	if (t < tMin || t > tMax)
		return false;
	const double x = r.origin().x() + t * r.direction().x();
	const double y = r.origin().y() + t * r.direction().y();
	if (x < _x0 || x > _x1 || y < _y0 || y > _y1)
		return false;
	rec.u = (x - _x0) / (_x1 - _x0);
	rec.v = (y - _y0) / (_y1 - _y0);
	rec.t = t;

	const Vec3 outwardNormal(0.0, 0.0, 1.0);
	rec.setFaceNormal(r, outwardNormal);
	rec.matPtr = _matPtr;
	rec.point = r.at(t);
	return true;
}

bool XZRect::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
	const double t = (_k - r.origin().y()) / r.direction().y();
	if (t < tMin || t > tMax)
		return false;
	const double x = r.origin().x() + t * r.direction().x();
	const double z = r.origin().z() + t * r.direction().z();
	if (x < _x0 || x > _x1 || z < _z0 || z > _z1)
		return false;
	rec.u = (x - _x0) / (_x1 - _x0);
	rec.v = (z - _z0) / (_z1 - _z0);
	rec.t = t;

	const Vec3 outwardNormal(0.0, 1.0, 0.0);
	rec.setFaceNormal(r, outwardNormal);
	rec.matPtr = _matPtr;
	rec.point = r.at(t);
	return true;
}

bool YZRect::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
	const double t = (_k - r.origin().x()) / r.direction().x();
	if (t < tMin || t > tMax)
		return false;
	const double y = r.origin().y() + t * r.direction().y();
	const double z = r.origin().z() + t * r.direction().z();
	if (y < _y0 || y > _y1 || z < _z0 || z > _z1)
		return false;
	rec.u = (y - _y0) / (_y1 - _y0);
	rec.v = (z - _z0) / (_z1 - _z0);
	rec.t = t;

	const Vec3 outwardNormal(1.0, 0.0, 0.0);
	rec.setFaceNormal(r, outwardNormal);
	rec.matPtr = _matPtr;
	rec.point = r.at(t);
	return true;
}