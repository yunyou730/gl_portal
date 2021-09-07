//
//  main.cpp
//  oneweekend
//
//  Created by bytedance on 2021/9/5.
//

#include <iostream>
#include "vec3.h"


const int image_width = 256;
const int image_height = 256;

const float kColorMax = 255.0f;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    for(int j = image_height - 1;j >= 0;--j)
    {
        std::cerr << "\rScanlines remaing: " << j << ' ' << std::flush;
        for(int i = 0;i < image_width;++i)
        {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;
            
            int ir = static_cast<int>(kColorMax * r);
            int ig = static_cast<int>(kColorMax * g);
            int ib = static_cast<int>(kColorMax * b);
            
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}
