#include <stdio.h>
#include <ctype.h>
#include <windows.h> // * para a função limpar_terminal()

/* 
1. Escreva um programa que usa estruturas capazes de armazenar os pedidos dos clientes.
2. Simule 10 pedidos. No final, imprima o faturamento do dia.

Cardápio:       Índice      Especificação       Código      Preço
                  1         Cachorro-Quente     100         R$ 5.20
                  2         Bauru Simples       101         R$ 6.30
                  3         Bauru com ovo       102         R$ 6.50
                  4         Hambúrguer          103         R$ 7.20
                  5         Cheeseburger        104         R$ 8.30
                  6         Refrigerante        105         R$ 5.00

OBS: A auto avaliação está no final do código.
*/

// !                                                        Estruturas:

struct Lanchonete
{
    int QntPedidoCardapio [6];      // * 0 = cachorro, 1 = bauSimples, 2 = bauOvo, 3 = Hamburger, 4 = cheese, 5 = refri
    float valorTotalCliente;
} clientes[10];
 
void AtribuirValoresIniciaisClientes()
{
    for (int i = 0; i < 10; i++)
    {
        clientes[i].valorTotalCliente = 0;
        for (int j = 0; j < 6; j++)
        {
            clientes[i].QntPedidoCardapio[j] = 0;
        }
    }
}

// ! Fim de estruturas

// ?                                                          Cálculos

void calculoValorTotalCliente (int vezCliente)
{
        clientes[vezCliente].valorTotalCliente = 
                                        clientes[vezCliente].QntPedidoCardapio[0] * 5.2 + clientes[vezCliente].QntPedidoCardapio[1] * 6.3 + 
                                        clientes[vezCliente].QntPedidoCardapio[2] * 6.5 + clientes[vezCliente].QntPedidoCardapio[3] * 7.2 + 
                                        clientes[vezCliente].QntPedidoCardapio[4] * 8.3 + clientes[vezCliente].QntPedidoCardapio[5] * 5.0;
}

float calculoFaturamentoTotal()
{
    float faturamentoTotal;
    for (int i = 0; i < 10; i++)
    {
        faturamentoTotal += clientes[i].valorTotalCliente; 
    }
    
    return faturamentoTotal;
}

// ? Fim de cálculos

////                                                            Etc

void limpar_terminal()                          // Função para limpar o terminal
{
    #if defined(_WIN32) || defined(_WIN64) // verifica se o sistema é windows 32 bits ou 64 bits
        system("cls"); // windows
    #else
        system("clear"); // linux e mac
    #endif
}

    char tabelaCardapio [7][4][20] = {
                                      {"Índice",     " Especificação",    "   Código",   "    Preço"},
                                      {"1",         "Cachorro-quente",          "100",     "R$ 5,20"},
                                      {"2",           "Bauru simples",          "101",     "R$ 6,30"},
                                      {"3",           "Bauru com ovo",          "102",     "R$ 6,50"},
                                      {"4",              "Hambúrguer",         " 103",    " R$ 7,20"},
                                      {"5",           "Cheeseburguer",          "104",     "R$ 8,30"},
                                      {"6",            "Refrigerante",          "105",     "R$ 5,00"}
                                        };

//// Fim etc

