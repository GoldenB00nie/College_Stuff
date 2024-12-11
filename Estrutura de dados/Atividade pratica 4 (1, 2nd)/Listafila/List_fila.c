#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List_fila.h"

// Cria uma fila vazia
Fila* cria_fila() {
    Fila* fi = (Fila*)malloc(sizeof(Fila));
    *fi = NULL; // Inicializa a fila como vazia
    return fi;
}

Lista_t* cria_lista_t() {
    Lista_t* li = (Lista_t*)malloc(sizeof(Lista_t));
    *li = NULL; // Inicializa a fila como vazia
    return li;
}

// Insere um paciente na fila (final)
int insere_fila(Fila* fi, Paciente dados) {
    Elem* novo = (Elem*)malloc(sizeof(Elem));
    if (novo == NULL) {
        return 0; // Falha na alocação
    }
    novo->dados = dados;
    novo->prox = NULL;

    if (*fi == NULL) {
        *fi = novo; // A fila estava vazia
    } else {
        Elem* temp = *fi;
        while (temp->prox != NULL) { // Navega até o final da fila
            temp = temp->prox;
        }
        temp->prox = novo; // Adiciona o novo elemento no final
    }
    return 1; // Inserção bem-sucedida
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

// Remove o paciente do início da fila
int remove_fila(Fila* fi) {
    if (*fi == NULL) {
        return 0; // A fila está vazia
    }
    Elem* temp = *fi;
    *fi = (*fi)->prox; // Move a cabeça da fila para o próximo elemento
    free(temp); // Libera o elemento removido
    return 1; // Remoção bem-sucedida
}

// Consulta o primeiro paciente da fila
Paciente* consulta_primeiro(Fila* fi) {
    if (*fi == NULL) {
        return NULL; // A fila está vazia
    }
    return &(*fi)->dados; // Retorna os dados do primeiro paciente
}

// Retorna o tamanho da fila
int tamanho_fila(Fila* fi) {
    int tamanho = 0;
    Elem* temp = *fi;
    while (temp != NULL) {
        tamanho++;
        temp = temp->prox;
    }
    return tamanho;
}

// Libera a memoria da fila
void libera_fila(Fila* fi) {
    while (remove_fila(fi)); // Remove todos os elementos da fila
    free(fi); // Libera a memória da fila
}

Paciente gera_paciente(int id) { // Função para gerar dados aleatorios para um paciente
    Paciente p;
    p.id_paciente = id;
    sprintf(p.nome_paciente, "Paciente_%d", id);
    
    int tipo = rand() % 3;
    if (tipo == 0)
        strcpy(p.tipo_transplante, "CORACAO");
    else if (tipo == 1)
        strcpy(p.tipo_transplante, "CORNEA");
    else
        strcpy(p.tipo_transplante, "MEDULA");
    
    return p;
}

void imprime_operacao(char* operacao, Fila* lista, Paciente* p) { // Funcao para imprimir a operacao realizada
    printf("%s na fila de %s - ID: %d, Nome: %s\n", 
           operacao, p->tipo_transplante, p->id_paciente, p->nome_paciente);
}