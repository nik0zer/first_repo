#include <stdio.h>
#include <math.h>
#include <assert.h>

#define TEST false
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
    *x1 = (sqrt(d) - b) / (2 * a);
    *x2 = (-sqrt(d) - b) / (2 * a);
}

void kvadratka(float a, float b, float c)
{
    float x1 = 0, x2 = 0;
    if(a == 0 && b == 0 && c==0)
    {
        puts("roots belongs to R");
    }
    else
    {
        if(a == 0 && b == 0)
        {
            puts("no solutions");
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

int main()
{
    float a = 0, b, c;
    if(TEST)
    {

    }
    else
    {
        puts("type a b c");
        scanf("%f %f %f", &a, &b, &c);
        kvadratka(a, b, c);
        return 0;
    }
}
