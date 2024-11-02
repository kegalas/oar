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

geo::mat4f geo::mat3to4(geo::mat3f const & m){
    geo::mat4f ret;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            ret[i][j] = m[i][j];
        }
    }
    ret[3][3] = 1.f;
    return ret;
}

std::tuple<float,float,float> geo::getBarycentric(
    std::array<geo::vec2f,3> const & tri,
    geo::vec2f pt
){
    // Fundamentals of Computer Graphics(Fifth Edition), P52
    // https://kegalas.top/p/%E8%AE%A1%E7%AE%97%E6%9C%BA%E5%9B%BE%E5%BD%A2%E5%AD%A6%E5%9F%BA%E7%A1%80%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0-%E6%95%B0%E5%AD%A6%E5%9F%BA%E7%A1%80/#%E9%87%8D%E5%BF%83%E5%9D%90%E6%A0%87%E7%B3%BB
    geo::vec2f pa = pt-tri[0];
    geo::vec2f ab = tri[0]-tri[1];
    geo::vec2f ac = tri[0]-tri[2];
    geo::vec3f v1 = geo::vec3f(pa.x,ab.x,ac.x);
    geo::vec3f v2 = geo::vec3f(pa.y,ab.y,ac.y);
    geo::vec3f v = geo::cross(v1,v2);
    v = v/v.x;

    float beta = v.y;
    float gamma = v.z;
    float alpha = 1.f - beta - gamma;
    return std::tuple<float,float,float>(alpha,beta,gamma);
}

std::tuple<float,float,float> geo::getBarycentric(
    std::array<geo::vec2i,3> const & tri,
    geo::vec2i pt
){
    geo::vec2i pa = pt-tri[0];
    geo::vec2i ab = tri[0]-tri[1];
    geo::vec2i ac = tri[0]-tri[2];
    geo::vec3f v1 = geo::vec3f(pa.x*1.f,ab.x*1.f,ac.x*1.f);
    geo::vec3f v2 = geo::vec3f(pa.y*1.f,ab.y*1.f,ac.y*1.f);
    geo::vec3f v = geo::cross(v1,v2);

    // 如果三角形退化成一条线或者一个点
    if (std::abs(v.x)<1e-9) return std::tuple<float,float,float>(-1.f, -1.f, -1.f);

    v = v/v.x;

    float beta = v.y;
    float gamma = v.z;
    float alpha = 1.f - beta - gamma;
    return std::tuple<float,float,float>(alpha,beta,gamma);
}

geo::mat4f geo::translate(vec4f const & v){
    mat4f ret;
    ret[0][3] = v.x / v.w;
    ret[1][3] = v.y / v.w;
    ret[2][3] = v.z / v.w;

    return ret;
}

geo::mat4f geo::scale(float t){
    mat4f ret;
    ret[0][0] = t;
    ret[1][1] = t;
    ret[2][2] = t;

    return ret;
}

geo::mat4f geo::rotateZ(float ridian){
    mat4f ret;

    ret[0][0] = std::cos(ridian);
    ret[0][1] = -std::sin(ridian);
    ret[1][0] = std::sin(ridian);
    ret[1][1] = std::cos(ridian);

    return ret;
}

geo::mat4f geo::rotateX(float ridian){
    mat4f ret;

    ret[1][1] = std::cos(ridian);
    ret[1][2] = -std::sin(ridian);
    ret[2][1] = std::sin(ridian);
    ret[2][2] = std::cos(ridian);

    return ret;
}

geo::mat4f geo::rotateY(float ridian){
    mat4f ret;

    ret[0][0] = std::cos(ridian);
    ret[0][2] = std::sin(ridian);
    ret[2][0] = -std::sin(ridian);
    ret[2][2] = std::cos(ridian);

    return ret;
}

geo::mat4f geo::viewport(int width, int height){
    mat4f ret;
    ret[0][0] = width/2.f;
    ret[1][1] = height/2.f;
    ret[0][3] = width/2.f;
    ret[1][3] = height/2.f;

    return ret;
}

geo::mat4f geo::orthographic(float left, float right, float top, float bottom, float near, float far){
    mat4f ret;

    ret[0][0] = 2.f/(right-left);
    ret[1][1] = 2.f/(top-bottom);
    ret[2][2] = 2.f/(near-far);

    ret[0][3] = -(right+left)/(right-left);
    ret[1][3] = -(top+bottom)/(top-bottom);
    ret[2][3] = -(near+far)/(near-far);

    ret[3][3] = 1.f;

    return ret;
}

geo::mat4f geo::cameraView(vec4f const & pos, vec4f const & gaze, vec4f const & up){
    //gaze 是z轴负半轴方向，坐标是右手系

    mat4f trans,ro;
    trans[0][3] = -pos.x / pos.w;
    trans[1][3] = -pos.y / pos.w;
    trans[2][3] = -pos.z / pos.w;
    vec3f gaze_ = geo::normalized(vec3f(gaze / gaze.w));
    vec3f up_ = geo::normalized(vec3f(up / up.w));

    vec3f tmp = geo::cross(gaze_,up_);
    ro[0][0] = tmp.x;ro[0][1] = tmp.y;ro[0][2] = tmp.z;
    ro[1][0] = up_.x;ro[1][1] = up_.y;ro[1][2] = up_.z;
    ro[2][0] = -gaze_.x;ro[2][1] = -gaze_.y;ro[2][2] = -gaze_.z;

    return ro*trans;
}

geo::mat4f geo::perspective(float near, float far){
    mat4f ret;

    ret[0][0] = near;
    ret[1][1] = near;
    ret[2][2] = near+far;
    ret[2][3] = -far*near;
    ret[3][2] = 1.f;
    ret[3][3] = 0.f;

    return ret;
}

geo::mat4f geo::perspectiveFov(float fovy, float aspect, float near, float far){
    mat4f ret;

    // 以下的计算其实可以分式化简，但出于直观就保留原样了
    float tanv = std::tan(fovy/2.f);
    float t = std::abs(near) * tanv;
    float b = -t;
    float r = t * aspect;
    float l = -r;

    ret[0][0] = 2*near/(r-l); ret[0][2] = (l+r)/(l-r);
    ret[1][1] = 2*near/(t-b); ret[1][2] = (b+t)/(b-t);
    ret[2][2] = (near+far)/(near-far);  ret[2][3] = (2*near*far)/(far-near);
    ret[3][2] = 1.f;
    ret[3][3] = 0.f;

    return ret;
}
