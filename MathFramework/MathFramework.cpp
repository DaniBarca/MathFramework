//
//  MathFramework.cpp
//  MathFramework
//
//  Created by Dani Barca on 23/07/13.
//  Copyleft (ɔ) 2013 Dani Barca.
//

#include "MathFramework.h"

int round_f(float x){ return (int)((x < 0) ? x - 0.5 : x + 0.5); }

int round_d(double x){ return round_f((float)x); }
