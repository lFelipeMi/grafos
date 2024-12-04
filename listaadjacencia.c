#include <stdio.h>
#include <stdlib.h>

struct vertice 
  {
  int id;
  struct vertice *proximo;
  };

struct Grafo 
  {
  int numerovertices;
  struct vertice **listaadjacencia;
  };

struct vertice *
criarvertice(int v)
  {
  struct vertice *novovertice;  
  
  novovertice =(struct vertice *) malloc(sizeof(struct vertice));
  novovertice->id = v;
  novovertice->proximo = NULL;
  
  return(novovertice);
  }

struct Grafo *
criargrafo(int vertices)
  {
  int i;
  struct Grafo *grafo;
  
  grafo = (struct Grafo *) malloc(sizeof(struct Grafo));
  grafo->numerovertices = vertices;
  grafo->listaadjacencia = (struct vertice **) malloc(vertices * sizeof(struct vertice *));

  for(i = 0; i < vertices; i++)
    {
    grafo->listaadjacencia[i] = NULL;
    }
  return(grafo);
  }

void 
adicionararesta(struct Grafo *grafo, int origem, int destino)
  {
  struct vertice *novovertice;
  
  novovertice = criarvertice(destino);
  novovertice->proximo = grafo->listaadjacencia[origem];
  grafo->listaadjacencia[origem] = novovertice;
  novovertice = criarvertice(origem);
  novovertice->proximo = grafo->listaadjacencia[destino];
  grafo->listaadjacencia[destino] = novovertice;
  }

void 
imprimirgrafo(struct Grafo *grafo)
  {
  int indice;
  
  for(indice = 0; indice < grafo->numerovertices; indice++)
    {
    struct vertice *temporario;
    
    temporario = grafo->listaadjacencia[indice];
    printf("\n Vertice %d: -> ", indice);
    while(temporario)
      {
      printf("%d -> ", temporario->id);
      temporario = temporario->proximo;
      }
    printf("\n");
    }
  }

int
main()
  {
  struct Grafo *grafo;
  
  grafo = criargrafo(4);
  adicionararesta(grafo, 0, 1);
  adicionararesta(grafo, 0, 2);
  adicionararesta(grafo, 0, 3);
  adicionararesta(grafo, 1, 2);
  imprimirgrafo(grafo);

  return(0);
  }
