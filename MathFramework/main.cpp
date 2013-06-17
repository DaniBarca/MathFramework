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

int main(int argc, const char * argv[])
{

    Vector v = Vector(3);
    v.set(2,3.4);
    v[0] = 2.7;
    
    v.print();
    
    return 0;
}

