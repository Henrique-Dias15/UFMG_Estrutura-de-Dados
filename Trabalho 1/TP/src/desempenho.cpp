#include "../include/desempenho.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>

Desempenho::Desempenho(int capacidade)
    : maxResultados(capacidade), resultadoAtual(0)
{
    resultados = new Resultado[maxResultados];
}

Desempenho::~Desempenho()
{
    delete[] resultados;
}

void Desempenho::iniciarMedicao()
{
    inicio = std::chrono::high_resolution_clock::now();
}

void Desempenho::finalizarMedicao(const std::string &criterio, const std::string &metodo, int tamanho, int payload)
{
    auto fim = std::chrono::high_resolution_clock::now();
    long long duracao = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio).count();

    // Armazenar o resultado
    if (resultadoAtual < maxResultados)
    {
        resultados[resultadoAtual++] = {criterio, metodo, tamanho, payload, duracao};
    }
    else
    {
        std::cerr << "Erro: Número de medições excedeu a capacidade do Desempenho.\n";
    }
}

void Desempenho::imprimirResumo() const
{
    std::cout << std::setw(10) << "Tamanho (r)"
              << std::setw(15) << "Payload (p)"
              << std::setw(10) << "Criterio"
              << std::setw(10) << "Metodo"
              << std::setw(20) << "Tempo(ns)\n";

    for (int i = 0; i < resultadoAtual; ++i)
    {
        const auto &r = resultados[i];
        std::cout << std::setw(10) << r.tamanho
                  << std::setw(15) << r.payload
                  << std::setw(10) << r.criterio
                  << std::setw(10) << r.metodo
                  << std::setw(20) << r.tempoExecucaoNs
                  << '\n';
    }
}

void Desempenho::salvarEmCSV() const
{

    std::string nomeArquivo = "../Resultados/Tempos/tempos.xcsv";

    std::ofstream arquivo(nomeArquivo, std::ios::app);
    if (!arquivo)
    {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << '\n';
        return;
    }

    // Escrever o cabeçalho se o arquivo estiver vazio
    if (arquivo.tellp() == 0)
    {
        arquivo << "Tamanho (r),Payload (p),Criterio,Metodo,Tempo(ns)\n";
    }

    // Escrever os dados
    for (int i = 0; i < resultadoAtual; ++i)
    {
        const auto &r = resultados[i];
        arquivo << r.tamanho << ',' << r.payload << ',' << r.criterio << ',' << r.metodo << ',' << r.tempoExecucaoNs << '\n';
    }

    // Fechar o arquivo
    arquivo.close();
    std::cout << "Desempenho salvo em: " << nomeArquivo << '\n';
}
