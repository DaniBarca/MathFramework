//
//  Vector3.h
//  MathFramework
//
//  Created by Dani Barca on 30/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#ifndef MathFramework_Vector3_h
#define MathFramework_Vector3_h

#include "Includes.h"
#include "Vector.h"

class Matrix;
#include "Matrix.h"

class Vector3 : public Vector{
public:
    Vector3(double, double, double);
    Vector3();
    
    Vector3(Vector& other);
    Vector3(Matrix& other);
    Vector3(Vector3& other);
    
    Vector3& operator =(const Vector3& b);
    Vector3& operator =(const Vector& b);       //Vector=Vector assignment
    Vector3& operator =(const Matrix& m);       //Vector=Matrix assignment (for 1 column matrices)
};

Vector3 operator +(const Vector3& a, const Vector3& b);
Vector3 operator -(const Vector3& a, const Vector3& b);
Vector3 operator *(const Vector3& a, const Vector3& b); //NOTE THAT THIS DOES THE CROSS PRODUCT
Vector3 operator /(const Vector3& a, const double& b);
Vector3 operator *(const Vector3& a, const double& b);
Vector3 operator *(const Vector3& a, const Matrix& m);


#endif
