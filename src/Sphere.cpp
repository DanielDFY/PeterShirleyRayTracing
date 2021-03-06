#include <Sphere.h>

bool Sphere::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
	const Vec3 oc = r.origin() - _center;
	const double a = r.direction().lengthSquared();
	const double bHalf = dot(oc, r.direction());
	const double c = oc.lengthSquared() - radius() * radius();
	const double discriminant = bHalf * bHalf - a * c;

	if (discriminant > 0) {
		const double root = sqrt(discriminant);
		double t = (-bHalf - root) / a;
		if (t > tMin && t < tMax) {
			rec.t = t;
			rec.point = r.at(t);
			const Vec3 outwardNormal = (rec.point - _center) / _radius;
			rec.setFaceNormal(r, outwardNormal);
			getSphereUV((rec.point - _center) / _radius, rec.u, rec.v);
			rec.matPtr = _matPtr;
			return true;
		}
		t = (-bHalf + root) / a;
		if (t > tMin && t < tMax) {
			rec.t = t;
			rec.point = r.at(t);
			const Vec3 outwardNormal = (rec.point - _center) / _radius;
			rec.setFaceNormal(r, outwardNormal);
			getSphereUV((rec.point - _center) / _radius, rec.u, rec.v);
			rec.matPtr = _matPtr;
			return true;
		}
	}

	return false;
}

bool Sphere::boundingBox(double t0, double t1, AABB& outputBox) const {
	const Vec3 halfVec(_radius, _radius, _radius);
	
	outputBox = AABB(
		_center - halfVec,
		_center + halfVec
	);
	
	return true;
}
