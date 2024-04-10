#ifndef _RASTER_H_
#define _RASTER_H_

#include "img/tga_image.h"
#include "math/geometry.h"
#include <array>

namespace ras{
    bool line(
            TGAImage & image,
            std::array<geo::vec2i,2> points,
            geo::OARColor const & color
    );

    bool triangle(
            TGAImage & image,
            std::array<geo::vec2i,3> const & points,
            std::array<geo::OARColor,3> const & colors
    );

    bool triangle(
        TGAImage & image,
        std::array<geo::vec4f,3> const & points,
        std::array<geo::OARColor,3> const & colors
    );

    bool triangle(
        TGAImage & image,
        std::array<geo::vec4f,3> const & points,
        std::array<geo::OARColor,3> const & colors,
        float zbuffer[]
    );

//    bool initZBuffer(float *zb, int width, int height);

//    bool deleteZBuffer(float *zb);

    geo::vec2i world2screen(geo::vec4f v, int width, int height);
}//namespace res

#endif

