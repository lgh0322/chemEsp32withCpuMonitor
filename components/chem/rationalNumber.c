#include "rationalNumber.h"

int absInt(int x)
{
    if(x < 0)
    {
        return -x;
    }
    else
    {
        return x;
    }
}




//--------------a=b--------------------------b->a;
void set( RationalNumber *a,  RationalNumber *b)
{
    a->numerator = b->numerator;
    a->denominator = b->denominator;
}


void simplify( RationalNumber* x)
{
    if(x->numerator == 0)
    {
        x->denominator = 1;
        return;
    }

    int np = absInt(x->numerator);
    int dp = absInt(x->denominator);
    int remainder = dp % np;
    int temp = 0;

    while(remainder != 0)
    {
        temp = np % remainder;
        np = remainder;
        remainder = temp;
    }

    x->numerator /= np;
    x->denominator /= np;
}

//-------------------------a+=b;
void add( RationalNumber *a,  RationalNumber *b)
{
    a->numerator = (a->numerator) * (b->denominator) + (b->numerator) * (a->denominator);
    (a->denominator) *= (b->denominator);
    simplify(a);
}




void multiply( RationalNumber *a,  RationalNumber *b)
{
    (a->numerator) *= (b->numerator);
    (a->denominator) *= (b->denominator);
    simplify(a);
}

void inv( RationalNumber* x)
{
    int temp = x->numerator;
    x->numerator = x->denominator;
    x->denominator = temp;
}


void strains( RationalNumber* x)
{
    x->numerator = -x->numerator;
}


int isZero( RationalNumber* x)
{
    if(x->numerator == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


