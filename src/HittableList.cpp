#include <HittableList.h>

bool HittableList::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
	HitRecord tempRec;
	bool isHit = false;
	double closest = tMax;

	for (const auto& object : _objects) {
		if (object->hit(r, tMin, closest, tempRec)) {
			isHit = true;
			closest = tempRec.t;
			rec = tempRec;
		}
	}

	return isHit;
}

bool HittableList::boundingBox(double t0, double t1, AABB& outputBox) const {
	if (_objects.empty()) return false;

	AABB tempBox;
	bool isFirstBox = true;

	for (const auto& object : _objects) {
		if (!object->boundingBox(t0, t1, tempBox)) return false;
		outputBox = isFirstBox ? tempBox : surroundingBox(outputBox, tempBox);
		isFirstBox = false;
	}

	return true;
}
