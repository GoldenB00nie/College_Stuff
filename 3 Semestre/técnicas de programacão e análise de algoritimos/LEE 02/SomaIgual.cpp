#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool possuiSomaIgual(vector<int> numeros, int valorAhProcurar);

int main() {
    int casosTeste;
    cin >> casosTeste;

    for(int i = 0; i < casosTeste; i++) {
        int qntNums, num;
        vector<int> numeros;
        
        cin >> qntNums;
        
        for(int j = 0; j < qntNums; j++) {
            cin >> num;
            numeros.push_back(num);
        }

        int valorAhProcurar;
        cin >> valorAhProcurar;

        if(possuiSomaIgual(numeros, valorAhProcurar)) cout << "SIM" << endl;
        else cout << "NAO" << endl;
    }
}

bool possuiSomaIgual(vector<int> numeros, int valorAhProcurar) {
    sort(numeros.begin(), numeros.end());
    int esquerda = 0, direita = numeros.size() - 1;
    while(esquerda < direita) {
        int soma = numeros[esquerda] + numeros[direita];
        if(soma == valorAhProcurar) return true;
        if(soma < valorAhProcurar) esquerda++;
        else direita--;
    }
    return false;
}
