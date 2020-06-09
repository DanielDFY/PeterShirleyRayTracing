#include <Vec3.h>

Vec3 randomVec3InUnitSphere() {
	while (true) {
		const Vec3 p = Vec3::random(-1, 1);
		if (p.lengthSquared() >= 1) continue;
		return p;
	}
}

Vec3 randomUnitVec3() {
	const auto a = randomDouble(0.0, 2.0 * M_PI);
	const auto z = randomDouble(-1.0, 1.0);
	const auto r = sqrt(1.0 - z * z);
	return { r * cos(a), r * sin(a), z };
}

Vec3 randomVec3InHemisphere(const Vec3& normal) {
	const Vec3 vec3InUnitSphere = randomVec3InUnitSphere();
	if (dot(vec3InUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
		return vec3InUnitSphere;
	else
		return -vec3InUnitSphere;
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2.0 * dot(v, n) * n;
}