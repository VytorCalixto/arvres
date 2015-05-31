#include <string.h>
#include "steamGames.h"
#define FALSE (0==1)
#define TRUE  !(FALSE)

// ------------ 2-3-4 ---------------- //
int eh_nodofolha234 (Ap234 p){ //retorna 1 se eh nodo folha
    if ((p->Ap[0]==NULL) && (p->Ap[1]==NULL) && (p->Ap[2]==NULL) && (p->Ap[3]==NULL)) return 1;
    return(0);
}
void imprime234 (Ap234 p){ //imprime a arvore

    if (p == NULL){
        return;
    }
    else if (p -> qtdNome == 1){
        printf( "(%s", p->nome[0]);
        imprime234(p->Ap[0]);
        imprime234(p->Ap[1]);
        printf(")");
        return;
    }
    else if(p -> qtdNome == 2){
        printf("(%s; ", p->nome[0]);
        printf(" %s", p->nome[1]);
        imprime234(p->Ap[0]);
        imprime234(p->Ap[1]);
        imprime234(p->Ap[2]);
        printf(")");
        return;
    }
    else if(p-> qtdNome == 3){
        printf("(%s;", p->nome[0]);
        printf("%s;", p->nome[1]);
        printf("%s", p->nome[2]);
        imprime234(p->Ap[0]);
        imprime234(p->Ap[1]);
        imprime234(p->Ap[2]);
        imprime234(p->Ap[3]);
        printf(")");
        return;
    }
    return;
}

Ap234 criaNodo234 (char *c, int linha){ //cria um novo nodo alocando espaço de memoria, os apontadores Ap[0..3] apontam para NULL.
 	Ap234 x;
	int i = 0;
	x = (tipo234*)malloc(sizeof(tipo234));
	x-> qtdNome = 1;
	while (*c != 0){
		x-> nome[0][i] = *c;
		c++;
		i++;
	}
	x-> nome[0][i] = '\0';
	x->linhaRegistro234[0]=linha;
	c = c - i; // retornando o pointer para o começo da string.
    x->Ap[0] = NULL; x->Ap[1] = NULL; x->Ap[2] = NULL; x->Ap[3]= NULL;
	return (x);
}

Ap234 split (Ap234 p, Ap234 pai_p){
    Ap234 aux1, aux2, aux3;

    //acontecera com uma raiz folha
    if (eh_nodofolha234(pai_p)==1){
        aux1 = criaNodo234(pai_p->nome[0], pai_p->linhaRegistro234[0]);
        aux2 = criaNodo234(pai_p->nome[2], pai_p->linhaRegistro234[2]);
        pai_p->qtdNome = 1;
        pai_p->Ap[0]=aux1;
        pai_p->Ap[1]=aux2;
        strcpy(pai_p->nome[0], pai_p->nome[1]);
        pai_p->linhaRegistro234[0] = pai_p->linhaRegistro234[1];
        return(pai_p);
    }
    //caso nao seja raiz folha
    aux1 = criaNodo234(p->nome[0], p->linhaRegistro234[0]);
    aux1->Ap[0] = p->Ap[0];
    aux1->Ap[1] = p->Ap[1];

    aux2 = criaNodo234(p->nome[2], p->linhaRegistro234[2]);
    aux2->Ap[0] = p->Ap[2];
    aux2->Ap[1] = p->Ap[3];


    aux3 = criaNodo234(p->nome[1], p->linhaRegistro234[1]);
    aux3->Ap[0] = aux1;
    aux3->Ap[1] = aux2;

    if (pai_p->qtdNome == 2){
        if (p == pai_p->Ap[0]){ // significa que nome[0] > c, c deve ser colocado à esquerda
            strcpy(pai_p->nome[2], pai_p->nome[1]);
            pai_p->linhaRegistro234[2] = pai_p->linhaRegistro234[1];
            strcpy(pai_p->nome[1], pai_p->nome[0]);
            pai_p->linhaRegistro234[1] = pai_p->linhaRegistro234[0];
            strcpy(pai_p->nome[0], aux3->nome[0]);
            pai_p->linhaRegistro234[0]= aux3->linhaRegistro234[0];
            pai_p->Ap[3]=pai_p->Ap[2];
            pai_p->Ap[2]=pai_p->Ap[1];
            pai_p->Ap[1]=aux2;
            pai_p->Ap[0]=aux1;
            pai_p->qtdNome ++;
        }
        else if (p == pai_p->Ap[1]){
            strcpy(pai_p->nome[2], pai_p->nome[1]);
            pai_p->linhaRegistro234[2] = pai_p->linhaRegistro234[1];
            strcpy(pai_p->nome[1], aux3->nome[0]);
            pai_p->linhaRegistro234[1] = aux3->linhaRegistro234[0];
            pai_p->Ap[3]=pai_p->Ap[2];
            pai_p->Ap[2]=aux2;
            pai_p->Ap[1]=aux1; // e ap[0] continua o mesmo.
            pai_p->qtdNome++;
        }
        else if (p==pai_p->Ap[2]){
            strcpy(pai_p->nome[2], aux3->nome[0]);
            pai_p->linhaRegistro234[2]= aux3->linhaRegistro234[0];
            pai_p->Ap[2]= aux1;
            pai_p->Ap[3]= aux2;
            pai_p->qtdNome ++;
        }
    }
    else if (pai_p->qtdNome == 1){ // tipo 2
        if(p == pai_p->Ap[0]){
            strcpy(pai_p->nome[1], pai_p->nome[0]);
            pai_p->linhaRegistro234[1] = pai_p->linhaRegistro234[0];
            pai_p->linhaRegistro234[0]= aux3->linhaRegistro234[0];
            strcpy(pai_p->nome[0], aux3->nome[0]);
            pai_p->Ap[2]=pai_p->Ap[1];
            pai_p->Ap[0]=aux1;
            pai_p->Ap[1]=aux2;
            pai_p->qtdNome ++;
        }
        else if(p == pai_p->Ap[1]){
            strcpy (pai_p->nome[1], aux3->nome[0]);
            pai_p->linhaRegistro234[1]=aux3->linhaRegistro234[0];
            pai_p->Ap[1]=aux1;
            pai_p->Ap[2]=aux2;
            pai_p->qtdNome ++;
        }
    }
    else if (pai_p == NULL){
        return(aux3);
    }
    return(pai_p);
}


