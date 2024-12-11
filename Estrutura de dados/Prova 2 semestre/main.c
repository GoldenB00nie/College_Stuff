#include "sndo.h"

int main() {
    colocar_terminal_UTF8();
    srand(time(NULL));
    Capital capitais[NUM_CAPITAIS] = {
        {"Rio Branco", 0}, {"Manaus", 0}, {"Porto Velho", 0}, {"Boa Vista", 0}, {"Macapá", 0},
        {"Palmas", 0}, {"Teresina", 0}, {"São Luís", 0}, {"Belém", 0}, {"Fortaleza", 1},
        {"Natal", 0}, {"João Pessoa", 0}, {"Recife", 0}, {"Maceió", 0}, {"Aracaju", 0},
        {"Salvador", 0}, {"Brasília", 1}, {"Goiânia", 0}, {"Cuiabá", 0}, {"Campo Grande", 0},
        {"Belo Horizonte", 0}, {"Vitória", 0}, {"Rio de Janeiro", 0}, {"São Paulo", 1}, {"Curitiba", 0},
        {"Florianópolis", 0}, {"Porto Alegre", 0}
    };

    Grafo* grafo = criarGrafo(NUM_CAPITAIS);

    { // Adicionar capitais ao mapa 
        adicionarAresta(grafo, 0, 1); // Rio Branco - Manaus
        adicionarAresta(grafo, 1, 2); // Manaus - Porto Velho
        adicionarAresta(grafo, 1, 3); // Manaus - Boa Vista
        adicionarAresta(grafo, 1, 8); // Manaus - Belém
        adicionarAresta(grafo, 3, 8); // Boa Vista - Belém
        adicionarAresta(grafo, 4, 8); // Macapá - Belém
        adicionarAresta(grafo, 5, 7); // Palmas - São Luís
        adicionarAresta(grafo, 5, 16); // Palmas - Brasília
        adicionarAresta(grafo, 5, 6); // Palmas - Teresina
        adicionarAresta(grafo, 7, 6); // São Luís - Teresina
        adicionarAresta(grafo, 9, 7); // Fortaleza - São Luís
        adicionarAresta(grafo, 8, 7); // Belém - São Luís
        adicionarAresta(grafo, 8, 16); // Belém - Brasília
        adicionarAresta(grafo, 9, 10); // Fortaleza - Natal
        adicionarAresta(grafo, 9, 16); // Fortaleza - Brasília
        adicionarAresta(grafo, 10, 11); // Natal - João Pessoa
        adicionarAresta(grafo, 11, 12); // João Pessoa - Recife
        adicionarAresta(grafo, 12, 13); // Recife - Maceió
        adicionarAresta(grafo, 13, 14); // Maceió - Aracaju
        adicionarAresta(grafo, 15, 14); // Salvador - Aracaju
        adicionarAresta(grafo, 15, 16); // Salvador - Brasília
        adicionarAresta(grafo, 16, 17); // Brasília - Goiânia
        adicionarAresta(grafo, 16, 18); // Brasília - Cuiabá
        adicionarAresta(grafo, 16, 23); // Brasília - São Paulo
        adicionarAresta(grafo, 16, 20); // Brasília - Belo Horizonte
        adicionarAresta(grafo, 18, 19); // Cuiabá - Campo Grande
        adicionarAresta(grafo, 19, 17); // Campo Grande - Goiânia
        adicionarAresta(grafo, 19, 23); // Campo Grande - São Paulo
        adicionarAresta(grafo, 20, 21); // Belo Horizonte - Vitória
        adicionarAresta(grafo, 20, 23); // Belo Horizonte - São Paulo
        adicionarAresta(grafo, 22, 20); // Rio de Janeiro - Belo Horizonte
        adicionarAresta(grafo, 22, 21); // Rio de Janeiro - Vitória
        adicionarAresta(grafo, 22, 23); // Rio de Janeiro - São Paulo
        adicionarAresta(grafo, 23, 24); // São Paulo - Curitiba
        adicionarAresta(grafo, 24, 25); // Curitiba - Florianópolis
        adicionarAresta(grafo, 25, 26); // Florianópolis - Porto Alegre
    }
    //imprimirGrafo(grafo, capitais);
    //CentroMaisProximo(grafo, 8, capitais); // Iniciando a busca em Brasília

    lista_global* li_globalBFS = criaLista(), *li_globalDFS = criaLista();
    Fila_orgaos* filasBFS[27], *filasDFS[27];
    Pilha_orgaos* pilhasBFS[27], *pilhasDFS[27];
    for (int i = 0; i <= 26; i++) 
    {
        if(capitais[i].eCentroDistribuicao == 1) {
            filasBFS[i] = criarFilaOrgaos();
            filasDFS[i] = criarFilaOrgaos();
            pilhasBFS[i] = criarPilhaOrgaos();
            pilhasDFS[i] = criarPilhaOrgaos();
        }
        else {
            filasBFS[i] = filasDFS[i] = NULL;
            pilhasBFS[i] = pilhasDFS[i] = NULL;
        }
    }

    char opcaoMenuPrincipal,
            opcaoInserirOrgao, tipoInseridoInserirOrgao, capitalInseridaInserirOrgao,
            opcaoProcessarOrgao, verticeProcessamentoOrgao, tipoInseridoProcessamentoOrgao,
            tipoAleatProcessamento,
            opcaoImprimirRelatorio;
    int opcaoSimularInsercoes, opcaoSimularProcessamento, verticeAleatProcessamento;
    Orgao orgao;
    while(1) {
        limpar_terminal();
        printf("---------------------- Bem vindo ao Sistema Nacional de Doações de Órgãos (SNDO) ----------------------\n\n");
        printf("1 - Informações.\n");
        printf("2 - Inserir órgão.\n");
        printf("3 - Processar um órgão (Encaminhar para transplante).\n");
        printf("4 - Simular inserções de órgãos.\n");
        printf("5 - Simular processamento de órgãos.\n");
        printf("6 - Imprimir relatório\n\n");
        printf("0 - Sair.\n\n\n");
        printf("Opção: "); scanf(" %d", &opcaoMenuPrincipal); flush_in();

        if(opcaoMenuPrincipal == 0) break;
        while(opcaoMenuPrincipal == 1) { // Informacoes
            limpar_terminal();
            printf("----------------------------------------- Informações ---------------------------------------------\n\n");
            printf("O Sistema Nacional de Transplantes (SNT) é o órgão responsável por regular, monitorar e ");
            printf("controlar o processo de doação e transplante de órgãos, tecidos e partes do corpo humano no Brasil.\n\n");
            printf("Nesse programa você pode simular inserções e processamentos de órgãos, que no caso é enviar o órgão ");
            printf("para transplante. Os órgãos inseridos são enviados ao Centro de Distribuição (CD) mais próximo e ");
            printf("eles são enviado para transplante para as capitais mais próximas de cada CDs através de ");
            printf("dois métodos diferentes: DFS e BFS.\n\n");

            printf("Os CDs são:\n");
            for(int i = 0; i <= 26; i++) {
                if(capitais[i].eCentroDistribuicao) printf("\t> %s\n", capitais[i].nome);
            }

            printf("\nAperte <ENTER> para sair."); getchar(); opcaoMenuPrincipal = -1;
        }

        while (opcaoMenuPrincipal == 2) { // Inserir orgao
            limpar_terminal();
            printf("---------------------------------------- Inserir órgão --------------------------------------------\n\n");
            printf("Insira o tipo do órgão:\n");
            printf("\t\t> Coração (C) \t\t> Medula (M) \t\t> Córnea (K) \n\n");
            escanearTipoOrgao: printf("Opção: "); scanf(" %c", &opcaoInserirOrgao); flush_in();
            opcaoInserirOrgao = toupper(opcaoInserirOrgao);
            if (opcaoInserirOrgao != 'C' && opcaoInserirOrgao != 'M' && opcaoInserirOrgao != 'K') {
                printf("\n\t\t\tOpção inválida! Por favor selecione um único caractere do tipo do órgão indicado pelos parenteses.\n\n");
                goto escanearTipoOrgao;
            }
            tipoInseridoInserirOrgao = opcaoInserirOrgao;
            opcaoInserirOrgao = ' ';
            limpar_terminal();
            printf("---------------------------------------- Inserir órgão --------------------------------------------\n\n");

            printf("Insira a capital desejada:\n\n");
            printf("\t0 = Rio branco\t 1 = Manaus\t\t 2 = Porto Velho\t 3 = Boa Vista\t 4 = Macapá\t\t 5 = Palmas\n");
            printf("\t6 = Teresina\t 7 = São Luís\t\t 8 = Belém\t\t 9 = Fortaleza\t 10 = Natal;\t\t 11 = João Pessoa\n");
            printf("\t12 = Recife\t 13 = Maceió\t\t 14 = Aracaju\t\t 15 = Salvador\t 16 = Brasília\t\t 17 = Goiânia\n");
            printf("\t18 = Cuiabá\t 19 = Campo Grande\t 20 = Belo Horizonte\t 21 = Vitória\t 22 = Rio de Janeiro\t 23 = São Paulo\n");
            printf("\t24 = Curitiba\t 25 = Florianópolis\t 26 = Porto Alegre.\n\n");
            escanearCapitalOrgao: printf("Opção: "); scanf(" %d", &opcaoInserirOrgao); flush_in();
            if(opcaoInserirOrgao < 0 || opcaoInserirOrgao > 26) {
                printf("\n\t\t\tOpção inválida! Por favor selecione um número de uma das capitais informadas.\n\n");
                goto escanearCapitalOrgao;
            }

            capitalInseridaInserirOrgao = opcaoInserirOrgao;
            opcaoInserirOrgao = ' ';
            orgao.tipo = tipoInseridoInserirOrgao; orgao.origem = capitalInseridaInserirOrgao;
            if (orgao.tipo == 'C') {
                printf("\n > BFS: \n"); empilharOrgaosCentro(pilhasBFS, li_globalBFS, orgao, grafo, capitais, 'B');
                printf("\n > DFS: \n"); empilharOrgaosCentro(pilhasDFS, li_globalDFS, orgao, grafo, capitais, 'D');
            }
            else {
                printf("\n > BFS: \n"); enfileirarOrgaosCentro(filasBFS, li_globalBFS, orgao, grafo, capitais, 'B');
                printf("\n > DFS: \n"); enfileirarOrgaosCentro(filasDFS, li_globalDFS, orgao, grafo, capitais, 'D');
            }
            printf("\nAperte <ENTER> para sair."); getchar(); opcaoMenuPrincipal = -1;
            opcaoMenuPrincipal = -1;
        }

        while (opcaoMenuPrincipal == 3) { // Processar um orgao
            limpar_terminal();
            printf("---------------------------------------- Processar órgão --------------------------------------------\n\n");
            printf("\t0 = Rio branco\t 1 = Manaus\t\t 2 = Porto Velho\t 3 = Boa Vista\t 4 = Macapá\t\t 5 = Palmas\n");
            printf("\t6 = Teresina\t 7 = São Luís\t\t 8 = Belém\t\t 9 = Fortaleza\t 10 = Natal;\t\t 11 = João Pessoa\n");
            printf("\t12 = Recife\t 13 = Maceió\t\t 14 = Aracaju\t\t 15 = Salvador\t 16 = Brasília\t\t 17 = Goiânia\n");
            printf("\t18 = Cuiabá\t 19 = Campo Grande\t 20 = Belo Horizonte\t 21 = Vitória\t 22 = Rio de Janeiro\t 23 = São Paulo\n");
            printf("\t24 = Curitiba\t 25 = Florianópolis\t 26 = Porto Alegre.\n\n");
            escanearVerticeProcessamentoOrgao: printf("Insira a capital que necessita de transplante: "); scanf("%d", &opcaoProcessarOrgao); flush_in();
            if(opcaoProcessarOrgao < 0 || opcaoProcessarOrgao > 26) {
                printf("\n\t\t\tOpção inválida! Por favor selecione um número de uma das capitais informadas.\n\n");
                goto escanearVerticeProcessamentoOrgao;
            }
            verticeProcessamentoOrgao = opcaoProcessarOrgao;
            opcaoProcessarOrgao = ' ';

            limpar_terminal();
            printf("---------------------------------------- Processar órgão --------------------------------------------\n\n");
            printf("Insira o tipo do órgão a ser processado:\n");
            printf("\t\t> Coração (C) \t\t> Medula (M) \t\t> Córnea (K) \n\n");
            escanearTipoOrgaoProcessamento: printf("Opção: "); scanf(" %c", &opcaoProcessarOrgao); flush_in();
            opcaoProcessarOrgao = toupper(opcaoProcessarOrgao);
            if (opcaoProcessarOrgao != 'C' && opcaoProcessarOrgao != 'M' && opcaoProcessarOrgao != 'K') {
                printf("\n\t\t\tOpção inválida! Por favor selecione um único caractere do tipo do órgão indicado pelos parenteses.\n\n");
                goto escanearTipoOrgaoProcessamento;
            }
            tipoInseridoProcessamentoOrgao = opcaoProcessarOrgao;
            printf("\n");
            processarOrgao(grafo, filasBFS, pilhasBFS, li_globalBFS, verticeProcessamentoOrgao, capitais, tipoInseridoProcessamentoOrgao, 'B');
            processarOrgao(grafo, filasDFS, pilhasDFS, li_globalDFS, verticeProcessamentoOrgao, capitais, tipoInseridoProcessamentoOrgao, 'D');
            printf("\n");
            printf("Pressione <ENTER> para voltar ao menu principal."); 
            getchar();
            opcaoMenuPrincipal = -1;
        }

        while (opcaoMenuPrincipal == 4) { // Simular insercoes de orgaos
            limpar_terminal();
            printf("--------------------------------- Simular inserção de órgãos -------------------------------------\n\n");
            printf("Insira a quantidade de inserções a serem feitas: ");
            escanearSimularInsercoes: scanf(" %d", &opcaoSimularInsercoes); flush_in();
            if(opcaoSimularInsercoes <= 0) {
                printf("\n\t\t\tOpção inválida! Por favor selecione um número de inserções maiores do que 0.\n\n");
                goto escanearSimularInsercoes;
            }

            limpar_terminal();
            printf("--------------------------------- Simular inserção de órgãos -------------------------------------\n\n");
            for (int i = 0; i < opcaoSimularInsercoes; i++) {
                orgao.tipo = TipoAleatOrgao();
                orgao.origem = numAleatIntervMax(26);
                if (orgao.tipo == 'C') {
                    printf("\n > BFS: \n"); empilharOrgaosCentro(pilhasBFS, li_globalBFS, orgao, grafo, capitais, 'B');
                    printf("\n > DFS: \n"); empilharOrgaosCentro(pilhasDFS, li_globalDFS, orgao, grafo, capitais, 'D');
                }
                else {
                    printf("\n > BFS: \n"); enfileirarOrgaosCentro(filasBFS, li_globalBFS, orgao, grafo, capitais, 'B');
                    printf("\n > DFS: \n"); enfileirarOrgaosCentro(filasDFS, li_globalDFS, orgao, grafo, capitais, 'D');
                }
            }
            
            printf("\n\nInserção de órgãos finalizado com sucesso. \n\nPressione <ENTER> para voltar ao menu principal."); 
            getchar();
            opcaoMenuPrincipal = -1;
        }

        while (opcaoMenuPrincipal == 5) { // Simular processamento de orgaos
            limpar_terminal();
            printf("------------------------------ Simular processamento de órgãos -----------------------------------\n\n");
            printf("Insira a quantidade de processamentos a serem feitas: ");
            escanearSimularProcessamento: scanf(" %d", &opcaoSimularProcessamento); flush_in();
            if(opcaoSimularProcessamento <= 0 ) {
                printf("\n\t\t\tOpção inválida! Por favor selecione um número de processamentos maiores do que 0.\n\n");
                goto escanearSimularProcessamento;
            }

            limpar_terminal();
            printf("------------------------------ Simular processamento de órgãos -----------------------------------\n\n");
            for (int i = 0; i < opcaoSimularProcessamento; i++) {
                tipoAleatProcessamento = TipoAleatOrgao();
                verticeAleatProcessamento = numAleatIntervMax(26);
                printf("\n > BFS: \n"); processarOrgao(grafo, filasBFS, pilhasBFS, li_globalBFS, verticeAleatProcessamento, capitais, tipoAleatProcessamento, 'B');
                printf("\n > DFS: \n"); processarOrgao(grafo, filasDFS, pilhasDFS, li_globalDFS, verticeAleatProcessamento, capitais, tipoAleatProcessamento, 'D');
            }

            printf("\n\nProcessamento de órgãos finalizado com sucesso.\n");
            printf("OBS: alguns processamentos podem dar errado porque não foi inserido um do mesmo tipo.\n\n");
            printf("Pressione <ENTER> para voltar ao menu principal."); 
            getchar();
            opcaoMenuPrincipal = -1;
        }

        while (opcaoMenuPrincipal == 6) { // Imprimir relatório
            limpar_terminal();
            printf("------------------------------------- Imprimir relatório -----------------------------------------\n\n");
            printf("1 - Relatório BFS \n2 - Relatório DFS \n\n0 - Voltar\n\n\n");
            escanearImpressao: printf("Opção: "); scanf(" %d", &opcaoImprimirRelatorio); flush_in();
            if(opcaoImprimirRelatorio < 0 || opcaoImprimirRelatorio > 2) {
                printf("\n\t\t\tOpção inválida! Por favor selecione um número das opções de impressão.\n\n");
                goto escanearImpressao;
            }
            if (opcaoImprimirRelatorio == 0) opcaoMenuPrincipal = -1;
            else if (opcaoImprimirRelatorio == 1) imprimirRelatorio(filasBFS, pilhasBFS, li_globalBFS, capitais, "BFS");
            else imprimirRelatorio(filasDFS, pilhasDFS, li_globalDFS, capitais, "DFS");
            printf("\nAperte <ENTER> para sair."); getchar(); opcaoMenuPrincipal = -1;
            opcaoMenuPrincipal = -1;
        }
    }

    free(grafo);
    free(li_globalBFS); free(li_globalDFS);
    for(int i = 0; i <= 26; i++) {
        free(filasBFS[i]); free(filasDFS[i]); free(pilhasBFS[i]); free(pilhasDFS[i]);
    }
    
    return 0;
}

/*
0 = Rio branco;     1 = Manaus;         2 = Porto Velho;        3 = Boa Vista;      4 = Macapá;             5 = Palmas;         
6 = Teresina;       7 = São Luís;       8 = Belém;              9 = Fortaleza;      10 = Natal;             11 = João Pessoa;
12 = Recife;        13 = Maceió;        14 = Aracaju;           15 = Salvador;      16 = Brasília;          17 = Goiânia;
18 = Cuiabá;        19 = Campo Grande;  20 = Belo Horizonte;    21 = Vitória;       22 = Rio de Janeiro;    23 = São Paulo;
24 = Curitiba;      25 = Florianópolis; 26 = Porto Alegre.
*/