//
//  Matrix.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#include "Matrix.h"

Matrix::Matrix(int r, int c){
    assert(r != 0 && c != 0);               //Matrix can't have 0 rows or columns
    size_    = r*c;
    rows_    = r;
    columns_ = c;
    
    m = new double[size_];
    clear();
}

void Matrix::clear(){
    for(int i = 0; i < size_; ++i)
        m[i] = 0;
}

double Matrix::get(int r, int c) const{
    assert(r < rows_ && c < columns_);          //You are out of the matrix
    return m[r*columns_+c];
}

int Matrix::rows() const{
    return rows_;
}

int Matrix::columns() const{
    return columns_;
}

void Matrix::print() const{
    for(int i = 0; i < columns_-1; ++i)
        cout << "------";
    cout << "-----" << endl;
    
    cout << fixed;
    for(int c = 0; c < columns_; ++c){
        for(int r = 0; r < rows_; ++r){
            cout << setprecision(3) << get(r,c);
            cout << fixed << " ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < columns_-1; ++i)
        cout << "------";
    cout << "-----" << endl;
}

void Matrix::set(int r, int c, double stuff){
    assert(r < rows_ && c < columns_);          //You are out of the matrix
    m[r*columns_+c] = stuff;
}

void Matrix::setIdentity(){
    assert(rows_ == columns_);                  //You can only create a square identity matrix
    clear();
    
    int r=0, c=0;
    while(r<rows_ && c<columns_){
        set(r,c,1);
        r++;
        c++;
    }
}