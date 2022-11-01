#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <cassert>
#include <cstddef>
#include <cmath>
#include <iostream>

namespace geo{
////////////////////////////////////////////////////////////////////////////////
    template<class T, size_t dim>
    class Vec{
    public:
        Vec(){
            for(size_t i=0;i<dim;i++){
                data_[i] = T();
            }
        }

        Vec(Vec<T,dim> const & v){
            for(size_t i=0;i<dim;i++){
                data_[i] = v[i];
            }
        }

        T& operator[](const size_t i){
            assert(i<dim && i>=0);
            return data_[i];
        }

        const T& operator[](const size_t i) const {
            assert(i<dim && i>=0);
            return data_[i];
        }

        Vec<T, dim>& operator=(const Vec<T,dim> vec){
            if(this==&vec){
                return *this;
            }

            for(size_t i=0;i<dim;i++){
                this->data_[i] = vec[i];
            }
            
            return *this;
        }

    private:
        T data_[dim];
    };

    template<class T>
    class Vec<T,2>{
    public:
        union{
            struct {T x,y;};
            struct {T s,t;};
            struct {T u,v;};
            T raw[2];
        };

        Vec<T,2>():x(),y(){}

        Vec<T,2>(T x_, T y_):x(x_),y(y_){}

        Vec<T,2>(Vec<T,2> const & v):x(v.x),y(v.y){}

        template<class U> Vec<T,2>(Vec<U,2> const &);
        template<class U> Vec<T,2>(Vec<U,3> const &);
        template<class U> Vec<T,2>(Vec<U,4> const &);

        T& operator[](const size_t i){
            assert(i<2 && i>=0);
            return raw[i];
        }

        const T& operator[](const size_t i) const{
            assert(i<2 && i>=0);
            return raw[i];
        }

        Vec<T, 2>& operator=(const Vec<T,2>& vec){
            if(this==&vec){
                return *this;
            }
            for(size_t i=0;i<2;i++){
                this->raw[i] = vec[i];
            }
            
            return *this;
        }

    };

    
    template<class T>
    class Vec<T,3>{
    public:
        union{
            struct {T x,y,z;};
            struct {T r,g,b;};
            T raw[3];
        };

        Vec<T,3>():x(),y(),z(){}

        Vec<T,3>(T x_, T y_, T z_):x(x_),y(y_),z(z_){}

        Vec<T,3>(Vec<T,3> const & v):x(v.x),y(v.y),z(v.z){}

        template<class U> Vec<T,3>(Vec<U,2> const &, U const);
        template<class U> Vec<T,3>(Vec<U,3> const &);
        template<class U> Vec<T,3>(Vec<U,4> const &);

        T& operator[](const size_t i){
            assert(i<3 && i>=0);
            return raw[i];
        }

        const T& operator[](const size_t i) const{
            assert(i<3 && i>=0);
            return raw[i];
        }

        Vec<T, 3>& operator=(const Vec<T,3>& vec){
            if(this==&vec){
                return *this;
            }
            for(size_t i=0;i<3;i++){
                this->raw[i] = vec[i];
            }
            
            return *this;
        }

    };

    template<class T>
    class Vec<T,4>{
    public:
        union{
            struct {T x,y,z,w;};
            struct {T r,g,b,a;};
            T raw[4];
        };

        Vec<T,4>():x(),y(),z(),w(){}

        Vec<T,4>(T x_, T y_, T z_, T w_):x(x_),y(y_),z(z_),w(w_){}

        Vec<T,4>(Vec<T,4> const & v):x(v.x),y(v.y),z(v.z),w(v.w){}

        template<class U> Vec<T,4>(Vec<U,2> const &, U const, U const);
        template<class U> Vec<T,4>(Vec<U,3> const &, U const);
        template<class U> Vec<T,4>(Vec<U,4> const &);

        T& operator[](const size_t i){
            assert(i<4 && i>=0);
            return raw[i];
        }

        const T& operator[](const size_t i) const{
            assert(i<4 && i>=0);
            return raw[i];
        }

