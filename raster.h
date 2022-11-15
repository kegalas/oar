#ifndef _RASTER_H_
#define _RASTER_H_

#include "tga_image.h"
#include "geometry.h"

namespace ras{
    void line(TGAImage & image, geo::vec2i points[], geo::vec4i colors[]);
    void triangle(TGAImage & image, geo::vec2i points[], geo::vec4i colors[]);
}//namespace res

#endif

