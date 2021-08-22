#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>


#define TEST true
#define NUMBER_OF_TESTS 16
#define PRECISION 0.0001

enum rootnum {NO_ROOT, ONE_ROOT, TWO_ROOTS, ERROR_OCCUR, INFINITE_ROOTS = 8};
enum errors {NO_ERRORS, VARIABLE_OVERFLOW, NULL_POINTER, EQUAL_POINTERS, NAN_INPUT};
int Errno = 0;

struct test_data
{
    float data[3];
    float data_check[3];
    float* x1;
    float* x2;
};

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
int schet_kvadr(float a, float b, float c, float* x1, float* x2)
{
    if((abs(FLT_MAX / b) < abs(b)) || (abs((FLT_MAX / 4) / a) < abs(c)))
    {
        Errno = NULL_POINTER;
        return ERROR_OCCUR;
    }
    float d = (b * b) - (4 * a * c);
    if(floatcmp(d, 0) == -1)
    {
        *x1 = 0;
        *x2 = 0;
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
        Errno = NULL_POINTER;
        return ERROR_OCCUR;
    }
    if(x2 == x1)
    {
        Errno = EQUAL_POINTERS;
        return ERROR_OCCUR;
    }
    if(isnan(a) || isnan(b) || isnan(c))
    {
        Errno = NAN_INPUT;
        return ERROR_OCCUR;
    }
    *x1 = 0;
    *x2 = 0;
    if(floatcmp(a, 0) == 0 && floatcmp(b, 0) == 0)
        return (floatcmp(c, 0) == 0) ? INFINITE_ROOTS : NO_ROOT;
    if(floatcmp(a, 0) == 0)
    {
        *x1 = schet_linear(b, c);
        return ONE_ROOT;
    }
    return schet_kvadr(a, b, c, x1, x2);
}

/*!
\brief тестирующая функция
\detail тестирующая функция прогоняет значения из data через kvadratka,
сравнивает с эталонными из data_check и пишет результаты тестов в консоль
*/
void test()
{
    float x1 = 0, x2 = 0;
    test_data test_data_array[NUMBER_OF_TESTS] =
    {
        {{    1,                  4,                   -3},    {2,    -4.6458,    0.6458},    &x1,    &x2},
        {{    1,                  0,                   -4},    {2,    -2.0000,    2.0000},    &x1,    &x2},
        {{    0,                  0,                    0},    {8,          0,         0},    &x1,    &x2},
        {{    0,                  4,                    5},    {1,    -1.2500,         0},    &x1,    &x2},
        {{    0,                  0,                    5},    {0,          0,         0},    &x1,    &x2},
        {{    2,                  3,                    7},    {0,          0,         0},    &x1,    &x2},
        {{15246,             120536,              -645721},    {2,   -11.5675,    3.6614},    &x1,    &x2},
        {{    0,            1154526,             -1125452},    {1,     0.9748,         0},    &x1,    &x2},
        {{    1,              -2068,              1069156},    {1,  1034.0000, 1034.0000},    &x1,    &x2},
        {{    1,  3.4*pow(10.0, 20),              1231031},    {3,          0,         0},    &x1,    &x2},
        {{    1,                 10,   -3.4*pow(10.0, 38)},    {3,          0,         0},    &x1,    &x2},
        {{    0,                  0,                    0},    {3,          0,         0},   NULL,    &x2},
        {{    0,                  0,                    0},    {3,          0,         0},    &x1,   NULL},
        {{    0,                  0,                    0},    {3,          0,         0},    &x1,    &x1},
        {{  NAN,                  0,                    0},    {3,          0,         0},    &x1,    &x2},
        {{    0,                  0,                  NAN},    {3,          0,         0},    &x1,    &x2},
    };
    for(int i = 0; i < NUMBER_OF_TESTS; i++)
    {
        int number_of_roots = kvadratka(test_data_array[i].data[0], test_data_array[i].data[1], test_data_array[i].data[2], test_data_array[i].x1, test_data_array[i].x2);
        if((number_of_roots == int(test_data_array[i].data_check[0]) && number_of_roots == 3))
        {
            printf("test %i OK\n", i + 1);
            printf("ERROR %d\n", Errno);
        }
        else
        {
            if(number_of_roots == int(test_data_array[i].data_check[0]) && floatcmp(x1, test_data_array[i].data_check[1]) == 0 && floatcmp(x2, test_data_array[i].data_check[2]) == 0)
                printf("test %i OK\n", i + 1);
            else
            {
                printf("test %i FAILED\n", i + 1);
                printf("right output: %i %.4f %.4f\n", int(test_data_array[i].data_check[0]), test_data_array[i].data_check[1], test_data_array[i].data_check[2]);
                printf("program output: %i %.4f %.4f\n", number_of_roots, x1, x2);
            }
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
    float a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    if(TEST)
    {
        test();
        return 0;
    }
    puts("type a b c");
    if(scanf("%f %f %f", &a, &b, &c) != 3)
    {
        puts("invalid input");
        return 0;
    }
    int number_of_roots = kvadratka(a, b, c, &x1, &x2);
    if(Errno != 0)
    {
        printf("ERROR: %d\n", Errno);
        return Errno;
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


