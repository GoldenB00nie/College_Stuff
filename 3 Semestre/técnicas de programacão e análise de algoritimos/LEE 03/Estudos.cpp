#include <bits/stdc++.h>
using namespace std;

int buscaBinaria(vector<int> exerciciosCapitulos, int maxSessoes);

int main() {
    int qntCapitulos, sessoes;
    cin >> qntCapitulos >> sessoes;

    vector<int> exerciciosCapitulos(qntCapitulos);
    for(int i = 0; i < qntCapitulos; i++) {
        cin >> exerciciosCapitulos[i];
    }

    sort(exerciciosCapitulos.begin(), exerciciosCapitulos.end());
    cout << buscaBinaria(exerciciosCapitulos, sessoes);
}

bool pode(vector<int> exerciciosCapitulos, int valorMaxExercicios, int maxSessoes) {
    int totalSessoes = 0;
    for(int qntExerciciosNoCapitulo : exerciciosCapitulos) {
        totalSessoes += (qntExerciciosNoCapitulo + valorMaxExercicios -1) / valorMaxExercicios;
        if(totalSessoes > maxSessoes) return false;
    }

    return true;
}

int buscaBinaria(vector<int> exerciciosCapitulos, int maxSessoes) {
    int numMin = 1, numMax = exerciciosCapitulos[exerciciosCapitulos.size() -1], resposta = numMax;
    while(numMin <= numMax) {
        int numMeio = numMin + (numMax - numMin) / 2;
        if(pode(exerciciosCapitulos, numMeio, maxSessoes)) {
            resposta = numMeio;
            numMax = numMeio -1;
        }

        else numMin = numMeio +1;
    }

    return resposta;
}