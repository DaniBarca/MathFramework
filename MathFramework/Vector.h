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

class Vector{
protected:
    double* v;
    int size_;
public:
    Vector(const Vector& other);
    
    Vector(int size);       //Defines size, allocates and clears
    Vector(double,double,double,double,double,double,double); //7D vector
    Vector(double,double,double); //3D vector
    Vector(double,double);        //2D vector
    
    void clear();           //Sets zeros
    
    int    size()   const;
    double get(int) const;
    
    void   set(int, double);
    void   print();
    
    double mod() const;           //Returns vector module (its length)
    void   norm();                //Normalizes the vector
    
    double dot(Vector b)   const;
    Vector cross(Vector b) const;
    
    double & operator [](int i);  //Allows easier access to data
    double & operator [](int i) const;
    Vector & operator =(const Vector& b);
    
    ~Vector();
};

Vector operator +(const Vector& a, const Vector& b);
Vector operator -(const Vector& a, const Vector& b);
Vector operator *(const Vector& a, const Vector& b); //NOTE THAT THIS DOES THE CROSS PRODUCT
Vector operator /(const Vector& a, const double& b);
Vector operator *(const Vector& a, const double& b);

class Vector2 : public Vector{
public:
    Vector2();
    Vector2(double,double);
};

class Vector3 : public Vector{
public:
    Vector3();
    Vector3(double,double,double);
};

#endif
