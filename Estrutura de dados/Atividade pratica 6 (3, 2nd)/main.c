#include "pilha.h"

int main() {
    SetConsoleOutputCP(CP_UTF8); // Configura o terminal para UTF-8. Serve para colocar caracteres especiais no terminal
    pilha* pi = cria_pilha();
    struct conversoes dados;
    char opcao_inserir[20];
    char booleano = 1;
    Elem* temp = *pi;

    while (1)
    {
        char opcao_principal = ' ';
        limpar_terminal();
        printf("> Inserir número na lista (I)\n");
        printf("> Remover número da lista (R)\n");
        printf("> Imprimir lista (L)\n");
        printf("> Sair (S)\n\n");
        printf("Opção: ");
        scanf(" %c", &opcao_principal);
        limpar_terminal(); flush_in();
        switch (opcao_principal)
        {
            case 'i': case 'I':
                while (2)
                {
                    strcpy(opcao_inserir, " ");
                    printf("Insira um inteiro: "); scanf(" %s", opcao_inserir);
                    limpar_terminal(); flush_in();
                    for (int i = 0; i < strlen(opcao_inserir); i++)
                    {
                        if (!isdigit(opcao_inserir[i])) 
                        {
                            booleano = 0; // Não é um dígito
                            break;
                        }
                    }
                    if (booleano == 1)
                    {
                        booleano = 1;
                        strcpy(opcao_inserir, " ");
                        dados.num_escolhido = atoi(opcao_inserir);
                        while (3)
                        {
                            printf("Escolha o tipo de conversão: \n\n");
                            printf("> Binário (2)\n");
                            printf("> Octal (8)\n");
                            printf("> Inteiro (10)\n");
                            printf("> Hexadecimal (16)\n");
                            printf("Opção: ");
                            scanf("%s", opcao_inserir);
                            limpar_terminal(); flush_in();
                            for (int i = 0; i < strlen(opcao_inserir); i++)
                            {
                                if (!isdigit(opcao_inserir[i])) 
                                {
                                    booleano = 0; // Não é um dígito
                                    break;
                                }
                            }
                            if (booleano == 1)
                            {
                                dados.tipo_conversao = atoi(opcao_inserir);
                                insere_pilha(pi, dados);
                                printf("Elemento inserido com sucesso!\n\n");
                                break;
                            }
                            else
                               printf("Inteiro inválido. Tente novamente.\n");
                        } break;
                    }
                    else
                        printf("Inteiro inválido. Tente novamente.\n");
                } break;
            case 'r': case 'R': remove_pilha(pi); break;
            case 'l': case 'L': imprime_lista(pi); getchar(); break;
            default: limpar_terminal(); printf("Opção inválida. Tente novamente. \n\n");
        }
        if (opcao_principal == 's' || opcao_principal == 'S')
            break;
    }
    
    
}