#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

typedef struct temp{
		int x,y;
		struct temp *prox,*ant;
		bool simetrico;
	}Par;
// estrutura arvore que vai ser usada para ordenar as coordenadas
typedef struct tempArv{
		int x,y;
		struct tempArv *esq,*dir;
		bool simetrico;
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

void inserirArv(Arv **inicio,int x,int y){  //Estrutura Arvore; Define o inicio como raiz
		if(*inicio == NULL){
			*inicio = criarArv(x,y);
		}else{
			bool ocupado = 1;
			Arv *novo = criarArv(x,y),*aux = *inicio;// aux se torna a nova "raiz" pois esta apontando para o inicio
			while(ocupado){//enquanto ocupado tiver o valor 1(verdadeiro) ele executa a repeticao.
				if(novo->x == aux->x){//  alocando ordenadamente os valores. Se o valor do novo->x for igual ao aux->x ou seja novo(2,y) aux(2,y), entao ele vai verificar o y para aloca ordenadamente.
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
				}else if(novo->x < aux->x){// se o novo->x for menor q a raiz entao vai se aloxado no lado esquerdo da arvore
					if(aux->esq == NULL){
						aux->esq = novo;
						ocupado = 0;
					}else{
						aux = aux->esq;
					}
				}else{// se o novo->x for maior q a raiz entao vai se aloxado no lado direito da arvore da arvore
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

bool repetido(Par *inicio,int x,int y){// verifica se o "par" inserido nao e repetido ex:(1,3)e(1,3). Se for repetido ele retorna 1 se nao for repetido ele executa o "while" ate chegar no Nulle sai da fuincao retornando 0.
		Par *aux = inicio;
		bool rep = 0;
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

bool Simetrico(Par *lista){//verifica todas as posicoes da lista, se e simetrico ou nao, se nao for status = 0.
		bool status = 1;
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

void transferir(Par *lista,Arv **inicio){ // passando os itens da lista para a "arvore".
		while(lista != NULL){
			Par *aux = lista;
			lista = lista->prox;
			inserirArv(inicio,aux->x,aux->y);
			if(!(aux->simetrico))// se o auxiliar nao for simetrico ou seja se tiver um par (3,2) e nao tiver um par (2,3) ele nao e simetrico, entao manda pra arvore os valroes de x e y trocados, pois um e o inverso do outro).
			inserirArv(inicio,aux->y,aux->x);
			free(aux);
		}
	}

int main()
{
	int m,n,q,x,y,i;
	Par *inicio = NULL,*fim;
	Arv *inicioArv = NULL;
	bool simetria;
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
					printf("\n%d\n",simetria);// Nao Simetrico.Vai imprimir a ordem simetrica das coordenadas.
						if(!(simetria)){// se Simetria nao for verdadeiro ou seja se retornar valor 0 ele entra na condicao.
							getch();
							transferir(inicio,&inicioArv);// vai transferir os itens da lista para a estrutura arvore e ordenar.
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