        Vec<T, 4>& operator=(const Vec<T,4>& vec){
            if(this==&vec){
                return *this;
            }
            for(size_t i=0;i<4;i++){
                this->raw[i] = vec[i];
            }
            
            return *this;
        }

    };
    
////////////////////////////////////////////////////////////////////////////////

    template<class T, size_t dim>
    Vec<T, dim> operator+(Vec<T, dim> const & lhs, Vec<T, dim> const & rhs){
        Vec<T,dim> ret;
        for(size_t i=0;i<dim;i++){
            ret[i] = lhs[i] + rhs[i];
        }
        return ret;
    }

    template<class T, size_t dim>
    Vec<T, dim> operator-(Vec<T, dim> const & lhs, Vec<T, dim> const & rhs){
        Vec<T,dim> ret;
        for(size_t i=0;i<dim;i++){
            ret[i] = lhs[i] - rhs[i];
        }
        return ret;
    }

    template<class T, size_t dim>
    Vec<T, dim> operator*(Vec<T, dim> const & lhs, Vec<T, dim> const & rhs){
        Vec<T,dim> ret;
        for(size_t i=0;i<dim;i++){
            ret[i] = lhs[i] * rhs[i];
        }
        return ret;
    }

    template<class T, size_t dim>
    Vec<T, dim> operator*(Vec<T, dim> const & lhs, T const rhs){
        Vec<T,dim> ret;
        for(size_t i=0;i<dim;i++){
            ret[i] = lhs[i] * rhs;
        }
        return ret;
    }

    template<class T, size_t dim>
    Vec<T, dim> operator*(T const lhs, Vec<T, dim> const & rhs){
        return rhs*lhs;
    }

    template<class T, size_t dim>
    Vec<T, dim> operator/(Vec<T, dim> const & lhs, Vec<T, dim> const & rhs){
        Vec<T,dim> ret;
        for(size_t i=0;i<dim;i++){
            ret[i] = lhs[i] / rhs[i];
        }
        return ret;
    }

    template<class T, size_t dim>
    Vec<T, dim> operator/(Vec<T, dim> const & lhs, T const rhs){
        Vec<T,dim> ret;
        for(size_t i=0;i<dim;i++){
            ret[i] = lhs[i] / rhs;
        }
        return ret;
    }

    template<class T, size_t dim>
    void operator+=(Vec<T, dim> & lv, Vec<T, dim> const & rv){
        lv = lv + rv;
    }

    template<class T, size_t dim>
    void operator-=(Vec<T, dim> & lv, Vec<T, dim> const & rv){
        lv = lv - rv;
    }

    template<class T, size_t dim>
    void operator*=(Vec<T, dim> & lv, Vec<T, dim> const & rv){
        lv = lv * rv;
    }

    template<class T, size_t dim>
    void operator*=(Vec<T, dim> & lv, T const rv){
        lv = lv * rv;
    }

    template<class T, size_t dim>
    void operator/=(Vec<T, dim> & lv, Vec<T, dim> const & rv){
        lv = lv / rv;
    }

    template<class T, size_t dim>
    void operator/=(Vec<T, dim> & lv, T const rv){
        lv = lv / rv;
    }

    template<class T, size_t dim>
    T dot(Vec<T, dim> const & lhs, Vec<T, dim> const & rhs){
        T ret = T();

        for(int i=0;i<dim;i++){
            ret += lhs[i] * rhs[i];
        }

        return ret;
    }

    template<class T>
    Vec<T, 3> cross(Vec<T, 3> const & lhs, Vec<T, 3> const & rhs){
        Vec<T, 3> ret;

        ret.x = lhs.y*rhs.z - lhs.z*rhs.y;
        ret.y = lhs.z*rhs.x - lhs.x*rhs.z;
        ret.z = lhs.x*rhs.y - lhs.y*rhs.x;

        return ret;
    }

    template<class T, size_t dim>
    T norm(Vec<T, dim> const & vec){
        T ret = dot(vec,vec);
        ret = std::sqrt(ret);
        return ret;
    }

    template<class T, size_t dim>
    void normalize(Vec<T, dim> & vec){
        T vnorm = (static_cast<T> (1))/norm(vec);
        for(size_t i=0;i<dim;i++){
            vec[i] *= vnorm;
        }
    }

