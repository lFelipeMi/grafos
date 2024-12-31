#include <stdio.h>
#include <stdlib.h>

typedef struct aresta
{
    int orig;
    int dest;
    int peso;
    struct aresta *prox;
}Aresta;

typedef struct vertice
{
    int id;
    int visitado;
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
        novo->visitado = 0;
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

int contar_vertice(Vertice *grafo)
{
    int quant =  0;
    while(grafo)
    {
        quant++;
        grafo = grafo->prox;
    }
    return quant;
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
        (*nova).peso = 1;

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

int buscar_conexao(Vertice *grafo, int id1, int id2)
{
    return (buscar_aresta(grafo, id1, id2) || buscar_aresta(grafo, id2, id1));
}

int contar_arestas(Vertice *grafo)
{
    int quant = 0;
    while(grafo)
    {
        Aresta *lista_adj = grafo->lista_adj;
        while(lista_adj)
        {
            quant++;
            lista_adj = lista_adj->prox;
        }
        grafo = grafo->prox;
    }
    return quant;
}

void adicionar_peso(Vertice *grafo, int orig, int dest, int peso)
{
    Aresta *aresta = buscar_aresta(grafo, orig, dest);
    
    if(aresta) aresta->peso = peso;
}

void dfs(Vertice *grafo, int id_inicio, int id_fim, int *caminho,  int nivel)
{
    if(buscar_vertice(grafo, id_inicio) == NULL)
    {
        printf("Vertice %d nao encontrado!\n", id_inicio);
        return;
    }
    Vertice *inicio = buscar_vertice(grafo, id_inicio);
    caminho[nivel] = id_inicio;
    inicio->visitado = 1;

    if(id_inicio == id_fim)
    {
        for(int i = 0; i <= nivel; i++)
        {
            printf("%d ", caminho[i]);
            if(i < nivel) printf("-> ");
        }
        printf("\n");
    } 
    else
    {
        Aresta *lista_adj = inicio->lista_adj;

        while(lista_adj)
        {
            Vertice *dest = buscar_vertice(grafo, lista_adj->dest);

            if(!dest->visitado)
                dfs(grafo, lista_adj->dest, id_fim, caminho, nivel + 1);

            lista_adj = lista_adj->prox;
        }
    }

    inicio->visitado = 0;
}

void imprimir_caminhos(Vertice *grafo, int id_inicio, int id_fim)
{
    int *caminho = malloc(contar_vertice(grafo) * sizeof(int));

    if(!caminho)
    {
        printf("Falha ao alocar memoria!\n");
        return;
    }

    printf("Caminhos de %d para %d:\n", id_inicio, id_fim);
    dfs(grafo, id_inicio, id_fim, caminho, 0);

    free(caminho);
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
                    printf("%d(%d) -> ", lista_adj->dest, lista_adj->peso);
                } else {
                    printf("%d(%d)", lista_adj->dest, lista_adj->peso); 
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
    inserir_aresta(&grafo, 6, 2);
    inserir_aresta(&grafo, 21, 10);
    inserir_aresta(&grafo, 2, 10);
    inserir_aresta(&grafo, 10, 3);
    inserir_aresta(&grafo, 3, 4);
    inserir_aresta(&grafo, 2, 4);
    inserir_aresta(&grafo, 4, 6);

    imprimir_caminhos(grafo, 6, 4);

    adicionar_peso(grafo, 6, 21, 5);

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
