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
#include <conio.h>

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
		//printf("\n");
		while(aux != NULL){
			printf("(%d,%d)\n",aux->x,aux->y);
			aux = aux->prox;
		}
	}

void imprimirArv(Arv *no){
		if(no->esq != NULL)
		imprimirArv(no->esq);
		printf("(%d,%d)\n",no->x,no->y);
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

void VerifSimet(Par *lista){
		Par *aux;
		while(lista != NULL){
			aux = lista;
			while(aux != NULL){
				if(lista->x == aux->y && lista->y == aux->x){
					lista->simetrico = aux->simetrico = 1;
					break;
				}
				aux = aux->prox;
			}
			lista = lista->prox;
		}
	}

_Bool Simetrico(Par *lista){
		_Bool status = 1;
		VerifSimet(lista);
		while(lista != NULL){
			if(lista->simetrico == 0){
				status = 0;
				break;
			}
			lista = lista->prox;
		}
		return status;
	}

void transferir(Par *lista,Arv **inicio){
		while(lista != NULL){
			Par *aux = lista;
			lista = lista->prox;
			inserirArv(inicio,aux->x,aux->y);
			if(!(aux->simetrico))
			inserirArv(inicio,aux->y,aux->x);
			free(aux);
		}
	}

int main()
{
	int m,n,q,x,y,i;
	Par *inicio = NULL,*fim;
	Arv *inicioArv = NULL;
	_Bool simetria;
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
				if(((n-m)*(n-m)) >= q){ //verifica se o numero de pares a serem gerados é menor ou igual aos pares disponiveis no intervalo
					srand(time(NULL)); //inicializar a função rand -> seed rand
					for(i=0;i<q;i++){ //repete as instruções abaixo por q vezes, definido pelo usuário
						x = aleatorio(m,n); //criar um numero aleatório, entre m e n, definidos pelo usuário.
						y = aleatorio(m,n);
						if(!(repetido(inicio,x,y))){ //inserir os elementos enquanto não há pares repetidos
							inserir(&inicio,&fim,x,y); //insere o par em uma estrutura dinâmica
						}else{
							i--; //retroceder no loop for e gerar novo par, caso haja um par repetido
						}
					}
					imprimir(inicio); //imprime todos os pares ordenados
					simetria = Simetrico(inicio);
					printf("%d\n",simetria);
					if(!(simetria)){
						getch();
						transferir(inicio,&inicioArv);
						imprimirArv(inicioArv);
					}
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

