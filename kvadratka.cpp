#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define TEST true
#define D 0.001

float discr(float a, float b, float c)
{
    return (b * b) - (4 * a * c);
}

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

float schet_linear(float b, float c)
{
    if(c == 0)
    {
        return float(0);
    }
    else
    {
        return -c / b;
    }
}

void schet_kvadr(float a, float b, float c, float* x1, float* x2)
{
    assert(*x1 == NULL);
    assert(*x2 == NULL);
    float d = discr(a, b, c);
    *x1 = (-sqrt(d) - b) / (2 * a);
    *x2 = (sqrt(d) - b) / (2 * a);
}

void kvadratka(float a, float b, float c, char str[])
{

    float x1 = 0, x2 = 0;
    if(TEST)
    {
        if(a == 0 && b == 0 && c==0)
        {
            sprintf(str, "8:");
        }
        else
        {
            if(a == 0 && b == 0)
            {
                sprintf(str, "0:");
            }
            else
            {
                if(a == 0)
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
        if(a == 0 && b == 0 && c==0)
        {
            puts("roots belongs to R");
        }
        else
        {
            if(a == 0 && b == 0)
            {
                puts("number of roots: 0");
            }
            else
            {
                if(a == 0)
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

void test()
{
    float a = 0, b, c;
    float data[3][3]={{1, 4,-3},{1, 0, -4},{0,0,0}};
    char data_check[3][50] = {"2:-4.6458 0.6458","2:-2.0000 2.0000","8:"};
    for(int i = 0; i < 3; i++)
    {
        char str[50];
        kvadratka(data[i][0], data[i][1], data[i][2], str);
        if(strcmp(data_check[i], str) == 0)
        {
            printf("test %i OK\n", i);
        }
        else
        {
            printf("test %i FAILED\n", i);
            printf("right output: %s\n", data_check[i]);
            printf("program output: %s\n", str);
        }
    }
}

int main()
{
    float a = 0, b, c;
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
