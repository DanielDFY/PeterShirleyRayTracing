#include<MovingSphere.h>

bool MovingSphere::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
	const Vec3 oc = r.origin() - center(r.time());
	const double a = r.direction().lengthSquared();
	const double bHalf = dot(oc, r.direction());
	const double c = oc.lengthSquared() - _radius * _radius;

	const double discriminant = bHalf * bHalf - a * c;

	if (discriminant > 0.0) {
		const double root = sqrt(discriminant);

		double temp = (-bHalf - root) / a;
		if (temp > tMin && temp < tMax) {
			rec.t = temp;
			rec.point = r.at(rec.t);
			const Vec3 outwardNormal = (rec.point - center(r.time())) / _radius;
			rec.setFaceNormal(r, outwardNormal);
			rec.matPtr = _matPtr;
			return true;
		}

		temp = (-bHalf + root) / a;
		if (temp < tMax && temp > tMin) {
			rec.t = temp;
			rec.point = r.at(rec.t);
			const Vec3 outwardNormal = (rec.point - center(r.time())) / _radius;
			rec.setFaceNormal(r, outwardNormal);
			rec.matPtr = _matPtr;
			return true;
		}
	}
	return false;
}
