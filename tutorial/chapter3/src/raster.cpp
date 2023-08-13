#include "raster.h"
#include <cassert>
#include <cmath>
#include <tuple>

bool ras::line(TGAImage & image, geo::vec2i points[], geo::OARColor const & color){
    geo::vec2i *p0 = &points[0], *p1 = &points[1];

    assert(p0->x>=0 && p0->x<image.getWidth() && p0->y>=0 && p0->y<image.getHeight());
    assert(p1->x>=0 && p1->x<image.getWidth() && p1->y>=0 && p1->y<image.getHeight());

    if(std::abs(p1->y-p0->y) > std::abs(p1->x-p0->x)){
        if(p0->y > p1->y) std::swap(p0,p1);
        
        auto fxy = [&](float x, float y)->float{
            // Fundamentals of Computer Graphics(Fifth Edition), P179
            return (p0->y-p1->y)*x+(p1->x-p0->x)*y+p0->x*p1->y-p1->x*p0->y;
        };

        int x = p0->x;
        for(int y = p0->y ; y<=p1->y ; y++){
            image.setFragment(x,y,color);
            float er = fxy(static_cast<float>(x)+.5f, static_cast<float>(y)+1.f);
            if(p0->x<p1->x && er > 0.f && x<image.getWidth()-1){
                x++;
            }
            else if(p0->x>p1->x && er < 0.f && x>0){
                x--;
            }
        }
    }
    else{
        if(p0->x>p1->x) std::swap(p0,p1);
        
        auto fxy = [&](float x, float y)->float{
            return (p0->y-p1->y)*x+(p1->x-p0->x)*y+p0->x*p1->y-p1->x*p0->y;
        };

        int y = p0->y;
        for(int x = p0->x ; x<=p1->x ; x++){
            image.setFragment(x,y,color);
            float er = fxy(static_cast<float>(x)+1.f, static_cast<float>(y)+.5f);
            if(p0->y<p1->y && er<0.f && y<image.getHeight()-1){
                y++;
            }
            else if(p0->y>p1->y && er>0.f && y>0){
                y--;
            }
        }
    }

    return true;
}

bool ras::triangle(TGAImage & image, geo::vec2i points[], geo::OARColor colors[]){
    geo::vec2i const & pa = points[0];
    geo::vec2i const & pb = points[1];
    geo::vec2i const & pc = points[2];

    assert(pa.x>=0 && pa.x<image.getWidth() && pa.y>=0 && pa.y<image.getHeight());
    assert(pb.x>=0 && pb.x<image.getWidth() && pb.y>=0 && pb.y<image.getHeight());
    assert(pc.x>=0 && pc.x<image.getWidth() && pc.y>=0 && pc.y<image.getHeight());

    int maxx = 0, minx = image.getWidth()-1, maxy = 0, miny = image.getHeight()-1;
    for(int i=0;i<3;i++){
        maxx = std::max(maxx, points[i].x);
        minx = std::min(minx, points[i].x);
        maxy = std::max(maxy, points[i].y);
        miny = std::min(miny, points[i].y);
    }

    for(int x=minx;x<=maxx;x++){
        for(int y=miny;y<=maxy;y++){
            std::tuple<float,float,float> ret = geo::getBarycentric(points, x, y);
            float alpha = std::get<0> (ret);
            float beta  = std::get<1> (ret);
            float gamma = std::get<2> (ret);
            if(0.f<=alpha && alpha<=1.f &&
               0.f<=beta  && beta <=1.f &&
               0.f<=gamma && gamma<=1.f)
            {
                geo::OARColor color = static_cast<geo::vec4i>(
                                      alpha*static_cast<geo::vec4f>(colors[0]) +
                                      beta*static_cast<geo::vec4f>(colors[1]) +
                                      gamma*static_cast<geo::vec4f>(colors[2]));
                image.setFragment(x,y,color);
            }
        }
    }

    return true;
}
