#include <bits/stdc++.h>
using namespace std;

int main() {
    int qntVertices, qntConexoes;
    cin >> qntVertices >> qntConexoes;

    bool matrizAdjacente[qntVertices][qntVertices] = {};
    for(int j = 0; j < qntConexoes; j++) {
        int num1, num2;
        cin >> num1 >> num2;

        matrizAdjacente[num1 -1][num2 -1] = true;
        matrizAdjacente[num2 -1][num1 -1] = true;
    }

    for(int j = 0; j < qntVertices; j++) {
        for(int i = 0; i < qntVertices; i++) {
            cout << (matrizAdjacente[j][i] ? 1 : 0) << (i < qntVertices -1 ? " " : "");
        }
        cout << endl;
    }
}