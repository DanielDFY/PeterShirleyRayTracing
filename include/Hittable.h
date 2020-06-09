#pragma once

#include <Ray.h>
class Material;

struct HitRecord {
	Point3 point;
	Vec3 normal;
	std::shared_ptr<Material> matPtr;
	double t;
	bool isFrontFace;

	void setFaceNormal(const Ray& r, const Vec3& outwardNormal) {
		isFrontFace = dot(r.direction(), outwardNormal) < 0;
		normal = isFrontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	Hittable() = default;
	Hittable(const Hittable&) = default;
	Hittable(Hittable&&) noexcept = default;
	Hittable& operator=(const Hittable&) = default;
	Hittable& operator=(Hittable&&) noexcept = default;
	virtual ~Hittable() = default;
	
	virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};