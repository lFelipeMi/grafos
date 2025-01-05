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

void liberar_caminho(Caminho *caminho);
Caminho* iniciar_caminho();
void inserir_inicio(Caminho *caminho, int id, int peso);
void inserir_fim(Caminho *caminho, int id, int peso);
void inserir_ordenado(Caminho *caminho, int id, int peso);
void remover_caminho(Caminho *caminho, int id);
void remover_fim(Caminho *caminho);
No* buscar_caminho(Caminho *caminho, int id);
void imprimir_caminho(Caminho *caminho);

#endif
