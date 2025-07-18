#include <iostream>
using namespace std;

int main() {
    int tam = 0;
    cin >> tam;

    long long int resultado = (1LL * tam * (tam + 1)) / 2;
    long long int num, soma = 0;

    for (int i = 0; i < tam - 1; i++) {
        cin >> num;
        if (num < 1 || num > tam) cerr << "Número fora do intervalo esperado!" << endl;
        soma += num;
    }

    cout << (resultado - soma) << endl;
}