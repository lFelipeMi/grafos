#include <stdio.h>
#include <stdlib.h>
#include "listaC.h"

void liberar_caminho(Caminho *caminho) 
{
    if (caminho->inicio) 
    {
        No *aux = caminho->inicio;

        do 
        {
            No *remover = aux;
            aux = aux->prox;
            free(remover);
        } while (aux != caminho->inicio); 

        caminho->inicio = NULL;
        caminho->fim = NULL;
        caminho->tam = 0;
    }
}


Caminho *iniciar_caminho()
{
    Caminho *caminho = malloc(sizeof(Caminho));
    if (!caminho) {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }
    caminho->inicio = NULL;
    caminho->fim = NULL;
    caminho->tam = 0;
    return caminho;
}

void inserir_inicio(Caminho *caminho, int id, int peso)
{
    No *novo = malloc(sizeof(No));

    if(novo)
    {
        novo->id = id;
        novo->peso = peso;
        novo->prox = caminho->inicio;
        caminho->inicio = novo;
        if(!caminho->fim) caminho->fim = novo;
        caminho->fim->prox = caminho->inicio;
        caminho->tam++;
    }
    else printf("Erro ao alocar memoria!\n");
}

void inserir_fim(Caminho *caminho, int id, int peso)
{
    No *novo = malloc(sizeof(No));

    if(novo)
    {
        novo->id = id;
        novo->peso = peso;

        if(!caminho->inicio)
        {
            caminho->inicio = novo;
            caminho->fim = novo;
            caminho->fim->prox = caminho->inicio;
        }
        else
        {
            caminho->fim->prox = novo;
            caminho->fim = novo;
            novo->prox = caminho->inicio;
        }
        caminho->tam++;
    } 
    else printf("Erro ao alocar memoria!\n");
}

void inserir_ordenado(Caminho *caminho, int id, int peso)
{
    No *novo = malloc(sizeof(No));

    if(novo)
    {
        novo->id = id;
        novo->peso = peso;

        if(!caminho->inicio || caminho->inicio->id > id)
        {
            novo->prox = caminho->inicio;
            caminho->inicio = novo;
            if(!caminho->fim) caminho->fim = novo;
            caminho->fim->prox = caminho->inicio;
        }
        else
        {
            No *aux = caminho->inicio;
            while(aux->prox != caminho->inicio && aux->prox->id < id)
                aux = aux->prox;
            
            if(aux->prox == caminho->inicio)
            {
                caminho->fim->prox = novo;
                caminho->fim = novo;
                novo->prox = caminho->inicio;
            }
            else
            {
                novo->prox = aux->prox;
                aux->prox = novo;
            }
        }
        caminho->tam++;
    }
    else printf("Erro ao alocar memoria!\n");
}

void remover_caminho(Caminho *caminho, int id)
{
    No *remover = NULL;
    if(caminho && caminho->inicio)
    {
        if(caminho->inicio == caminho->fim && caminho->inicio->id == id)
        {
            remover = caminho->inicio;
            caminho->inicio = NULL;
            caminho->fim = NULL;
        }
        else if(caminho->inicio->id == id)
        {
            remover = caminho->inicio;
            caminho->inicio = caminho->inicio->prox;
            caminho->fim->prox= caminho->inicio;
        }
        else
        {
            No *aux = caminho->inicio;
            while(aux->prox != caminho->inicio && aux->prox->id != id)
                aux = aux->prox;
            
            if(aux->prox == caminho->inicio)
            {
                printf("Vertice nao encontrado no caminho!\n");
                return;
            }

            if(caminho->fim == aux->prox)
            {
                remover = caminho->fim;
                aux->prox = caminho->inicio;
                caminho->fim = aux;
            } 
            else
            {
                remover = aux->prox;
                aux->prox = aux->prox->prox;
            }
        }
        free(remover);
        caminho->tam--;
    }
    else printf("O caminho esta vazio!\n");
}

No* buscar_caminho(Caminho *caminho, int id){
    No *no = NULL;
    No *aux = caminho->inicio;
    
    if(aux){
        do{
            if(aux->id == id)
                return aux;
            aux = aux->prox;
        }while(aux != caminho->inicio);
        printf("Valor nao encontrado!\n");
    } else
        printf("O caminho esta vazio!\n");
    return NULL;
}

void imprimir_caminho(Caminho *caminho)
{
    No *no = caminho->inicio;
    if(no)
    {
        do
        {
            printf("%d(%d)", no->id, no->peso);
            no = no->prox;
            if(no != caminho->inicio) printf(" -> ");
        } while (no != caminho->inicio);
        
    }
    else printf("Erro ao alocar memoria!");
    printf("\n");
}
