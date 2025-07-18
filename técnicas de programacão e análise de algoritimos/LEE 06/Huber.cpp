#include <bits/stdc++.h>
using namespace std;

int main() {
    int numLocaisConhecidos, qntLigacoes;
    cin >> numLocaisConhecidos >> qntLigacoes;

    vector<vector<pair<int, int>>> grafo(numLocaisConhecidos + 1);
    for (int i = 0; i < qntLigacoes; ++i) {
        int rota1, rota2, distRotas;
        cin >> rota1 >> rota2 >> distRotas;
        grafo[rota1].push_back({rota2, distRotas});
        grafo[rota2].push_back({rota1, distRotas});
    }

    const long long INF = numeric_limits<long long>::max();
    vector<long long> dist(numLocaisConhecidos + 1, INF);
    priority_queue<pair<long long, int>, 
                         vector<pair<long long, int>>, 
                         greater<pair<long long, int>>> filaPrioridade;

    dist[1] = 0;
    filaPrioridade.push({0, 1});
    while (!filaPrioridade.empty()) {
        long long d_u = filaPrioridade.top().first; 
        int u = filaPrioridade.top().second;
        filaPrioridade.pop();
        if (d_u > dist[u]) {
            continue;
        }

        for (auto& conexao : grafo[u]) {
            int vertice = conexao.first;
            int peso = conexao.second;
            if (dist[u] + peso < dist[vertice]) {
                dist[vertice] = dist[u] + peso;
                filaPrioridade.push({dist[vertice], vertice});
            }
        }
    }

    if (dist[numLocaisConhecidos] == INF) {
        cout << "Preso no IDP" << endl;
    } else {
        cout << "Distancia para chegar em casa: " << dist[numLocaisConhecidos] << endl;
    }
}