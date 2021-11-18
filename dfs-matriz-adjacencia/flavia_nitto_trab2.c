#include<stdio.h>
#include<stdlib.h>
#define V 6 //trocar isso aqui pra 5

typedef struct Grafo 
{
    int v;
    int **matriz;
}GRAFO;

GRAFO* inicializaGrafo()
{
    int x, y;
    GRAFO *G=malloc(sizeof(GRAFO));
    G->v=V;
    G->matriz=malloc(V*sizeof(int*));
    for(x=0; x<V; x++) {
        G->matriz[x] = malloc(V*sizeof(int));
        for(y=0; y<V; y++) {
            G->matriz[x][y]=0;
        }
    }  
    return G;
}
void inicializaVet(int marcados[])
{
    int i;
    for(i=0; i<V; i++) {
        marcados[i]=0;
    }
}
void imprimeGrafo(GRAFO *G)
{
    int i, j;
    printf("\n-Mostrando matriz de adjacencia-\n");
    for(i=0; i<V; i++) {
        for(j=0; j<V; j++) {
            printf("[%d] ", G->matriz[i][j]);
        }
        printf("\n");        
    }   
}
void addAresta(GRAFO *G, int x, int y)  
{
    G->matriz[x][y]=1;
    printf("\nAresta criada: [%d] => [%d]\n", x, y);
}
int buscaDFS(GRAFO *G, int marcados[], int inicio, int objetivo) 
{
    int i, aux;
    printf("\nPercorremos o no: [%d]", inicio);
    marcados[inicio]=1;
    if(objetivo==inicio) {
        printf("\nEncontramos o vertice [%d].", objetivo);
        aux=1;
        return aux;
    }
    else {
        for(i=0; i<V; i++) {
            if(G->matriz[inicio][i]==1 && (!marcados[i])) {
                if(buscaDFS(G, marcados, i, objetivo)==1)
                    aux=1;  break;                
            }
        }
    return aux;        
    }
}
int buscaAuxiliar(GRAFO *G, int marcados[], int inicio, int objetivo)
{
    int novoNo, i;
    printf("\nNo inicial: [%d]", inicio);
    do
    {
        novoNo=0;
        for(i=0; i<V; i++) {
            if(marcados[i]==0) {
                novoNo=1;
                inicio=i;
                break;
            }
        }
        if(!novoNo)
            return 0;
        printf("\nNo inicial: [%d]", inicio);
    } while (buscaDFS(G,marcados,inicio,objetivo)==0);
}
int verificaMatriz(GRAFO *G) 
{
    int x, y;
    int inicio=-1;
    for(x=0; x<V; x++) {    
        for(y=0; y<V; y++) {
            if(G->matriz[x][y]==1 && inicio==-1) {
                inicio=x;
            }        
        }
    }      
    if(inicio==-1)
        return 0;
    else
        return inicio;
}
int main() 
{
    int marcados[V];
    inicializaVet(marcados);

    GRAFO *G;
    G=inicializaGrafo();
    imprimeGrafo(G);

    int op=-1, vertice, inicio;
    inicio=verificaMatriz(G);

    do
    {
        printf("\n\n---------MENU---------");
        printf("\n1) Criar aresta");
        printf("\n2) Buscar vertice do grafo");
        printf("\n3) Mostrar matriz de adjacencia");
        printf("\n0) Sair\nOpcao: ");
        scanf("%d", &op);
        switch(op)
        {
            case 1:
            {
                int auxInicio, auxDest;
                printf("\nInsira o inicio (de 0 a 4): ");
                scanf("%d", &auxInicio);
                printf("Insira o destino (de 0 a 4): ");
                scanf("%d", &auxDest);
                if(auxInicio<0 || auxInicio>4 || auxDest<0 || auxDest>4) {
                    printf("\nAVISO: valor invalido!"); break;                     
                }               
                else {
                    addAresta(G, auxInicio, auxDest);   
                    imprimeGrafo(G);                 
                }
            }break;
            case 2:
            {
                printf("\nInsira o vertice a ser buscado (de 0 a 4): ");
                scanf("%d", &vertice);
                if(vertice<0 || vertice>4) {
                    printf("\nAVISO: valor invalido!"); break;
                }
                else {
                    if(buscaAuxiliar(G, marcados, inicio, vertice)==0) {
                        printf("\nAVISO: nao foi possivel encontrar o elemento [%d] no grafo", vertice);
                    }
                    inicializaVet(marcados);
                }
            }break;
            case 3:
            {
                imprimeGrafo(G);
            }break;            
            case 0: printf("\nSaindo do sistema..."); break;
            default: printf("\nAVISO: Opcao invalida!"); break;
        }
    } while(op!=0);
}