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

Vertice* remover_vertice(Vertice **grafo, int id)
{
    Vertice* remover = NULL;

    if(!(*grafo)) printf("Grafo nulo!\n");

    while(*grafo && (*grafo)->id != id)
        grafo = &(*grafo)->prox;

    if(*grafo)
    {
        remover = *grafo;
        *grafo = remover->prox;
        remover->prox = NULL;
        return remover;
    }

    printf("Vertice nao encontrado!\n");
    return NULL;
}

Vertice* buscar_vertice(Vertice *grafo, int id)
{
    while(grafo)
    {
        if(grafo->id == id) return grafo;

        grafo = grafo->prox;
    }

    printf("Vertice nao encontrado!\n");
    return NULL;
}

//0 - Existe // 1 - Nao existe
int verificar_vertice (Vertice *grafo, int id)
{
    while(grafo)
    {
        if(grafo->id == id) return 0;

        grafo = grafo->prox;
    }
    return 1;
}

void inserir_aresta(Vertice **grafo, int id1, int id2)
{
    if(verificar_vertice(*grafo, id1) || verificar_vertice(*grafo, id2))
    { 
        printf("Um ou ambos vertices nao existem!\n");
        return;
    }

    while((*grafo)->id != id1)
        grafo = &(*grafo)->prox;

    Aresta *nova = malloc(sizeof(Aresta));
    if(nova)
    {
        (*nova).orig = id1;
        (*nova).dest = id2;

        Aresta **lista_adj = &(*grafo)->lista_adj;
        while(*lista_adj && (*lista_adj)->dest < id2)
            lista_adj = &(*lista_adj)->prox;

        if (*lista_adj && (*lista_adj)->dest == id2) 
        {
            printf("Aresta %d -> %d ja existe!\n", id1, id2);
            return;
        }

        nova->prox = *lista_adj;
        *lista_adj = nova;

        return;
    }
    printf("Falha ao alocar memoria!\n");
}

Aresta* remover_aresta(Vertice *grafo, int orig, int dest)
{
    Vertice *vertice = buscar_vertice(grafo, orig);
    if(!vertice)
    {
        printf("Vertice de origem %d nao encontrado.\n", orig);
        return NULL;
    }

    Aresta **lista_adj = &vertice->lista_adj;
    Aresta *remover = NULL;

    while (*lista_adj && (*lista_adj)->dest != dest) 
        lista_adj = &(*lista_adj)->prox;

    if(*lista_adj)
    {
        remover = *lista_adj;
        *lista_adj = remover->prox;
        remover->prox = NULL;
        return remover;
    }

    printf("Aresta de %d para %d nao encontrada.\n", orig, dest);
    return NULL;
}

Aresta* buscar_aresta(Vertice *grafo, int orig, int dest)
{
    Vertice *vertice = buscar_vertice(grafo, orig);
    if (!vertice) {
        printf("Vertice de origem %d nao encontrado.\n", orig);
        return NULL;
    }

    Aresta *lista_adj = vertice->lista_adj;
    while (lista_adj) {
        if (lista_adj->dest == dest) return lista_adj;

        lista_adj = lista_adj->prox;
    }

    printf("Aresta de %d para %d nao encontrada.\n", orig, dest);
    return NULL;
}

void imprimir_grafo(Vertice **grafo){
    if(*grafo == NULL)
    {
        printf("Grafo nulo!");
        return;
    }
    int vazio = -1;

    while(*grafo)
    {
        printf("\n\tVertice %02d: ", (*grafo)->id);
        Aresta *lista_adj = (*grafo)->lista_adj;
        if (!lista_adj) 
        {
            printf("Nenhuma aresta.");
        } 
        else 
        {
            vazio = 0;
            while (lista_adj) {
                if (lista_adj->prox) {
                    printf("%d -> ", lista_adj->dest);
                } else {
                    printf("%d", lista_adj->dest); 
                }
                lista_adj = lista_adj->prox;
            }
        }
        grafo = &(*grafo)->prox;
    }
    if(vazio) printf("Grafo vazio!\n");
}

int main()
{
    Vertice *grafo = NULL;
    inserir_vertice(&grafo, 6);
    inserir_vertice(&grafo, 21);
    inserir_vertice(&grafo, 2);
    inserir_vertice(&grafo, 10);
    inserir_vertice(&grafo, 3);
    inserir_vertice(&grafo, 4);

    inserir_aresta(&grafo, 6, 21);
    inserir_aresta(&grafo, 21, 2);
    inserir_aresta(&grafo, 2, 10);
    inserir_aresta(&grafo, 2, 3);
    inserir_aresta(&grafo, 3, 4);
    inserir_aresta(&grafo, 4, 6);
    inserir_aresta(&grafo, 21, 21);

    imprimir_grafo(&grafo);
    ///////////////////////////////////////////////////
    printf("\n\n");
    Vertice *vertice_search = buscar_vertice(grafo, 21);
    printf("Vertice buscado: %d\n", vertice_search->id);

    Aresta *aresta_search = buscar_aresta(grafo, 4, 6);
    printf("Aresta de %d -> %d buscada\n", aresta_search->orig, aresta_search->dest);
    ///////////////////////////////////////////////////
    printf("\n");
    Vertice *vertice_remove = remover_vertice(&grafo, 10);
    printf("Vertice removido %d\n", vertice_remove->id);
    Aresta *aresta_remove = remover_aresta(grafo, 4, 6);
    printf("Aresta removida %d -> %d\n", aresta_remove->orig, aresta_remove->dest);
    imprimir_grafo(&grafo);

    free(vertice_remove);
    free(aresta_remove);
    liberar_Grafo(grafo);
    printf("\n");
    return 0;
}
