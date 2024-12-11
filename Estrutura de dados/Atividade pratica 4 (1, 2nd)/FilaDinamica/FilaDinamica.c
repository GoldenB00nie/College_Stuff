#include <stdio.h>
#include <stdlib.h>
#include "FilaDinamica.h"

// Struct lista movida para o arquivo FilaDinamica.h pois precisava acessar a quantidade
struct elemento{
    struct paciente dados;
    struct elemento *prox;
};

typedef struct elemento Elem;

// Função auxiliar para gerar um paciente com ID, nome e tipo de transplante
struct paciente gera_paciente(int id) {
    struct paciente p;
    p.id = id;
    snprintf(p.nome, 30, "Paciente %d", id);

    int tipo = rand() % 3;
    if (tipo == 0)
        snprintf(p.tipo_transplante, 10, "CORACAO");
    else if (tipo == 1)
        snprintf(p.tipo_transplante, 10, "CORNEA");
    else
        snprintf(p.tipo_transplante, 10, "MEDULA");

    return p;
}

Fila* cria_fila(){
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->inicio = NULL;
        fi->final = NULL;
        fi->qtd = 0;
    }
    return fi;
}

Lista_t* cria_lista_t() {
    Lista_t* li = (Lista_t*)malloc(sizeof(Lista_t));
    *li = NULL; // Inicializa a fila como vazia
    return li;
}

void libera_fila(Fila* fi){
    if(fi != NULL){
        Elem* no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int tamanho_fila(Fila* fi){
    if(fi == NULL) return 0;
    return fi->qtd;
}

int fila_vazia(Fila* fi){
    if(fi == NULL || fi->inicio == NULL)
        return 1;
    return 0;
}

int insere_fila(Fila* fi, struct paciente pc){
    if(fi == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = pc;
    no->prox = NULL;
    if(fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

int insere_lista_t(Lista_t* li, Tempos dados_tempos) {
    Elem_t* novo = (Elem_t*)malloc(sizeof(Elem_t));
    if (novo == NULL) {
        return 0; // Falha na alocação
    }
    novo->dados_tempos = dados_tempos;
    novo->prox = NULL;

    if (*li == NULL) {
        *li = novo; // A fila estava vazia
    } else {
        Elem_t* temp = *li;
        while (temp->prox != NULL) { // Navega até o final da fila
            temp = temp->prox;
        }
        temp->prox = novo; // Adiciona o novo elemento no final
    }
    return 1; // Inserção bem-sucedida
}

int remove_fila(Fila* fi){
    if(fi == NULL || fi->inicio == NULL) return 0;
    Elem *no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return 1;
}

void imprime_fila(Fila* fi){
    if(fi == NULL) return;
    Elem* no = fi->inicio;
    while(no != NULL){
        printf("Paciente: %s\nTipo de Transplante: %s\n", no->dados.nome, no->dados.tipo_transplante);
        no = no->prox;
    }
}