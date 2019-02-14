#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere: public hittable {
public:
    vec3 center;
    float radius;
    material* mat_ptr;

    sphere() = default;
    sphere(vec3 c, float r, material *m) : center(c), radius(r), mat_ptr(m) {}
    bool hit(const ray &r, float t_min, float t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(b * b - a * c)) / a;
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp =  (-b + sqrt(b * b - a * c)) / a;
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif //SPHERE_H
