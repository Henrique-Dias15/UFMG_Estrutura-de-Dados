#include "../include/arquivo.hpp"

std::string Arquivo::gerarNomeArquivo(int r, int p)
{
    return "./carga/cad.r" + std::to_string(r) + ".p" + std::to_string(p) + ".xcsv";
}

void Arquivo::processarArquivo(int r, int p, Desempenho &desempenho,
                               const std::string metodos[], int numMetodos,
                               const std::string criterios[], int numCriterios)
{
    std::string arquivo = gerarNomeArquivo(r, p);

    Agenda agenda;
    agenda.carregarCSV(arquivo);

    for (int m = 0; m < numMetodos; ++m)
    {
        for (int c = 0; c < numCriterios; ++c)
        {
            desempenho.iniciarMedicao();

            int *indices = Ordenador::ordenar(agenda, criterios[c], metodos[m]);

            if (indices)
            {
                desempenho.finalizarMedicao(criterios[c], metodos[m], r, p);
                delete[] indices; // Liberar memória dos índices
            }
        }
    }
}

void Arquivo::processarCombinacoes(Agenda &agenda, Desempenho &desempenho, int r, int p,
                                   const std::string metodos[], int numMetodos,
                                   const std::string criterios[], int numCriterios)
{
    for (int m = 0; m < numMetodos; ++m)
    {

        iniciaMemLog((std::string("../Resultados/Memoria/") + metodos[m]).c_str());
        ativaMemLog();

        for (int c = 0; c < numCriterios; ++c)
        {
            desempenho.iniciarMedicao();

            int *indices = Ordenador::ordenar(agenda, criterios[c], metodos[m]);

            if (indices)
            {
                desempenho.finalizarMedicao(criterios[c], metodos[m], r, p);
                delete[] indices; // Liberar memória dos índices
            }
            if (c == 0)
            {
                desativaMemLog();
                finalizaMemLog();
            }
        }
    }
}