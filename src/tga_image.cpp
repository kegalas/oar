#include <fstream>
#include <cassert>
#include <cstring>

#include "tga_image.h"

TGAImage::TGAImage(std::uint16_t const width_, std::uint16_t const height_, unsigned int const type_){
    width               = width_;
    height              = height_;
    type                = type_;
    data                = new std::uint8_t[width*height*TGAType::pixelSize[type]];
    isFlipVertically    = 0;
    std::fill(data,data+width*height*TGAType::pixelSize[type],0);
}

TGAImage::TGAImage(std::string const & dir){
    readFromFile(dir);
}

TGAImage::~TGAImage(){
    delete[] data;
}

bool TGAImage::readFromFile(std::string const & dir){
    std::ifstream ifs;
    ifs.open(dir, std::ios::binary);

    if(!ifs.is_open()){
        std::cerr << "Error! Can't open file: " << dir << "\n";
        ifs.close();
        return false;
    }

    TGAHeader header;
    ifs.read(reinterpret_cast<char *>(&header), sizeof(header));
    if(!ifs.good()){
        std::cerr << "An error occured while reading the header. File: " << dir << "\n";
        ifs.close();
        return false;
    }

    if(header.descriptor&0x20){
        isFlipVertically = 1;
    }

    width  = header.width;
    height = header.height;
    if(width<=0||height<=0){
        std::cerr << "Error! Bad image width/height. File: " << dir << "\n";
        ifs.close();
        return false;
    }

    if(header.imageType == 2){
        if(header.pixelDepth == 24){
            type = TGAType::rgb;
        }
        else if(header.pixelDepth == 32){
            type = TGAType::rgba;
        }
        else{
            std::cerr << "Error! Unknown pixel depth. File: " << dir << "\n";
            ifs.close();
            return false;
        }
    } 
    else if(header.imageType == 3){
        type = TGAType::grey;
        if(header.pixelDepth != 8){
            std::cerr << "Error! Unknown pixel depth. File: " << dir << "\n";
            ifs.close();
            return false;
        }
    }
    else{
        std::cerr << "Error! Unknown image type. File: " << dir << "\n";
        ifs.close();
        return false;
    }

    int pixelSize = TGAType::pixelSize[type];

    data = new std::uint8_t[width * height * pixelSize];

    ifs.read(reinterpret_cast<char *>(data), pixelSize*width*height);
    if(!ifs.good()){
        std::cerr << "An error occured while reading the data. File: " << dir << "\n";
        ifs.close();
        return false;
    }

    std::cerr << width << "x" << height << "/" << pixelSize*8 << "\n";
    ifs.close();

    if(isFlipVertically){
        flipVertically();
    }

    return true;
}

bool TGAImage::writeToFile(std::string const & dir){
    std::ofstream ofs;
    ofs.open(dir, std::ios::binary);

    if(!ofs.is_open()){
        std::cerr << "Error! Can't open file: " << dir << "\n";
        ofs.close();
        return false;
    }

    TGAHeader header(type, width, height);
    if(isFlipVertically){
        header.descriptor |= 0x20;
    }

    ofs.write(reinterpret_cast<char *>(&header), sizeof(header));
    if(!ofs.good()){
        std::cerr << "An error occured while writing the header. File: " << dir << "\n";
        ofs.close();
        return false;
    }

    int pixelSize = TGAType::pixelSize[type];
    ofs.write(reinterpret_cast<char *>(data), pixelSize*width*height);
    if(!ofs.good()){
        std::cerr << "An error occured while writing the data. File: " << dir << "\n";
        ofs.close();
        return false;
    }

    TGAFooter footer;
    ofs.write(reinterpret_cast<char *>(&footer), sizeof(footer));
    if(!ofs.good()){
        std::cerr << "An error occured while writing the footer. File: " << dir << "\n";
        ofs.close();
        return false;
    }

    std::cerr << "Write to " << dir << " " << width << "x" << height << "/" << pixelSize*8 << "\n";
    ofs.close();

    return true;
}

bool TGAImage::setFragment(std::uint16_t x, std::uint16_t y, geo::OARColor color){
    x = std::max(std::uint16_t(0),x);x = std::min(std::uint16_t(width-1),x);
    y = std::max(std::uint16_t(0),y);y = std::min(std::uint16_t(height-1),y);
    color.r = std::max(0,color.r);color.r = std::min(255,color.r);
    color.g = std::max(0,color.g);color.g = std::min(255,color.g);
    color.b = std::max(0,color.b);color.b = std::min(255,color.b);
    color.a = std::max(0,color.a);color.a = std::min(255,color.a);

    int pixelSize = TGAType::pixelSize[type];
    size_t index = (y*width + x)*pixelSize;

    if(type==TGAType::grey){
        data[index] = static_cast<std::uint8_t> (color.r/3.0f+color.g/3.0f+color.b/3.0f+0.5f);
    }
    else if(type==TGAType::rgb || type==TGAType::rgba){
        data[index] = color.b;
        data[index+1] = color.g;
        data[index+2] = color.r;

        if(type==TGAType::rgba){
            data[index+3] = color.a;
        }
    }
    else{
        std::cerr<<"An error occured while set fragment\n";
        return false;
    }

    return true;
}

geo::OARColor TGAImage::getFragment(std::uint16_t x, std::uint16_t y){

}

bool TGAImage::flipVertically(){
    int pixelSize = TGAType::pixelSize[type];
    int half = height/2;
    isFlipVertically = isFlipVertically^1;

    for(int i=0;i<width;i++){
        for(int j=0;j<half;j++){
            for(int k=0;k<pixelSize;k++){
                std::swap(data[(i+j*width)*pixelSize+k], data[(i+(height-1-j)*width)*pixelSize+k]);
            }
        }
    }

    return true;
}
