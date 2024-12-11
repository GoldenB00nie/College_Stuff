#include <stdio.h>
#include "lista circular.h"

int main() {
    ListaCircular* lista = cria_lista();

    struct aluno a1 = {2};
    struct aluno a2 = {3};
    struct aluno a3 = {4};
    struct aluno a4 = {1};
    struct aluno a5 = {5};

    insere_lista_circular(lista, a1);
    insere_lista_circular(lista, a2);
    insere_lista_circular(lista, a3);
    insere_lista_circular(lista, a4);
    insere_lista_circular(lista, a5);

    imprime_lista_circular(lista);

    troca(lista, 2);
    printf("\n\n\n");
    imprime_lista_circular(lista);


    return 0;
}

