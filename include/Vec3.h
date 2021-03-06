#pragma once

#include <iostream>
#include <cmath>

#include <helperUtils.h>

class Vec3 {
public:
	Vec3() = default;
	Vec3(double e1, double e2, double e3) : _elem{ e1, e2, e3 } {}

	double x() const { return _elem[0]; }
	double y() const { return _elem[1]; }
	double z() const { return _elem[2]; }

	double elem(size_t i) const { return _elem[i]; }

	Vec3 operator-() const { return { -_elem[0], -_elem[1], -_elem[2] }; }
	double operator[](int i) const { return _elem[i]; }
	double& operator[](int i) { return _elem[i]; }

	Vec3& operator+=(const Vec3& rhs) {
		_elem[0] += rhs._elem[0];
		_elem[1] += rhs._elem[1];
		_elem[2] += rhs._elem[2];
		return *this;
	}

	Vec3& operator*=(const double k) {
		_elem[0] *= k;
		_elem[1] *= k;
		_elem[2] *= k;
		return *this;
	}

	Vec3& operator/=(const double k) {
		return *this *= 1 / k;
	}

	double lengthSquared() const {
		return _elem[0] * _elem[0] + _elem[1] * _elem[1] + _elem[2] * _elem[2];
	}

	double length() const {
		return sqrt(lengthSquared());
	}

	inline static Vec3 random() {
		return Vec3(randomDouble(), randomDouble(), randomDouble());
	}

	inline static Vec3 random(double min, double max) {
		return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}
	
protected:
	double _elem[3];
};

// Utility functions
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
	return { lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() };
}

inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
	return { lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z() };
}

inline Vec3 operator*(const Vec3& lhs, const Vec3& rhs) {
	return { lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z() };
}

inline Vec3 operator*(const double k, const Vec3& v) {
	return { k * v.x(), k * v.y(), k * v.z() };
}

inline Vec3 operator*(const Vec3& v, const double k) {
	return k * v;
}

inline Vec3 operator/(const Vec3& v, const double k) {
	return (1 / k) * v;
}

inline double dot(const Vec3& lhs, const Vec3& rhs) {
	return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

inline Vec3 cross(const Vec3& lhs, const Vec3& rhs) {
	return { lhs.y() * rhs.z() - lhs.z() * rhs.y(),
		lhs.z() * rhs.x() - lhs.x() * rhs.z(),
		lhs.x() * rhs.y() - lhs.y() * rhs.x() };
}

inline Vec3 unitVec3(Vec3 v) {
	return v / v.length();
}

Vec3 randomVec3InUnitSphere();

Vec3 randomUnitVec3();

Vec3 randomVec3InHemisphere(const Vec3& normal);

Vec3 randomVec3InUnitDisk();

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2.0 * dot(v, n) * n;
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etaOverEtaPrime);