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


Aresta* selectArestaComAnterior(int v1, int v2, Aresta *anterior, Grafo* grafo);
	
Aresta* selectAresta(int v1, int v2, Grafo* grafo);

bool inicializaGrafo(Grafo *grafo, int nV);

void imprimeGrafo(Grafo* grafo);

bool insereAresta(int v1, int v2, Peso peso, Grafo *grafo);

bool existeAresta(int v1, int v2, Grafo *grafo);

bool removeAresta(int v1, int v2, Peso *peso, Grafo *grafo);

bool listaAdjVazia(int v, Grafo *grafo);

int tamanhoListaAdj(int vertice, Grafo* grafo);

bool getListaAdj(int vertice, int *valores, Grafo* grafo);

Grafo *lerArquivo(char* nome);

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

bool inicializaFila(Fila *fila);

bool filaChecaInicializacao(Fila *fila);

int filaVazia(Fila *fila);

int inserirNaFila(int elemento, Fila *fila);

int removerDaFila(Fila *fila);

void mostraFila(Fila *fila);

void printaFamilia(int valor, int *antecessor);

void visitaLargura(int vertice, Grafo *grafo, int *cor, int *antecessor, int *distancia);

void leituraPorBFS(Grafo *grafo, int *cor, int *antecessor, int *distancia);

void printLeituraPorBFS(Grafo *grafo);

void visitaBP(int v, Grafo *grafo, int tempo, int *cor, int *tdesc, int *tterm, int *antecessor, int *componentes, int componente);

void leituraPorDFS(Grafo *grafo, int *cor, int *tdesc, int *tterm, int *antecessor, int *componentes, int componente);

void printLeituraPorDFS(Grafo *grafo);