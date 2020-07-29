#include <BVH.h>

#include <algorithm>
#include <functional>

BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end, double time0, double time1) {
	const int axis = randomInt(0, 2);

	const auto comparatorBase = (axis == 0) ? boxCompareX : (axis == 1) ? boxCompareY : boxCompareZ;
	const auto comparator = std::bind(comparatorBase, std::placeholders::_1, std::placeholders::_2, time0, time1);

	const size_t objectSpan = end - start;

	if (objectSpan == 1) {
		// The traversal algorithm should be smooth and not have to check for null pointers,
		// so if there is only one element, duplicate it in each subtree.
		_leftPtr = _rightPtr = objects[start];
	} else if (objectSpan == 2) {
		// There are only two elements
		const size_t secondIdx = start + 1;
		if (comparator(objects[start], objects[secondIdx])) {
			_leftPtr = objects[start];
			_rightPtr = objects[secondIdx];
		} else {
			_leftPtr = objects[secondIdx];
			_rightPtr = objects[start];
		}
	} else {
		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		const size_t mid = start + objectSpan / 2;
		_leftPtr = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
		_rightPtr = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
	}

	AABB boxLeft, boxRight;

	if (!_leftPtr->boundingBox(time0, time1, boxLeft) || !_rightPtr->boundingBox(time0, time1, boxRight))
		std::cerr << "No bounding box in BVHNode constructor." << std::endl;

	_boundingBox = surroundingBox(boxLeft, boxRight);
}

bool BVHNode::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
	if (!_boundingBox.hit(r, tMin, tMax))
		return false;

	const bool isLeftHit = _leftPtr->hit(r, tMin, tMax, rec);
	const bool isRightHit = _rightPtr->hit(r, tMin, isLeftHit ? rec.t : tMax, rec);

	return isLeftHit || isRightHit;
}

bool BVHNode::boundingBox(double t0, double t1, AABB& outputBox) const {
	outputBox = _boundingBox;
	return true;
}
