#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxvetP 1000 //quantidade max de elementos do vetor pequeno
#define maxvetM 10000 //quantidade max de elementos do vetor medio
#define maxvetG 50000 //quantidade max de elementos do vetor grande
#define billion 1000000000

//definicoes para os buckets
#define tamBucket 500 //numero de baldes
#define capacidade 100 //capacidade de cada balde

int tamVetor;

// calcular o tempo de execucao
struct timespec inicio;
struct timespec final;

double calculaTempo(struct timespec inicio, struct timespec final)
{
    double seg, nanoseg;
    seg = (final.tv_sec - inicio.tv_sec);
    nanoseg = (final.tv_nsec - inicio.tv_nsec);
    seg += (nanoseg / billion);
    return seg;
}

// funcao para alocar o vetor dinamico
void alocaVetor(int *vetor)
{
    FILE *fpVetor;
    // fpVetor = fopen("crescenteP.dat", "r");
    // fpVetor = fopen("crescenteM.dat", "r");
    // fpVetor = fopen("crescenteG.dat", "r");

    // fpVetor = fopen("decrescenteP.dat", "r");
    // fpVetor = fopen("decrescenteM.dat", "r");
    // fpVetor = fopen("decrescenteG.dat", "r");

    // fpVetor = fopen("randP.dat", "r");
    // fpVetor = fopen("randM.dat", "r");
    fpVetor = fopen("randG.dat", "r");

    int i = 0;
    do
    {
        fscanf(fpVetor, "%d\n", &vetor[i]);
        // printf("[%d]: %d\n", i, vetor[i]);
        i++;
    } while (!feof(fpVetor));
    tamVetor = i;
    vetor = (int *)realloc(vetor, tamVetor * sizeof(int));
    fclose(fpVetor);
}

struct no {
    int num;
    struct no *prox;
};

// bucket
int getBucketIndex(int valor) 
{
    return valor/capacidade;
}
struct no *insertionSort(struct no *lista) {
    struct no *k;
    struct no *listaNo;
    if(lista==0 || lista->prox==0) {
        return lista;
    }
    listaNo = lista;
    k = lista->prox;
    listaNo->prox = 0;
    while(k!=0) {
        struct no *ptr;
        if(listaNo->num > k->num) {
            struct no *aux;
            aux = k;
            k = k->prox;
            aux->prox = listaNo;
            listaNo = aux;
            continue;
        }
        for(ptr = listaNo; ptr->prox!=0; ptr=ptr->prox) {
            if(ptr->prox->num > k->num) {
                break;
            }
        }
        if(ptr->prox!=0) {
            struct no *aux;
            aux = k;
            k = k->prox;
            aux->prox = ptr->prox;
            ptr->prox = aux;
            continue;
        }
        else {
            ptr->prox = k;
            k = k->prox;
            ptr->prox->prox = 0;
            continue;
        }
    }
    return listaNo;
}
void bucketSort(int *vetor)
{
    int i, j;
    struct no **buckets;
    //alocando memoria para os baldes
    buckets = (struct no**)malloc(sizeof(struct no*)*tamBucket);
    for(i=0; i<tamBucket; i++) {
        buckets[i]=NULL;
    }
    //preenchendo os baldes com os respectivos elementos
    for(i=0; i<tamVetor; i++) {
        struct no *atual;
        int pos = getBucketIndex(vetor[i]);
        atual = (struct no*)malloc(sizeof(struct no));
        atual->num = vetor[i];
        atual->prox = buckets[pos];
        buckets[pos] = atual;
    }
    //ordenando os elementos 
    for(i=0; i<tamBucket; i++) {
        buckets[i] = insertionSort(buckets[i]);
    }
    //combinando os elementos ordenados no vetor
    for(j=0, i=0; i<tamBucket; i++) {
        struct no *node;
        node = buckets[i];
        while(node) {
            vetor[j++] = node->num;
            node = node->prox;
        }
    }
    return ;
}

int main()
{
    // int *vetor = (int*)malloc(maxvetP*sizeof(int));
    // int *vetor = (int*)malloc(maxvetM*sizeof(int));
    int *vetor = (int *)malloc(maxvetG * sizeof(int));

    alocaVetor(vetor);

    double tempo;
    clock_gettime(CLOCK_REALTIME, &inicio);
    bucketSort(vetor);
    clock_gettime(CLOCK_REALTIME, &final);
    tempo = calculaTempo(inicio, final);
    printf("\nTempo ordenacao: %lf", tempo);

    free(vetor);
    return 0;
}
