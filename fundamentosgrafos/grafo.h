#ifndef GRAFO_H
#define GRAFO_H

typedef struct aresta {
    int orig;
    int dest;
    int percorrida;
    struct aresta *prox;
    struct aresta *ant;
} Aresta;

typedef struct vertice {
    int id;
    int grau_entrada;
    int grau_saida;
    int visitado;
    Aresta *lista_adj;
    struct vertice *prox;
} Vertice;

void liberar_grafo(Vertice *grafo);
void inserir_vertice(Vertice **grafo, int id);
void remover_vertice(Vertice **grafo, int id);
Vertice *buscar_vertice(Vertice *grafo, int id);
int contar_vertice(Vertice *grafo);
void inserir_aresta(Vertice **grafo, int orig, int dest);
void remover_aresta(Vertice **grafo, int orig, int dest);
Aresta *buscar_aresta(Vertice **grafo, int orig, int dest);
int contar_arestas(Vertice *grafo);
void imprimir_grafo(Vertice *grafo);

#endif 
