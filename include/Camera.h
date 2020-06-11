#pragma once

#include <Ray.h>

class Camera {
public:
	Camera(
		const Point3& lookFrom = { 0.0, 0.0, 0.0 },
		const Point3& lookAt = { 0.0, 0.0, -1.0 },
		const Vec3& vUp = { 0.0, 1.0, 0.0 },
		double vFov = 90,
		double aspectRatio = 16.0 / 9.0,
		double aperture = 0.0,
		double focusDist = 1.0
	);

	Ray getRay(double s, double t) const;

private:
	Point3 _origin;
	Point3 _lowerLeftCorner;
	Vec3 _horizontal;
	Vec3 _vertical;
	Vec3 _u, _v, _w;
	double _lensRadius;
};