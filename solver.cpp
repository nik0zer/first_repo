#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <errno.h>
#include "solver.h"

#define PRECISION 0.0001

enum rootnum {NO_ROOT, ONE_ROOT, TWO_ROOTS, ERROR_OCCUR, INFINITE_ROOTS = 8};
enum errors {NO_ERRORS, VARIABLE_OVERFLOW, NULL_POINTER, EQUAL_POINTERS, NAN_INPUT};

/*!
\brief Сравнивает 2 float
\param x1,x2 числа для сравнения
\return 0 - равны, 1 - первое больше, -1 - второе больше, аналогия с strcmp
*/
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
float schet_linear(float b, float c)
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
int schet_kvadr(float a, float b, float c, float* x1, float* x2)
{
    if((abs(FLT_MAX / b) < abs(b)) || (abs((FLT_MAX / 4) / a) < abs(c)))
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

/*!
\brief Решает квадратное уравнение от переданных коэффициентов
\detail Решает квадрратное уравнение разбивая на различные случаи в зависимости от входных данных квадратное, линейное и т.д
\param a,b,с коэффициенты
\param x1,x2 корни возвращаемые по итогам работы
\warning при бесконечном количестве корней return возвращает 8, при ошибке возвращает 3
\return количество корней
*/
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
