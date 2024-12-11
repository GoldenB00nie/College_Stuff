#include <stdio.h>
#include "ListaDinEncadeada.h"

struct aluno estrutura_de_dados[10];
struct aluno fabrica_de_projetos2[10];

int main() {
    colocar_terminal_UTF8();
    struct aluno al;
    struct elemento *lista_estrutura = NULL;
    struct elemento *lista_fabrica = NULL;
    
    Lista *li = cria_lista();

    short int opcao; char opcao_Q1;
    limpar_terminal();

    // Inserir alunos nas listas
    for (int i = 0; i < 10; i++) {
        lista_estrutura = insere_ordenado(lista_estrutura, estrutura_de_dados[i]);
        lista_fabrica = insere_ordenado(lista_fabrica, fabrica_de_projetos2[i]);
    }

    struct elemento *lista_combinada = juntar_listas(lista_estrutura, lista_fabrica);
    struct elemento *Os10_melhores = selecionar_10melhores(lista_combinada);
    struct elemento *Os10_piores = selecionar_10piores(lista_combinada);

    ListaDupla* lista_concatenada = concatena_listas_duplamente(&lista_estrutura, &lista_fabrica);
    
    while (1) {
        printf("Escolha uma das questões: \n\n");
        Escolher_Questao:
        printf("1) Crie 2 (duas) listas dinâmicas encadeadas, uma para cada disciplina, e cadastre ");
        printf("os dados listados acima ordenados pela nota final (da maior para a menor) [AP3].\n\n");
        printf("2) Crie uma terceira lista dinâmica encadeada que liste as 10 melhores notas finais ");
        printf("ordenadas da maior para a menor considerando as duas disciplinas [AP3].\n\n");
        printf("3) Crie uma quarta lista dinâmica encadeada que liste as 10 piores notas finais");
        printf("ordenadas da maior para a menor considerando as duas disciplinas [AP3].\n\n");
        printf("4) Crie uma lista dinâmica duplamente encadeada que concatena as duas listas");
        printf("encadeadas ordenando pela nota final (da maior para a menor) [AP4].\n\n");
        printf("5) Inverta a ordem da ordenação da lista duplamente encadeada (da menor para a");
        printf("maior) usando os ponteiros [AP4].\n\n\n");

        printf("\t> Sair (0) \t> Opção: "); scanf(" %hd", &opcao); fflush(stdin);

        switch (opcao) {
            case 0: break;

            case 1: limpar_terminal();
                Escolher_Lista_Q1: opcao_Q1 = ' ';
                printf("A) Lista dos alunos de Estrutura de Dados\n");
                printf("B) Lista dos alunos de Fábrica de projetos\n\n");
                printf("\t> Voltar (V) \t> Opção: "); scanf(" %c", &opcao_Q1); fflush(stdin);
                limpar_terminal();
                switch (opcao_Q1) {
                    case 'A': case 'a': printf("Lista dos alunos de Estrutura de Dados:\n");
                                        imprime_lista(lista_estrutura);
                                        printf("\n\n\tAperte <ENTER> para voltar.");
                                        getchar(); limpar_terminal(); break;
                    
                    case 'B': case 'b': printf("\nLista dos alunos de Fabrica de Projetos 2:\n");
                                        imprime_lista(lista_fabrica);
                                        printf("\n\n\tAperte <ENTER> para voltar.");
                                        getchar(); limpar_terminal(); break;
                    
                    case 'V': case 'v': limpar_terminal(); break;

                    default: printf("Caractere inválido. Tente novamente.\n");
                            goto Escolher_Lista_Q1; break;
                } break;
            
            case 2: limpar_terminal();
                    printf("Os 10 melhores de Estrutura de Dados e Fábrica de projetos são:\n");
                    imprime_lista(Os10_melhores);
                    printf("\n\n\tAperte <ENTER> para voltar.");
                    getchar(); limpar_terminal(); break;

            case 3: limpar_terminal();
                    printf("Os 10 piores de Estrutura de Dados e Fábrica de projetos são:\n");
                    imprime_lista(Os10_piores);
                    printf("\n\n\tAperte <ENTER> para voltar.");
                    getchar(); limpar_terminal(); break;

            case 4: limpar_terminal();
                    printf("Lista dupla concatenada: \n");
                    imprime_lista_dupla(lista_concatenada);
                    printf("\n\n\tAperte <ENTER> para voltar.");
                    getchar(); limpar_terminal(); break;

            case 5: limpar_terminal();
                    printf("Lista dupla concatenada invertida: \n");
                    inverter_lista_dupla(lista_concatenada);
                    imprime_lista_dupla(lista_concatenada);
                    printf("\n\n\tAperte <ENTER> para voltar.");
                    getchar(); limpar_terminal(); break;

            if (opcao < 0 && opcao > 5) { // default
                    default: opcao = -1;
                    limpar_terminal();
                    printf("Número da questão não reconhecido. Tente novamente.\n\n");
                    goto Escolher_Questao; break;
            }

        }

        if (opcao == 0)
            {limpar_terminal(); printf("Saindo..."); break;}
    }

    return 0;
}

struct aluno estrutura_de_dados[10] = {
        {16350, "Joao", 5.0, 5.0, 5.5, 3.5, 4.5, 0.0},
        {17890, "Ricardo", 7.0, 8.0, 6.2, 4.3, 5.8, 0.0},
        {16350, "Bianca", 1.0, 1.1, 2.2, 2.7, 4.1, 0.0},
        {16350, "Jose", 1.0, 1.1, 2.5, 2.9, 3.1, 0.0},
        {11234, "Marcelo", 2.0, 7.0, 2.5, 2.9, 4.6, 0.0},
        {17890, "Carla", 7.0, 2.3, 2.4, 3.6, 4.3, 0.0},
        {17823, "Fabiano", 1.0, 1.7, 2.8, 3.0, 3.1, 0.0},
        {15212, "Ana", 8.0, 1.6, 2.9, 3.1, 3.5, 0.0},
        {15542, "Joaquim", 5.0, 8.6, 9.9, 8.1, 6.5, 0.0},
        {13452, "Gabriel", 8.0, 6.4, 9.5, 7.5, 5.7, 0.0}
    };

    struct aluno fabrica_de_projetos2[10] = {
        {16340, "Fábio", 8.0, 9.0, 7.5, 5.5, 9.5, 0.0},
        {17390, "Rafael", 9.0, 8.0, 8.5, 7.5, 5.0, 0.0},
        {12350, "Luana", 8.0, 9.1, 8.2, 7.7, 6.5, 0.0},
        {15350, "Carlos", 5.0, 7.1, 8.5, 9.9, 8.1, 0.0},
        {12244, "Maria", 8.0, 7.0, 8.5, 9.9, 8.5, 0.0},
        {14560, "Luiza", 9.0, 6.5, 7.5, 8.5, 7.5, 0.0},
        {12523, "Roberto", 8.0, 7.7, 8.8, 8.0, 6.1, 0.0},
        {15514, "Tiago", 9.0, 8.0, 9.9, 8.1, 7.5, 0.0},
        {13542, "Humberto", 8.0, 6.0, 8.9, 7.1, 8.5, 0.0},
        {16432, "Samuel", 6.0, 6.0, 9.5, 8.5, 7.0, 0.0}
    };