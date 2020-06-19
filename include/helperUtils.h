#pragma once
#include <chrono>
#include <limits>
#include <random>

constexpr double M_DOUBLE_INFINITY = std::numeric_limits<double>::infinity();
constexpr double M_PI = 3.1415926535897932385;

inline double degreeToRadian(const double degree) { return degree * M_PI / 180.0; }

inline double randomDouble() {
    // returns a random real in [0,1)
    const auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    static std::mt19937 generator(seed);
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double randomDouble(double min, double max) {
    // returns a random real in [min,max)
    return min + (max - min) * randomDouble();
}

inline double randomInt(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(randomDouble(min, max + 1.0));
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}