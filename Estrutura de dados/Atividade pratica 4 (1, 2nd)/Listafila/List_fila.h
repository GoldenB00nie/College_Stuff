#ifndef LIST_FILA_H
#define LIST_FILA_H

typedef struct paciente {
    int id_paciente;  // Identificador do paciente
    char nome_paciente[50];  // Nome do paciente
    char tipo_transplante[20];  // Tipo de transplante (Coração, Córnea, Medula)
} Paciente;

typedef struct tempos
{
    double tempo_insercao;
    double tempo_remocao;
} Tempos;

typedef struct elemento {
    Paciente dados;
    struct elemento *prox;
} Elem;

typedef struct elemento_tempos
{
    Tempos dados_tempos;
    struct elemento_tempos* prox;
} Elem_t;

typedef Elem* Fila;
typedef Elem_t* Lista_t;

// Funções para manipulação da fila
Fila* cria_fila();
    Lista_t* cria_lista_t();
int insere_fila(Fila* fi, Paciente dados);
    int insere_lista_t(Lista_t* li, Tempos dados_tempos);
int remove_fila(Fila* fi);
Paciente* consulta_primeiro(Fila* fi);
int tamanho_fila(Fila* fi);
void libera_fila(Fila* fi);
void imprime_operacao(char* operacao, Fila* lista, Paciente* p);
Paciente gera_paciente(int id);

#endif
