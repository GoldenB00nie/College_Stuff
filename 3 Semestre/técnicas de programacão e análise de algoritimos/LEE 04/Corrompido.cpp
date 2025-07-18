#include <bits/stdc++.h>
using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int qntArquivos;
    cin >> qntArquivos;

    for(int i = 0; i < qntArquivos; i++) {
        int qntLinhas;
        cin >> qntLinhas;

        map<int, map<string, int>> alunos;
        for(int j = 0; j < qntLinhas; j++) {
            int matricula;
            cin >> matricula;

            string disciplina;
            cin >> disciplina;

            if(alunos[matricula].count(disciplina) == 0) alunos[matricula][disciplina] = 0;
            alunos[matricula][disciplina]++;
        }

        int countErros = 0;
        for(map<int, map<string, int>>::iterator it = alunos.begin(); it != alunos.end(); it++) {
            for(map<string, int>::iterator at = it->second.begin(); at != it->second.end(); at++) {
                if(at->second != 1) {
                    countErros += at->second -1;
                }
            }
        }

        if(countErros == 0) cout << "Arquivo OK" << endl;
        else cout << "Corrompido com " << to_string(countErros) << " erro(s)" << endl;
    }
}