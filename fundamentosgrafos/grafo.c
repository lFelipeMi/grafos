#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void liberar_grafo(Vertice *grafo)
{
    while(grafo != NULL)
    {
        Aresta *adj = grafo->lista_adj;
        while(adj)
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
    
    if(!novo)
    {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    novo->id = id;
    novo->grau_entrada = 0;
    novo->grau_saida = 0;
    novo->visitado = 0;
    novo->lista_adj = NULL;
    novo->prox = NULL;

    while(*grafo && (*grafo)->id < id)
        grafo = &(*grafo)->prox;
    
    novo->prox = *grafo;
    *grafo = novo;
}

void remover_vertice(Vertice **grafo, int id)
{
    Vertice *remover;

    while(*grafo && (*grafo)->id != id)
        grafo = &(*grafo)->prox;

    if(*grafo)
    {
        remover = (*grafo);
        *grafo = (*grafo)->prox;
        remover->prox = NULL;
        free(remover);
        return;
    }

    printf("Vertice nao encontrado!\n");
}

Vertice *buscar_vertice(Vertice *grafo, int id)
{
    while(grafo)
    {   
        if(grafo->id == id) return grafo;
        grafo = grafo->prox;
    }

    return NULL;
}

int contar_vertice(Vertice *grafo)
{
    if(!grafo) return 0;
    return 1 + contar_vertice(grafo->prox);
}

void inserir_aresta(Vertice **grafo, int orig, int dest)
{
    if (!grafo || !(*grafo)) 
    {
        printf("Grafo vazio!\n");
        return;
    }

    Vertice *vertice_origem = buscar_vertice(*grafo, orig);
    if (!vertice_origem) 
    {
        printf("Vertice de origem (%d) nao encontrado!\n", orig);
        return;
    }

    Vertice *vertice_destino = buscar_vertice(*grafo, dest);
    if (!vertice_destino) 
    {
        printf("Vertice de destino (%d) nao encontrado!\n", dest);
        return;
    }

    Aresta *nova = malloc(sizeof(Aresta));
    if (!nova) 
    {
        printf("Erro ao alocar memoria\n");
        return;
    }

    nova->orig = orig;
    nova->dest = dest;
    nova->prox = NULL;
    nova->ant = NULL;

    Aresta **lista_adj = &vertice_origem->lista_adj;

    if (!(*lista_adj)) 
        *lista_adj = nova;
    else if ((*lista_adj)->dest > dest) 
    {
        nova->prox = *lista_adj;
        (*lista_adj)->ant = nova;
        *lista_adj = nova;
    } 
    else 
    {
        Aresta *atual = *lista_adj;
        while (atual->prox && atual->prox->dest < dest)
            atual = atual->prox;

        nova->prox = atual->prox;
        if (atual->prox) 
            atual->prox->ant = nova;

        atual->prox = nova;
        nova->ant = atual;
    }
}


void remover_aresta(Vertice **grafo, int orig, int dest)
{
    while(*grafo && (*grafo)->id != orig)
        grafo = &(*grafo)->prox;

    if(!(*grafo && (*grafo)->lista_adj))
    {
        printf("Aresta nao encontrada!\n");
        return;
    }

    Aresta *remover = NULL;
    Aresta **lista_adj = &(*grafo)->lista_adj;

    if((*lista_adj)->dest == dest)
    {
        remover = *lista_adj;
        *lista_adj = (*lista_adj)->prox;
        if(*lista_adj) (*lista_adj)->ant = NULL; 
    }
    else
    {
        while((*lista_adj)->prox && (*lista_adj)->prox->dest != dest)
            lista_adj = &(*lista_adj)->prox;
        if((*lista_adj)->prox)
        {
            remover = (*lista_adj)->prox;
            (*lista_adj)->prox = remover->prox;
            if((*lista_adj)->prox) (*lista_adj)->prox->ant = (*lista_adj);
        }
        else printf("Valor nao encontrado!\n");
    }
    
    if(remover) free(remover);
}

Aresta *buscar_aresta(Vertice **grafo, int orig, int dest)
{
    while(*grafo && (*grafo)->id != orig)
        grafo = &(*grafo)->prox;

    if(!(*grafo && (*grafo)->lista_adj)) return NULL;

    if((*grafo)->lista_adj->dest == dest) return (*grafo)->lista_adj;

    Aresta **lista_adj = &(*grafo)->lista_adj;

    while((*lista_adj)->prox && (*lista_adj)->prox->dest != dest)
        lista_adj = &(*lista_adj)->prox;

    return (*lista_adj)->prox;
}

int contar_arestas(Vertice *grafo)
{
    if(!grafo) return 0;
    
    int quant = 0;
    Aresta *lista_adj = grafo->lista_adj;

    while(lista_adj)
    {
        quant++;
        lista_adj = lista_adj->prox;
    }

    return quant + contar_arestas(grafo->prox);
}

void imprimir_grafo(Vertice *grafo)
{
    if(!grafo)
    {
        printf("Grafo nulo!\n");
        return;
    }

    int vertices = contar_vertice(grafo);
    int arestas = contar_arestas(grafo);
    if(!arestas) printf("Grafo vazio, imprimindo vertices:\n");

    do
    {
        printf("%d: ", grafo->id);
        Aresta *lista_adj = grafo->lista_adj;
        while(lista_adj)
        {
            printf("%d", lista_adj->dest);
            lista_adj = lista_adj->prox;
            if(lista_adj) printf(" -> ");
            else printf("\n");
        }
        grafo = grafo->prox;
    }while(grafo);
    printf("\nNumero de vertices: %d\n", vertices);
    printf("Numero de arestas: %d\n", arestas);
}