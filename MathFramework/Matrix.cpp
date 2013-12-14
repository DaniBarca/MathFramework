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

Matrix::Matrix(const Vector & other){
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

double Matrix::get(int n) const{
    assert(n < size_);
    return m[n];
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
    for(int i = 0; i < columns_-1; ++i)     //Some shiny things, erase it if you don't like it
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

void Matrix::transpose(){
    Matrix matrix = Matrix(columns_,rows_);
    for(int r = 0; r < rows_; ++r){
        for(int c = 0; c < columns_; ++c){
            matrix.set(c, r, get(r,c));
        }
    }
    copy(matrix.m,matrix.m+matrix.size(),m);  //We copy the resulting trasposed matrix to "this" Matrix
}

int Matrix::isSquare() const{
    return (rows_ == columns_) ? rows_ : -1;
}

//---------------Operators:
Matrix & Matrix::operator =(const Matrix & b){
    if(this != &b){
        delete [] m;
        m = new double[b.size()];
        copy(b.m, b.m+b.size(),m);
        size_    = b.size();
        rows_    = b.rows();
        columns_ = b.columns();
    }
    return *this;
}

Matrix & Matrix::operator=(const Vector &v){
    m = new double[v.size()];
    rows_   = v.size();
    columns_= 1;
    size_   = v.size();
    
    for(int i = 0; i < v.size(); ++i)
        m[i] = v[i];
    
    return *this;
}

double * Matrix::operator[](const int i){
    assert(i < size_);
    return m+i*columns_;
}

Matrix & operator*(const Matrix & a, const Matrix & b){
    assert(a.columns() == b.rows());                        //You can't multiply these matrix
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

//Here, we play with the fact that a vector can be considered a 1 column Matrix and vice-versa:
Vector & operator*(const Matrix & a, const Vector & v){
    assert(a.columns() == v.size() || (a.isSquare() == 4 && v.size() == 3));
    
    //Very useful for 3D operations, allows to multiply a 4x4 matrix and a 3-sized vector
    if(a.isSquare() == 4 && v.size() == 3){
        Vector *res = new Vector(3);
        res->set(0,a.get(0) * v[0] + a.get(1) * v[1] + a.get(2)  * v[2] + a.get(3));
        res->set(1,a.get(4) * v[0] + a.get(5) * v[1] + a.get(6)  * v[2] + a.get(7));
        res->set(2,a.get(8) * v[0] + a.get(9) * v[1] + a.get(10) * v[2] + a.get(11));
        return *res;
    }
    
    //For anything else:
    Matrix m = v;
    Vector *res = new Vector(a.rows());
    *res = a*m;
    return *res;
}

//----------------------------------------------------------------------------------------------
//Matrix44
//----------------------------------------------------------------------------------------------

Matrix44::Matrix44(const Matrix & other) : Matrix(4,4){
    assert(other.isSquare() == 4);                      //You can only assign a 4x4 matrix to a Matrix44
    operator=(other);
}

Matrix44::Matrix44(const Matrix44 & other) : Matrix(4,4){
    operator=(other);
}

Matrix44::Matrix44() : Matrix(4,4){}

void Matrix44::setRotationMatrix(double radians, Vector axis){
    assert(axis.size() == 3);
    clear();
	Vector axis_n = axis;
	axis_n.norm();
    
	float c = cos( radians );
	float s = sin( radians );
	float t = 1 - c;
    
	m[0] = t * axis[0] * axis[0] + c;
	m[4] = t * axis[0] * axis[1] - s * axis[2];
	m[8] = t * axis[0] * axis[2] + s * axis[1];
    
	m[1] = t * axis[0] * axis[1] + s * axis[2];
	m[5] = t * axis[1] * axis[1] + c;
	m[9] = t * axis[1] * axis[2] - s * axis[0];
    
	m[2] = t * axis[0] * axis[2] - s * axis[1];
	m[6] = t * axis[1] * axis[2] + s * axis[0];
	m[10]= t * axis[2] * axis[2] + c;
    
    m[15] = 1.0f;
}

void Matrix44::setTranslationMatrix(double x, double y, double z){
    setIdentity();
    setPosition(x,y,z);
}

void Matrix44::setPosition(double x, double y, double z){
    m[3] = x;
    m[7] = y;
    m[11]= z;
}

void Matrix44::setPosition(Vector pos){
    setPosition(pos[0], pos[1], pos[2]);
}

void Matrix44::setRotation(double radians, Vector axis){
    assert(axis.size() == 3);
    Matrix44 r   = Matrix44();
    Matrix44 aux = Matrix44();;
    aux.setIdentity();
    aux.setPosition(m[3],m[7],m[11]);
    r.setRotationMatrix(radians, axis);
    operator=(r*aux);
}

void Matrix44::rotate(double radians, Vector axis){
    Matrix44 r   = Matrix44();
    Matrix44 aux = *this;
    operator=(r*aux);
}

void Matrix44::translate(double x, double y, double z){
    m[3] += x;
    m[7] += y;
    m[11]+= z;
}

void Matrix44::translate(Vector v){
    translate(v[0], v[1], v[2]);
}

//---------------------
//For a local rotation you have to:
//1. Put the Matrix at 0,0,0 world coordinates after memorizing the original position
//2. Make a normal rotation
//3. Put back Matrix to its original position
//---------------------
void Matrix44::rotateLocal(double radians, Vector axis){
    //1
    Matrix44 r  = Matrix44();
    r.setRotationMatrix(radians,axis);
    
    Vector   pos= Vector(3);
    pos.takePosition(*this);

    setPosition(0,0,0);
    
    //2
    operator=(r*(*this));
    
    //3
    setPosition(pos[0], pos[1], pos[2]);
}

void Matrix44::translateLocal(double x, double y, double z){
    Matrix44 t = Matrix44();
    t.setTranslationMatrix(x, y, z);
    operator=(t*(*this));
}

void Matrix44::translateLocal(Vector v){
    translateLocal(v[0], v[1], v[2]);
}

Vector Matrix44::rotateVector(Vector v){
    assert(v.size() == 3);
    Matrix44 aux = *this;
    aux.setPosition(0,0,0);
    return aux * v;
}

Vector Matrix44::translateVector(Vector v){
    assert(v.size() == 3);
    Vector aux = v;
    aux[0] += m[3];
    aux[1] += m[7];
    aux[2] += m[11];
    return aux;
}

//---------------Operators:

Matrix44 & Matrix44::operator =(const Matrix & b){
    assert(b.isSquare() == 4);                      //You can only assign a 4x4 Matrix to a Matrix44
    if(this != &b){
        delete [] m;
        m = new double[b.size()];
        
        for(int i = 0; i < 4; ++i){
            for(int j = 0 ; j < 4; ++j)
                set(i, j, b.get(i,j));
        }
        
        size_    = b.size();
        rows_    = b.rows();
        columns_ = b.columns();
    }
    return *this;
}

Matrix44 & Matrix44::operator =(const Matrix44 & b){
    if(this != &b){
        delete [] m;
        m = new double[b.size()];
        
        for(int i = 0; i < 4; ++i){
            for(int j = 0 ; j < 4; ++j)
                set(i, j, b.get(i,j));
        }
        
        size_    = b.size();
        rows_    = b.rows();
        columns_ = b.columns();
    }
    return *this;
}
