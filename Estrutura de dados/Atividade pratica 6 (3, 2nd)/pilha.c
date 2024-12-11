#include "pilha.h"

pilha* cria_pilha () {
    pilha* pi = (pilha*) malloc(sizeof(pilha));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}

int insere_pilha (pilha* pi, struct conversoes dados) {
    Elem* novo = (Elem*)malloc(sizeof(Elem));
    if (novo == NULL)
        return 0; // Falha na alocação

    novo->dados = dados;
    novo->prox = *pi;
    *pi = novo;
    return 1; // Inserção bem-sucedida
}

int remove_pilha (pilha* pi) {
    if (*pi == NULL)
        return 0; // A pilha está vazia

    Elem* temp = *pi;
    while (temp->prox != NULL) // Percorre até o fim da pilha
        temp = temp->prox;
    free(temp);
    return 1; // Remoção bem-sucedida
}

int consulta_elem (pilha* pi, int num) {
    if (*pi == NULL)
        return 0; // A pilha está vazia
    
    Elem* aux = *pi;
    aux->dados.posicao = 1;
    while (aux->prox->dados.num_escolhido != num) // Percorre até o fim da pilha
    {
        aux = aux->prox;
        aux->dados.posicao++;
    }

    transforma_num(aux);
    printf("---------------------------------\n");
    printf("Posição: %d\n", aux->dados.posicao);
    printf("Número escolhido: %d\n", aux->dados.num_escolhido);
    printf("Tipo de Conversão: %s\n", aux->dados.string_tipo); 
    printf("Resultado da conversão: %s\n", aux->dados.resultado_conversao);
    printf("---------------------------------\n");
    return 1;
}

int imprime_lista (pilha* pi) {
    if (*pi == NULL)
        return 0; // A pilha está vazia
    
    Elem* aux = *pi;
    aux->dados.posicao = 1;
    while (aux->prox != NULL) // Percorre até o fim da pilha
    {
        transforma_num(aux);
        printf("---------------------------------\n");
        printf("Posição: %d\n", aux->dados.posicao);
        printf("Número escolhido: %d\n", aux->dados.num_escolhido);
        printf("Tipo de Conversão: %s\n", aux->dados.string_tipo); 
        printf("Resultado da conversão: %s\n", aux->dados.resultado_conversao);
        printf("---------------------------------\n");
        aux = aux->prox;
        aux->dados.posicao++;
    }
    return 1;
}

int destroi_pilha (pilha* pi) {
    if (*pi == NULL)
        return 0; // A pilha está vazia
    free(pi);
    return 1;
}

void transforma_num (Elem* no) {
    switch (no->dados.tipo_conversao) {
        case 2: strcpy(no->dados.string_tipo, "Binário");
                itoa(no->dados.num_escolhido, no->dados.resultado_conversao, 2);
                break;
        case 8: strcpy(no->dados.string_tipo, "Octal");
                itoa(no->dados.num_escolhido, no->dados.resultado_conversao, 8);
                break;
        case 10: strcpy(no->dados.string_tipo, "Inteiro");
                 itoa(no->dados.num_escolhido, no->dados.resultado_conversao, 10);
                 break;
        case 16: strcpy(no->dados.string_tipo, "Hexadecimal");
                 itoa(no->dados.num_escolhido, no->dados.resultado_conversao, 16);
                 break;
        default: strcpy(no->dados.string_tipo, "Não reconhecido");
                 strcpy(no->dados.resultado_conversao, "Erro ao calcular");
    }
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