Ap234 inserer234 (Ap234 p, Ap234 pai_p, char *c , int linha){ // abordagem otimista (tudo vai dar certo eee \o/ slip só quando não dá maiss
	int string_eh_maior;
	int i,j,k,l,aux,eh_folha = 0;
    Ap234 a_inserir;

	if (p == NULL){ // se for um nodo nulo, cria um novo nodo e dá o novo nodo pro p
		p = (criaNodo234(c, linha));
		return (p);
    }
    else{
        eh_folha = eh_nodofolha234(p);
            //SE TIPO 2:
            if (p->qtdNome == 1){
                j = (unsigned)strlen(p->nome[0]);
                i = (unsigned)strlen(c); //tamanho da string c
                if (j < i) i = j; //quem tem temanho menor?
                string_eh_maior = strncasecmp(p->nome[0], c, i); // compara os chars de p->nome[0] e *c até i que é o tamanho da menor string

                if (string_eh_maior <= 0){ //significa que p->nome[0] <= *c alfabeticamente, e c vai à direita de p-> nome
                    if(eh_folha == 1){
                        strcpy (p->nome[1], c);
                        p->linhaRegistro234[1]=linha;
                        p->qtdNome ++;
                        return(p);
                    }
                    else{
                        if (p->Ap[1]->qtdNome == 3){
                           p = split(p->Ap[1], p);
                        }
                           p->Ap[1] = inserer234(p->Ap[1], p, c, linha);
                    }
                }
                else { // significa que p->nome[0] > c, e c fica no lugar de p->nome[0]
                    if(eh_folha == 1){
                        strcpy(p->nome[1], p->nome[0]);
                        p->linhaRegistro234[1] = p->linhaRegistro234[0];
                        //tanho faz os p->ap pq são todos apontadores pra null
                        p->linhaRegistro234[0]= linha;
                        strcpy(p->nome[0], c);
                        p->qtdNome ++;
                        return(p);
                    }
                    else{
                        if (p->Ap[0]->qtdNome == 3){
                            p = split(p->Ap[0], p);
                        }
                        p->Ap[0] = inserer234(p->Ap[0], p, c, linha);
                    }

                }
        }
        //se nodo atual for tipo 3
        else if (p->qtdNome == 2){
            i = (unsigned)strlen(p->nome[0]);
            j = (unsigned)strlen(p->nome[1]);
            k = (unsigned)strlen(c); //tamanho da string c
            if (k < i) aux = k;
            else aux = i;
            string_eh_maior = strncasecmp(p->nome[0], c, aux);

            if (string_eh_maior > 0){ //significa que p->nome[0] > c, insere c em nome[0]
                if (eh_folha == 0) {
                    if (p->Ap[0]->qtdNome == 3){
                            p = split(p->Ap[0], p);
                    }
                    p->Ap[0] = inserer234(p->Ap[0], p, c, linha);
                }
                else if(eh_folha == 1){
                    strcpy(p->nome[2], p->nome[1]);
                    p->linhaRegistro234[2] = p->linhaRegistro234[1];
                    strcpy(p->nome[1], p->nome[0]);
                    p->linhaRegistro234[1] = p->linhaRegistro234[0];
                    strcpy(p->nome[0], c);
                    p->linhaRegistro234[0] = linha;
                    p->qtdNome ++;
                    return(p);
                }

            }

            else { //significa que p->nome[0] <= c
                if (k < j) aux = k;
                else aux = j;
                string_eh_maior = strncasecmp(p->nome[1], c, aux);

                if (string_eh_maior <= 0){ //significa que p->nome[1] <= c, ou seja, c deve ser colocado em nome[2]
                    if(eh_folha == 1){
                        strcpy(p->nome[2], c);
                        p->linhaRegistro234[2]= linha;
                        p->qtdNome ++;
                        return(p);
                    }
                    else{
                        if (p->Ap[2]->qtdNome == 3){
                            p = split(p->Ap[2], p);
                        }
                        p->Ap[2] = inserer234(p->Ap[2], p, c, linha);
                    }
                }
                else{ // significa que nome[0] <= c < nome[1], c deve ser colocado em nome[1]
                    if(eh_folha == 1){
                        strcpy(p->nome[2], p->nome[1]);
                        p->linhaRegistro234[2] = p->linhaRegistro234[1];
                        strcpy(p->nome[1], c);
                        p->linhaRegistro234[1] = linha;
                        p->qtdNome++;
                        return(p);
                    }
                    else{
                        if (p->Ap[1]->qtdNome == 3){
                            p = split(p->Ap[1], p);
                        }
                        p->Ap[1] = inserer234(p->Ap[1], p, c, linha);
                    }
                }
            }
         }
        //TIPO 4
        else if (p->qtdNome == 3){
            i = (unsigned)strlen(p->nome[0]);
            j = (unsigned)strlen(p->nome[1]);
            k = (unsigned)strlen(p->nome[2]);
            l = (unsigned)strlen(c); //tamanho da string c
                //comparando com p->nome[0]
                if (l<i) aux = l;
                else aux = i;
                string_eh_maior=strncasecmp(p->nome[0], c, aux);
                if (string_eh_maior > 0){ //significa que p->nome[0] > c, insere c em nome[0]
                     if(eh_folha==0) //este if nunca deve acontecer
                        p->Ap[0] = inserer234 (p->Ap[0], p, c, linha);
                     else{
                          p=split(p->Ap[0], p);
                          if (strcasecmp(p->nome[0], c) <= 0)
                               p->Ap[1] = inserer234(p->Ap[1], p, c, linha);
                          else
                               p->Ap[0] = inserer234(p->Ap[1], p, c, linha);
                          p->Ap[0] = inserer234 (p->Ap[0], p, c, linha);
                     }
                }
                else { //significa que p->nome[0] <= c
                    if (l<j) aux = l;
                    else aux = j;
                    string_eh_maior=strncasecmp(p->nome[1], c, aux);
                    if (string_eh_maior > 0){ //significa que p->nome[1] > c
                        if (eh_folha == 0) //este if nunca deve acontecer
                            p->Ap[1]= inserer234(p->Ap[1], p, c, linha);
                        else{
                            p=split(p->Ap[1], p);
                            if(strcasecmp(p->nome[0], c) <= 0) // significa que c deve ser colocado em ap[1];
                                p->Ap[1] = inserer234(p->Ap[1], p, c, linha);
                            else
                                p->Ap[0] = inserer234(p->Ap[0], p, c, linha);
                        }
                    }
                    else { // significa que c >= p->nome[1]
                        if (l<k) aux = l;
                        else aux = k;
                        string_eh_maior=strncasecmp(p->nome[2], c, aux);
                        if (string_eh_maior > 0){
                            if (eh_folha == 0) //este if nunca deve acontecer
                                p->Ap[2] = inserer234(p->Ap[2], p, c, linha);
                            else{
                                p=split(p->Ap[2], p);
                                if (strcasecmp(p->nome[0], c) <= 0)
                                    p->Ap[1] = inserer234(p->Ap[1], p, c, linha);
                                else
                                    p->Ap[0] = inserer234(p->Ap[1], p, c, linha);
                            }
                        }
                        else{ //c eh o maior do mundo bwaha
                            if(eh_folha == 0) //este if nunca deve acontecer
                                p->Ap[3] = inserer234(p->Ap[3], p, c, linha);
                            else{
                                p = split(p->Ap[3], p);
                                if (strcasecmp(p->nome[0], c) <= 0)
                                    p->Ap[1] = inserer234(p->Ap[1], p, c, linha);
                                else
                                    p->Ap[0] = inserer234(p->Ap[1], p, c, linha);
                            }
                        }
                    }
                }
            }
        }
    return(p);
}

