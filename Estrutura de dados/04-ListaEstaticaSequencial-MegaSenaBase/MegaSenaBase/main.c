#include <stdio.h>
#include <stdlib.h>
#include "ListaSequencial.h"

int main() {
    struct megasena m[8] = {{2,16350,"Joao",5,15,25,35,45,55},
                            {4,17890,"Ricardo",7,8,26,43,58,59},
                            {1,16350,"Bianca",1,11,22,27,41,48},
                            {7,16350,"Jose",10,11,25,29,31,38},
                            {5,11234,"Marcelo",2,7,25,29,46,54},
                            {13,17890,"Carla",7,23,24,36,43,60},
                            {9,17823,"Fabiano",10,17,28,30,31,39},
                            {3,15212,"Ana",8,16,29,31,35,44}};

    Lista *li; // Cria ponteiro para lista
    li = cria_lista();

    printf("\nTamanho: %d - Cheia? %d - Vazia: %d\n\n", tamanho_lista(li), lista_cheia(li), lista_vazia(li));

    // Inserir em uma lista vazia
    if(lista_vazia(li)) {
        insere_lista_vazia(li, m[0]); // Insere na primeira posição da lista vazia
    }

    printf("\nTamanho: %d - Cheia? %d - Vazia: %d\n\n", tamanho_lista(li), lista_cheia(li), lista_vazia(li));

    // Inserir no final da lista
    if(!lista_cheia(li)) {
        insere_lista_final(li, m[1]); // Insere no final da lista
    }

    // Inserir no início da lista
    if(!lista_cheia(li)) {
        insere_lista_inicio(li, m[2]); // Insere no início da lista
    }

    if(!lista_cheia(li)) {
        insere_lista_inicio(li, m[6]); // Insere no início da lista
    }

    // Imprimir a lista
    imprime_lista(li);
    printf("\n\n\n");
    insere_lista_ordenada(li, m[0]);

    // Liberar a lista (deve ser chamado ao final, após as operações)
    libera_lista(li);

    return 0;
}