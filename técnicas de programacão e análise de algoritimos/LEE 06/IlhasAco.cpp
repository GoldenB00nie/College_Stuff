#include <bits/stdc++.h>
using namespace std;

int main() {
    int numIlhas, numPontes;
    cin >> numIlhas >> numPontes;

    vector<vector<int>> adj(numIlhas + 1);
    for (int i = 0; i < numPontes; ++i) {
        int ilha1, ilha2;
        cin >> ilha1 >> ilha2;

        adj[ilha1].push_back(ilha2);
        adj[ilha2].push_back(ilha1);
    }

    queue<int> fila;
    vector<int> distancia(numIlhas + 1, -1);
    fila.push(1);
    distancia[1] = 0;
    while (!fila.empty()) {
        int ilhaAtual = fila.front();
        fila.pop();

        if (ilhaAtual == numIlhas) {
            cout << distancia[numIlhas] << endl;
            return 0;
        }

        for (int ilhaVisinha : adj[ilhaAtual]) {
            if (distancia[ilhaVisinha] == -1) {
                distancia[ilhaVisinha] = distancia[ilhaAtual] + 1;
                fila.push(ilhaVisinha);
            }
        }
    }

    cout << -1 << endl;
}