#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"
#include <unistd.h>

void imprimeLinha(int linha);
char *registros;
char *buscas;

int main (int argc, char **argv) {
    // Lê os parâmetros de entrada
    // Hard coded de acordo com a especificação: 1-registros, 2-busca
    registros = argv[1];
    buscas = argv[2];
    
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
        printf("%d\t", linha);
        imprime234(raiz234);
        puts("");
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
            ApAVL no = buscaAVL(raizAVL, codigo);
            if(no != NULL){
                imprimeLinha(no->linhaRegistroAVL);
            }
        }else if(tipo == 'n'){
            fscanf(arqBuscas,"%s", &jogo);
            busca234(raiz234, &jogo, imprimeLinha);
        }
        fscanf(arqBuscas, "%c", &tipo);
    }
    
    fclose(arqBuscas);
    

    exit(0);
}

void imprimeLinha(int n){
    FILE *arq = fopen(registros, "r");
    if(arq == NULL){
        return;
    }
    int cont = 0;
    --n;
    char linha[256];
    while (fgets(linha, sizeof linha, arq) != NULL && cont < n){
        cont++;
    }
    printf("%s", linha);
    fclose(arq);
}