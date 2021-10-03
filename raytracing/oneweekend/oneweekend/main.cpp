//
//  main.cpp
//  oneweekend
//
//  Created by bytedance on 2021/9/5.
//

#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

//bool hit_sphere(const point3& center,double radius,const ray& r)
//{
//    vec3 oc = r.origin() - center;
//
//
//    return true;
//}

color ray_color(const ray& r)
{
    if(hit_sphere(point3(0,0,-1),0.5,r))
    {
        return color(1,0,0);
    }
    vec3 unit_dir = unit_vector(r.direction());
    auto t = 0.5 * (unit_dir.y() + 1.0);    // [-1,1] -> [0,1]
    return t * color(0.5,0.7,1.0) + (1.0 - t) * color(1.0,1.0,1.0);
}

int main(int argc, const char * argv[])
{
    // Image
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = image_width / aspect_ratio;
    
    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;
    
    auto origin = point3(0,0,0);
    auto horizontal = vec3(viewport_width,0,0);
    auto vertical = vec3(0,viewport_height,0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length);
    
    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    for(int j = image_height - 1;j >= 0;--j)
    {
        std::cerr << "\rScanlines remaing: " << j << ' ' << std::flush;
        for(int i = 0;i < image_width;++i)
        {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin,lower_left_corner + u * horizontal + v * vertical - origin);
            
            color pixel_color = ray_color(r);
            write_color(std::cout,pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}
