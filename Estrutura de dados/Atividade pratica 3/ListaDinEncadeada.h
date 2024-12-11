#include <windows.h>

struct aluno {
    int matricula;
    char nome[30];
    float ap1, ap2, ap3, ap4; // Atividades Práticas
    float np;                 // Nota da Prova
    float av1;                // Avaliação final (AV1)
};

typedef struct elemento *Lista; // Apelido para a lista
typedef struct elemento_duplo *ListaDupla;

void calcula_av1(struct aluno *al);
Lista* cria_lista();
void libera_lista(Lista* li);
void imprime_lista(struct elemento *lista);
struct elemento* insere_ordenado(struct elemento *lista, struct aluno al);
struct elemento* juntar_listas(struct elemento *lista1, struct elemento *lista2);
struct elemento* selecionar_10melhores(struct elemento *lista);
struct elemento* selecionar_10piores(struct elemento *lista);

// Dupla
ListaDupla* insere_ordenado_duplamente(ListaDupla* lista, struct aluno al);
ListaDupla* concatena_listas_duplamente(Lista* lista1, Lista* lista2);
ListaDupla* inverter_lista_dupla(ListaDupla* lista);
void imprime_lista_dupla(ListaDupla* lista);

// Funções especiais para melhorar o código:
void limpar_terminal();
void colocar_terminal_UTF8();
void flush_in();