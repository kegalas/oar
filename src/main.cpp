#include "tga_image.h"
#include "raster.h"
#include "model.h"
#include <ctime>
#include <cstdlib>

int const width = 1500;
int const height = 1500;

int main(){
    Model model("../obj/african_head.obj");
    TGAImage image(width,height,TGAType::rgb);
    int nface = model.getFaceSize();
    std::array<geo::vec4f,3> vert;
    std::array<geo::OARColor,3> color;
    std::array<geo::vec2i,3> screen;

    for(int i=0;i<nface;i++){
        model.getTriangle(vert, i);
        for(int j=0;j<3;j++){
            color[j] = geo::OARColor(255,255,255,255);
            screen[j] = ras::world2screen(vert[j],width,height);
        }
        ras::triangle(image,screen,color);
    }
    image.writeToFile("./af.tga");

    return 0;
}

