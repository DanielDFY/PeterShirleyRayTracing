#pragma once
#include <limits>

constexpr double DOUBLE_INFINITY = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double degreeToRadian(const double degree) { return degree * PI / 180.0; }