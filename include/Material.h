#pragma once

#include <Ray.h>
#include <Hittable.h>
#include <Color.h>

class Material {
public:
	Material() = default;
	Material(const Material&) = default;
	Material(Material&&) noexcept = default;
	Material& operator=(const Material&) = default;
	Material& operator=(Material&&) noexcept = default;
	virtual ~Material() = default;
	
	virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material{
public:
	Lambertian(const Color& a) : _albedo(a) {}

	bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
	
private:
	Color _albedo;
};

class Metal : public Material {
public:
	Metal(const Color& albedo, double fuzz) : _albedo(albedo), _fuzz(fuzz < 1.0 ? fuzz :1.0) {}

	bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	Color _albedo;
	double _fuzz;
};