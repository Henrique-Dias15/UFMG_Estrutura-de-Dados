#ifndef AGENDA_HPP
#define AGENDA_HPP

#include "contato.hpp"
#include "memlog.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Agenda
{
private:
    Contato *contatos = nullptr;
    int quantidade = 0;
    std::string cabecalho[5];

public:
    ~Agenda() { delete[] contatos; }

    int getQuantidade() const { return quantidade; }
    Contato *getContatos() const { return contatos; }

    void carregarCSV(const std::string &nomeArquivo);
    void imprimirCabecalho() const;
};

#endif // !AGENDA_HPP
