#include <iostream>
#include <string>
#include "../include/arquivo.hpp"
#include "../include/desempenho.hpp"
#include "../include/memlog.hpp"

int main()
{
    const int valoresR[] = {1000, 5000};
    const int valoresP[] = {1000, 5000};
    const int numR = sizeof(valoresR) / sizeof(valoresR[0]);
    const int numP = sizeof(valoresP) / sizeof(valoresP[0]);

    const std::string metodos[] = {"quick", "heap", "merge"};
    const std::string criterios[] = {"nome", "id", "endereco"};
    const int numMetodos = sizeof(metodos) / sizeof(metodos[0]);
    const int numCriterios = sizeof(criterios) / sizeof(criterios[0]);

    const int totalMedições = numR * numP * numMetodos * numCriterios;

    Desempenho desempenho(totalMedições);
    Arquivo arquivo;

    for (int i = 0; i < numR; ++i)
    {
        for (int j = 0; j < numP; ++j)
        {
            Agenda agenda;

            agenda.carregarCSV(Arquivo::gerarNomeArquivo(valoresR[i], valoresP[j]));

            arquivo.processarCombinacoes(agenda, desempenho, valoresP[i], valoresR[j], metodos, numMetodos, criterios, numCriterios);
        }
    }

    desempenho.salvarEmCSV();

    return 0;
}
