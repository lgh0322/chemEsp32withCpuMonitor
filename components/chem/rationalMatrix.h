#ifndef RATIONALMATRIX
#define RATIONALMATRIX
#include "rationalNumber.h"
#include "stdlib.h"
#ifdef __cplusplus
extern "C"
{
#endif
void initMatrix(int ** chem, int myRow, int myColumn);
void rref();
void coefficientArray();
extern int * coefficientNum;
extern RationalNumber** rationalMatrix;
void freeMatrix() ;
#ifdef __cplusplus
}
#endif
#endif