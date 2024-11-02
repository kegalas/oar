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

bool ras::triangleGouraud(
    TGAImage & image,
    geo::TriCoords const & tcoords,
    std::array<geo::OARColorf, 3> const & colors,
    geo::vec4f const & lightPos, // 光的位置
    geo::OARColorf const & light, // 光的颜色
    geo::vec4f const & cameraPos //相机的位置
    ){
    float const EPS = 1e-5;
    int width = image.getWidth(), height = image.getHeight();
    std::array<geo::vec2i,3> screenPoints;

    for(int i=0;i<3;i++){
        screenPoints[i][0] = (int)(tcoords.screenCoords[i][0] / tcoords.screenCoords[i].w+.5f);
        screenPoints[i][1] = (int)(tcoords.screenCoords[i][1] / tcoords.screenCoords[i].w+.5f);
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

    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f}; //设置三种反射的反射因子
    std::array<geo::OARColorf, 3> intensity;

    for(int i=0;i<3;i++){
        geo::vec4f l = geo::normalized(lightPos-tcoords.worldCoords[i]); //顶点到光源的单位向量
        geo::vec4f v = geo::normalized(cameraPos-tcoords.worldCoords[i]); //顶点到相机的单位向量
        geo::vec4f h = geo::normalized(v+l); //半程向量
        geo::vec4f norm = geo::normalized(tcoords.norms[i]);
        float value = geo::dot(l,norm); //我们直接将dot(l,n)<0的三角形不进行绘制
        if(value<0.f){
            return true;
        }
        geo::OARColorf ld = kd * light * value;
        geo::OARColorf ls = ks * light * std::pow(std::max(0.f,geo::dot(norm,h)), 100.f);
        geo::OARColorf la = ka * geo::vec4f(.3f, .3f, .3f, 1.f); //三种光强
        intensity[i] = ld + ls + la;
    }

    for(int x=minx;x<=maxx;x++){
        for(int y=miny;y<=maxy;y++){
            std::tuple<float,float,float> ret = geo::getBarycentric(screenPoints, geo::vec2i(x,y));
            // 有透视投影后，从屏幕空间中进行重心插值其实是错的，之后纹理一章我们会讲解
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
    int width = image.getWidth(), height = image.getHeight();
    std::array<geo::vec2i,3> screenPoints;

    for(int i=0;i<3;i++){
        screenPoints[i][0] = (int)(tcoords.screenCoords[i][0] / tcoords.screenCoords[i].w+.5f);
        screenPoints[i][1] = (int)(tcoords.screenCoords[i][1] / tcoords.screenCoords[i].w+.5f);
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

    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f}; //设置三种反射的反射因子

    for(int x=minx;x<=maxx;x++){
        for(int y=miny;y<=maxy;y++){
            std::tuple<float,float,float> ret = geo::getBarycentric(screenPoints, geo::vec2i(x,y));
            // 有透视投影后，从屏幕空间中进行重心插值其实是错的，之后纹理一章我们会讲解
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

            float value = geo::dot(l, norm); //我们直接将dot(l,n)<0的点忽略
            if(value<0.f){
                continue;
            }
            geo::OARColorf ld = kd * light * value;
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

bool ras::trianglePhong(
    TGAImage & image,
    geo::TriCoords const & tcoords,
    std::array<geo::OARColorf, 3> const & colors,
    geo::vec4f const & lightPos, // 光的位置
    geo::OARColorf const & light, // 光的颜色
    geo::vec4f const & cameraPos, //相机的位置
    float zbuffer[]
){
    float const EPS = 1e-5;
    int width = image.getWidth(), height = image.getHeight();
    std::array<geo::vec2i,3> screenPoints;

    for(int i=0;i<3;i++){
        screenPoints[i][0] = (int)(tcoords.screenCoords[i][0] / tcoords.screenCoords[i].w+.5f);
        screenPoints[i][1] = (int)(tcoords.screenCoords[i][1] / tcoords.screenCoords[i].w+.5f);
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

    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f}; //设置三种反射的反射因子

    for(int x=minx;x<=maxx;x++){
        for(int y=miny;y<=maxy;y++){
            std::tuple<float,float,float> ret = geo::getBarycentric(screenPoints, geo::vec2i(x,y));
            float alpha = std::get<0> (ret);
            float beta  = std::get<1> (ret);
            float gamma = std::get<2> (ret);
            if(alpha<-EPS || beta<-EPS || gamma<-EPS) continue;

            float z = alpha * tcoords.screenCoords[0].z +
                      beta  * tcoords.screenCoords[1].z +
                      gamma * tcoords.screenCoords[2].z;
            // z值在这里可以先这样用，下一节我们会发现这样插值是有误差的
            // 虽然我们这里传进来的是屏幕空间而非剪裁空间，但这两个空间的z坐标是相同的

            if(z<zbuffer[y*width+x]){
                continue;
            }
            zbuffer[y*width+x] = z;

            geo::vec4f norm = alpha*tcoords.norms[0] + beta*tcoords.norms[1] + gamma*tcoords.norms[2];
            geo::vec4f world =  alpha*tcoords.worldCoords[0] + beta*tcoords.worldCoords[1] + gamma*tcoords.worldCoords[2];
            // 插值得出三角形内点的世界坐标与法向量

            geo::vec4f l = geo::normalized(lightPos-world); //顶点到光源的单位向量
            geo::vec4f v = geo::normalized(cameraPos-world); //顶点到相机的单位向量
            geo::vec4f h = geo::normalized(v+l); //半程向量
            geo::normalize(norm); // 不进行单位化，specular就会过强

            geo::OARColorf ld = kd * light * std::max(0.f, geo::dot(l, norm));
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
