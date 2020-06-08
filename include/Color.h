#pragma once

#include <Vec3.h>
#include <iostream>

class Color : public Vec3 {
public:
    Color() = default;
    Color(double e1, double e2, double e3) : Vec3(e1, e2, e3) {}
    Color(Vec3 v) : Color(v.x(), v.y(), v.z()) {}

    void clamp(int samplesPerPixel) {
        const double scale = 1.0 / static_cast<double>(samplesPerPixel);
        _elem[0] *= scale;
        _elem[1] *= scale;
        _elem[2] *= scale;
    }
	
    double r() const { return _elem[0]; }
    double g() const { return _elem[1]; }
    double b() const { return _elem[2]; }

    double r8bit() const { return 255 * _elem[0]; }
    double g8bit() const { return 255 * _elem[1]; }
    double b8bit() const { return 255 * _elem[2]; }
};

inline void writeColor8bit(std::ostream& out, Color color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(color.r8bit()) << ' '
        << static_cast<int>(color.g8bit()) << ' '
        << static_cast<int>(color.b8bit()) << '\n';
}