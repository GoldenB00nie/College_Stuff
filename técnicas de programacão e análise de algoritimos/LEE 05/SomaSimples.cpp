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
        int complemento = valorEncontrar - listaNumeros[i];
        if(elementosVistos.count(complemento)) {
            cout << listaNumeros[i] << " " << complemento << endl;
            return 0;
        }

        elementosVistos.insert(listaNumeros[i]);
    }
    cout << "Nao existe" << endl;
}