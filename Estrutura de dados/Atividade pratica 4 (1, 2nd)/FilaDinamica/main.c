#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FilaDinamica.h"
#include <windows.h>

int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8); // Configura o terminal para UTF-8. Serve para colocar caracteres especiais no terminal

    // Criação das filas para cada tipo de transplante
    Fila *fila_coracao = cria_fila();
    Fila *fila_cornea = cria_fila();
    Fila *fila_medula = cria_fila();
    Lista_t* li = cria_lista_t();
    int qnt_repeticoes = 20;

    clock_t clock_start_programa = clock(), clock_end_programa;
    for(int i = 0; i < qnt_repeticoes; i++)
    {
        // Simula 100 insercoes
        clock_t clock_start = clock(), clock_end;
        for (int j = 1; j <= 100; j++) {
            struct paciente p = gera_paciente(j);
            int fila_escolhida = rand() % 3;  // Escolhe: 0 = CORAÇÃO, 1 = CÓRNEA, 2 = MEDULA. 

            if (fila_escolhida == 0) {
                insere_fila(fila_coracao, p);
                printf("Inserido na fila CORACAO: %s\n", p.nome);
            } else if (fila_escolhida == 1) {
                insere_fila(fila_cornea, p);
                printf("Inserido na fila CORNEA: %s\n", p.nome);
            } else {
                insere_fila(fila_medula, p);
                printf("Inserido na fila MEDULA: %s\n", p.nome);
            }
        }
        clock_end = clock();
        double tempo_insercao = (double) (clock_end - clock_start) / CLOCKS_PER_SEC;

        // Simulação de 40 remoções aleatórias
        clock_start = clock();
        for (int j = 1; j <= 40; j++) {
            int fila_escolhida = rand() % 3;  // Escolha aleatória da fila: 0 = CORAÇÃO, 1 = CÓRNEA, 2 = MEDULA

            if (fila_escolhida == 0) {
                if (remove_fila(fila_coracao))
                    printf("Removido da fila CORACAO\n");
                else
                    printf("Fila CORACAO está vazia\n");
            } else if (fila_escolhida == 1) {
                if (remove_fila(fila_cornea))
                    printf("Removido da fila CORNEA\n");
                else
                    printf("Fila CORNEA está vazia\n");
            } else {
                if (remove_fila(fila_medula))
                    printf("Removido da fila MEDULA\n");
                else
                    printf("Fila MEDULA está vazia\n");
            }
        }
        clock_end = clock();
        double tempo_remocao = (double) (clock_end - clock_start) / CLOCKS_PER_SEC;

        Tempos t;
        t.tempo_insercao = tempo_insercao;
        t.tempo_remocao = tempo_remocao;
        insere_lista_t(li, t);
        
        while(fila_coracao->qtd != 0) // Remove todos os elementos das filas para repetir as acoes
            remove_fila(fila_coracao);
        while(fila_cornea->qtd != 0)
            remove_fila(fila_cornea);
        while(fila_medula->qtd != 0)
            remove_fila(fila_medula);

        printf("\nTempo de inserção: %.1f ms ou %f s", tempo_insercao * 1000, tempo_insercao);
        printf("\nTempo de remoção: %.1f ms ou %f s\n", tempo_remocao * 1000, tempo_remocao);
    }

    printf("\n---------------------------------------\n");
    clock_end_programa = clock();
    double tempo_programa = (double) (clock_end_programa - clock_start_programa) / CLOCKS_PER_SEC;
    printf("Programa finalizado em %.1f ms ou %f s\n", tempo_programa * 1000, tempo_programa);

    Elem_t* temp = *li;
    double soma_insercao = 0, soma_remocao = 0;
    while (temp != NULL) {
        soma_insercao += temp->dados_tempos.tempo_insercao;
        soma_remocao += temp->dados_tempos.tempo_remocao;
        temp = temp->prox;
    }

    double media_insercao = soma_insercao / qnt_repeticoes,
           media_remocao = soma_remocao / qnt_repeticoes;
    
    printf("\nA média das inserções é: %.1f ms ou %f s\n"
           "A média das remoções é: %.1f ms ou %f s\n", 
           media_insercao * 1000, media_insercao, media_remocao * 1000, media_remocao);

    // Liberação das filas
    libera_fila(fila_coracao);
    libera_fila(fila_cornea);
    libera_fila(fila_medula);

    return 0;
}