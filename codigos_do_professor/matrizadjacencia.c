#include <stdio.h>
#include <stdlib.h>

int
main()
  {
  int **matriz;
  int linhas;
  int colunas;
  int i;
  int j;

  printf("Entre com a quantidade de linhas\n");
  scanf("%d", &linhas);
  printf("Entre com a quantidade de colunas\n");
  scanf("%d", &colunas);
  matriz = (int **) malloc (linhas * sizeof (int *));

  for(i = 0; i < linhas; i++)
    {
    *(matriz + i) = (int *) malloc (colunas * sizeof (int));
    }

  for(i = 0; i < linhas; i++)
    {
    for(j = 0; j < colunas; j++)
      {
      *(*(matriz + i) + j) = i + j;
      }
    }

  printf("\n");
  for(i = 0; i < linhas; i++)
    {
    for(j = 0; j < colunas; j++)
      {
      printf("%d ", *(*(matriz + i) + j));
      }
    printf("\n");
    }

  for(i = 0; i < linhas; i++)
    {
    free(*(matriz + i));
    }
  free(matriz);
  return(0);
  }
