#include <stdio.h>
#include <stdlib.h>
#include  <string.h>

typedef struct aresta {
    int id;
    struct aresta *prox;
} Aresta;

typedef struct vertice {
    int id;
    char cond;
    Aresta *lista;
    struct vertice *prox;
} Vertice;

// Inserir vertice de maneira ordenada
void inserir_Vertice(Vertice **vertices, int id, char cond) {
    Vertice *novo = malloc(sizeof(Vertice));
    if (novo) {
        novo->id = id;
        novo->cond = cond;
        novo->lista = NULL;
        novo->prox = NULL;

        if (*vertices == NULL || id < (*vertices)->id) {
            novo->prox = *vertices;
            *vertices = novo;
        } else {
            Vertice *temp = *vertices;
            while (temp->prox && temp->prox->id < id) {
                temp = temp->prox;
            }
            novo->prox = temp->prox;
            temp->prox = novo;
        }
    } else {
        printf("Erro ao alocar memória!\n");
    }
}
// Verifica se o vértice existe
int verifica_vertice(Vertice *lista, int id) {
    while (lista && lista->id != id)
        lista = lista->prox;
    return lista != NULL;
}

int existe_Aresta(Aresta *lista, int id) {
    while (lista) {
        if (lista->id == id) {
            return 1; // Aresta já existe
        }
        lista = lista->prox;
    }
    return 0; // Aresta não existe
}

void inserir_Aresta(Vertice *lista, int id1, int id2) {
    if (verifica_vertice(lista, id1) && verifica_vertice(lista, id2)) {
        while (lista->id != id1)
            lista = lista->prox;

        if (!existe_Aresta(lista->lista, id2)) {
            Aresta *nova = malloc(sizeof(Aresta));
            if (nova) {
                nova->id = id2;
                nova->prox = lista->lista;
                lista->lista = nova;
            } else {
                printf("Erro ao alocar memória para a aresta!\n");
            }
        }
    } else {
        printf("Um ou ambos os vértices %d ou %d não existem!\n", id1, id2);
    }
}
// Como não armazenamos a condição do vertice na aresta essa funcao se faz necessario para buscar a condicao na lista de vertices.
char buscar(const Vertice *inicio, int id) {
    while (inicio) {
        if (inicio->id == id)
            return inicio->cond;
        inicio = inicio->prox;
    }
    return '\0';  // Retorna '\0' se não encontrado
}


void imprimir_Grafo(Vertice *grafo) {
    Vertice *lista_temp = grafo;
    printf("-------- Lista de Adjacências --------\n");
    while (grafo) {
        printf("Vértice %d [%c]:", grafo->id, grafo->cond);
        Aresta *adj = grafo->lista;
        while (adj) {
            printf(" -> %d [%c]", adj->id, buscar(lista_temp, adj->id));
            adj = adj->prox;
        }
        printf("\n");
        grafo = grafo->prox;
    }
    printf("----------------- FIM ----------------\n");
}

int calculos_probabilidade(char cond1, char cond2) {
    if (cond1 == 'C' || cond1 == 'D') 
        return 100;
    if (((cond1 == 'A') && (cond2 == 'B')) || ((cond1 == 'B') && (cond2 == 'A'))) 
        return 0;
    if(((cond1 == 'A') || (cond1 == 'B')) && (cond1 == cond2))
        return 0;

    if (cond1 == 'A') {
        if (cond2 == 'C') 
            return 50;
        if (cond2 == 'D')   
            return 100;
    }

    if (cond1 == 'B') {
        if (cond2 == 'C') 
            return 25;
        if (cond2 == 'D') 
            return 50;
    }

    return -1;  // Vai que...
}


