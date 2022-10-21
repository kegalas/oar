#include "geometry.h"

int main(){
    geo::mat4f mat1;
    geo::vec4f vec(213.f,256.f,0.f, 55.88f);
    mat1[0] = geo::vec4f(1.f, 1.f, 1.f, 1.f);
    mat1[1] = geo::vec4f(1.f, 1.f, 1.f, 3.f);
    mat1[2] = geo::vec4f(1.f, 2.f, 1.f, 1.f);
    mat1[3] = geo::vec4f(1.f, 1.f, 9.f, 1.f);

    std::cout<<geo::det(mat1)<<"\n";

    std::cout<<geo::adjugate(mat1);

    std::cout<<geo::inverse(mat1)<<"\n";

    //geo::Mat<float,1,1> mat;
    //geo::det(mat);

    return 0;
}

