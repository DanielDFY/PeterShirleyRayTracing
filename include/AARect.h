#pragma once
#include <Hittable.h>

class XYRect : public Hittable {
public:
	XYRect() = default;
	XYRect(double x0, double x1, double y0, double y1, double k, std::shared_ptr<Material> matPtr)
		: _x0(x0), _x1(x1), _y0(y0), _y1(y1), _k(k), _matPtr(matPtr) { }

	bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
	bool boundingBox(double t0, double t1, AABB& outputBox) const override {
		// The bounding box must have non-zero width in each dimension, so pad the
		// Z dimension a small amount
		outputBox = AABB({ _x0, _y0, _k - 0.0001 }, { _x1, _y1, _k + 0.0001 });
		return true;
	}

private:
	std::shared_ptr<Material> _matPtr;
	double _x0, _x1, _y0, _y1, _k;
};

class XZRect : public Hittable {
public:
	XZRect() = default;
	XZRect(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Material> matPtr)
		: _x0(x0), _x1(x1), _z0(z0), _z1(z1), _k(k), _matPtr(matPtr) {
	}

	bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
	bool boundingBox(double t0, double t1, AABB& outputBox) const override {
		// The bounding box must have non-zero width in each dimension, so pad the
		// Y dimension a small amount
		outputBox = AABB({ _x0, _k - 0.0001, _z0 }, { _x1, _k + 0.0001, _z1 });
		return true;
	}

private:
	std::shared_ptr<Material> _matPtr;
	double _x0, _x1, _z0, _z1, _k;
};

class YZRect : public Hittable {
public:
	YZRect() = default;
	YZRect(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Material> matPtr)
		: _y0(y0), _y1(y1), _z0(z0), _z1(z1), _k(k), _matPtr(matPtr) {
	}

	bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
	bool boundingBox(double t0, double t1, AABB& outputBox) const override {
		// The bounding box must have non-zero width in each dimension, so pad the
		// X dimension a small amount
		outputBox = AABB({ _k - 0.0001, _y0, _z0 }, { _k + 0.0001, _y1, _z1 });
		return true;
	}

private:
	std::shared_ptr<Material> _matPtr;
	double _y0, _y1, _z0, _z1, _k;
};