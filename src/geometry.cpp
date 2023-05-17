#include "geometry.h"

////////////////////////////////////////////////////////////////////////////////

template<> template<>
geo::Vec<float,4>::Vec(geo::Vec<float, 2> const & v, float const z_, float const w_){
    x = v.x;
    y = v.y;
    z = z_;
    w = w_;
}

template<> template<>
geo::Vec<float,4>::Vec(geo::Vec<float, 3> const & v, float const w_){
    x = v.x;
    y = v.y;
    z = v.z;
    w = w_;
}

template<> template<>
geo::Vec<float,4>::Vec(geo::Vec<int, 2> const & v, int const z_, int const w_){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
    z = static_cast<float>(z_);
    w = static_cast<float>(w_);
}

template<> template<>
geo::Vec<float,4>::Vec(geo::Vec<int, 3> const & v, int const w_){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
    z = static_cast<float>(v.z);
    w = static_cast<float>(w_);
}

template<> template<>
geo::Vec<float,4>::Vec(geo::Vec<int,4> const & v){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
    z = static_cast<float>(v.z);
    w = static_cast<float>(v.w);
}

template<> template<>
geo::Vec<int,4>::Vec(geo::Vec<int, 2> const & v, int const z_, int const w_){
    x = v.x;
    y = v.y;
    z = z_;
    w = w_;
}

template<> template<>
geo::Vec<int,4>::Vec(geo::Vec<int, 3> const & v, int const w_){
    x = v.x;
    y = v.y;
    z = v.z;
    w = w_;
}

template<> template<>
geo::Vec<int,4>::Vec(geo::Vec<float, 2> const & v, float const z_, float const w_){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
    z = static_cast<int>(z_ + 0.5f);
    w = static_cast<int>(w_ + 0.5f);
}

template<> template<>
geo::Vec<int,4>::Vec(geo::Vec<float, 3> const & v, float const w_){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
    z = static_cast<int>(v.z + 0.5f);
    w = static_cast<int>(w_ + 0.5f);
}

template<> template<>
geo::Vec<int,4>::Vec(geo::Vec<float,4> const & v){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
    z = static_cast<int>(v.z + 0.5f);
    w = static_cast<int>(v.w + 0.5f);
}

////////////////////////////////////////////////////////////////////////////////

template<> template<>
geo::Vec<float,3>::Vec(geo::Vec<float, 2> const & v, float const z_){
    x = v.x;
    y = v.y;
    z = z_;
}

template<> template<>
geo::Vec<float,3>::Vec(geo::Vec<float, 4> const & v){
    x = v.x;
    y = v.y;
    z = v.z;
}

template<> template<>
geo::Vec<float,3>::Vec(geo::Vec<int, 2> const & v, int const z_){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
    z = static_cast<float>(z_);
}

template<> template<>
geo::Vec<float,3>::Vec(geo::Vec<int, 3> const & v){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
    z = static_cast<float>(v.z);
}

template<> template<>
geo::Vec<float,3>::Vec(geo::Vec<int, 4> const & v){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
    z = static_cast<float>(v.z);
}

template<> template<>
geo::Vec<int,3>::Vec(geo::Vec<int, 2> const & v, int const z_){
    x = v.x;
    y = v.y;
    z = z_;
}

template<> template<>
geo::Vec<int,3>::Vec(geo::Vec<int, 4> const & v){
    x = v.x;
    y = v.y;
    z = v.z;
}

template<> template<>
geo::Vec<int,3>::Vec(geo::Vec<float, 2> const & v, float const z_){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
    z = static_cast<int>(z_ + 0.5f);
}

template<> template<>
geo::Vec<int,3>::Vec(geo::Vec<float, 3> const & v){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
    z = static_cast<int>(v.z + 0.5f);
}

template<> template<>
geo::Vec<int,3>::Vec(geo::Vec<float, 4> const & v){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
    z = static_cast<int>(v.z + 0.5f);
}

////////////////////////////////////////////////////////////////////////////////

template<> template<>
geo::Vec<float,2>::Vec(geo::Vec<float, 3> const & v){
    x = v.x;
    y = v.y;
}

template<> template<>
geo::Vec<float,2>::Vec(geo::Vec<float, 4> const & v){
    x = v.x;
    y = v.y;
}

template<> template<>
geo::Vec<float,2>::Vec(geo::Vec<int, 2> const & v){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
}

template<> template<>
geo::Vec<float,2>::Vec(geo::Vec<int, 3> const & v){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
}

template<> template<>
geo::Vec<float,2>::Vec(geo::Vec<int, 4> const & v){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
}

template<> template<>
geo::Vec<int,2>::Vec(geo::Vec<int, 3> const & v){
    x = v.x;
    y = v.y;
}

