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
    Model model("../obj/teapot.obj");
    TGAImage image(width,height,TGAType::rgb);
    TGAImage image2(width,height,TGAType::rgb);
    int nface = model.getFaceSize();
    geo::TriCoords tcoords;
    std::array<geo::OARColorf, 3> color;

    for(int i=0;i<nface;i++){
        model.getTriangle(tcoords.worldCoords, i);
        model.getNorm(tcoords.norms, i);

        for(int j=0;j<3;j++){
            tcoords.screenCoords[j] = ras::world2screen(tcoords.worldCoords[j], width, height);
            color[j] = {1.0f, 0.0f, 0.0f, 1.0f};
        }

        ras::triangleGouraud(image, tcoords, color, lightPos, light, camera);
        ras::trianglePhong(image2, tcoords, color, lightPos, light, camera);
    }
    image.writeToFile("./tp_g.tga");
    image2.writeToFile("./tp_p.tga");

    return 0;
}

