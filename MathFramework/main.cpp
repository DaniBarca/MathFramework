//
//  main.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//
//  THIS IS AN EXAMPLE CODE USING THE MATHFRAMEWORK

#include <iostream>
#include "Matrix.h"

int main(int argc, const char * argv[])
{
    Vector v = Vector(1,2,3);
    Matrix a = Matrix(4,4);
    a.setIdentity();
    Matrix44 b = a;
    Matrix44 c = a;
    c[3][3] = 5;
    b = b*c;
    
    b.print();
    return 0;
}
