#include <iostream>
#include <string>
#include <cctype> // Para a função tolower()

using namespace std;

string xoring(string R, string S) {
  string T = "";
  for (int i = 0; i < R.length(); i++) {
    if (tolower(R[i]) == tolower(S[i])) { // Compara as letras em caixa baixa
      T += R[i]; // Se as letras forem iguais, mantém a caixa original
    } else {
      // Se as letras forem diferentes, mas a mesma letra em caixa diferente,
      // converte para caixa baixa.
      T += tolower(R[i]); 
    }
  }
  return T;
}

int main() {
  int n;
  cin >> n; // Lê o número de casos de teste

  for (int i = 0; i < n; i++) {
    string R, S;
    cin >> R >> S; // Lê as strings R e S

    string T = xoring(R, S); // Calcula a string T
    cout << T << endl; // Imprime a string T
  }

  return 0;
}