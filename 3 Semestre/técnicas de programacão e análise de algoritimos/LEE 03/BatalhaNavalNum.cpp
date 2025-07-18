#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int qntLinhas, qntColunas, numConsultas;
    cin >> qntLinhas >> qntColunas >> numConsultas;

    unordered_map<int, pair<int, int>> posicoesTabuleiro;
    posicoesTabuleiro.reserve(qntLinhas * qntColunas);
    int entrada;
    for(int i = 0; i < qntLinhas; i++) {
        for(int j = 0; j < qntColunas; j++) {
            cin >> entrada;
            if(posicoesTabuleiro.find(entrada) == posicoesTabuleiro.end()) posicoesTabuleiro[entrada] = {i, j};
        }
    }

    while(numConsultas--) {
        int valorAhProcurar;
        cin >> valorAhProcurar;

        if(posicoesTabuleiro.find(valorAhProcurar) != posicoesTabuleiro.end()) {
            cout << posicoesTabuleiro[valorAhProcurar].first << " " << posicoesTabuleiro[valorAhProcurar].second << endl;
        }
        else cout << "-1 -1" << endl;
    }
}