#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/************************ Capitais ***************************/ // 3

#define NUM_CAPITAIS 27
#define TAM_NOME 20

typedef struct {
    char nome[TAM_NOME];
    int eCentroDistribuicao;
} Capital;

typedef struct Nodo {
    int vertice;
    struct Nodo* prox;
} Nodo;

typedef struct {
    Nodo* cabeca;
} ListaAdj;

typedef struct {
    int numVertices;
    ListaAdj* lista;
    //int* visited; // para o BFS
} Grafo;

typedef struct {
    int* items;
    int frente;
    int tras;
    int tamanho;
} Fila;

Nodo* criarNodo(int v);
Grafo* criarGrafo(int vertices);
void adicionarAresta(Grafo* grafo, int src, int dest);
void imprimirGrafo(Grafo* grafo, Capital capitais[]);

/********************* Lista global structs *********************/ // Nao esta no sndo.c

typedef struct {
    char tipo;  // C - Coração, M - Medula, K - Cornea
    int origem;
    char status[30];
    int id;
} Orgao;

typedef struct elemento {
    Orgao orgao;
    struct elemento* ant;
    struct elemento* prox;
} NodoLista;

typedef struct Lista_global {
    NodoLista* inicio;
} *lista_global;

/************************ Fila Medula e Cornea ***************************/ // 258

typedef struct NodoFilaOrgaos {
    Orgao orgao;
    struct NodoFilaOrgaos* prox;
} NodoFilaOrgaos;

typedef struct filaOrgaos{
    NodoFilaOrgaos* frente;
    NodoFilaOrgaos* tras;
} Fila_orgaos;

Fila_orgaos* criarFilaOrgaos();
int FilaVaziaOrgaos(Fila_orgaos* fila);
void enfileirarOrgaos(Fila_orgaos* fila, Orgao orgao);
int enfileirarOrgaosCentro(Fila_orgaos* filas[27], lista_global* li, Orgao orgao, Grafo* grafo, Capital capitais[], char metodo);
Orgao desenfileirarOrgaos(Fila_orgaos* fila);
void removeNodoFilaOrgaos(Fila_orgaos* fila);

/********************** Pilha Coracao *********************/ // 336

typedef struct NodoPilhaOrgaos {
    Orgao orgao;
    struct NodoPilhaOrgaos* prox;
} NodoPilhaOrgaos;

typedef struct pilhaOrgaos {
    NodoPilhaOrgaos* topo;
} Pilha_orgaos;

Pilha_orgaos* criarPilhaOrgaos();
int PilhaVaziaOrgaos(Pilha_orgaos* pilha);
void empilharOrgaos(Pilha_orgaos* pilha, Orgao orgao);
int empilharOrgaosCentro(Pilha_orgaos* pilhas[27], lista_global* li, Orgao orgao, Grafo* grafo, Capital capitais[], char metodo);
int desempilharOrgaos(Pilha_orgaos* pilha);
void removeNodoPilhaOrgaos(Pilha_orgaos* pilha);

/********************* Lista global funcoes *********************/ // 401

lista_global* criaLista();
int listaVaziaOrgaos(lista_global* li);
int insere_lista(lista_global* li, Orgao orgao);
int remove_lista(lista_global* li, char tipo);

/*************************** BFS ***************************/ // 33

Fila* criarFila(int tamanho);
int estaVazia(Fila* fila);
void enfileirar(Fila* fila, int valor);
int desenfileirar(Fila* fila);
void imprime_nos_visitados(Capital capital);
int CentroMaisProximoBFS(Grafo* grafo, int verticeInicial, Capital capitais[]);
int ProcurarOrgaoCentroMaisProximoBFS(Grafo* grafo, Fila_orgaos* filas[27], Pilha_orgaos* pilhas[27], int verticeInicial, Capital capitais[], char tipoOrg);

int TemOTipoFila(Fila_orgaos* fila, char tipo); // Comum entre os dois tipos

/*************************** DFS ***************************/ // 154

typedef struct NodoPilha {
    int vertice;
    struct NodoPilha* prox;
} NodoPilha;

typedef struct {
    NodoPilha* topo;
} Pilha;

Pilha* criarPilha(int tamanho);
int estaVaziaPilha(Pilha* pilha);
void empilhar(Pilha* pilha, int valor);
int desempilhar(Pilha* pilha);
int CentroMaisProximoDFS(Grafo* grafo, int verticeInicial, Capital capitais[]);
int ProcurarOrgaoCentroMaisProximoDFS(Grafo* grafo, Fila_orgaos* filas[27], Pilha_orgaos* pilhas[27], int verticeInicial, Capital capitais[], char tipoOrg);

/********************* Processamento de orgaos *********************/ // 453

int processarFilaOrgaos(Fila_orgaos* fila, lista_global* li_global, char tipo);
int processarPilhaOrgaos(Pilha_orgaos* pilha, lista_global* li_global);
int processarListaOrgaos(lista_global* li, int id);
int processarOrgao(Grafo* grafo, Fila_orgaos* filas[27], Pilha_orgaos* pilhas[27], lista_global* li, int verticeInicial, Capital capitais[], char tipo, char metodo);

/***************************** Relatorios **************************/ // 526

void imprimirFila(Fila_orgaos* fila, Capital capital[]);
void imprimirPilha(Pilha_orgaos* pilha, Capital capital[]);
void imprimirLista(lista_global* lista, Capital capital[]);
void imprimirRelatorio(Fila_orgaos* filas[27], Pilha_orgaos* pilhas[27], lista_global* lista, Capital capital[], char metodo[3]);

/****************************** Especiais *************************/ // 622

int id_max();
int numAleatIntervMax(int max);
char TipoAleatOrgao();

void limpar_terminal();
void colocar_terminal_UTF8();
void flush_in();