//
//  MathFramework.h
//  MathFramework
//
//  Created by Dani Barca on 30/06/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#ifndef MathFramework_MathFramework_h
#define MathFramework_MathFramework_h

#include "Includes.h"
#include "Vector.h"
#include "Matrix.h"

#define PI      3.14159265358979323846f
#define DEG2RAD 0.01745329251994329576923f
#define RAD2DEG 57.2957795130823208767981f

#define DEGTORAD(d) d*DEG2RAD
#define RADTODEG(r) r*RAD2DEG

int round(float x);
int round_d(double x);

#endif
