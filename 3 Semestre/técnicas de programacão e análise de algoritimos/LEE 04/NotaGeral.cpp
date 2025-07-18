#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int qntAlunos;
    scanf(" %d", &qntAlunos);
 
    vector<int> listaNotas(11, 0);
    for(int i = 0; i < qntAlunos; i++) {
        int notaAluno;
        scanf(" %d", &notaAluno);

        listaNotas[notaAluno]++;
    }

    for(int i = 0; i < listaNotas.size(); i++) {
        if(listaNotas[i] == 0) continue;
        else {
            for(int j = 0; j < listaNotas[i]; j++) {
                printf("%d\n", i);
            }
        }
    }
}