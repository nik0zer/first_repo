#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define TEST true
#define PRECISION 0.0001

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
    if(d < -PRECISION)
    {
        return 0;
    }
    if(abs(d) < PRECISION)
    {
        return 1;
    }
    if(d > PRECISION)
    {
        return 2;
    }
}

/*!
\brief Находит корень линейного уравнения от переданных коэффициентов
\param b,с коэффициенты
\return корень
*/
float schet_linear(float b, float c)
{
    if(abs(c) < PRECISION)
    {
        return float(0);
    }
    else
    {
        return -c / b;
    }
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
    float d = discr(a, b, c);
    *x1 = (-sqrt(d) - b) / (2 * a);
    *x2 = (sqrt(d) - b) / (2 * a);
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
    if(abs(a) < PRECISION && abs(b) < PRECISION && abs(c) < PRECISION)
    {
        return 8;
    }
    if(abs(a) < PRECISION && abs(b) < PRECISION)
    {
        return 0;
    }
    if(abs(a) < PRECISION)
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
    float x1, x2;
    float data[k][3]= {{1, 4,-3}, {1, 0, -4}, {0,0,0}, {0,4,5}, {0, 0, 5}, {2, 3, 7}, {15246, 120536, -645721}, {0, 1154526, -1125452}, {1, -2068, 1069156}};
    char data_check[k][50] = {"2:-4.6458 0.6458", "2:-2.0000 2.0000", "8:", "1:-1.2500", "0:", "0:", "2:-11.5675 3.6614", "1:0.9748", "1:1034.0000"};
    for(int i = 0; i < k; i++)
    {
        char str[50];
        int number_of_roots = kvadratka(data[i][0], data[i][1], data[i][2], &x1, &x2);
        switch(number_of_roots)
        {
        case 0:
            sprintf(str, "0:");
            break;
        case 1:
            sprintf(str, "1:%.4f", x1);
            break;
        case 2:
            sprintf(str, "2:%.4f %.4f", x1, x2);
            break;
        case 8:
            sprintf(str, "8:");
            break;
        }
        if(strcmp(data_check[i], str) == 0)
        {
            printf("test %i OK\n", i + 1);
        }
        else
        {
            printf("test %i FAILED\n", i + 1);
            printf("right output: %s\n", data_check[i]);
            printf("program output: %s\n", str);
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
    }
    else
    {
        puts("type a b c");
        assert(scanf("%f %f %f", &a, &b, &c) == 3);
        int number_of_roots = kvadratka(a, b, c, &x1, &x2);
        if(number_of_roots != 8)
        {
            printf("number of roots: %d\n", number_of_roots);
            if(number_of_roots == 1)
            {
                printf("root: %.4f\n", x1);
            }
            if(number_of_roots == 2)
            {
                printf("roots: %.4f %.4f\n", x1, x2);
            }
        }
        else
        {
            puts("roots belongs to R");
        }
        return 0;
    }
}
