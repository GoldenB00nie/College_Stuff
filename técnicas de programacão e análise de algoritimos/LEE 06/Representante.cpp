#include <bits/stdc++.h>
using namespace std;

int acharTamanhoComponente(int noInicial, const unordered_map<int, vector<int>>& grafo, unordered_set<int>& visitados);

int main() {
    int numAlunos, numDuplas;
    cin >> numAlunos >> numDuplas;

    unordered_map<int, vector<int>> grafo;
    for (int i = 0; i < numDuplas; ++i) {
        int aluno1, aluno2;
        cin >> aluno1 >> aluno2;
        grafo[aluno1].push_back(aluno2);
        grafo[aluno2].push_back(aluno1);
    }

    unordered_set<int> todosNosVisitados;
    int numMaxGrupo = 0;
    for (int i = 1; i <= numAlunos; ++i) {
        if (todosNosVisitados.find(i) == todosNosVisitados.end()) {
            int tamanhoGrupoAtual = acharTamanhoComponente(i, grafo, todosNosVisitados);
            numMaxGrupo = max(numMaxGrupo, tamanhoGrupoAtual);
        }
    }

    cout << "O grupo mais numeroso tem " << numMaxGrupo << " aluno(s)" << endl;
}

int acharTamanhoComponente(int noInicial, const unordered_map<int, vector<int>>& grafo, unordered_set<int>& visitados) {
    
    stack<int> pilha;
    pilha.push(noInicial);
    visitados.insert(noInicial);
    int tamanhoComponenteAtual = 0;

    while (!pilha.empty()) {
        int noAtual = pilha.top();
        pilha.pop();
        tamanhoComponenteAtual++;
        auto it = grafo.find(noAtual);
        if (it != grafo.end()) {
            for (int visinho : it->second) {
                if (!visitados.count(visinho)) {
                    visitados.insert(visinho);
                    pilha.push(visinho);
                }
            }
        }
    }
    return tamanhoComponenteAtual;
}