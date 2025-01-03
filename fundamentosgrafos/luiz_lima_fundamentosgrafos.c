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
    while(grafo)
    {
        if(buscar_aresta(&grafo, grafo->id, grafo->id)) return 1;
        grafo = grafo->prox;
    }
    return 0;
}

int verificar_paralelas();

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
int calcular_grau_extremos();

//ordem do grafo
int calcular_ordem();

int verificar_simples();

int verificar_multigrafo();

int verificar_completo();

int verificar_regular();

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