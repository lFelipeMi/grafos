#ifndef LISTAC_H
#define LISTAC_H

typedef struct no {
    int id;
    int peso;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int tam;
} Caminho;

void liberar(Caminho *caminho);
void iniciar_caminho(Caminho *caminho);
void inserir_inicio(Caminho *caminho, int id, int peso);
void inserir_fim(Caminho *caminho, int id, int peso);
void inserir_ordenado(Caminho *caminho, int id, int peso);
void remover(Caminho *caminho, int id);
No* buscar(Caminho *caminho, int id);
void imprimir(Caminho caminho);

#endif
