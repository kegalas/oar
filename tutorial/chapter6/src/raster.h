#ifndef _RASTER_H_
#define _RASTER_H_

#include "tga_image.h"
#include "geometry.h"
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

    geo::vec2i world2screen(geo::vec4f v, int width, int height);
}//namespace res

#endif

