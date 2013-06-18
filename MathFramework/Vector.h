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
    
    void clear();                                             //Sets zeros
    
    int    size()   const;                      //Returns number of items
    double get(int) const;                      //Returns item at (int)
    
    void   set(int, double);                    //Sets an item into (int)
    void   print() const;                       //Prints the vector
    
    double mod() const;                         //Returns vector module (its length)
    void   norm();                              //Normalizes the vector
    
    double dot(Vector b)   const;               //Dot product between vectors
    Vector cross(Vector b) const;               //Cross product between vectors
    
    double & operator [](int i);                //Allows easier access to data
    double & operator [](int i) const;
    Vector & operator =(const Vector& b);       //Vector=Vector assignment
    Vector & operator =(const Matrix& m);       //Vector=Matrix assignment (for 1 column matrices)

    ~Vector();
};

Vector operator +(const Vector& a, const Vector& b);
Vector operator -(const Vector& a, const Vector& b);
Vector operator *(const Vector& a, const Vector& b); //NOTE THAT THIS DOES THE CROSS PRODUCT
Vector operator /(const Vector& a, const double& b);
Vector operator *(const Vector& a, const double& b);
Vector operator *(const Vector& a, const Matrix& m);

#endif
