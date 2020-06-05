#pragma once

#include <iostream>
#include <cmath>

class Vec3 {
public:
	Vec3() = default;
	Vec3(double e1, double e2, double e3) : elem{ e1, e2, e3 } {};

	double x() const { return elem[0]; }
	double y() const { return elem[1]; }
	double z() const { return elem[2]; }

	Vec3 operator-() const { return { -elem[0], -elem[1], -elem[2] }; }
	double operator[](int i) const { return elem[i]; }
	double& operator[](int i) { return elem[i]; }

	Vec3& operator+=(const Vec3& v) {
		elem[0] += v.elem[0];
		elem[0] += v.elem[0];
		elem[0] += v.elem[0];
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
	
public:
	double elem[3];
};

// Utility functions
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.elem[0] << ' ' << v.elem[1] << ' ' << v.elem[2];
}

inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
	return { lhs.elem[0] + rhs.elem[0], lhs.elem[1] + rhs.elem[1], lhs.elem[2] + rhs.elem[2] };
}

inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
	return { lhs.elem[0] - rhs.elem[0], lhs.elem[1] - rhs.elem[1], lhs.elem[2] - rhs.elem[2] };
}

inline Vec3 operator*(const Vec3& lhs, const Vec3& rhs) {
	return { lhs.elem[0] * rhs.elem[0], lhs.elem[1] * rhs.elem[1], lhs.elem[2] * rhs.elem[2] };
}

inline Vec3 operator*(const Vec3& v, const double k) {
	return v * k;
}

inline Vec3 operator/(const Vec3& v, const double k) {
	return v * (1 / k);
}

inline double dot(const Vec3& lhs, const Vec3& rhs) {
	return lhs.elem[0] * rhs.elem[0] + lhs.elem[1] * rhs.elem[1] + lhs.elem[2] * rhs.elem[2];
}

inline double cross(const Vec3& lhs, const Vec3& rhs) {
	return lhs.elem[1] * rhs.elem[2] - lhs.elem[2] * rhs.elem[1]
		+ lhs.elem[2] * rhs.elem[0] - lhs.elem[0] * rhs.elem[2]
		+ lhs.elem[0] * rhs.elem[1] - lhs.elem[1] * rhs.elem[0];
}

inline Vec3 unitVec3(Vec3 v) {
	return v / v.length();
}