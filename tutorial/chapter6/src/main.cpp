#include "tga_image.h"
#include "raster.h"
#include "model.h"
#include <ctime>
#include <cstdlib>

int const width = 1500;
int const height = 1500;
geo::vec4f lightPos = {0.f, 0.f, -1.f, 1.f};
geo::OARColorf light = {1.f, 1.f, 1.f, 1.f};
geo::vec4f camera = {0.f, 0.f, 1.f, 1.f};
float const PI = std::acos(-1.f);

void keep3x3(geo::mat4f & mat){
    mat[3][0] = 0.0f; mat[3][1] = 0.0f; mat[3][2] = 0.0f; mat[3][3] = 1.0f;
    mat[0][3] = 0.0f; mat[1][3] = 0.0f; mat[2][3] = 0.0f;
}

void drawTeapot(){
    Model model("../obj/teapot.obj");
    TGAImage image(width,height,TGAType::rgb);
    int nface = model.getFaceNum();
    std::array<geo::OARColorf,3> color;
    geo::TriCoords tcoords;

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(camera, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f persp = geo::perspective(-0.01f,-1000.f);
    geo::mat4f orth = geo::orthographic(-0.01f, 0.01f, 0.01f, -0.01f, -0.01f, -1000.f);
    geo::mat4f trans = orth * persp * cam;

    auto paint = [&](geo::mat4f trans_mat, TGAImage &out){
        for(int T=8;T>=0;T--){
            geo::mat4f py = geo::translate({2.0f,-1.0f,-2.0f-T*2.0f,1.f});
            geo::mat4f sx = geo::scale(1.5f);
            geo::mat4f trans_inv = geo::transpose(geo::inverse(py*sx));
            keep3x3(trans_inv);

            for(int i=0;i<nface;i++){
                model.getTriangle(tcoords.worldCoords, i);
                model.getNorm(tcoords.norms, i);

                for(int j=0;j<3;j++){
                    color[j] = {1.0f, 1.0f, 1.0f, 1.0f};
                    tcoords.worldCoords[j] = py * sx * tcoords.worldCoords[j];
                    tcoords.screenCoords[j] = trans_mat * tcoords.worldCoords[j];
                    tcoords.screenCoords[j] /= tcoords.screenCoords[j].w; //这一句非常重要
                    tcoords.screenCoords[j] = view * tcoords.screenCoords[j];

                    tcoords.norms[j] = trans_inv * tcoords.norms[j];
                }
                ras::trianglePhong(out, tcoords, color, lightPos, light, camera);
            }
        }
    };

    paint(trans, image);
    image.writeToFile("./tp.tga");

    TGAImage image2(width,height,TGAType::rgb);
    trans = geo::perspectiveFov(PI/2.0f, 1.0f*width/height, -0.01f, -1000.0f) * cam;
    paint(trans, image2);
    image2.writeToFile("./tp2.tga"); // 应当和上图一致

    TGAImage image3(width,height,TGAType::rgb);
    orth = geo::orthographic(-1.f, 1.f, 1.f, -1.f, -0.01f, -1000.f);
    trans = orth * persp * cam;
    paint(trans, image3);
    image3.writeToFile("./tp3.tga"); // 应当没图
}

void drawSQ(){
    Model model("../obj/sq.obj");
    TGAImage image(width,height,TGAType::rgb);
    int nface = model.getFaceNum();
    geo::TriCoords tcoords;
    std::array<geo::OARColorf, 3> color;

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(camera, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f persp = geo::perspective(-0.01f,-1000.f);
    geo::mat4f orth = geo::orthographic(-0.01f, 0.01f, 0.01f, -0.01f, -0.01f, -1000.f);
    geo::mat4f trans = orth * persp * cam;

    geo::mat4f py = geo::translate({0.0f, 0.0f, -1.0f, 1.f});
    geo::mat4f ry = geo::rotateY(PI/4.0f);
    geo::mat4f sx = geo::scale(1.5f);
    geo::mat4f model_inv = geo::transpose(geo::inverse(py*ry*sx));
    keep3x3(model_inv);

    for(int i=0;i<nface;i++){
        model.getTriangle(tcoords.worldCoords, i);
        model.getNorm(tcoords.norms, i);

        for(int j=0;j<3;j++){
            color[j] = {1.0f, 0.0f, 0.0f, 1.0f};
            tcoords.worldCoords[j] = py * ry * sx * tcoords.worldCoords[j];
            tcoords.screenCoords[j] = trans * tcoords.worldCoords[j];
            tcoords.screenCoords[j] /= tcoords.screenCoords[j].w; //这一句非常重要
            tcoords.screenCoords[j] = view * tcoords.screenCoords[j];

            tcoords.norms[j] = model_inv * tcoords.norms[j];
        }
        ras::trianglePhong(image, tcoords, color, {1.f, 0.f, -1.f, 1.f}, light, camera);
    }

    image.writeToFile("./SQ.tga");
}

int main(){
    // drawTeapot();
    drawSQ();

    return 0;
}

