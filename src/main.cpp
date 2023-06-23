#include "tga_image.h"
#include "raster.h"
#include "model.h"
#include <ctime>
#include <cstdlib>

geo::vec3f light = {0.0,0.0,-1.0};

int main(){

    geo::normalize(light);
    Model model("../obj/african_head.obj");
    TGAImage image(1500,1500,TGAType::rgb);
    int nface = model.getFaceSize();
    std::array<geo::vec3f,3> vert;
    std::array<geo::vec3f,3> norm;
    std::array<geo::vec2i,3>  screen;
    std::array<geo::OARColor,3> color;
    for(int i=0;i<nface;i++){
        model.getTriangle(vert, i);
        model.getNorm(norm,i);

        bool check = 1;
        for(int j=0;j<3;j++){
            screen[j] = geo::vec2i((vert[j].x+1.f)*image.getWidth()*.5f+.5f,
                                   (vert[j].y+1.f)*image.getHeight()*.5f+.5f);
            geo::normalize(norm[j]);

            float intensity = geo::dot(norm[j]*(-1.f),light);
            if(intensity<0.f || intensity>1.f){
                check = 0;
                break;
            }
            color[j] = geo::OARColor(intensity*255+.5f,intensity*255+.5f,intensity*255+.5f,255);
        }
        if(check) ras::triangle(image,screen,color);
    }
    image.writeToFile("./af.tga");


    return 0;
}

