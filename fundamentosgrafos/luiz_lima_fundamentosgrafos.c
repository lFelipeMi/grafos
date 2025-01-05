//Nome: Luiz Felipe Miranda // Turma: 5
//Curso: Eng. da computacao

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "listaC.h"

#define CAMINHO 0
#define CICLO 1
#define TRILHA 2
#define CIRCUITO 3

int dfs(Vertice *grafo, int id_atual, int id_destino, Caminho *caminho_atual, int objetivo) 
{
    Vertice *atual = buscar_vertice(grafo, id_atual); 
    if (!atual) return -1;

    int encontrado = 0;

    atual->visitado = 1; 
    inserir_fim(caminho_atual, id_atual, 0); 

    if ((objetivo == CAMINHO || objetivo == TRILHA) && id_atual == id_destino) 
    {
        imprimir_caminho(caminho_atual); 
        encontrado = 1;
    } 
    else if ((objetivo == CICLO || objetivo == CIRCUITO) && id_atual == id_destino && caminho_atual->tam > 2) 
    {
        imprimir_caminho(caminho_atual); 
        encontrado = 1;
    } 
    else 
    {
        Aresta *lista_adj = atual->lista_adj;

        while (lista_adj) 
        {
            Vertice *dest = buscar_vertice(grafo, lista_adj->dest);

            if (!dest) break;

            if ((objetivo == CICLO || objetivo == CAMINHO) && !lista_adj->percorrida)
            {
                lista_adj->percorrida = 1;
                encontrado = dfs(grafo, lista_adj->dest, id_destino, caminho_atual, objetivo);
                lista_adj->percorrida = 0;
            } 
            else if ((objetivo == CIRCUITO || objetivo == TRILHA) && !dest->visitado)
            {
                encontrado = dfs(grafo, lista_adj->dest, id_destino, caminho_atual, objetivo);
            }
            lista_adj = lista_adj->prox;
        }
    }

    remover_caminho(caminho_atual, id_atual);
    atual->visitado = 0;

    return encontrado;
}

/////////////////////////////////////////////////////////////
/*Funcoes propostas*/
int verificar_conexo(Vertice *grafo)
{
    int id1 = grafo->id;
    int conexo = 1;
    Vertice *aux = grafo->prox;
    Caminho *caminho = iniciar_caminho();

    while(aux)
    {
        if(!dfs(grafo, id1, aux->id, caminho, CAMINHO))
        {
            printf("O grafo nao eh conexo!\n");
            return 0;
        }
        aux = aux->prox;
    }

    printf("O grafo eh conexo!\n");
    return 1;
}

int verificar_lacos(Vertice *grafo)
{
    if(!grafo)
    {
        printf("Grafo vazio\n");
        return -1;
    }

    while(grafo)
    {
        if(buscar_aresta(&grafo, grafo->id, grafo->id)) return 1;
        grafo = grafo->prox;
    }
    return 0;
}

int verificar_paralelas(Vertice *grafo)
{
    int paralela = 0;

    if(!grafo)
    {
        printf("Grafo vazio\n");
        return -1;
    }

    while(grafo)
    {
        Aresta *lista_adj = grafo->lista_adj;
        while(lista_adj && lista_adj->prox)
        {
            if(lista_adj->dest == lista_adj->prox->dest)
            {
                printf("Aresta %d -> %d eh paralela\n",lista_adj->orig, lista_adj->dest);
                paralela = 1;
            }
            lista_adj = lista_adj->prox;
        }
        grafo = grafo->prox;
    }

    return paralela;
}

int calcular_grau(Vertice *grafo, int id)
{
    while(grafo && grafo->id != id)
        grafo = grafo->prox;

    if(!grafo)
    {
        printf("Vertice nao encontrado!\n");
        return -1;
    }

    Aresta *lista_adj = grafo->lista_adj;
    int grau = 0;
    while(lista_adj)
    {
        grau++;
        lista_adj = lista_adj->prox;
    }
    
    return grau;
}

//Criar uma funcao que calcule grau minino e max. Imprimir repeticoes com o indentificador do vertice.
void calcular_grau_extremos(Vertice *grafo)
{
    int maior = -1, maior_id = 0;
    int menor = -1, menor_id = 0;
    int aux = 0;

    while(grafo)
    {
        aux = calcular_grau(grafo, grafo->id);
        if(menor > aux && menor != -1)
        {
            menor = aux;
            menor_id = grafo->id;
        }
        if(maior < aux)
        {
            maior = aux;
            maior_id = grafo->id;
        }
        grafo = grafo->prox; 
    }
    printf("Maior: %d grau %d\n", maior_id, maior);
    printf("Menor: %d grau %d\n", menor_id, menor);
}

int calcular_ordem(Vertice *grafo)
{
    if(!grafo) return 0;
    return 1 + contar_vertice(grafo->prox);
}

int verificar_simples(Vertice *grafo)
{
    int simples = 1;
    if(verificar_lacos(grafo)) return 0;

    while(grafo)
    {
        Aresta *lista_adj = grafo->lista_adj;
        while(lista_adj && lista_adj->prox)
        {
            if(lista_adj->dest == lista_adj->prox->dest) simples = 0;
            lista_adj = lista_adj->prox;
        }
        grafo = grafo->prox;
    }

    return simples;
}

int verificar_multigrafo(Vertice *grafo)
{
    int multi = 0;
    if(verificar_lacos(grafo)) return 1;

    while(grafo)
    {
        Aresta *lista_adj = grafo->lista_adj;
        while(lista_adj && lista_adj->prox)
        {
            if(lista_adj->dest == lista_adj->prox->dest) multi = 1;
            lista_adj = lista_adj->prox;
        }
        grafo = grafo->prox;
    }

    return multi;
}

