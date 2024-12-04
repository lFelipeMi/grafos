//Nome: Luiz Felipe Miranda // Turma: 5
//Curso: Eng. da computacao

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct aresta 
{
    char id;
    struct aresta *prox;
} Aresta;

typedef struct vertice 
{
    char id; // De A ate Z
    int cond;
    Aresta *lista;
    struct vertice *prox;
} Vertice;
/*  condicoes:
0 - s/ masc, s/ inf -> 0%, 50%, 100% de ser inf
1 - c/ masc, s/ inf -> 0%, 25%, 50% de ser inf
2 - c/ masc, c/ inf -> 25% ou 50% de infectar
3 - s/ masc, c/ inf -> 50% ou 100% de infectar
*/

/*
Percorre a lista de vertices e suas respectivas listas de
adjacencias, liberando a memoria de cada estrutura.
*/
void liberar_Grafo(Vertice *grafo) 
{
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

int verifica_vertice(Vertice *lista, char id) 
{
    while (lista && lista->id != id)
        lista = lista->prox;
    return lista != NULL;
}

void inserir_Vertice(Vertice **vertices, char id, int cond) 
{
    // Garante que o id seja valido, ou seja, uma letra maiuscula
    if (id < 65 || id > 90) 
    {
        printf("ID deve ser uma letra válida!\n");
        return;
    }

    // Verifica se o vertice existe, evitando duplicacao
    if (verifica_vertice(*vertices, id)) 
    {
        printf("Vértice com ID %c ja existe!\n", id);
        return;
    }

    Vertice *novo = malloc(sizeof(Vertice));
    if (novo) {
        novo->id = id;
        novo->cond = cond;
        novo->lista = NULL;
        novo->prox = NULL;
        // Se a lista de vertices for nula, ou o elemento for o menor, insere no inicio.
        if (*vertices == NULL || id < (*vertices)->id) 
        {
            novo->prox = *vertices;
            *vertices = novo;
        } 
        else // Senão, percorremos a lista procurando o seu lugar, no meio ou final
        {
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

int existe_Aresta(Aresta *lista, char id) {
    while (lista) {
        if (lista->id == id) {
            return 1; // Aresta já existe
        }
        lista = lista->prox;
    }
    return 0; // Aresta não existe
}

// Metodos diferentes de insercao para praticar
void inserir_Aresta(Vertice *lista, char id1, char id2) {
    // Verifica se o vertice existe antes de inserir a ligacao
    if (verifica_vertice(lista, id1) && verifica_vertice(lista, id2)) {
        // Encontrar o vértice id1 na lista de vertices
        while (lista && lista->id != id1) {
            lista = lista->prox;
        }

        if (lista) {  // Se o vértice foi encontrado
            // Verificar se a aresta id1 -> id2 já existe
            if (!existe_Aresta(lista->lista, id2)) {
                Aresta *nova = malloc(sizeof(Aresta));
                if (nova) {
                    nova->id = id2;

                    // Inserir a aresta de forma ordenada
                    Aresta **p = &lista->lista;
                    while (*p && (*p)->id < id2) {
                    }

                    // Inserir a nova aresta na posição correta, inicio, meio ou fim
                    nova->prox = *p;
                    *p = nova;
                } else {
                    printf("Erro ao alocar memoria para a aresta!\n");
                }
            }
        }
    } else {
        printf("Um ou ambos os vertices %c ou %c nao existem!\n", id1, id2);
    }
}

// Gambiarra pra inserir bidirecional //////////TA ERRADO??
void inserir_bidirecional(Vertice **lista, char id1, char id2) {
    inserir_Aresta(*lista, id1, id2);
    inserir_Aresta(*lista, id2, id1);
}

// Como nao armazenamos a condicao do vertice na struct aresta essa funcao busca a condicao na lista de vertices
int buscar(const Vertice *inicio, char id) {
    while (inicio) {
        if (inicio->id == id)
            return inicio->cond;
        inicio = inicio->prox;
    }
    return -1;  // Retorna -1 se nao encontrado
}

// Dois sem inf = 0
// Sem mascara -> inf = 100
// Cada mascara reduz a probabilidade pela metade
int calculos_probabilidade(int cond1, int cond2) {
    if (cond1 == 2 || cond1 == 3) 
        return 100;
    if (((cond1 == 0) && (cond2 == 1)) || ((cond1 == 1) && (cond2 == 0))) 
        return 0;
    if (((cond1 == 0) || (cond1 == 1)) && (cond1 == cond2))
        return 0;

    if (cond1 == 0) {
        if (cond2 == 2) 
            return 50;
        if (cond2 == 3)   
            return 100;
    }

    if (cond1 == 1) {
        if (cond2 == 2) 
            return 25;
        if (cond2 == 3) 
            return 50;
    }

    return -1;  // Caso invalido... vai que
}

// Aqui queremos apenas a pior probabilidade de um individuo ser infectado, de acordo com suas conexoes, essa funcao retorna o id de um individuo com a pior condicao na lista.
// 0 < 1 < 2 < 3
int encontra_pior(Vertice *grafo, Aresta *lista) {
    int maior = lista->id;
    Vertice *lista_temp = grafo;
    char pior_cond = buscar(lista_temp, maior);
    
    lista = lista->prox;
    // Se encontrarmos um individuo com condicao 3 temos certeza de que essa eh a pior condicao possivel e por isso paramos o laco
    while (lista && (pior_cond != 3)) {
        char cond_atual = buscar(lista_temp, lista->id);

        if (cond_atual > pior_cond) {
            maior = lista->id;
            pior_cond = cond_atual;
        }
        
        lista = lista->prox;
    }

    return maior;
}

///////////////// FUNCOES PROPOSTAS NAS ORIENTACOES /////////////////////////
/*
1) Desenvolva uma fucao em C usando de passagem de parametros 
por referencia que leia os valores da lista de adjacencias de
um arquivo CSV (Valores separados por virgula)
*/
void ler_Grafo(Vertice **grafo) {
    FILE *p = fopen("t1_b1_listaadjacencia_epidemia.csv", "r");
    if (p == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), p)) {
        char id1, id2;
        int cond1, cond2;

        // Remove o caractere '\n' no final da linha, se existir
        linha[strcspn(linha, "\n")] = '\0';

        // Lê o formato esperado: ID1,COND1,ID2,COND2 
        // Caso nao seja valido o formato pulamos pra proxima
        if (sscanf(linha, "%c,%d,%c,%d", &id1, &cond1, &id2, &cond2) == 4) {
            if (!verifica_vertice(*grafo, id1)) {
                inserir_Vertice(grafo, id1, cond1);
            }
            if (!verifica_vertice(*grafo, id2)) {
                inserir_Vertice(grafo, id2, cond2);
            }
            inserir_bidirecional(grafo, id1, id2);
        } else {
            printf("Linha ignorada: formato invalido (%s)\n", linha);
        }
    }

    fclose(p);
    printf("Leitura do arquivo concluida.\n");
}

/*
2) Desenvolva uma funcao em C usando  de passagem de parametros 
por referencia que grave as probabilidades de infeccao de cada 
individuo, uma relacao por linha, em um arquivo texto.
*/
void gravar_1po1(Vertice *grafo) {
    FILE *p = fopen("luiz_lima_listaadjacencia_epidemia.1por1.saida", "w");
    if (!p) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vertice *lista_temp1 = grafo;

    while (lista_temp1) {
        if (lista_temp1->lista) {
            Aresta *lista = lista_temp1->lista;

            while (lista) {
                // Verifica se o ID do vertice origem eh menor que o da aresta, evitando duplicacaoo na impressao do arquivo
                // Tirar duvida se eh isso mesmo... Parece meio errado já que relacoes relevantes estao sendo deixadas de fora
                if (lista_temp1->id < lista->id) {
                    int probabilidade = calculos_probabilidade(
                        lista_temp1->cond, buscar(grafo, lista->id));
                    fprintf(p, "%c -> %c: %d%%\n",
                            lista_temp1->id, lista->id, probabilidade);
                }

                lista = lista->prox;
            }
        }
        lista_temp1 = lista_temp1->prox;
    }

    fclose(p);
}

/*
3) Desenvolva uma funcao em C usando de passgem de parametros por referencia que calcule atraves da lista de adjacencias, criada dinamicamente, a maior probabilidade de cada individuo se infectar com a EPIDEMIA, levando em consideracao somente as adjacencias  dele  naquele exato momento.
*/
void gravar_total(Vertice *grafo) {
    FILE *p = fopen("luiz_lima_listaadjacencia_epidemia.total.saida", "w");
    if (!p) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vertice *lista_temp1 = grafo;

    while (lista_temp1) {
        if (lista_temp1->lista) {
            char pior = encontra_pior(grafo, lista_temp1->lista);
            int probabilidade = calculos_probabilidade(lista_temp1->cond, buscar(grafo, pior));
            fprintf(p, "%c: %d%%\n", lista_temp1->id, probabilidade);
        }
        lista_temp1 = lista_temp1->prox;
    }

    fclose(p);
}

int main() {
    Vertice *grafo = NULL;

    ler_Grafo(&grafo);
    gravar_1po1(grafo);
    gravar_total(grafo);
    liberar_Grafo(grafo);

    return 0;
}
