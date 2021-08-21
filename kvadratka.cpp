#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define TEST true

#define PRECISION 0.0001

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
\brief Находит дискриминант от переданных коэффициентов
\param a,b,с коэффициенты
\return дискриминант
*/
float discr(float a, float b, float c)
{
    return (b * b) - (4 * a * c);
}

/*!
\brief Находит количество корней квадратного уравнения от переданных коэффициентов
\param a,b,с коэффициенты
\return количество корней
*/
int check(float a, float b, float c)
{
    float d = discr(a, b, c);
    return floatcmp(d, 0) + 1;
}

/*!
\brief Находит корень линейного уравнения от переданных коэффициентов
\param b,с коэффициенты
\return корень
*/
float schet_linear(float b, float c)
{
    if(floatcmp(c, 0) == 0)
        return float(0);
    else
        return -c / b;
}

/*!
\brief Находит корни квадратного уравнения от переданных коэффициентов
\param a,b,с коэффициенты
\param x1,x2 возвращаемые корни уравнения
*/
void schet_kvadr(float a, float b, float c, float* x1, float* x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x2 != x1);
    if(check(a, b, c) == 0)
    {
        *x1 = 0;
        *x2 = 0;
    }
    float d = sqrt(discr(a, b, c)) / (2 * a);
    float const_part = -b / (2 * a);
    *x1 = -d + const_part;
    *x2 =  d + const_part;
}

/*!
\brief Решает квадратное уравнение от переданных коэффициентов
\detail Решает квадрратное уравнение разбивая на различные случаи в зависимости от входных данных квадратное, линейное и т.д
\param a,b,с коэффициенты
\param x1,x2 корни возвращаемые по итогам работы
\warning при бесконечном количестве корней return возвращает 8
\return количество корней
*/
int kvadratka(float a, float b, float c, float* x1, float* x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x2 != x1);
    *x1 = 0;
    *x2 = 0;
    if(floatcmp(a, 0) == 0 && floatcmp(b, 0) == 0)
        return (floatcmp(c, 0) == 0) ? 8 : 0;
    if(floatcmp(a, 0) == 0)
    {
        *x1 = schet_linear(b, c);
        return 1;
    }
    schet_kvadr(a, b, c, x1, x2);
    return check(a, b, c);
}

/*!
\brief тестирующая функция
\detail тестирующая функция прогоняет значения из data через kvadratka,
сравнивает с эталонными из data_check и пишет результаты тестов в консоль
*/
void test()
{
    int k = 9;
    float x1 = 0, x2 = 0;
    float data[k][3]= {{1, 4,-3}, {1, 0, -4}, {0,0,0}, {0,4,5}, {0, 0, 5}, {2, 3, 7},
    {15246, 120536, -645721},{0, 1154526, -1125452}, {1, -2068, 1069156}};
    float data_check[k][3] = {{2, -4.6458, 0.6458}, {2, -2.0000, 2.0000}, {8, 0, 0}, {1, -1.2500, 0}, {0, 0, 0},
    {0, 0, 0}, {2, -11.5675, 3.6614}, {1, 0.9748, 0}, {1, 1034.0000, 1034.0000}};
    for(int i = 0; i < k; i++)
    {
        int number_of_roots = kvadratka(data[i][0], data[i][1], data[i][2], &x1, &x2);
        if(number_of_roots == int(data_check[i][0]) && floatcmp(x1, data_check[i][1]) == 0 && floatcmp(x2, data_check[i][2]) == 0)
            printf("test %i OK\n", i + 1);
        else
        {
            printf("test %i FAILED\n", i + 1);
            printf("right output: %i %.4f %.4f\n", int(data_check[i][0]), data_check[i][1], data_check[i][2]);
            printf("program output: %i %.4f %.4f\n", number_of_roots, x1, x2);
        }
    }
}

/*!
\detail в режиме теста запускает тестирующую функцию,
в обычном считывает коэффициенты из консоли и запускает kvadratka,
а затем печатает полученные значения
*/
int main()
{
    float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    if(TEST)
    {
        test();
        return 0;
    }
    puts("type a b c");
    assert(scanf("%f %f %f", &a, &b, &c) == 3);
    int number_of_roots = kvadratka(a, b, c, &x1, &x2);
    if(number_of_roots != 8)
    {
        printf("number of roots: %d\n", number_of_roots);
        if(number_of_roots == 1)
            printf("root: %.4f\n", x1);
        if(number_of_roots == 2)
            printf("roots: %.4f %.4f\n", x1, x2);
        return 0;
    }
    puts("roots belongs to R");
    return 0;
}

