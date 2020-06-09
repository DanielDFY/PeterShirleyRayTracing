#include <Material.h>

bool Lambertian::scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
	const Vec3 scatterDirection = rec.normal + randomUnitVec3();
	scattered = Ray(rec.point, scatterDirection);
	attenuation = _albedo;
	return true;
}

bool Metal::scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
	const Vec3 reflected = reflect(unitVec3(rayIn.direction()), rec.normal);
	scattered = Ray(rec.point, reflected + _fuzz * randomVec3InUnitSphere());
	attenuation = _albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}