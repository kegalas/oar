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

bool ras::triangleGouraud(
    TGAImage & image,
    geo::TriCoords const & tcoords,
    std::array<geo::OARColorf, 3> const & colors,
    geo::vec4f const & lightPos, // 光的位置
    geo::OARColorf const & light, // 光的颜色
    geo::vec4f const & cameraPos //相机的位置
){
    float const EPS = 1e-5;
    int maxx = 0, minx = image.getWidth()-1, maxy = 0, miny = image.getHeight()-1;
    for(int i=0;i<3;i++){
        maxx = std::max(maxx, tcoords.screenCoords[i].x);
        minx = std::min(minx, tcoords.screenCoords[i].x);
        maxy = std::max(maxy, tcoords.screenCoords[i].y);
        miny = std::min(miny, tcoords.screenCoords[i].y);
    }
    maxx = std::min(maxx, image.getWidth()-1);
    minx = std::max(minx, 0);
    maxy = std::min(maxy, image.getHeight()-1);
    miny = std::max(miny, 0);

    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f}; //设置三种反射的反射因子
    std::array<geo::OARColorf, 3> intensity;

    for(int i=0;i<3;i++){
        geo::vec4f l = geo::normalized(lightPos-tcoords.worldCoords[i]); //顶点到光源的单位向量
        geo::vec4f v = geo::normalized(cameraPos-tcoords.worldCoords[i]); //顶点到相机的单位向量
        geo::vec4f h = geo::normalized(v+l); //半程向量
        geo::vec4f norm = geo::normalized(tcoords.norms[i]);
        float value = geo::dot(l,norm);
        if(value<0.f){
            return true;
        }
        // 我们直接将dot(l,n)<0的点忽略
        // 按正常算法，value应该是std::max(0.f, geo::dot(l, norm))。但是我们这里还没有zbuffer，使用max会让一部分茶壶背后光照不到的显示在前面
        // 方便展示先这样操作。但这也会导致有些三角面缺失。因为虽然直接光照不到，还有环境光照射，不会是纯黑的三角形。
        
        geo::OARColorf ld = kd * light * value;
        geo::OARColorf ls = ks * light * std::pow(std::max(0.f,geo::dot(norm,h)), 100.f);
        geo::OARColorf la = ka * geo::vec4f(.3f, .3f, .3f, 1.f); //三种光强
        intensity[i] = ld + ls + la;
    }

    for(int x=minx;x<=maxx;x++){
        for(int y=miny;y<=maxy;y++){
            std::tuple<float,float,float> ret = geo::getBarycentric(tcoords.screenCoords, geo::vec2i(x,y));
            float alpha = std::get<0> (ret);
            float beta  = std::get<1> (ret);
            float gamma = std::get<2> (ret);
            if(alpha<-EPS || beta<-EPS || gamma<-EPS) continue;
            geo::OARColor color = geo::toOARColor(
                (alpha * colors[0] + beta  * colors[1] + gamma * colors[2]) *
                (alpha * intensity[0] + beta  * intensity[1] + gamma * intensity[2])
            );
            // 最终物体的颜色是 自身颜色*光照颜色
            image.setFragment(x,y,color);
        }
    }

    return true;
}

bool ras::trianglePhong(
    TGAImage & image,
    geo::TriCoords const & tcoords,
    std::array<geo::OARColorf, 3> const & colors,
    geo::vec4f const & lightPos, // 光的位置
    geo::OARColorf const & light, // 光的颜色
    geo::vec4f const & cameraPos //相机的位置
){
    float const EPS = 1e-5;
    int maxx = 0, minx = image.getWidth()-1, maxy = 0, miny = image.getHeight()-1;
    for(int i=0;i<3;i++){
        maxx = std::max(maxx, tcoords.screenCoords[i].x);
        minx = std::min(minx, tcoords.screenCoords[i].x);
        maxy = std::max(maxy, tcoords.screenCoords[i].y);
        miny = std::min(miny, tcoords.screenCoords[i].y);
    }
    maxx = std::min(maxx, image.getWidth()-1);
    minx = std::max(minx, 0);
    maxy = std::min(maxy, image.getHeight()-1);
    miny = std::max(miny, 0);

    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f}; //设置三种反射的反射因子

    for(int x=minx;x<=maxx;x++){
        for(int y=miny;y<=maxy;y++){
            std::tuple<float,float,float> ret = geo::getBarycentric(tcoords.screenCoords, geo::vec2i(x,y));
            float alpha = std::get<0> (ret);
            float beta  = std::get<1> (ret);
            float gamma = std::get<2> (ret);
            if(alpha<-EPS || beta<-EPS || gamma<-EPS) continue;

            geo::vec4f norm = alpha*tcoords.norms[0] + beta*tcoords.norms[1] + gamma*tcoords.norms[2];
            geo::vec4f world =  alpha*tcoords.worldCoords[0] + beta*tcoords.worldCoords[1] + gamma*tcoords.worldCoords[2];
            // 插值得出三角形内点的世界坐标与法向量

            geo::vec4f l = geo::normalized(lightPos-world); //顶点到光源的单位向量
            geo::vec4f v = geo::normalized(cameraPos-world); //顶点到相机的单位向量
            geo::vec4f h = geo::normalized(v+l); //半程向量
            geo::normalize(norm); // 不进行单位化，specular就会过强

            float value = geo::dot(l, norm);
            if(value<0.f){
                continue;
            }
            geo::OARColorf ld = kd * light * value;
            // 我们直接将dot(l,n)<0的点忽略
            // 按正常算法，value应该是std::max(0.f, geo::dot(l, norm))。但是我们这里还没有zbuffer，使用max会让一部分茶壶背后光照不到的显示在前面
            // 方便展示先这样操作。但这也会导致有些三角面缺失。因为虽然直接光照不到，还有环境光照射，不会是纯黑的三角形。
            
            geo::OARColorf ls = ks * light * std::pow(std::max(0.f,geo::dot(norm, h)), 100.f);
            geo::OARColorf la = ka * geo::vec4f(.3f, .3f, .3f, 1.f); //三种光强
            geo::vec4f intensity = ld + ls + la;

            geo::OARColor color = geo::toOARColor(
                (alpha * colors[0] + beta  * colors[1] + gamma * colors[2]) * intensity
            );
            // 最终物体的颜色是 自身颜色*光照颜色
            image.setFragment(x,y,color);
        }
    }

    return true;
}

geo::vec2i ras::world2screen(geo::vec4f v, int width, int height){
    return geo::vec2i(int((v.x+1.f)*width*.5f+.5f), int((v.y+1.f)*height*.5f+.5f));
}
