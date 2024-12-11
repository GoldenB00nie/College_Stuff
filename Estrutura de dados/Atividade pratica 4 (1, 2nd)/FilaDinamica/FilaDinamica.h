struct paciente{
    int id;
    char nome[30];
    char tipo_transplante[10]; // Ex: "CORAÇÃO", "CÓRNEA", "MEDULA"
};

struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
};

typedef struct tempos
{
    double tempo_insercao;
    double tempo_remocao;
} Tempos;

typedef struct elemento_tempos
{
    Tempos dados_tempos;
    struct elemento_tempos* prox;
} Elem_t;

typedef struct fila Fila;
typedef Elem_t* Lista_t;

Fila* cria_fila();
    Lista_t* cria_lista_t();
void libera_fila(Fila* fi);
int tamanho_fila(Fila* fi);
int fila_vazia(Fila* fi);
int insere_fila(Fila* fi, struct paciente pc);
    int insere_lista_t(Lista_t* li, Tempos dados_tempos);
int remove_fila(Fila* fi);
void imprime_fila(Fila* fi);
struct paciente gera_paciente(int id);