    template<class T, size_t dim>
    Vec<T, dim> normalized(Vec<T, dim> const & vec){
        Vec<T, dim> ret;
        T vnorm = (static_cast<T> (1))/norm(vec);
        for(size_t i=0;i<dim;i++){
            ret[i] = vec[i] * vnorm;
        }
        return ret;
    }

    template<class T, size_t dim>
    std::ostream& operator<<(std::ostream& out, const Vec<T, dim>& vec){
        for(size_t i=0;i<dim;i++){
            out<<vec[i]<<" ";
        }
        return out;
    }

    
    Vec<int,3> toRGB(Vec<int,3> const & v);
    Vec<int,3> toRGB(Vec<float,3> const & v);
    Vec<int,4> toRGBA(Vec<int,4> const & v);
    Vec<int,4> toRGBA(Vec<float,4> const & v);

////////////////////////////////////////////////////////////////////////////////

    template<class T, size_t nRow, size_t nCol>
    class Mat{
    private:
        Vec<T, nCol> rowVec[nRow];

    public:
        Mat<T, nRow, nCol>(){
            size_t minDim = std::min(nRow, nCol);
            for(size_t i=0 ; i<minDim ; i++){
                rowVec[i][i] = static_cast<T> (1);
            }
        }

        Mat<T, nRow, nCol>(T const value){
            size_t minDim = std::min(nRow, nCol);
            for(size_t i=0 ; i<minDim ; i++){
                rowVec[i][i] = value;
            }
        }

        Mat<T, nRow, nCol>(Mat<T, nRow, nCol> const & m){
            for(size_t i=0 ; i<nRow ; i++){
                rowVec[i] = m[i];
            }
        }

        Vec<T, nCol>& operator[](size_t const i){
            assert(i>=0 && i<nRow);
            return rowVec[i];
        }

        const Vec<T, nCol>& operator[](size_t const i) const {
            assert(i>=0 && i<nRow);
            return rowVec[i];
        }

        Mat<T, nRow, nCol>& operator=(Mat<T, nRow, nCol> const & mat){
            if(this==&mat){
                return *this;
            }
            for(size_t i=0 ; i<nRow ; i++){
                this->rowVec[i] = mat[i];
            }
            return *this;
        }

        Vec<T, nRow> getColVec(size_t const index) const {
            assert(index>=0 && index<nCol);
            Vec<T, nRow> ret;
            for(size_t i=0 ; i<nRow ; i++){
                ret[i] = rowVec[i][index];
            }
            return ret;
        }

        void setColVec(size_t const index, Vec<T, nRow> const & vec){
            assert(index>=0 && index<nCol);
            for(size_t i=0 ; i<nRow ; i++){
                rowVec[i][index] = vec[i];
            }
        }


    };

////////////////////////////////////////////////////////////////////////////////
    template<class T, size_t nRow, size_t nCol>
    Mat<T, nRow, nCol> operator+(Mat<T, nRow, nCol> const & lhs, Mat<T, nRow, nCol> const & rhs){
        Mat<T, nRow, nCol> ret;
        for(size_t i=0 ; i<nRow ; i++){
            ret[i] = lhs[i] + rhs[i];
        }
        return ret;
    }

    template<class T, size_t nRow, size_t nCol>
    Mat<T, nRow, nCol> operator-(Mat<T, nRow, nCol> const & lhs, Mat<T, nRow, nCol> const & rhs){
        Mat<T, nRow, nCol> ret;
        for(size_t i=0 ; i<nRow ; i++){
            ret[i] = lhs[i] - rhs[i];
        }
        return ret;
    }

    template<class T, size_t nRow, size_t nCol>
    Mat<T, nRow, nCol> operator*(Mat<T, nRow, nCol> const & lhs, T const rhs){
        Mat<T, nRow, nCol> ret;
        for(size_t i=0 ; i<nRow ; i++){
            ret[i] = lhs[i] * rhs;
        }
        return ret;
    }

    template<class T, size_t nRow, size_t nCol>
    Mat<T, nRow, nCol> operator*(T const lhs, Mat<T, nRow, nCol> const & rhs){
        return rhs * lhs;
    }

