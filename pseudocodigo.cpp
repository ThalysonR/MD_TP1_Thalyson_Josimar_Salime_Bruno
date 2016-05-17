
Algoritmo_matematicaDiscreta

tipo
Par: Registro
	variavel
	x,y:inteiro;
	prox,ant:>Par;
	simetrico:logico;
	
	fim registro
variavel
inicio,fim:>par;	

tipo 
Arv:Registro
	variavel
	x,y:inteiro;
	esq,dir:>Arv;
	simetrico:logico;
	fim registro
	variavel
	
inicioArv:>Arv;

	funcao aleatorio(min,max:inteiro):inteiro
		r,dif:inteiro;
		dif<-max-min;
		r<- min+(rand()%dif);
		returne r;
		
	fimfuncao
	
	funcao criar(x,y:inteiro):>Par	
		novo:>Par;
		novo.x<-x;
		novo.y<-y;
		novo.esq<-novo.dir;
		retorne novo;
		
	fimfuncao
	
	funcao criarArv(x,y:inteiro):>Arv
		novo->x=x;
		novo->y=y;
		novo->esq=novo->dir;
		novo->simetrico=0;
		returne novo;
	fimfuncao
	
	funcao inserir(inicio,fim:Par;x,y:inteiro):
		variavel 
		novo:>Par;
			se(inicio=Nulo)Entao
				inicio=fim=criar(x,y);
			senao
				novo<-criar(x,y);
				fim.prox<-novo;
				novo.ant<-fim;
				fim-<novo;
			fimse	
	fimfuncao		
			
		inserirArv(inicio:>Arv;x,y:inteiro):
			novo,aux:>Par;
			ocupado:>logico;
			
			se(inicio=Nulo)Entao
				inicio<-criar(x,y);
			senao
				ocupado<-1;
				novo<-criarArv(x,y);
				aux=inicio;
				enquanto(ocupado=1)entao:
						se(novo.x=aux.x)entao
								se(novo.y<aux.y)entao
									se(aux.esq=Nulo)entao
										aux.esq=novo;
										ocupado=0;
								senao
									aux<-aux.esq;
								fimse		
						senao
								se(aux.dir=Nulo)Entao
									aux.dir=Nulo;	
									ocupado<-0;
								senao
									aux<-aux.dir;	
								fimse
						fimse		
				fimenquanto
			fimse
		fimfuncao
		
		funcao imprimir(inicio:>Par)
			aux:>Par;
			aux<-inicio;
				enquanto(aux<>Nulo)entao:
					escreva(aux" ");
					aux<-aux.prox;
				fimenquanto
		fimfuncao
		
		funcao imprimirArv(no:>Arv)
			se(no.esq<>NUlo)Entao
				imprimiArv(no.esq);
				escreva(no.dir,no.esq );
			fimse
			se(no.dir<>Nulo)Entao
				imprimirArv(no.dir);
			fimse
		fimfuncao	
		
		funcao repetido(inicio:>Par; x,y:inteiro):logico
			aux:>Par;
			aux=inicio;
			rep=0:logico;	
				enquanto(aux<>Nulo e rep<>1)entao
					se(aux.x=x e aux.y=y)Entao
						rep=1;
					senao
						aux<-aux.prox;
					fimse
				fimenquanto
			returne rep;
		fimfuncao
			
		verifSimet(lista:>Par)
			aux:>Par;
			enquanto(lista<>Nulo)entao:
				aux<-lista;
				enquanto(aux<Nulo)entao
					se(lista.x=aux.y e lista.y=aux.x)entao
						lista.simetrico<-1;
						aux.simetrico<-1;
					fimse						
					aux<-aux.prox;
				fimenquanto
				lista<-lista.prox;
			fimenquanto			
		fimfuncao	
		
		funcao Simetrico(lista:>Par):logico;
			status = 1:logico;
			VerifSimet(lista);
			enquanto(lista <> Nulo)entao
				se(lista.simetrico = 0)entao
					status <- 0;
				fimse
				lista <-lista.prox;
			fimenquanto
				returne status;
		fimfuncao
		
		transferir(lista:>Par inicio:>Arv)
			aux:>Par;
			enquanto(lista <> NULL)entao
					aux = lista;
					lista = lista.prox;
					inserirArv(inicio,aux.x,aux.y);
				se((aux.simetrico)<>1)
					inserirArv(inicio,aux->y,aux->x);
				
				fimse
			fimenquanto	
		fimfuncao
		
		inicio
			m,n,q,x,y,i:inteiro;
			inicio,fim:>Par;
			inicioArv:Arv;
			simetria:logico;
			
			escreva("Informe numero minimo ");
			leia(m);
			se(m>=0)entao
				escreva("Informe o numero maximo ");
				leis(n);
				se(n<=100)entao
					n<-n+1;
					se(((n-m)*(n-m))>=q)entao
							srand(time(NULL));
						para(i=0 ate q passo p)	faca
								x <-aleatorio(m,n); 
								y <- aleatorio(m,n);
							se((repetido(inicio,x,y))<>1) 
								inserir(&inicio,&fim,x,y); 
							senao
								i<- i-1; 
							fimse
						fimpara	
					
						imprimir(inicio); 
						simetria <- Simetrico(inicio);
						escreva(simetria);
						se((simetria)<>1)entao
							transferir(inicio,&inicioArv);
							imprimirArv(inicioArv);
						fimse
				    senao
						escreva("Nao existem pares suficientes no intervalo escolhido.");
					fimse
				senao
					escreva("Intervalo Invalido.");
				fimse
		 senao
			escreva("Limite superior maximo: 100");
		 fimse
	senao
		escreva("Numero Invalido.");
	fimse
	
fimalgoritmo
							
			
