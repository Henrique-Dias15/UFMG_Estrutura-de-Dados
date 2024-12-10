#include "./../include/sorts.h"

alg_t algvet[] = {
    {ALGINSERTION, "i"},
    {ALGSELECTION, "s"},
    {ALGQSORT, "q"},
    {ALGQSORT3, "q3"},
    {ALGQSORTINS, "qi"},
    {ALGQSORT3INS, "q3i"},
    {ALGSHELLSORT, "h"},
    {ALGRECSEL, "rs"},
    {0, 0}};

int name2num(char *name)
{
  int i = 0;
  while (algvet[i].num)
  {
    if (!strcmp(algvet[i].name, name))
      return algvet[i].num;
    i++;
  }
  return 0;
}

char *num2name(int num)
{
  int i = 0;
  while (algvet[i].num)
  {
    if (algvet[i].num == num)
      return algvet[i].name;
    i++;
  }
  return 0;
}

void resetcounter(sortperf_t *s)
{
  // Descricao: inicializa estrutura
  // Entrada:
  // Saida: s
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void inccmp(sortperf_t *s, int num)
{
  // Descricao: incrementa o numero de comparacoes em num
  // Entrada: s, num
  // Saida: s
  s->cmp += num;
}

void incmove(sortperf_t *s, int num)
{
  // Descricao: incrementa o numero de movimentacoes de dados em num
  // Entrada: s, num
  // Saida: s
  s->move += num;
}

void inccalls(sortperf_t *s, int num)
{
  // Descricao: incrementa o numero de chamadas de função em num
  // Entrada: s, num
  // Saida: s
  s->calls += num;
}

char *printsortperf(sortperf_t *s, char *str, char *pref)
{
  // Descricao: gera string com valores de sortperf
  // Entrada: s, pref
  // Saida: str

  sprintf(str, "%s cmp %d move %d calls %d", pref, s->cmp, s->move, s->calls);
  return str;
}

void initVector(int *vet, int size)
{
  // Descricao: inicializa vet com valores aleatorios
  // Entrada: vet
  // Saida: vet
  int i;
  // inicializa a parte alocada da vetor com valores aleatorios
  for (i = 0; i < size; i++)
  {
    vet[i] = (int)(drand48() * size);
  }
}

void printVector(int *vet, int size)
{
  // Descricao: inicializa vet com valores aleatorios
  // Entrada: vet
  // Saida: vet
  int i;
  for (i = 0; i < size; i++)
  {
    printf("%d ", vet[i]);
  }
  printf("\n");
}

void swap(int *xp, int *yp, sortperf_t *s)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  incmove(s, 3);
}

// shellsort
void shellSort(int *array, int n, sortperf_t *s)
{
  inccalls(s, 1);
  for (int h = n / 2; h > 0; h /= 2)
  {
    for (int i = h; i < n; i += 1)
    {
      int temp = array[i];
      incmove(s, 1);
      int j;
      inccmp(s, 1);
      for (j = i; j >= h && array[j - h] > temp; j -= h)
      {
        array[j] = array[j - h];
        incmove(s, 1);
        inccmp(s, 1);
      }
      array[j] = temp;
      incmove(s, 1);
    }
  }
}

// recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t *s)
{
  // find the minimum element in the unsorted subarray `[i…n-1]`
  // and swap it with `arr[i]`
  int min = l;
  inccalls(s, 1);
  for (int j = l + 1; j <= r; j++)
  {
    // if `arr[j]` is less, then it is the new minimum
    inccmp(s, 1);
    if (arr[j] < arr[min])
    {
      min = j; // update the index of minimum element
    }
  }

  // swap the minimum element in subarray `arr[i…n-1]` with `arr[i]`
  if (min != l)
    swap(&arr[min], &arr[l], s);

  if (l + 1 < r)
  {
    recursiveSelectionSort(arr, l + 1, r, s);
  }
}

