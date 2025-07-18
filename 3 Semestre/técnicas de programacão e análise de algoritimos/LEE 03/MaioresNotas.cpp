#include <bits/stdc++.h>
using namespace std;

int buscaBinaria(vector<int>& notas, int notaDeCorte);

int main() {
    int qntAlunos, qntConsultas;
    cin >> qntAlunos >> qntConsultas;

    vector<int> notas(qntAlunos);
    for(int i = 0; i < qntAlunos; i++) {
        cin >> notas[i];
    }

    for(int i = 0; i < qntConsultas; i++) {
        int NotaDeCorte;
        cin >> NotaDeCorte;

        int qntNotasMaioresQCorte = notas.size() - buscaBinaria(notas, NotaDeCorte);
        cout << qntNotasMaioresQCorte << " notas maiores que " << NotaDeCorte << endl;
    }
}

int buscaBinaria(vector<int>& notas, int notaDeCorte) {
    int inicio = 0, meio, fim = notas.size() -1;
    while(inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;
        if(notas[meio] > notaDeCorte) fim = meio -1;
        else inicio = meio +1;
    }
    return inicio;
}