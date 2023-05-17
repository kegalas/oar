#include "tga_image.h"
#include "raster.h"

int main(){
    /*
    TGAImage image("./test.tga");
    image.flipVertically();
    image.writeToFile("./ttt.tga");
    */

    TGAImage image(100,100,TGAType::rgb);

    geo::vec2i pts0[2] = {geo::vec2i(99,0),geo::vec2i(0,99)};
    ras::line(image, pts0, geo::OARColor(255,0,0,255));
    
    for(int i=0;i<=99;i+=10){
        pts0[0] = geo::vec2i(i,0);
        ras::line(image, pts0, geo::OARColor(255,0,0,255));
    }
    
    image.writeToFile("./line.tga");

    TGAImage image2(100,100,TGAType::rgb);
    geo::vec2i pts1[3] = {geo::vec2i(60,5),geo::vec2i(5,60),geo::vec2i(70,90)};
    geo::OARColor colors[3] = {geo::OARColor(255,0,0,255),geo::OARColor(0,255,0,255),geo::OARColor(0,0,255,255)};
    ras::triangle(image2,pts1,colors);
    image2.writeToFile("./triangle.tga");

    return 0;
}