// selection sort
void selectionSort(int arr[], int l, int r, sortperf_t *s)
{
  inccalls(s, 1);
  // Loop para percorrer o array de l até r
  for (int i = l; i < r; i++)
  {
    int minIndex = i;

    // Encontra o índice do menor elemento no restante do array
    for (int j = i + 1; j <= r; j++)
    {
      inccmp(s, 1);
      if (arr[j] < arr[minIndex])
      {
        minIndex = j;
      }
    }

    // Troca o elemento atual com o menor elemento encontrado, se necessário
    if (minIndex != i)
    {
      swap(&arr[i], &arr[minIndex], s);
    }
  }
  return;
}

// insertion sort
void insertionSort(int v[], int l, int r, sortperf_t *s)
{
  inccalls(s, 1);
  for (int i = l + 1; i <= r; i++)
  {
    int key = v[i];
    incmove(s, 1);
    int j = i - 1;
    inccmp(s, 1);
    while (j >= 0 && v[j] > key)
    {
      v[j + 1] = v[j];
      incmove(s, 1);
      j--;
      inccmp(s, 1);
    }
    v[j + 1] = key;
    incmove(s, 1);
  }
}

// median of 3 integers
int median(int a, int b, int c)
{
  if ((a <= b) && (b <= c))
    return b; // a b c
  if ((a <= c) && (c <= b))
    return c; // a c b
  if ((b <= a) && (a <= c))
    return a; // b a c
  if ((b <= c) && (c <= a))
    return c; // b c a
  if ((c <= a) && (a <= b))
    return a; // c a b
  return b;   // c b a
}

// Função partition3 usando mediana de três
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s)
{
  int m = median(A[l], A[(l + r) / 2], A[r]);
  *i = l;
  *j = r;
  while (*i <= *j)
  {
    inccmp(s, 1);
    while (A[*i] < m)
    {
      inccmp(s, 1);
      (*i)++;
    }
    while (A[*j] > m)
    {
      inccmp(s, 1);
      (*j)--;
    }
    inccmp(s, 1);
    if (*i <= *j)
    {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }
  }
}

// Função partition padrão
void partition(int *A, int l, int r, int *i, int *j, sortperf_t *s)
{
  int pivot = A[(l + r) / 2];
  *i = l;
  *j = r;
  while (*i <= *j)
  {
    inccmp(s, 1);
    while (A[*i] < pivot)
    {
      inccmp(s, 1);
      (*i)++;
    }
    while (A[*j] > pivot)
    {
      inccmp(s, 1);
      (*j)--;
    }
    inccmp(s, 1);
    if (*i <= *j)
    {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }
  }
}

// Função quickSort padrão
void quickSort(int *A, int l, int r, sortperf_t *s)
{
  if (l < r)
  {
    int i, j;
    partition(A, l, r, &i, &j, s);
    inccalls(s, 2);
    quickSort(A, l, j, s);
    quickSort(A, i, r, s);
  }
}

// Função quickSort usando mediana de três
void quickSort3(int *A, int l, int r, sortperf_t *s)
{
  if (l < r)
  {
    int i, j;
    partition3(A, l, r, &i, &j, s);
    inccalls(s, 2);
    quickSort3(A, l, j, s);
    quickSort3(A, i, r, s);
  }
}

// Função quickSort com Insertion Sort para pequenas partições
void quickSortIns(int *A, int l, int r, sortperf_t *s)
{
  if ((r - l) <= 50 && !((r - l) == 8 && l == 0))
  {
    insertionSort(A, l, r, s);
  }
  else
  {
    int i, j;
    partition(A, l, r, &i, &j, s);
    inccalls(s, 2);
    if (l < j)
      quickSortIns(A, l, j, s);
    if (i < r)
      quickSortIns(A, i, r, s);
  }
}

// Função quickSort usando mediana de três e Insertion Sort para pequenas partições
void quickSort3Ins(int *A, int l, int r, sortperf_t *s)
{
  if ((r - l) <= 50 && !((r - l) == 8 && l == 0))
  {
    insertionSort(A, l, r, s);
  }
  else
  {
    int i, j;
    partition3(A, l, r, &i, &j, s);
    inccalls(s, 2);
    if (l < j)
      quickSort3Ins(A, l, j, s);
    if (i < r)
      quickSort3Ins(A, i, r, s);
  }
}
