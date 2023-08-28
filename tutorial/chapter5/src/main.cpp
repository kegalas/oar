#include "tga_image.h"
#include "raster.h"
#include "model.h"
#include <ctime>
#include <cstdlib>

int const width = 1500;
int const height = 1500;
geo::vec4f lightPos = {0.f, 0.f, 10.f, 1.f};//光源的位置
geo::OARColorf light = {1.f, 1.f, 1.f, 1.f};//光的强度
geo::vec4f camera = {0.f, 0.f, 2.f, 1.f};//相机的位置

int main(){
    Model model("../obj/african_head.obj");
    TGAImage image(width,height,TGAType::rgb);
    int nface = model.getFaceSize();
    std::array<geo::vec4f,3> vert;
    std::array<geo::OARColor,3> color;
    std::array<geo::vec4f, 3> norm;
    std::array<geo::vec2i,3> screen;
    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f};//设置三种反射的反射因子

    for(int i=0;i<nface;i++){
        model.getTriangle(vert, i);
        model.getNorm(norm, i);

        bool check = 1;
        for(int j=0;j<3;j++){
            geo::vec4f l = geo::normalized(lightPos-vert[j]);//顶点到光源的单位向量
            geo::vec4f v = geo::normalized(camera-vert[j]);//顶点到相机的单位向量
            geo::vec4f h = geo::normalized(v+l);//半程向量
            float intensity = geo::dot(l,norm[j]);//我们直接不绘制dot(l,n)<0的三角形
            if(intensity<0.f){
                check = 0;
                break;
            }
            geo::OARColorf ld = kd * light * intensity;//因为我们还没学zbuffer，如果用max的话会绘制全黑的三角形
            geo::OARColorf ls = ks * light * std::pow(std::max(0.f,geo::dot(norm[j],h)), 100.f);
            geo::OARColorf la = ka * geo::vec4f(.3f, .3f, .3f, 1.f);//三种光强
            color[j] = geo::toOARColor(ld+ls+la);
            screen[j] = ras::world2screen(vert[j],width,height);
        }
        if(check) ras::triangle(image,screen,color);
    }
    image.writeToFile("./af.tga");

    return 0;
}

