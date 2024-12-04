#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void liberar_Grafo(Vertice *grafo) {
    while (grafo) {
        Aresta *adj = grafo->lista;
        while (adj) {
            Aresta *aux = adj;
            adj = adj->prox;
            free(aux);
        }
        Vertice *temp = grafo;
        grafo = grafo->prox;
        free(temp);
    }
}

// Verifica se o vértice existe
int verifica_vertice(Vertice *lista, int id) {
    while (lista && lista->id != id)
        lista = lista->prox;
    return lista != NULL;
}

// Função para inserir vértices na lista de vértices de forma ordenada
void inserir_Vertice(Vertice **vertices, int id, char cond) {
    if (id <= 0) {
        printf("ID deve ser maior que 0!\n");
        return;
    }
    if (verifica_vertice(*vertices, id)) {
        printf("Vértice com ID %d já existe!\n", id);
        return;
    }

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

void remover_Vertice(Vertice **grafo, int id) {
    if (*grafo == NULL) {
        printf("Grafo vazio!\n");
        return;
    }

    Vertice *temp = *grafo;
    Vertice *anterior = NULL;

    // Encontrar o vértice a ser removido
    while (temp && temp->id != id) {
        anterior = temp;
        temp = temp->prox;
    }

    if (temp == NULL) {
        printf("Vertice %d nao encontrado!\n", id);
        return;
    }

    // Remover arestas que apontam para o vértice a ser removido
    Vertice *atual = *grafo;
    while (atual) {
        Aresta *adj = atual->lista;
        Aresta *anteriorAdj = NULL;

        while (adj) {
            if (adj->id == id) {
                if (anteriorAdj == NULL) {
                    atual->lista = adj->prox;
                } else {
                    anteriorAdj->prox = adj->prox;
                }
                free(adj);
                break;
            }
            anteriorAdj = adj;
            adj = adj->prox;
        }

        atual = atual->prox;
    }

    // Remover o vértice e sua lista de adjacências
    if (anterior == NULL) {
        *grafo = temp->prox;
    } else {
        anterior->prox = temp->prox;
    }

    Aresta *adj = temp->lista;
    while (adj) {
        Aresta *aux = adj;
        adj = adj->prox;
        free(aux);
    }

    free(temp);
    printf("Vertice %d removido!\n", id);
}

// Função para inserir aresta
void inserir_Aresta(Vertice *lista, int id1, int id2) {
    if (lista == NULL) {
        printf("Impossível inserir aresta, grafo nulo\n");
        return;
    }

    if (verifica_vertice(lista, id1) && verifica_vertice(lista, id2)) {
        while (lista->id != id1)
            lista = lista->prox;

        Aresta *nova = malloc(sizeof(Aresta));
        if (nova) {
            nova->id = id2;
            nova->prox = NULL;

            if (lista->lista == NULL || lista->lista->id > id2) {
                nova->prox = lista->lista;
                lista->lista = nova;
            } else {
                Aresta *temp = lista->lista;
                while (temp->prox && (temp->prox->id < id2)) {
                    temp = temp->prox;
                }
                nova->prox = temp->prox;
                temp->prox = nova;
            }
        } else {
            printf("Erro ao alocar memória para a aresta!\n");
        }
    } else {
        printf("Um ou ambos os vértices %d ou %d não existem!\n", id1, id2);
    }
}

void inserir_Aresta_Bidirecional(Vertice *lista, int id1, int id2) {
    inserir_Aresta(lista, id1, id2);
    inserir_Aresta(lista, id2, id1);
}


void remover_Aresta(Vertice *grafo, int id1, int id2) {
    if (grafo == NULL) {
        printf("Grafo vazio!\n");
        return;
    }

    while (grafo && grafo->id != id1)
        grafo = grafo->prox;

    if (grafo == NULL) {
        printf("Vertice %d nao encontrado!\n", id1);
        return;
    }

    Aresta *adj = grafo->lista;
    Aresta *anterior = NULL;

    while (adj && adj->id != id2) {
        anterior = adj;
        adj = adj->prox;
    }

    if (adj == NULL) {
        printf("Aresta %d -> %d nao encontrada!\n", id1, id2);
        return;
    }

    if (anterior == NULL) {
        grafo->lista = adj->prox;
    } else {
        anterior->prox = adj->prox;
    }

    free(adj);
    printf("Aresta %d -> %d removida!\n", id1, id2);
}


// Função para ler o grafo do arquivo CSV
void ler_Grafo(Vertice **grafo) {
    FILE *p = fopen("listaadjacencia.csv", "r");
    if (p == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[256];
    int linha_atual = 1; // Para rastrear a linha que está sendo processada

    while (fgets(linha, sizeof(linha), p)) {
        int id1, id2;
        char cond1, cond2;

        // Remove o caractere '\n' no final da linha, se existir
        linha[strcspn(linha, "\n")] = '\0';

        // Validar a linha
        if (sscanf(linha, "%d,%c,%d,%c", &id1, &cond1, &id2, &cond2) == 4) {
            // Certifique-se de que os IDs são positivos e os caracteres de condição são válidos
            if (id1 > 0 && id2 > 0 && (isalpha(cond1) && isalpha(cond2))) {
                if (!verifica_vertice(*grafo, id1)) {
                    inserir_Vertice(grafo, id1, cond1);
                }
                if (!verifica_vertice(*grafo, id2)) {
                    inserir_Vertice(grafo, id2, cond2);
                }
                inserir_Aresta(*grafo, id1, id2);
            } else {
                printf("Linha %d ignorada: IDs ou condições inválidos (%s)\n", linha_atual, linha);
            }
        } else {
            printf("Linha %d ignorada: formato inválido (%s)\n", linha_atual, linha);
        }

        linha_atual++;
    }

    fclose(p);
    printf("Leitura do arquivo concluída.\n");
}


char buscar(Vertice *inicio, int id) {
    // Sempre começa do início da lista de vértices
    while (inicio && inicio->id != id)
        inicio = inicio->prox;
    if (inicio)
        return inicio->cond;
    return '\0';  // Retorna \0 se não encontrado
}
// Função para imprimir o grafo
void imprimir_Grafo(Vertice *vertices) {
    printf("-------- Lista de Adjacências --------\n");
    Vertice *inicio = vertices; // Guarda o início da lista
    while (vertices) {
        printf("Vértice %d [%c]:", vertices->id, vertices->cond);
        Aresta *adj = vertices->lista;
        while (adj) {
            printf(" -> %d [%c]", adj->id, buscar(inicio, adj->id));
            adj = adj->prox;
        }
        printf("\n");
        vertices = vertices->prox;
    }
    printf("----------------- FIM ----------------\n");
}

// Função para gravar o grafo no formato especificado em "saida.txt"
void gravar_Grafo(Vertice *grafo) {
    FILE *p = fopen("saida.txt", "w");
    if (p == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Vertice *origem = grafo;
    while (origem) {
        Aresta *adj = origem->lista;
        while (adj) {
            // Buscar condição do vértice de destino
            char cond_destino = buscar(grafo, adj->id);
            if (cond_destino != '\0') {
                // Gravar no formato: origem,cond_origem,destino,cond_destino
                fprintf(p, "%d,%c,%d,%c\n", origem->id, origem->cond, adj->id, cond_destino);
            }
            adj = adj->prox;
        }
        origem = origem->prox;
    }

    fclose(p);
    printf("Grafo gravado em 'saida.txt' no formato especificado.\n");
}


int main(){
    Vertice *grafo = NULL;
    int id1, id2, opcao;
    char cond;

    ler_Grafo(&grafo);
    do{
        printf("\n\tSelecione a opcao desejada:\n\t  1 - Inserir Individuo (vertice)\n\t  2 - Inserir interacao (aresta)\n\t  3 - Remover Individuo (vertice)\n\t  4 - Remover interacao (aresta)\n\t  5 - Imprimir lista de adjacencias\n\t  6 - Gravar lista de adjacencias\n\t  7 - Ler Grafo\n\t  0 - SAIR\n\tOpcao selecionada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite um ID e condicao do individuo: ");
            scanf("%d %c", &id1, &cond);
            inserir_Vertice(&grafo, id1, cond);
            break;
        case 2:
            printf("Digite os ID's dos individuos: ");
            scanf(" %d %d", &id1, &id2);
            inserir_Aresta_Bidirecional(grafo, id1, id2);
            break;
        case 3:
            printf("Digite o ID do individuo a ser removido: ");
            scanf("%d", &id1);
            remover_Vertice(&grafo, id1);
            break;
        case 4:
            printf("Digite os IDs dos individuos para remover a interacao: ");
            scanf("%d %d", &id1, &id2);
            remover_Aresta(grafo, id1, id2);
            remover_Aresta(grafo, id2, id1);
            break;
        case 5:
            imprimir_Grafo(grafo);
            break;
        case 6:
            gravar_Grafo(grafo);
            break;
        case 7:
            ler_Grafo(&grafo);
            break;
        default:
            if(opcao != 0)
                printf("Opcao invalida");
            break;
        }
    } while(opcao != 0);


    gravar_Grafo(grafo);
    liberar_Grafo(grafo);
    printf("Encerrando programa...\n");
    return 0;
}
