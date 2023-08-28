#include "tga_image.h"
#include "raster.h"
#include "model.h"
#include <ctime>
#include <cstdlib>

int const width = 1500;
int const height = 1500;
geo::vec4f lightPos = {0.f, 0.f, 10.f, 1.f};
geo::OARColorf light = {1.f, 1.f, 1.f, 1.f};
geo::vec4f camera = {0.f, 0.f, 2.f, 1.f};

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
    geo::vec4f ka = {.2f, .2f, .2f, 1.f};

    for(int i=0;i<nface;i++){
        model.getTriangle(vert, i);
        model.getNorm(norm, i);

        bool check = 1;
        for(int j=0;j<3;j++){
            geo::vec4f l = geo::normalized(lightPos-vert[j]);
            geo::vec4f v = geo::normalized(camera-vert[j]);
            geo::vec4f h = geo::normalized(v+l);
            float intensity = geo::dot(l,norm[j]);
            if(intensity<0.f){
                check = 0;
                break;
            }
            geo::OARColorf ld = kd * light * intensity;
            geo::OARColorf ls = ks * light * std::pow(std::max(0.f,geo::dot(norm[j],h)), 100.f);
            geo::OARColorf la = ka * geo::vec4f(.3f, .3f, .3f, 1.f);
            color[j] = geo::toOARColor(ld+ls+la);
            screen[j] = ras::world2screen(vert[j],width,height);
        }
        if(check) ras::triangle(image,screen,color);
    }
    image.writeToFile("./af.tga");

    return 0;
}

