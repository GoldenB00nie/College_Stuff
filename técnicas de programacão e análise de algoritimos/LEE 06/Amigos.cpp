#include <bits/stdc++.h>
using namespace std;

void dfs(int noInicial, const unordered_map<int, vector<int>>& grafo, unordered_set<int>& nosVisitados);

int main() {
    int qntAlunos, qntAmizades;
    cin >> qntAlunos >> qntAmizades;

    unordered_map<int, vector<int>> grafo;
    for(int i = 0; i < qntAmizades; i++) {
        int amigo1, amigo2;
        cin >> amigo1 >> amigo2;

        grafo[amigo1].push_back(amigo2);
        grafo[amigo2].push_back(amigo1);
    }
            
    unordered_set<int> todosNosVisitados;
    int numComponentes = 0;
    for (int i = 1; i <= qntAlunos; ++i) {
        if (todosNosVisitados.find(i) == todosNosVisitados.end()) {
            numComponentes++;
            dfs(i, grafo, todosNosVisitados);
        }
    }

    if (numComponentes == 1) {
        cout << "Todo mundo eh amigo de todo mundo" << endl;
    } else {
        cout << "Varios grupos de amigos" << endl;
    }
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