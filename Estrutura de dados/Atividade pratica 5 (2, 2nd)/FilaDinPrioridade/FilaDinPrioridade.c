#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaDinPrioridade.h"

struct paciente{
    int id;
    int idade;
    char nome[30];
    char tipo_transplante[10]; // Ex: "CORAÇÃO", "CÓRNEA", "MEDULA"
};

struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
};

// Struct lista movida para o arquivo FilaDinamica.h pois precisava acessar a quantidade
struct elemento{
    struct paciente dados;
    struct elemento *prox;
};

typedef struct elemento Elem;

// Função auxiliar para gerar um paciente com ID, nome e tipo de transplante
struct paciente gera_paciente(int id, int idade) {
    struct paciente pc;
    pc.id = id;
    pc.idade = idade;
    snprintf(pc.nome, 30, "Paciente %d", id);

    int tipo = rand() % 3;
    if (tipo == 0)
        snprintf(pc.tipo_transplante, 10, "CORACAO");
    else if (tipo == 1)
        snprintf(pc.tipo_transplante, 10, "CORNEA");
    else
        snprintf(pc.tipo_transplante, 10, "MEDULA");

    return pc;
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

int insere_fila(Fila* fi, int id, int idade){
    struct paciente pc = gera_paciente(id, idade);

    if(fi == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = pc;
    no->prox = NULL;
    
    if (fi->inicio == NULL) { // Se a fila está vazia
        fi->inicio = fi->final = no;
        fi->qtd++;
        return 1;
    } else {
        if(idade > fi->inicio->dados.idade) {
            no->prox = fi->inicio;
            fi->inicio = no;
            fi->qtd++;
            return 1;
        } else {
            Elem* aux = fi->inicio;
            while (aux->prox != NULL && idade <= aux->prox->dados.idade)
                aux = aux->prox;
            no->prox = aux->prox;
            aux->prox = no;
            fi->qtd++;
            return 1;
        }
    }
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
    int valor = no->dados.id;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return valor;
}

int idade_inicio_fila(Fila* fi) {
    if(fi == NULL || fi->inicio == NULL) return 0;
    return fi->inicio->dados.idade;
}

int id_inicio_fila(Fila* fi) {
    if(fi == NULL || fi->inicio == NULL) return 0;
    return fi->inicio->dados.id;
}

void imprime_fila(Fila* fi, int tipo_fila){
    if(fi == NULL) return;
    Elem* no = fi->inicio;
    #define print_dados_fila printf("Paciente: %s\nTipo de Transplante: %s\nIdade: %d\n", no->dados.nome, no->dados.tipo_transplante, no->dados.idade);
    switch (tipo_fila)
    {
        case 1: while(no != NULL){
                    if (strcmp(no->dados.tipo_transplante, "CORACAO") == 0){
                        print_dados_fila;
                    } no = no->prox;
        } break;
        case 2: while(no != NULL){
                    if (strcmp(no->dados.tipo_transplante, "CORNEA") == 0){
                        print_dados_fila;
                    } no = no->prox;
        }
        case 3: while(no != NULL){
                    if (strcmp(no->dados.tipo_transplante, "MEDULA") == 0){
                        print_dados_fila;
                    } no = no->prox;
        } break;
        
        default: while(no != NULL){
                    print_dados_fila;
                    no = no->prox;
                } break;
    }
    printf("--------------------------\n");
}