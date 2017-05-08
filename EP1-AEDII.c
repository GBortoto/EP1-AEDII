#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Peso;

typedef struct Aresta {
	int verticeDeDestino;
	Peso peso;
	struct Aresta * prox;
} Aresta;

typedef Aresta* Apontador;

typedef struct {
	Apontador *listaAdj;
	int numVertices;
	int numArestas;	
} Grafo;

// -------------------- Implementação do grafo -----------------------------

Aresta* selectArestaComAnterior(int v1, int v2, Aresta *anterior, Grafo* grafo){
	if(grafo == NULL){
		printf("SelectComAnterior: Deu ruim ao tentar para (%d,%d)\n", v1, v2);
		printf("Seu grafo foi inicializado?\n");
		return NULL;
	}

	Aresta *tmp = grafo->listaAdj[v1];
	
	Aresta *tmp2;
	
	while(!(tmp == NULL)){	
		if(tmp->verticeDeDestino == v2){

			//printf("SelectComAnterior: Retornando (%d,%d) \n", v1, v2);
			//printf("SelectComAnterior: Setando 'anterior'");
			anterior = tmp2;
			return tmp;
		}
		tmp2 = tmp;
		tmp = tmp->prox;
	}
	//printf("SelectComAnterior: (%d,%d) não existe\n", v1, v2);
	return NULL;
}

Aresta* selectAresta(int v1, int v2, Grafo* grafo){
	if(grafo == NULL){
		printf("Select: Deu ruim ao tentar para (%d,%d)\n", v1, v2);
		printf("Seu grafo foi inicializado?\n");
		return NULL;
	}
	
	Aresta *tmp = grafo->listaAdj[v1];
		
	while(!(tmp == NULL)){
		if(tmp->verticeDeDestino == v2){
			//printf("Select: Retornando (%d,%d) \n", v1, v2);
			return tmp;
		}
		tmp = tmp->prox;
	}
	//printf("Select: (%d,%d) não existe\n", v1, v2);
	return NULL;
}

bool inicializaGrafo(Grafo *grafo, int nV){
	grafo->listaAdj = (Apontador*) malloc(sizeof(Apontador) * nV);
	if(grafo->listaAdj == NULL){
		return 0;
	}
	int i;
	for(i=0; i<nV+1; i++){
		grafo->listaAdj[i] = malloc(sizeof(Aresta));
		if(grafo->listaAdj[i] == NULL){
			return 0;
		}
		grafo->listaAdj[i]->verticeDeDestino = 0;
		if(grafo->listaAdj[i] == NULL){
			printf("inicializa: Deu ruim --> grafo->listaAdj[i] == NULL\n");
		}
	}
	grafo->numVertices = nV;
	grafo->numArestas = 0;
	if(grafo == NULL){
		printf("inicializa: Deu ruim --> grafo == NULL\n");
	}
	
	return 1;
}

void imprimeGrafo(Grafo* grafo){
	printf("%d %d\n", grafo->numVertices, grafo->numArestas);
	int i;
	int j;
	for(i=1; i<=grafo->numVertices; i++){
		for(j=1; j<=grafo->numVertices; j++){
			Aresta *aresta = selectAresta(i, j, grafo);
			if(!(aresta == NULL)){
				printf("%d %d %d\n", i, aresta->verticeDeDestino, aresta->peso);
			}
		}
	}
	printf("\n");
}

bool insereAresta(int v1, int v2, Peso peso, Grafo *grafo){
	if(grafo == NULL){
		printf("Deu ruim na inserção da aresta %d-%d de peso %d\n", v1, v2, peso);
		printf("Seu grafo foi inicializado?\n");
		return 0;
	}
	
	if(grafo->listaAdj[v1]->verticeDeDestino == 0){
		//printf("Insere: verticeDeDestino == 0 para %d-%d com peso %d\n", v1, v2, peso);
		grafo->listaAdj[v1]->verticeDeDestino = v2;
		grafo->listaAdj[v1]->peso = peso;
		grafo->listaAdj[v1]->prox = NULL;
		grafo->numArestas++;
	}else{
		Aresta *novaAresta = malloc(sizeof(Aresta));
		novaAresta->verticeDeDestino = v2;
		novaAresta->peso = peso;
		novaAresta->prox = grafo->listaAdj[v1];
		grafo->listaAdj[v1] = novaAresta;
		grafo->numArestas++;
		
		if(grafo->listaAdj[v1]->prox == NULL){
		//printf("Insere: Deu ruim --> grafo->listaAdj[i]->prox == NULL");
		}
	}
	if(grafo->listaAdj[v1] == NULL){
		printf("Insere: Deu ruim --> grafo->listaAdj[v1] == NULL\n");
		return 0;
	}
	
	
	//printf("Aresta (%d,%d) com peso %d inserida com sucesso\n", v1, v2, peso);
	return 1;
}

