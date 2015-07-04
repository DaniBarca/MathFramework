//
//  Matrix.cpp
//  MathFramework
//
//  Created by Dani Barca on 17/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#include "Matrix.h"

template<class T>
Matrix<T>::Matrix(const Matrix<T> & other){
    operator=(other);
}

template<class T>
Matrix<T>::Matrix(const Vector<T> & other){
    operator=(other);
}

template<class T>
Matrix<T>::Matrix(unsigned int r, unsigned int c){
    assert(r != 0 && c != 0);               //Matrix can't have 0 rows or columns
    size_    = r*c;
    rows_    = r;
    columns_ = c;
    
    m = new double[size_];
    clear();
}

template<class T>
Matrix<T>::Matrix(){
    operator=(Matrix<T>(3,3));
}

template<class T>
void Matrix<T>::clear(int n){
    for(int i = 0; i < size_; ++i)
        m[i] = n;
}

template<class T>
T Matrix<T>::get(int r, int c) const{
    assert(r * columns_ + c < size_ && r < rows_ && c < columns_ );          //You are out of the matrix
    return m[r*columns_+c];
}

template<class T>
T Matrix<T>::get(int n) const{
    assert(n < size_);
    return m[n];
}

template<class T>
int Matrix<T>::rows() const{
    return rows_;
}

template<class T>
int Matrix<T>::columns() const{
    return columns_;
}

template<class T>
int Matrix<T>::size() const{
    return size_;
}

