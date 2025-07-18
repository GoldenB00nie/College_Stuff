#include <bits/stdc++.h>
using namespace std;

int main() {
    long long qntNos;
    cin >> qntNos;

    vector<int> arvore(qntNos +1, -1);
    for(long long i = 1; i <= qntNos; i++) {
        cin >> arvore[i];
    }

    long long qntConsultas;
    cin >> qntConsultas;
    while(qntConsultas--) {
        int posAhConsulta;
        cin >> posAhConsulta;

        if(arvore.size() == 2) {
            cout << "NULL" << endl;
            break;
        }

        int pai = posAhConsulta / 2;
        int esquerda = 2 * posAhConsulta, direita = 2 * posAhConsulta +1;
        if(pai <= qntNos && pai != 0) {
            cout << arvore[pai] << " - ";
        } else if (pai == 0) {
            cout << "RAIZ - ";
        } else {
            cout << "NULL";
            break;
        }

        if(esquerda <= qntNos && arvore[esquerda] != -1) {
            cout << arvore[esquerda];
        } else {
            cout << "NULL";
        }

        cout << " ";
        if(direita <= qntNos && arvore[direita] != -1) {
            cout << arvore[direita];
        } else {
            cout << "NULL";
        }

        cout << endl;
    }
}