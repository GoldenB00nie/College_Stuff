#include <bits/stdc++.h>
using namespace std;

int main() {
    int numElementos, valorEncontrar;
    cin >> numElementos >> valorEncontrar;

    unordered_set<int> elementosVistos;
    vector<int> listaNumeros(numElementos);
    for(int i = 0; i < numElementos; i++) {
        cin >> listaNumeros[i];
    }

    for(int i = 0; i < numElementos; i++) {
        int novoValorEncontrar = valorEncontrar - listaNumeros[i];
        for(int j = 0; j < numElementos; j++) {
            if(j == i) continue;
            int complemento = novoValorEncontrar - listaNumeros[j];
            if(elementosVistos.count(complemento)) {
                cout << listaNumeros[i] << " " << listaNumeros[j] << " " << complemento << endl;
                return 0;
            }

            elementosVistos.insert(listaNumeros[j]);
        }

        elementosVistos.clear();
    }

    cout << "Nao existe" << endl;
}
