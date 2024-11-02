#include "tga_image.h"
#include "raster.h"
#include "model.h"
#include <ctime>
#include <cstdlib>
#include <memory>

int const width = 1500;
int const height = 1500;
geo::vec4f lightPos = {0.f, 0.f, 10.f, 1.f};
geo::OARColorf light = {1.f, 1.f, 1.f, 1.f};
//geo::vec4f camera = {-1.f, 0.f, 1.f, 1.f};
geo::vec4f camera = {0.f, 0.f, 2.f, 1.f};
float const PI = std::acos(-1.f);

void keep3x3(geo::mat4f & mat){
    mat[3][0] = 0.0f; mat[3][1] = 0.0f; mat[3][2] = 0.0f; mat[3][3] = 1.0f;
    mat[0][3] = 0.0f; mat[1][3] = 0.0f; mat[2][3] = 0.0f;
}

void drawTeapot(){
    Model model("../obj/teapot.obj");
    TGAImage image(width,height,TGAType::rgb);
    int nface = model.getFaceNum();
    std::array<geo::OARColorf, 3> color;
    geo::TriCoords tcoords;

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(camera, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f proj = geo::perspectiveFov(PI/2.0f, 1.0f*width/height, -0.01f, -1000.0f);
    geo::mat4f trans = proj * cam;
    auto zbuf = std::make_unique<float[]>(width*height);
    std::fill(zbuf.get(), zbuf.get()+width*height, -std::numeric_limits<float>::max());

    auto paint = [&](geo::mat4f trans_mat, TGAImage &out){
        geo::mat4f py = geo::translate({0.0f, 0.0f, 0.1f, 1.f});
        geo::mat4f rx = geo::rotateX(PI/4.0f);
        geo::mat4f ry = geo::rotateY(-PI/8.0f);
        geo::mat4f sx = geo::scale(1.5f);
        geo::mat4f trans_inv = geo::transpose(geo::inverse(py*ry*rx*sx));
        keep3x3(trans_inv);

        for(int i=0;i<nface;i++){
            model.getTriangle(tcoords.worldCoords, i);
            model.getNorm(tcoords.norms, i);

            for(int j=0;j<3;j++){
                color[j] = {1.0f, 1.0f, 1.0f, 1.0f};
                tcoords.worldCoords[j] = py*ry*rx*sx*tcoords.worldCoords[j];
                tcoords.screenCoords[j] = trans_mat * tcoords.worldCoords[j];
                tcoords.screenCoords[j] /= tcoords.screenCoords[j].w; //这一句非常重要
                tcoords.screenCoords[j] = view * tcoords.screenCoords[j];

                tcoords.norms[j] = trans_inv * tcoords.norms[j];
            }
            ras::trianglePhong(out, tcoords, color, lightPos, light, camera, zbuf.get());
        }

        // for(int i=550;i<600;i++){
        //     model.getTriangle(tcoords.worldCoords, i);
        //     model.getNorm(tcoords.norms, i);

        //     for(int j=0;j<3;j++){
        //         color[j] = {1.0f, 1.0f, 1.0f, 1.0f};
        //         tcoords.worldCoords[j] = py*ry*rx*sx*tcoords.worldCoords[j];
        //         tcoords.screenCoords[j] = trans_mat * tcoords.worldCoords[j];
        //         tcoords.screenCoords[j] /= tcoords.screenCoords[j].w; //这一句非常重要
        //         tcoords.screenCoords[j] = view * tcoords.screenCoords[j];

        //         tcoords.norms[j] = trans_inv * tcoords.norms[j];
        //     }
        //     ras::trianglePhong(out, tcoords, color, lightPos, light, camera, zbuf.get());
        // }

        // for(int i=1500;i<1750;i++){
        //     model.getTriangle(tcoords.worldCoords, i);
        //     model.getNorm(tcoords.norms, i);

        //     for(int j=0;j<3;j++){
        //         color[j] = {1.0f, 1.0f, 1.0f, 1.0f};
        //         tcoords.worldCoords[j] = py*ry*rx*sx*tcoords.worldCoords[j];
        //         tcoords.screenCoords[j] = trans_mat * tcoords.worldCoords[j];
        //         tcoords.screenCoords[j] /= tcoords.screenCoords[j].w; //这一句非常重要
        //         tcoords.screenCoords[j] = view * tcoords.screenCoords[j];

        //         tcoords.norms[j] = trans_inv * tcoords.norms[j];
        //     }
        //     ras::trianglePhong(out, tcoords, color, lightPos, light, camera, zbuf.get());
        // }

        // for(int i=4000;i<5000;i++){
        //     model.getTriangle(tcoords.worldCoords, i);
        //     model.getNorm(tcoords.norms, i);

        //     for(int j=0;j<3;j++){
        //         color[j] = {1.0f, 1.0f, 1.0f, 1.0f};
        //         tcoords.worldCoords[j] = py*ry*rx*sx*tcoords.worldCoords[j];
        //         tcoords.screenCoords[j] = trans_mat * tcoords.worldCoords[j];
        //         tcoords.screenCoords[j] /= tcoords.screenCoords[j].w; //这一句非常重要
        //         tcoords.screenCoords[j] = view * tcoords.screenCoords[j];

        //         tcoords.norms[j] = trans_inv * tcoords.norms[j];
        //     }
        //     ras::trianglePhong(out, tcoords, color, lightPos, light, camera, zbuf.get());
        // }
    };

    paint(trans, image);
    image.writeToFile("./tp.tga");
}

void drawSQ(){
    Model model("../obj/sq.obj");
    TGAImage image(width,height,TGAType::rgb);
    int nface = model.getFaceNum();
    std::array<geo::OARColorf, 3> color;
    geo::TriCoords tcoords;

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(camera, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f proj = geo::perspectiveFov(PI/2.0f, 1.0f*width/height, -0.01f, -1000.0f);
    geo::mat4f trans = proj * cam;
    auto zbuf = std::make_unique<float[]>(width*height);
    std::fill(zbuf.get(), zbuf.get()+width*height, -std::numeric_limits<float>::max());

    auto paint = [&](geo::mat4f trans_mat, TGAImage &out, float tmp){
        geo::mat4f py = geo::translate({tmp, 0.0f, 0.0f, 1.f});
        geo::mat4f rx = geo::rotateX(PI/4.0f);
        geo::mat4f ry = geo::rotateY(-PI/8.0f);
        geo::mat4f sx = geo::scale(1.5f);
        geo::mat4f model_m = py;

        geo::mat4f trans_inv = geo::transpose(geo::inverse(model_m));
        keep3x3(trans_inv);

        for(int i=0;i<nface;i++){
            model.getTriangle(tcoords.worldCoords, i);
            model.getNorm(tcoords.norms, i);

            for(int j=0;j<3;j++){
                color[j] = {1.0f, 1.0f, 1.0f, 1.0f};
                tcoords.worldCoords[j] = model_m*tcoords.worldCoords[j];
                tcoords.screenCoords[j] = trans_mat * tcoords.worldCoords[j];
                tcoords.screenCoords[j] /= tcoords.screenCoords[j].w; //这一句非常重要
                tcoords.screenCoords[j] = view * tcoords.screenCoords[j];

                tcoords.norms[j] = trans_inv * tcoords.norms[j];
            }
            ras::trianglePhong(out, tcoords, color, lightPos, light, camera, zbuf.get());
        }
    };

    paint(trans, image, -0.5f);
    paint(trans, image, 0.5f);
    image.writeToFile("./sq.tga");
}

int main(){
    drawTeapot();
    // drawSQ();

    return 0;
}

