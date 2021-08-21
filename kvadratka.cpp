#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define TEST true
#define D 0.001

/*!
Находит дискриминант от переданных коэффициентов
\param a,b,с коэффициенты
\return дискриминант
*/
float discr(float a, float b, float c)
{
    return (b * b) - (4 * a * c);
}

/*!
Находит количество корней квадратного уравнения от переданных коэффициентов
\param a,b,с коэффициенты
\return количество корней
*/
int check(float a, float b, float c)
{
    float d = discr(a, b, c);
    if(d < -D)
    {
        return 0;
    }
    if(abs(d) < D)
    {
        return 1;
    }
    if(d > D)
    {
        return 2;
    }
}

/*!
Находит корень линейного уравнения от переданных коэффициентов
\param b,с коэффициенты
\return корень
*/
float schet_linear(float b, float c)
{
    if(abs(c) < D)
    {
        return float(0);
    }
    else
    {
        return -c / b;
    }
}

/*!
Находит корни квадратного уравнения от переданных коэффициентов
\param a,b,с коэффициенты
\param x1,x2 возвращаемые корни уравнения
*/
void schet_kvadr(float a, float b, float c, float* x1, float* x2)
{
    assert(*x1 == NULL);
    assert(*x2 == NULL);
    float d = discr(a, b, c);
    *x1 = (-sqrt(d) - b) / (2 * a);
    *x2 = (sqrt(d) - b) / (2 * a);
}

/*!
Решает квадратное уравнение от переданных коэффициентов, может работать в двух режимах: в обычном печатает решение уравнения в консоль, в режиме тестов возвращает строку с количеством корней и их значениями
\param a,b,с коэффициенты
\param str возвращаемая в режиме тестов строка
*/
void kvadratka(float a, float b, float c, char str[])
{
    float x1 = 0, x2 = 0;
    if(TEST)
    {
        if(abs(a) < D && abs(b) < D && abs(c) < D)
        {
            sprintf(str, "8:");
        }
        else
        {
            if(abs(a) < D && abs(b) < D)
            {
                sprintf(str, "0:");
            }
            else
            {
                if(abs(a) < D)
                {
                    sprintf(str, "1:%.4f", schet_linear(b, c));
                }
                else
                {
                    switch(check(a, b, c))
                    {
                    case 0:
                        sprintf(str, "0:");
                        break;
                    case 1:
                        schet_kvadr(a, b, c, &x1, &x2);
                        sprintf(str, "%d:%.4f", check(a, b, c), x1);
                        break;
                    case 2:
                        schet_kvadr(a, b, c, &x1, &x2);
                        sprintf(str, "%d:%.4f %.4f", check(a, b, c), x1, x2);
                    }
                }
            }
        }
    }
    else
    {
        if(abs(a) < D && abs(b) < D && abs(c) < D)
        {
            puts("roots belongs to R");
        }
        else
        {
            if(abs(a) < D && abs(b) < D)
            {
                puts("number of roots: 0");
            }
            else
            {
                if(abs(a) < D)
                {
                    puts("number of roots: 1");
                    printf("root: %.4f\n", schet_linear(b, c));
                }
                else
                {
                    printf("number of roots: %d\n", check(a, b, c));
                    switch(check(a, b, c))
                    {
                    case 0:
                        break;
                    case 1:
                        schet_kvadr(a, b, c, &x1, &x2);
                        printf("root: %.4f\n", x1);
                        break;
                    case 2:
                        schet_kvadr(a, b, c, &x1, &x2);
                        printf("roots: %.4f %.4f\n", x1, x2);
                    }
                }
            }
        }
    }
}

/*!
тестирующая функция прогоняет значения из data через kvadratka и сравнивает с эталонными из data_check и пишет результаты тестов в консоль
*/
void test()
{
    int k = 9;
    float data[k][3]= {{1, 4,-3}, {1, 0, -4}, {0,0,0}, {0,4,5}, {0, 0, 5}, {2, 3, 7}, {15246, 120536, -645721}, {0, 1154526, -1125452}, {1, -2068, 1069156}};
    char data_check[k][50] = {"2:-4.6458 0.6458", "2:-2.0000 2.0000", "8:", "1:-1.2500", "0:", "0:", "2:-11.5675 3.6614", "1:0.9748", "1:1034.0000"};
    for(int i = 0; i < k; i++)
    {
        char str[50];
        kvadratka(data[i][0], data[i][1], data[i][2], str);
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
в режиме теста запускает тестирующую функцию, в обычном считывает коэффициенты из консоли и запускает kvadratka
*/
int main()
{
    float a = 0, b = 0, c = 0;
    char str[20];
    if(TEST)
    {
        test();
    }
    else
    {
        puts("type a b c");
        scanf("%f %f %f", &a, &b, &c);
        kvadratka(a, b, c, str);
        return 0;
    }
}
