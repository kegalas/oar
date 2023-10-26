#include "raster.h"
#include <cassert>
#include <cmath>
#include <tuple>

bool ras::line(
    TGAImage & image,
    std::array<geo::vec2i,2> points,
    geo::OARColor const & color
){
    geo::vec2i & p0 = points[0], & p1 = points[1];
    int const width = image.getWidth();
    int const height = image.getHeight();

    if(std::abs(p1.y-p0.y) > std::abs(p1.x-p0.x)){
        if(p0.y > p1.y) std::swap(p0,p1);
        
        auto fxy = [&p0,&p1](float x, float y)->float{
            // Fundamentals of Computer Graphics(Fifth Edition), P179
            return (p0.y-p1.y)*x+(p1.x-p0.x)*y+p0.x*p1.y-p1.x*p0.y;
        };

        int x = p0.x;
        for(int y = p0.y ; y<=p1.y ; y++){
            if(x>=0 && x<width && y>=0 && y<height) image.setFragment(x,y,color);
            float er = fxy(static_cast<float>(x)+.5f, static_cast<float>(y)+1.f);
            if(p0.x<p1.x && er > 0.f && x<image.getWidth()-1){
                x++;
            }
            else if(p0.x>p1.x && er < 0.f && x>0){
                x--;
            }
        }
    }
    else{
        if(p0.x>p1.x) std::swap(p0,p1);
        
        auto fxy = [&p0,&p1](float x, float y)->float{
            return (p0.y-p1.y)*x+(p1.x-p0.x)*y+p0.x*p1.y-p1.x*p0.y;
        };

        int y = p0.y;
        for(int x = p0.x ; x<=p1.x ; x++){
            if(x>=0 && x<width && y>=0 && y<height) image.setFragment(x,y,color);
            float er = fxy(static_cast<float>(x)+1.f, static_cast<float>(y)+.5f);
            if(p0.y<p1.y && er<0.f && y<image.getHeight()-1){
                y++;
            }
            else if(p0.y>p1.y && er>0.f && y>0){
                y--;
            }
        }
    }

    return true;
}

bool ras::triangle(
    TGAImage & image,
    std::array<geo::vec2i,3> const & points,
    std::array<geo::OARColor,3> const & colors
){
    float const EPS = 1e-5;
    int maxx = 0, minx = image.getWidth()-1, maxy = 0, miny = image.getHeight()-1;
    for(int i=0;i<3;i++){
        maxx = std::max(maxx, points[i].x);
        minx = std::min(minx, points[i].x);
        maxy = std::max(maxy, points[i].y);
        miny = std::min(miny, points[i].y);
    }
    maxx = std::min(maxx, image.getWidth()-1);
    minx = std::max(minx, 0);
    maxy = std::min(maxy, image.getHeight()-1);
    miny = std::max(miny, 0);

    for(int x=minx;x<=maxx;x++){
        for(int y=miny;y<=maxy;y++){
            std::tuple<float,float,float> ret = geo::getBarycentric(points, geo::vec2i(x,y));
            float alpha = std::get<0> (ret);
            float beta  = std::get<1> (ret);
            float gamma = std::get<2> (ret);
            if(alpha<-EPS || beta<-EPS || gamma<-EPS) continue;
            geo::OARColor color = geo::vec4i(
                                      alpha*geo::vec4f(colors[0]) +
                                      beta*geo::vec4f(colors[1]) +
                                      gamma*geo::vec4f(colors[2]));
            image.setFragment(x,y,color);
        }
    }

    return true;
}

bool ras::triangle(
    TGAImage & image,
    std::array<geo::vec4f,3> const & points,
    std::array<geo::OARColor,3> const & colors
){
    float const EPS = 1e-5;
    int width = image.getWidth(), height = image.getHeight();

    std::array<geo::vec2i,3> screenPoints;

    for(int i=0;i<3;i++){
        screenPoints[i][0] = (int)(points[i][0] / points[i].w+.5f);
        screenPoints[i][1] = (int)(points[i][1] / points[i].w+.5f);
    }

    int maxx = 0, minx = width-1, maxy = 0, miny = height-1;
    for(int i=0;i<3;i++){
        maxx = std::max(maxx, screenPoints[i].x);
        minx = std::min(minx, screenPoints[i].x);
        maxy = std::max(maxy, screenPoints[i].y);
        miny = std::min(miny, screenPoints[i].y);
    }
    maxx = std::min(maxx, width-1);
    minx = std::max(minx, 0);
    maxy = std::min(maxy, height-1);
    miny = std::max(miny, 0);

    for(int x=minx;x<=maxx;x++){
        for(int y=miny;y<=maxy;y++){
            std::tuple<float,float,float> ret = geo::getBarycentric(screenPoints, geo::vec2i(x,y));
            float alpha = std::get<0> (ret);
            float beta  = std::get<1> (ret);
            float gamma = std::get<2> (ret);
            if(alpha<-EPS || beta<-EPS || gamma<-EPS) continue;

            geo::OARColor color = geo::vec4i(
                alpha*geo::vec4f(colors[0]) +
                beta*geo::vec4f(colors[1]) +
                gamma*geo::vec4f(colors[2]));
            image.setFragment(x,y,color);
        }
    }

    return true;
}

geo::vec2i ras::world2screen(geo::vec4f v, int width, int height){
    return geo::vec2i(int((v.x+1.f)*width*.5f+.5f), int((v.y+1.f)*height*.5f+.5f));
}