// Como queremos apenas a pior probabilidade de um individuo ser infectado, de acordo com suas conexoes, essa funcao retorna o id de um individuo com a pior condicao na lista.
// A < B < C < D
int encontra_pior(Vertice *grafo, Aresta *lista) {
    int maior = lista->id;
    Vertice *lista_temp = grafo;
    char pior_cond = buscar(lista_temp, maior);
    
    lista = lista->prox;
    // Se encontrarmos um individuo com condicao 'D' temos certeza de que essa eh a pior condicao possivel e por isso paramos o laco.
    while (lista && (pior_cond != 'D')) {
        char cond_atual = buscar(lista_temp, lista->id);

        if (cond_atual > pior_cond) {
            maior = lista->id;
            pior_cond = cond_atual;
        }
        
        lista = lista->prox;
    }

    return maior;
}

void imprimir_probabilidades(Vertice *grafo) {
    Vertice *lista_temp = grafo;
    printf("------ Tabela de Probabilidades ------\n");
    while (grafo) {
        if (grafo->lista) {
            int pior = encontra_pior(grafo, grafo->lista);
            char piorCond = buscar(lista_temp, pior);
            printf("%d [%c] -> %d [%c]: %d%%\n", 
                   grafo->id, grafo->cond, pior, piorCond, 
                   calculos_probabilidade(grafo->cond, piorCond));
        }
        grafo = grafo->prox;
    }
    printf("------------------ FIM -----------------\n");
}

void gravar_probabilidades(Vertice *grafo) {
    FILE *p = fopen("saida.txt", "w");
    if (!p) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vertice *lista_temp1 = grafo;
    Vertice *lista_temp = grafo;

    fprintf(p, "----------------- Todos casos -------------------\n");
    while (lista_temp1) {
        if (lista_temp1->lista) {
            Aresta *lista = lista_temp1->lista;
            while (lista) {
                int pior = encontra_pior(lista_temp1, lista_temp1->lista);
                char piorCond = buscar(grafo, pior); // Corrigido para usar grafo completo
                fprintf(p, "%d [%c] -> %d [%c]: %d%%\n", 
                        lista_temp1->id, lista_temp1->cond, 
                        lista->id, buscar(grafo, lista->id), 
                        calculos_probabilidade(lista_temp1->cond, piorCond));
                lista = lista->prox;
            }
        }
        lista_temp1 = lista_temp1->prox;  // Avançar sem perder grafo original
    }

    // Reinicializar grafo para próximo loop
    lista_temp1 = grafo;

    fprintf(p, "\n\n\n----------------- Piores casos -------------------\n");
    while (lista_temp1) {
        if (lista_temp1->lista) {
            int pior = encontra_pior(lista_temp1, lista_temp1->lista);
            char piorCond = buscar(grafo, pior);
            fprintf(p, "%d [%c] -> %d [%c]: %d%%\n", 
                    lista_temp1->id, lista_temp1->cond, 
                    pior, piorCond, 
                    calculos_probabilidade(lista_temp1->cond, piorCond));
        }
        lista_temp1 = lista_temp1->prox;
    }

    fclose(p);    
}



// Função para ler o grafo do arquivo CSV
void ler_Grafo(Vertice **grafo) {
    FILE *p = fopen("listaadjacencia.csv", "r");
    if (p == NULL) {
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

    // Retorna ao início do arquivo para a segunda passagem
    rewind(p);

    // Segunda passagem: Adicionar arestas
    while (fgets(linha, sizeof(linha), p)) {
        int id1, id2;
        token = strtok(linha, ",");
        
        if (token && sscanf(token, "%d", &id1) == 1) {
            // Ignora o segundo campo (condição do vértice)
            token = strtok(NULL, ",");

            // Processa os vértices adjacentes e adiciona as arestas
            while ((token = strtok(NULL, ",")) != NULL) {
                if (sscanf(token, "%d", &id2) == 1) {
                    inserir_Aresta(*grafo, id1, id2);
                }
            }
        }
    }

    imprimir_Grafo(*grafo);
    imprimir_probabilidades(*grafo);
    gravar_probabilidades(*grafo);
    fclose(p);
}

int main() {
    Vertice *grafo = NULL;

    ler_Grafo(&grafo);

    return 0;
}
