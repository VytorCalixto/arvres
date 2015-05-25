#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"
#include <unistd.h>

int main (int argc, char **argv) {
    // Lê os parâmetros de entrada
    // Hard coded de acordo com a especificação: 1-registros, 2-busca
    char *registros = argv[1];
    char *buscas = argv[2];
    
    Ap234 raiz234 = NULL;
    ApAVL raizAVL = NULL;

    FILE *dados = fopen(registros, "r");
    if(dados == NULL){
        exit(-1);
    }
    int codigo = 0;
    char jogo;
    int linha = 0;
    fscanf(dados, "%d", &codigo);
    while(codigo != 0){
        ++linha;
        //printf("%d: %d - ", linha, codigo);
        int mudaA = (0==1);
        raizAVL = insereAVL(raizAVL, codigo, &mudaA, linha);
        fscanf(dados, "%s", &jogo);
        raiz234 = insere234(raiz234, &jogo, linha);
        //printf("%s\n", &jogo);
        char descricao;
        fscanf(dados, "%[^\t\n]", &descricao);
        fscanf(dados, "%d", &codigo);
    }
    fclose(dados);
    
    puts("\nCodigo:");
    imprimeAVL(raizAVL);
    puts("\nNome:");
    imprime234(raiz234);
    puts("\n");
    
    FILE *arqBuscas = fopen(buscas, "r");
    if(arqBuscas == NULL){
        exit(-1);
    }
    char tipo;
    fscanf(arqBuscas, "%c", &tipo);
    while(tipo != 'f'){
        if(tipo == 'c'){
            fscanf(arqBuscas,"%d", &codigo);
            printf("%d\n", codigo);
            ApAVL no = buscaAVL(raizAVL, codigo);
            if(no != NULL){
                puts("Achou");
                // TODO: Recuperar linha do arquivo
            }
        }else if(tipo == 'n'){
            fscanf(arqBuscas,"%s", &jogo);
            printf("%s\n", &jogo);
            // TODO: Buscar e recuperar linha do arquivo.
        }
        fscanf(arqBuscas, "%c", &tipo);
    }
    
    fclose(arqBuscas);
    

    exit(0);
}