    template<class T, size_t nRow, size_t nCol>
    Vec<T, nRow> operator*(Mat<T, nRow, nCol> const & lhs, Vec<T, nCol> const & rhs){
        Vec<T, nRow> ret;
        for(size_t i=0 ; i<nRow ; i++){
            ret[i] = dot(lhs[i] , rhs);
        }
        return ret;
    }

    template<class T, size_t nRow, size_t nCol, size_t sameDim>
    Mat<T, nRow, nCol> operator*(Mat<T, nRow, sameDim> const & lhs, Mat<T, sameDim, nCol> const & rhs){
        Mat<T, nRow, nCol> ret;
        for(size_t i=0 ; i<nRow ; i++){
            for(size_t j=0 ; j<nCol ; j++){
                ret[i][j] = dot(lhs[i] , rhs.getColVec(j));
            }
        }
        return ret;
    }

    template<class T, size_t nRow, size_t nCol>
    Mat<T, nRow, nCol> operator/(Mat<T, nRow, nCol> const & lhs, T const rhs){
        Mat<T, nRow, nCol> ret;
        for(size_t i=0 ; i<nRow ; i++){
            ret[i] = lhs[i] / rhs;
        }
        return ret;
    }

    template<class T, size_t nRow, size_t nCol>
    Mat<T, nCol, nRow> transpose(Mat<T, nRow, nCol> const & mat){
        Mat<T, nCol, nRow> ret;
        for(size_t i=0 ; i<nRow ; i++){
            ret.setColVec(i, mat[i]);
        }
        return ret;
    }

    template<class T, size_t dim>
    Mat<T, dim-1, dim-1> getMinor(Mat<T, dim, dim> const & mat, size_t x, size_t y){
        assert(dim>0);
        Mat<T, dim-1, dim-1> ret;
        for(size_t i=0;i<dim-1;i++){
            for(size_t j=0;j<dim-1;j++){
                ret[i][j] = mat[i<x?i:i+1][j<y?j:j+1];
            }
        }
        return ret;
    }

    template<class T, size_t dim>
    T det(Mat<T, dim, dim> const & mat){
        assert(dim>0);

        T ret = T();

        for(size_t i=0;i<dim;i++){  
            ret += cofactor(mat, 0, i) * mat[0][i];
        }

        return ret;
    }

    template<class T>
    T det(Mat<T,2,2> const & mat){
        return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    }

    template<class T>
    T det(Mat<T,1,1> const & mat){
        return mat[0][0];
    }

    template<class T>
    T det(Mat<T,0,0> const & mat){
        return static_cast<T>(0);
    }

    template<class T, size_t dim>
    T cofactor(Mat<T, dim, dim> const & mat, size_t x, size_t y){
        return det(getMinor(mat,x,y)) * static_cast<T>((x+y)%2?-1:1);
    }

    template<class T, size_t dim>
    Mat<T,dim,dim> adjugate(Mat<T, dim, dim> const & mat){
        Mat<T, dim, dim> ret;
        for(size_t i=0;i<dim;i++){
            for(size_t j=0;j<dim;j++){
                ret[j][i] = cofactor(mat,i,j);
            }
        }
        return ret;
    }

    template<class T, size_t dim>
    Mat<T,dim,dim> inverse(Mat<T, dim, dim> const & mat){
        Mat<T, dim, dim> ret;
        ret = adjugate(mat)/det(mat);
        return ret;
    }

    template<class T, size_t nRow, size_t nCol>
    std::ostream& operator<<(std::ostream& out, Mat<T, nRow, nCol> const & mat){
        for(size_t i=0 ; i<nRow ; i++){
            out<<mat[i]<<"\n";
        }
        return out;
    }

////////////////////////////////////////////////////////////////////////////////

    typedef Vec<float,2> vec2f;
    typedef Vec<float,3> vec3f;
    typedef Vec<float,4> vec4f;
    typedef Vec<int,2> vec2i;
    typedef Vec<int,3> vec3i;
    typedef Vec<int,4> vec4i;

    typedef Mat<float, 4, 4> mat4f;
    typedef Mat<int, 4, 4> mat3f;

}//namespace geo

#endif
