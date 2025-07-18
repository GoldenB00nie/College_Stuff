#include <bits/stdc++.h>
using namespace std;

int main() {
    long long qntNos, qntConsultas;
    cin >> qntNos >> qntConsultas;

    vector<int> arvore(qntNos +1, -1);
    for(long long i = 1; i <= qntNos; i++) {
        cin >> arvore[i];
    }

    while(qntConsultas--) {
        int posAhConsulta;
        cin >> posAhConsulta;

        if(arvore.size() == 2) {
            cout << "NULL" << endl;
            break;
        }

        int esquerda = 2 * posAhConsulta, direita = 2 * posAhConsulta +1;
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