#define _POSIX_C_SOURCE 199309L

#include "./../include/sorts.h"

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
     fprintf(stderr, "sortperf\n");
     fprintf(stderr, "\t-z <int>\t(vector size)\n");
     fprintf(stderr, "\t-s <int>\t(initialization seed)\n");
     fprintf(stderr, "\t-a <s|i|q|q3|qi|q3i|h|rs>\t(algorithm)\n");
     fprintf(stderr, "\t    s\tselection\n");
     fprintf(stderr, "\t    i\tinsertion\n");
     fprintf(stderr, "\t    q\tquicksort\n");
     fprintf(stderr, "\t    q3\tquicksort+median3\n");
     fprintf(stderr, "\t    qi\tquicksort+insertion\n");
     fprintf(stderr, "\t    q3i\tquicksort+median3+insertion\n");
     fprintf(stderr, "\t    h\theapsort\n");
     fprintf(stderr, "\t    rs\trecursive selection\n");
}

void parse_args(int argc, char **argv, opt_t *opt)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc, argv, opt
// Saida: opt
{
     // variaveis externas do getopt
     extern char *optarg;
     extern int optind;

     // variavel auxiliar
     int c;

     // inicializacao variaveis globais para opcoes
     opt->seed = 1;
     opt->size = 10;
     opt->alg = 1;

     // getopt - letra indica a opcao, : junto a letra indica parametro
     // no caso de escolher mais de uma operacao, vale a ultima
     while ((c = getopt(argc, argv, "z:s:a:h")) != EOF)
     {
          switch (c)
          {
          case 'z':
               opt->size = atoi(optarg);
               break;
          case 's':
               opt->seed = atoi(optarg);
               break;
          case 'a':
               opt->alg = name2num(optarg);
               break;
          case 'h':
          default:
               uso();
               exit(1);
          }
     }
     if (!opt->alg)
     {
          uso();
          exit(1);
     }
}

void clkDiff(struct timespec t1, struct timespec t2,
             struct timespec *res)
// Descricao: calcula a diferenca entre t2 e t1, que e armazenada em res
// Entrada: t1, t2
// Saida: res
{
     if (t2.tv_nsec < t1.tv_nsec)
     {
          // ajuste necessario, utilizando um segundo de tv_sec
          res->tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
          res->tv_sec = t2.tv_sec - t1.tv_sec - 1;
     }
     else
     {
          // nao e necessario ajuste
          res->tv_nsec = t2.tv_nsec - t1.tv_nsec;
          res->tv_sec = t2.tv_sec - t1.tv_sec;
     }
}

int main(int argc, char **argv)
{

     sortperf_t s;
     int *vet;
     char buf[200];
     char pref[100];
     opt_t opt;
     struct timespec inittp, endtp, restp;
     int retp;

     // parse_args
     parse_args(argc, argv, &opt);

     // malloc with opt.size+1 for heapsort
     vet = (int *)malloc((opt.size + 1) * sizeof(int));

     // initialize
     resetcounter(&s);
     srand48(opt.seed);
     initVector(vet, opt.size);
     vet[opt.size] = vet[0]; // for heapsort
     // if (opt.size < 100) printVector(vet, opt.size);

     retp = clock_gettime(CLOCK_MONOTONIC, &inittp);

     // execute algorithm
     switch (opt.alg)
     {
     case ALGINSERTION:
          insertionSort(vet, 0, opt.size - 1, &s);
          break;
     case ALGSELECTION:
          selectionSort(vet, 0, opt.size - 1, &s);
          break;
     case ALGQSORT:
          quickSort(vet, 0, opt.size - 1, &s);
          break;
     case ALGQSORT3:
          quickSort3(vet, 0, opt.size - 1, &s);
          break;
     case ALGQSORTINS:
          quickSortIns(vet, 0, opt.size - 1, &s);
          break;
     case ALGQSORT3INS:
          quickSort3Ins(vet, 0, opt.size - 1, &s);
          break;
     case ALGSHELLSORT:
          shellSort(vet, opt.size, &s);
          break;
     case ALGRECSEL:
          recursiveSelectionSort(vet, 0, opt.size - 1, &s);
          break;
     }
     retp = clock_gettime(CLOCK_MONOTONIC, &endtp);
     clkDiff(inittp, endtp, &restp);

     // if (opt.size<100) printVector(vet, opt.size);

     // print stats
     sprintf(pref, "alg %s seed %d size %d time %ld.%.9ld",
             num2name(opt.alg), opt.seed, opt.size, restp.tv_sec, restp.tv_nsec);

     printsortperf(&s, buf, pref);
     printf("%s\n", buf);

     exit(0);
}