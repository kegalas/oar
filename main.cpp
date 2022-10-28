#include "tga_image.h"

int main(){
    
    TGAImage image("./test.tga");
    image.flipVertically();
    image.writeToFile("./ttt.tga");

    return 0;
}

