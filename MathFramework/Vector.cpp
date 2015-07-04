//
//  Vector.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#include "Vector.h"

Vector::Vector(const Vector& other){
    operator=(other);
}

Vector::Vector(const Matrix& other){
    operator=(other);
}

Vector::Vector(int size){
    assert(size!=0);                            //You can't create 0 size vectors
    v = new double[size];
    
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

Vector::Vector(){
    v = (double*)malloc(sizeof(double)*3);
    this->size_ = 3;
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

void Vector::print() const{
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
    assert((size_ == 3 || size_ == 7) && size_ == b.size()); //The cross product only has sense for 3D and 7D vectors
    
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
    
    return Vector(0); //If you reach this line, stop playing with the universe
}

double & Vector::operator [](int i){
    assert(i < size_);                          //You accesessed an invalid position. Shame on you.
    return v[i];
}

//This one does exactly the same as the last one, but can be used if Vector is const
//For example at some operators
double & Vector::operator [](int i) const{
    assert(i < size_);
    return v[i];
}

Vector & Vector::operator =(const Vector & b){
    if(this != &b){
        v = new double[b.size()];
        copy(b.v, b.v+b.size(),v);
        size_ = b.size();
    }
    return *this;
}

Vector & Vector::operator =(const Matrix& m){
    assert(m.columns() == 1 || m.rows() == 1);
    v = new double[m.size()];
    
    if(m.columns() == 1){
        for(int i = 0; i < m.rows(); ++i)
            v[i] = m.get(i,0);
    }
    if(m.rows() == 1){
        for(int i = 0; i < m.columns(); ++i)
            v[i] = m.get(0,i);
    }
    
    size_ = m.size();
    return *this;
}

void Vector::takePosition(const Matrix44 &m){
    assert(size_ == 3);
    v[0] = m.get(3);
    v[1] = m.get(7);
    v[2] = m.get(11);
}

Vector::~Vector(){
    delete [] v;
}

//---------------------- Operators between Vectors

Vector operator +(const Vector& a, const Vector& b){
    assert(a.size() == b.size());
    Vector v = Vector(a.size());
    
    for(int i = 0; i<v.size(); ++i)
        v[i] = a.get(i) + b[i];
    
    return v;
}

Vector operator -(const Vector& a, const Vector& b){
    assert(a.size() == b.size());
    Vector v = Vector(a.size());

    for(int i = 0; i<v.size(); ++i)
        v[i] = a.get(i) - b[i];

    return v;
}

Vector operator *(const Vector& a, const Vector& b){
    return a.cross(b);
}

Vector operator /(const Vector& a, const double& b){
    return a * (1/b);
}

Vector operator *(const Vector& a, const double& b){
    Vector v = Vector(a.size());
    
    for(int i = 0; i<v.size(); ++i)
        v[i] = a[i] * b;
    
    return v;
}

Vector operator *(const Vector & a, const Matrix& b){
    assert(a.size() == b.rows());
    Matrix m = a;
    m.transpose();
    Vector *v = new Vector(a.size());
    *v = (m*b);
    return *v;
}

//----------------------------------------------------------------------------------------------
//Vector3
//----------------------------------------------------------------------------------------------

Vector3::Vector3() : Vector(3) , x(v[0]), y(v[1]), z(v[2]){
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
}

Vector3::Vector3(const Vector& other) : Vector(other) , x(v[0]) , y(v[1]) , z(v[2]){
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
}

Vector3::Vector3(const Vector3& other) : x(v[0]) , y(v[1]), z(v[2]){
    operator=(other);
}

Vector3::Vector3(double x,double y,double z) : Vector(x,y,z) , x(v[0]), y(v[1]), z(v[2]){
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
}

// Operators -------------------------------------------

Vector3 & Vector3::operator =(const Vector3& b){
    v = new double[3];
    
    v[0] = b[0];
    v[1] = b[1];
    v[2] = b[2];
    
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
    
    return *this;
}

Vector3 & Vector3::operator =(const Vector& b){
    assert(b.size() == 3);
    v = new double[3];
    
    v[0] = b[0];
    v[1] = b[1];
    v[2] = b[2];
    
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
    
    return *this;
}

Vector3 & Vector3::operator =(const Matrix& m){
    assert((m.rows() == 3 && m.columns() == 1) || (m.rows() == 1 && m.columns() == 3));
    
    Vector::operator=(m);

    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
    return *this;
}

Vector3 operator +(const Vector3& a, const Vector& b){
    return Vector3(operator+((Vector)a,b));
}

Vector3 operator -(const Vector3& a, const Vector& b){
    return Vector3(operator-(Vector(a),b));
}

Vector3 operator *(const Vector3& a, const Vector& b){
    return Vector3(a.cross(b));
}

Vector3 operator /(const Vector3& a, const double& b){
    return a * (1/b);
}

Vector3 operator *(const Vector3& a, const double& b){
    Vector v = Vector(a.size());
    
    for(int i = 0; i<v.size(); ++i)
        v[i] = a[i] * b;
    
    return v;
}
