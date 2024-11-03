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

    bool triangleGouraud(
        TGAImage & image,
        geo::TriCoords const & tcoords,
        std::array<geo::OARColorf, 3> const & colors,
        geo::vec4f const & lightPos, // 光的位置
        geo::OARColorf const & light, // 光的颜色
        geo::vec4f const & cameraPos //相机的位置
    );

    bool trianglePhong(
        TGAImage & image,
        geo::TriCoords const & tcoords,
        std::array<geo::OARColorf, 3> const & colors,
        geo::vec4f const & lightPos, // 光的位置
        geo::OARColorf const & light, // 光的颜色
        geo::vec4f const & cameraPos //相机的位置
    );

    bool trianglePhong(
        TGAImage & image,
        geo::TriCoords const & tcoords,
        std::array<geo::OARColorf, 3> const & colors,
        geo::vec4f const & lightPos, // 光的位置
        geo::OARColorf const & light, // 光的颜色
        geo::vec4f const & cameraPos, //相机的位置
        float zbuffer[]
    );

    bool trianglePhong(
        TGAImage & image,
        TGAImage const & tex,
        geo::TriCoords const & tcoords,
        geo::OARColorf const & lightColorf,
        geo::vec4f const & lightPos,
        geo::vec4f const & cameraPos,
        std::array<geo::vec4f, 3> const & reflect,
        float zbuffer[]
    );

    bool initZBuffer(float * & zb, int width, int height);

    bool deleteZBuffer(float * & zb);

    geo::vec2i world2screen(geo::vec4f v, int width, int height);
}//namespace res

#endif

