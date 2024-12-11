#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ListaSequencial.h" //inclui os Protótipos

struct lista
{
    int contagem;
    struct aluno dados[MAX];
};

float calcula_av1(struct aluno al) {
    // Ordenar as notas das atividades práticas (APs)
    float notas[4] = {al.ap1, al.ap2, al.ap3, al.ap4};
    
    // Ordenando as notas em ordem decrescente para obter as maiores notas
    for(int i = 0; i < 4; i++) {
        for(int j = i + 1; j < 4; j++) {
            if(notas[i] < notas[j]) {
                float temp = notas[i];
                notas[i] = notas[j];
                notas[j] = temp;
            }
        }
    }
    
    // Calcular a média das maiores notas
    float media_aps = (notas[0] + notas[1] + notas[2] + notas[3]) / 4.0;

    // Calcular a nota final (AV1)
    return (media_aps * 0.4) + (al.np * 0.6);
}

Lista* cria_lista() {
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if(li != NULL)
        li->contagem = 0;
    return li;
}

void libera_lista(Lista* li)
{
    free(li);
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return -1;
    else
        return li->contagem;
}

int lista_cheia(Lista* li){
    if(li == NULL)
        return -1;
    return (li->contagem == MAX); // Se igual a MAX returna 1, senão retorna 0
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return -1;
    return (li->contagem == 0); // Se contagem igual a 0 returna 1, senão retorna 0
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;

    int i = 0;
    if(i == li->contagem) {
        printf("Lista vazia.\n");
    }

    else {
        printf("-------------------------------\n");
        for(i; i < li->contagem; i++) {
            printf("Índice: %d\n", i+1);
            printf("Codigo: %d\n",li->dados[i].codigo);
            printf("Nome: %s\n",li->dados[i].nome);
            printf("APs (1 a 4): %.1f | %.1f | %.1f | %.1f\n", li->dados[i].ap1,
                                                               li->dados[i].ap2,
                                                               li->dados[i].ap3,
                                                               li->dados[i].ap4);
            printf("NP: %.1f\n", li->dados[i].np);
            printf("AV1 = %.1f\n",li->dados[i].av1);
            printf("-------------------------------\n");
        }
    }
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if(li == NULL || lista_cheia(li))
        return 0;

    int i = 0;
    while(i < li->contagem && li->dados[i].codigo < al.codigo)
        i++;

    // Deslocar todos os elementos após o ponto de inserção
    for(int k = li->contagem - 1; k >= i; k--)
        li->dados[k + 1] = li->dados[k];

    // Inserir o aluno na posição correta
    li->dados[i] = al;
    li->dados[i].av1 = calcula_av1(al); // Calcula e armazena a nota final
    li->contagem++;

    return 1;
}

int remove_lista_inicio(Lista* li) {
    if(li == NULL || lista_vazia(li))
        return 0;
    for(int i = 0; i < li->contagem - 1; i++)
        li->dados[i] = li->dados[i + 1];
    li->contagem--;
    return 1;
}

int remove_lista_final(Lista* li) {
    if(li == NULL || lista_vazia(li))
        return 0;
    li->contagem--;
    return 1;
}

int remove_lista_pelo_codigo(Lista* li, int cod) {
    if(li == NULL || lista_vazia(li))
        return 0;

    int i = 0;
    while(i < li->contagem && li->dados[i].codigo != cod)
        i++;

    if(i == li->contagem) // Código não encontrado
        return 0;

    for(int k = i; k < li->contagem - 1; k++)
        li->dados[k] = li->dados[k + 1];

    li->contagem--;
    return 1;
}

int consulta_lista_pos(Lista* li, int pos) {
    if(li == NULL || pos <= 0 || pos > li->contagem) {
        printf("Índice do aluno não encontrado.\n\n");
        return 0;
    }
    
    struct aluno al = li->dados[pos - 1];
    printf("-------------------------------\n");
    printf("Índice: %d\n", pos);
    printf("Codigo: %d\n",al.codigo);
    printf("Nome: %s\n",al.nome);
    printf("APs (1 a 4): %.1f | %.1f | %.1f | %.1f\n", al.ap1, al.ap2, al.ap3, al.ap4);
    printf("NP: %.1f\n", al.np);
    printf("AV1 = %.1f\n",al.av1);
    printf("-------------------------------\n\n");
    return 1;
}

int consulta_lista_cod(Lista* li, int cod) {
    if(li == NULL)
        return 0;

    int i = 0;
    while(i < li->contagem && li->dados[i].codigo != cod)
        i++;

    if(i == li->contagem) { // Código não encontrado
        printf("Código do aluno não encontrado.\n\n");
        return 0;
    }

    struct aluno al = li->dados[i];
    printf("-------------------------------\n");
    printf("Codigo: %d\n",al.codigo);
    printf("Nome: %s\n",al.nome);
    printf("APs (1 a 4): %.1f | %.1f | %.1f | %.1f\n", al.ap1, al.ap2, al.ap3, al.ap4);
    printf("NP: %.1f\n", al.np);
    printf("AV1 = %.1f\n",al.av1);
    printf("-------------------------------\n\n");
    return 1;
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

int CharOuNum_opcao(char charAux_opcao) {
    if(!isdigit(charAux_opcao))
        return -1;
    else {
        char str[2];
        str[0] = charAux_opcao; str[1] = '\0';
        return atoi(str);
    }
}