Ap234 insere234 (Ap234 raiz, char *c , int linha){ // abordagem pessimista
    raiz = inserer234 (raiz, raiz, c, linha);
    return(raiz);
}

void busca234 (Ap234 p, char *c, void (*f)(int)){
    if(p == NULL) return;
    int i = 0;
    while(i < p->qtdNome && strcasecmp(p->nome[i], c) < 0) ++i;
    if(i < p->qtdNome && strcasecmp(p->nome[i], c) == 0){
        (*f)(p->linhaRegistro234[i]);
        busca234(p->Ap[i+1], c, (*f));
    }
    busca234(p->Ap[i], c, (*f));
}

// ------------ AVL ---------------- //
ApAVL rotEsq (ApAVL p){
	//Rotação Esquerda 
	ApAVL d = NULL;
	d = p->esq;
	p->esq = d->dir;
	d->dir = p;
	return d;
}

ApAVL rotDir (ApAVL p){
	//Rotação Direita
	ApAVL e = NULL;
	e = p->dir;
	p->dir = e->esq;
	e->esq = p;
	return e;
}

ApAVL criaNodoAVL(int k, int linha){
	//Cria um nodo Vazio
	ApAVL n = malloc(sizeof(*n));
	n->codigo = k;
	n->bal = 0;
	n->esq = NULL;
	n->dir = NULL;
	n->linhaRegistroAVL = linha;
	return n;
}

