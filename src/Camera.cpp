#include <Camera.h>

Camera::Camera(
	const Point3& lookFrom,
	const Point3& lookAt,
	const Vec3& vUp,
	double vFov,
	double aspectRatio,
	double aperture,
	double focusDist) {
	
	const double theta = degreeToRadian(vFov);
	const double h = tan(theta / 2.0);
	const double viewportHeight = 2.0 * h;
	const double viewportWidth = aspectRatio * viewportHeight;
	
	_w = unitVec3(lookFrom - lookAt);
	_u = unitVec3(cross(vUp, _w));
	_v = cross(_w, _u);
	
	_origin = lookFrom;
	_horizontal = focusDist * viewportWidth * _u;
	_vertical = focusDist * viewportHeight * _v;
	_lowerLeftCorner = _origin - _horizontal / 2 - _vertical / 2 - focusDist * _w;
	_lensRadius = aperture / 2;
}

Ray Camera::getRay(double s, double t) const {
	const Vec3 rd = _lensRadius * randomVec3InUnitDisk();
	const Vec3 offset = _u * rd.x() + _v * rd.y();
	
	return { _origin + offset, _lowerLeftCorner + s * _horizontal + t * _vertical - _origin - offset };
}