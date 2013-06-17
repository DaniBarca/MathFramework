//
//  Matrix.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#include "Matrix.h"

Matrix::Matrix(const Matrix & other){
    operator=(other);
}

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
    assert(r * columns_ + c < size_ && r < rows_ && c < columns_ );          //You are out of the matrix
    return m[r*columns_+c];
}

int Matrix::rows() const{
    return rows_;
}

int Matrix::columns() const{
    return columns_;
}

int Matrix::size() const{
    return size_;
}

void Matrix::print() const{
    for(int i = 0; i < columns_-1; ++i)
        cout << "------";
    cout << "-----" << endl;
    
    cout << fixed;
    for(int r = 0; r < rows_; ++r){
        for(int c = 0; c < columns_; ++c){
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
    assert(r * columns_ + c < size_ && r < rows_ && c < columns_ );  //You are out of the matrix
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

Matrix & Matrix::operator =(const Matrix & b){
    if(this != &b){
        delete [] m;
        m = new double[b.size()];
        copy(b.m, b.m+b.size(),m);
        size_ = b.size();
    }
    return *this;
}

//---------------Operators:

Matrix & operator*(const Matrix & a, const Matrix & b){
    assert(a.columns() == b.rows());
    Matrix *m = new Matrix(a.rows(), b.columns());
    double temp;
    
    for(int r = 0; r < m->rows(); ++r){
        for(int c = 0; c < m->columns(); ++c){
            temp = 0;
            for(int t = 0; t < a.columns(); ++t)
                temp += a.get(r,t) * b.get(t,c);
            m->set(r,c,temp);
        }
    }
    
    return *m;
}
