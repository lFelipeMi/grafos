#include "listaC.h"

//Para testar -> gcc -o testelistaC.c testelistaC.c listaC.c

int main() {
    Caminho *caminho = iniciar_caminho();


    inserir_inicio(caminho, 2, 20);
    inserir_ordenado(caminho, 1, 10);
    inserir_fim(caminho, 3, 30);

    imprimir_caminho(caminho);

    remover(caminho, 2);
    imprimir_caminho(caminho);

    liberar_caminho(caminho);

    return 0;
}
