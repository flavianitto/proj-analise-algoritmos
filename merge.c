#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define maxvetP 1000 //quantidade max de elementos do vetor pequeno
#define maxvetM 10000 //quantidade max de elementos do vetor medio
#define maxvetG 50000 //quantidade max de elementos do vetor grande
#define billion 1000000000

int tamVetor;

//calcular o tempo de execucao
struct timespec inicio;
struct timespec final;

double calculaTempo(struct timespec inicio, struct timespec final)
{
    double seg, nanoseg;
    seg = (final.tv_sec - inicio.tv_sec);
    nanoseg = (final.tv_nsec - inicio.tv_nsec);
    seg += (nanoseg/billion);
    return seg;
}

//funcao para alocar o vetor dinamico
void alocaVetor(int *vetor)
{
    FILE *fpVetor;
    //fpVetor = fopen("crescenteP.dat", "r");
    //fpVetor = fopen("crescenteM.dat", "r");
    //fpVetor = fopen("crescenteG.dat", "r");

    //fpVetor = fopen("decrescenteP.dat", "r");
    //fpVetor = fopen("decrescenteM.dat", "r");
    //fpVetor = fopen("decrescenteG.dat", "r");   

    //fpVetor = fopen("randP.dat", "r");
    //fpVetor = fopen("randM.dat", "r");
    fpVetor = fopen("randG.dat", "r");
    
    int i=0;
    do {
        fscanf(fpVetor, "%d\n", &vetor[i]);
        //printf("[%d]: %d\n", i, vetor[i]);
        i++;
    }while(!feof(fpVetor));
    tamVetor=i;
    vetor = (int*)realloc(vetor, tamVetor*sizeof(int));
    fclose(fpVetor);
}

//merge
void intercala(int *vetor, int p, int q, int r)
{
    int *aux = malloc((r-p)*sizeof(int));
    int i=p, j=q, k=0;
    while(i<q && j<r)
    {
        if(vetor[i]<=vetor[j])
            aux[k++] = vetor[j++];
        else
            aux[k++] = vetor[j++];
    }
    while(i<q)
        aux[k++]=vetor[i++];
    while(j<r)
        aux[k++]=vetor[j++];
    for(i=p; i<r; i++)
        vetor[i]=aux[i-p];
    free(aux);
}
void mergeSort(int *vetor, int p, int r)
{
    if(p<r-1)
    {
        int q = (p+r)/2;
        mergeSort(vetor, p, q);
        mergeSort(vetor, q, r);
        intercala(vetor, p, q, r);
    }
}

int main()
{
    //int *vetor = (int*)malloc(maxvetP*sizeof(int));
    //int *vetor = (int*)malloc(maxvetM*sizeof(int));
    int *vetor = (int*)malloc(maxvetG*sizeof(int));

    alocaVetor(vetor);

    double tempo;
    clock_gettime(CLOCK_REALTIME, &inicio);
    mergeSort(vetor, 0, tamVetor);
    clock_gettime(CLOCK_REALTIME, &final);
    tempo = calculaTempo(inicio, final);
    printf("\nTempo ordenacao: %lf", tempo);

    free(vetor);
    return 0;
}
