#include "tga_image.h"

int main(){

    TGAImage image(100,100,TGAType::rgb);

    for(int i=0;i<100;i++){
		image.setFragment(i,i,{255,0,0,255});
    }
    
    image.writeToFile("./test.tga");

    return 0;
}

