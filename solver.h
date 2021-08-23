#ifndef __SOLVER_H__
#define __SOLVER_H__

const float PRECISION = 0.0001;

enum rootnum
{
    NO_ROOT = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    ERROR_OCCUR = 3,
    INFINITE_ROOTS = 8
};
enum errors
{
    NO_ERRORS = 0,
    VARIABLE_OVERFLOW = 1,
    NULL_POINTER = 2,
    EQUAL_POINTERS = 3,
    NAN_INPUT = 4
};

/*!
\brief Сравнивает 2 float
\param x1,x2 числа для сравнения
\return 0 - равны, 1 - первое больше, -1 - второе больше, аналогия с strcmp
*/
int floatcmp(float x1, float x2);

/*!
\brief Решает квадратное уравнение от переданных коэффициентов
\detail Решает квадрратное уравнение разбивая на различные случаи в зависимости от входных данных квадратное, линейное и т.д
\param a,b,с коэффициенты
\param x1,x2 корни возвращаемые по итогам работы
\warning при бесконечном количестве корней return возвращает 8, при ошибке возвращает 3
\return количество корней
*/
int kvadratka(float a, float b, float c, float* x1, float* x2);

/*!
\brief Печатает решение квадратного уравнениея в консоль
\param a,b,с коэффициенты
*/
int output(float a, float b, float c);

/*!
\brief Печатает информацию о корнях
\param Rootnum количество корней
*/
void typeRootnum(int Rootnum);

/*!
\brief Печатает информацию об ошибках
\param error пояснение к ошибке
*/
void typeErrors(int error);

#endif
