#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <math.h>
#include "./../include/fatorial.h"
#include "./../include/fibonacci.h"

int main(int argc, char *argv[])
{

    struct timespec start, end;
    struct rusage usage_start, usage_end;

    // Verifica se o número de argumentos é adequado
    if (argc < 3)
    {
        printf("Uso: %s <operação> <número>\n", argv[0]);
        printf("Operações disponíveis:\n");
        printf("  fi <n>  -> Fatorial Iterativo\n");
        printf("  fr <n>  -> Fatorial Recursivo\n");
        printf("  frs <n>  -> Fatorial Recursivo Com Seno\n");
        printf("  fib <n> -> Fibonacci Iterativo\n");
        printf("  fbr <n> -> Fibonacci Recursivo\n");
        printf("  fbrs <n> -> Fibonacci Recursivo Com Seno\n");
        return 1;
    }

    // Converte o segundo argumento para um número inteiro
    int n = atoi(argv[2]);

    // Define o nome do arquivo CSV de acordo com a operação escolhida
    char filename[50];
    if (strcmp(argv[1], "fi") == 0)
    {
        strcpy(filename, "Fatorial Iterativo.csv");
    }
    else if (strcmp(argv[1], "fr") == 0)
    {
        strcpy(filename, "Fatorial Recursivo.csv");
    }
    else if (strcmp(argv[1], "frs") == 0)
    {
        strcpy(filename, "Fatorial Recursivo Com Seno.csv");
    }
    else if (strcmp(argv[1], "fib") == 0)
    {
        strcpy(filename, "Fibonacci Iterativo.csv");
    }
    else if (strcmp(argv[1], "fbr") == 0)
    {
        strcpy(filename, "Fibonacci Recursivo.csv");
    }
    else if (strcmp(argv[1], "fbrs") == 0)
    {
        strcpy(filename, "Fibonacci Recursivo Com Seno.csv");
    }
    else
    {
        printf("Operação inválida. Use uma das seguintes:\n");
        printf("  fi <n>  -> Fatorial Iterativo\n");
        printf("  fr <n>  -> Fatorial Recursivo\n");
        printf("  frs <n>  -> Fatorial Recursivo Com Seno\n");
        printf("  fib <n> -> Fibonacci Iterativo\n");
        printf("  fbr <n> -> Fibonacci Recursivo\n");
        printf("  fbrs <n> -> Fibonacci Recursivo Com Seno\n");
        return 1;
    }

    // Abrir o arquivo CSV para escrita
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo CSV!\n");
        return 1;
    }

    // Marcar o tempo de início
    clock_gettime(CLOCK_MONOTONIC, &start);
    getrusage(RUSAGE_SELF, &usage_start);

    // Executa a operação
    if (strcmp(argv[1], "fi") == 0)
    {
        fatorialIterativo(n);
    }
    else if (strcmp(argv[1], "fr") == 0)
    {
        fatorialRecursivo(n);
    }
    else if (strcmp(argv[1], "frs") == 0)
    {
        fatorialRecursivoComSeno(n);
    }
    else if (strcmp(argv[1], "fib") == 0)
    {
        fibonacciIterativo(n);
    }
    else if (strcmp(argv[1], "fbr") == 0)
    {
        fibonacciRecursivo(n);
    }
    else if (strcmp(argv[1], "fbrs") == 0)
    {
        fibonacciRecursivoComSeno(n);
    }

    // Marcar o tempo de fim
    clock_gettime(CLOCK_MONOTONIC, &end);
    getrusage(RUSAGE_SELF, &usage_end);

    // Cálculo do tempo de relógio em microsegundos
    double tempo_relogio = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;

    // Cálculo do tempo de CPU no modo usuário em microsegundos
    double tempo_usuario = (usage_end.ru_utime.tv_sec - usage_start.ru_utime.tv_sec) * 1e6 +
                           (usage_end.ru_utime.tv_usec - usage_start.ru_utime.tv_usec);

    // Cálculo do tempo de CPU no modo sistema em microsegundos
    double tempo_sistema = (usage_end.ru_stime.tv_sec - usage_start.ru_stime.tv_sec) * 1e6 +
                           (usage_end.ru_stime.tv_usec - usage_start.ru_stime.tv_usec);

    // Escrever os tempos no arquivo CSV com precisão de microsegundos
    fprintf(file, "%d,%.0f,%.0f,%.0f\n", n, tempo_relogio, tempo_usuario, tempo_sistema);

    // Fechar o arquivo
    fclose(file);

    return 0;
}
