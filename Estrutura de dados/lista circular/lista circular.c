#include <stdio.h>
#include <stdlib.h>
#include "lista circular.h"

typedef struct elemento {
    struct aluno dados;
    struct elemento* prox;
} Elem;

typedef Elem* ListaCircular;

ListaCircular* cria_lista() {
    ListaCircular* li = (ListaCircular*) malloc(sizeof(ListaCircular));
    if(li != NULL)
        *li = NULL;
    return li;
}

int insere_lista_circular(ListaCircular* li, struct aluno al) {
    if (li == NULL) return 0; // se não tiver lista
    Elem* novo = (Elem*) malloc(sizeof(Elem));
    if (novo == NULL) return 0; // se não for possível alocar memória
    novo->dados = al;

    if (*li == NULL) { // se estiver vazia
        // Primeiro elemento da lista
        *li = novo;
        novo->prox = novo; // O único nó aponta para si mesmo
    } else {
        Elem* aux = *li;
        // Percorrer até o último nó
        while (aux->prox != *li) {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->prox = *li; // O novo último nó aponta para o primeiro
    }
    return 1;
}


void libera_lista(ListaCircular* li)
{
    if (li != NULL)
    {
        Elem* no;
        while ((*li) != NULL)
        {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }

        free(li);
    }
}

void imprime_lista_circular(ListaCircular* li) {
    if (li == NULL || *li == NULL) return;
    
    Elem* temp = *li;
    do {
        printf("---------------------------\n");
        printf("Matrícula: %d\n", temp->dados.num);
        temp = temp->prox;
        printf("---------------------------\n");
    } while (temp != *li); // Volta ao início da lista
}

void troca(ListaCircular* li, int n) {
    if (li == NULL || *li == NULL) return;
    Elem* aux = *li; // ponteiro auxiliar
    Elem* anterior = NULL;
    if (aux->dados.num != n) // Verifico se não é primeiro valor, senão, aplico a troca no primeiro
    {
        do // percorre a lista até achar a posição do número n
        {
            anterior = aux; // anterior recebe o atual do auxiliar
            aux = aux->prox;
            
            ////printf("mais um\n"); // para debug para saber o que está acontecendo
        } while (aux->dados.num != n && aux->prox != *li); // Verifica se o número é diferente de n, e se o próximo valor é o inicio da lista

        Elem* temp = aux->prox;
        char num_no_final = 0; // Número para evitar copiar código, char porque eu descobri que dá para usar como se fosse um
        // int, mas sem precisar alocar 4 bytes de memória

        if (aux->dados.num == n)
        {
            if (aux->prox == *li) num_no_final = 1; // Se estiver no final da lista

            anterior->prox = temp;
            aux->prox = temp->prox;
            temp->prox = aux;

            if (num_no_final == 1) // Evitar cópia de código
                *li = aux;
            return;
        }
        else if (aux->prox == *li) // verifica se não encontrou nada
        {
            printf("Valor não encontrado");
            return;
        }
    }
    else
    {
        anterior = *li; // Anterior, nesse caso, se refere ao primeiro elemento
        aux = aux->prox;

        anterior->prox = aux->prox;
        aux->prox = anterior;
        
        Elem* ultimo = anterior; // Elemento usado para evitar loop infinito da lista
        while (ultimo->prox != *li) { // Percorre até achar o último valor
            ultimo = ultimo->prox;
        }

        ultimo->prox = aux;
        *li = ultimo->prox;
        
        return;
    }
}