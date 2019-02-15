# Peter Shirley Ray Tracing Lib

C++ source code of classes in << Ray Tracing in One Weekend >> —— Peter Shirley

And the cover image creating project.

### In-One-Weekend

<img alt="in-one-weekend cover image" src="In-One-Weekend%20cover%20image%20creating/Output.png">

```C++
#include <fstream>
#include <float.h>
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"

vec3 color(const ray& r, hittable *world, int depth ) {
    hit_record rec;
    if (world -> hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr -> scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        else {
            return vec3(0, 0, 0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        auto t = static_cast<float>(0.5 * (unit_direction.y() + 1.0));
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

hittable *random_scene() {
    int n = 500;
    hittable **list = new hittable*[n + 1];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            float choose_mat = static_cast<float>(drand48());
            vec3 center(static_cast<float>(a + 0.9 * drand48()), 0.2, static_cast<float>(b + 0.9 * drand48()));
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) { // diffuse
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3(static_cast<float>(drand48()*drand48()), static_cast<float>(drand48()*drand48()), static_cast<float>(drand48()*drand48()))));
                } else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(center, 0.2, new metal(vec3(static_cast<float>(0.5 * (1 + drand48())), static_cast<float>(0.5 * (1 + drand48())), static_cast<float>(0.5 * (1 + drand48()))), static_cast<float>(0.5 * drand48())));
                } else { // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hittable_list(list, i);
}

int main() {
    int nx = 800;
    int ny = 600;
    int ns = 100;
    std::ofstream Out;
    Out.open("./Output.ppm");
    Out << "P3\n" << nx << " " << ny << "\n255\n";

    hittable *world = random_scene();

    vec3 look_from(12, 2, 3);
    vec3 look_at(0, 0, -1);
    float dist_to_focus = (look_from - look_at).length();
    float aperture = 0.05;
    camera cam(look_from, look_at, vec3(0, 1, 0), 25, static_cast<float >(nx) / static_cast<float>(ny), aperture, dist_to_focus);

    for (int j = ny-1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            vec3 col(0, 0, 0);
            for ( int s = 0; s < ns; ++s) {
                auto u = static_cast<float>(i + drand48()) / static_cast<float>(nx);
                auto v = static_cast<float>(j + drand48()) / static_cast<float>(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));
            auto ir = static_cast<int>(255.99 * col[0]);
            auto ig = static_cast<int>(255.99 * col[1]);
            auto ib = static_cast<int>(255.99 * col[2]);

            Out << ir << " " << ig << " " << ib << "\n";
        }
    }

    Out.close();
    return 0;
}
```

