#include <bits/stdc++.h>
using namespace std;

int bfs(int noInicial, int noFinal, int numPontosMonitorados, const vector<vector<int>>& grafo);

int main() {
    int numPontosMonitorados, numCorredores;
    cin >> numPontosMonitorados >> numCorredores;

    vector<vector<int>> grafo(numPontosMonitorados + 1);
    for (int i = 0; i < numCorredores; ++i) {
        int acesso1, acesso2;
        cin >> acesso1 >> acesso2;
        grafo[acesso1].push_back(acesso2);
        grafo[acesso2].push_back(acesso1);
    }

    int posSeguranca, posExtintor, focoIncendio;
    cin >> posSeguranca >> posExtintor >> focoIncendio;

    int distSeguranca_Extintor = bfs(posSeguranca, posExtintor, numPontosMonitorados, grafo);
    int distExtintor_Foco = bfs(posExtintor, focoIncendio, numPontosMonitorados, grafo);
    cout << distSeguranca_Extintor + distExtintor_Foco << endl;

    return 0;
}

int bfs(int noInicial, int noFinal, int numPontosMonitorados, const vector<vector<int>>& grafo) {
    vector<int> dist(numPontosMonitorados + 1, -1);
    queue<int> fila;
    fila.push(noInicial);
    dist[noInicial] = 0;
    while (!fila.empty()) {
        int noAtual = fila.front();
        fila.pop();
        if (noAtual == noFinal) {
            return dist[noFinal];
        }

        for (int neighbor : grafo[noAtual]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[noAtual] + 1;
                fila.push(neighbor);
            }
        }
    }

    return -1; 
}