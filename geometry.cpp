#include "geometry.h"

////////////////////////////////////////////////////////////////////////////////

template<> template<>
geo::Vec<float,4>::Vec(geo::Vec<float, 3> const & v, float const w_){
    x = v.x;
    y = v.y;
    z = v.z;
    w = w_;
}

template<> template<>
geo::Vec<float,4>::Vec(geo::Vec<float, 2> const & v, float const z_, float const w_){
    x = v.x;
    y = v.y;
    z = z_;
    w = w_;
}

template<> template<>
geo::Vec<float,4>::Vec(geo::Vec<int, 3> const & v, int const w_){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
    z = static_cast<float>(v.z);
    w = static_cast<float>(w_);
}

template<> template<>
geo::Vec<float,4>::Vec(geo::Vec<int, 2> const & v, int const z_, int const w_){
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
    z = static_cast<float>(z_);
    w = static_cast<float>(w_);
}

template<> template<>
geo::Vec<int,4>::Vec(geo::Vec<int, 3> const & v, int const w_){
    x = v.x;
    y = v.y;
    z = v.z;
    w = w_;
}

template<> template<>
geo::Vec<int,4>::Vec(geo::Vec<int, 2> const & v, int const z_, int const w_){
    x = v.x;
    y = v.y;
    z = z_;
    w = w_;
}

template<> template<>
geo::Vec<int,4>::Vec(geo::Vec<float, 3> const & v, float const w_){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
    z = static_cast<int>(v.z + 0.5f);
    w = static_cast<int>(w_ + 0.5f);
}

template<> template<>
geo::Vec<int,4>::Vec(geo::Vec<float, 2> const & v, float const z_, float const w_){
    x = static_cast<int>(v.x + 0.5f);
    y = static_cast<int>(v.y + 0.5f);
    z = static_cast<int>(z_ + 0.5f);
    w = static_cast<int>(w_ + 0.5f);
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

geo::Vec<int,3> geo::toRGB(geo::Vec<int,3> const & v){
    geo::Vec<int,3> ret;
    if(v.r<0) ret.r = 0;
    else if(v.r>255) ret.r = 255;
    else ret.r = v.r;

    if(v.g<0) ret.g = 0;
    else if(v.g>255) ret.g = 255;
    else ret.g = v.g;

    if(v.b<0) ret.b = 0;
    else if(v.b>255) ret.b = 255;
    else ret.b = v.b;

    return ret;
}

geo::Vec<int,3> geo::toRGB(geo::Vec<float,3> const & v){
    geo::Vec<int,3> ret;
    
    ret.r = static_cast<int>(v.r*255.f+0.5f);
    if (ret.r<0) ret.r = 0;
    else if(ret.r>255) ret.r = 255;

    ret.g = static_cast<int>(v.g*255.f+0.5f);
    if (ret.g<0) ret.g = 0;
    else if(ret.g>255) ret.g = 255;

    ret.b = static_cast<int>(v.b*255.f+0.5f);
    if (ret.b<0) ret.b = 0;
    else if(ret.b>255) ret.b = 255;

    return ret;
}

geo::Vec<int,4> geo::toRGBA(geo::Vec<int,4> const & v){
    geo::Vec<int,4> ret;
    if(v.r<0) ret.r = 0;
    else if(v.r>255) ret.r = 255;
    else ret.r = v.r;

    if(v.g<0) ret.g = 0;
    else if(v.g>255) ret.g = 255;
    else ret.g = v.g;

    if(v.b<0) ret.b = 0;
    else if(v.b>255) ret.b = 255;
    else ret.b = v.b;

    if(v.a<0) ret.a = 0;
    else if(v.a>255) ret.a = 255;
    else ret.a = v.a;

    return ret;
}

geo::Vec<int,4> geo::toRGBA(geo::Vec<float,4> const & v){
    Vec<int,4> ret;
    
    ret.r = static_cast<int>(v.r*255.f+0.5f);
    if (ret.r<0) ret.r = 0;
    else if(ret.r>255) ret.r = 255;

    ret.g = static_cast<int>(v.g*255.f+0.5f);
    if (ret.g<0) ret.g = 0;
    else if(ret.g>255) ret.g = 255;

    ret.b = static_cast<int>(v.b*255.f+0.5f);
    if (ret.b<0) ret.b = 0;
    else if(ret.b>255) ret.b = 255;

    ret.a = static_cast<int>(v.a*255.f+0.5f);
    if (ret.a<0) ret.a = 0;
    else if(ret.a>255) ret.a = 255;

    return ret;
}
    
