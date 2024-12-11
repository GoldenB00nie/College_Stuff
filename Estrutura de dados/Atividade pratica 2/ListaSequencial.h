#include <windows.h>
#define MAX 100 // Definindo um número máximo de alunos

struct aluno {
    int codigo;
    char nome[30];
    float ap1, ap2, ap3, ap4; // Atividades Práticas
    float np;                 // Nota da Prova
    float av1;                // Avaliação final (AV1)
};

typedef struct lista Lista; // Apelido para a lista

Lista* cria_lista();
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia(Lista* li);

void imprime_lista(Lista* li);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int remove_lista_pelo_codigo(Lista* li, int cod);
int consulta_lista_pos(Lista* li, int pos);
int consulta_lista_cod(Lista* li, int cod);

// Funções especiais para melhorar o código:
void limpar_terminal();
void colocar_terminal_UTF8();
void flush_in();
int CharOuNum_opcao(char charAux_opcao);