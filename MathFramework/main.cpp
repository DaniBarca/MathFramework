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
    Matrix a = Matrix(3,1);
    a[0][0] = 1; a[1][0] = 2;  a[2][0] = 3;
    
    cout<<a.get(0, 0)<<endl;

    (a).print();
    return 0;
}

