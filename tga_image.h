#ifndef _TGA_IMAGE_H_
#define _TGA_IMAGE_H_

#include <cstdint>
#include <iostream>
#include <string>

#include "geometry.h"

namespace TGAType{
    const unsigned int rgb  = 0;
    const unsigned int rgba = 1;
    const unsigned int grey = 2;
    const unsigned int pixelSize[] = {3,4,1};
}

#pragma pack(push)
#pragma pack(1)

struct TGAHeader{
    std::uint8_t  length{};       //TGA图像信息的长度
    std::uint8_t  colorMapType{}; //0：不使用颜色表，1：使用颜色表
    std::uint8_t  imageType{};    //图像类型，2代表未压缩的真彩色图像，3代表未压缩的黑白图像
    std::uint16_t cMapStart{};    //颜色表首地址
    std::uint16_t cMapLength{};   //颜色表长度
    std::uint8_t  cMapDepth{};    //颜色表位数
    std::uint16_t xOffset{};      //x坐标的起始位置
    std::uint16_t yOffset{};      //y坐标的起始位置
    std::uint16_t width{};        //图形宽度
    std::uint16_t height{};       //图像高度
    std::uint8_t pixelDepth{};   //图像每一个像素占用的位数，例如RGB为24位，RGBA为32位
    std::uint8_t descriptor{};   //图像描述信息，可见http://paulbourke.net/dataformats/tga/

    TGAHeader(){}
    TGAHeader(unsigned int type, std::uint16_t width_, std::uint16_t height_){
        if(type == TGAType::rgb){
            imageType = 2;
            pixelDepth = 24;
        }
        else if(type == TGAType::rgba){
            imageType = 2;
            pixelDepth = 32;
        }
        else if(type == TGAType::grey){
            imageType = 3;
            pixelDepth = 8;
        }
        else{
            std::cerr<<"Error! Wrong TGA Type!\n";
        }

        width  = width_;
        height = height_;

        if(type == TGAType::grey || type == TGAType::rgb){
            descriptor = 0;
        }
        else if(type == TGAType::rgba){
            descriptor = 8;
        }
    }

};

struct TGAFooter{
    std::uint32_t extend{}; //扩展区域
    std::uint32_t custom{}; //开发者自定义区域
    std::uint64_t sig1{};   //签名1
    std::uint64_t sig2{};   //签名2
    std::uint16_t end;      //结束

    TGAFooter(){
        sig1 = 0x4953495645555254;  //TRUEVISI
        sig2 = 0x454C4946582D4E4F;  //ON-XFILE
        end  = 0x002E;           
    }
};

#pragma pack(pop)

class TGAImage{
private:
    std::uint16_t width;
    std::uint16_t height;
    std::uint8_t  *data;
    unsigned int  type;
    bool isFlipVertically;

public:
    TGAImage(std::uint16_t const width_, std::uint16_t const height_, unsigned int const type_);
    TGAImage(std::string const & dir);
    ~TGAImage();

    bool readFromFile(std::string const & dir);
    bool writeToFile(std::string const & dir);
    bool setFragment(std::uint16_t const x, std::uint16_t const y, geo::vec3i const & color);
    bool setFragment(std::uint16_t const x, std::uint16_t const y, geo::vec4i const & color);
    bool flipVertically();

};

#endif
