#pragma once

#include <Vec3.h>

class Point3 : public Vec3 {
public:
	Point3() : Vec3() {};
	Point3(double e1, double e2, double e3) : Vec3(e1, e2, e3) {};
};