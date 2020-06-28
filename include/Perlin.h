#pragma once

#include <Point3.h>

class Perlin {
public:
	Perlin();
	~Perlin();

	double noise(const Point3& p) const;
	double turb(const Point3& p, int depth = 7) const;

private:
	static const int _pointCount = 256;
	Vec3* _ranVecList;
	int* _permX;
	int* _permY;
	int* _permZ;

	static int* perlinGeneratePerm();

	static void permute(int* p, int n);

	inline static double perlinInterp(Vec3 c[2][2][2], double u, double v, double w);
};