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