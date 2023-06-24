#include "tga_image.h"
#include "raster.h"
#include "model.h"
#include <ctime>
#include <cstdlib>

geo::vec3f light = {0.0,0.0,-1.0};
int const width = 1500;
int const height = 1500;

int main(){

    geo::normalize(light);
    Model model("../obj/african_head.obj");
    TGAImage image(width,height,TGAType::rgb);
    int nface = model.getFaceSize();
    std::array<geo::vec4f,3> vert;
    std::array<geo::vec3f,3> norm;
    std::array<geo::OARColor,3> color;

    float *zbuffer = new float[1500 * 1500];

    for(int i=0;i<1500*1500;i++){
        zbuffer[i] = -std::numeric_limits<float>::max();
    }

    if(zbuffer == nullptr){
        std::cerr<<"errors when creating zbuffer.\n";
        return 0;
    }

    for(int i=0;i<nface;i++){
        model.getTriangle(vert, i);
        model.getNorm(norm,i);

        bool check = 1;
        for(int j=0;j<3;j++){
            geo::normalize(norm[j]);

            float intensity = geo::dot(norm[j]*(-1.f),light);
            if(intensity<0.f || intensity>1.f){
                check = 0;
                break;
            }
            color[j] = geo::OARColor(intensity*255+.5f,intensity*255+.5f,intensity*255+.5f,255);
        }
        if(check) ras::triangle(image,vert,color,zbuffer);
    }
    image.writeToFile("./af.tga");

    delete[] zbuffer;

    return 0;
}

