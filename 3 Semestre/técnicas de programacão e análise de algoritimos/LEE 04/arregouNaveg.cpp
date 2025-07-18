#include <bits/stdc++.h>
using namespace std;

struct Nodo {
    int valor;
    Nodo* esquerda;
    Nodo* direita;
};

Nodo inserir(Nodo* raiz, int& valor);
void ordenaInfixo(Nodo* raiz, vector<int>& ordenado);

int main() {
    int qntNos;
    cin >> qntNos;

    //vector<int> arvore(qntNos +1, -1);
    Nodo raiz;
    raiz.valor = NULL; raiz.esquerda = nullptr; raiz.direita = nullptr;
    for(int i = 1; i <= qntNos; i++) {
        int valor;
        cin >> valor;

        raiz = inserir(&raiz, valor);
    }

    vector<int> infixo, prefixo, posfixo;
    ordenaInfixo(&raiz, infixo);
    for(vector<int>::iterator i = infixo.begin(); i != infixo.end(); i++) 
        cout << to_string(*i) << (i != infixo.end() ? " " : "\n");

    // prefixa (ordenado a partir da raiz, esquerda e direita)
    // posfixa
}

Nodo inserir(Nodo* raiz, int& valor) {
    if(raiz->valor == NULL) {
        Nodo novo;
        novo.valor = valor; novo.esquerda = nullptr; novo.direita = nullptr;
        return novo;

    }
    else if(valor < raiz->valor) inserir(raiz->esquerda, valor);
    else inserir(raiz->direita, valor);
    return *raiz;
}

void ordenaInfixo(Nodo* raiz, vector<int>& ordenado) {
    if(raiz != nullptr) {
        ordenaInfixo(raiz->esquerda, ordenado);
        ordenado.push_back(raiz->valor);
        ordenaInfixo(raiz->direita, ordenado);
    }
}