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

int aleatorio(int min,int max){
		int r,dif;
		dif = max - min;
		r = min + (rand()%dif);
		return r;
	}

Par *criar(int x,int y){
		Par *novo = (Par *)malloc(sizeof(Par));
		novo->x = x;
		novo->y =y;
		novo->prox = novo->ant = NULL;
		return novo;
	}

void inserir(Par **inicio,Par **fim,int n1,int n2){
		if(*inicio == NULL){
				*inicio = *fim = criar(n1,n2);
		}else{
			Par *novo = criar(n1,n2);
			(*fim)->prox = novo;
			novo->ant = *fim;
			*fim = novo;
		}
	}

void imprimir(Par *inicio){
		Par *aux = inicio;
		printf("{");
		while(aux != NULL){
			printf("(%d,%d)",aux->x,aux->y);
			aux = aux->prox;
		}
		printf("}");
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
		n++;
		if(n-m > 0){ //verifica se o intervalo contém algum elemento
			printf("Informe o numero de elementos a serem gerados: ");
			scanf("%d",&q);
			if(pow(2,(n-m)) >= q){ //verifica se o numero de elementos escolhido é menor que os pares disponiveis no intervalo
				for(i=0;i<q;i++){ //repete as instruções abaixo por q vezes, definido pelo usuário
					srand(time(NULL)); //inicializar a função rand -> seed rand
					x = aleatorio(m,n); //criar um numero aleatório, entre m e n, definidos pelo usuário.
					sleep(1);
					y = aleatorio(m,n);
					inserir(&inicio,&fim,x,y); //insere o par em uma estrutura dinâmica
				}
				imprimir(inicio); //imprime todos os pares ordenados
			}else{
				printf("Numero Invalido.\n");
			}
		}else{
			printf("Intervalo Invalido.\n");
		}
	}else{
		printf("Numero Invalido.\n");
	}
	return 0;
}

