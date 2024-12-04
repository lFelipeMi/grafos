#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aresta {
    char id;
    struct aresta *prox;
} Aresta;

typedef struct vertice {
    char id; // De A ate Z
    int cond;
    Aresta *lista;
    struct vertice *prox;
} Vertice;

void imprimir_probabilidades(Vertice *grafo) {
    Vertice *lista_temp = grafo;
    printf("------ Tabela de Probabilidades ------\n");
    while (grafo) {
        if (grafo->lista) {
            int pior = encontra_pior(grafo, grafo->lista);
            char piorCond = buscar(lista_temp, pior);
            printf("%c [%d] -> %c [%d]: %d%%\n", 
                   grafo->id, grafo->cond, pior, piorCond, 
                   calculos_probabilidade(grafo->cond, piorCond));
        }
        grafo = grafo->prox;
    }
    printf("------------------ FIM -----------------\n");
}

void gravar_probabilidades(Vertice *grafo) {
    FILE *p = fopen("saida_teste.txt", "w");
    if (!p) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vertice *lista_temp1 = grafo;

    fprintf(p, "----------------- Todos casos -------------------\n");
    while (lista_temp1) {
        if (lista_temp1->lista) {
            Aresta *lista = lista_temp1->lista;
            while (lista) {
                int probabilidade = calculos_probabilidade(
                    lista_temp1->cond, buscar(grafo, lista->id));
                fprintf(p, "%c [%d] -> %c [%d]: %d%%\n",
                        lista_temp1->id, lista_temp1->cond,
                        lista->id, buscar(grafo, lista->id),
                        probabilidade);
                lista = lista->prox;
            }
        }
        lista_temp1 = lista_temp1->prox;
    }

    // Calculo mais "pior probabilidade":
    lista_temp1 = grafo;
    fprintf(p, "\n\n\n----------------- Piores casos -------------------\n");
    while (lista_temp1) {
        if (lista_temp1->lista) {
            char pior = encontra_pior(lista_temp1, lista_temp1->lista);
            int probabilidade = calculos_probabilidade(
                lista_temp1->cond, buscar(grafo, pior));
            fprintf(p, "%c [%d] -> %c [%d]: %d%%\n",
                    lista_temp1->id, lista_temp1->cond,
                    pior, buscar(grafo, pior),
                    probabilidade);
        }
        lista_temp1 = lista_temp1->prox;
    }

    fclose(p);
} //acima de gravar todos