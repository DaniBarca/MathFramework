//
//  Vector3.cpp
//  MathFramework
//
//  Created by Dani Barca on 30/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#include "Vector3.h"

Vector3::Vector3(double x,double y,double z) : Vector(x,y,z){}
Vector3::Vector3() : Vector(3){}

Vector3::Vector3(Vector& other) : Vector(other){}
Vector3::Vector3(Matrix& other) : Vector(3){
    operator=(other);
}
Vector3::Vector3(Vector3& other): Vector((Vector) other){}

Vector3& Vector3::operator =(const Vector3& b){
    if(this != &b){
        v[0] = b[0];
        v[1] = b[1];
        v[2] = b[2];
    }
    return *this;
}

Vector3& Vector3::operator =(const Vector& b){
    if(this != &b){
        v[0] = b[0];
        v[1] = b[1];
        v[2] = b[2];
    }
    return *this;
}

Vector3& Vector3::operator =(const Matrix& m){
    assert((m.columns() == 1 && m.rows() == 3) || (m.rows() == 1 && m.columns() == 3));
    delete [] v;
    v = new double[m.size()];
    
    v[0] = m.get(0);
    v[1] = m.get(1);
    v[2] = m.get(2);
    
    size_ = m.size();
    return *this;
}

Vector3 operator +(const Vector3& a, const Vector3& b){
    Vector3 c;
    c[0] = a[0] + b[0];
    c[1] = a[1] + b[1];
    c[2] = a[2] + b[2];
    return c;
}

Vector3 operator -(const Vector3& a, const Vector3& b){
    Vector3 c;
    c[0] = a[0] - b[0];
    c[1] = a[1] - b[1];
    c[2] = a[2] - b[2];
    return c;
}

Vector3 operator *(const Vector3& a, const Vector3& b); //NOTE THAT THIS DOES THE CROSS PRODUCT
Vector3 operator /(const Vector3& a, const double& b);
Vector3 operator *(const Vector3& a, const double& b);
Vector3 operator *(const Vector3& a, const Matrix& m);