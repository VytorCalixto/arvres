#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "steamGames.h"

// Tipo impressão sinaliza se deve imprimir como AVL ( = 0) ou 234 ( = 1)
void imprimeLinha(int linha, int tipoImpressao);

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
        int mudaA = (0==1);
        raizAVL = insereAVL(raizAVL, codigo, &mudaA, linha);
        fscanf(dados, " %s", &jogo);
        raiz234 = insere234(raiz234, &jogo, linha);
        //char descricao;
        fscanf(dados, "%[^\t\n]", &jogo);
        fscanf(dados, "%d", &codigo);
    }
    fclose(dados);
    
    
    puts("Codigo:");
    imprimeAVL(raizAVL);
    puts("\nNome:");
    imprime234(raiz234);
    puts("\n");
    
    FILE *arqBuscas = fopen(buscas, "r");
    if(arqBuscas == NULL){
        exit(-1);
    }
    char tipo;
    fscanf(arqBuscas, " %c", &tipo);
    while(tipo != 'f'){
        if(tipo == 'c'){
            fscanf(arqBuscas," %d", &codigo);
            ApAVL no = buscaAVL(raizAVL, codigo);
            if(no != NULL){
                imprimeLinha(no->linhaRegistroAVL, 0);
            }
        }else if(tipo == 'n'){
            fscanf(arqBuscas," %s", &jogo);
            busca234(raiz234, &jogo, imprimeLinha);
        }
        fscanf(arqBuscas, " %c", &tipo);
    }
    
    fclose(arqBuscas);
    

    exit(0);
}

void imprimeLinha(int n, int tipoImpressao){
    FILE *arq = fopen(registros, "r");
    if(arq == NULL){
        return;
    }
    int cont = 0;
    --n;
    char linha[1024];
    while (fgets(linha, sizeof linha, arq) != NULL && cont < n){
        cont++;
    }
    // Tipo impressao != 0 imprime como 234
    if(tipoImpressao){
        int codigo, id;
        char descricao, aux;
        sscanf(linha, "%d", &codigo);
        id = codigo;
        sscanf(linha, "%*d %[^\t\n]", linha);
        linha[strlen(linha)] = '\n';
        sscanf(linha, "%*s %[^\n\t]", &descricao);
        printf("%d %s\n", id, &descricao);
    }else{
        printf("%s", linha);
    }
    fclose(arq);
}