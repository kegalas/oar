#include "img/tga_image.h"
#include "math/geometry.h"
#include "util/raster.h"
#include "model/model.h"
#include <array>
#include <charconv>
#include <ctime>
#include <cstdlib>

int const width = 1500;
int const height = 1500;
geo::vec4f lightPos = {0.f, 0.f, 10.f, 1.f};
geo::OARColorf lightColorf = {1.f, 1.f, 1.f, 1.f};
geo::vec4f cameraPos = {0.f, 0.f, 0.5f, 1.f};
float const PI = std::acos(-1.f);

void drawMan(){
    Model model("../obj/african_head.obj");
    TGAImage image(width,height,TGAType::rgb);
    TGAImage diffTex("../texture/african_head_diffuse.tga");
    int nface = model.getFaceNum();
    geo::TriCoords tcoords;
    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f};
    std::array<geo::vec4f, 3> reflect = {kd, ks, ka};

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(cameraPos, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f prosp = geo::prospective(2.9f,-1000.f);
    //geo::mat4f orth = geo::orthographic(-1.f, 1.f, 1.f, -1.f, 2.f, -2.f);
    geo::mat4f mod = geo::rotateY(0);
    //geo::mat4f prosp;
    //geo::mat4f mod;
    //geo::mat4f cam;
    
    float * zbuf = nullptr;
    ras::initZBuffer(zbuf, width, height);
    
    for(int i=0;i<nface;i++){
        model.getTriangle(tcoords.worldCoords, i);
        model.getNorm(tcoords.norms, i);
        model.getUV(tcoords.uvs, i);

        for(int j=0;j<3;j++){
            tcoords.worldCoords[j] = mod * tcoords.worldCoords[j];
            tcoords.norms[j] = geo::transpose(geo::inverse(mod)) * tcoords.norms[j];
            
            tcoords.camCoords[j] = cam * tcoords.worldCoords[j];
            tcoords.screenCoords[j] = prosp * tcoords.camCoords[j];
            tcoords.screenCoords[j] /= tcoords.screenCoords[j].w;
            tcoords.screenCoords[j] = view * tcoords.screenCoords[j];
        }
        ras::triangle(image,diffTex,tcoords,lightColorf,lightPos,cameraPos,reflect,zbuf);
    }
    image.writeToFile("./af.tga");

    ras::deleteZBuffer(zbuf);
}

void drawSQ(){
    Model model("../obj/sq.obj");
    TGAImage image(width,height,TGAType::rgb);
    TGAImage diffTex("../texture/sq.tga");
    int nface = model.getFaceNum();
    geo::TriCoords tcoords;
    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {0.83f, 0.83f, 0.83f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f};
    std::array<geo::vec4f, 3> reflect = {kd, ks, ka};

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(cameraPos, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f prosp = geo::prospective(2.9f,-1000.f);
    //geo::mat4f orth = geo::orthographic(-1.f, 1.f, 1.f, -1.f, 2.f, -2.f);
    geo::mat4f mod = geo::rotateY(0);
    //geo::mat4f prosp;
    //geo::mat4f mod;
    //geo::mat4f cam;

    float * zbuf = nullptr;
    ras::initZBuffer(zbuf, width, height);

    for(int i=0;i<nface;i++){
        model.getTriangle(tcoords.worldCoords, i);
        model.getNorm(tcoords.norms, i);
        model.getUV(tcoords.uvs, i);

        for(int j=0;j<3;j++){
            tcoords.worldCoords[j] = mod * tcoords.worldCoords[j];
            tcoords.norms[j] = geo::transpose(geo::inverse(mod)) * tcoords.norms[j];

            tcoords.camCoords[j] = cam * tcoords.worldCoords[j];
            tcoords.screenCoords[j] = prosp * tcoords.camCoords[j];
            tcoords.screenCoords[j] /= tcoords.screenCoords[j].w;
            tcoords.screenCoords[j] = view * tcoords.screenCoords[j];
        }
        ras::triangle(image,diffTex,tcoords,lightColorf,lightPos,cameraPos,reflect,zbuf);
    }
    image.writeToFile("./sq.tga");

    ras::deleteZBuffer(zbuf);
}

void drawTeaPot(){
    Model model("../obj/teapot.obj");
    TGAImage image(width,height,TGAType::rgb);
    TGAImage diffTex("../texture/brick.tga");
    int nface = model.getFaceNum();
    geo::TriCoords tcoords;
    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f};
    std::array<geo::vec4f, 3> reflect = {kd, ks, ka};

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(cameraPos, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f prosp = geo::prospective(2.9f,-1000.f); // 存在问题，-0.001~-1000是不行的，必须要near为正数
    geo::mat4f mod = geo::rotateY(-PI/12.f)*geo::rotateX(PI/2.f*3.f);

    float * zbuf = nullptr;
    ras::initZBuffer(zbuf, width, height);

    for(int i=0;i<nface;i++){
        model.getTriangle(tcoords.worldCoords, i);
        model.getNorm(tcoords.norms, i);
        model.getUV(tcoords.uvs, i);

        for(int j=0;j<3;j++){
            tcoords.worldCoords[j] = mod * tcoords.worldCoords[j];
            tcoords.norms[j] = geo::transpose(geo::inverse(mod)) * tcoords.norms[j];

            tcoords.camCoords[j] = cam * tcoords.worldCoords[j];
            tcoords.screenCoords[j] = prosp * tcoords.camCoords[j];
            tcoords.screenCoords[j] /= tcoords.screenCoords[j].w;
            tcoords.screenCoords[j] = view * tcoords.screenCoords[j];
        }
        ras::triangle(image,diffTex,tcoords,lightColorf,lightPos,cameraPos,reflect,zbuf);
    }
    image.writeToFile("./tp.tga");

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
    geo::mat4f cam = geo::cameraView(cameraPos, {0.f,0.f,-1.f,1.f}, {0.f,1.f,0.f,1.f});
    geo::mat4f trans;
    trans = view * cam * trans;

    for(int i=0;i<3;i++){
        screen[i] = trans * tri[i];
    }

    ras::triangle(image, screen, color);

    image.writeToFile("./tri.tga");
}

int main(){
//    drawMan();
    drawTeaPot();

    return 0;
}

