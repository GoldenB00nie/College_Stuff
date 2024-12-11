#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

struct conversoes {
    int posicao;
    int num_escolhido;
    int tipo_conversao; // 10 - inteiro; 2 - Binário; 8 - Octal; 16 - Hexadecimal
    char string_tipo[20];
    char resultado_conversao[30];
};

struct elemento {
    struct conversoes dados;
    struct elemento* prox;
};

typedef struct elemento Elem;
typedef Elem* pilha;

pilha* cria_pilha ();
int insere_pilha (pilha* pi, struct conversoes dados);
int remove_pilha (pilha* pi);
int consulta_Elem (pilha* pi, int num);
int imprime_lista (pilha* pi);
int destroi_pilha (pilha* pi);
void transforma_num (Elem* aux);

// Funções especiais para melhorar o código:
void limpar_terminal();
void colocar_terminal_UTF8();
void flush_in();