#include "raster.h"
#include <cassert>
#include <cmath>

bool ras::line(TGAImage & image, geo::vec2i points[], geo::OARColor const & color){
    geo::vec2i *p0 = &points[0], *p1 = &points[1];

    assert(p0->x>=0 && p0->x<image.getWidth() && p0->y>=0 && p0->y<image.getHeight());
    assert(p1->x>=0 && p1->x<image.getWidth() && p1->y>=0 && p1->y<image.getHeight());

    if(std::abs(p1->y-p0->y)>std::abs(p1->x-p0->x)){
        if(p0->y>p1->y) std::swap(p0,p1);
        
        auto fxy = [&](float x, float y){
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
        
        auto fxy = [&](float x, float y){
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
    
    return true;
}
