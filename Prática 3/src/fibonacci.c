#include "./../include/fibonacci.h"

unsigned long long int fibonacciRecursivo(unsigned long long int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}

unsigned long long int fibonacciRecursivoComSeno(unsigned long long int n)
{

    double seno;
    for (double j = 0; j < 100000; j++)
    {
        seno = sin(j);
    }

    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}

unsigned long long int fibonacciIterativo(unsigned long long int n)
{
    unsigned long long int f1 = 0, f2 = 1, fi;

    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    for (unsigned long long int i = 2; i <= n; i++)
    {
        fi = f1 + f2;
        f1 = f2;
        f2 = fi;
    }
    return fi;
}