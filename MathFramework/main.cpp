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
    a.set(0,0,3); a.set(0,1,4);
    a.set(1,0,5); a.set(1,1,7);
    a.set(2,0,6); a.set(2,1,8);
    
    a[0][0] = 2;
    
    cout<<a[0][1]<<endl;

    (a).print();
    return 0;
}

