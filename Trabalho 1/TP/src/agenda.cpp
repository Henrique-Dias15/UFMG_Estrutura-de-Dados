#include "../include/agenda.hpp"

void Agenda::carregarCSV(const std::string &nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        std::exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; ++i)
    {
        std::getline(arquivo, cabecalho[i]);
    }

    std::string linha;
    if (std::getline(arquivo, linha))
    {
        std::istringstream iss(linha);
        if (!(iss >> quantidade))
        {
            std::cerr << "Erro: a linha não contém um inteiro válido." << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    contatos = new Contato[quantidade];
    int index = 0;
    while (std::getline(arquivo, linha) && index < quantidade)
    {

        size_t pos = 0;
        size_t colIndex = 0;

        while ((pos = linha.find(',')) != std::string::npos)
        {
            if (colIndex == 0)
                contatos[index].setNome(linha.substr(0, pos));
            else if (colIndex == 1)
                contatos[index].setId(linha.substr(0, pos));
            else if (colIndex == 2)
                contatos[index].setEndereco(linha.substr(0, pos));
            linha.erase(0, pos + 1);
            ++colIndex;
        }
        contatos[index].setPayload(linha);
        ++index;
    }
}

void Agenda::imprimirCabecalho() const
{
    for (const auto &linha : cabecalho)
    {
        std::cout << linha << std::endl;
    }
    std::cout << quantidade << std::endl;
}