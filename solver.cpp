#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <errno.h>
#include "solver.h"

int floatcmp(float x1, float x2)
{
    if((x1 - x2) > PRECISION)
        return 1;
    if((x1 - x2) < -PRECISION)
        return -1;
    return 0;
}

float schet_linear(float b, float c)
{
    if(!floatcmp(c, 0))
        return float(0);
    else
        return -c / b;
}

int schet_kvadr(float a, float b, float c, float* x1, float* x2)
{
    if((fabs(FLT_MAX / b) < fabs(b)) || (fabs((FLT_MAX / 4) / a) < fabs(c)) || (FLT_MAX - b * b) < (- 4 * a * c))
    {
        errno = VARIABLE_OVERFLOW;
        return ERROR_OCCUR;
    }
    float d = (b * b) - (4 * a * c);
    if(d < 0)
    {
        *x1 = 0;
        *x2 = 0;
        return 0;
    }
    float change_part = sqrt(d) / (2 * a);
    float const_part = -b / (2 * a);
    *x1 = -change_part + const_part;
    *x2 =  change_part + const_part;
    return floatcmp(d, 0) + 1;
}

int kvadratka(float a, float b, float c, float* x1, float* x2)
{
    if(x1 == NULL || x2 == NULL)
    {
        errno = NULL_POINTER;
        return ERROR_OCCUR;
    }
    if(x2 == x1)
    {
        errno = EQUAL_POINTERS;
        return ERROR_OCCUR;
    }
    if(isnan(a) || isnan(b) || isnan(c))
    {
        errno = NAN_INPUT;
        return ERROR_OCCUR;
    }
    *x1 = 0;
    *x2 = 0;
    if(!floatcmp(a, 0) && !floatcmp(b, 0))
        return (!floatcmp(c, 0)) ? INFINITE_ROOTS : NO_ROOT;
    if(!floatcmp(a, 0))
    {
        *x1 = schet_linear(b, c);
        return ONE_ROOT;
    }
    return schet_kvadr(a, b, c, x1, x2);
}
