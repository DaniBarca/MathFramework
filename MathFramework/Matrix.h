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
#include "Vector.h"

class Matrix{
    double* m;
    
    int rows_;
    int columns_;
    int size_;
    
public:
    Matrix(int,int);
    
    void clear();
    
    double get(int,int) const;
    int    rows()       const;
    int    columns()    const;
    void   print()      const;
    void   set(int,int,double);
    
    void setIdentity();
};

#endif
