# kvadratka - код для решения квадратного уравнения 
В данном репозитории представлен код, решающий квадратное уравнение. Подобная задача была рассмотрена и реализована в рамках летней школы по промышленному программированию для абитурентов МФТИ. Ниже будет кратко рассказано об основных частях программы.
____
## main.cpp
main.cpp - основной файл, содержащий фукцию main, в которой реализован ввод коэффициентов и вывод итоговыъ значаний, а также при `#define TEST true` запускается тестирующая функция:
```cpp
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
    if(errno != 0)
    {
        printf("ERROR: %d\n", errno);
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
```
также файл содержит фукцию test, в которой хранится массив структур с данными для тестирования и верными ответами:
```cpp
test_data test_data_array[NUMBER_OF_TESTS] =
    {
        {{    1,                  4,                   -3},    {     TWO_ROOTS,    -4.6458,    0.6458,         NO_ERRORS},    &x1,    &x2},
        {{    1,                  0,                   -4},    {     TWO_ROOTS,    -2.0000,    2.0000,         NO_ERRORS},    &x1,    &x2},
        {{    0,                  0,                    0},    {INFINITE_ROOTS,          0,         0,         NO_ERRORS},    &x1,    &x2},
        {{    0,                  4,                    5},    {      ONE_ROOT,    -1.2500,         0,         NO_ERRORS},    &x1,    &x2},
        {{    0,                  0,                    5},    {       NO_ROOT,          0,         0,         NO_ERRORS},    &x1,    &x2},
        {{    2,                  3,                    7},    {       NO_ROOT,          0,         0,         NO_ERRORS},    &x1,    &x2},
        {{15246,             120536,              -645721},    {     TWO_ROOTS,   -11.5675,    3.6614,         NO_ERRORS},    &x1,    &x2},
        {{    0,            1154526,             -1125452},    {      ONE_ROOT,     0.9748,         0,         NO_ERRORS},    &x1,    &x2},
        {{    1,              -2068,              1069156},    {      ONE_ROOT,  1034.0000, 1034.0000,         NO_ERRORS},    &x1,    &x2},
        {{    1,  3.4*pow(10.0, 20),              1231031},    {   ERROR_OCCUR,          0,         0, VARIABLE_OVERFLOW},    &x1,    &x2},
        {{    1,                 10,   -3.4*pow(10.0, 38)},    {   ERROR_OCCUR,          0,         0, VARIABLE_OVERFLOW},    &x1,    &x2},
        {{    0,                  0,                    0},    {   ERROR_OCCUR,          0,         0,      NULL_POINTER},   NULL,    &x2},
        {{    0,                  0,                    0},    {   ERROR_OCCUR,          0,         0,      NULL_POINTER},    &x1,   NULL},
        {{    0,                  0,                    0},    {   ERROR_OCCUR,          0,         0,    EQUAL_POINTERS},    &x1,    &x1},
        {{  NAN,                  0,                    0},    {   ERROR_OCCUR,          0,         0,         NAN_INPUT},    &x1,    &x2},
        {{    0,                  0,                  NAN},    {   ERROR_OCCUR,          0,         0,         NAN_INPUT},    &x1,    &x2},
    };
```
и сам механизм тестирования, в котором запускается функция `kvadratka` от данных из `test_data_array`, а затем вывод сравнивается с ответами из `test_data_array` и в консоль выводится информация о прохождении теста:
```cpp
for(int i = 0; i < NUMBER_OF_TESTS; i++)
    {
        int number_of_roots = kvadratka(test_data_array[i].data[0],
                                        test_data_array[i].data[1],
                                        test_data_array[i].data[2],
                                        test_data_array[i].x1,
                                        test_data_array[i].x2);
        if(number_of_roots == int(test_data_array[i].data_check[0]) && number_of_roots == 3
           && !floatcmp(float(errno), test_data_array[i].data_check[3]))
        {
            printf("test %i OK\n", i + 1);
            printf("ERROR %d\n", errno);
        }
        else
        {
            if(number_of_roots == int(test_data_array[i].data_check[0])
               && !floatcmp(x1, test_data_array[i].data_check[1])
               && !floatcmp(x2, test_data_array[i].data_check[2])
               && !floatcmp(float(errno), test_data_array[i].data_check[3]))
                printf("test %i OK\n", i + 1);
            else
            {
                printf("test %i FAILED\n", i + 1);
                printf("right output: %i %.4f %.4f\n", int(test_data_array[i].data_check[0]),
                       test_data_array[i].data_check[1],
                       test_data_array[i].data_check[2]);
                printf("program output: %i %.4f %.4f\n", number_of_roots, x1, x2);
            }
        }
    }
```
## solver.h
solver.h - файл, который содержит заголовки фукций из solver.cpp
## solver.cpp
solver.cpp - файл с функциями ответственными за само решение квадратного уравнения
### floatcmp
функция сравнения двух float, выводит 0 при равенстве, 1 если больше первое число, -1 если второе:
```cpp
int floatcmp(float x1, float x2)
{
    if((x1 - x2) > PRECISION)
        return 1;
    if((x1 - x2) < -PRECISION)
        return -1;
    return 0;
}
```
### schet_linear
решает линейное уравнение от 2 коэффициентов, возвращает корень уравнения:
```cpp
float schet_linear(float b, float c)
{
    if(floatcmp(c, 0) == 0)
        return float(0);
    else
        return -c / b;
}
```
### schet_kvadr
Находит корни квадратного уравнения от переданных коэффициентов, выдает их в переданные по указателям переменные, возвращает количество корней уравнения, возвращает 3 в случае ошибки и 8 в случае бесконечного количества корней:
```cpp
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
```
### kvadratka
функция решающая уравнение от трех коэффициентов разбивая его на различные случаи в зависимости от входных данных квадратное, линейное и т.д и затем вызывая разные функции в зависимости от вида уравнения(`schet_kvadr`, `schet_linear`), выдает корни в переданные по указателям переменные, возвращает количество корней уравнения, возвращает 3 в случае ошибки и 8 в случае бесконечного количества корней:
```cpp
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
```