int main ()
{
    AtribuirValoresIniciaisClientes();
    SetConsoleOutputCP(CP_UTF8); // permite letras com acentos de aparecerem no terminal
    limpar_terminal();

    char opcao[20];
    int numOpcao, codErro, codCompra;
    for (int vezCliente = 0; vezCliente < 10; vezCliente++)
    {

        printf("Bem vindo à lanchonete do Guilherme, cliente %d. Faça o pedido atráves do número do item, ou do código ou do nome.\n\n", vezCliente + 1);
        strcpy(opcao, "");
        while(1)
        {
            if (codCompra == 1)
                printf("Item %d adicionado ao carrinho com sucesso.\n\n", numOpcao);
            if (codErro == 1)
                printf("Número ou código de produto não reconhecido. Tente novamente.\n\n");
            else if (codErro == 2)
                printf("Texto inserido não reconhecido como um produto. Tente novamente.\n\n");
            
            codErro = 0; codCompra = 0; numOpcao = 0; strcpy(opcao, "");
            printf("Cardápio:\n");
            for (int i = 0; i < 7; i++) 
            {
                printf("\t\t");
                for (int j = 0; j < 4; j++) 
                {
                    printf("%-30s", tabelaCardapio[i][j]);
                }
                printf("\n"); 
            }
            
            printf("\n\n\t\t> Finalizar pedido (F)\t\t> Carrinho (C)\t\t> Opção: "); gets(opcao);

            int ehNumero = 1;
            for (int i = 0; opcao[i] != '\0'; i++)
            {
                if (!isdigit(opcao[i]))
                    {ehNumero = 0; break;}
            }
            
            if (ehNumero)
            {
                numOpcao = atoi(opcao);
                if (numOpcao >= 1 && numOpcao <= 6)
                    {clientes[vezCliente].QntPedidoCardapio[numOpcao-1]++; codCompra = 1;}
                else if (numOpcao >= 100 && numOpcao <= 105)
                    {numOpcao = numOpcao - 99; clientes[vezCliente].QntPedidoCardapio[numOpcao-1]++; codCompra = 1;}
                else
                    codErro = 1;
            }
            else
            {
                opcao[20] = tolower(opcao[20]);
                if (strcmp(opcao, "f") == 0)
                    {calculoValorTotalCliente(vezCliente); limpar_terminal(); break;}
                else if (strcmp(opcao, "c") == 0)
                {
                    while(1)
                    {
                        char opcaoCarrinho = ' ';
                        limpar_terminal();
                        if (codErro == 3)
                            printf("Caractere digitado não reconhecido como uma opção. Tente novamente.\n\n");
                        codErro = 0;

                        printf("Carrinho:\n\n");
                        printf("\t\tCachorro quente: \t   %d\n", clientes[vezCliente].QntPedidoCardapio[0]);
                        printf("\t\tBauru simples \t\t   %d\n", clientes[vezCliente].QntPedidoCardapio[1]);
                        printf("\t\tBauru com ovo: \t\t   %d\n", clientes[vezCliente].QntPedidoCardapio[2]);
                        printf("\t\tHambúrguer: \t\t   %d\n", clientes[vezCliente].QntPedidoCardapio[3]);
                        printf("\t\tCheeseburguer: \t\t   %d\n", clientes[vezCliente].QntPedidoCardapio[4]);
                        printf("\t\tRefrigerante: \t\t   %d\n", clientes[vezCliente].QntPedidoCardapio[5]);
                        printf("\t\tTotal: \t\t\tR$ %.2f\n", clientes[vezCliente].valorTotalCliente);
                        printf("\n\n\t\t> Voltar (V)\t\t> Opção: "); scanf(" %c", &opcaoCarrinho); getchar();
                        opcaoCarrinho = tolower(opcaoCarrinho);
                        if (opcaoCarrinho == 'v')
                            break;
                        else
                            codErro = 3;
                    }
                }
                else
                    codErro = 2;
                
                if (strcmp(opcao, "cachorro quente") == 0) {clientes[vezCliente].QntPedidoCardapio[0]++; codCompra = 1; numOpcao = 1; codErro = 0;}
                  else if (strcmp(opcao, "cachorro") == 0) {clientes[vezCliente].QntPedidoCardapio[0]++; codCompra = 1; numOpcao = 1; codErro = 0;}
                
                else if (strcmp(opcao, "bauru simples") == 0) {clientes[vezCliente].QntPedidoCardapio[1]++; codCompra = 1; numOpcao = 2; codErro = 0;}
                      else if (strcmp(opcao, "bau sim") == 0) {clientes[vezCliente].QntPedidoCardapio[1]++; codCompra = 1; numOpcao = 2; codErro = 0;}
                
                else if (strcmp(opcao, "bauru com ovo") == 0) {clientes[vezCliente].QntPedidoCardapio[2]++; codCompra = 1; numOpcao = 3; codErro = 0;}
                      else if (strcmp(opcao, "bau ovo") == 0) {clientes[vezCliente].QntPedidoCardapio[2]++; codCompra = 1; numOpcao = 3; codErro = 0;}
                
                else if (strcmp(opcao, "hambúrguer") == 0) {clientes[vezCliente].QntPedidoCardapio[3]++; codCompra = 1; numOpcao = 4; codErro = 0;}
                else if (strcmp(opcao, "hamburguer") == 0) {clientes[vezCliente].QntPedidoCardapio[3]++; codCompra = 1; numOpcao = 4; codErro = 0;}
                    else if (strcmp(opcao, "hambur") == 0) {clientes[vezCliente].QntPedidoCardapio[3]++; codCompra = 1; numOpcao = 4; codErro = 0;}
                
                else if (strcmp(opcao, "cheeseburguer") == 0) {clientes[vezCliente].QntPedidoCardapio[4]++; codCompra = 1; numOpcao = 5; codErro = 0;}
                       else if (strcmp(opcao, "cheese") == 0) {clientes[vezCliente].QntPedidoCardapio[4]++; codCompra = 1; numOpcao = 5; codErro = 0;}
                
                else if (strcmp(opcao, "refrigerante") == 0) {clientes[vezCliente].QntPedidoCardapio[5]++; codCompra = 1; numOpcao = 6; codErro = 0;}
                       else if (strcmp(opcao, "refri") == 0) {clientes[vezCliente].QntPedidoCardapio[5]++; codCompra = 1; numOpcao = 6; codErro = 0;}
            }
            calculoValorTotalCliente(vezCliente);
            limpar_terminal();
        }
        
    }

    float faturamentoTotal = 0;
    faturamentoTotal = calculoFaturamentoTotal();
    printf("O faturamento total do dia foi de R$ %.2f\n\n", faturamentoTotal);
    
    /*
    //printf("\n\n");
    //for (int i = 0; i < 10; i++)
    //{
    //    for (int j = 0; j < 6; j++)
    //    {
    //        printf(" %d", clientes[i].QntPedidoCardapio[j]);
    //        if (j == 5) putchar('\n');
    //    }
    //}
    
    //printf("\n%.2f", clientes[0].valorTotalCliente);
    */
}

/*
TODO: Autoavalição
Nome = Guilherme de Oliveira Portas
RA = 24101108

Obs: Em todos acho que posso melhorar a indentação e a organização do código

1. Não testei, mas não duvido nada que se tentar colocar texto em variáveis de numeros vai dar erro que nem no exercício 2. Bem neutro minha
    autoavaliação nessa.

2. Esse aqui eu fiquei mais cansado quando tava escrevendo, então naturalmente deixei alguns erros passarem, como quando ele pergunta de uma
    variável numérica que se você colocar uma letra só ele dá erro e fica repetindo infinitamente até você interromper o código manualmente.
    Eu podia melhorar mais nisso.Eu gostei da sacada de usar o goto para voltar para o início para reescrever as variáveis,
    definitivamente vou usar nos próximos códigos.

3. Nesse aqui eu estava mais focado no código então acredito que tenha poucos erros. Acho que eu ainda tenho que aprender a reduzir o tamanho
    de alguns códigos, tipo o bando de ifs que eu use para identificar qual produto que o usuário iria escolher. No geral eu acho que eu fui
    muito bem.
*/