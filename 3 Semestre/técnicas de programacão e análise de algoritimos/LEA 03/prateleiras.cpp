#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Função de comparação para ordenar os títulos
bool compararTitulos(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() < b.length(); // Ordena por tamanho (crescente)
    }
    return a < b; // Se o tamanho for igual, ordena lexicograficamente
}

int main() {
    int N;
    cin >> N;
    cin.ignore(); // Consumir a quebra de linha após ler N

    vector<string> titulos(N);
    for (int i = 0; i < N; ++i) {
        getline(cin, titulos[i]); // Lê cada título, incluindo espaços
    }

    // Ordena os títulos usando a função de comparação
    sort(titulos.begin(), titulos.end(), compararTitulos);

    // Imprime os títulos ordenados
    for (const string& titulo : titulos) {
        cout << titulo << endl;
    }

    return 0;
}
