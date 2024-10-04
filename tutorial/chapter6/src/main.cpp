#include "tga_image.h"
#include "raster.h"
#include "model.h"
#include <ctime>
#include <cstdlib>

int const width = 1500;
int const height = 1500;
geo::vec4f lightPos = {3.f, 3.f, 3.f, 1.f};
geo::OARColorf light = {1.f, 1.f, 1.f, 1.f};
geo::vec4f camera = {0.f, 0.f, 1.f, 1.f};
float const PI = std::acos(-1.f);

void drawTeapot(){
    Model model("../obj/teapot.obj");
    TGAImage image(width,height,TGAType::rgb);
    int nface = model.getFaceNum();
    std::array<geo::vec4f,3> vert;
    std::array<geo::OARColor,3> color;
    std::array<geo::vec4f, 3> norm;
    std::array<geo::vec4f, 3> screen;
    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f};

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(camera, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f persp = geo::perspective(-0.01f,-1000.f);
    geo::mat4f orth = geo::orthographic(-0.01f, 0.01f, 0.01f, -0.01f, -0.01f, -1000.f);
    geo::mat4f trans = orth * persp * cam;

    auto paint = [&](geo::mat4f trans_mat, TGAImage &out){
        for(int i=8;i>=0;i--){
            geo::mat4f py = geo::translate({2.0f,-1.0f,-1.0f-i*2.0f,1.f});
            geo::mat4f sx = geo::scale(1.5f);
            geo::mat4f trans_inv = geo::transpose(geo::inverse(py*sx));

            for(int i=0;i<nface;i++){
                model.getTriangle(vert, i);
                model.getNorm(norm, i);

                bool check = 1;
                for(int j=0;j<3;j++){
                    geo::vec4f l = geo::normalized(lightPos-py*sx*vert[j]);
                    geo::vec4f v = geo::normalized(camera-py*sx*vert[j]);
                    geo::vec4f h = geo::normalized(v+l);
                    float intensity = geo::dot(l,trans_inv*norm[j]);
                    if(intensity<0.f){
                        check = 0;
                        break;
                    }
                    geo::OARColorf ld = kd * light * intensity;
                    geo::OARColorf ls = ks * light * std::pow(std::max(0.f,geo::dot(trans_inv*norm[j],h)), 100.f);
                    geo::OARColorf la = ka * geo::vec4f(.3f, .3f, .3f, 1.f);
                    color[j] = geo::toOARColor(ld+ls+la);
                    screen[j] = trans_mat * py * sx * vert[j];
                    screen[j] /= screen[j].w;//这一句非常重要
                    screen[j] = view * screen[j];
                }
                if(check) ras::triangle(out,screen,color);
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
    std::array<geo::vec4f,3> vert;
    std::array<geo::OARColor,3> color;
    std::array<geo::vec4f, 3> norm;
    std::array<geo::vec4f, 3> screen;
    geo::vec4f kd = {.75f, .75f, .75f, 1.f};
    geo::vec4f ks = {1.f, 1.f, 1.f, 1.f};
    geo::vec4f ka = {.2f, .2f, .2f, 1.f};

    geo::mat4f view = geo::viewport(width, height);
    geo::mat4f cam = geo::cameraView(camera, {0.f,0.f,-1.f,1.f},{0.f,1.f,0.f,1.f});
    geo::mat4f persp = geo::perspective(-0.01f,-1000.f);
    geo::mat4f orth = geo::orthographic(-0.01f, 0.01f, 0.01f, -0.01f, -0.01f, -1000.f);
    geo::mat4f trans = orth * persp * cam;

    geo::mat4f py = geo::translate({0.0f, 0.0f, -1.0f, 1.f});
    geo::mat4f sx;// = geo::scale(1.5f);
    geo::mat4f model_inv = geo::transpose(geo::inverse(py*sx));

    for(int i=0;i<nface;i++){
        model.getTriangle(vert, i);
        model.getNorm(norm, i);

        bool check = 1;
        for(int j=0;j<3;j++){
            geo::vec4f l = geo::normalized(lightPos-py*sx*vert[j]);
            geo::vec4f v = geo::normalized(camera-py*sx*vert[j]);
            geo::vec4f h = geo::normalized(v+l);
            float intensity = geo::dot(l,model_inv*norm[j]);
            if(intensity<0.f){
                check = 0;
                break;
            }
            geo::OARColorf ld = kd * light * intensity;
            geo::OARColorf ls = ks * light * std::pow(std::max(0.f,geo::dot(model_inv*norm[j],h)), 100.f);
            geo::OARColorf la = ka * geo::vec4f(.3f, .3f, .3f, 1.f);
            color[j] = geo::toOARColor(ld+ls+la);
            // color[j] = geo::OARColor({255, 255, 255, 255});
            screen[j] = trans * py * sx * vert[j];
            screen[j] /= screen[j].w;//这一句非常重要
            screen[j] = view * screen[j];
        }
        if(check) ras::triangle(image,screen,color);
    }

    image.writeToFile("./SQ.tga");
}

int main(){
    //drawTeapot();
    drawSQ();

    return 0;
}

