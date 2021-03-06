#pragma once

#include <memory>
#include <vector>
#include <HittableList.h>

class BVHNode : public Hittable {
public:
	BVHNode() = default;
	BVHNode(HittableList& list, double time0, double time1)
		: BVHNode(list.objects(), 0, list.objects().size(), time0, time1) {}

	BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end, double time0, double time1);

	bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
	bool boundingBox(double t0, double t1, AABB& outputBox) const override;
	
private:
	std::shared_ptr<Hittable> _leftPtr;
	std::shared_ptr<Hittable> _rightPtr;
	AABB _boundingBox;
};

inline bool boxCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, int axis, double time0, double time1) {
	AABB boxA, boxB;
	
	if (!a->boundingBox(time0, time1, boxA) || !b->boundingBox(time0, time1, boxB))
		std::cerr << "No bounding box in BVHNode constructor." << std::endl;

	return boxA.minPoint().elem(axis) < boxB.minPoint().elem(axis);
}

inline bool boxCompareX(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, double time0, double time1) {
	return boxCompare(a, b, 0, time0, time1);
}

inline bool boxCompareY(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, double time0, double time1) {
	return boxCompare(a, b, 1, time0, time1);
}

inline bool boxCompareZ(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, double time0, double time1) {
	return boxCompare(a, b, 2, time0, time1);
}