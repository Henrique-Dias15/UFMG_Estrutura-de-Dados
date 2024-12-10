#ifndef ORDENADOR_HPP
#define ORDENADOR_HPP

#include "agenda.hpp"
#include "memlog.hpp"
#include <functional>

class Ordenador
{
public:
    static int *ordenar(Agenda &agenda, const std::string &criterio, const std::string &metodo);

private:
    static int *criarIndice(int quantidade);
    static std::function<bool(const Contato &, const Contato &)> selecionarComparator(const std::string &criterio);
    static void quickSort(int indices[], int l, int r, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator);
    static int partition(int indices[], int l, int r, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator);
    static void heapSort(int indices[], int n, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator);
    static void heapify(int indices[], int n, int i, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator);
    static void mergeSort(int indices[], int l, int r, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator);
    static void merge(int indices[], int l, int m, int r, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator);
    static void imprimirOrdenado(const Contato *contatos, const int *indices, int quantidade);
};

#endif // !ORDENADOR_HPP