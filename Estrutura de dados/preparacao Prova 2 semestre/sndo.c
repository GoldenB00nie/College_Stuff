#include "sndo.h"

/******************************************************* Capitais ***************************************************************/

Nodo* criarNodo(int v) {
    Nodo* novoNodo = malloc(sizeof(Nodo));
    novoNodo->vertice = v;
    novoNodo->prox = NULL;
    return novoNodo;
}

Grafo* criarGrafo(int vertices) {
    Grafo* grafo = malloc(sizeof(Grafo));
    grafo->numVertices = vertices;
    grafo->lista = malloc(vertices * sizeof(ListaAdj));

    for (int i = 0; i < vertices; i++) {
        grafo->lista[i].cabeca = NULL;
    }
    return grafo;
}

void adicionarAresta(Grafo* grafo, int src, int dest) {
    Nodo* novoNodo = criarNodo(dest);
    novoNodo->prox = grafo->lista[src].cabeca;
    grafo->lista[src].cabeca = novoNodo;

    novoNodo = criarNodo(src);
    novoNodo->prox = grafo->lista[dest].cabeca;
    grafo->lista[dest].cabeca = novoNodo;
}

/********************************************************* BFS **************************************************************/

Fila* criarFila(int tamanho) {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->items = (int*) malloc(tamanho * sizeof(int));
    fila->frente = -1;
    fila->tras = -1;
    fila->tamanho = tamanho;
    return fila;
}

int estaVazia(Fila* fila) {
    return fila->tras == -1;
}

void enfileirar(Fila* fila, int valor) {
    if (fila->tras == fila->tamanho - 1)
        return;
    if (fila->frente == -1)
        fila->frente = 0;
    fila->items[++fila->tras] = valor;
}

int desenfileirar(Fila* fila) {
    int item;
    if (estaVazia(fila)) {
        item = -1;
    } else {
        item = fila->items[fila->frente];
        if (fila->frente >= fila->tras) {
            fila->frente = -1;
            fila->tras = -1;
        } else {
            fila->frente++;
        }
    }
    return item;
}

int CentroMaisProximoBFS(Grafo* grafo, int verticeInicial, Capital capitais[]) { 
    int visitados[NUM_CAPITAIS] = {0};
    int distancia[NUM_CAPITAIS] = {0};
    Fila* fila = criarFila(NUM_CAPITAIS);
    visitados[verticeInicial] = 1;
    enfileirar(fila, verticeInicial);
    while (!estaVazia(fila)) {
        int vertice = desenfileirar(fila);
        if (capitais[vertice].eCentroDistribuicao) {
            printf("Centro de distribuição mais próximo de %s é %s, com %d pulos.\n", capitais[verticeInicial].nome, capitais[vertice].nome, distancia[vertice]);
            return vertice; 
        }

        Nodo* temp = grafo->lista[vertice].cabeca;
        while (temp) {
            int adjVertice = temp->vertice;
            if (!visitados[adjVertice]) {
                visitados[adjVertice] = 1;
                distancia[adjVertice] = distancia[vertice] + 1;
                enfileirar(fila, adjVertice);
            }
            
            temp = temp->prox;
        }
    }

    printf("Nenhum centro de distribuição encontrado a partir de %s.\n", capitais[verticeInicial].nome);
    return -1;
}

