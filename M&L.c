/*
 * M&L.c
 * 
 * Copyright 2016 Thalyson <Thalyson@THALYSON-PC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef struct temp{
		int x,y;
		struct temp *prox,*ant;
		_Bool simetrico;
	}Par;

typedef struct tempArv{
		int x,y;
		struct tempArv *esq,*dir;
		_Bool simetrico;
	}Arv;

int aleatorio(int min,int max){
		int r,dif;
		dif = max - min; //calcula o numero de elementos no intervalo
		r = min + (rand()%dif);
		return r;
	}

Par *criar(int x,int y){
		Par *novo = (Par *)malloc(sizeof(Par));
		novo->x = x;
		novo->y = y;
		novo->simetrico = 0;
		novo->prox = novo->ant = NULL;
		return novo;
	}

Arv *criarArv(int x,int y){
		Arv *novo = (Arv *)malloc(sizeof(Arv));
		novo->x = x;
		novo->y = y;
		novo->esq = novo->dir = NULL;
		novo->simetrico = 0;
		return novo;
	}

void inserir(Par **inicio,Par **fim,int x,int y){
		if(*inicio == NULL){
				*inicio = *fim = criar(x,y);
		}else{
			Par *novo = criar(x,y);
			(*fim)->prox = novo;
			novo->ant = *fim;
			*fim = novo;
		}
	}

void inserirArv(Arv **inicio,int x,int y){
		if(*inicio == NULL){
			*inicio = criarArv(x,y);
		}else{
			_Bool ocupado = 1;
			Arv *novo = criarArv(x,y),*aux = *inicio;
			while(ocupado){
				if(novo->x == aux->x){
					if(novo->y < aux->y){
						if(aux->esq == NULL){
							aux->esq = novo;
							ocupado = 0;
						}else{
							aux = aux->esq;
						}
					}else{
						if(aux->dir == NULL){
							aux->dir = novo;
							ocupado = 0;
						}else{
							aux = aux->dir;
						}
					}
				}else if(novo->x < aux->x){
					if(aux->esq == NULL){
						aux->esq = novo;
						ocupado = 0;
					}else{
						aux = aux->esq;
					}
				}else{
					if(aux->dir == NULL){
						aux->dir = novo;
						ocupado = 0;
					}else{
						aux = aux->dir;
					}
				}
			}
		}
	}

void imprimir(Par *inicio){
		Par *aux = inicio;
		printf("\n{");
		while(aux != NULL){
			printf("(%d,%d)",aux->x,aux->y);
			aux = aux->prox;
		}
		printf("}\n");
	}

void imprimirArv(Arv *no){
		if(no->esq != NULL)
		imprimirArv(no->esq);
		printf("(%d,%d)",no->x,no->y);
		if(no->dir != NULL)
		imprimirArv(no->dir);
	}

_Bool repetido(Par *inicio,int x,int y){
		Par *aux = inicio;
		_Bool rep = 0;
		while(aux != NULL && !rep){
			if(aux->x == x && aux->y == y){
				rep = 1;
			}else{
				aux = aux->prox;
			}
		}
		return rep;
	}

int main()
{
	int m,n,q,x,y,i;
	Par *inicio = NULL,*fim;
	printf("Informe numero minimo:");
	scanf("%d",&m);
	if(m >= 0){ //verifica se o numero minimo é positivo
		printf("Informe o numero maximo:");
		scanf("%d",&n);
		if(n <= 100){
			n++;
			if(n-m > 0){ //verifica se o intervalo contém algum elemento
				printf("Informe o numero de elementos a serem gerados: ");
				scanf("%d",&q);
				if(pow(2,(n-m)) >= q){ //verifica se o numero de pares a serem gerados é menor ou igual aos pares disponiveis no intervalo
					printf("Aguarde");
					for(i=0;i<q;i++){ //repete as instruções abaixo por q vezes, definido pelo usuário
						srand(time(NULL)); //inicializar a função rand -> seed rand
						x = aleatorio(m,n); //criar um numero aleatório, entre m e n, definidos pelo usuário.
						sleep(1);
						y = aleatorio(m,n);
						if(!(repetido(inicio,x,y))){ //inserir os elementos enquanto não há pares repetidos
							inserir(&inicio,&fim,x,y); //insere o par em uma estrutura dinâmica
							printf(".");
						}else{
							i--; //retroceder no loop for e gerar novo par, caso haja um par repetido
						}
					}
					printf("Lista:");
					imprimir(inicio); //imprime todos os pares ordenados
					Par *aux = inicio;
					Arv *inicioArv = NULL;
					while(aux != NULL){
						inserirArv(&inicioArv,aux->x,aux->y);
						aux = aux->prox;
					}
					printf("Arvore:\n\n");
					imprimirArv(inicioArv);
				}else{
					printf("Nao existem pares suficientes no intervalo escolhido.\n");
				}
			}else{
				printf("Intervalo Invalido.\n");
			}
		}else{
			printf("Limite superior maximo: 100\n");
		}
	}else{
		printf("Numero Invalido.\n");
	}
	return 0;
}

