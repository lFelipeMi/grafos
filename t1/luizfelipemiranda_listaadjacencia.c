//Nome: Luiz Felipe Miranda // Turma 5
//Eng. da computação

/* Informações para realização
A - sem mascara, sem inf (branco)
B - com mascara, sem inf (verde)
C - com mascara, com inf (laranaja)
D - sem mascara, com inf (vermelho)

s infecção; chance =  0
infecção; chance = 100
Uma mascara; chance /= 2

    C   <->   B  <-> D
já inf  <-> p50% <-> já inf
Não há soma de probabilidade caso um individuo sem inf entre em
contato com mais de um individuo inf. A maior probabilidade deve
ser considerada.

  B <->    A    <-> D
p0% <->  p100%  <-> já inf
probabilidade != de estar infectado, logo não altera individuos não 
relacionados
*/

//  ler os valores da lista de adjacências de um arquivo CSV.

//  gravar as probabilidades de infecção de cada individuo,
//  um por linha, em um arquivo texto.

//  Criação da lista de adjacências através de alocação dinâmica.

//  Cálculo da probabilidade de cada individuo de se infectar.

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
/*  condicao:
A - sem mascara, sem inf
B - com mascara, sem inf
C - com mascara, com inf
D - sem mascara, com inf
*/
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
    gravar_probabilidades(*grafo);
    printf("Leitura do arquivo concluída.\n");
}


int main() {
    Vertice *grafo = NULL;

    ler_Grafo(&grafo);
    liberar_Grafo(grafo);

    return 0;
}