int ProcurarOrgaoCentroMaisProximoBFS(Grafo* grafo, Fila_orgaos* filas[27], Pilha_orgaos* pilhas[27], int verticeInicial, Capital capitais[], char tipoOrg) { 
    tipoOrg = toupper(tipoOrg);
    if(tipoOrg != 'C' && tipoOrg != 'M' && tipoOrg != 'K') {
        printf("Erro: A função \"ProcurarOrgaoCentroMaisProximoBFS\" só aceita tipos 'C', 'M' ou 'K', e o tipo inserido foi '%c'.\n", tipoOrg); 
        return -1;
    }
    int visitados[NUM_CAPITAIS] = {0};
    int distancia[NUM_CAPITAIS] = {0};
    Fila* fila = criarFila(NUM_CAPITAIS);
    visitados[verticeInicial] = 1;
    enfileirar(fila, verticeInicial);
    while (!estaVazia(fila)) {
        int vertice = desenfileirar(fila);
        if (capitais[vertice].eCentroDistribuicao) {
            if ((tipoOrg == 'M' || tipoOrg == 'K') && !FilaVaziaOrgaos(filas[vertice])) {
                if (TemOTipoFila(filas[vertice], tipoOrg)) {
                    printf("Centro de distribuição mais próximo de %s, com o órgão do tipo '%c', é %s, com %d pulos.\n", capitais[verticeInicial].nome, tipoOrg, capitais[vertice].nome, distancia[vertice]);
                    return vertice;
                }
            }
            if (tipoOrg == 'C' && !PilhaVaziaOrgaos(pilhas[vertice])) {
                printf("Centro de distribuição mais próximo de %s, com o órgão do tipo '%c', é %s, com %d pulos.\n", capitais[verticeInicial].nome, tipoOrg, capitais[vertice].nome, distancia[vertice]);
                return vertice;
            }
        }

        Nodo* temp = grafo->lista[vertice].cabeca;
        while (temp) {
            int adjVertice = temp->vertice;
            if (!visitados[adjVertice]) {
                visitados[adjVertice] = 1;
                distancia[adjVertice] = distancia[vertice] + 1;
                enfileirar(fila, adjVertice);
            }
            temp = temp->prox;
        }
    }

    printf("Nenhum centro de distribuição encontrado com órgão do tipo '%c' a partir de %s.\n", tipoOrg, capitais[verticeInicial].nome);
    return -1;
}

int TemOTipoFila(Fila_orgaos* fila, char tipo) {
    NodoFilaOrgaos* aux = fila->frente;
    while(aux->prox != NULL && aux->orgao.tipo != tipo) {
        aux = aux->prox;
    }
    if(aux->orgao.tipo == tipo)
        return 1;
    else return 0;
}

/********************************************************* DFS **************************************************************/

