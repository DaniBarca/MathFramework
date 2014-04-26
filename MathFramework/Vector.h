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

class Matrix;
class Matrix44;
#include "Matrix.h"

class Vector{
protected:
    double* v;
    int size_;
public:
    Vector(const Vector& other);
    Vector(const Matrix& other);
    
    Vector(int size);                                         //Defines size, allocates and clears
    Vector(double,double,double,double,double,double,double); //7D vector
    Vector(double,double,double);                             //3D vector
    Vector(double,double);                                    //2D vector
    Vector();                                                 //3D vector default
    
    void clear();                                             //Sets zeros
    
    int    size()   const;                      //Returns number of items
    double get(int) const;                      //Returns item at (int) position
    
    void   set(int, double);                    //Sets an item at (int) position
    void   print() const;                       //Prints the vector
    
    double mod() const;                         //Returns vector module (its length)
    void   norm();                              //Normalizes the vector
    
    double dot(Vector b)   const;               //Dot product between vectors
    Vector cross(Vector b) const;               //Cross product between vectors
    
    double & operator [](int i);                //Allows easier access to data
    double & operator [](int i) const;
    Vector & operator =(const Vector& b);       //Vector=Vector assignment
    Vector & operator =(const Matrix& m);       //Vector=Matrix assignment (for 1 column/row matrices)
    
    void takePosition(const Matrix44& m);       //Take coordinates from this Matrix

    ~Vector();
};

Vector operator +(const Vector& a, const Vector& b); //v1 + v2
Vector operator -(const Vector& a, const Vector& b); //v1 - v2
Vector operator *(const Vector& a, const Vector& b); //v1 * v2 NOTE THAT THIS DOES THE CROSS PRODUCT
Vector operator /(const Vector& a, const double& b); //v1 / n1
Vector operator *(const Vector& a, const double& b); //v1 * n1
Vector operator *(const Vector& a, const Matrix& m); //v1 * m1

class Vector3 : public Vector{
public:
    double& x;      //Access to v[0] NOTE: Don't use this for data modification, just access. I will thank any clue on how to make modification work with this.
    double& y;      //Access to v[1]
    double& z;      //Access to v[2]
    
    Vector3(const Vector&  other);
    Vector3(const Vector3& other);
    
    Vector3();                                  //Creates empty Vector3
    Vector3(double,double,double);              //3D Vector
    
    Vector3 & operator =(const Vector3& b);
    Vector3 & operator =(const Vector& b);      //Vector=Vector assignment
    Vector3 & operator =(const Matrix& m);      //Vector=Matrix assignment (for 1 column/row matrices)
};

Vector3 operator +(const Vector3& a, const Vector& b); //v1 + v2
Vector3 operator -(const Vector3& a, const Vector& b); //v1 - v2
Vector3 operator *(const Vector3& a, const Vector& b); //v1 * v2 NOTE THAT THIS DOES THE CROSS PRODUCT
Vector3 operator /(const Vector3& a, const double& b); //v1 / n1
Vector3 operator *(const Vector3& a, const double& b); //v1 * n1
Vector3 operator *(const Vector3& a, const Matrix& m); //v1 * m1

#endif
