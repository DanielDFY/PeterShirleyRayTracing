#pragma once

#include <Hittable.h>

#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
	HittableList() = default;
	HittableList(const std::shared_ptr<Hittable>& object) { add(object); }

	void add(const std::shared_ptr<Hittable>& object) { _objects.push_back(object); }
	void clear() { _objects.clear(); }
	std::vector<std::shared_ptr<Hittable>>& objects() { return _objects; }
	
	bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
	bool boundingBox(double t0, double t1, AABB& outputBox) const override;

private:
	std::vector<std::shared_ptr<Hittable>> _objects;
};