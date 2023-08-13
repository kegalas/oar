#include "tga_image.h"
#include "raster.h"
#include "model.h"
#include <ctime>
#include <cstdlib>

int const width = 1500;
int const height = 1500;//设置输出图片的长宽

int main(){
    Model model("../obj/african_head.obj");//读取我们的模型
    TGAImage image(width,height,TGAType::rgb);//新建一个图对象
    int nface = model.getFaceSize();//获取三角面的总数
    std::array<geo::vec4f,3> vert;//读取顶点坐标
    std::array<geo::OARColor,3> color;//设置顶点颜色
    std::array<geo::vec2i,3> screen;//把顶点的空间坐标转化到屏幕像素坐标上

    for(int i=0;i<nface;i++){
        model.getTriangle(vert, i);//把序号为i的三角形的顶点全部读入vert
        for(int j=0;j<3;j++){
            color[j] = geo::OARColor(255,255,255,255);//设置颜色为全白
            screen[j] = ras::world2screen(vert[j],width,height);//转换坐标，函数定义见下
        }
        ras::triangle(image,screen,color);//绘制三角形i号
    }
    image.writeToFile("./af.tga");//写入图像文件

    return 0;
}