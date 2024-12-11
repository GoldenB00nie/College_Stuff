#include <stdio.h>
#include "ListaDinEncadeada.h" //inclui os Protótipos

struct elemento
{
    struct aluno dados;
    struct elemento *prox;
};

struct elemento_duplo
{
    struct aluno dados;
    struct elemento_duplo *prox;
    struct elemento_duplo *ant;
};

typedef struct elemento Elem;
typedef struct elemento_duplo Elem_Duplo;

void calcula_av1(struct aluno *al) {
    al->av1 = ((al->ap1 + al->ap2 + al->ap3 + al->ap4) / 4) * 0.4 + (al->np * 0.6);
}

Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li)
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

void imprime_lista(struct elemento *lista) {
    struct elemento *temp = lista;
    putchar('\n');
    while (temp != NULL)
    {
        printf("\t- - - - - - - - - - - - - - - -\n\n");
        printf("\t\tMatrícula: %d \n\t\tNome: %s \n\t\tAV1: %.2f\n\n", temp->dados.matricula, temp->dados.nome, temp->dados.av1);
        temp = temp->prox;
    }
    printf("\t- - - - - - - - - - - - - - - -\n");
}

struct elemento* insere_ordenado(struct elemento *lista, struct aluno al) {
    struct elemento *novo = (struct elemento*) malloc(sizeof(struct elemento));
    struct elemento *atual = lista, *anterior = NULL;

    calcula_av1(&al);
    novo->dados = al;
    novo->prox = NULL;

    if (lista == NULL || al.av1 > lista->dados.av1)
    {
        novo->prox = lista;
        return novo;
    }

    while (atual != NULL && atual->dados.av1 > al.av1)
    {
        anterior = atual;
        atual = atual->prox;
    }

    novo->prox = atual;
    anterior->prox = novo;

    return lista;
}

struct elemento* juntar_listas(struct elemento *lista1, struct elemento *lista2) {
    struct elemento *lista_combinada = NULL;
    struct elemento *temp1 = lista1;
    struct elemento *temp2 = lista2;

    while (temp1 != NULL )
    {
        lista_combinada = insere_ordenado(lista_combinada, temp1->dados);
        temp1 = temp1->prox;
    }

    while (temp2 != NULL )
    {
        lista_combinada = insere_ordenado(lista_combinada, temp2->dados);
        temp2 = temp2->prox;
    }
    
    return lista_combinada;
}

struct elemento* selecionar_10melhores(struct elemento *lista) {
    struct elemento* melhores_notas = NULL;
    struct elemento* temp = lista;
    int count = 0;

    while (temp != NULL && count < 10)
    {
        melhores_notas = insere_ordenado(melhores_notas, temp->dados);
        temp = temp->prox;
        count++;
    }

    return melhores_notas;
}

struct elemento* selecionar_10piores(struct elemento *lista) {
    struct elemento *piores = NULL;
    struct elemento *temp = lista;
    int total = 0, count = 0;

    while (temp != NULL)
    {
        total++;
        temp = temp->prox;
    }

    temp = lista;
    while (temp != NULL && count < (total - 10))
    {
        temp = temp->prox;
        count++;
    }

    while (temp != NULL)
    {
        piores = insere_ordenado(piores, temp->dados);
        temp = temp->prox;
    }

    return piores;
}

//                                                          - Duplas -

ListaDupla* insere_ordenado_duplamente(ListaDupla* lista, struct aluno al) {
    Elem_Duplo *novo = (Elem_Duplo*) malloc(sizeof(Elem_Duplo));
    if (novo == NULL) return 0;

    novo->dados = al;
    novo->prox = NULL;
    novo->ant = NULL;

    if (*lista == NULL)
        *lista = novo;
    
    else
    {
        Elem_Duplo *atual = *lista;
        while (atual != NULL && atual->dados.av1 > al.av1)
            atual = atual->prox;

        if (atual == NULL)
        {
            Elem_Duplo *ultimo = *lista;
            while (ultimo->prox != NULL)
                ultimo = ultimo->prox;

            ultimo->prox = novo;
            novo->ant = ultimo;
        } 
        
        else if (atual == *lista)
        {
            novo->prox = *lista;
            (*lista)->ant = novo;
            *lista = novo;
        } 
        
        else
        {
            novo->prox = atual;
            novo->ant = atual->ant;
            atual->ant->prox = novo;
            atual->ant = novo;
        }
    }

    return lista;
}

ListaDupla* concatena_listas_duplamente(Lista* lista1, Lista* lista2) {
    ListaDupla* lista_dupla = (ListaDupla*) malloc(sizeof(ListaDupla));
    if (lista_dupla == NULL)
        return NULL;

    *lista_dupla = NULL;
    Elem *temp1 = *lista1;
    Elem *temp2 = *lista2;
    while (temp1 != NULL)
    {
        lista_dupla = insere_ordenado_duplamente(lista_dupla, temp1->dados);
        temp1 = temp1->prox;
    }

    while (temp2 != NULL)
    {
        lista_dupla = insere_ordenado_duplamente(lista_dupla, temp2->dados);
        temp2 = temp2->prox;
    }

    return lista_dupla;
}

ListaDupla* inverter_lista_dupla(ListaDupla* lista) {
    if (*lista == NULL)
        return NULL;

    Elem_Duplo *atual = *lista;
    Elem_Duplo *temp = NULL;
    while (atual != NULL)
    {
        temp = atual->ant;
        atual->ant = atual->prox;
        atual->prox = temp;
        atual = atual->ant;
    }

    if (temp != NULL)
        *lista = temp->ant;

    return lista;
}

void imprime_lista_dupla(ListaDupla* lista) {
    if (*lista == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    Elem_Duplo* temp = *lista;
    while (temp != NULL)
    {
        printf("\t- - - - - - - - - - - - - - - -\n\n");
        printf("\t\tMatrícula: %d \n\t\tNome: %s \n\t\tAV1: %.2f\n\n", temp->dados.matricula, temp->dados.nome, temp->dados.av1);
        temp = temp->prox;
    }
    printf("\t- - - - - - - - - - - - - - - -\n");
}


void limpar_terminal()                          // Função para limpar o terminal
{
    #if defined(_WIN32) || defined(_WIN64) // verifica se o sistema é windows 32 bits ou 64 bits
        system("cls"); // windows
    #else
        system("clear"); // linux e mac
    #endif
}

void colocar_terminal_UTF8() {
    SetConsoleOutputCP(CP_UTF8); // Configura o terminal para UTF-8. Serve para colocar caracteres especiais no terminal
}

void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}