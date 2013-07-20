//
//  Matrix.h
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#ifndef MathFramework_Matrix_h
#define MathFramework_Matrix_h

#include "Includes.h"

class Vector;
#include "Vector.h"

class Matrix{
protected:
    double* m;
    
    int rows_;
    int columns_;
    int size_;
    
public:
    Matrix(const Matrix & other);           //Copy a Matrix
    Matrix(const Vector & other);           //Copy a Vector (can be considered a 1 column matrix)
    Matrix(int,int);                        //Set a new matrix
    
    void clear();                           //Set zeros everywhere
    
    double get(int,int) const;              //Get a value
    double get(int)     const;              //Get a vaule from array
    int    rows()       const;              //Get rows number
    int    columns()    const;              //Get columns number
    int    size()       const;              //Get rows*columns, the number of items in m
    void   print()      const;              //Print the Matrix
    void   set(int,int,double);             //Set a value into the Matrix
    
    void setIdentity();                     //Set an identity matrix (1s at the diagonal)
    void transpose();                       //Set the transposed matrix
    
    int  isSquare() const;                  //Tells if the matrix has the same number of rows/columns (-1 if not)
    
    Matrix & operator =(const Matrix & b);  //For Matrix=Matrix assignment
    Matrix & operator =(const Vector & v);  //For Matrix=Vector assignment
    double * operator[](const int i);       //Faster access to matrix [][]
};

Matrix & operator *(const Matrix & a, const Matrix & b);
Vector & operator *(const Matrix & a, const Vector & v);


class Matrix44 : public Matrix{
public:
    Matrix44(const Matrix & other);             //Copy a Matrix. Be careful, the matrix must be 4x4
    Matrix44(const Matrix44 & other);           //Copy a Matrix44
    Matrix44();
    
    Matrix44 & operator =(const Matrix & b);
    Matrix44 & operator =(const Matrix44 & b);
};

#endif
