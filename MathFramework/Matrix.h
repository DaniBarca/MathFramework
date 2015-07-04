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

template <class T> class Vector;
template <class T> class Vector3;
#include "Vector.h"

template <class T>
class Matrix{
friend Matrix44<T>;                         //Shut up, this is here for a reason.
    
protected:
    T* m;
    
    int rows_;
    int columns_;
    int size_;
    
public:
    Matrix(const Matrix<T> & other);        //Copy a Matrix
    Matrix(const Vector<T> & other);        //Copy a Vector (can be considered a 1 column matrix)
    Matrix(unsigned int, unsigned int);     //Set a new matrix
    Matrix();                               //3x3 Matrix default
    
    void clear(int n = 0);                  //Set n everywhere
    
    T get(int,int)      const;              //Get a value
    T get(int)          const;              //Get a vaule from array (not very intuitive, make sure you know what you're doing)
    int    rows()       const;              //Get rows number
    int    columns()    const;              //Get columns number
    int    size()       const;              //Get rows*columns, the number of items in m
    void   print()      const;              //Print the Matrix
    void   set(int,int,T);                  //Set a value into the Matrix
    
    void setIdentity();                     //Set an identity matrix (1s at the diagonal)
    void transpose();                       //Set the transposed matrix
    
    int  isSquare() const;                  //Tells if the matrix has the same number of rows/columns (-1 if not, number else)
    
    ~Matrix();
    
    Matrix<T> & operator =(const Matrix<T> & b);  //For Matrix=Matrix assignment
    Matrix<T> & operator =(const Vector<T> & v);  //For Matrix=Vector assignment
    T * operator[](const unsigned int i);                  //Faster access to matrix [][]
    
    friend Matrix<T> & operator *(const Matrix<T> & a, const Matrix<T> & b);
    friend Vector<T> & operator *(const Matrix<T> & a, const Vector<T> & v);
};

//--------------------------------------------------------------------------------
//Matrix 44 class, a certain type of square Matrix that has 4 rows and 4 columns
//Useful for 3D calculations
//--------------------------------------------------------------------------------

#define X_I 3
#define Y_I 7
#define Z_I 11

template <class T>
class Matrix44 : public Matrix<T>{
public:
    Matrix44(const Matrix<T> & other);             //Copy a Matrix. Be careful, the matrix must be 4x4
    Matrix44(const Matrix44<T> & other);           //Copy a Matrix44
    Matrix44();
    
	void setRotationMatrix(double radians, Vector3<uint8_t> axis); //Convert "this" into a rotation Matirx (erases existent data)
    void setTranslationMatrix(T, T, T);                 //Convert "this" into a translation Matrix (erases existent data)
    void setTranslationMatrix(Vector3<T>);
    
    void setPosition(T, T, T);                               //Sets Matrix into a position about World coordinates
    void setPosition(Vector3<T>);
	void setRotation(double radians, Vector3<uint8_t> axis);       //Sets a rotation

	Vector3<T> getPosition();								 //Returns position
    
    void setU(const Vector3<T>& U);
    void setV(const Vector3<T>& V);
    void setN(const Vector3<T>& N);
    
	void rotate(double radians, Vector3<uint8_t> axis);       //Rotates Matrix about World
    void translate  (T,T,T);              //Translates about World coordinates
    void translate  (Vector3<T>);
	void rotateLocal(double radians, Vector3<uint8_t> axis);       //Rotates Matrix about Local Matrix rotation
    void translateLocal(T,T,T);           //Translates Matrix about Local Matrix coordinates
    void translateLocal(Vector3<T>);

    Vector3<T> rotateVector(Vector3<T>);                         //Rotates a given Vector
    Vector3<T> translateVector(Vector3<T>);                      //Translates a given Vector
    
    ~Matrix44();
    
    Matrix44<T> & operator =(const Matrix<T> & b);
    Matrix44<T> & operator =(const Matrix44<T> & b);
    
    Matrix44<T> & mult(const Matrix44<T> & b, Matrix44<T> & r) const; //Matrix multiplication without allocating new memory
    
    friend Matrix44<T> & operator *(const Matrix44<T> &a, const Matrix44<T> &b);
};

#endif