int verificar_completo(Vertice *grafo)
{
    if(!grafo)
    {
        printf("Grafo vazio!\n");
        return -1;
    }

    Vertice *inicio = grafo;

    while(grafo)
    {
        Vertice *grafo_aux = inicio;
        while(grafo_aux)
        {
            if(grafo->id != grafo_aux->id)
                if(!buscar_aresta(&inicio, grafo->id, grafo_aux->id)) return 0;
            grafo_aux = grafo_aux->prox;
        }
        grafo = grafo->prox;
    }
    return 1;
}

int verificar_regular(Vertice *grafo)
{
    if(!grafo)
    {
        printf("Grafo vazio!\n");
        return -1;
    }

    int grau_ref = calcular_grau(grafo, grafo->id);
    grafo = grafo->prox;

    while(grafo)
    {
        int grau_atual = calcular_grau(grafo, grafo->id);
        if(grau_ref != grau_atual) return 0;
        grafo = grafo->prox;
    }

    return 1;
}

int imprimir_passeios();

int imprimir_trilhas(Vertice *grafo)
{
    Caminho *trilha = iniciar_caminho();
    Vertice *ref_inicio = grafo;

    while(grafo)
    {
        Vertice *aux = grafo->prox;
        while(aux)
        {
            printf("Trilhas de %d a %d:\n", grafo->id, aux->id);
            dfs(ref_inicio, grafo->id, aux->id, trilha, TRILHA);
            aux = aux->prox;
        }
        grafo = grafo->prox;
    }
}

int imprimir_circuitos(Vertice *grafo)
{
    Caminho *circuito = iniciar_caminho();
    Vertice *ref_inicio = grafo;
    while(grafo)
    {
        printf("Circuitos de %d:\n", grafo->id);
        dfs(ref_inicio, grafo->id, grafo->id, circuito, CIRCUITO);
        grafo = grafo->prox;
    }
}

void imprimir_caminhos(Vertice *grafo)
{
    Caminho *caminho = iniciar_caminho();
    Vertice *ref_inicio = grafo;
    while(grafo)
    {
        Vertice *aux = grafo->prox;
        while(aux)
        {
            printf("Caminhos de %d a %d:\n", grafo->id, aux->id);
            if(grafo->id != aux->id)
            {
                dfs(ref_inicio, grafo->id, aux->id, caminho, CAMINHO);
            }
            aux = aux->prox;
        }
        grafo = grafo->prox;
    }
}

int imprimir_ciclos(Vertice *grafo)
{
    Caminho *ciclo = iniciar_caminho();
    Vertice *ref_inicio = grafo;
    while(grafo)
    {
        printf("Ciclos de %d:\n", grafo->id);
        dfs(ref_inicio, grafo->id, grafo->id, ciclo, CICLO);
        grafo = grafo->prox;
    }
}

int main()
{
    Vertice *grafo = NULL;

    inserir_vertice(&grafo, 1);
    inserir_vertice(&grafo, 2);
    inserir_vertice(&grafo, 3);
    inserir_vertice(&grafo, 4);

    inserir_aresta(&grafo, 1, 2);
    inserir_aresta(&grafo, 2, 3);
    inserir_aresta(&grafo, 3, 4);
    inserir_aresta(&grafo, 4, 1); 
    inserir_aresta(&grafo, 1, 3); 
    inserir_aresta(&grafo, 2, 2); 
    inserir_aresta(&grafo, 3, 2);

    imprimir_grafo(grafo);
    printf("### Testando Propriedades do Grafo ###\n\n");

    printf("\nConexidade do grafo:\n");
    if (verificar_conexo(grafo))
        printf("O grafo é conexo.\n");
    else
        printf("O grafo não é conexo.\n");

    printf("\nVerificando laços:\n");
    if (verificar_lacos(grafo))
        printf("O grafo possui laços.\n");
    else
        printf("O grafo não possui laços.\n");

    printf("\nVerificando arestas paralelas:\n");
    if (verificar_paralelas(grafo))
        printf("O grafo possui arestas paralelas.\n");
    else
        printf("O grafo não possui arestas paralelas.\n");

    printf("\nGraus dos vértices:\n");
    for (int i = 1; i <= 4; i++)
        printf("Grau do vértice %d: %d\n", i, calcular_grau(grafo, i));

    printf("\nGrau mínimo e máximo:\n");
    calcular_grau_extremos(grafo);

    printf("\nVerificando simplicidade do grafo:\n");
    if (verificar_simples(grafo))
        printf("O grafo é simples.\n");
    else
        printf("O grafo não é simples.\n");

    printf("\nVerificando se é multigrafo:\n");
    if (verificar_multigrafo(grafo))
        printf("O grafo é um multigrafo.\n");
    else
        printf("O grafo não é um multigrafo.\n");

    printf("\nVerificando completude do grafo:\n");
    if (verificar_completo(grafo))
        printf("O grafo é completo.\n");
    else
        printf("O grafo não é completo.\n");

    printf("\nVerificando regularidade do grafo:\n");
    if (verificar_regular(grafo))
        printf("O grafo é regular.\n");
    else
        printf("O grafo não é regular.\n");

    printf("\nTrilhas no grafo:\n");
    imprimir_trilhas(grafo);

    printf("\nCircuitos no grafo:\n");
    imprimir_circuitos(grafo);

    printf("\nCaminhos no grafo:\n");
    imprimir_caminhos(grafo);

    printf("\nCiclos no grafo:\n");
    imprimir_ciclos(grafo);

    imprimir_grafo(grafo);
    liberar_grafo(grafo);

    return 0;
}