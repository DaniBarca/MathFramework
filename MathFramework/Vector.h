//
//  Vector.h
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#ifndef MathFramework_Vector_h
#define MathFramework_Vector_h

#include "Includes.h"

template <class T> class Matrix;
template <class T> class Matrix44;
#include "Matrix.h"

template<class T>
class Vector{
protected:
    T* v;
    int size_;
public:
    Vector(const Vector& other);
    Vector(const Matrix<T>& other);
    
    Vector(int size);                      //Defines size, allocates and clears
    Vector(T,T,T,T,T,T,T);				   //7D vector
    Vector(T,T,T);                         //3D vector
    Vector(T,T);                           //2D vector
    Vector();                              //3D vector default
    
    void clear();                          //Sets zeros
    
    int    size()   const;                 //Returns number of items
    T get(int) const;                      //Returns item at (int) position
    
    void   set(int, T);                    //Sets an item at (int) position
    void   print() const;                  //Prints the vector
    
    T mod() const;                         //Returns vector module (its length)
    void   norm();                         //Normalizes the vector
    
    T dot(Vector b)   const;               //Dot product between vectors
    Vector cross(Vector b) const;               //Cross product between vectors
    
    T & operator [](int i);                //Allows easier access to data
    T & operator [](int i) const;
    Vector & operator =(const Vector& b);          //Vector=Vector assignment
    Vector & operator =(const Matrix<T>& m);       //Vector=Matrix assignment (for 1 column/row matrices)
    
    void takePosition(const Matrix44<T>& m);       //Take coordinates from this Matrix

    ~Vector();
    
    friend Vector<T> operator +(const Vector& a, const Vector& b); //v1 + v2
    friend Vector<T> operator -(const Vector& a, const Vector& b); //v1 - v2
    friend Vector<T> operator *(const Vector& a, const Vector& b); //v1 * v2 NOTE THAT THIS DOES THE CROSS PRODUCT
    friend Vector<T> operator /(const Vector& a, const T& b); //v1 / n1
    friend Vector<T> operator *(const Vector& a, const T& b); //v1 * n1
    friend Vector<T> operator *(const Vector& a, const Matrix<T>& m); //v1 * m1
};

template<class T>
class Vector3 : public Vector<T>{
public:
    T& x;      //Access to v[0] NOTE: Don't use this for data modification, just access. I will thank any clue on how to make modification work with this.
    T& y;      //Access to v[1]
    T& z;      //Access to v[2]
    
    Vector3(const Vector<T>&  other);
    Vector3(const Vector3& other);
    
    Vector3();                   //Creates empty Vector3
    Vector3(T,T,T);              //3D Vector
    
    Vector3<T> & operator =(const Vector3& b);
    Vector3<T> & operator =(const Vector<T>& b);      //Vector=Vector assignment
    Vector3<T> & operator =(const Matrix<T>& m);      //Vector=Matrix assignment (for 1 column/row matrices)
    
    friend Vector3<T> operator +(const Vector3<T>& a, const Vector<T>& b); //v1 + v2
    friend Vector3<T> operator -(const Vector3<T>& a, const Vector<T>& b); //v1 - v2
    friend Vector3<T> operator *(const Vector3<T>& a, const Vector<T>& b); //v1 * v2 NOTE THAT THIS DOES THE CROSS PRODUCT
    friend Vector3<T> operator /(const Vector3<T>& a, const T& b); //v1 / n1
    friend Vector3<T> operator *(const Vector3<T>& a, const T& b); //v1 * n1
    friend Vector3<T> operator *(const Vector3<T>& a, const Matrix<T>& m); //v1 * m1
};

#endif
