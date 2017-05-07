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

// Para debuggin
void imprimeGrafo(Grafo* grafo, int nV){
	int i;
	for(i=0; i<=nV; i++){
		Aresta *tmp = grafo->listaAdj[i];
		
		while(!(tmp == NULL)){
			if(tmp->verticeDeDestino == 0){
				tmp = tmp->prox;
				continue;
			}
			printf("Vértice %d | Aresta (%d, %d) | Peso: %d\n", i, i, tmp->verticeDeDestino, tmp->peso);
			tmp = tmp->prox;
		}
	}
}


bool insereAresta(int v1, int v2, Peso peso, Grafo *grafo){
	if(grafo == NULL){
		printf("Deu ruim na inserção da aresta %d-%d de peso %d\n", v1, v2, peso);
		printf("Seu grafo foi inicializado?\n");
		return 0;
	}
	
	if(grafo->listaAdj[v1]->verticeDeDestino == 0){
		printf("Insere: verticeDeDestino == 0 para %d-%d com peso %d\n", v1, v2, peso);
		grafo->listaAdj[v1]->verticeDeDestino = v2;
		grafo->listaAdj[v1]->peso = peso;
		grafo->listaAdj[v1]->prox = NULL;
	}else{
		Aresta *novaAresta = malloc(sizeof(Aresta));
		novaAresta->verticeDeDestino = v2;
		novaAresta->peso = peso;
		novaAresta->prox = grafo->listaAdj[v1];
		
		grafo->listaAdj[v1] = novaAresta;
		
		if(grafo->listaAdj[v1]->prox == NULL){
		printf("Insere: Deu ruim --> grafo->listaAdj[i]->prox == NULL");
		}
	}
	if(grafo->listaAdj[v1] == NULL){
		printf("Insere: Deu ruim --> grafo->listaAdj[v1] == NULL\n");
		return 0;
	}
	
	
	printf("Aresta (%d,%d) com peso %d inserida com sucesso\n", v1, v2, peso);
	return 1;
}


bool existeAresta(int v1, int v2, Grafo *grafo){

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
}


bool removeAresta(int v1, int v2, Peso *peso, Grafo *grafo){
	if(grafo == NULL){
		printf("Deu ruim na remoção da aresta %d-%d de peso %d\n", v1, v2, *peso);
		printf("Seu grafo foi inicializado?\n");
		return 0;
	}
	if(!existeAresta(v1, v2, grafo)){
		//printf("A aresta (%d,%d) não pode ser removida - A aresta não existe\n", v1, v2);
		return 0;
		
	}else{
		Aresta *tmp = grafo->listaAdj[v1];
		Aresta *tmp2 = NULL;
		
		while(!(tmp == NULL)){
			if(tmp->verticeDeDestino == v2){
				*peso = tmp->peso;
				if(tmp2){
					tmp2->prox = tmp->prox;
				}
				free(tmp);
				printf("A aresta (%d,%d) foi removida com sucesso\n", v1, v2);
				return 1;
				
			}
			tmp2 = tmp;
			tmp = tmp->prox;
		}
		printf("A aresta (%d,%d) não foi removida\n", v1, v2);
		return 0;
	}
}

void main(){
	
	Grafo *grafo = malloc(sizeof(Grafo));
	bool x = inicializaGrafo(grafo, 10);
	
	if(x){
		printf("Yaaaay\n\n\n");
	}
	
	
	insereAresta(1, 2, 1, grafo);
	insereAresta(1, 3, 2, grafo);
	insereAresta(2, 4, 3, grafo);
	insereAresta(3, 4, 4, grafo);
	insereAresta(4, 5, 5, grafo);
	insereAresta(4, 6, 6, grafo);
	insereAresta(5, 7, 7, grafo);
	insereAresta(6, 7, 8, grafo);

	
	printf("\n\n\n");
	
	imprimeGrafo(grafo, 10);
	
	printf("\n\n\n");

	Peso *peso = malloc(sizeof(Peso));
	int i;
	int j;
	for(i=1; i<=10; i++){
		for(j=1; j<=10; j++){
			*peso = -1;
			bool x = removeAresta(i, j, peso, grafo);
			if(x){
				printf("O peso da aresta (%d,%d) é %d\n", i, j, *peso);
			}
		}
	}
	
	
	for(i=1; i<=10; i++){
		for(j=1; j<=10; j++){
			existeAresta(i, j, grafo);
		}
	}
	

}