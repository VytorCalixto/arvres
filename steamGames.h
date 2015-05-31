#ifndef _steamGames_
#define _steamGames_

#include <stdio.h>
#include <stdlib.h>
#endif


/* *********************** Estruturas *************************** */

// ------------ AVL ---------------- //
typedef struct no *ApAVL;

typedef struct no {
	int codigo;
	int bal;
	ApAVL esq;
	ApAVL dir;
	int linhaRegistroAVL;
} tipoAVL;


// ------------ 2-3-4 ---------------- //

typedef struct nodo *Ap234;

typedef struct nodo {
	char nome[3][15];
	Ap234 Ap[4];
	int qtdNome;
	int linhaRegistro234[3];
} tipo234;


/* ******************** Funções ************************** */

// ------------ AVL ---------------- //
ApAVL	rotDir			(ApAVL);
ApAVL	rotEsq			(ApAVL);
ApAVL	balanceiaAVL		(ApAVL);
ApAVL	criaNodoAVL		(int, int linha);
ApAVL	insereAVL		(ApAVL, int, int *mudaA, int);
void	imprimeAVL		(ApAVL);
ApAVL	buscaAVL		(ApAVL, int);


// ------------ 2-3-4 ---------------- //
Ap234	split234		(Ap234, Ap234);
Ap234	criaNodo234		(char *, int linha);
Ap234	insere234		(Ap234, char *, int);
void	imprime234		(Ap234);
void	busca234		(Ap234, char *, void (*f)(int, int));
