#pragma once

#include <Ray.h>
#include <Hittable.h>
#include <Color.h>
#include <Texture.h>

double schlick(double cos, double refIdx);

class Material {
public:
	Material() = default;
	Material(const Material&) = default;
	Material(Material&&) noexcept = default;
	Material& operator=(const Material&) = default;
	Material& operator=(Material&&) noexcept = default;
	virtual ~Material() = default;
	
	virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
	virtual Color emitted(double u, double v, const Point3& point) const {
		return { 0.0, 0.0, 0.0 };
	}
};

class Lambertian : public Material{
public:
	Lambertian(std::shared_ptr<Texture> albedoPtr) : _albedoPtr(std::move(albedoPtr)) {}
	Lambertian(const Color& albedo) : Lambertian(std::make_shared<SolidColor>(albedo)) {}

	bool scatter(const Ray& rayIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;
	
private:
	std::shared_ptr<Texture> _albedoPtr;
};

class Metal : public Material {
public:
	Metal(const Color& albedo, double fuzz) : _albedo(albedo), _fuzz(fuzz < 1.0 ? fuzz :1.0) {}

	bool scatter(const Ray& rayIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;

private:
	Color _albedo;
	double _fuzz;
};

class Dielectric : public Material {
public:
	Dielectric(double refIdx) : _refIdx(refIdx) {}

	bool scatter(const Ray& rayIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;

private:
	double _refIdx;
};

class DiffuseLight : public Material {
public:
	DiffuseLight(std::shared_ptr<Texture> emitTex) : _emitTex(emitTex) {}
	DiffuseLight(Color color) : _emitTex(std::make_shared<SolidColor>(color)) {}

	bool scatter(const Ray& rayIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override {
		return false;
	}

	Color emitted(double u, double v, const Point3& point) const override {
		return _emitTex->value(u, v, point);
	}

private:
	std::shared_ptr<Texture> _emitTex;
};