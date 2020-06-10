#include <Camera.h>

Camera::Camera(const Point3& lookFrom, const Point3& lookAt, Vec3 vUp, double vFov, double aspectRatio) {
	const double theta = degreeToRadian(vFov);
	const double h = tan(theta / 2.0);
	const double viewportHeight = 2.0 * h;
	const double viewportWidth = aspectRatio * viewportHeight;
	
	const Vec3 w = unitVec3(lookFrom - lookAt);
	const Vec3 u = unitVec3(cross(vUp, w));
	const Vec3 v = cross(w, u);
	
	_origin = lookFrom;
	_horizontal = viewportWidth * u;
	_vertical = viewportHeight * v;
	_lowerLeftCorner = _origin - _horizontal / 2 - _vertical / 2 - w;
}