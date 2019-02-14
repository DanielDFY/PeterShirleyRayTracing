#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

class hittable_list: public hittable {
public:
    hittable** list;
    int list_size;

    hittable_list() = default;
    hittable_list(hittable** l, int n) : list(l), list_size(n) {}
    bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
};

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < list_size; ++i) {
        if (list[i] -> hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif //HITTABLE_LIST_H
