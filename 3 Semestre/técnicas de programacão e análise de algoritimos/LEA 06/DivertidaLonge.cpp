#include <bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max();

int main() {
    int qntCasas, qntCaminhos;
    cin >> qntCasas >> qntCaminhos;

    vector<vector<pair<int, int>>> cidade(qntCasas + 1);
    for (int i = 0; i < qntCaminhos; ++i) {
        int rota1, rota2, distanciasanciaCasas;
        cin >> rota1 >> rota2 >> distanciasanciaCasas;
        cidade[rota1].push_back({rota2, distanciasanciaCasas});
        cidade[rota2].push_back({rota1, distanciasanciaCasas});
    }

    vector<int> distancias(qntCasas + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;
    distancias[1] = 0;
    filaPrioridade.push({0, 1});
    while (!filaPrioridade.empty()) {
        int menorDistanciaNohAtual = filaPrioridade.top().first;
        int nohAtual = filaPrioridade.top().second;
        filaPrioridade.pop();
        if (menorDistanciaNohAtual > distancias[nohAtual]) {
            continue;
        }

        for (auto& edge : cidade[nohAtual]) {
            int verticeAtual = edge.first;
            int peso = edge.second;
            if (distancias[nohAtual] + peso < distancias[verticeAtual]) {
                distancias[verticeAtual] = distancias[nohAtual] + peso;
                filaPrioridade.push({distancias[verticeAtual], verticeAtual});
            }
        }
    }

    long long max_distancias = 0;
    bool possible = true;
    for (int i = 2; i <= qntCasas; ++i) {
        if (distancias[i] == INF) {
            possible = false; 
            break; 
        }
        if (distancias[i] > max_distancias) {
            max_distancias = distancias[i];
        }
    }

    if (possible) {
        cout << "Casa mais distante a " << max_distancias << " metros" << endl;
    } else {
        cout << "Impossivel chegar" << endl;
    }
}