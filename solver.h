#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <errno.h>

#define PRECISION 0.0001

/*!
\brief Сравнивает 2 float
\param x1,x2 числа для сравнения
\return 0 - равны, 1 - первое больше, -1 - второе больше, аналогия с strcmp
*/
int floatcmp(float x1, float x2);

/*!
\brief Находит корень линейного уравнения от переданных коэффициентов
\param b,с коэффициенты
\return корень
*/
float schet_linear(float b, float c);

/*!
\brief Находит корни квадратного уравнения от переданных коэффициентов
\param a,b,с коэффициенты
\param x1,x2 возвращаемые корни уравнения
*/
int schet_kvadr(float a, float b, float c, float* x1, float* x2);

/*!
\brief Решает квадратное уравнение от переданных коэффициентов
\detail Решает квадрратное уравнение разбивая на различные случаи в зависимости от входных данных квадратное, линейное и т.д
\param a,b,с коэффициенты
\param x1,x2 корни возвращаемые по итогам работы
\warning при бесконечном количестве корней return возвращает 8, при ошибке возвращает 3
\return количество корней
*/
int kvadratka(float a, float b, float c, float* x1, float* x2);

#endif
