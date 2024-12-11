#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "List_fila.h"

//lista agindo como fila
int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8); // Configura o terminal para UTF-8. Serve para colocar caracteres especiais no terminal
    Fila* fila_coracao = cria_fila(); //cria as listas
    Fila* fila_cornea = cria_fila();
    Fila* fila_medula = cria_fila();
    Lista_t* li = cria_lista_t();
    int qnt_repeticoes = 20;

    clock_t clock_start_programa = clock(),
            clock_end_programa;
    
    for (int i = 0; i < qnt_repeticoes; i++)
    {
        int operacoes_insercao = 100;
        int operacoes_remocao = 40;
        int id_atual = 1;
        int escolha_lista;
        double tempo_insercao, tempo_remocao;


        clock_t clock_start = clock(), clock_end;
        while (operacoes_insercao > 0)
        {
            escolha_lista = rand() % 3; // Escolhe aleatoriamente a fila (coração, córnea, ou medula)
            Fila* lista_escolhida;
            
            // Define qual lista foi escolhida
            if (escolha_lista == 0) { //escolhe uma lista aleatoria
                lista_escolhida = fila_coracao;
            } else if (escolha_lista == 1) {
                lista_escolhida = fila_cornea;
            } else {
                lista_escolhida = fila_medula;
            }

            Paciente p = gera_paciente(id_atual++);
                insere_fila(lista_escolhida, p);
                imprime_operacao("Inserido", lista_escolhida, &p);
                operacoes_insercao--;
        }
        clock_end = clock();
        tempo_insercao = (double) (clock_end - clock_start) / CLOCKS_PER_SEC;
        
        clock_start = clock();
        while (operacoes_remocao > 0)
        {
            escolha_lista = rand() % 3; // Escolhe aleatoriamente a fila (coração, córnea, ou medula)
            Fila* lista_escolhida;
            
            // Define qual lista foi escolhida
            if (escolha_lista == 0) { //escolhe uma lista aleatoria
                lista_escolhida = fila_coracao;
            } else if (escolha_lista == 1) {
                lista_escolhida = fila_cornea;
            } else {
                lista_escolhida = fila_medula;
            }

            Paciente* primeiro = consulta_primeiro(lista_escolhida);
                if (primeiro != NULL) {
                    imprime_operacao("Removido", lista_escolhida, primeiro);
                    remove_fila(lista_escolhida);
                    operacoes_remocao--;
                }
        }
        clock_end = clock();
        tempo_remocao = (double) (clock_end - clock_start) / CLOCKS_PER_SEC;

        Tempos t;
        t.tempo_insercao = tempo_insercao;
        t.tempo_remocao = tempo_remocao;
        insere_lista_t(li, t);

        while(*fila_coracao != NULL) // Remove todos os elementos das filas para repetir as acoes
            remove_fila(fila_coracao);
        while(*fila_cornea != NULL)
            remove_fila(fila_cornea);
        while(*fila_medula != NULL)
            remove_fila(fila_medula);
        
        printf("\n\nTempo de inserção: %.1f ms ou %f s\n", tempo_insercao * 1000, tempo_insercao);
        printf("Tempo de remoção: %.1f ms ou %f s\n", tempo_remocao * 1000, tempo_remocao);
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
    

    // Libera as três listas após as operações
    libera_fila(fila_coracao);
    libera_fila(fila_cornea);
    libera_fila(fila_medula);

    return 0;
}

// Parte do codigo que estava com defeito
/*for (int i = 0; i < operacoes_insercao + operacoes_remocao; i++) {
        int escolha_lista = rand() % 3; // Escolhe aleatoriamente a fila (coração, córnea, ou medula)
        Fila* lista_escolhida;
        
        // Define qual lista foi escolhida
        if (escolha_lista == 0) { //escolhe uma lista aleatoria
            lista_escolhida = fila_coracao;
        } else if (escolha_lista == 1) {
            lista_escolhida = fila_cornea;
        } else {
            lista_escolhida = fila_medula;
        }
        
        int escolha_operacao = rand() % 2; // Escolhe aleatoriamente entre inserir e remover

        if ((escolha_operacao == 0 || operacoes_insercao > 0) && operacoes_insercao > 0) {
            Paciente p = gera_paciente(id_atual++);
            insere_fila(lista_escolhida, p);
            imprime_operacao("Inserido", lista_escolhida, &p);
            operacoes_insercao--;
        } else if ( escolha_operacao != 0 && operacoes_remocao > 0) {
            Paciente* primeiro = consulta_primeiro(lista_escolhida);
            if (primeiro != NULL) {
                imprime_operacao("Removido", lista_escolhida, primeiro);
                remove_fila(lista_escolhida);
                operacoes_remocao--;
            }
        }
    }*/