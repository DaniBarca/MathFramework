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

    Vector2 v = Vector2();
    Vector2 b = v;
    
    v[0] = 1;
    v.print();
    
    return 0;
}

