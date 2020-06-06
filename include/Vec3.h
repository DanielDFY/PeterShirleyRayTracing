#pragma once

#include <iostream>
#include <cmath>

class Vec3 {
public:
	Vec3() = default;
	Vec3(double e1, double e2, double e3) : elem{ e1, e2, e3 } {}

	double x() const { return elem[0]; }
	double y() const { return elem[1]; }
	double z() const { return elem[2]; }

	Vec3 operator-() const { return { -elem[0], -elem[1], -elem[2] }; }
	double operator[](int i) const { return elem[i]; }
	double& operator[](int i) { return elem[i]; }

	Vec3& operator+=(const Vec3& v) {
		elem[0] += v.elem[0];
		elem[1] += v.elem[1];
		elem[2] += v.elem[1];
		return *this;
	}

	Vec3& operator*=(const double k) {
		elem[0] *= k;
		elem[1] *= k;
		elem[2] *= k;
		return *this;
	}

	Vec3& operator/=(const double k) {
		return *this *= 1 / k;
	}

	double lengthSquared() const {
		return elem[0] * elem[0] + elem[1] * elem[1] + elem[2] * elem[2];
	}

	double length() const {
		return sqrt(lengthSquared());
	}
	
protected:
	double elem[3];
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

inline double cross(const Vec3& lhs, const Vec3& rhs) {
	return lhs.y() * rhs.z() - lhs.z() * rhs.y()
		+ lhs.z() * rhs.x() - lhs.x() * rhs.z()
		+ lhs.x() * rhs.y() - lhs.y() * rhs.x();
}

inline Vec3 unitVec3(Vec3 v) {
	return v / v.length();
}