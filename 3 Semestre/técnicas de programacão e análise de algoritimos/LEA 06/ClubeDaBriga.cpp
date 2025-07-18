#include <bits/stdc++.h>
using namespace std;

void dfs(int noInicial, const unordered_map<int, vector<int>>& grafo, unordered_set<int>& nosVisitados);

int main() {
    int qntParticipantes, qntPares;
    cin >> qntParticipantes >> qntPares;

    unordered_map<int, vector<int>> grafo;
    for(int i = 0; i < qntPares; i++) {
        int participante1, participante2;
        cin >> participante1 >> participante2;

        grafo[participante1].push_back(participante2);
        grafo[participante2].push_back(participante1);
    }
            
    unordered_set<int> todosNosVisitados;
    int numComponentes = 0;
    for (int i = 1; i <= qntParticipantes; ++i) {
        if (todosNosVisitados.find(i) == todosNosVisitados.end()) {
            numComponentes++;
            dfs(i, grafo, todosNosVisitados);
        }
    }

    cout << numComponentes << " gangue(s) no clube da briga" << endl;
}

void dfs(int noInicial, const unordered_map<int, vector<int>>& grafo, unordered_set<int>& nosVisitados) {
    stack<int> pilha;
    pilha.push(noInicial);
    nosVisitados.insert(noInicial);

    while (!pilha.empty()) {
        int noAtual = pilha.top();
        pilha.pop();
        auto it = grafo.find(noAtual);
        if (it != grafo.end()) {
            for (int noVisinho : it->second) {
                if (!nosVisitados.count(noVisinho)) {
                    nosVisitados.insert(noVisinho);
                    pilha.push(noVisinho);
                }
            }
        }
    }
}