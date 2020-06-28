#include <Texture.h>

Color CheckerTexture::value(double u, double v, const Point3& point) const {
	const double sines = sin(10 * point.x()) * sin(10 * point.y()) * sin(10 * point.z());
	return sines < 0 ? _oddTexture->value(u, v, point) : _evenTexture->value(u, v, point);
}