ApAVL balanceiaAVL(ApAVL p){
	if (p == NULL)
		return NULL;
	if (p->bal == 2) //Se tem mais do lado esquerdo
		if (p->esq->bal == 1){ //Tipo esq->esq
			p->bal = 0;
			p = rotEsq(p); //Uma rotação basta
			p->bal = 0;
			p->dir->bal = 0;
			return p;
		}
		else { //Se p->esq->bal == -1, ou seja, esq->dir
			p->esq = rotDir(p->esq);
			p = rotEsq(p);
			if (p->bal == 1) {
				p->bal = 0;
				p->esq->bal = 0;
				p->dir->bal = -1;
			}
			else {
				p->bal = 0;
				p->esq->bal = 1;
				p->dir->bal = 0;
			}
			return p;
		}
	else { //Se está aqui, tem nodos a mais do lado direito
		if (p->dir->bal == -1){ //Tipo dir-dir
			p->bal = 0;
			p = rotDir(p);
			p->bal = 0;
			p->dir->bal = 0;
			return p;
		}
		else { //Se p->dir>bal == 1, ou seja, dir->esq
			p->dir = rotEsq(p->dir);
			p = rotDir(p);
			if (p->bal == 1) {
				p->bal = 0;
				p->esq->bal = 0;
				p->dir->bal = -1;
			}
			else {
				p->bal = 0;
				p->esq->bal = -1;
				p->dir->bal = 0;
			}
			return p;
		}
	}
	return p; //Nunca vai chegar aqui
}

ApAVL insereAVL(ApAVL p, int k, int *mudaA, int linha){
	ApAVL n;
	if (p == NULL){ //Chegou na folha
		n = criaNodoAVL(k, linha);
		*mudaA = TRUE; //Alterou o balanceamento
		return n;
	}
	if (p->codigo == k) { //Não pode inserir o que já existe
		*mudaA = FALSE;
		return p;
	}
	if (k < p->codigo){ //Vai pro lado esquerdo
		p->esq = insereAVL(p->esq, k, mudaA, linha);
		if (*mudaA){
			p->bal++;
			if (p->bal == 2)
				p = balanceiaAVL(p);
			if (p-> bal == 0)
				*mudaA = FALSE;
		}
	}
	else { //Lado Direito
		p->dir = insereAVL(p->dir, k, mudaA, linha);
		if (*mudaA){
			p->bal--;
			if(p->bal == -2)
				p = balanceiaAVL(p);
			if(p->bal == 0)
				*mudaA = FALSE;
		}
	}
	return p;
}

ApAVL buscaAVL(ApAVL p, int k){
	//Busca Binária
	if (p == NULL) return NULL;
	if (p->codigo == k) return p;
	if (k < p->codigo) //Se for menor, vai pra esquerda
		return buscaAVL(p->esq,k);
	else //Senão, direita
		return buscaAVL(p->dir,k);
}

void imprimeAVL(ApAVL p){
	//Tipo pré-ordem
	if (p != NULL) {
		printf(" (%d - %d",p->codigo, p->bal);
		imprimeAVL(p->esq);
		imprimeAVL(p->dir);
		printf(")");
	}
}	
