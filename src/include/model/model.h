#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include <iostream>
#include <array>

#include "math/geometry.h"

class Model{
private:
    std::vector<geo::vec3f> vertices{};
    std::vector<geo::vec2f> tex_coords{};
    std::vector<geo::vec3f> norms{};
    std::vector<size_t> face_vi{};
    std::vector<size_t> face_ti{};
    std::vector<size_t> face_ni{};

public:
    Model(std::string const & dir);
    ~Model();
    
    size_t getFaceNum();
    geo::vec3f getVert(size_t faceid, size_t nth);
    bool getTriangle(std::array<geo::vec3f,3> & dist, size_t faceid);
    bool getTriangle(std::array<geo::vec4f,3> & dist, size_t faceid);
    bool getNorm(std::array<geo::vec3f,3> & dist, size_t faceid);
    bool getNorm(std::array<geo::vec4f,3> & dist, size_t faceid);
    bool getUV(std::array<geo::vec2f, 3> & dist, size_t faceid);
};

#endif
