#include <bits/stdc++.h>
using namespace std;

int main() {
    long long numSeguidores, qntDias;
    cin >> numSeguidores >> qntDias;

    vector<long long> ultimos30Dias(30);
    long long somaInscricoes = 0;
    for(int i = 0; i < 30; i++) {
        cin >> ultimos30Dias[i];
        somaInscricoes += ultimos30Dias[i];
    }

    for(int i = 0; i < qntDias; ++i) {
        long long mediaInscricoes = (somaInscricoes + 29) / 30;
        numSeguidores += mediaInscricoes;

        int indiceVelho = i % 30;
        somaInscricoes -= ultimos30Dias[indiceVelho];
        ultimos30Dias[indiceVelho] = mediaInscricoes;
        somaInscricoes += mediaInscricoes;

    }

    cout << numSeguidores << endl;
}