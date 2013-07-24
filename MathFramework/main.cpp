//
//  main.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//
//  THIS IS AN EXAMPLE CODE USING THE MATHFRAMEWORK

#include <iostream>
#include "MathFramework.h"

int main(int argc, const char * argv[])
{
    //You can create Vectors and Matrices
    Vector   v = Vector(3);
    Vector  vb = 3;         //This does exactly the same as vb = Vector(3), creating a 3D vector
    Vector   b = v;
    Matrix   m = Matrix(2,3); //(rows,columns)
    Matrix44 mb= Matrix44();  //Matrix44 is the same as Matrix, but it can only be 4x4 and have a lot of useful functions for 3D
    
    //You can set/get its values and print them
    //For Vector:
    v[0] = 3; v[1] = 6; v[2] = 12;
    v.set(0,4);
    
    cout << "v.get(2) does the same as v[2]" << endl;
    cout << v.get(2) << " = " << v[2] <<  endl;
    
    cout << "\nPrint a vector with v.print()" << endl;
    v.print();
    
    //For Matrix and Matrix44:
    //You can manually set the values
    m[0][0] = 10;
    m[1][2] = 5;
    
    //And some other functions that set values automatically for diverse purposes
    mb.setIdentity();                                  //Create an identity function
    
    //Rotate 90º in the z axis (remember: the angle must be in radians, you can convert it with DEGTORAD)
    mb.setRotationMatrix(DEGTORAD(90), Vector(0,0,1));
    mb.setPosition(4,5,8);
    
    //etc.
    
    //And finally you can operate between these classes:
    Matrix vm = v; //Creates a 1x3 Matrix and copies the vector v
    Vector mv = vm;//Just the opposite, only if the matrix is nx1 or 1xn
    
    Vector result = mb.rotateVector(v);           //You can do only the rotation
    result        = mb.translateVector(v);        //Or you can do only the translation
    result        = mb * v;                       //Or you can do both multiplying

    //And finally watch the result
    result.print();
    
    return 0;
}
