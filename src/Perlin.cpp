#include <Perlin.h>

#include <cmath>

Perlin::Perlin() {
	_ranVecList = new Vec3[_pointCount];
	for (int i = 0; i < _pointCount; ++i) {
		_ranVecList[i] = unitVec3(Vec3::random(-1.0, 1.0));
	}

	_permX = perlinGeneratePerm();
	_permY = perlinGeneratePerm();
	_permZ = perlinGeneratePerm();
}

Perlin::~Perlin() {
	delete[] _ranVecList;
	delete[] _permX;
	delete[] _permY;
	delete[] _permZ;
}

double Perlin::noise(const Point3& p) const {
	const double u = p.x() - floor(p.x());
	const double v = p.y() - floor(p.y());
	const double w = p.z() - floor(p.z());

	const auto i = static_cast<int>(floor(p.x()));
	const auto j = static_cast<int>(floor(p.y()));
	const auto k = static_cast<int>(floor(p.z()));

	Vec3 c[2][2][2];

	for (int di = 0; di < 2; ++di)
		for (int dj = 0; dj < 2; ++dj)
			for (int dk = 0; dk < 2; ++dk)
				c[di][dj][dk] = _ranVecList[
					_permX[(i + di) & 255] ^
					_permY[(j + dj) & 255] ^
					_permZ[(k + dk) & 255]
				];

	return perlinInterp(c, u, v, w);
}

double Perlin::turb(const Point3& p, int depth) const {
	double accum = 0.0;
	Point3 tempPoint = p;
	double weight = 1.0;

	for (int i = 0; i < depth; ++i) {
		accum += weight * noise(tempPoint);
		weight *= 0.5;
		tempPoint *= 2;
	}

	return fabs(accum);
}

int* Perlin::perlinGeneratePerm() {
	const auto p = new int[_pointCount];

	for (int i = 0; i < _pointCount; ++i) {
		p[i] = i;
	}

	permute(p, _pointCount);

	return p;
}

void Perlin::permute(int* p, int n) {
	for (int i = n - 1; i > 0; --i) {
		int target = randomInt(0, i);
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
}

inline double Perlin::perlinInterp(Vec3 c[2][2][2], double u, double v, double w) {
	const double uu = u * u * (3 - 2 * u);
	const double vv = v * v * (3 - 2 * v);
	const double ww = w * w * (3 - 2 * w);
	double accum = 0.0;

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k) {
				Vec3 weightVec(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu))
					* (j * vv + (1 - j) * (1 - vv))
					* (k * ww + (1 - k) * (1 - ww))
					* dot(c[i][j][k], weightVec);
			}


	return accum;
}