bool existeAresta(int v1, int v2, Grafo *grafo){

	Aresta *aresta = selectAresta(v1, v2, grafo);
	if(aresta){
		return 1;
	}
	return 0;

	/*
	Aresta *tmp = grafo->listaAdj[v1];
	
	while(!(tmp == NULL)){
		if(tmp->verticeDeDestino == v2){
			printf("A aresta (%d,%d) existe\n", v1, v2);
			return 1;
		}
		tmp = tmp->prox;
	}
	//printf("A aresta (%d,%d) não existe\n", v1, v2);
	return 0;
	*/
}

bool removeAresta(int v1, int v2, Peso *peso, Grafo *grafo){
	Aresta *anterior = malloc(sizeof(Aresta));
	Aresta *aresta = selectArestaComAnterior(v1, v2, anterior, grafo);
	if(aresta){
		*peso = aresta->peso;
		if(anterior->verticeDeDestino == 0){
			anterior->prox = NULL;
		}else{
			anterior->prox = aresta->prox;
		}
		free(aresta);
		printf("A aresta (%d,%d) foi removida com sucesso\n", v1, v2);
		grafo->numArestas--;
		return 1;
	}
	//printf("A aresta (%d,%d) não existe\n", v1, v2);
	return 0;
}

bool listaAdjVazia(int v, Grafo *grafo){
	if(grafo->listaAdj[v]->verticeDeDestino == 0){
		printf("listaAdjVazia(%d) está vazia\n", v);
		return 1;
	}else{
		printf("listaAdjVazia(%d) não está vazia\n", v);
		return 0;
	}
}

Grafo *lerArquivo(char* nome){
	FILE *file;
	file = fopen(nome, "r");
	
	// # de Vértices
	char buffer[3];
	fscanf(file, "%s", buffer);
	int nVertices = atoi(buffer);
	
	
	// # de Arestas
	fscanf(file, "%s", buffer);
	int nArestas = atoi(buffer);
	
	Grafo *grafo = malloc(sizeof(Grafo));
	inicializaGrafo(grafo, nVertices);
	
	int i;
	for(i=0; i<nArestas; i++){
		// v1
		fscanf(file, "%s", buffer);
		int v1 = atoi(buffer);

		// v2
		fscanf(file, "%s", buffer);
		int v2 = atoi(buffer);
	
		// peso
		fscanf(file, "%s", buffer);
		int peso = atoi(buffer);
		
		insereAresta(v1, v2, peso, grafo);
	}
		
	fclose(file);
	
	return grafo;
}

// -------------------- Implementação da Fila -----------------------------

typedef struct No{
	int valor;
	struct No *anterior;
	struct No *prox;
}No;

typedef struct Fila{
	No *inicio;
	No *fim;
	int nElementos;
}Fila;

bool inicializaFila(Fila *fila){
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->nElementos = 0;	
}

bool filaChecaInicializacao(Fila *fila){
	if(fila){
		return 1;
	}
	printf("Essa fila não está inicializada\n");
	return 0;
}

int filaVazia(Fila *fila){
	if(filaChecaInicializacao){
		if(fila->nElementos == 0){
			return 1;
		}
		return 0;
	}
	return -1;
}

int inserirNaFila(int elemento, Fila *fila){
	if(filaChecaInicializacao){
		No *novoNo = (No *) malloc(sizeof(No));
		if(!novoNo){
			printf("inserirNaFila: Não foi possivel alocar memória para o novoNó\n");
			return -2;
		}
		novoNo->valor = elemento;
		novoNo->prox = fila->fim;
		novoNo->anterior = NULL;
		
		if(filaVazia(fila) == 1){
			fila->inicio = novoNo;
			fila->fim = novoNo;
		}else{
		fila->fim->anterior = novoNo;
		fila->fim = novoNo;	
		}
		fila->nElementos++;
		return 1;
	}
	return -1;
}