// Funções para manipular a pilha
Pilha* criarPilha(int tamanho) {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

int estaVaziaPilha(Pilha* pilha) {
    return pilha->topo == NULL;
}

void empilhar(Pilha* pilha, int valor) {
    NodoPilha* novoNodo = (NodoPilha*)malloc(sizeof(NodoPilha));
    novoNodo->vertice = valor;
    novoNodo->prox = pilha->topo;
    pilha->topo = novoNodo;
}

int desempilhar(Pilha* pilha) {
    if (estaVaziaPilha(pilha)) {
        printf("Pilha vazia\n");
        exit(1);
    }
    NodoPilha* temp = pilha->topo;
    int vertice = temp->vertice;
    pilha->topo = pilha->topo->prox;
    free(temp);
    return vertice;
}

int CentroMaisProximoDFS(Grafo* grafo, int verticeInicial, Capital capitais[]) { 
    int visitados[NUM_CAPITAIS] = {0};
    int distancia[NUM_CAPITAIS] = {0};
    Pilha* pilha = criarPilha(NUM_CAPITAIS);
    visitados[verticeInicial] = 1;
    empilhar(pilha, verticeInicial);
    while (!estaVaziaPilha(pilha)) {
        int vertice = desempilhar(pilha);
        if (capitais[vertice].eCentroDistribuicao) {
            printf("Centro de distribuição mais próximo de %s é %s, com %d pulos.\n", capitais[verticeInicial].nome, capitais[vertice].nome, distancia[vertice]);
            return vertice; 
        }

        Nodo* temp = grafo->lista[vertice].cabeca;
        while (temp) {
            int adjVertice = temp->vertice;
            if (!visitados[adjVertice]) {
                visitados[adjVertice] = 1;
                distancia[adjVertice] = distancia[vertice] + 1;
                empilhar(pilha, adjVertice);
            }
            
            temp = temp->prox;
        }
    }

    printf("Nenhum centro de distribuição encontrado a partir de %s.\n", capitais[verticeInicial].nome);
    return -1;
}

int ProcurarOrgaoCentroMaisProximoDFS(Grafo* grafo, Fila_orgaos* filas[27], Pilha_orgaos* pilhas[27], int verticeInicial, Capital capitais[], char tipoOrg) { 
    tipoOrg = toupper(tipoOrg);
    if(tipoOrg != 'C' && tipoOrg != 'M' && tipoOrg != 'K') {
        printf("Erro: A função \"ProcurarOrgaoCentroMaisProximoBFS\" só aceita tipos 'C', 'M' ou 'K', e o tipo inserido foi '%c'.\n", tipoOrg); 
        return -1;
    }
    int visitados[NUM_CAPITAIS] = {0};
    int distancia[NUM_CAPITAIS] = {0};
    Pilha* pilha = criarPilha(NUM_CAPITAIS);
    visitados[verticeInicial] = 1;
    empilhar(pilha, verticeInicial);
    while (!estaVaziaPilha(pilha)) {
        int vertice = desempilhar(pilha);
        if (capitais[vertice].eCentroDistribuicao) {
            if ((tipoOrg == 'M' || tipoOrg == 'K') && !FilaVaziaOrgaos(filas[vertice])) {
                if (TemOTipoFila(filas[vertice], tipoOrg)) {
                    printf("Centro de distribuição mais próximo de %s, com o órgão do tipo '%c', é %s, com %d pulos.\n", capitais[verticeInicial].nome, tipoOrg, capitais[vertice].nome, distancia[vertice]);
                    return vertice;
                }
            }
            if (tipoOrg == 'C' && !PilhaVaziaOrgaos(pilhas[vertice])) {
                printf("Centro de distribuição mais próximo de %s, com o órgão do tipo '%c', é %s, com %d pulos.\n", capitais[verticeInicial].nome, tipoOrg, capitais[vertice].nome, distancia[vertice]);
                return vertice;
            }
        }

        Nodo* temp = grafo->lista[vertice].cabeca;
        while (temp) {
            int adjVertice = temp->vertice;
            if (!visitados[adjVertice]) {
                visitados[adjVertice] = 1;
                distancia[adjVertice] = distancia[vertice] + 1;
                empilhar(pilha, adjVertice);
            }
            temp = temp->prox;
        }
    }

    printf("Nenhum centro de distribuição encontrado com órgão do tipo '%c' a partir de %s.\n", tipoOrg, capitais[verticeInicial].nome);
    return -1;
}

/************************************************** Fila Medula e Cornea *********************************************************/

Fila_orgaos* criarFilaOrgaos() {
    Fila_orgaos* fila = (Fila_orgaos*)malloc(sizeof(Fila_orgaos));
    fila->frente = NULL;
    fila->tras = NULL;
    return fila;
}

int FilaVaziaOrgaos(Fila_orgaos* fila) {
    return fila->frente == NULL;
}

void enfileirarOrgaos(Fila_orgaos* fila, Orgao orgao) {
    NodoFilaOrgaos* novoNodo = (NodoFilaOrgaos*)malloc(sizeof(NodoFilaOrgaos));
    novoNodo->orgao = orgao;
    novoNodo->prox = NULL;
    if (FilaVaziaOrgaos(fila)) {
        fila->frente = novoNodo;
        fila->tras = novoNodo;
    } else {
        fila->tras->prox = novoNodo;
    }
    fila->tras = novoNodo;
}

int id = 1;

int enfileirarOrgaosCentro(Fila_orgaos* filas[27], lista_global* li, Orgao orgao, Grafo* grafo, Capital capitais[], char metodo) {
    orgao.tipo = toupper(orgao.tipo);
    if(orgao.tipo == 'C') {
        printf("Tipo do orgão não aceito na fila.\n");
        return 0;
    }
    int centroProximo;
    metodo = toupper(metodo);
    if(metodo == 'B') centroProximo = CentroMaisProximoBFS(grafo, orgao.origem, capitais);
    else if(metodo == 'D') centroProximo = CentroMaisProximoDFS(grafo, orgao.origem, capitais);
    else return 0;
    if (centroProximo != -1 ) {
        orgao.id = id;
        id += 1;
        strcpy(orgao.status, "Em espera para transplante");
        enfileirarOrgaos(filas[centroProximo], orgao);
        insere_lista(li, orgao);
        return 1;
    } else {
        printf("Nenhum centro de distribuição encontrado para o órgão de %s.\n", capitais[orgao.origem].nome);
        return 0;
    }
}

Orgao desenfileirarOrgaos(Fila_orgaos* fila) {
    if (FilaVaziaOrgaos(fila)) {
        printf("Fila vazia\n");
        exit(1);
    }
    NodoFilaOrgaos* temp = fila->frente;
    Orgao orgao = temp->orgao;
    fila->frente = fila->frente->prox;
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    free(temp);
    return orgao;
}

void removeNodoFilaOrgaos(Fila_orgaos* fila) {
    if (FilaVaziaOrgaos(fila)) {
        printf("Fila vazia\n");
        exit(1);
    }
    NodoFilaOrgaos* nodo = fila->frente;
    fila->frente = nodo->prox;
    free(nodo);
    printf("Nodo removido da fila\n");
}

/***************************************************** Pilha Coracao *************************************************************/

Pilha_orgaos* criarPilhaOrgaos() {
    Pilha_orgaos* pilha = (Pilha_orgaos*)malloc(sizeof(Pilha_orgaos));
    pilha->topo = NULL;
    return pilha;
}

int PilhaVaziaOrgaos(Pilha_orgaos* pilha) {
    return pilha->topo == NULL;
}

void empilharOrgaos(Pilha_orgaos* pilha, Orgao orgao) {
    NodoPilhaOrgaos* novoNodo = (NodoPilhaOrgaos*)malloc(sizeof(NodoPilhaOrgaos));
    novoNodo->orgao = orgao;
    novoNodo->prox = pilha->topo;
    pilha->topo = novoNodo;
}

int empilharOrgaosCentro(Pilha_orgaos* pilhas[27], lista_global* li, Orgao orgao, Grafo* grafo, Capital capitais[], char metodo) {
    orgao.tipo = toupper(orgao.tipo);
    if(orgao.tipo != 'C') {
        printf("Tipo do orgão não aceito na pilha.\n");
        return 0;
    }
    int centroProximo;
    metodo = toupper(metodo);
    if(metodo == 'B') centroProximo = CentroMaisProximoBFS(grafo, orgao.origem, capitais);
    else if(metodo == 'D') centroProximo = CentroMaisProximoDFS(grafo, orgao.origem, capitais);
    else return 0;
    if (centroProximo != -1) {
        orgao.id = id;
        id += 1;
        strcpy(orgao.status, "Em espera para transplante");
        empilharOrgaos(pilhas[centroProximo], orgao);
        insere_lista(li, orgao);
        return 1;
    } else {
        printf("Nenhum centro de distribuição encontrado para o órgão de %s.\n", capitais[orgao.origem].nome);
        return 0;
    }
}

int desempilharOrgaos(Pilha_orgaos* pilha) {
    if (PilhaVaziaOrgaos(pilha)) {
        printf("Pilha vazia\n");
        exit(1);
    }
    NodoPilhaOrgaos* temp = pilha->topo;
    int origem = temp->orgao.origem;
    pilha->topo = pilha->topo->prox;
    free(temp);
    return origem;
}

void removeNodoPilhaOrgaos(Pilha_orgaos* pilha) {
    if (PilhaVaziaOrgaos(pilha)) {
        printf("Pilha vazia\n");
        exit(1);
    }
    NodoPilhaOrgaos* nodo = pilha->topo;
    pilha->topo = nodo->prox;
    free(nodo);
}

/************************************************** Lista global *********************************************************/

lista_global* criaLista() {
    lista_global* li = (lista_global*) malloc(sizeof(lista_global));
    if(li != NULL)
        *li = NULL;
    return li;
}

int listaVaziaOrgaos(lista_global* li) {
    return (*li)->inicio == NULL;
}

int insere_lista(lista_global* li, Orgao orgao) {
    if(li == NULL) return 0;
    NodoLista* novo = (NodoLista*) malloc(sizeof(NodoLista));
    if(novo == NULL) return 0;
    novo->orgao = orgao;
    strcpy(novo->orgao.status, orgao.status);
    novo->prox = NULL;
    if((*li) == NULL){ //lista vazia
        novo->ant = NULL;
        *li = malloc(sizeof(li));
        if(*li == NULL) return 0;
        (*li)->inicio = novo;
    } else {
        NodoLista *aux = (*li)->inicio;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
    aux->prox = novo;
    novo->ant = aux;
    }
    return 1;
}

int remove_lista(lista_global* li, char tipo) {
    if(li == NULL) return 0;
    NodoLista *aux = (*li)->inicio;
    while(aux->orgao.tipo != tipo) {
        aux = aux->prox;
        if (aux == NULL) return 0;
    }
    if (aux->ant == NULL) {
        (*li)->inicio = aux->prox;
        if(aux->prox != NULL || (*li)->inicio != NULL) aux->prox->ant = NULL;
    }
    else aux->ant->prox = aux->prox;
    free(aux);
    return 1;
}

/******************************************** Processamento de orgaos *****************************************************/

int processarFilaOrgaos(Fila_orgaos* fila, lista_global* li_global, char tipo) { // tirar da fila
    if (FilaVaziaOrgaos(fila)) {
        printf("Fila vazia\n");
        exit(1);
    }
    NodoFilaOrgaos* nodo = fila->frente;
    if(nodo->orgao.tipo == tipo) {
        processarListaOrgaos(li_global, nodo->orgao.id);
        fila->frente = nodo->prox;
        free(nodo);
        printf("Nodo removido da fila\n\n");
        return 1;
    }
    else {
        NodoFilaOrgaos* aux;
        while(nodo->orgao.tipo != tipo && nodo->prox != NULL) {
            aux = nodo;
            nodo = nodo->prox;
        }
        if(nodo->orgao.tipo == tipo) {
            processarListaOrgaos(li_global, nodo->orgao.id);
            aux->prox = nodo->prox;
            free(nodo);
            printf("Nodo removido da fila\n\n");
            return 1;
        }
        else {
            printf("Nodo não encontrado na fila.\n");
            return 0;
        }
    }
    return 0;
}

int processarPilhaOrgaos(Pilha_orgaos* pilha, lista_global* li_global) { // tirar da pilha
    if(PilhaVaziaOrgaos(pilha)) {
        printf("Pilha vazia.\n");
        return 0;
    }
    NodoPilhaOrgaos* nodo = pilha->topo;
    processarListaOrgaos(li_global, nodo->orgao.id);
    pilha->topo = nodo->prox;
    free(nodo);
    printf("Nodo removido da pilha.\n\n");
    return 1;
}

int processarListaOrgaos(lista_global* li, int id) {
    if(listaVaziaOrgaos(li)) {
        printf("Lista vazia.\n");
        return 0;
    }
    NodoLista* nodo = (*li)->inicio;
    while(nodo->orgao.id != id && nodo->prox != NULL) {
        nodo = nodo->prox;
    }
    if(nodo->orgao.id != id) {
        printf("Nodo não encontrado na lista.\n");
        return 0;
    }
    strcpy(nodo->orgao.status, "Órgão transplantado");
    return 1;
}

int processarOrgao(Grafo* grafo, Fila_orgaos* filas[27], Pilha_orgaos* pilhas[27], lista_global* li, int verticeInicial, Capital capitais[], char tipo, char metodo) { // processar tudo
    tipo = toupper(tipo);
    metodo = toupper(metodo);
    int vertice;
    if (metodo == 'B')
        vertice = ProcurarOrgaoCentroMaisProximoBFS(grafo, filas, pilhas, verticeInicial, capitais, tipo);
    else if (metodo == 'D')
        vertice = ProcurarOrgaoCentroMaisProximoDFS(grafo, filas, pilhas, verticeInicial, capitais, tipo);
    else {printf("Método não aceito.\n"); return 0;}
    if(vertice == -1) return 0;
    switch (tipo) {
        case 'M': case 'K': processarFilaOrgaos(filas[vertice], li, tipo);
                            return 1; break;
        case 'C': processarPilhaOrgaos(pilhas[vertice], li);
                  return 1; break;
        default:  printf("Erro: A função \"processarOrgao\" só aceita tipos 'C', 'M' ou 'K', e o tipo inserido foi '%c'.\n", tipo); 
                  return 0;
    }
}

/*************************************************** Relatorios **********************************************************/

void imprimirFila(Fila_orgaos* fila, Capital capital[]) {
    if (fila->frente == NULL || fila == NULL) return;
    int ordem = 1;
    char nomeTipoOrgao[10];
    NodoFilaOrgaos* aux = fila->frente;
    while (aux != NULL) {
        switch (aux->orgao.tipo) {
            case 'C': strcpy(nomeTipoOrgao, "Coração"); break;
            case 'M': strcpy(nomeTipoOrgao, "Medula"); break;
            case 'K': strcpy(nomeTipoOrgao, "Córnea"); break;
            default: strcpy(nomeTipoOrgao, "ERRO");
        }
        printf("%10d.  %s: \t{id: %d, origem: \"%s\"}\n", ordem, nomeTipoOrgao, aux->orgao.id, capital[aux->orgao.origem].nome);
        aux = aux->prox;
        ordem++;
    }
    return;
}

void imprimirPilha(Pilha_orgaos* pilha, Capital capital[]) {
    if (pilha->topo == NULL || pilha == NULL) return;
    int ordem = 1;
    char nomeTipoOrgao[10];
    NodoPilhaOrgaos* aux = pilha->topo;
    while (aux != NULL) {
        switch (aux->orgao.tipo) {
            case 'C': strcpy(nomeTipoOrgao, "Coração"); break;
            case 'M': strcpy(nomeTipoOrgao, "Medula"); break;
            case 'K': strcpy(nomeTipoOrgao, "Córnea"); break;
            default: strcpy(nomeTipoOrgao, "ERRO");
        }
        printf("%10d.  %s: \t{id: %d, origem: \"%s\"}\n", ordem, nomeTipoOrgao, aux->orgao.id, capital[aux->orgao.origem].nome);
        aux = aux->prox;
        ordem++;
    }
    return;
}

void imprimirLista(lista_global* lista, Capital capital[]) {
    if ((*lista)->inicio == NULL || lista == NULL) return;
    int ordem = 1;
    char nomeTipoOrgao[10];
    NodoLista* aux = (*lista)->inicio;
    while (aux != NULL) {
        switch (aux->orgao.tipo) {
            case 'C': strcpy(nomeTipoOrgao, "Coração"); break;
            case 'M': strcpy(nomeTipoOrgao, "Medula"); break;
            case 'K': strcpy(nomeTipoOrgao, "Córnea"); break;
            default: strcpy(nomeTipoOrgao, "ERRO");
        }
        printf("%10d.  %s: \t{id: %d, origem: \"%s\", status: \"%s\"}\n",
        ordem, nomeTipoOrgao, aux->orgao.id, capital[aux->orgao.origem].nome, aux->orgao.status);
        aux = aux->prox;
        ordem++;
    }
    return;
}

void imprimirRelatorio(Fila_orgaos* filas[27], Pilha_orgaos* pilhas[27], lista_global* lista, Capital capital[], char metodo[3]) {
    limpar_terminal();
    printf("\t\t/*********************    Relatório da estrutura de dados usando %s *********************\\ \n\n", metodo);
    if((*lista) == NULL) {
        printf("Lista vazia. Tente inserir novos órgãos ou simular a inserção dos órgãos.\n\n");
        printf("Pressione <ENTER> para voltar ao menu principal."); 
        getchar();
        return;
    }
    char nomeCapital[20];
    for (int i = 0; i <= 26; i++) {
        if (capital[i].eCentroDistribuicao) {
            for (int j = 0; j < 20; j++)
                nomeCapital[j] = toupper(capital[i].nome[j]);
            printf("Fila de %s {\n", nomeCapital);
            imprimirFila(filas[i], capital);
            printf("}\n\n");
        }
    }
    for (int i = 0; i <= 26; i++) {
        if (capital[i].eCentroDistribuicao) {
            for (int j = 0; j < 20; j++)
                nomeCapital[j] = toupper(capital[i].nome[j]);
            printf("Pilha de %s {\n", nomeCapital);
            imprimirPilha(pilhas[i], capital);
            printf("}\n\n");
        }
    }
    printf("Lista global do método de %s {\n", metodo);
    imprimirLista(lista, capital);
    printf("}\n\n");
    printf("Pressione <ENTER> para voltar ao menu principal."); 
    getchar();
    return;
}

/**************************************************** Especiais ***********************************************************/

int id_max() {
    int id_max = id / 2;
    return id_max;
}

int numAleatIntervMax(int max) {
    int rd_num = rand() % (max + 1);
    return rd_num;
}

char TipoAleatOrgao() {
    int rd_num = (rand() % 3) + 1;
    if(rd_num == 1) return 'C';
    else if(rd_num == 2) return 'M';
    else return 'K';
}

void limpar_terminal() {                         // Função para limpar o terminal
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