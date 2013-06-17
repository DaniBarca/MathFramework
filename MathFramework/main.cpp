//
//  main.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//
//  THIS IS AN EXAMPLE CODE USING THE MATHFRAMEWORK

#include <iostream>
#include "Vector.h"
#include "Matrix.h"

int main(int argc, const char * argv[])
{
    Matrix a = Matrix(3,2);
    Matrix b = Matrix(2,3);
    
    a.set(0,0,1); a.set(0,1,2); 
    a.set(1,0,4); a.set(1,1,5); 
    a.set(2,0,7); a.set(2,1,8); 
    
    b.set(0,0,1); b.set(0,1,2); b.set(0,2,3);
    b.set(1,0,4); b.set(1,1,5); b.set(1,2,6);
    
    (a*b).print();
    
    return 0;
}

