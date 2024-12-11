#include <stdio.h>
#include "ListaSequencial.h"

int main() {
    colocar_terminal_UTF8();
    Lista *li = cria_lista();
    struct aluno al;
    int opcao, cod, ind;
    char charAux_opcao[2];

    limpar_terminal();
    printf("Bem vindo ao controle de notas da escola Guilherme's Basics on Education and Learning! Por favor, escolha uma opção para começar.\n\n\n");
    
    do {
        printf("\t\t\t\t- - - - - - - - - - - - - - - - - Menu - - - - - - - - - - - - - - - - -\n\n");
        
        printf("1 - Inserir aluno");
        printf("\n2 - Remover primeiro aluno \n3 - Remover último aluno \n4 - Remover aluno pelo código");
        printf("\n5 - Consultar aluno por índice\n6 - Consultar aluno por código");
        printf("\n7 - Imprimir lista\n\n0 - Sair\n\n\t\t> Opção: ");
        scanf("%s", &charAux_opcao);
        opcao = CharOuNum_opcao(charAux_opcao[0]);
        strcpy(charAux_opcao, " "); flush_in();

        switch(opcao) {
            case 1: limpar_terminal();
                    printf("Digite o código do aluno: ");
                    scanf("%d", &al.codigo); flush_in();
                    printf("Digite o nome do aluno: ");
                    scanf("%s", al.nome); flush_in();

                    escanearNotasAPs: printf("Digite as 4 notas das atividades práticas: ");
                    scanf("%f %f %f %f", &al.ap1, &al.ap2, &al.ap3, &al.ap4); flush_in(); // Tem um problema se colocar letra na nota, e eu não sei resolver
                    if (al.ap1 < 0 || al.ap1 > 10 || al.ap2 < 0 || al.ap2 > 10 || al.ap3 < 0 || al.ap3 > 10 || al.ap4 < 0 || al.ap4 > 10)
                        {al.ap1 = 0; al.ap2 = 0; al.ap3 = 0; al.ap4 = 0; printf("\nNotas inválidas. Tente novamente:\n"); goto escanearNotasAPs;}

                    EscanearNotaNP: printf("Digite a nota da prova: ");
                    scanf("%f", &al.np); flush_in();
                    if(al.np < 0 || al.np > 10)
                        {al.np = 0; printf("\nNota inválida. Tente novamente:\n"); goto EscanearNotaNP;}

                    if (insere_lista_ordenada(li, al))
                        {limpar_terminal(); printf("Aluno inserido com sucesso!\n");}
                    else
                        {limpar_terminal(); printf("Falha ao inserir aluno. Tente novamente:\n");}
                    break;

            case 2: if (remove_lista_inicio(li))
                        {limpar_terminal(); printf("Primeiro aluno removido com sucesso.\n\n");}
                    else
                        {limpar_terminal(); printf("Falha ao remover aluno.\n\n");}
                    break;

            case 3: limpar_terminal();
                    if (remove_lista_final(li))
                        printf("Último aluno removido com sucesso.\n\n");
                    else
                        printf("Falha ao remover aluno.\n\n");
                    break;

            case 4: limpar_terminal();
                    printf("Digite o código do aluno: ");
                    scanf("%d", &cod); flush_in();
                    if (remove_lista_pelo_codigo(li, cod))
                        {limpar_terminal(); printf("Aluno removido com sucesso.\n\n");}
                    else
                        {limpar_terminal(); printf("Aluno não encontrado.\n\n");}
                    break;

            case 5: limpar_terminal();
                    printf("Digite o índice do aluno: ");
                    scanf("%d", &ind); flush_in();
                    limpar_terminal();
                    consulta_lista_pos(li, ind);
                    break;

            case 6: limpar_terminal();
                    printf("Digite o código do aluno: ");
                    scanf("%d", &cod); flush_in();
                    limpar_terminal();
                    consulta_lista_cod(li, cod);
                    break;

            case 7: limpar_terminal();
                    imprime_lista(li);
                    printf("\n\t\t > Continuar <ENTER>"); flush_in(); limpar_terminal();
                    break;

            case 0: limpar_terminal();
                    printf("\nSaindo...\n\n");
                    break;

            default:limpar_terminal(); flush_in();
                    printf("Opção inválida!\n\n");
                    break;
        }
    } while(opcao != 0);

    libera_lista(li);
    return 0;
}
