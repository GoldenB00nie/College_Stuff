#include <bits/stdc++.h>
using namespace std;

struct Nodo {
    int valor;
    Nodo* esquerda;
    Nodo* direita;

    Nodo(int valor) : valor(valor), esquerda(nullptr), direita(nullptr) {}
};

Nodo* inserir(Nodo* raiz, int valor);
void organizarInfixo(Nodo* raiz, vector<int>& res);
void organizarPrefixo(Nodo* raiz, vector<int>& res);
void organizarPosfixo(Nodo* raiz, vector<int>& res);
void print(const string& nomeOrdem, const vector<int>& res);

int main() {
    int qntNos;
    cin >> qntNos;
    Nodo* raiz = nullptr;
    for (int i = 0; i < qntNos; i++) {
        int valor;
        cin >> valor;
        raiz = inserir(raiz, valor);
    }

    vector<int> in, pre, pos;
    organizarInfixo(raiz, in);
    organizarPrefixo(raiz, pre);
    organizarPosfixo(raiz, pos);

    print("In.:", in);
    print("Pre:", pre);
    print("Pos:", pos);
}

Nodo* inserir(Nodo* raiz, int valor) {
    if (raiz == nullptr) return new Nodo(valor);
    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else
        raiz->direita = inserir(raiz->direita, valor);
    return raiz;
}

void organizarInfixo(Nodo* raiz, vector<int>& res) {
    if (raiz) {
        organizarInfixo(raiz->esquerda, res);
        res.push_back(raiz->valor);
        organizarInfixo(raiz->direita, res);
    }
}

void organizarPrefixo(Nodo* raiz, vector<int>& res) {
    if (raiz) {
        res.push_back(raiz->valor);
        organizarPrefixo(raiz->esquerda, res);
        organizarPrefixo(raiz->direita, res);
    }
}

void organizarPosfixo(Nodo* raiz, vector<int>& res) {
    if (raiz) {
        organizarPosfixo(raiz->esquerda, res);
        organizarPosfixo(raiz->direita, res);
        res.push_back(raiz->valor);
    }
}

void print(const string& nomeOrdem, const vector<int>& res) {
    cout << nomeOrdem;
    for (int valor : res) cout << " " << valor;
    cout << "\n";
}