#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int id;
    int peso;
    struct no *prox;
}No;

void liberar(No *caminho) {
    while (caminho) {
        No *remover = caminho;
        caminho = caminho->prox;
        free(remover);
    }
}

void inserir_inicio(No **caminho, int id, int peso)
{
    No *novo = malloc(sizeof(No));

    if(novo)
    {
        novo->id =  id;
        novo->peso = peso;
        novo->prox = *caminho;
        *caminho = novo;
    } 
    else printf("Erro ao alocar memoria.\n");
}

void inserir_fim(No **caminho, int id, int peso)
{
    No *novo = malloc(sizeof(No));

    if(novo)
    {
        if(*caminho == NULL) 
            *caminho = novo;
        else
        {
            while((*caminho)->prox)
                caminho = &(*caminho)->prox;
            (*caminho)->prox = novo;
        }
    }
    else printf("Erro ao alocar memoria.\n");
}

void inserir_ordenado(No **caminho, int id, int peso)
{
    No *novo = malloc(sizeof(No));

    if(novo)
    {
        novo->id = id;
        novo->peso = peso;
        novo->prox = NULL;

        while(*caminho && (*caminho)->id < id)
            caminho = &(*caminho)->prox;
        novo->prox = *caminho;
        *caminho = novo;
    } 
    else printf("Erro ao alocar memoria.\n");
}

void remover(No **caminho, int id)
{
    if(*caminho)
    {
        while(*caminho && (*caminho)->id != id)
            caminho = &(*caminho)->prox;

        if(*caminho)
        {
            No *remover = *caminho;
            *caminho = (*caminho)->prox;
            free(remover);
        }
        else printf("Valor nao encontrado!\n");
    }
    else printf("O caminho esta vazio!\n");
}

No* buscar(No *caminho, int id)
{
    while(caminho && caminho->id != id)
        caminho = caminho->prox;
    
    if(!caminho) printf("Vertice nao encontrado no caminho!\n");

    return caminho;
}

void imprimir(No *caminho)
{
    if(!caminho) printf("O caminho esta vazio.");
    while(caminho)
    {
        printf("%d(%d) ", caminho->id, caminho->peso);
        caminho = caminho->prox;
        if(caminho) printf("-> ");
    }
    printf("\n");
}

int main()
{
    printf("Nem testei...");
    return 0;
}