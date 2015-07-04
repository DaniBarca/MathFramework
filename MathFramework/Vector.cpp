//
//  Vector.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#include "Vector.h"

template<class T>
Vector<T>::Vector(const Vector<T>& other){
    operator=(other);
}

template<class T>
Vector<T>::Vector(const Matrix<T>& other){
    operator=(other);
}

template<class T>
Vector<T>::Vector(int size){
    assert(size!=0);                            //You can't create 0 size vectors
    v = new T[size];
    
    this->size_ = size;
    
    clear();
}

template<class T>
Vector<T>::Vector(T a, T b, T c, T d, T e, T f, T g){
    v = (T*)malloc(sizeof(T)*7);
    this->size_ = 7;
    
    v[0] = a;  v[1] = b;  v[2] = c;
    v[3] = d;  v[4] = e;  v[5] = f;
    v[6] = g;
}

template<class T>
Vector<T>::Vector(T x, T y, T z){
    v = (T*)malloc(sizeof(T)*3);
    this->size_ = 3;
    
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

template<class T>
Vector<T>::Vector(T x, T y){
    v = (T*)malloc(sizeof(T)*2);
    this->size_ = 2;
    
    v[0] = x;
    v[1] = y;
}

template<class T>
Vector<T>::Vector(){
    v = (T*)malloc(sizeof(T)*3);
    this->size_ = 3;
}

template<class T>
void Vector<T>::clear(){
    for(int i = 0; i < size_; ++i)
        v[i] = 0;
}

template<class T>
int Vector<T>::size() const{
    return size_;
}

template<class T>
T Vector<T>::get(int n) const{
    assert(n<size_);                           //You accesessed an invalid position
    return v[n];
}

template<class T>
void Vector<T>::set(int n, T stuff){
    assert(n<size_);
    v[n] = stuff;
}

template<class T>
void Vector<T>::print() const{
    cout << "----------" << endl;
    for(int i = 0; i < size_; ++i)
        cout<<v[i] << " ";
    cout << endl << "----------" << endl;
}

template<class T>
T Vector<T>::mod() const{
    T stuff = 0;
    for(int i = 0; i < size_; ++i)
        stuff += v[i]*v[i];
    return sqrt(stuff);
}

template<class T>
void Vector<T>::norm(){
    T module = 1/mod();
    
    for(int i = 0; i < size_; ++i)
        v[i] = v[i] * module;
}

template<class T>
T Vector<T>::dot(Vector b) const{
    assert(size_ == b.size());
    T dot = 0;
    for(int i = 0; i < size_; ++i)
        dot += v[i] * b[i];
    return dot;
}

template<class T>
Vector<T> Vector<T>::cross(Vector b) const{
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

template<class T>
T & Vector<T>::operator [](int i){
    assert(i < size_);                          //You accesessed an invalid position. Shame on you.
    return v[i];
}

//This one does exactly the same as the last one, but can be used if Vector is const
//For example at some operators
template<class T>
T & Vector<T>::operator [](int i) const{
    assert(i < size_);
    return v[i];
}

template<class T>
Vector<T> & Vector<T>::operator =(const Vector & b){
    if(this != &b){
        v = new T[b.size()];
        copy(b.v, b.v+b.size(),v);
        size_ = b.size();
    }
    return *this;
}

template<class T>
Vector<T> & Vector<T>::operator =(const Matrix<T>& m){
    assert(m.columns() == 1 || m.rows() == 1);
    v = new T[m.size()];
    
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

template<class T>
void Vector<T>::takePosition(const Matrix44<T> &m){
    assert(size_ == 3);
    v[0] = m.get(3);
    v[1] = m.get(7);
    v[2] = m.get(11);
}

template<class T>
Vector<T>::~Vector(){
    delete [] v;
}

//---------------------- Operators between Vectors
template<class T>
Vector<T> operator +(const Vector<T>& a, const Vector<T>& b){
    assert(a.size() == b.size());
    Vector<T> v = Vector<T>(a.size());
    
    for(int i = 0; i<v.size(); ++i)
        v[i] = a.get(i) + b[i];
    
    return v;
}

template<class T>
Vector<T> operator -(const Vector<T>& a, const Vector<T>& b){
    assert(a.size() == b.size());
    Vector<T> v = Vector<T>(a.size());

    for(int i = 0; i<v.size(); ++i)
        v[i] = a.get(i) - b[i];

    return v;
}

template<class T>
Vector<T> operator *(const Vector<T>& a, const Vector<T>& b){
    return a.cross(b);
}

template<class T>
Vector<T> operator /(const Vector<T>& a, const T& b){
    return a * (1/b);
}

template<class T>
Vector<T> operator *(const Vector<T>& a, const T& b){
    Vector<T> v = Vector<T>(a.size());
    
    for(int i = 0; i<v.size(); ++i)
        v[i] = a[i] * b;
    
    return v;
}

template<class T>
Vector<T> operator *(const Vector<T> & a, const Matrix<T>& b){
    assert(a.size() == b.rows());
    Matrix<T> m = a;
    m.transpose();
    Vector<T> *v = new Vector<T>(a.size());
    *v = (m*b);
    return *v;
}

//----------------------------------------------------------------------------------------------
//Vector3
//----------------------------------------------------------------------------------------------
template<class T>
Vector3<T>::Vector3() : Vector(3) , x(v[0]), y(v[1]), z(v[2]){
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
}

template<class T>
Vector3<T>::Vector3(const Vector& other) : Vector(other) , x(v[0]) , y(v[1]) , z(v[2]){
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
}

template<class T>
Vector3<T>::Vector3(const Vector3<T>& other) : x(v[0]) , y(v[1]), z(v[2]){
    operator=(other);
}

template<class T>
Vector3<T>::Vector3(T x,T y,T z) : Vector(x,y,z) , x(v[0]), y(v[1]), z(v[2]){
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
}

// Operators -------------------------------------------
template<class T>
Vector3<T> & Vector3<T>::operator =(const Vector3<T>& b){
    v = new T[3];
    
    v[0] = b[0];
    v[1] = b[1];
    v[2] = b[2];
    
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
    
    return *this;
}

template<class T>
Vector3<T> & Vector3<T>::operator =(const Vector& b){
    assert(b.size() == 3);
    v = new T[3];
    
    v[0] = b[0];
    v[1] = b[1];
    v[2] = b[2];
    
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
    
    return *this;
}

template<class T>
Vector3<T> & Vector3<T>::operator =(const Matrix<T>& m){
    assert((m.rows() == 3 && m.columns() == 1) || (m.rows() == 1 && m.columns() == 3));
    
    Vector<T>::operator=(m);

    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
    return *this;
}

template<class T>
Vector3<T> operator +(const Vector3<T>& a, const Vector<T>& b){
    return Vector3<T>(operator+((Vector<T>)a,b));
}

template<class T>
Vector3<T> operator -(const Vector3<T>& a, const Vector<T>& b){
    return Vector3<T>(operator-(Vector<T>(a),b));
}

template<class T>
Vector3<T> operator *(const Vector3<T>& a, const Vector<T>& b){
    return Vector3<T>(a.cross(b));
}

template<class T>
Vector3<T> operator /(const Vector3<T>& a, const T& b){
    return a * (1/b);
}

template<class T>
Vector3<T> operator *(const Vector3<T>& a, const T& b){
    Vector v = Vector(a.size());
    
    for(int i = 0; i<v.size(); ++i)
        v[i] = a[i] * b;
    
    return v;
}
