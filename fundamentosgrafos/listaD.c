#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int id;
    int peso;
    struct no *prox;
    struct no *ant;
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
        novo->id = id;
        novo->peso = peso;
        novo->prox = *caminho;
        novo->ant = NULL;

        if(*caminho) (*caminho)->ant = novo;
        *caminho = novo;
    }
    else("Erro ao alocar memoria!\n");
}

void inserir_final(No **caminho, int id, int peso)
{
    No *novo = malloc(sizeof(No));
    
    if(novo)
    {
        novo->id = id;
        novo->peso = peso;
        novo->prox = NULL;

        if(!(*caminho))
        {
            *caminho = novo;
            novo->ant = NULL;
            return;
        }
        
        while ((*caminho)->prox)
            caminho = &(*caminho)->prox;

        (*caminho)->prox = novo;
        novo->ant = *caminho;
    }
    else printf("Erro ao alocar memoria!\n");
}

void inserir_ordenado(No **caminho, int id, int peso)
{
    No *novo = malloc(sizeof(No));

    if(novo)
    {
        novo->id = id;
        novo->peso = peso;

        if(!(*caminho))
        {
            novo->prox = NULL;
            novo->ant = NULL;
            *caminho = novo;
        }
        else if((*caminho)->id > id) 
        {
            novo->prox = (*caminho);
            novo->ant = NULL;
            (*caminho)->ant = novo;
            *caminho = novo;            
        }
        else
        {
            while((*caminho)->prox && (*caminho)->prox->id < id)
                caminho = &(*caminho)->prox;
            novo->prox = (*caminho)->prox;
            if (novo->prox) novo->prox->ant = novo;
            novo->ant = (*caminho);
            (*caminho)->prox = novo;
        }
    }
    else printf("Erro ao alocar memoria!\n");
}

void remover(No **caminho, int id)
{
    No *remover = NULL;
    if(*caminho)
    {
        if((*caminho)->id == id)
        {
            remover = *caminho;
            (*caminho) = (*caminho)->prox;
            if(*caminho) (*caminho)->ant = NULL;
        }
        else
        {
            while((*caminho)->prox && (*caminho)->prox->id != id)
                caminho = &(*caminho)->prox;
            if((*caminho)->prox)
            {
                remover = (*caminho)->prox;
                (*caminho)->prox = remover->prox;
                if((*caminho)->prox) (*caminho)->prox->ant = (*caminho);
            } 
            else printf("Valor nao encontrado!\n");
        }
    }
    else printf("O caminho esta vazio!\n");
    if(remover) free(remover);
}

No *buscar(No *caminho, int id)
{
    while(caminho && caminho->id != id)
        caminho = caminho->prox;
    if(!caminho) printf("Vertice nao encontrado");
    
    return caminho;
}

void imprimir(No *caminho)
{
    while (caminho)
    {
        printf("%d(%d) ", caminho->id, caminho->peso);
        caminho = caminho->prox;
        if (caminho) printf("-> ");
    }
    printf("\n");
}

No *ultimo(No *caminho)
{
    if(!caminho) 
    {
        printf("O caminho esta vazio!\n");
        return caminho;
    }

    while(caminho->prox)
        caminho = caminho->prox;
    return caminho;
}

void imprimirContrario(No *caminho)
{
    caminho = ultimo(caminho);
    while(caminho)
    {
        printf("%d(%d)", caminho->id, caminho->peso);
        caminho = caminho->ant;
        if(caminho) printf(" <- ");
    }
    printf("\n");
}

int main()
{
    No *caminho = NULL;
    inserir_final(&caminho, 1, 10);
    inserir_final(&caminho, 2, 20);
    inserir_final(&caminho, 3, 30);
    inserir_ordenado(&caminho, 6, 60);
    inserir_ordenado(&caminho, 5, 50);
    inserir_ordenado(&caminho, 4, 40);
    remover(&caminho, 3);

    printf("Caminho:\n");
    imprimir(caminho);
    imprimirContrario(caminho);

    return 0;
}