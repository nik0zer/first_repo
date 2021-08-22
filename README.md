# kvadratka - код для решения квадратного уравнения 
____
## main.cpp
main.cpp - основной файл, содержащий фукцию main, в которой реализован ввод коэффициентов и вывод итоговыъ значаний, а также при `#define TEST true` запускается тестирующая функция:
```с++
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
