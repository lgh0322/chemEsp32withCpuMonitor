#ifndef RATIONALNUMBER
#define RATIONALNUMBER
#ifdef __cplusplus
extern "C"
{
#endif
typedef  struct
{
    int numerator;
    int denominator;
} RationalNumber;


void set( RationalNumber *a,  RationalNumber *b);
void inv( RationalNumber* x);
void add( RationalNumber *a,  RationalNumber *b);
void multiply( RationalNumber *a,  RationalNumber *b);
void strains( RationalNumber* x);
int isZero( RationalNumber* x);
int absInt(int x);
#ifdef __cplusplus
}
#endif
#endif