#pragma once

#include <Ray.h>

class Camera {
public:
	Camera() = delete;
	Camera(const Point3& lookFrom, const Point3& lookAt, Vec3 vUp, double vFov, double aspectRatio);

	Ray getRay(double u, double v) const {
		return { _origin, _lowerLeftCorner + u * _horizontal + v * _vertical - _origin };
	}

private:
	Point3 _origin;
	Point3 _lowerLeftCorner;
	Vec3 _horizontal;
	Vec3 _vertical;
};