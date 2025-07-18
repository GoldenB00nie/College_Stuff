#include <bits/stdc++.h>
using namespace std;

int main() {
    int qntVertices;
    cin >> qntVertices;

    bool matrizAdjacente[qntVertices][qntVertices] = {};
    for(int j = 0; j < qntVertices; j++) {
        int qntAdjacentes;
        cin >> qntAdjacentes;

        for(int i = 0; i < qntAdjacentes; i++) {
            int num;
            cin >> num;

            matrizAdjacente[j][num -1] = true;
        }
    }

    for(int j = 0; j < qntVertices; j++) {
        for(int i = 0; i < qntVertices; i++) {
            cout << (matrizAdjacente[j][i] ? 1 : 0) << (i < qntVertices -1 ? " " : "");
        }
        cout << endl;
    }
}