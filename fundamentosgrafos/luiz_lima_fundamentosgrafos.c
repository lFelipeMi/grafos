//Nome: Luiz Felipe Miranda // Turma: 5
//Curso: Eng. da computacao

#include <stdio.h>
#include "grafo.h"
#include "listaC.h"

/////////////////////////////////////////////////////////////
/*Funcoes propostas*/
int verificar_conexo(Vertice *grafo)
{
    int id1 = grafo->id;
    grafo = grafo->prox;

    while(grafo)
    {
        if(!dfs(grafo, id1, grafo->id, 0));
    }
}

int verificar_lacos();

int verificar_paralelas();

void calcular_grau();

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

}