int removerDaFila(Fila *fila){
	if(filaChecaInicializacao){
		if(filaVazia(fila) == 0){
			int valor = fila->inicio->valor;
			fila->inicio = fila->inicio->anterior;
			if(fila->inicio){
				fila->inicio->prox->anterior = NULL;
				free(fila->inicio->prox);
				fila->inicio->prox = NULL;
			}else{
				free(fila->fim);
				fila->fim = NULL;
			}
			fila->nElementos--;
			return valor;
		}
		printf("removerDaFila: Não foi possível remover da fila - fila vazia\n");
		return -3;
	}
	return -1;
}

void mostraFila(Fila *fila){
	if(filaChecaInicializacao){
		//printf("filaVaria(fila)=%d\n", filaVazia(fila));
		if(filaVazia(fila) == 0){
			No *no = fila->inicio;
			printf("nElementos: %d | ", fila->nElementos);
			printf("Conteúdo da fila:");
			while(no){
				printf(" %d", no->valor);
				no = no->anterior;
			}
			printf("\n");
			return;
		}
		printf("mostraFila: A fila está vazia\n");
		return;
	}
	return;
}



void leituraPorBFS(Grafo *grafo){
	int nV = grafo->nVertices;
	// No array cor:
	// 0 = branco
	// 1 = cinza
	// 2 = preto
	int *cor = (int *) malloc(sizeof(int)*nV);
	int *antecessor = (int *) malloc(sizeof(int)*nV);
	int *distancia = (int *) malloc(sizeof(int)*nV);
	int i;
	for(i=0; i<nV; i++){
		cor[i] = 0;
		antecessor[i] = -1;
		// Distancia = Infinito
		distancia[i] = NULL;
	}
	for(i=0; i<nV; i++){
		if(cor[i] == 0){
			visitaLargura(i, grafo, cor, antecessor, distancia);
		}
	}
	
}

void visitaLargura(int vertice, Grafo *grafo, int *cor, int *antecessor, int *distancia){
	
}





void main(int argc, char **argv){
	Grafo *grafo;
	if(argc >= 2){
		grafo = lerArquivo(argv[1]);
	}
	
	// Task 1 - Imprimir grafo de forma identica a entrada
	if(grafo){
		imprimeGrafo(grafo);
	}
	
	/*
	Fila *fila = (Fila *) malloc(sizeof(Fila));
	inicializaFila(fila);
	mostraFila(fila);
	int i;
	for(i=0; i<10; i++){
		inserirNaFila(i, fila);
		mostraFila(fila);
	}
	
	int nElementos = fila->nElementos;
	for(i=0; i<nElementos; i++){
		printf("%d\n", removerDaFila(fila));
		mostraFila(fila);
	}
	*/
	
	// Task 2 - 
	
	
	/*
	Grafo *grafo = malloc(sizeof(Grafo));
	inicializaGrafo(grafo, 7);

	insereAresta(1, 2, 1, grafo);
	insereAresta(1, 3, 2, grafo);
	insereAresta(2, 4, 3, grafo);
	insereAresta(3, 4, 4, grafo);
	insereAresta(4, 5, 5, grafo);
	insereAresta(4, 6, 6, grafo);
	insereAresta(5, 7, 7, grafo);
	insereAresta(6, 7, 8, grafo);

	
	printf("\n\n\n");
	
	imprimeGrafo(grafo);
	
	printf("\n\n\n");

	
	*/
	/*
	Peso *peso = malloc(sizeof(Peso));	
	int i;
	int j;
	for(i=1; i<=10; i++){
		for(j=1; j<=10; j++){
			*peso = -1;
			bool x = removeAresta(i, j, peso, grafo);
			if(x){
				printf("O peso da aresta (%d,%d) é %d\n", i, j, *peso);
				imprimeGrafo(grafo);
				
			}
		}
	}
	*/
	
	/*
	insereAresta(1, 2, 1, grafo);
	insereAresta(1, 3, 2, grafo);
	insereAresta(2, 4, 3, grafo);
	insereAresta(3, 4, 4, grafo);
	insereAresta(4, 5, 5, grafo);
	insereAresta(4, 6, 6, grafo);
	insereAresta(5, 7, 7, grafo);
	insereAresta(6, 7, 8, grafo);
	
	imprimeGrafo(grafo);
	*/
	
	/*
	for(i=1; i<=10; i++){
		listaAdjVazia(i, grafo);
	}
	*/
	

}