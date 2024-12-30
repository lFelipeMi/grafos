#include <stdio.h>

char verifica_projeto(int A1, int A2, int A3, int A4) 
{
    int combinacoes[3][2] = 
    {
        {A1 + A2, A3 + A4},
        {A1 + A3, A2 + A4},
        {A1 + A4, A2 + A3}
    };
    
    int total_area = A1 + A2 + A3 + A4;

    for (int i = 0; i < 3; i++) 
    {
        int largura = combinacoes[i][0];
        int altura = combinacoes[i][1];
        if (largura * altura == total_area)
            return 'S';
    }
    
    return 'N';
}

int main() 
{
    int A1, A2, A3, A4;
    scanf("%d %d %d %d", &A1, &A2, &A3, &A4);
    printf("%c\n", verifica_projeto(A1, A2, A3, A4));

    return 0;
}
