#ifndef CHEM
#define CHEM
#include <stdlib.h>
#include <string.h>

#include "rationalMatrix.h"


extern int** baby;
extern int myRow;
extern int myColume;
void setChem(const char* chem);
void toMatrixBaby();
void freeChem();

#endif