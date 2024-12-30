#include <stdio.h>
#include <stdlib.h>

typedef struct aresta
{
    int orig;
    int dest;
    struct aresta *prox;
}Aresta;

typedef struct vertice
{
    int id;
    Aresta *lista_adj;
    struct vertice *prox;
}Vertice;

void liberar_Grafo(Vertice *grafo) 
{
    while (grafo != NULL) 
    {
        Aresta *adj = grafo->lista_adj;
        while (adj != NULL) 
        {
            Aresta *aux = adj;
            adj = adj->prox;
            free(aux);
        }
        Vertice *temp = grafo;
        grafo = grafo->prox;
        free(temp);
    }
}

void inserir_vertice(Vertice **grafo, int id)
{
    Vertice *novo = malloc(sizeof(Vertice));

    if(novo)
    {
        novo->id = id;
        novo->lista_adj = NULL;
        novo->prox = NULL;

        while(*grafo && (*grafo)->id < id)
            grafo = &(*grafo)->prox;

        if (*grafo != NULL && (*grafo)->id == id)
        {
            printf("Ja existe vertice com esse id!\n");
            free(novo);
            return;
        }

        novo->prox = *grafo;
        *grafo = novo;

        return;
    }
    printf("Erro ao alocar memoria para novo vertice.\n");
}

void imprimir_grafo(Vertice **grafo){
    while(*grafo){
        printf("Vertice: %d\n", (*grafo)->id);
        grafo = &(*grafo)->prox;
    }
}

int main(){
    Vertice *grafo = NULL;
    inserir_vertice(&grafo, 6);
    inserir_vertice(&grafo, 21);
    inserir_vertice(&grafo, 2);
    inserir_vertice(&grafo, 10);
    inserir_vertice(&grafo, 3);
    inserir_vertice(&grafo, 4);
    imprimir_grafo(&grafo);
    liberar_Grafo(grafo);

    return 0;
}