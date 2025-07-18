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

        int pai = posAhConsulta / 2;
        if(pai <= qntNos && pai != 0) {
            cout << arvore[pai];
        } else if (pai == 0) {
            cout << "RAIZ";
        } else {
            cout << "NULL";
            break;
        }

        cout << endl;
    }
}