#include <stdio.h>
#include <math.h>
#define NDEBUG
#include <assert.h>
#include <float.h>
#include <errno.h>
#include "solver.h"

void typeRootnum(int Rootnum)
{
    switch(Rootnum)
    {
    case NO_ROOT:
        puts("no roots");
        break;
    case ONE_ROOT:
        puts("one root");
        break;
    case TWO_ROOTS:
        puts("two roots");
        break;
    case ERROR_OCCUR:
        puts("failed with an error");
        break;
    case INFINITE_ROOTS:
        puts("roots belongs to R");
        break;
    default:
        puts("unknown root number");
        break;
    }
}

void typeErrors(int error)
{
    switch(error)
    {
    case NO_ERRORS:
        puts("no errors");
        break;
    case VARIABLE_OVERFLOW:
        puts("the value in the variable is too large");
        break;
    case NULL_POINTER:
        puts("pointer = NULL");
        break;
    case EQUAL_POINTERS:
        puts("two equal pointers");
        break;
    case NAN_INPUT:
        puts("value of the variable is NAN");
        break;
    default:
        puts("unknown error number");
        break;
    }
}

int floatcmp(float x1, float x2)
{
    if((x1 - x2) > PRECISION)
        return 1;
    if((x1 - x2) < -PRECISION)
        return -1;
    return 0;
}

/*!
\brief Находит корень линейного уравнения от переданных коэффициентов
\param b,с коэффициенты
\return корень
*/
static float schet_linear(float b, float c)
{
    if(!floatcmp(c, 0))
        return float(0);
    else
        return -c / b;
}

/*!
\brief Находит корни квадратного уравнения от переданных коэффициентов
\param a,b,с коэффициенты
\param x1,x2 возвращаемые корни уравнения
*/
static int schet_kvadr(float a, float b, float c, float* x1, float* x2)
{
    assert(isfinite(b * b));
    assert(isfinite(4 * a * c));
    assert(isfinite(b * b - 4 * a * c));
    if(!isfinite(b * b) || !isfinite(4 * a * c) || !isfinite(b * b - 4 * a * c))
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
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);
    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));
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

int output(float a, float b, float c)
{
    float x1 = NAN, x2 = NAN;
    int number_of_roots = kvadratka(a, b, c, &x1, &x2);
    if(errno != 0)
    {
        printf("ERROR: %d\n", errno);
        typeErrors(errno);
        return errno;
    }
    if(number_of_roots != INFINITE_ROOTS)
    {
        printf("number of roots: %d\n", number_of_roots);
        if(number_of_roots == ONE_ROOT)
            printf("root: %.4f\n", x1);
        if(number_of_roots == TWO_ROOTS)
            printf("roots: %.4f %.4f\n", x1, x2);
        return 0;
    }
    puts("roots belongs to R");
    return 0;
}
