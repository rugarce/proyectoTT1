#ifndef _GLOBAL_
#define _GLOBAL_

#include "../include/matrix.hpp"
#include <cmath>

extern Matrix eopdata;
extern Matrix Cnm;
extern Matrix Snm;
extern Matrix PC;
extern Matrix obs;

typedef struct {
    double Mjd_UTC;
    double Mjd_TT;
    int n;
    int m;
    int sun;
    int moon;
    int planets;
} AuxParamStruct;

extern AuxParamStruct AuxParam;

void eop19620101(int c);
void GGM03S(int n);
void DE430Coeff(int f, int c);
void GEOS3(int f);

#endif