template<class T>
void Matrix<T>::print() const{
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

template<class T>
void Matrix<T>::set(int r, int c, T stuff){
    assert(r * columns_ + c < size_ && r < rows_ && c < columns_ );  //You are out of the matrix
    m[r*columns_+c] = stuff;
}

template<class T>
void Matrix<T>::setIdentity(){
    assert(rows_ == columns_);                  //You can only create a square identity matrix
    clear();
    
    int r=0, c=0;
    while(r<rows_ && c<columns_){
        set(r,c,1);
        r++;
        c++;
    }
}

template<class T>
void Matrix<T>::transpose(){
    Matrix<T> matrix = Matrix<T>(columns_,rows_);
    for(int r = 0; r < rows_; ++r){
        for(int c = 0; c < columns_; ++c){
            matrix.set(c, r, get(r,c));
        }
    }
    copy(matrix.m,matrix.m+matrix.size(),m);  //We copy the resulting trasposed matrix to "this" Matrix
}

template<class T>
int Matrix<T>::isSquare() const{
    return (rows_ == columns_) ? rows_ : -1;
}

template<class T>
Matrix<T>::~Matrix(){
    delete [] m;
}

//---------------Operators:
template<class T>
Matrix<T> & Matrix<T>::operator =(const Matrix<T> & b){
    if(this != &b){
        //delete [] m;
        //m = new double[b.size()];
        copy(b.m, b.m+b.size(),m);
        size_    = b.size();
        rows_    = b.rows();
        columns_ = b.columns();
    }
    return *this;
}

template<class T>
Matrix<T> & Matrix<T>::operator=(const Vector<T> &v){
    m = new T[v.size()];
    rows_   = v.size();
    columns_= 1;
    size_   = v.size();
    
    for(int i = 0; i < v.size(); ++i)
        m[i] = v[i];
    
    return *this;
}

template<class T>
T * Matrix<T>::operator[](const unsigned int i){
    assert(i < size_);
    return m+i*columns_;
}

template<class T>
Matrix<T> & operator*(const Matrix<T> & a, const Matrix<T> & b){
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
template<class T>
Vector<T> & operator*(const Matrix<T> & a, const Vector<T> & v){
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
    Vector *res = new Vector<T>(a.rows());
    *res = a*m;
    return *res;
}

//----------------------------------------------------------------------------------------------
//Matrix44
//----------------------------------------------------------------------------------------------
template<class T>
Matrix44<T>::Matrix44(const Matrix<T> & other) : Matrix(4,4){
    assert(other.isSquare() == 4);                      //You can only assign a 4x4 matrix to a Matrix44
    operator=(other);
}

template<class T>
Matrix44<T>::Matrix44(const Matrix44<T> & other) : Matrix(4,4){
    operator=(other);
}

template<class T>
Matrix44<T>::Matrix44() : Matrix<T>(4,4){}

template<class T>
void Matrix44<T>::setRotationMatrix(double radians, Vector3<uint8_t> axis){
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

template<class T>
void Matrix44<T>::setTranslationMatrix(T x, T y, T z){
    setIdentity();
    setPosition(x,y,z);
}

template<class T>
void Matrix44<T>::setPosition(T x, T y, T z){
    m[X_I] = x;
    m[Y_I] = y;
    m[Z_I]= z;
}

template<class T>
void Matrix44<T>::setPosition(Vector3<T> pos){
    setPosition(pos[0], pos[1], pos[2]);
}

template<class T>
void Matrix44<T>::setRotation(double radians, Vector3<uint8_t> axis){
    Matrix44 r   = Matrix44();
    Matrix44 aux = Matrix44();;
    aux.setIdentity();
    aux.setPosition(m[X_I],m[Y_I],m[Z_I]);
    r.setRotationMatrix(radians, axis);
    operator=(r*aux);
}

template<class T>
Vector3<T> Matrix44<T>::getPosition(){
	return Vector3(m[X_I], m[Y_I], m[Z_I]);
}

template<class T>
void Matrix44<T>::setU(const Vector3<T>& U){
    m[0] = U[0];
    m[1] = U[1];
    m[2] = U[2];
}

template<class T>
void Matrix44<T>::setV(const Vector3<T>& V){
    m[4] = V[0];
    m[5] = V[1];
    m[6] = V[2];
}

template<class T>
void Matrix44<T>::setN(const Vector3<T>& N){
    m[8] = N[0];
    m[9] = N[1];
    m[10]= N[2];
}

template<class T>
void Matrix44<T>::rotate(double radians, Vector3<uint8_t> axis){
    Matrix44 r   = Matrix44();
    Matrix44 aux = *this;
    operator=(r*aux);
}

template<class T>
void Matrix44<T>::translate(T x, T y, T z){
    m[X_I] += x;
    m[Y_I] += y;
    m[Z_I] += z;
}

template<class T>
void Matrix44<T>::translate(Vector3<T> v){
    translate(v[0], v[1], v[2]);
}

//---------------------
//For a local rotation you have to:
//1. Put the Matrix at 0,0,0 world coordinates after memorizing the original position
//2. Make a normal rotation
//3. Put back Matrix to its original position
//---------------------
template<class T>
void Matrix44<T>::rotateLocal(double radians, Vector3<uint8_t> axis){
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

template<class T>
void Matrix44<T>::translateLocal(T x, T y, T z){
    Matrix44<T> t = Matrix44<T>();
    t.setTranslationMatrix(x, y, z);
    operator=(t*(*this));
}

template<class T>
void Matrix44<T>::translateLocal(Vector3<T> v){
    translateLocal(v[0], v[1], v[2]);
}

template<class T>
Vector3<T> Matrix44<T>::rotateVector(Vector3<T> v){
    assert(v.size() == 3);
    Matrix44<T> aux = *this;
    aux.setPosition(0,0,0);
    return aux * v;
}

template<class T>
Vector3<T> Matrix44<T>::translateVector(Vector3<T> v){
    Vector3 aux = v;
    aux[0] += m[X_I];
    aux[1] += m[Y_I];
    aux[2] += m[Z_I];
    return aux;
}

template<class T>
Matrix44<T>::~Matrix44(){
}

//---------------Operators:
template<class T>
Matrix44<T> & Matrix44<T>::operator =(const Matrix<T> & b){
    assert(b.isSquare() == size_);                      //You can only assign a 4x4 Matrix to a Matrix44
    if(this != &b){
        //delete [] m;
        //m = new double[b.size()];
        
        for(int i = 0; i < size_; ++i){
            m[i] = b.m[i];
        }
        
        /*for(int i = 0; i < 4; ++i){
            for(int j = 0 ; j < 4; ++j)
                set(i, j, b.get(i,j));
        }*/
        
        size_    = b.size();
        rows_    = b.rows();
        columns_ = b.columns();
    }
    return *this;
}

template<class T>
Matrix44<T> & Matrix44<T>::operator =(const Matrix44<T> & b){
   // if(this != &b){
        //delete [] m;
        //m = new double[b.size()];
        
        for(int i = 0; i < size_; ++i){
            m[i] = b.m[i];
        }
        
        /*for(int i = 0; i < 4; ++i){
            for(int j = 0 ; j < 4; ++j)
                set(i, j, b.get(i,j));
        }*/
        
        size_    = b.size();
        rows_    = b.rows();
        columns_ = b.columns();
    //}
    return *this;
}

template<class T>
Matrix44<T> & Matrix44<T>::mult(const Matrix44<T> & b, Matrix44<T> & r) const{
    /*r.set(0,0,get(0,0) * b.get(0,0) + get(0,1) * b.get(1,0) + get(0,2) * b.get(2,0) + get(0,3) * b.get(3,0));
    r.set(0,1,get(0,0) * b.get(0,1) + get(0,1) * b.get(1,1) + get(0,2) * b.get(2,1) + get(0,3) * b.get(3,1));
    r.set(0,2,get(0,0) * b.get(0,2) + get(0,1) * b.get(1,2) + get(0,2) * b.get(2,2) + get(0,3) * b.get(3,2));
    r.set(0,3,get(0,0) * b.get(0,3) + get(0,1) * b.get(1,3) + get(0,2) * b.get(2,3) + get(0,3) * b.get(3,3));
    r.set(1,0,get(1,0) * b.get(0,0) + get(1,1) * b.get(1,0) + get(1,2) * b.get(2,0) + get(1,3) * b.get(3,0));
    r.set(1,1,get(1,0) * b.get(0,1) + get(1,1) * b.get(1,1) + get(1,2) * b.get(2,1) + get(1,3) * b.get(3,1));
    r.set(1,2,get(1,0) * b.get(0,2) + get(1,1) * b.get(1,2) + get(1,2) * b.get(2,2) + get(1,3) * b.get(3,2));
    r.set(1,3,get(1,0) * b.get(0,3) + get(1,1) * b.get(1,3) + get(1,2) * b.get(2,3) + get(1,3) * b.get(3,3));
    r.set(2,0,get(2,0) * b.get(0,0) + get(2,1) * b.get(1,0) + get(2,2) * b.get(2,0) + get(2,3) * b.get(3,0));
    r.set(2,1,get(2,0) * b.get(0,1) + get(2,1) * b.get(1,1) + get(2,2) * b.get(2,1) + get(2,3) * b.get(3,1));
    r.set(2,2,get(2,0) * b.get(0,2) + get(2,1) * b.get(1,2) + get(2,2) * b.get(2,2) + get(2,3) * b.get(3,2));
    r.set(2,3,get(2,0) * b.get(0,3) + get(2,1) * b.get(1,3) + get(2,2) * b.get(2,3) + get(2,3) * b.get(3,3));
    r.set(3,0,get(3,0) * b.get(0,0) + get(3,1) * b.get(1,0) + get(3,2) * b.get(2,0) + get(3,3) * b.get(3,0));
    r.set(3,1,get(3,0) * b.get(0,1) + get(3,1) * b.get(1,1) + get(3,2) * b.get(2,1) + get(3,3) * b.get(3,1));
    r.set(3,2,get(3,0) * b.get(0,2) + get(3,1) * b.get(1,2) + get(3,2) * b.get(2,2) + get(3,3) * b.get(3,2));
    r.set(3,3,get(3,0) * b.get(0,3) + get(3,1) * b.get(1,3) + get(3,2) * b.get(2,3) + get(3,3) * b.get(3,3));*/
    
    
    r.m[0]  = m[0]  * b.m[0] + m[1]  * b.m[4] + m[2]  * b.m[8]  + m[3]  * b.m[12];
    r.m[1]  = m[0]  * b.m[1] + m[1]  * b.m[5] + m[2]  * b.m[9]  + m[3]  * b.m[13];
    r.m[2]  = m[0]  * b.m[2] + m[1]  * b.m[6] + m[2]  * b.m[10] + m[3]  * b.m[14];
    r.m[3]  = m[0]  * b.m[3] + m[1]  * b.m[7] + m[2]  * b.m[11] + m[3]  * b.m[15];
    
    r.m[4]  = m[4]  * b.m[0] + m[5]  * b.m[4] + m[6]  * b.m[8]  + m[7]  * b.m[12];
    r.m[5]  = m[4]  * b.m[1] + m[5]  * b.m[5] + m[6]  * b.m[9]  + m[7]  * b.m[13];
    r.m[6]  = m[4]  * b.m[2] + m[5]  * b.m[6] + m[6]  * b.m[10] + m[7]  * b.m[14];
    r.m[7]  = m[4]  * b.m[3] + m[5]  * b.m[7] + m[6]  * b.m[11] + m[7]  * b.m[15];
    
    r.m[8]  = m[8]  * b.m[0] + m[9]  * b.m[4] + m[10] * b.m[8]  + m[11] * b.m[12];
    r.m[9]  = m[8]  * b.m[1] + m[9]  * b.m[5] + m[10] * b.m[9]  + m[11] * b.m[13];
    r.m[10] = m[8]  * b.m[2] + m[9]  * b.m[6] + m[10] * b.m[10] + m[11] * b.m[14];
    r.m[11] = m[8]  * b.m[3] + m[9]  * b.m[7] + m[10] * b.m[11] + m[11] * b.m[15];
    
    r.m[12] = m[12] * b.m[0] + m[13] * b.m[4] + m[14] * b.m[8]  + m[15] * b.m[12];
    r.m[13] = m[12] * b.m[1] + m[13] * b.m[5] + m[14] * b.m[9]  + m[15] * b.m[13];
    r.m[14] = m[12] * b.m[2] + m[13] * b.m[6] + m[14] * b.m[10] + m[15] * b.m[14];
    r.m[15] = m[12] * b.m[3] + m[13] * b.m[7] + m[14] * b.m[11] + m[15] * b.m[15];
    
    /*...
    
    r.m[0] = m[0] * b.m[0];  r.m[1] = m[0] * b.m[1];  r.m[2] = m[0] * b.m[2];  r.m[3] = m[0] * b.m[3];
    r.m[0]+= m[1] * b.m[4];  r.m[1]+= m[1] * b.m[5];  r.m[2]+= m[1] * b.m[6];  r.m[3]+= m[1] * b.m[7];
    r.m[0]+= m[2] * b.m[8];  r.m[1]+= m[2] * b.m[9];  r.m[2]+= m[2] * b.m[10]; r.m[3]+= m[2] * b.m[11];
    r.m[0]+= m[3] * b.m[12]; r.m[1]+= m[3] * b.m[13]; r.m[2]+= m[3] * b.m[14]; r.m[3]+= m[3] * b.m[15];
    
    r.m[4] = m[0] * b.m[0];  r.m[5] = m[0] * b.m[1];  r.m[6] = m[0] * b.m[2];  r.m[7] = m[0] * b.m[3];
    r.m[4]+= m[1] * b.m[4];  r.m[5]+= m[1] * b.m[5];  r.m[6]+= m[1] * b.m[6];  r.m[7]+= m[1] * b.m[7];
    r.m[4]+= m[2] * b.m[8];  r.m[5]+= m[2] * b.m[9];  r.m[6]+= m[2] * b.m[10]; r.m[7]+= m[2] * b.m[11];
    r.m[4]+= m[3] * b.m[12]; r.m[5]+= m[3] * b.m[13]; r.m[6]+= m[3] * b.m[14]; r.m[7]+= m[3] * b.m[15];

    r.m[8] = m[0] * b.m[0];  r.m[9] = m[0] * b.m[1];  r.m[10] = m[0] * b.m[2];  r.m[11] = m[0] * b.m[3];
    r.m[8]+= m[1] * b.m[4];  r.m[9]+= m[1] * b.m[5];  r.m[10]+= m[1] * b.m[6];  r.m[11]+= m[1] * b.m[7];
    r.m[8]+= m[2] * b.m[8];  r.m[9]+= m[2] * b.m[9];  r.m[10]+= m[2] * b.m[10]; r.m[11]+= m[2] * b.m[11];
    r.m[8]+= m[3] * b.m[12]; r.m[9]+= m[3] * b.m[13]; r.m[10]+= m[3] * b.m[14]; r.m[11]+= m[3] * b.m[15];

    r.m[12] = m[0] * b.m[0];  r.m[13] = m[0] * b.m[1];  r.m[14] = m[0] * b.m[2];  r.m[15] = m[0] * b.m[3];
    r.m[12]+= m[1] * b.m[4];  r.m[13]+= m[1] * b.m[5];  r.m[14]+= m[1] * b.m[6];  r.m[15]+= m[1] * b.m[7];
    r.m[12]+= m[2] * b.m[8];  r.m[13]+= m[2] * b.m[9];  r.m[14]+= m[2] * b.m[10]; r.m[15]+= m[2] * b.m[11];
    r.m[12]+= m[3] * b.m[12]; r.m[13]+= m[3] * b.m[13]; r.m[14]+= m[3] * b.m[14]; r.m[15]+= m[3] * b.m[15];
    */
    
    return r;
}

template<class T>
Matrix44<T> & operator *(const Matrix44<T> & a, const Matrix44<T> & b){
    Matrix44<T> m = Matrix44<T>();
    return a.mult(b,m);
}
