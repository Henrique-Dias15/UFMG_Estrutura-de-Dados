#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <string>
#include <iostream>
#include "agenda.hpp"
#include "desempenho.hpp"
#include "ordenador.hpp"
#include "memlog.hpp"

class Arquivo
{
public:
    static std::string gerarNomeArquivo(int r, int p);

    static void processarArquivo(int r, int p, Desempenho &desempenho,
                                 const std::string metodos[], int numMetodos,
                                 const std::string criterios[], int numCriterios);

    void processarCombinacoes(Agenda &agenda, Desempenho &desempenho, int r, int p,
                              const std::string metodos[], int numMetodos,
                              const std::string criterios[], int numCriterios);
};

#endif
