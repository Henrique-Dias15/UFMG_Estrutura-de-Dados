#ifndef DESEMPENHO_H
#define DESEMPENHO_H

#include <string>
#include <chrono>
#include <iostream>

class Desempenho
{
private:
    struct Resultado
    {
        std::string criterio;
        std::string metodo;
        int tamanho;
        int payload;
        long long tempoExecucaoNs;
    };

    Resultado *resultados;
    int maxResultados;
    int resultadoAtual;
    std::chrono::time_point<std::chrono::high_resolution_clock> inicio;

public:
    Desempenho(int capacidade);
    ~Desempenho();

    void iniciarMedicao();
    void finalizarMedicao(const std::string &criterio, const std::string &metodo, int tamanho, int payload);
    void imprimirResumo() const;
    void salvarEmCSV() const;
};

#endif
