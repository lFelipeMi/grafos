#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estruturas
typedef struct Aresta {
    int id;                 // ID do vértice adjacente
    struct Aresta *prox;    // Próxima aresta
} Aresta;

typedef struct Vertice {
    int id;                 // ID do vértice
    char cond;              // Condição do vértice (A, B, C, D, etc.)
    Aresta *lista;          // Lista de adjacências
    struct Vertice *prox;   // Próximo vértice
} Vertice;

char buscar(Vertice *inicio, int id) {
    while (inicio) {
        if (inicio->id == id) {
            return inicio->cond;  // Retorna a condição do vértice
        }
        inicio = inicio->prox;
    }
    return '\0';  // Retorna '\0' se não encontrar o vértice
}

void inserir_Aresta(Vertice *inicio, int id_origem, int id_destino) {
    while (inicio && inicio->id != id_origem) {
        inicio = inicio->prox;
    }

    if (inicio) {
        Aresta *nova = (Aresta *)malloc(sizeof(Aresta));
        nova->id = id_destino;
        nova->prox = inicio->lista;
        inicio->lista = nova;
    }
}

void inserir_Vertice(Vertice **inicio, int id, char cond) {
    Vertice *novo = (Vertice *)malloc(sizeof(Vertice));
    novo->id = id;
    novo->cond = cond;
    novo->lista = NULL;
    novo->prox = *inicio;
    *inicio = novo;
}

void validar_busca(Vertice *grafo) {
    while (grafo) {
        Aresta *adj = grafo->lista;
        while (adj) {
            char cond = buscar(grafo, adj->id);
            if (cond == '\0') {
                printf("Erro: Condição não encontrada para vértice %d em aresta (%d -> %d)\n",
                       adj->id, grafo->id, adj->id);
            }
            adj = adj->prox;
        }
        grafo = grafo->prox;
    }
}

void ler_Grafo(Vertice **grafo) {
    FILE *p = fopen("listaadjacencia.csv", "r");
    if (!p) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[256];
    char *token;

    // Primeira passagem: Adicionar vértices
    while (fgets(linha, sizeof(linha), p)) {
        int id1;
        char cond1;
        token = strtok(linha, ",");
        
        if (token && sscanf(token, "%d", &id1) == 1) {
            token = strtok(NULL, ",");
            if (token && sscanf(token, "%c", &cond1) == 1) {
                inserir_Vertice(grafo, id1, cond1);
            }
        }
    }

    rewind(p); // Segunda passagem: Adicionar arestas

    while (fgets(linha, sizeof(linha), p)) {
        int id1, id2;
        token = strtok(linha, ",");
        
        if (token && sscanf(token, "%d", &id1) == 1) {
            strtok(NULL, ","); // Ignora o campo da condição
            while ((token = strtok(NULL, ",")) != NULL) {
                if (sscanf(token, "%d", &id2) == 1) {
                    inserir_Aresta(*grafo, id1, id2);
                }
            }
        }
    }

    fclose(p);
}

void imprimir_Grafo(Vertice *grafo) {
    printf("-------- Lista de Adjacências --------\n");
    while (grafo) {
        printf("Vértice %d [%c]:", grafo->id, grafo->cond);
        Aresta *adj = grafo->lista;
        while (adj) {
            printf(" -> %d [%c]", adj->id, buscar(grafo, adj->id));
            adj = adj->prox;
        }
        printf("\n");
        grafo = grafo->prox;
    }
    printf("----------------- FIM ----------------\n");
}

int main() {
    Vertice *grafo = NULL;

    ler_Grafo(&grafo);
    imprimir_Grafo(grafo);
    validar_busca(grafo);

    return 0;
}

