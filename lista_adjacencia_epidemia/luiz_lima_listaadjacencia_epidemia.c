//Nome: Luiz Felipe Miranda // Turma: 5
//Curso: Eng. da computacao

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>

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

void liberar_Grafo(Vertice *grafo) 
{
    while (grafo != NULL) 
    {
        Aresta *adj = grafo->lista;
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

int verificar_vertice(Vertice *lista, char id) 
{
    while (lista && lista->id != id)
        lista = lista->prox;
    return lista != NULL;
}

void inserir_Vertice(Vertice **vertices, char id, int cond) 
{
    if (id < 65 || id > 90) 
    {
        printf("ID deve ser uma letra válida!\n");
        return;
    }

    if (verificar_vertice(*vertices, id)) 
    {
        printf("Vértice com ID %c ja existe!\n", id);
        return;
    }

    Vertice *novo = malloc(sizeof(Vertice));
    if (novo) 
    {
        novo->id = id;
        novo->cond = cond;
        novo->lista = NULL;
        novo->prox = NULL;
        if (*vertices == NULL || id < (*vertices)->id) 
        {
            novo->prox = *vertices;
            *vertices = novo;
        } 
        else 
        {
            Vertice *temp = *vertices;
            while (temp->prox && temp->prox->id < id) 
            {
                temp = temp->prox;
            }
            novo->prox = temp->prox;
            temp->prox = novo;
        }
    } else
        printf("Erro ao alocar memória!\n");
}

int verificar_Aresta(Aresta *lista, char id) 
{
    while (lista) 
    {
        if (lista->id == id)
        {
            return 1; // Aresta já existe
        }
        lista = lista->prox;
    }
    return 0; // Aresta não existe
}

// Metodos diferentes de insercao apenas para praticar
void inserir_Aresta(Vertice *lista, char id1, char id2) 
{
    if (verificar_vertice(lista, id1) && verificar_vertice(lista, id2)) 
    {
        while (lista && lista->id != id1)
            lista = lista->prox;
        

        if (lista) 
        {
            if (!verificar_Aresta(lista->lista, id2)) 
            {
                Aresta *nova = malloc(sizeof(Aresta));
                if (nova) 
                {
                    nova->id = id2;

                    Aresta **p = &lista->lista;
                    while (*p && (*p)->id < id2)
                        p = &(*p)->prox; 
                    nova->prox = *p;
                    *p = nova;
                } else  
                    printf("Erro ao alocar memória para aresta.");
            }
        }
    } else
        printf("Um ou ambos os vertices %c ou %c nao existem!\n", id1, id2);
}

// "Gambiarra" pra inserir aresta nao direcionada 
void inserir_aresta_simples(Vertice **lista, char id1, char id2) 
{
    inserir_Aresta(*lista, id1, id2);
    inserir_Aresta(*lista, id2, id1);
}

int buscar_condicao(const Vertice *inicio, char id) 
{
    while (inicio) 
    {
        if (inicio->id == id)
            return inicio->cond;
        inicio = inicio->prox;
    }
    return -1;
}

int calcular_probabilidade(int cond1, int cond2) 
{
    if (cond1 == 2 || cond1 == 3) 
        return 100;
    if (((cond1 == 0) && (cond2 == 1)) || ((cond1 == 1) && (cond2 == 0))) 
        return 0;
    if (((cond1 == 0) || (cond1 == 1)) && (cond1 == cond2))
        return 0;

    if (cond1 == 0) 
    {
        if (cond2 == 2) 
            return 50;
        if (cond2 == 3)   
            return 100;
    }

    if (cond1 == 1) 
    {
        if (cond2 == 2) 
            return 25;
        if (cond2 == 3) 
            return 50;
    }

    return -1;  // Caso invalido... vai que
}
// Melhor pro pior
// 0 < 1 < 2 < 3
int encontrar_pior(Vertice *grafo, Aresta *lista) 
{
    int id_pior = lista->id;
    Vertice *lista_temp = grafo;
    char pior_cond = buscar_condicao(lista_temp, id_pior);
    
    lista = lista->prox;
    while (lista && (pior_cond != 3)) 
    {
        char cond_atual = buscar_condicao(lista_temp, lista->id);

        if (cond_atual > pior_cond) 
        {
            id_pior = lista->id;
            pior_cond = cond_atual;
        }
        
        lista = lista->prox;
    }

    return id_pior;
}

void gerarTimestamp(char *buffer, size_t tamanho) 
{
    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, tamanho, "%Y%m%d%H%M%S%z", info);
}

///////////////// FUNCOES PROPOSTAS NAS ORIENTACOES /////////////////////////
/*
1) Desenvolva uma fucao em C usando de passagem de parametros 
por referencia que leia os valores da lista de adjacencias de
um arquivo CSV (Valores separados por virgula)
*/
void ler_grafo(Vertice **grafo) 
{
    FILE *p = fopen("t1_b1_listaadjacencia_epidemia.csv", "r");
    if (p == NULL) 
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), p)) 
    {
        char id1, id2;
        int cond1, cond2;

        linha[strcspn(linha, "\n")] = '\0';

        // Lê o formato esperado: ID1,COND1,ID2,COND2 
        // Caso nao seja valido o formato pulamos pra proxima
        if (sscanf(linha, "%c,%d,%c,%d", &id1, &cond1, &id2, &cond2) == 4) {
            if (!verificar_vertice(*grafo, id1))
                inserir_Vertice(grafo, id1, cond1);
            
            if (!verificar_vertice(*grafo, id2))
                inserir_Vertice(grafo, id2, cond2);
            
            inserir_aresta_simples(grafo, id1, id2);
        } else
            printf("Linha ignorada: formato invalido (%s)\n", linha);

    }
    fclose(p);
    printf("Leitura do arquivo concluida.\n");
}

