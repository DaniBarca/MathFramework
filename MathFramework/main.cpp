//
//  main.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//
//  THIS IS AN EXAMPLE AND TEST CODE USING THE MATHFRAMEWORK

#include <iostream>
#include "MathFramework.h"
#include <time.h>

int main(int argc, const char * argv[])
{
    Matrix44<unsigned int> A = Matrix44<unsigned int>();
    Matrix44<unsigned int> B = Matrix44<unsigned int>();

    A[0][0] = 1;  A[0][1] = 2;  A[0][2] = 3;  A[0][3] = 4;
    A[1][0] = 5;  A[1][1] = 6;  A[1][2] = 7;  A[1][3] = 8;
    A[2][0] = 9;  A[2][1] = 10; A[2][2] = 11; A[2][3] = 12;
    A[3][0] = 13; A[3][1] = 14; A[3][2] = 15; A[3][3] = 16;
    
    B[0][0] = 1;  B[0][1] = 2;  B[0][2] = 3;  B[0][3] = 4;
    B[1][0] = 5;  B[1][1] = 6;  B[1][2] = 7;  B[1][3] = 8;
    B[2][0] = 9;  B[2][1] = 10; B[2][2] = 11; B[2][3] = 12;
    B[3][0] = 13; B[3][1] = 14; B[3][2] = 15; B[3][3] = 16;

    Matrix44<unsigned int> r = Matrix44<unsigned int>();
    for(int i = 0; i < 100000000; ++i){
        A.mult(B,r);
    }    
    
    return 0;
    
    /*/You can create Vectors and Matrices
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
    
    //You can create a Vector3 and access with x, y, z values (JUST ACCESS, FOR NOW; I DON'T KNOW HOW TO PROPERLY CHANGE THE VALUES WITH THIS):
    //I'll keep working on this.
    Vector3 v3 = Vector3(10,9,8);
    
    cout << "\nTesting v3.x -- v3.y -- v3.z" << endl;
    cout << v3.x << " -- " << v3.y << " -- " << v3.z <<endl;
    
    v3.print();
    
    //For Matrix and Matrix44:
    //You can manually set the values
    m[0][0] = 10;
    m[1][2] = 5;
    
    //And some other functions that set values automatically for diverse purposes
    mb.setIdentity();                                  //Create an identity function
    
    //Rotate 90º in the z axis (remember: the angle must be in radians, you can convert it with DEGTORAD(n))
    mb.setRotationMatrix(DEGTORAD(90), Vector(0,0,1));
    mb.setPosition(4,5,8);
    
    //etc.
    
    //And finally you can operate between these classes:
    Matrix vm = v; //Creates a 1x3 Matrix and copies the vector v
    Vector mv = vm;//Just the opposite, only if the matrix is nx1 or 1xn
    v3 = vm;
    
    //
    vm.print();
    mv.print();
    
    cout << v3.x << " -- " << v3.y << " -- " << v3.z <<endl;
    cout << v3[0]<< " -- " << v3[1]<< " -- " << v3[2]<< "\n" <<endl;
    
    v3[0] = 10;
    v3.y  = 20;
    
    cout << v3.x << " -- " << v3.y << " -- " << v3.z <<endl;
    v3.print();
    cout << "*" << endl;
    
    v.print();
    cout << "=" << endl;
    
    v3 = v3 * v;
    v3.print();
    
    cout << v3.x << " -- " << v3.y << " -- " << v3.z <<endl;
    cout << v3[0]<< " -- " << v3[1]<< " -- " << v3[2]<< "\n" <<endl;
    
    Vector result = mb.rotateVector(v);           //You can do only the rotation
    result        = mb.translateVector(v);        //Or you can do only the translation
    result        = mb * v;                       //Or you can do both multiplying

    //And finally watch the result
    result.print();
    
    return 0;*/
}
