#include "img/tga_image.h"
#include "math/geometry.h"
#include "util/raster.h"
#include "model/model.h"
#include <charconv>
#include <ctime>
#include <cstdlib>

int const width = 1500;
int const height = 1500;
geo::vec4f lightPos = {0.f, 0.f, 10.f, 1.f};
geo::OARColorf light = {1.f, 1.f, 1.f, 1.f};
geo::vec4f camera = {0.f, 0.f, 3.f, 1.f};
float const PI = std::acos(-1.f);

void drawMan(){
    Model model("../obj/african_head.obj");
    TGAImage image(width,height,TGAType::rgb);
    //TGAImage diffTex("../texture/african_head_diffuse.tga");
    int nface = model.getFaceNum();
    geo::TriCoords tcoords;
    std::array<geo::OARColor,3> color;
    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f};

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(camera, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f prosp = geo::prospective(2.9f,-1000.f);
    //geo::mat4f orth = geo::orthographic(-1.f, 1.f, 1.f, -1.f, 2.f, -2.f);
    geo::mat4f mod = geo::rotateY(PI/4);
    
    float * zbuf = nullptr;
    ras::initZBuffer(zbuf, width, height);
    
    for(int i=0;i<nface;i++){
        model.getTriangle(tcoords.worldCoords, i);
        model.getNorm(tcoords.norms, i);
        model.getUV(tcoords.uvs, i);

        bool check = 1;
        for(int j=0;j<3;j++){
            tcoords.worldCoords[j] = mod * tcoords.worldCoords[j];
            tcoords.norms[j] = geo::transpose(geo::inverse(mod)) * tcoords.norms[j];
            
            geo::vec4f l = geo::normalized(lightPos-tcoords.worldCoords[j]);
            geo::vec4f v = geo::normalized(camera-tcoords.worldCoords[j]);
            geo::vec4f h = geo::normalized(v+l);
            geo::OARColorf ld = kd * light * std::max(0.f, geo::dot(l, tcoords.norms[j]));
            geo::OARColorf ls = ks * light * std::pow(std::max(0.f,geo::dot(tcoords.norms[j],h)), 100.f);
            geo::OARColorf la = ka * geo::vec4f(.3f, .3f, .3f, 1.f);
            color[j] = geo::toOARColor(ld+ls+la);

            tcoords.camCoords[j] = cam * tcoords.worldCoords[j];
            tcoords.screenCoords[j] = prosp * tcoords.camCoords[j];
            tcoords.screenCoords[j] /= tcoords.screenCoords[j].w;
            tcoords.screenCoords[j] = view * tcoords.screenCoords[j];
        }
        if(check) ras::triangle(image,tcoords,color,zbuf);
    }
    image.writeToFile("./af.tga");

    ras::deleteZBuffer(zbuf);
}

void drawTri(){
    TGAImage image(width,height,TGAType::rgb);

    std::array<geo::vec4f, 3> tri;
    std::array<geo::vec2i, 3> screen;
    std::array<geo::OARColor, 3> color;
    tri[0] = {-1.f,1.f,0.f,1.f};
    tri[1] = {1.f,0.f,0.f,1.f};
    tri[2] = {0.f,-1.f,0.f,1.f};
    color[0] = {255,0,0,255};
    color[1] = {0,255,0,255};
    color[2] = {0,0,255,255};

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(camera, {0.f,0.f,-1.f,1.f}, {0.f,1.f,0.f,1.f});
    geo::mat4f trans;
    trans = view * cam * trans;

    for(int i=0;i<3;i++){
        screen[i] = trans * tri[i];
    }

    ras::triangle(image, screen, color);

    image.writeToFile("./tri.tga");
}

int main(){
    drawMan();

    return 0;
}

