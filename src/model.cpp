#include "model.h"
#include "geometry.h"
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model(std::string const & dir){
    std::ifstream in;
    in.open(dir,std::ifstream::in);
    if(in.fail()) return;

    std::string line;
    while(!in.eof()){
        std::getline(in,line);
        std::istringstream iss(line);
        char discard;

        if(line.compare(0,2,"v ")==0){
            iss>>discard;
            geo::vec3f v;
            for(int i=0;i<3;i++) iss>>v[i];
            vertices.push_back(v);
        }
        else if(line.compare(0,3,"vt ")==0){
            iss>>discard>>discard;
            geo::vec2f vt;
            for(int i=0;i<2;i++) iss>>vt[i];
            tex_coords.push_back(vt);
        }
        else if (line.compare(0,3,"vn ")==0) {
            iss>>discard>>discard;
            geo::vec3f vn;
            for(int i=0;i<3;i++) iss>>vn[i];
            norms.push_back(vn);
        }
        else if(line.compare(0,2,"f ")==0){
            iss>>discard;
            size_t fv,ft,fn;
            while(iss>>fv>>discard>>ft>>discard>>fn){
                face_vi.push_back(fv-1);
                face_ti.push_back(ft-1);
                face_ni.push_back(fn-1);
            }
        }
    }
    std::cerr<<"v: "<<vertices.size()<<" t: "<<tex_coords.size()<<" n: "<<norms.size()<<"\n";
    std::cerr<<"f: "<<face_ni.size()/3<<"\n";
}

Model::~Model(){
    vertices.clear();
    tex_coords.clear();
    norms.clear();
    face_ni.clear();
    face_ti.clear();
    face_vi.clear();
}

size_t Model::getFaceNum(){
    return face_ni.size()/3;
}

geo::vec3f Model::getVert(size_t faceid, size_t nth){
    return vertices[face_vi[faceid*3+nth]];
}

bool Model::getTriangle(std::array<geo::vec3f,3> & dist, size_t faceid){
    for(int i=0;i<3;i++){
        dist[i] = vertices[face_vi[faceid*3+i]];
    }
    return true;
}

bool Model::getTriangle(std::array<geo::vec4f,3> & dist, size_t faceid){
    for(int i=0;i<3;i++){
        dist[i] = geo::vec4f(vertices[face_vi[faceid*3+i]],1.f);
    }
    return true;
}

bool Model::getNorm(std::array<geo::vec3f,3> & dist, size_t faceid){
    for(int i=0;i<3;i++){
        dist[i] = norms[face_ni[faceid*3+i]];
    }
    return true;
}

bool Model::getNorm(std::array<geo::vec4f,3> & dist, size_t faceid){
    for(int i=0;i<3;i++){
        dist[i] = geo::vec4f(norms[face_ni[faceid*3+i]],1.f);
    }
    return true;
}
