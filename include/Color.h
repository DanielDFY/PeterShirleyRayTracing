#pragma once

#include <Vec3.h>
#include <iostream>

class Color : public Vec3 {
public:
    Color() = default;
    Color(double e1, double e2, double e3) : Vec3(e1, e2, e3) {}
    Color(Vec3 v) : Color(v.x(), v.y(), v.z()) {}
	
    double r() const { return elem[0]; }
    double g() const { return elem[1]; }
    double b() const { return elem[2]; }

    double r8bit() const { return 255 * elem[0]; }
    double g8bit() const { return 255 * elem[1]; }
    double b8bit() const { return 255 * elem[2]; }
};

inline void writeColor8bit(std::ostream& out, Color color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(color.r8bit()) << ' '
        << static_cast<int>(color.g8bit()) << ' '
        << static_cast<int>(color.b8bit()) << '\n';
}