/*
2) Desenvolva uma funcao em C usando  de passagem de parametros 
por referencia que grave as probabilidades de infeccao de cada 
individuo, uma relacao por linha, em um arquivo texto.
*/void gravar_1po1(Vertice *grafo) 
{
    char timestamp[20];
    char nomeArquivo[100];
    gerarTimestamp(timestamp, 20);
    snprintf(nomeArquivo, sizeof(nomeArquivo), "luiz_lima_listaadjacencia_epidemia.1por1.saida.%s", timestamp);

    FILE *p = fopen(nomeArquivo, "w");
    if (!p) 
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    Vertice *vertice_atual = grafo;

    while (vertice_atual) 
    {
        Aresta *aresta_atual = vertice_atual->lista;

        while (aresta_atual) 
        {
            if (vertice_atual->id < aresta_atual->id) 
            {
                int cond_alvo = buscar_condicao(grafo, aresta_atual->id);
                if (cond_alvo != -1)
                {
                    int probabilidade = calcular_probabilidade(vertice_atual->cond, cond_alvo);
                    fprintf(p, "%c -> %c: %d%%\n", vertice_atual->id, aresta_atual->id, probabilidade);
                }
                else 
                    printf("Erro: Não foi possível encontrar o vértice %c para cálculo da probabilidade.\n", aresta_atual->id);
            }
            aresta_atual = aresta_atual->prox;
        }

        vertice_atual = vertice_atual->prox;
    }

    fclose(p);
}
/*
3) Desenvolva uma funcao em C usando de passgem de parametros por referencia que calcule atraves da lista de adjacencias, criada dinamicamente, a maior probabilidade de cada individuo se infectar com a EPIDEMIA, levando em consideracao somente as adjacencias  dele  naquele exato momento.
*/
void gravar_total(Vertice *grafo) 
{    
    char timestamp[20];
    char nomeArquivo[100];
    gerarTimestamp(timestamp, 20);
    snprintf(nomeArquivo, sizeof(nomeArquivo), "luiz_lima_listaadjacencia_epidemia.total.saida.%s", timestamp);

    FILE *p = fopen(nomeArquivo, "w");
    if (!p) 
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vertice *lista_temp1 = grafo;

    while (lista_temp1)
    {
        if (lista_temp1->lista) 
        {
            char pior = encontrar_pior(grafo, lista_temp1->lista);
            int probabilidade = calcular_probabilidade(lista_temp1->cond, buscar_condicao(grafo, pior));
            fprintf(p, "%c: %d%%\n", lista_temp1->id, probabilidade);
        }
        lista_temp1 = lista_temp1->prox;
    }

    fclose(p);
}

int main() {
    Vertice *grafo = NULL;

    ler_grafo(&grafo);
    gravar_1po1(grafo);
    gravar_total(grafo);
    liberar_Grafo(grafo);

    return 0;
}
