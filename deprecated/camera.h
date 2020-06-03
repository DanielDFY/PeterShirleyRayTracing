#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

vec3 random_in_unit_dist() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    return p;
}

class camera {
public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;

    camera(vec3 look_from, vec3 look_at, vec3 vup, float vFov, float aspect, float aperture, float focus_dist) { // vFov is top to bottom in degree
        lens_radius = aperture / 2;
        auto theta = static_cast<float>(vFov * M_PI / 180);
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;
        origin = look_from;

        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        lower_left_corner = origin - u * half_width * focus_dist - v * half_height * focus_dist - w * focus_dist;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }
    ray get_ray(float s, float t) {
        vec3 rd = lens_radius * random_in_unit_dist();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }
};

#endif //CAMERA_H
