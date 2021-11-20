#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 11

int main()
{
    int i, j, k;
    int pontuacao=0;
    int gap=-1;
    char seq1[N], seq2[N];
    char sol1[N*2], sol2[N*2];

    //recebendo as duas sequencias de dna
    printf("\n---Alinhamento de duas sequencias de DNA---");
    printf("\nInsira uma sequencia (max [%d] elementos): ", N);
    scanf(" %s", seq1);
    printf("Insira outra sequencia (max [%d] elementos): ", N);
    scanf(" %s", seq2);    

    //processo de alinhamento das sequencias
    for(i=0, j=0, k=0; (i<N || j<N) && k<N*2; i++, j++, k++) {
        if(i==N) {
            sol1[k]='-';
            sol2[k]=seq2[j];
            pontuacao=-(pontuacao-gap);
            gap--;
            i--;
        }
        if(j==N) {
            sol1[k]=seq1[i];
            sol2[k]='-';
            pontuacao=-(pontuacao-gap);
            gap--;
            j--;
        }
        else if(seq1[i]==seq2[j]) {
            sol1[k]=seq1[i];
            sol2[k]=seq2[j];
            pontuacao=pontuacao+2;
        }
        else {
            //(a,b) => custo -4
            if(pontuacao-4 > (-(pontuacao-gap))) {
                sol1[k]=seq1[i];
                sol2[k]=seq2[j];
                pontuacao=pontuacao-4;
            }
            //(gap) => custo -1
            else {
                sol1[k]='-';
                sol2[k]=seq2[j];
                pontuacao=-(pontuacao-gap);
                gap--;
                i--;
            }
        }
    }
    int solucao=strlen(sol1);
    printf("\n---Imprimindo solucao encontrada---");
    printf("\nPontuacao total: %d\n", pontuacao);
    for(i=0; i<solucao; i++) {
        printf("%c ", sol1[i]);
    }
    printf("\n");
    for(i=0; i<solucao; i++) {
        printf("%c ", sol2[i]);
    }
}