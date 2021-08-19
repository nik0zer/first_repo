#include <stdio.h>
#include <math.h>

int check(float a, float b, float c)
{
    float d = (b * b) - (4 * a * c);
    if(d < 0)
    {
        return 0;
    }
    if(d == 0)
    {
        return 1;
    }
    if(d > 0)
    {
        return 2;
    }
}

void schet(float a, float b, float c, float* x1, float* x2)
{
    float d = b * b - 4 * a * c;
    *x1 = (sqrt(d) - b) / (2 * a);
    *x2 = (-sqrt(d) - b) / (2 * a);
}

int main()
{
    float a = 0, b, c;
    float x1, x2;
    while(a == 0)
    {
        puts("type a b c");
        scanf("%f %f %f", &a, &b, &c);
        if(a == 0)
        {
            puts("a cannot be equal 0");
        }
        else
        {
            printf("number of roots: %d\n", check(a, b, c));
            switch(check(a, b, c))
            {
            case 0:
                break;
            case 1:
                schet(a, b, c, &x1, &x2);
                printf("root: %.4f\n", x1);
                break;
            case 2:
                schet(a, b, c, &x1, &x2);
                printf("roots: %.4f %.4f\n", x1, x2);
            }
        }
    }
    return 0;
}
