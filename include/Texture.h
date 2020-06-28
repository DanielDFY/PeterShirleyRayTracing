#pragma once

#include <Color.h>
#include <Point3.h>
#include <Perlin.h>

class Texture {
public:
	virtual Color value(double u, double v, const Point3& point) const = 0;
};

class SolidColor : public Texture {
public:
	SolidColor() = default;
	SolidColor(const Color& color) : _colorValue(color) {}
	SolidColor(double red, double green, double blue)
		: SolidColor(Color(red, green, blue)) {}

	Color value(double u, double v, const Point3& point) const override {
		return _colorValue;
	}

private:
	Color _colorValue;
};

class CheckerTexture : public Texture {
public:
	CheckerTexture() = default;
	CheckerTexture(std::shared_ptr<Texture> oddTexture, std::shared_ptr<Texture> evenTexture)
		: _oddTexture(std::move(oddTexture)), _evenTexture(std::move(evenTexture)) { }

	Color value(double u, double v, const Point3& point) const override;
	
private:
	std::shared_ptr<Texture> _oddTexture;
	std::shared_ptr<Texture> _evenTexture;
};

class NoiseTexture : public Texture {
public:
	NoiseTexture() = default;
	NoiseTexture(double scale) : _scale(scale) {}

	Color value(double u, double v, const Point3& p) const override {
		return Color(1.0, 1.0, 1.0) * 0.5 * (1.0 + sin(_scale * p.z() + 10.0 * _noise.turb(p)));
	}

private:
	Perlin _noise;
	double _scale;
};