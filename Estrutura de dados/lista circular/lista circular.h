struct aluno {
    int num;
};

typedef struct elemento *ListaCircular; // Apelido para a lista

ListaCircular* cria_lista();
int insere_lista_circular(ListaCircular* li, struct aluno al);
void libera_lista(ListaCircular* li);
void imprime_lista_circular(ListaCircular* li);
void troca(ListaCircular* li, int n);