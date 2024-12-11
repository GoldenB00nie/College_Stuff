//Arquivo ListaSequencial.h
#define MAX 10
struct megasena{
    int codigo;
    int concurso;
    char nome[30];
    int n1,n2,n3,n4,n5,n6;
};

typedef struct lista Lista; // Define apelido (alias) para struct lista
Lista* cria_lista(); // prototipo da função para inicializar lista
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia(Lista* li);
void imprime_lista(Lista* li);
void imprime_elemento(struct megasena ms);
int insere_lista_vazia(Lista* li, struct megasena ms);
int insere_lista_final(Lista* li, struct megasena ms);
int insere_lista_inicio(Lista* li, struct megasena ms);

// QUESTAO 01 (Prototipo da funcao): inserir elementos na lista (ordenado pelo código)
int insere_lista_ordenada(Lista* li, struct megasena ms){
    if (li == NULL)
        return -1;
    for (int i = 0; i < li->qtd; i++) {
        if (li->dados[i].codigo == ms.codigo)
            printf("Codigo: %d\n",li->dados[i].codigo);
            printf("Concurso: %d\n",li->dados[i].concurso);
            printf("Nome: %s\n",li->dados[i].nome);
            printf("Numeros: %d - %d - %d - %d - %d - %d\n",li->dados[i].n1,
                                                            li->dados[i].n2,
                                                            li->dados[i].n3,
                                                            li->dados[i].n4,
                                                            li->dados[i].n5,
                                                            li->dados[i].n6);
            printf("-------------------------------\n");
    }
    return 1;
}

// QUESTAO 02 (Prototipo da funcao): remover primeiro elemento da lista
int remove_lista_inicio(Lista* li);

// QUESTAO 03 (Prototipo da funcao): remover último elemento da lista
int remove_lista_final(Lista* li);

// QUESTAO 04 (Prototipo da funcao): remover elemento através do código
int remove_lista_pelo_codigo(Lista* li, int cod);

// QUESTAO 05 (Prototipo da funcao): consultar elemento pelo índice
int consulta_lista_pos(Lista* li, int ind);

// QUESTAO 06 (Prototipo da funcao): consultar elemento pelo código
int consulta_lista_cod(Lista* li, int cod);