template<> template<>
geo::Vec<int,2>::Vec(geo::Vec<int, 4> const & v){
    x = v.x;
    y = v.y;
}

template<> template<>
geo::Vec<int,2>::Vec(geo::Vec<float, 2> const & v){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
}

template<> template<>
geo::Vec<int,2>::Vec(geo::Vec<float, 3> const & v){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
}

template<> template<>
geo::Vec<int,2>::Vec(geo::Vec<float, 4> const & v){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
}

////////////////////////////////////////////////////////////////////////////////

geo::Vec<int,4> geo::toOARColor(geo::Vec<int,4> const & v){
    OARColor ret;
    for(int i=0;i<4;i++){
        if(v[i]<0) ret[i] = 0;
        else if(v[i]>255) ret[i] = 255;
        else ret[i] = v[i];
    }

    return ret;
}

geo::Vec<int,4> geo::toOARColor(geo::Vec<float,4> const & v){
    OARColor ret;
    for(int i=0;i<4;i++){
        ret[i] = static_cast<int>(v[i]*255.f+0.5f);
        if (ret[i]<0) ret[i] = 0;
        else if(ret[i]>255) ret[i] = 255;
    }

    return ret;
}

geo::Vec<int,4> geo::toOARColor(geo::Vec<int,3> const & v){
    OARColor ret;
    for(int i=0;i<3;i++){
        if(v[i]<0) ret[i] = 0;
        else if(v[i]>255) ret[i] = 255;
        else ret[i] = v[i];
    }
    ret[3] = 255;

    return ret;
}

geo::Vec<int,4> geo::toOARColor(geo::Vec<float,3> const & v){
    OARColor ret;
    for(int i=0;i<3;i++){
        ret[i] = static_cast<int>(v[i]*255.f+0.5f);
        if (ret[i]<0) ret[i] = 0;
        else if(ret[i]>255) ret[i] = 255;
    }
    ret[3] = 255;

    return ret;
}

geo::Vec<int,4> geo::toOARColor(int const & v){
    OARColor ret;
    for(int i=0;i<3;i++){
        if(v<0) ret[i] = 0;
        else if(v>255) ret[i] = 255;
        else ret[i] = v;
    }
    ret[3] = 255;

    return ret;
}

geo::Vec<int,4> geo::toOARColor(float const & v){
    OARColor ret;
    for(int i=0;i<3;i++){
        ret[i] = static_cast<int>(v*255.f+0.5f);
        if (ret[i]<0) ret[i] = 0;
        else if(ret[i]>255) ret[i] = 255;
    }
    ret[3] = 255;

    return ret;
}

std::tuple<float,float,float> geo::getBarycentric(geo::vec2f points[], float x, float y){
    geo::vec2f const & pa = points[0];
    geo::vec2f const & pb = points[1];
    geo::vec2f const & pc = points[2];

    // Fundamentals of Computer Graphics(Fifth Edition), P52
    float beta = ((pa.y-pc.y)*x + (pc.x-pa.x)*y + pa.x*pc.y - pc.x*pa.y) / ((pa.y-pc.y)*pb.x + (pc.x-pa.x)*pb.y + pa.x*pc.y - pc.x*pa.y);
    float gamma = ((pa.y-pb.y)*x + (pb.x-pa.x)*y + pa.x*pb.y - pb.x*pa.y) / ((pa.y-pb.y)*pc.x + (pb.x-pa.x)*pc.y + pa.x*pb.y - pb.x*pa.y);
    float alpha = 1.f - beta - gamma;
    return std::tuple<float,float,float>(alpha,beta,gamma);
}

std::tuple<float,float,float> geo::getBarycentric(geo::vec2i points[], int x_, int y_){
    float x = static_cast<float>(x_), y = static_cast<float>(y_);
    geo::vec2f const & pa = static_cast<geo::vec2f >(points[0]);
    geo::vec2f const & pb = static_cast<geo::vec2f >(points[1]);
    geo::vec2f const & pc = static_cast<geo::vec2f >(points[2]);

    float beta = ((pa.y-pc.y)*x + (pc.x-pa.x)*y + pa.x*pc.y - pc.x*pa.y) / ((pa.y-pc.y)*pb.x + (pc.x-pa.x)*pb.y + pa.x*pc.y - pc.x*pa.y);
    float gamma = ((pa.y-pb.y)*x + (pb.x-pa.x)*y + pa.x*pb.y - pb.x*pa.y) / ((pa.y-pb.y)*pc.x + (pb.x-pa.x)*pc.y + pa.x*pb.y - pb.x*pa.y);
    float alpha = 1.f - beta - gamma;
    return std::tuple<float,float,float>(alpha,beta,gamma);
}
