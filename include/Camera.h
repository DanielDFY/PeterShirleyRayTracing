#pragma once

#include <Ray.h>

class Camera {
public:
	Camera() {
		const double aspectRatio = 16.0 / 9.0;
		const double viewportHeight = 2.0;
		const double viewportWidth = aspectRatio * viewportHeight;
		const double focalLength = 1.0;

		_origin = Point3(0.0, 0.0, 0.0);
		_horizontal = Vec3(viewportWidth, 0.0, 0.0);
		_vertical = Vec3(0.0, viewportHeight, 0.0);
		_lowerLeftCorner = _origin - _horizontal / 2 - _vertical / 2 - Vec3(0.0, 0.0, focalLength);
	}

	Ray getRay(double u, double v) const {
		return { _origin, _lowerLeftCorner + u * _horizontal + v * _vertical - _origin };
	}

private:
	Point3 _origin;
	Point3 _lowerLeftCorner;
	Vec3 _horizontal;
	Vec3 _vertical;
};