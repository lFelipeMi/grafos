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

int verificar_vertice(Vertice *grafo, char id) 
{
    while (grafo && grafo->id != id)
        grafo = grafo->prox;
    return grafo != NULL;
}

void inserir_Vertice(Vertice **grafo, char id, int cond) 
{
    if (id < 65 || id > 90) 
    {
        printf("ID deve ser uma letra valida!\n");
        return;
    }

    if (verificar_vertice(*grafo, id)) 
    {
        printf("Vertice com ID %c ja existe!\n", id);
        return;
    }

    Vertice *novo = malloc(sizeof(Vertice));
    if (novo) 
    {
        novo->id = id;
        novo->cond = cond;
        novo->lista = NULL;
        novo->prox = NULL;
        if (*grafo == NULL || id < (*grafo)->id) 
        {
            novo->prox = *grafo;
            *grafo = novo;
        } 
        else 
        {
            Vertice *temp = *grafo;
            while (temp->prox && temp->prox->id < id)
                temp = temp->prox;

            novo->prox = temp->prox;
            temp->prox = novo;
        }
    } else
        printf("Erro ao alocar memoria!\n");
}

int verificar_Aresta(Aresta *lista_adj, char id) 
{
    while (lista_adj) 
    {
        if (lista_adj->id == id)
        {
            return 1; // Aresta ja existe
        }
        lista_adj = lista_adj->prox;
    }
    return 0; // Aresta nao existe
}

// Metodos diferentes de insercao apenas para praticar
void inserir_Aresta(Vertice *grafo, char id1, char id2) 
{
    if (verificar_vertice(grafo, id1) && verificar_vertice(grafo, id2)) 
    {
        while (grafo && grafo->id != id1)
            grafo = grafo->prox;
        //nao precisava pois ja sabemos que seria encontrado, gracas a verificacao, mas pra garantir...
        if (grafo) 
        {
            if (!verificar_Aresta(grafo->lista, id2)) 
            {
                Aresta *nova = malloc(sizeof(Aresta));
                if (nova) 
                {
                    nova->id = id2;

                    Aresta **lista_adj = &grafo->lista;
                    while (*lista_adj && (*lista_adj)->id < id2)
                        lista_adj = &(*lista_adj)->prox;

                    nova->prox = *lista_adj;
                    *lista_adj = nova;
                } else 
                    printf("Erro ao alocar memoria para aresta.");
            } else
                printf("Grafo simples, impossivel inserir aresta multipla!\n");
        }
    } else
        printf("Um ou ambos os vertices %c ou %c nao existem!\n", id1, id2);
}

// "Gambiarra" pra inserir aresta nao direcionada 
void inserir_aresta_simples(Vertice **grafo, char id1, char id2) 
{
    inserir_Aresta(*grafo, id1, id2);
    inserir_Aresta(*grafo, id2, id1);
}

int buscar_condicao(const Vertice *grafo, char id) 
{
    while (grafo) 
    {
        if (grafo->id == id)
            return grafo->cond;
        grafo = grafo->prox;
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
    Vertice *grafo_aux = grafo;
    char pior_cond = buscar_condicao(grafo_aux, id_pior);
    
    lista = lista->prox;
    while (lista && (pior_cond != 3)) 
    {
        char cond_atual = buscar_condicao(grafo_aux, lista->id);

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

        // Le o formato esperado: ID1,COND1,ID2,COND2 
        // Caso nao seja valido o formato, pulamos pra proxima
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

    Vertice *grafo_aux = grafo;

    while (grafo_aux) 
    {
        Aresta *lista_adj = grafo_aux->lista;

        while (lista_adj) 
        {
            if (grafo_aux->id < lista_adj->id) 
            {
                int cond_alvo = buscar_condicao(grafo, lista_adj->id);
                if (cond_alvo != -1)
                {
                    int probabilidade = calcular_probabilidade(grafo_aux->cond, cond_alvo);
                    fprintf(p, "%c -> %c: %d%%\n", grafo_aux->id, lista_adj->id, probabilidade);
                }
                else 
                    printf("Erro: Nao foi possivel encontrar o vertice %c para calculo da probabilidade.\n", lista_adj->id);
            }
            lista_adj = lista_adj->prox;
        }

        grafo_aux = grafo_aux->prox;
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

    Vertice *grafo_aux = grafo;

    while (grafo_aux)
    {
        if (grafo_aux->lista) 
        {
            char pior = encontrar_pior(grafo, grafo_aux->lista);
            int probabilidade = calcular_probabilidade(grafo_aux->cond, buscar_condicao(grafo, pior));
            fprintf(p, "%c: %d%%\n", grafo_aux->id, probabilidade);
        }
        grafo_aux = grafo_aux->prox;
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
