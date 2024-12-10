#include "../include/ordenador.hpp"

int *Ordenador::ordenar(Agenda &agenda, const std::string &criterio, const std::string &metodo)
{
    int quantidade = agenda.getQuantidade();
    if (quantidade == 0)
    {
        std::cerr << "Erro: Agenda está vazia!" << std::endl;
        return nullptr;
    }

    // Fase 0: Alocação de recursos
    defineFaseMemLog(0); // Início da alocação
    int *indices = criarIndice(quantidade);
    escreveMemLog(reinterpret_cast<long int>(indices), quantidade * sizeof(int), 1);

    auto comparator = Ordenador::selecionarComparator(criterio);

    if (!comparator)
    {
        std::cerr << "Erro: Critério de ordenação inválido!" << std::endl;
        delete[] indices;
        return nullptr;
    }

    // Fase 1: Execução da operação principal
    defineFaseMemLog(1); // Operação principal
    if (metodo == "quick")
        quickSort(indices, 0, quantidade - 1, agenda.getContatos(), comparator);
    else if (metodo == "heap")
        heapSort(indices, quantidade, agenda.getContatos(), comparator);
    else if (metodo == "merge")
        mergeSort(indices, 0, quantidade - 1, agenda.getContatos(), comparator);
    else
    {
        std::cerr << "Erro: Método de ordenação inválido!" << std::endl;
        delete[] indices;
        return nullptr;
    }

    // Fase 2: Finalização (liberação de recursos ou operações finais)
    defineFaseMemLog(2); // Finalização
    return indices;
}

int *Ordenador::criarIndice(int quantidade)
{
    defineFaseMemLog(0); // Alocação de índices
    int *indices = new int[quantidade];
    escreveMemLog(reinterpret_cast<long int>(indices), quantidade * sizeof(int), 0);
    for (int i = 0; i < quantidade; ++i)
        indices[i] = i;
    return indices;
}

std::function<bool(const Contato &, const Contato &)> Ordenador::selecionarComparator(const std::string &criterio)
{
    defineFaseMemLog(1); // Definir comparador (parte da operação principal)
    if (criterio == "nome")
        return [](const Contato &a, const Contato &b)
        { return a.getNome() < b.getNome(); };
    if (criterio == "id")
        return [](const Contato &a, const Contato &b)
        { return a.getId() < b.getId(); };
    if (criterio == "endereco")
        return [](const Contato &a, const Contato &b)
        { return a.getEndereco() < b.getEndereco(); };
    return nullptr;
}

void Ordenador::quickSort(int indices[], int low, int high, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator)
{
    if (low < high)
    {
        int pi = partition(indices, low, high, contatos, comparator);
        leMemLog(reinterpret_cast<long int>(&indices[pi]), sizeof(int), 1);
        quickSort(indices, low, pi - 1, contatos, comparator);
        quickSort(indices, pi + 1, high, contatos, comparator);
    }
}

int Ordenador::partition(int indices[], int low, int high, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator)
{
    defineFaseMemLog(1); // Partição ocorre na fase de execução
    int pivotIndex = indices[high];
    leMemLog(reinterpret_cast<long int>(&indices[high]), sizeof(int), 1);

    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        leMemLog(reinterpret_cast<long int>(&indices[j]), sizeof(int), 1);

        if (comparator(contatos[indices[j]], contatos[pivotIndex]))
        {
            escreveMemLog(reinterpret_cast<long int>(&indices[i + 1]), sizeof(int), 2);
            escreveMemLog(reinterpret_cast<long int>(&indices[j]), sizeof(int), 2);
            std::swap(indices[++i], indices[j]);
        }
    }
    escreveMemLog(reinterpret_cast<long int>(&indices[i + 1]), sizeof(int), 2);
    escreveMemLog(reinterpret_cast<long int>(&indices[high]), sizeof(int), 2);
    std::swap(indices[i + 1], indices[high]);
    return i + 1;
}

void Ordenador::heapSort(int indices[], int n, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator)
{
    defineFaseMemLog(1); // Execução do heapSort
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(indices, n, i, contatos, comparator);

    for (int i = n - 1; i > 0; --i)
    {
        escreveMemLog(reinterpret_cast<long int>(&indices[0]), sizeof(int), 2);
        escreveMemLog(reinterpret_cast<long int>(&indices[i]), sizeof(int), 2);
        std::swap(indices[0], indices[i]);
        heapify(indices, i, 0, contatos, comparator);
    }
}

void Ordenador::heapify(int indices[], int n, int i, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator)
{
    defineFaseMemLog(1); // Parte do heapify ocorre durante a execução
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;

    if (left < n)
        leMemLog(reinterpret_cast<long int>(&indices[left]), sizeof(int), 2);

    if (right < n)
        leMemLog(reinterpret_cast<long int>(&indices[right]), sizeof(int), 2);

    if (left < n && comparator(contatos[indices[largest]], contatos[indices[left]]))
        largest = left;

    if (right < n && comparator(contatos[indices[largest]], contatos[indices[right]]))
        largest = right;

    if (largest != i)
    {
        escreveMemLog(reinterpret_cast<long int>(&indices[i]), sizeof(int), 2);
        escreveMemLog(reinterpret_cast<long int>(&indices[largest]), sizeof(int), 2);
        std::swap(indices[i], indices[largest]);
        heapify(indices, n, largest, contatos, comparator);
    }
}

void Ordenador::mergeSort(int indices[], int l, int r, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(indices, l, m, contatos, comparator);
        mergeSort(indices, m + 1, r, contatos, comparator);

        // O merge agora está otimizado para logs
        merge(indices, l, m, r, contatos, comparator);
    }
}

void Ordenador::merge(int indices[], int l, int m, int r, const Contato *contatos, const std::function<bool(const Contato &, const Contato &)> &comparator)
{
    int n1 = m - l + 1, n2 = r - m;

    // Alocação dos arrays temporários
    int *L = new int[n1];
    int *R = new int[n2];

    // Registrar alocação no log
    escreveMemLog(reinterpret_cast<long int>(L), n1 * sizeof(int), 1);
    escreveMemLog(reinterpret_cast<long int>(R), n2 * sizeof(int), 1);

    // Copiar dados para os arrays temporários
    for (int i = 0; i < n1; ++i)
        L[i] = indices[l + i];
    for (int i = 0; i < n2; ++i)
        R[i] = indices[m + 1 + i];

    // Mesclando os arrays temporários de volta ao original
    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        // Registrar leitura somente quando realmente necessário
        leMemLog(reinterpret_cast<long int>(&L[i]), sizeof(int), 2);
        leMemLog(reinterpret_cast<long int>(&R[j]), sizeof(int), 2);

        // Movimentação final gravada no log
        escreveMemLog(reinterpret_cast<long int>(&indices[k]), sizeof(int), 2);

        indices[k++] = comparator(contatos[L[i]], contatos[R[j]]) ? L[i++] : R[j++];
    }

    // Inserir elementos restantes do lado esquerdo (se houver)
    while (i < n1)
    {
        leMemLog(reinterpret_cast<long int>(&L[i]), sizeof(int), 2);
        escreveMemLog(reinterpret_cast<long int>(&indices[k]), sizeof(int), 2);
        indices[k++] = L[i++];
    }

    // Inserir elementos restantes do lado direito (se houver)
    while (j < n2)
    {
        leMemLog(reinterpret_cast<long int>(&R[j]), sizeof(int), 2);
        escreveMemLog(reinterpret_cast<long int>(&indices[k]), sizeof(int), 2);
        indices[k++] = R[j++];
    }

    // Liberação de memória
    delete[] L;
    delete[] R;
}
