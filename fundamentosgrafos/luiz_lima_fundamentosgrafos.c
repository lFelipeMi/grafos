//Nome: Luiz Felipe Miranda // Turma: 5
//Curso: Eng. da computacao

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "listaC.h"

int dfs(Vertice *grafo, int id_inicio, int id_fim, Caminho *caminho, int nivel)
{
    if(id_inicio == id_fim && nivel == 0) return 0;
    int menor_caminho = 0;
    int compara = 0;

    if(buscar_vertice(grafo, id_inicio) == NULL)
    {
        printf("Vertice %d nao encontrado!\n", id_inicio);
    }
    else
    {
        Vertice *inicio = buscar_vertice(grafo, id_inicio);
        inserir_fim(caminho, id_inicio, 0);
        inicio->visitado = 1;

        if(id_inicio == id_fim)
        {
            imprimir_caminho(caminho);
            
            inicio->visitado = 0;
            return nivel + 1;
        } 
        else
        {
            Aresta *lista_adj = inicio->lista_adj;

            while(lista_adj)
            {
                Vertice *dest = buscar_vertice(grafo, lista_adj->dest);

                if(!dest->visitado)
                {
                    compara = dfs(grafo, lista_adj->dest, id_fim, caminho, nivel + 1);
                    if(menor_caminho > compara || menor_caminho == 0) menor_caminho = compara;
                }

                lista_adj = lista_adj->prox;
            }
        }

        if(caminho->inicio) liberar_caminho(caminho);
        inicio->visitado = 0;
        return menor_caminho;
    }
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
        if(!dfs(grafo, id1, aux->id, caminho, 0))
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

int imprimir_trilhas();

int imprimir_circuitos();

int imprimir_caminhhos();

int imprimir_ciclos();

int main()
{
    Vertice *grafo = NULL;

    inserir_vertice(&grafo, 1);
    inserir_vertice(&grafo, 2);
    inserir_vertice(&grafo, 3);

    // Inserindo arestas
    inserir_aresta(&grafo, 1, 2);
    inserir_aresta(&grafo, 2, 3);

    // Teste de conectividade
    int resultado = verificar_conexo(grafo);
    imprimir_grafo(grafo);
    printf("Resultado esperado: Conexo. Obtido: %s\n", resultado ? "Conexo" : "Não Conexo");
    return 0;
}