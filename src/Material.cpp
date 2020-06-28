#include <Material.h>

double schlick(double cos, double refIdx) {
	double r0 = (1.0 - refIdx) / (1.0 + refIdx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cos), 5);
}


bool Lambertian::scatter(const Ray& rayIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
	const Vec3 scatterDirection = rec.normal + randomUnitVec3();
	scattered = Ray(rec.point, scatterDirection, rayIn.time());
	attenuation = _albedoPtr->value(rec.u, rec.v, rec.point);
	return true;
}

bool Metal::scatter(const Ray& rayIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
	const Vec3 reflected = reflect(unitVec3(rayIn.direction()), rec.normal);
	scattered = Ray(rec.point, reflected + _fuzz * randomVec3InUnitSphere());
	attenuation = _albedo;
	return (dot(scattered.direction(), rec.normal) > 0.0);
}

bool Dielectric::scatter(const Ray& rayIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
	attenuation = Vec3(1.0, 1.0, 1.0);
	const double etaOverEtaPrime = rec.isFrontFace ? 1.0 / _refIdx : _refIdx;	// 1.0 for air

	const Vec3 unitDirection = unitVec3(rayIn.direction());
	const double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
	const double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
	if (etaOverEtaPrime * sinTheta > 1.0) {
		// must reflect
		const Vec3 reflected = reflect(unitDirection, rec.normal);
		scattered = Ray(rec.point, reflected);
		return true;
	} else {
		// can refract
		const double reflectProb = schlick(cosTheta, etaOverEtaPrime);
		if (randomDouble() < reflectProb) {
			const Vec3 reflected = reflect(unitDirection, rec.normal);
			scattered = Ray(rec.point, reflected);
			return true;
		} else {
			const Vec3 refracted = refract(unitDirection, rec.normal, etaOverEtaPrime);
			scattered = Ray(rec.point, refracted);
			return true;
		}
	}
}