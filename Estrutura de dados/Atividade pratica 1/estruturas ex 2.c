#include <stdio.h>
#include <ctype.h>
#include <windows.h>

/*
 1. Escreva um programa que usa uma estrutura capaz de armazenar dados de solicitações de empréstimos de clientes de um banco.
    O programa deve ler os seguintes dados: nome do cliente, salário do cliente, o valor do empréstimo e o número de meses para quitação.
        A) O programa deve calcular o valor da parcela do empréstimo requerido.
TODO:       B) Se o valor da parcela for maior que 20% do salário, o empréstimo será reprovado, caso contrário, o empréstimo será aprovado.
TODO: 2. Simule a solicitação de 10 empréstimos. No final, imprima a quantidade de empréstimos concedidos e a quantidade de
*        empréstimos não concedidos.
*/

// !                                                            Estruturas

struct Banco
{
    char nome[50];
    float salario, valorEmprestimo, valorParcela;
    int mesesQuitacao;

    
} Cliente[10];

// ! Fim de estruturas

// ?                                                            Cálculos

void calcularParcela(int vezCliente)
{
    if (Cliente[vezCliente].mesesQuitacao == 0)
        Cliente[vezCliente].valorParcela = Cliente[vezCliente].valorEmprestimo;
    else
        Cliente[vezCliente].valorParcela = Cliente[vezCliente].valorEmprestimo / Cliente[vezCliente].mesesQuitacao;
}

// ? Fim dos cálculos

//                                                              Funções
void inicializarClientes()
{
    for (int i = 0; i < 10; i++)
    {
        strcpy(Cliente[i].nome, ""); Cliente[i].salario = -1, Cliente[i].valorEmprestimo = -1;
        Cliente[i].mesesQuitacao = -1; Cliente[i].valorParcela = -1;
    }
}
int aprovarEmprestimo(int vezCliente)
{
    if (Cliente[vezCliente].valorEmprestimo > Cliente[vezCliente].salario / 5)
        return 0;
    else
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

// Fim de funções
int main()
{
    SetConsoleOutputCP(CP_UTF8); // permite letras com acentos de aparecerem no terminal
    inicializarClientes();
    limpar_terminal();

    for (int vezCliente = 0; vezCliente < 10; vezCliente++)
    {
        reinserirDados: fflush(stdin);
        printf("Bem vindo ao Banco do Guilherme, cliente %d. Por favor insira o seu nome.\n\n", vezCliente +1);
        printf("Nome: "); gets(Cliente[vezCliente].nome);

        limpar_terminal();
        printf("%s, insira a quantidade de dinheiro que você possui.\n\n", Cliente[vezCliente].nome);
        while (1)
        {
            printf("Salário: "); scanf(" %f", &Cliente[vezCliente].salario);
            if (Cliente[vezCliente].salario < 0)
                {Cliente[vezCliente].salario = -1; printf("\n\nSalário inválido. Tente novamente.\n");}
            else break;
        }

        limpar_terminal();
        printf("Salário inserido com sucesso. Agora insira o valor do empréstimo que quer. (mín = R$ 1,00)\n\n");
        while (1)
        {
            printf("Valor do empréstimo: "); scanf(" %f", &Cliente[vezCliente].valorEmprestimo);
            if (Cliente[vezCliente].valorEmprestimo <= 0) 
                {Cliente[vezCliente].valorEmprestimo = -1; printf("\n\nValor incorreto ou insuficiente. Tente novamente.\n");}
            else break;
        }

        limpar_terminal();
        printf("Valor do empréstimo inserido com sucesso. Insira em quantos meses quer quitar. (máx = 12)\n\n");
        while (1)
        {
            printf("Meses para quitação: "); scanf("%d", &Cliente[vezCliente].mesesQuitacao);
            if (Cliente[vezCliente].mesesQuitacao < 0 || Cliente[vezCliente].mesesQuitacao > 12)
                {Cliente[vezCliente].mesesQuitacao = -1; printf("\n\nQuantidade de meses inválido ou excedente. Tente novamente.\n");}
            else break;
        }

        calcularParcela(vezCliente);
        limpar_terminal();
        char opcao = ' ';
        int aprovarCliente = -1;

        printf("Meses para quitação inserido com sucesso. Aqui estão suas informações, caso estejam erradas você pode reinserir elas.\n\n");
        printf("Nome: \t\t\t%s", Cliente[vezCliente].nome);
        printf("\nSalário: \t\tR$ %.2f", Cliente[vezCliente].salario);
        printf("\nValor do empréstimo: \tR$ %.2f", Cliente[vezCliente].valorEmprestimo);
        printf("\nMeses para quitação: \t%d", Cliente[vezCliente].mesesQuitacao);
        printf("\nValor da parcela: \tR$ %.2f", Cliente[vezCliente].valorParcela);
        printf("\n\n\t\t> Reinserir (R) \t\t> Continuar (C) \t\t> Opção: "); scanf(" %c", &opcao);

        limpar_terminal();
        opcao = tolower(opcao);
        switch (opcao)
        {
        case 'r': goto reinserirDados; break;
        case 'c': aprovarCliente = aprovarEmprestimo(vezCliente);
                switch (aprovarCliente)
                {
                case 0: printf("Empréstimo negado."); break;
                case 1: printf("Empréstimo Aprovado."); break;
                default: printf("Erro ao calcular a aprovação. Empréstimo automaticamente negado.");
                } break;
        default: printf("Opção inexistente. Tente novamente."); break;
        }

        fflush(stdin);
        printf("\n\n\n\n\n\n\nPressione <ENTER> para continuar."); getchar();
        limpar_terminal();
    }
}

// conta