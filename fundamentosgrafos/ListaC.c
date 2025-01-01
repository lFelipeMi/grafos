#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int id;
    int peso;
    struct no *prox;
}No;

typedef struct
{
    No *inicio;
    No *fim;
    int tam;
}Caminho;

void iniciar_caminho(Caminho *caminho)
{
    caminho->inicio = NULL;
    caminho->fim = NULL;
    caminho->tam = 0;
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

void remover(Caminho *caminho, int id)
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

void imprimir(Caminho caminho)
{
    No *no = caminho.inicio;
    if(no)
    {
        do
        {
            printf("%d(%d)", no->id, no->peso);
            no = no->prox;
            if(no != caminho.inicio) printf(" -> ");
        } while (no != caminho.inicio);
        
    }
    else printf("Erro ao alocar memoria!");
    printf("\n");
}

int main()
{
    Caminho caminho;
    iniciar_caminho(&caminho);

    inserir_ordenado(&caminho, 3, 30);
    inserir_ordenado(&caminho, 1, 10);
    inserir_ordenado(&caminho, 5, 50);
    inserir_ordenado(&caminho, 4, 40);
    inserir_ordenado(&caminho, 2, 20);

    printf("Lista inicial:\n");
    imprimir(caminho);

    printf("\nRemovendo o vértice 1:\n");
    remover(&caminho, 1);
    imprimir(caminho);

    printf("\nRemovendo o vértice 5:\n");
    remover(&caminho, 5);
    imprimir(caminho);

    printf("\nRemovendo o vértice 3:\n");
    remover(&caminho, 3);
    imprimir(caminho);

    printf("\nTentando remover o vértice 10 (não existe):\n");
    remover(&caminho, 10);
    imprimir(caminho);

    return 0;
}
