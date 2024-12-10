#include "./../include/fatorial.h"

unsigned long long int fatorialRecursivo(unsigned long long int n)
{
    if (n <= 1)
    {
        return 1;
    }
    return n * fatorialRecursivo(n - 1);
}

unsigned long long int fatorialRecursivoComSeno(unsigned long long int n)
{
    double seno;
    for (double j = 0; j < 100000; j++)
    {
        seno = sin(j);
    }

    if (n <= 1)
    {
        return 1;
    }
    return n * fatorialRecursivo(n - 1);
}

unsigned long long int fatorialIterativo(unsigned long long int n)
{
    unsigned long long int res = 1;
    for (unsigned long long int i = n; i >= 1; i--)
    {
        res *= i;
    }
    return res;
}