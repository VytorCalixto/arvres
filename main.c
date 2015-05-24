#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"
#include <unistd.h>

int main (int argc, char **argv) {
    // Lê os parâmetros de entrada
    // Hard coded de acordo com a especificação: 1-registros, 2-busca
    char *registros = argv[1];
    char *buscas = argv[2];

    FILE *dados = fopen(registros, "r");
    char jogo;
    int codigo;
    fscanf(dados, "%d %s", &codigo, &jogo);
    printf("%d\t%s\n", codigo, &jogo);
    fclose(dados);

    return 0;
}
