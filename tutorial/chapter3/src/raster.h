#ifndef _RASTER_H_
#define _RASTER_H_

#include "tga_image.h"
#include "geometry.h"

namespace ras{
    bool line(TGAImage & image, geo::vec2i points[], geo::OARColor const & color);
    bool triangle(TGAImage & image, geo::vec2i points[], geo::OARColor colors[]);
}//namespace res

#endif

