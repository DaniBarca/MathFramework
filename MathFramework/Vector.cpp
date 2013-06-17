//
//  Vector.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#include "Vector.h"

Vector::Vector(int size){
    assert(size!=0);                            //You can't create 0 size vectors
    v = (double*)malloc(sizeof(double)*size);
    
    this->size_ = size;
    
    clear();
}

Vector::Vector(double a, double b, double c, double d, double e, double f, double g){
    v = (double*)malloc(sizeof(double)*7);
    this->size_ = 7;
    
    v[0] = a;  v[1] = b;  v[2] = c;
    v[3] = d;  v[4] = e;  v[5] = f;
    v[6] = g;
}

Vector::Vector(double x, double y, double z){
    v = (double*)malloc(sizeof(double)*3);
    this->size_ = 3;
    
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

Vector::Vector(double x, double y){
    v = (double*)malloc(sizeof(double)*2);
    this->size_ = 2;
    
    v[0] = x;
    v[1] = y;
}

void Vector::clear(){
    for(int i = 0; i < size_; ++i)
        v[i] = 0;
}

int Vector::size() const{
    return size_;
}

double Vector::get(int n) const{
    assert(n<size_);                           //You accesessed an invalid position
    return v[n];
}

void Vector::set(int n, double stuff){
    assert(n<size_);
    v[n] = stuff;
}

void Vector::print(){
    cout << "----------" << endl;
    for(int i = 0; i < size_; ++i)
        cout<<v[i] << " ";
    cout << endl << "----------" << endl;
}

double Vector::mod() const{
    double stuff = 0;
    for(int i = 0; i < size_; ++i)
        stuff += v[i]*v[i];
    return sqrt(stuff);
}

void Vector::norm(){
    double module = 1/mod();
    
    for(int i = 0; i < size_; ++i)
        v[i] = v[i] * module;
}

double Vector::dot(Vector b) const{
    assert(size_ == b.size());
    double dot = 0;
    for(int i = 0; i < size_; ++i)
        dot += v[i] * b[i];
    return dot;
}

Vector Vector::cross(Vector b) const{
    assert(size_ == b.size() && (size_ == 3 || size_ == 7)); //The cross product only has sense for 3D and 7D vectors
    
    if(size_ == 3)
        return Vector(v[1]*b[2] - v[2]*b[1], v[2]*b[0] - v[0]*b[2], v[0]*b[1] - v[1]*b[0]);
    if(size_ == 7)
        return Vector(v[1]*b[3] - v[3]*b[1] + v[2]*b[6] - v[6]*b[2] + v[4]*b[5] - v[5]*b[4],
                      v[2]*b[4] - v[4]*b[2] + v[3]*b[0] - v[0]*b[3] + v[5]*b[6] - v[6]*b[5],
                      v[3]*b[5] - v[5]*b[3] + v[4]*b[1] - v[1]*b[4] + v[6]*b[0] - v[0]*b[6],
                      v[4]*b[6] - v[6]*b[4] + v[5]*b[2] - v[2]*b[5] + v[0]*b[1] - v[1]*b[0],
                      v[5]*b[0] - v[0]*b[5] + v[6]*b[3] - v[3]*b[6] + v[1]*b[2] - v[2]*b[1],
                      v[6]*b[1] - v[1]*b[6] + v[0]*b[4] - v[4]*b[0] + v[2]*b[3] - v[3]*b[2],
                      v[0]*b[2] - v[2]*b[0] + v[1]*b[5] - v[5]*b[1] + v[3]*b[4] - v[4]*b[3]);
    return Vector(0);
}

double & Vector::operator [](int i){
    assert(i < size_);                          //You accesessed an invalid position
    return v[i];
}

//---------------------- Operators between Vectors

Vector operator +(const Vector& a, const Vector& b){
    assert(a.size() == b.size());
    Vector v = Vector(a.size());
    
    for(int i = 0; i<v.size(); ++i)
        v[i] = a.get(i) + b.get(i);
    
    return v;
}

Vector operator -(const Vector& a, const Vector& b){
    assert(a.size() == b.size());
    Vector v = Vector(a.size());

    for(int i = 0; i<v.size(); ++i)
        v[i] = a.get(i) - b.get(i);

    return v;
}

Vector operator *(const Vector& a, const Vector& b){
    return a.cross(b);
}

Vector operator /(const Vector& a, const double& b){
    Vector v = Vector(a.size());
    double inv = 1/b;
    
    for(int i = 0; i<v.size(); ++i)
        v[i] = a.get(i) * inv;
    
    return v;
}

Vector operator *(const Vector& a, const double& b){
    Vector v = Vector(a.size());
    
    for(int i = 0; i<v.size(); ++i)
        v[i] = a.get(i) * b;
    
    return v;
}

//------------------Vector 2
Vector2::Vector2() : Vector(2){}
Vector2::Vector2(double x, double y) : Vector(x,y){}

//------------------Vector 3
Vector3::Vector3() : Vector(3){}
Vector3::Vector3(double x, double y, double z) : Vector(x,y,z){}
